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

    static _UINT32_T PMC_DivRem_UI_UX_Imp(_UINT32_T u, NUMBER_OBJECT_UINT* v, _UINT32_T* q) noexcept(false)
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

            // q = 0, r = 0 を返す
            if (q != nullptr)
                *q = 0;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = u;
                return (0);
            }
            else
            {
                // u と v がともに 0 ではない場合

                if (q != nullptr)
                {
                    __UNIT_TYPE q_buf;
                    __UNIT_TYPE r_buf;
                    basic_ep.DivRem(u, _UBASIC_T(v), q_buf, r_buf);
                    *q = (_UINT32_T)q_buf;
                    return ((_UINT32_T)r_buf);
                }
                else
                {
                    __UNIT_TYPE r_buf;
                    basic_ep.Remainder(u, _UBASIC_T(v), r_buf);
                    return ((_UINT32_T)r_buf);
                }
            }
        }
    }

    _UINT32_T PMC_DivRem_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(u))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivRem_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivRem_UI_UX_Imp(u, nv, q));
    }

    _UINT32_T PMC_DivRem_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v, NUMBER_OBJECT_UINT** q)
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

            // q = 0, r = 0 を返す

            if (q != nullptr)
                *q = &number_object_uint_zero;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = DuplicateNumber(tc, u);
                return (0);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の商・剰余を計算する

                if (q != nullptr)
                {
                    ResourceHolderUINT root(tc);

                    *q = root.AllocateNumber(u->UNIT_WORD_COUNT);

                    __UNIT_TYPE r_buf;
                    basic_ep.DivRem(_UBASIC_T(u), v, _UBASIC_T(*q), r_buf);
#ifdef _DEBUG
                    root.CheckNumber(*q);
#endif
                    CommitNumber(tc, *q);
                    if ((*q)->IS_ZERO)
                    {
                        root.DeallocateNumber(*q);
                        *q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(*q);
                    return ((_UINT32_T)r_buf);
                }
                else
                {
                    __UNIT_TYPE r_buf;
                    basic_ep.Remainder(_UBASIC_T(u), v, r_buf);
                    return ((_UINT32_T)r_buf);
                }
            }
        }
    }

    _UINT32_T PMC_DivRem_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(v))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivRem_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq;
        if (q != nullptr)
        {
            _UINT32_T r = PMC_DivRem_UX_UI_Imp(tc, nu, v, &nq);
            root.HookNumber(nq);
            *q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (r);
        }
        else
        {
            _UINT32_T r = PMC_DivRem_UX_UI_Imp(tc, nu, v, nullptr);
            return (r);
        }
    }

#ifdef _M_IX86
    static _UINT64_T PMC_DivRem_UL_UX_Imp(_UINT64_T u, NUMBER_OBJECT_UINT* v, _UINT64_T* q) noexcept(false)
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

            // q = 0, r = 0 を返す
            if (q != nullptr)
                *q = 0;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = u;
                return (0);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                _UINT32_T u_hi;
                _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);
                if (u_hi == 0)
                {
                    // u の値が 32bit で表現できる場合

                    if (q != nullptr)
                    {
                        __UNIT_TYPE r_buf;
                        __UNIT_TYPE q_buf;
                        basic_ep.DivRem(u_lo, _UBASIC_T(v), q_buf, r_buf);
                        *q = q_buf;
                        return (r_buf);
                    }
                    else
                    {
                        __UNIT_TYPE r_buf;
                        basic_ep.Remainder(u_lo, _UBASIC_T(v), r_buf);
                        return (r_buf);
                    }
                }
                else
                {
                    // u の値が 32bit では表現できない場合

                    if (q != nullptr)
                    {
                        __UNIT_TYPE u_buf[] = { u_lo, u_hi };
                        __UNIT_TYPE q_buf[countof(u_buf)];
                        __UNIT_TYPE r_buf[countof(u_buf) + 1]; // 演算結果を格納するためには v と同じ大きさだけあれば十分であるが、除算の作業用バッファも兼ねているので余分にとっている。
                        __UNIT_TYPE work_v_buf[2];
                        basic_ep.DivRem(_UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(v), _UBASIC_T(work_v_buf, countof(work_v_buf)), _UBASIC_T(q_buf, countof(q_buf)), _UBASIC_T(r_buf, countof(r_buf)));
                        *q = _FROMWORDTODWORD(q_buf[1], q_buf[0]);
                        return (_FROMWORDTODWORD(r_buf[1], r_buf[0]));
                    }
                    else
                    {
                        __UNIT_TYPE u_buf[] = { u_lo, u_hi };
                        __UNIT_TYPE r_buf[countof(u_buf) + 1]; // 演算結果を格納するためには v と同じ大きさだけあれば十分であるが、除算の作業用バッファも兼ねているので余分にとっている。
                        __UNIT_TYPE work_v_buf[2];
                        basic_ep.Remainder(_UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(v), _UBASIC_T(work_v_buf, countof(work_v_buf)), _UBASIC_T(r_buf, countof(r_buf)));
                        return (_FROMWORDTODWORD(r_buf[1], r_buf[0]));
                    }
                }
            }
        }
    }
#elif defined(_M_X64)
    static _UINT64_T PMC_DivRem_UL_UX_Imp(_UINT64_T u, NUMBER_OBJECT_UINT* v, _UINT64_T* q) noexcept(false)
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

            // q = 0, r = 0 を返す
            if (q != nullptr)
                *q = 0;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = u;
                return (0);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する

                if (q != nullptr)
                {
                    __UNIT_TYPE r_buf;
                    __UNIT_TYPE q_buf;
                    basic_ep.DivRem(u, _UBASIC_T(v), q_buf, r_buf);
                    *q = q_buf;
                    return (r_buf);
                }
                else
                {
                    __UNIT_TYPE r_buf;
                    basic_ep.Remainder(u, _UBASIC_T(v), r_buf);
                    return (r_buf);
                }
            }
        }
    }
#else
#error unknown platform
#endif

    _UINT64_T PMC_DivRem_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(u))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivRem_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivRem_UL_UX_Imp(u, nv, q));
    }

#ifdef _M_IX86
    _UINT64_T PMC_DivRem_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v, NUMBER_OBJECT_UINT** q)
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
            if (q != nullptr)
                *q = &number_object_uint_zero;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = DuplicateNumber(tc, u);
                return (0);
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
                    if (q != nullptr)
                    {
                        ResourceHolderUINT root(tc);

                        *q = root.AllocateNumber(u->UNIT_WORD_COUNT);

                        __UNIT_TYPE r_buf = 0;

                        basic_ep.DivRem(_UBASIC_T(u), v_lo, _UBASIC_T(*q), r_buf);
#ifdef _DEBUG
                        root.CheckNumber(*q);
#endif
                        CommitNumber(tc, *q);
                        if ((*q)->IS_ZERO)
                        {
                            root.DeallocateNumber(*q);
                            *q = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(*q);
                        return (r_buf);
                    }
                    else
                    {
                        __UNIT_TYPE r_buf = 0;
                        basic_ep.Remainder(_UBASIC_T(u), v_lo, r_buf);
                        return (r_buf);
                    }
                }
                else
                {
                    // v の値が 32bit では表現できない場合

                    if (u->UNIT_WORD_COUNT < _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT))
                    {
                        // 明らかに u < v である場合

                        // q = 0, r = u を返す

                        if (q != nullptr)
                            *q = &number_object_uint_zero;
                        if (u->UNIT_WORD_COUNT == 1)
                            return (u->BLOCK[0]);
                        else
                            return (_FROMWORDTODWORD(u->BLOCK[0], u->BLOCK[0]));
                    }
                    else
                    {
                        if (q != nullptr)
                        {
                            ResourceHolderUINT root(tc);

                            __UNIT_TYPE v_buf[] = { v_lo, v_hi };
                            __UNIT_TYPE work_v_buf[countof(v_buf)];

                            *q = root.AllocateNumber(u->UNIT_WORD_COUNT - countof(v_buf) + 1);

                            _UBASIC_T r_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                            basic_ep.DivRem(_UBASIC_T(u), _UBASIC_T(v_buf, countof(v_buf)), _UBASIC_T(work_v_buf, countof(work_v_buf)), _UBASIC_T(*q), r_buf);
#ifdef _DEBUG
                            root.CheckNumber(*q);
                            root.CheckBlock(r_buf);
#endif
                            CommitNumber(tc, *q);
                            if ((*q)->IS_ZERO)
                            {
                                root.DeallocateNumber(*q);
                                *q = &number_object_uint_zero;
                            }
                            else
                                root.UnlinkNumber(*q);
                            return (_FROMWORDTODWORD(r_buf.BLOCK[1], r_buf.BLOCK[0]));
                        }
                        else
                        {
                            ResourceHolderUINT root(tc);

                            __UNIT_TYPE v_buf[] = { v_lo, v_hi };
                            __UNIT_TYPE work_v_buf[countof(v_buf)];

                            _UBASIC_T r_buf = root.AllocateBlock(u->UNIT_WORD_COUNT + 1);

                            basic_ep.Remainder(_UBASIC_T(u), _UBASIC_T(v_buf, countof(v_buf)), _UBASIC_T(work_v_buf, countof(work_v_buf)), r_buf);
#ifdef _DEBUG
                            root.CheckBlock(r_buf);
#endif
                            return (_FROMWORDTODWORD(r_buf.BLOCK[1], r_buf.BLOCK[0]));
                        }
                    }
                }
            }
        }
    }
#elif defined(_M_X64)
    _UINT64_T PMC_DivRem_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v, NUMBER_OBJECT_UINT** q)
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
            if (q != nullptr)
                *q = &number_object_uint_zero;
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = DuplicateNumber(tc, u);
                return (0);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する

                if (q != nullptr)
                {
                    ResourceHolderUINT root(tc);

                    *q = root.AllocateNumber(u->UNIT_WORD_COUNT);

                    __UNIT_TYPE r_buf;

                    basic_ep.DivRem(_UBASIC_T(u), v, _UBASIC_T(*q), r_buf);
#ifdef _DEBUG
                    root.CheckNumber(*q);
#endif
                    CommitNumber(tc, *q);
                    if ((*q)->IS_ZERO)
                    {
                        root.DeallocateNumber(*q);
                        *q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(*q);
                    return (r_buf);
                }
                else
                {
                    __UNIT_TYPE r_buf;
                    basic_ep.Remainder(_UBASIC_T(u), v, r_buf);
                    return (r_buf);
                }
            }
        }
    }
#else
#error unknown platform
#endif

    _UINT64_T PMC_DivRem_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(v))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivRem_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq;
        if (q != nullptr)
        {
            _UINT64_T r = PMC_DivRem_UX_UL_Imp(tc, nu, v, &nq);
            root.HookNumber(nq);
            *q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (r);
        }
        else
        {
            _UINT64_T r = PMC_DivRem_UX_UL_Imp(tc, nu, v, nullptr);
            return (r);
        }
    }

    NUMBER_OBJECT_UINT* PMC_DivRem_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v, NUMBER_OBJECT_UINT** q)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // q = 0, r = 0 を返す
            if (q != nullptr)
                *q = &number_object_uint_zero;
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                if (q != nullptr)
                    *q = DuplicateNumber(tc, u);
                return (&number_object_uint_zero);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                if (u->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
                {
                    // 明らかに u < v である場合

                    // q = 0, r = u を返す

                    if (q != nullptr)
                        *q = &number_object_uint_zero;
                    return (DuplicateNumber(tc, u));
                }
                else
                {

                    // x と y の商・剰余を計算する

                    if (q != nullptr)
                    {
                        ResourceHolderUINT root(tc);

                        *q = root.AllocateNumber(u->UNIT_WORD_COUNT - v->UNIT_WORD_COUNT + 1);
                        NUMBER_OBJECT_UINT* r = root.AllocateNumber(u->UNIT_WORD_COUNT + 1); // 演算結果を格納するためには v->UNIT_WORD_COUNT だけあれば十分であるが、除算の作業用バッファも兼ねているので余分にとっている。
                        _UBASIC_T work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);

                        basic_ep.DivRem(_UBASIC_T(u), _UBASIC_T(v), work_v_buf, _UBASIC_T(*q), _UBASIC_T(r));
#ifdef _DEBUG
                        root.CheckBlock(work_v_buf);
                        root.CheckNumber(*q);
                        root.CheckNumber(r);
#endif
                        root.DeallocateBlock(work_v_buf);
                        CommitNumber(tc, *q);
                        CommitNumber(tc, r);
                        if ((*q)->IS_ZERO)
                        {
                            root.DeallocateNumber(*q);
                            *q = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(*q);
                        if (r->IS_ZERO)
                        {
                            root.DeallocateNumber(r);
                            r = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(r);
                        return (r);
                    }
                    else
                    {
                        ResourceHolderUINT root(tc);

                        NUMBER_OBJECT_UINT* r = root.AllocateNumber(u->UNIT_WORD_COUNT + 1); // 演算結果を格納するためには v->UNIT_WORD_COUNT だけあれば十分であるが、除算の作業用バッファも兼ねているので余分にとっている。
                        _UBASIC_T work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);

                        basic_ep.Remainder(_UBASIC_T(u), _UBASIC_T(v), work_v_buf, _UBASIC_T(r));
#ifdef _DEBUG
                        root.CheckBlock(work_v_buf);
                        root.CheckNumber(r);
#endif
                        root.DeallocateBlock(work_v_buf);
                        CommitNumber(tc, r);
                        if (r->IS_ZERO)
                        {
                            root.DeallocateNumber(r);
                            r = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(r);
                        return (r);
                    }
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivRem_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false)
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
        NUMBER_OBJECT_UINT* nq;
        NUMBER_OBJECT_UINT* nr;

        if (q != nullptr)
        {
            nr = PMC_DivRem_UX_UX_Imp(tc, nu, nv, &nq);
            root.HookNumber(nq);
            root.HookNumber(nr);
            *q = GET_NUMBER_HANDLE(nq);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nq);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            nr = PMC_DivRem_UX_UX_Imp(tc, nu, nv, nullptr);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

    _UINT32_T PMC_Modulo_X_UI(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT32_T v)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(v))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_Modulo_X_UI;1");
        }
        NUMBER_OBJECT_UINT* nu_abs = GET_NUMBER_OBJECT(u_abs, L"u_abs");
        _UINT32_T r = PMC_DivRem_UX_UI_Imp(tc, nu_abs, v, nullptr);
        if (u_sign < 0 && r > 0)
            r = v - r;
        return (r);
    }

    _UINT64_T PMC_Modulo_X_UL(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT64_T v)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(u_abs))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_Modulo_X_UL;1");
        }
        NUMBER_OBJECT_UINT* nu_abs = GET_NUMBER_OBJECT(u_abs, L"u_abs");
        _UINT64_T r = PMC_DivRem_UX_UL_Imp(tc, nu_abs, v, nullptr);
        if (u_sign < 0 && r > 0)
            r = v - r;
        return (r);
    }

    static NUMBER_OBJECT_UINT* PMC_Modulo_X_UX_Imp(ThreadContext& tc, SIGN_T u_sign, NUMBER_OBJECT_UINT* u_abs, NUMBER_OBJECT_UINT* v)
    {
        if (u_abs->IS_ZERO)
        {
            // u が 0 である場合

            // r = 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // r = 0 を返す
                return (&number_object_uint_zero);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // x と y の商・剰余を計算する
                if (u_abs->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
                {
                    // 明らかに u_abs < v である場合

                    // r = u ( u < 0 の場合は v - u)を返す。
                    if (u_abs->IS_ZERO)
                        return (&number_object_uint_zero);
                    else if (u_sign >= 0)
                        return (DuplicateNumber(tc, u_abs));
                    else
                    {
                        ResourceHolderUINT root(tc);

                        NUMBER_OBJECT_UINT* r = root.AllocateNumber(v->UNIT_WORD_COUNT);
                        basic_ep.USubtruct(_UBASIC_T(v), _UBASIC_T(u_abs), _UBASIC_T(r));
#ifdef _DEBUG
                        root.CheckNumber(r);
#endif
                        CommitNumber(tc, r);
#ifdef _DEBUG
                        // このルートで 0 になるはずはない
                        if (r->IS_ZERO)
                            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divrem.cpp;PMC_Modulo_X_UX_Imp;1");
#endif
                        root.UnlinkNumber(r);
                        return (r);
                    }
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    _UBASIC_T work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);

                    NUMBER_OBJECT_UINT* r = root.AllocateNumber(u_abs->UNIT_WORD_COUNT + 1);

                    basic_ep.Remainder(_UBASIC_T(u_abs), _UBASIC_T(v), work_v_buf, _UBASIC_T(r));
                    _UBASIC_T result_r_buf = _UBASIC_T(r).Shrink();
#ifdef _DEBUG
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(r);

                    // r の実際のデータのワード長は v のワード長以下のはずである
                    if (result_r_buf.BLOCK_COUNT > v->UNIT_WORD_COUNT)
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divrem.cpp;PMC_Modulo_X_UX_Imp;2");
#endif

                    if (u_sign < 0 && result_r_buf.BLOCK_COUNT != 0)
                        basic_ep.UNegativeSubtruct(_UBASIC_T(r), _UBASIC_T(v));
                    CommitNumber(tc, r);
                    if (r->IS_ZERO)
                    {
                        root.DeallocateNumber(r);
                        r = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(r);
                    return (r);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_Modulo_X_UX(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nu_abs = GET_NUMBER_OBJECT(u_abs, L"u_abs");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nr = PMC_Modulo_X_UX_Imp(tc, u_sign, nu_abs, nv);
        root.HookNumber(nr);
        PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    static NUMBER_OBJECT_UINT* PMC_Modulo_I_UX_Imp(ThreadContext& tc, SIGN_T u_sign, NUMBER_OBJECT_UINT* v, _UINT32_T r_value)
    {
        if (r_value == 0)
            return (&number_object_uint_zero);
        if (u_sign >= 0)
            return (From_UI_Imp(tc, r_value));
        else
        {
            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* r = root.AllocateNumber(v->UNIT_WORD_COUNT);
            __UNIT_TYPE u_buf[] = { r_value };
            basic_ep.USubtruct(_UBASIC_T(v), _UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(r));
#ifdef _DEBUG
            root.CheckNumber(r);
#endif
            CommitNumber(tc, r);
#ifdef _DEBUG
            // このルートで 0 になるはずはない
            if (r->IS_ZERO)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divrem.cpp;PMC_Modulo_I_UX_Imp;1");
#endif
            root.UnlinkNumber(r);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_Modulo_I_UX(ThreadContext& tc, SIGN_T u_sign, _UINT32_T u_abs, PMC_HANDLE_UINT v)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(u_abs))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_Modulo_I_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        _UINT32_T r_value = PMC_DivRem_UI_UX_Imp(u_abs, nv, nullptr);
        return (GET_NUMBER_HANDLE(PMC_Modulo_I_UX_Imp(tc, u_sign, nv, r_value)));
    }

#ifdef _M_IX86
    static NUMBER_OBJECT_UINT* PMC_Modulo_L_UX_Imp(ThreadContext& tc, SIGN_T u_sign, NUMBER_OBJECT_UINT* v, _UINT64_T r_value)
    {
        if (r_value == 0)
            return (&number_object_uint_zero);
        if (u_sign >= 0)
            return (From_UL_Imp(tc, r_value));
        else
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* r = root.AllocateNumber(v->UNIT_WORD_COUNT);
            _UINT32_T r_value_hi;
            _UINT32_T r_value_lo = _FROMDWORDTOWORD(r_value, &r_value_hi);
            if (r_value_hi != 0)
            {
                __UNIT_TYPE u_buf[] = { r_value_lo, r_value_hi };
                basic_ep.USubtruct(_UBASIC_T(v), _UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(r));
            }
            else
            {
                __UNIT_TYPE u_buf[] = { r_value_lo };
                basic_ep.USubtruct(_UBASIC_T(v), _UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(r));
            }
#ifdef _DEBUG
            root.CheckNumber(r);
#endif
            CommitNumber(tc, r);
#ifdef _DEBUG
            // このルートで 0 になるはずはない
            if (r->IS_ZERO)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divrem.cpp;PMC_Modulo_L_UX_Imp;1");
#endif
            root.UnlinkNumber(r);
            return (r);
        }
    }
#elif defined(_M_X64)
    static NUMBER_OBJECT_UINT* PMC_Modulo_L_UX_Imp(ThreadContext& tc, SIGN_T u_sign, NUMBER_OBJECT_UINT* v, _UINT64_T r_value)
    {
        if (r_value == 0)
            return (&number_object_uint_zero);
        if (u_sign >= 0)
            return (From_UL_Imp(tc, r_value));
        else
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* r = root.AllocateNumber(v->UNIT_WORD_COUNT);
            __UNIT_TYPE u_buf[] = { r_value };
            basic_ep.USubtruct(_UBASIC_T(v), _UBASIC_T(u_buf, countof(u_buf)), _UBASIC_T(r));
#ifdef _DEBUG
            root.CheckNumber(r);
#endif
            CommitNumber(tc, r);
#ifdef _DEBUG
            // このルートで 0 になるはずはない
            if (r->IS_ZERO)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divrem.cpp;PMC_Modulo_L_UX_Imp;1");
#endif
            root.UnlinkNumber(r);
            return (r);
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_Modulo_L_UX(ThreadContext& tc, SIGN_T u_sign, _UINT64_T u_abs, PMC_HANDLE_UINT v)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(u_abs))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_Modulo_L_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        _UINT64_T r_value = PMC_DivRem_UL_UX_Imp(u_abs, nv, nullptr);
        return (GET_NUMBER_HANDLE(PMC_Modulo_L_UX_Imp(tc, u_sign, nv, r_value)));
    }

    PMC_STATUS_CODE Initialize_DivRem(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */