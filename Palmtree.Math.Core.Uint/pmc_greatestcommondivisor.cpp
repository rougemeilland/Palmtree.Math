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

    static NUMBER_OBJECT_UINT* PMC_GreatestCommonDivisor_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であり、GCD は一意に存在しないため、エラーを返す。
                throw ArithmeticException(L"引数が2つとも0なのでGCDを一意に求めることができません。");
            }
            else
            {
                // v が 0 ではない場合

                // GCD は v そのものであるため、v を計算結果として返す。
                return (From_UI_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // GCD は u そのものであるため、u を計算結果として返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の GCD を計算する

                ResourceHolderUINT root(tc);

                __UNIT_TYPE v_buf[] = { v };
                __UNIT_TYPE work_buf_count = _MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT));
                __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_buf_count);
                __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_buf_count);
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                Basic::GreatestCommonDivisor(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, work_buf_count, work_v_buf, work_buf_count, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckBlock(work_u_buf);
                root.CheckBlock(work_v_buf);
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

#ifdef _M_IX86
    static NUMBER_OBJECT_UINT* PMC_GreatestCommonDivisor_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であり、GCD は一意に存在しないため、エラーを返す。
                throw ArithmeticException(L"引数が2つとも0なのでGCDを一意に求めることができません。");
            }
            else
            {
                // v が 0 ではない場合

                // GCD は v そのものであるため、v を計算結果として返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // GCD は u そのものであるため、u を計算結果として返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の GCD を計算する

                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit で表現可能な場合

                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE v_buf[] = { v_lo };
                    __UNIT_TYPE work_buf_count = _MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT));
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_buf_count);
                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_buf_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                    Basic::GreatestCommonDivisor(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, work_buf_count, work_v_buf, work_buf_count, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
                else
                {
                    // y の値が 32bit では表現できない場合

                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE v_buf[] = { v_lo, v_hi };
                    __UNIT_TYPE work_buf_count = _MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT));
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_buf_count);
                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_buf_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                    Basic::GreatestCommonDivisor(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, work_buf_count, work_v_buf, work_buf_count, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
            }
        }
    }
#elif defined(_M_X64)
    static NUMBER_OBJECT_UINT* PMC_GreatestCommonDivisor_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であり、GCD は一意に存在しないため、エラーを返す。
                throw ArithmeticException(L"引数が2つとも0なのでGCDを一意に求めることができません。");
            }
            else
            {
                // v が 0 ではない場合

                // GCD は v そのものであるため、v を計算結果として返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // GCD は u そのものであるため、u を計算結果として返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の GCD を計算する

                ResourceHolderUINT root(tc);

                __UNIT_TYPE v_buf[] = { v };
                __UNIT_TYPE work_buf_count = _MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT));
                __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_buf_count);
                __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_buf_count);
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                Basic::GreatestCommonDivisor(u->BLOCK, u->UNIT_WORD_COUNT, v_buf, countof(v_buf), work_u_buf, work_buf_count, work_v_buf, work_buf_count, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckBlock(work_u_buf);
                root.CheckBlock(work_v_buf);
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }
#else
#error unknown platform
#endif


    NUMBER_OBJECT_UINT* PMC_GreatestCommonDivisor_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v->IS_ZERO)
            {
                // v が 0 である場合

                // u と v がともに 0 であり、GCD は一意に存在しないため、エラーを返す。
                throw ArithmeticException(L"引数が2つとも0なのでGCDを一意に求めることができません。");
            }
            else
            {
                // v が 0 ではない場合

                // GCD は v そのものであるため、v を計算結果として返す。
                return (DuplicateNumber(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ZERO)
            {
                // v が 0 である場合

                // GCD は u そのものであるため、u を計算結果として返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の GCD を計算する

                ResourceHolderUINT root(tc);

                __UNIT_TYPE work_buf_count = _MAXIMUM_UNIT(u->UNIT_WORD_COUNT, v->BLOCK_COUNT);
                __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_buf_count);
                __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_buf_count);
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, v->BLOCK_COUNT) + 1);

                Basic::GreatestCommonDivisor(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, work_u_buf, work_buf_count, work_v_buf, work_buf_count, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckBlock(work_u_buf);
                root.CheckBlock(work_v_buf);
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;PMC_GreatestCommonDivisor_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_GreatestCommonDivisor_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;PMC_GreatestCommonDivisor_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_GreatestCommonDivisor_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;PMC_GreatestCommonDivisor_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_GreatestCommonDivisor_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;PMC_GreatestCommonDivisor_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_GreatestCommonDivisor_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_GreatestCommonDivisor_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_GreatestCommonDivisor(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */