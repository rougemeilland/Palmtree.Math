﻿/*
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


#include <windows.h>
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    // 32bit 整数との OR 演算の実装。u_countは 0 であってはならない。v は 0 であってはならない。
    static void BitwiseOr_UX_1W(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* w)
    {
        if (u_count == 1)
            w[0] = u[0] | v;
        else
        {
            w[0] = u[0] | v;
            _COPY_MEMORY_UNIT(w + 1, u + 1, u_count - 1);
        }
    }

    // 64bit 整数との OR 演算の実装。u_countは 0 であってはならない。v_hi は 0 であってはならない。
    static void BitwiseOr_UX_2W(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w)
    {
        if (u_count == 1)
        {
            w[0] = u[0] | v_lo;
            w[1] = v_hi;
        }
        else if (u_count == 2)
        {
            w[0] = u[0] | v_lo;
            w[1] = u[1] | v_hi;
        }
        else
        {
            w[0] = u[0] | v_lo;
            w[1] = u[1] | v_hi;
            _COPY_MEMORY_UNIT(w + 2, u + 2, u_count - 2);
        }
    }

    // OR 演算の実装。u_countは 0 であってはならない。v_count は 0 であってはならない。u_count >= y_count でなければならない。
    static void BitwiseOr_UX_UX(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w)
    {
        __UNIT_TYPE or_count = v_count;
        __UNIT_TYPE cp_count = u_count - v_count;

        __UNIT_TYPE count = or_count >> 5;
        while (count > 0)
        {
            w[0] = u[0] | v[0];
            w[1] = u[1] | v[1];
            w[2] = u[2] | v[2];
            w[3] = u[3] | v[3];
            w[4] = u[4] | v[4];
            w[5] = u[5] | v[5];
            w[6] = u[6] | v[6];
            w[7] = u[7] | v[7];
            w[8] = u[8] | v[8];
            w[9] = u[9] | v[9];
            w[10] = u[10] | v[10];
            w[11] = u[11] | v[11];
            w[12] = u[12] | v[12];
            w[13] = u[13] | v[13];
            w[14] = u[14] | v[14];
            w[15] = u[15] | v[15];
            w[16] = u[16] | v[16];
            w[17] = u[17] | v[17];
            w[18] = u[18] | v[18];
            w[19] = u[19] | v[19];
            w[20] = u[20] | v[20];
            w[21] = u[21] | v[21];
            w[22] = u[22] | v[22];
            w[23] = u[23] | v[23];
            w[24] = u[24] | v[24];
            w[25] = u[25] | v[25];
            w[26] = u[26] | v[26];
            w[27] = u[27] | v[27];
            w[28] = u[28] | v[28];
            w[29] = u[29] | v[29];
            w[30] = u[30] | v[30];
            w[31] = u[31] | v[31];
            u += 32;
            v += 32;
            w += 32;
            --count;
        }

        if (or_count & 0x10)
        {
            w[0] = u[0] | v[0];
            w[1] = u[1] | v[1];
            w[2] = u[2] | v[2];
            w[3] = u[3] | v[3];
            w[4] = u[4] | v[4];
            w[5] = u[5] | v[5];
            w[6] = u[6] | v[6];
            w[7] = u[7] | v[7];
            w[8] = u[8] | v[8];
            w[9] = u[9] | v[9];
            w[10] = u[10] | v[10];
            w[11] = u[11] | v[11];
            w[12] = u[12] | v[12];
            w[13] = u[13] | v[13];
            w[14] = u[14] | v[14];
            w[15] = u[15] | v[15];
            u += 16;
            v += 16;
            w += 16;
        }

        if (or_count & 0x8)
        {
            w[0] = u[0] | v[0];
            w[1] = u[1] | v[1];
            w[2] = u[2] | v[2];
            w[3] = u[3] | v[3];
            w[4] = u[4] | v[4];
            w[5] = u[5] | v[5];
            w[6] = u[6] | v[6];
            w[7] = u[7] | v[7];
            u += 8;
            v += 8;
            w += 8;
        }

        if (or_count & 0x4)
        {
            w[0] = u[0] | v[0];
            w[1] = u[1] | v[1];
            w[2] = u[2] | v[2];
            w[3] = u[3] | v[3];
            u += 4;
            v += 4;
            w += 4;
        }

        if (or_count & 0x2)
        {
            w[0] = u[0] | v[0];
            w[1] = u[1] | v[1];
            u += 2;
            v += 2;
            w += 2;
        }

        if (or_count & 0x1)
        {
            w[0] = u[0] | v[0];
            u += 1;
            v += 1;
            w += 1;
        }

        _COPY_MEMORY_UNIT(w, u, cp_count);
    }

    static NUMBER_OBJECT_UINT* PMC_BitwiseOr_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 でない場合
                return (From_UI_Imp(tc, v));
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (DuplicateNumber(tc, u));
        }
        else
        {
            // u と v がともに 0 ではない場合
            ResourceHolderUINT root(tc);
            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
            __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
            BitwiseOr_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    PMC_HANDLE_UINT PMC_BitwiseOr_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseor.cpp;PMC_BitwiseOr_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseOr_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_BitwiseOr_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseor.cpp;PMC_BitwiseOr_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseOr_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_BitwiseOr_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 でない場合
                return (From_UL_Imp(tc, v));
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (DuplicateNumber(tc, u));
        }
        else
        {
            // u と v がともに 0 ではない場合
            if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
            {
                // _UINT64_T が 1 ワードで表現しきれない場合
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit で表現可能な場合
                    ResourceHolderUINT root(tc);
                    __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                    __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                    BitwiseOr_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v_lo, w->BLOCK);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
                else
                {
                    // v の値が 32bit では表現できない場合
                    ResourceHolderUINT root(tc);
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                    __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                    BitwiseOr_UX_2W(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo, w->BLOCK);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
            }
            else
            {
                // _UINT64_T が 1 ワードで表現できる場合
                ResourceHolderUINT root(tc);
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                BitwiseOr_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, (__UNIT_TYPE)v, w->BLOCK);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_BitwiseOr_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseor.cpp;PMC_BitwiseOr_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseOr_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_BitwiseOr_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseor.cpp;PMC_BitwiseOr_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseOr_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_BitwiseOr_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
            return (DuplicateNumber(tc, v));
        else if (v->IS_ZERO)
            return (DuplicateNumber(tc, u));
        else
        {
            ResourceHolderUINT root(tc);
            if (u->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
            {
                NUMBER_OBJECT_UINT* t = u;
                u = v;
                v = t;
            }
            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
            __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
            BitwiseOr_UX_UX(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    PMC_HANDLE_UINT PMC_BitwiseOr_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseOr_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_BitwiseOr(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */
