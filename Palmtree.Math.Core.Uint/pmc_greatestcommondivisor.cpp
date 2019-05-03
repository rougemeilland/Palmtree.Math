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

    static void GreatestCommonDivisor_Imp(__UNIT_TYPE* p1_buf, __UNIT_TYPE* p2_buf, __UNIT_TYPE word_count, __UNIT_TYPE *w_buf, __UNIT_TYPE *w_buf_count)
    {
        __UNIT_TYPE* u = p1_buf;
        __UNIT_TYPE* v = p2_buf;
        for (;;)
        {
            while (word_count > 0 && u[word_count - 1] == 0 && v[word_count - 1] == 0)
                --word_count;
            if (word_count <= 0)
            {
                // このルートへの到達はあり得ないはず。
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;GreatestCommonDivisor_Imp;1");
            }
            int c = Compare_Imp(u, v, word_count);
            if (c == 0)
            {
                // u == v の場合

                // GCD を u として復帰
                _COPY_MEMORY_UNIT(w_buf, u, word_count);
                *w_buf_count = word_count;
                return;
            }
            if (c < 0)
            {
                __UNIT_TYPE* tt = u;
                u = v;
                v = tt;
            }
            // この時点で u > v かつ u と v はともに奇数である

            Subtruct_Imp(u, word_count, v, word_count, u, word_count);

            // この時点で u は偶数

            // u が奇数になるまで u を右シフトする
            __UNIT_TYPE* t_ptr = u;
            int tz_count = 0;
            while (*t_ptr == 0)
            {
                ++t_ptr;
                tz_count += __UNIT_TYPE_BIT_COUNT;
            }
            tz_count += _TZCNT_ALT_UNIT(*t_ptr);
            if (tz_count > 0)
                RightShift_Imp(u, word_count, tz_count, u, TRUE);
        }
    }

    static __UNIT_TYPE GreatestCommonDivisor_1W_Imp(__UNIT_TYPE u, __UNIT_TYPE v)
    {
        int k;
        {
            int u_tz_count = _TZCNT_ALT_UNIT(u);
            int v_tz_count = _TZCNT_ALT_UNIT(v);
            k = u_tz_count < v_tz_count ? u_tz_count : v_tz_count;
            if (u_tz_count > 0)
                u >>= u_tz_count;
            if (v_tz_count > 0)
                v >>= v_tz_count;
        }
        for (;;)
        {
            if (u == 0 || v == 0)
            {
                // このルートへの到達はあり得ないはず。
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_greatestcommondivisor.cpp;GreatestCommonDivisor_1W_Imp;1");
            }
            if (u == v)
            {
                // u == v の場合

                // GCD を u として復帰
                return (u << k);
            }
            if (u < v)
            {
                __UNIT_TYPE tt = u;
                u = v;
                v = tt;
            }
            // この時点で u > v かつ u と v はともに奇数である

            u = u - v;

            // この時点で u は偶数

            // u が奇数になるまで u を右シフトする
            {
                int u_tz_count = _TZCNT_ALT_UNIT(u);
                if (u_tz_count > 0)
                    u >>= u_tz_count;
            }
        }
    }

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
                if (u->UNIT_WORD_COUNT <= 1)
                {
                    // u と v がともに 1 ワードで表現できる場合
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(__UNIT_TYPE_BIT_COUNT);
                    w->BLOCK[0] = GreatestCommonDivisor_1W_Imp(u->BLOCK[0], v);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
                else
                {
                    // u と v のどちらかが 1 ワードで表現できない場合
                    __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
                    __UNIT_TYPE work_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_bit_count);
                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_bit_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(work_bit_count);
                    __UNIT_TYPE u_tzcnt = u->TRAILING_ZERO_BITS_COUNT;
                    __UNIT_TYPE v_tzcnt = _TZCNT_ALT_UNIT(v);
                    __UNIT_TYPE k = _MINIMUM_UNIT(u_tzcnt, v_tzcnt);
                    if (u_tzcnt > 0)
                        RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, u_tzcnt, work_u_buf, FALSE);
                    else
                        _COPY_MEMORY_UNIT(work_u_buf, u->BLOCK, u->UNIT_WORD_COUNT);
                    work_v_buf[0] = v >> v_tzcnt;
                    __UNIT_TYPE w_buf_count;
                    GreatestCommonDivisor_Imp(work_u_buf, work_v_buf, _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT), w->BLOCK, &w_buf_count);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(w);
#endif
                    root.DeallocateBlock(work_v_buf);
                    root.DeallocateBlock(work_u_buf);
                    LeftShift_Imp(w->BLOCK, w_buf_count, k, w->BLOCK, TRUE);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
            }
        }
    }

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
                        if (u->UNIT_WORD_COUNT <= 1)
                        {
                            // u と v がともに 1 ワードで表現できる場合
                            NUMBER_OBJECT_UINT* w = root.AllocateNumber(__UNIT_TYPE_BIT_COUNT);
                            w->BLOCK[0] = GreatestCommonDivisor_1W_Imp(u->BLOCK[0], v_lo);
#ifdef _DEBUG
                            root.CheckNumber(w);
#endif
                            CommitNumber(tc, w);
                            root.UnlinkNumber(w);
                            return (w);
                        }
                        else
                        {
                            // u と v のどちらかが 1 ワードで表現できない場合
                            __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                            __UNIT_TYPE work_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                            __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_bit_count);
                            __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_bit_count);
                            NUMBER_OBJECT_UINT* w = root.AllocateNumber(work_bit_count);

                            __UNIT_TYPE u_tzcnt = u->TRAILING_ZERO_BITS_COUNT;
                            __UNIT_TYPE v_tzcnt = _TZCNT_ALT_UNIT(v_lo);
                            __UNIT_TYPE k = _MINIMUM_UNIT(u_tzcnt, v_tzcnt);
                            if (u_tzcnt > 0)
                                RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, u_tzcnt, work_u_buf, FALSE);
                            else
                                _COPY_MEMORY_UNIT(work_u_buf, u->BLOCK, u->UNIT_WORD_COUNT);
                            work_v_buf[0] = v_lo >> v_tzcnt;

                            __UNIT_TYPE w_buf_count;
                            GreatestCommonDivisor_Imp(work_u_buf, work_v_buf, _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT), w->BLOCK, &w_buf_count);
#ifdef _DEBUG
                            root.CheckBlock(work_u_buf);
                            root.CheckBlock(work_v_buf);
                            root.CheckNumber(w);
#endif
                            root.DeallocateBlock(work_v_buf);
                            root.DeallocateBlock(work_u_buf);

                            LeftShift_Imp(w->BLOCK, w_buf_count, k, w->BLOCK, TRUE);
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
                        // y の値が 32bit では表現できない場合
                        ResourceHolderUINT root(tc);
                        __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                        __UNIT_TYPE work_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                        __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_bit_count);
                        __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_bit_count);
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(work_bit_count);

                        __UNIT_TYPE u_tzcnt = u->TRAILING_ZERO_BITS_COUNT;
                        __UNIT_TYPE v_tzcnt = v_lo == 0 ? 32 + _TZCNT_ALT_UNIT(v_hi) : _TZCNT_ALT_UNIT(v_lo);
                        __UNIT_TYPE k = _MINIMUM_UNIT(u_tzcnt, v_tzcnt);
                        if (u_tzcnt > 0)
                            RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, u_tzcnt, work_u_buf, FALSE);
                        else
                            _COPY_MEMORY_UNIT(work_u_buf, u->BLOCK, u->UNIT_WORD_COUNT);
                        work_v_buf[0] = v_lo;
                        work_v_buf[1] = v_hi;
                        if (v_tzcnt > 0)
                            RightShift_Imp(work_v_buf, 2, v_tzcnt, work_v_buf, TRUE);

                        __UNIT_TYPE w_buf_count;
                        GreatestCommonDivisor_Imp(work_u_buf, work_v_buf, _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT), w->BLOCK, &w_buf_count);
#ifdef _DEBUG
                        root.CheckBlock(work_u_buf);
                        root.CheckBlock(work_v_buf);
                        root.CheckNumber(w);
#endif
                        root.DeallocateBlock(work_v_buf);
                        root.DeallocateBlock(work_u_buf);

                        LeftShift_Imp(w->BLOCK, w_buf_count, k, w->BLOCK, TRUE);
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
                    if (u->UNIT_WORD_COUNT <= 1)
                    {
                        // u と v がともに 1 ワードで表現できる場合
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(__UNIT_TYPE_BIT_COUNT);
                        w->BLOCK[0] = GreatestCommonDivisor_1W_Imp(u->BLOCK[0], (__UNIT_TYPE)v);
#ifdef _DEBUG
                        root.CheckNumber(w);
#endif
                        CommitNumber(tc, w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                    else
                    {
                        // u と v のどちらかが 1 ワードで表現できない場合
                        __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                        __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                        __UNIT_TYPE work_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);

                        __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_bit_count);
                        __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_bit_count);
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(work_bit_count);
                        __UNIT_TYPE u_tzcnt = u->TRAILING_ZERO_BITS_COUNT;
                        __UNIT_TYPE v_tzcnt = _TZCNT_ALT_UNIT((__UNIT_TYPE)v);
                        __UNIT_TYPE k = _MINIMUM_UNIT(u_tzcnt, v_tzcnt);
                        if (u_tzcnt > 0)
                            RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, u_tzcnt, work_u_buf, FALSE);
                        else
                            _COPY_MEMORY_UNIT(work_u_buf, u->BLOCK, u->UNIT_WORD_COUNT);
                        work_v_buf[0] = (__UNIT_TYPE)(v >> v_tzcnt);

                        __UNIT_TYPE w_buf_count;
                        GreatestCommonDivisor_Imp(work_u_buf, work_v_buf, _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT), w->BLOCK, &w_buf_count);
#ifdef _DEBUG
                        root.CheckBlock(work_u_buf);
                        root.CheckBlock(work_v_buf);
                        root.CheckNumber(w);
#endif
                        root.DeallocateBlock(work_v_buf);
                        root.DeallocateBlock(work_u_buf);

                        LeftShift_Imp(w->BLOCK, w_buf_count, k, w->BLOCK, TRUE);
#ifdef _DEBUG
                        root.CheckNumber(w);
#endif
                        CommitNumber(tc, w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                }
            }
        }
    }

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
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                __UNIT_TYPE work_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count);
                if (work_bit_count <= __UNIT_TYPE_BIT_COUNT)
                {
                    // u と v がともに 1 ワードで表現できる場合
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(__UNIT_TYPE_BIT_COUNT);
                    w->BLOCK[0] = GreatestCommonDivisor_1W_Imp(u->BLOCK[0], v->BLOCK[0]);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
                else
                {
                    // u と v のどちらかが 1 ワードで表現できない場合
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_bit_count);
                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_bit_count);
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(work_bit_count);

                    __UNIT_TYPE u_tzcnt = u->TRAILING_ZERO_BITS_COUNT;
                    __UNIT_TYPE v_tzcnt = v->TRAILING_ZERO_BITS_COUNT;
                    __UNIT_TYPE k = _MINIMUM_UNIT(u_tzcnt, v_tzcnt);
                    if (u_tzcnt > 0)
                        RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, u_tzcnt, work_u_buf, FALSE);
                    else
                        _COPY_MEMORY_UNIT(work_u_buf, u->BLOCK, u->UNIT_WORD_COUNT);
                    if (v_tzcnt > 0)
                        RightShift_Imp(v->BLOCK, v->UNIT_WORD_COUNT, v_tzcnt, work_v_buf, FALSE);
                    else
                        _COPY_MEMORY_UNIT(work_v_buf, v->BLOCK, v->UNIT_WORD_COUNT);

                    __UNIT_TYPE w_buf_count;
                    GreatestCommonDivisor_Imp(work_u_buf, work_v_buf, _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT), w->BLOCK, &w_buf_count);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(w);
#endif
                    root.DeallocateBlock(work_v_buf);
                    root.DeallocateBlock(work_u_buf);

                    if (k > 0)
                        LeftShift_Imp(w->BLOCK, w_buf_count, k, w->BLOCK, TRUE);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
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