/*
 * The MIT License
 *
 * Copyright 2019 Palmtree Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    static _UINT32_T PMC_DivideExactly_UI_UX_Imp(ThreadContext& tc, _UINT32_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // u が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // x と y の商・剰余を計算する

                __UNIT_TYPE temp_q;
                Basic::DivideExactly(u, v->BLOCK, v->UNIT_WORD_COUNT, temp_q);
                return ((_UINT32_T)temp_q);
            }
        }
    }

    _UINT32_T PMC_DivideExactly_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(u))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivideExactly_UI_UX_Imp(tc, u, nv));
    }

    static NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // x と y の商・剰余を計算する
                if (v == 3)
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT);
                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT);

                    Basic::DivideExactlyBy3(u->BLOCK, u->UNIT_WORD_COUNT, work_u_buf, u->UNIT_WORD_COUNT, q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                    __UNIT_TYPE v_buf[] = { v };
                    __UNIT_TYPE work_v_buf[countof(v_buf)];

                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT - countof(v_buf) + 2);

                    Basic::DivideExactly(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, u->UNIT_WORD_COUNT + 1, work_v_buf, countof(work_v_buf), q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(v))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

#ifdef _M_IX86
    static _UINT64_T PMC_DivideExactly_UL_UX_Imp(ThreadContext& tc, _UINT64_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // x が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                _UINT32_T u_hi;
                _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);
                if (u_hi == 0)
                {
                    // u の値が 32bit で表現可能な場合

                    __UNIT_TYPE temp_q;
                    Basic::DivideExactly(u_lo, v->BLOCK, v->UNIT_WORD_COUNT, temp_q);
                    return (temp_q);
                }
                else
                {
                    // v の値が 32bit では表現できない場合

                    if (v->UNIT_WORD_COUNT > 2)
                    {
                        // 明らかに u < v である場合

                        // u != 0 なので、 u は v では割り切れない
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");

                    }
                    else
                    {
                        ResourceHolderUINT root(tc);

                        __UNIT_TYPE u_buf[] = { u_lo, u_hi };
                        __UNIT_TYPE work_u_buf[countof(u_buf) + 1];

                        __UNIT_TYPE* work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);

                        __UNIT_TYPE q_buf[3];

                        Basic::DivideExactly(u_buf, countof(u_buf), v->BLOCK, v->UNIT_WORD_COUNT, work_u_buf, countof(work_u_buf), work_v_buf, v->UNIT_WORD_COUNT, q_buf, countof(q_buf));
#ifdef _DEBUG
                        root.CheckBlock(work_v_buf);
#endif
                        return (_FROMWORDTODWORD(q_buf[1], q_buf[0]));
                    }
                }
            }
        }
    }
#elif defined(_M_X64)
    static _UINT64_T PMC_DivideExactly_UL_UX_Imp(ThreadContext& tc, _UINT64_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // x が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する

                __UNIT_TYPE temp_q;
                Basic::DivideExactly(u, v->BLOCK, v->UNIT_WORD_COUNT, temp_q);
                return (temp_q);
            }
        }
    }
#else
#error unknown platform
#endif

    _UINT64_T PMC_DivideExactly_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(u))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivideExactly_UL_UX_Imp(tc, u, nv));
    }

#ifdef _M_IX86
    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit で表現可能な場合
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                    __UNIT_TYPE v_buf[] = { v_lo };
                    __UNIT_TYPE work_v_buf[countof(v_buf)];

                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT - countof(v_buf) + 2);

                    Basic::DivideExactly(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, u->UNIT_WORD_COUNT + 1, work_v_buf, countof(work_v_buf), q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
                else
                {
                    // v の値が 32bit では表現できない場合
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                    __UNIT_TYPE v_buf[] = { v_lo, v_hi };
                    __UNIT_TYPE work_v_buf[countof(v_buf)];

                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT - countof(v_buf) + 2);

                    Basic::DivideExactly(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, u->UNIT_WORD_COUNT + 1, work_v_buf, countof(work_v_buf), q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }
#elif defined(_M_X64)
    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            // q = 0, r = 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                ResourceHolderUINT root(tc);

                __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                __UNIT_TYPE v_buf[] = { v };
                __UNIT_TYPE work_v_buf[countof(v_buf)];

                NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT - countof(v_buf) + 2);

                Basic::DivideExactly(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, u->UNIT_WORD_COUNT + 1, work_v_buf, countof(work_v_buf), q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckBlock(work_u_buf);
                root.CheckNumber(q);
#endif
                CommitNumber(tc, q);
                if (q->IS_ZERO)
                {
                    root.DeallocateNumber(q);
                    q = &number_object_uint_zero;
                }
                else
                    root.UnlinkNumber(q);
                return (q);
            }
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(v))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // x と y の商・剰余を計算する
                if (u->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
                {
                    // 明らかに u < v である場合

                    // u != 0 なので、u は v では割り切れない
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);

                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(u->UNIT_WORD_COUNT - v->UNIT_WORD_COUNT + 2);

                    Basic::DivideExactly(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, work_u_buf, u->UNIT_WORD_COUNT + 1, work_v_buf, v->UNIT_WORD_COUNT, q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

}


/*
 * END OF FILE
 */
