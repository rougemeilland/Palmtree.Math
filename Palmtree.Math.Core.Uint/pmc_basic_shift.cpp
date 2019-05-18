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

#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    __inline static __UNIT_TYPE RightShift_UNIT(__UNIT_TYPE k, __UNIT_TYPE* in_p, _UINT32_T n_lshift_bit_count, _UINT32_T n_rshift_bit_count, __UNIT_TYPE* out_p)
    {
        __UNIT_TYPE data = in_p[0];
        k |= data << n_lshift_bit_count;
        out_p[0] = k;
        k = data >> n_rshift_bit_count;
        return (k);
    }

    static void RightShift_Imp(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T& out_buf)
    {
#ifdef _DEBUG
        if (in_buf.BLOCK_COUNT > 0 && in_buf.BLOCK[in_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;RightShift_Imp;1");
        if (out_buf.BLOCK_COUNT + n / __UNIT_TYPE_BIT_COUNT < in_buf.BLOCK_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;RightShift_Imp;2");
#endif
        // n_word_count ワード右に移動し、更に n_bit_count ビット右に移動する。
        __UNIT_TYPE n_word_count = n / __UNIT_TYPE_BIT_COUNT;
        _UINT32_T n_rshift_bit_count = n % __UNIT_TYPE_BIT_COUNT;
        if (n_rshift_bit_count == 0)
        {
            // シフト数がちょうどワード境界分であれば単にワード単位のデータ移動のみ行う。
            out_buf.CopyFrom(in_buf.Region(n_word_count));
        }
        else
        {
            __UNIT_TYPE* in_ptr = in_buf.BLOCK + n_word_count;
            __UNIT_TYPE* out_ptr = out_buf.BLOCK;
            _UINT32_T n_lshift_bit_count = __UNIT_TYPE_BIT_COUNT - n_rshift_bit_count;
            __UNIT_TYPE k = *in_ptr >> n_rshift_bit_count;
            __UNIT_TYPE t_count = in_buf.BLOCK_COUNT - n_word_count - 1;
            __UNIT_TYPE count = t_count >> 5;
            while (count > 0)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                k = RightShift_UNIT(k, in_ptr + 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 1);
                k = RightShift_UNIT(k, in_ptr + 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 2);
                k = RightShift_UNIT(k, in_ptr + 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 3);
                k = RightShift_UNIT(k, in_ptr + 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 4);
                k = RightShift_UNIT(k, in_ptr + 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 5);
                k = RightShift_UNIT(k, in_ptr + 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 6);
                k = RightShift_UNIT(k, in_ptr + 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 7);
                k = RightShift_UNIT(k, in_ptr + 9, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 8);
                k = RightShift_UNIT(k, in_ptr + 10, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 9);
                k = RightShift_UNIT(k, in_ptr + 11, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 10);
                k = RightShift_UNIT(k, in_ptr + 12, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 11);
                k = RightShift_UNIT(k, in_ptr + 13, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 12);
                k = RightShift_UNIT(k, in_ptr + 14, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 13);
                k = RightShift_UNIT(k, in_ptr + 15, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 14);
                k = RightShift_UNIT(k, in_ptr + 16, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 15);
                k = RightShift_UNIT(k, in_ptr + 17, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 16);
                k = RightShift_UNIT(k, in_ptr + 18, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 17);
                k = RightShift_UNIT(k, in_ptr + 19, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 18);
                k = RightShift_UNIT(k, in_ptr + 20, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 19);
                k = RightShift_UNIT(k, in_ptr + 21, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 20);
                k = RightShift_UNIT(k, in_ptr + 22, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 21);
                k = RightShift_UNIT(k, in_ptr + 23, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 22);
                k = RightShift_UNIT(k, in_ptr + 24, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 23);
                k = RightShift_UNIT(k, in_ptr + 25, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 24);
                k = RightShift_UNIT(k, in_ptr + 26, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 25);
                k = RightShift_UNIT(k, in_ptr + 27, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 26);
                k = RightShift_UNIT(k, in_ptr + 28, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 27);
                k = RightShift_UNIT(k, in_ptr + 29, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 28);
                k = RightShift_UNIT(k, in_ptr + 30, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 29);
                k = RightShift_UNIT(k, in_ptr + 31, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 30);
                k = RightShift_UNIT(k, in_ptr + 32, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 31);
                --count;
                in_ptr += 32;
                out_ptr += 32;
            }

            if (t_count & 0x10)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                k = RightShift_UNIT(k, in_ptr + 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 1);
                k = RightShift_UNIT(k, in_ptr + 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 2);
                k = RightShift_UNIT(k, in_ptr + 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 3);
                k = RightShift_UNIT(k, in_ptr + 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 4);
                k = RightShift_UNIT(k, in_ptr + 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 5);
                k = RightShift_UNIT(k, in_ptr + 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 6);
                k = RightShift_UNIT(k, in_ptr + 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 7);
                k = RightShift_UNIT(k, in_ptr + 9, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 8);
                k = RightShift_UNIT(k, in_ptr + 10, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 9);
                k = RightShift_UNIT(k, in_ptr + 11, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 10);
                k = RightShift_UNIT(k, in_ptr + 12, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 11);
                k = RightShift_UNIT(k, in_ptr + 13, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 12);
                k = RightShift_UNIT(k, in_ptr + 14, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 13);
                k = RightShift_UNIT(k, in_ptr + 15, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 14);
                k = RightShift_UNIT(k, in_ptr + 16, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 15);
                in_ptr += 16;
                out_ptr += 16;
            }

            if (t_count & 0x8)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                k = RightShift_UNIT(k, in_ptr + 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 1);
                k = RightShift_UNIT(k, in_ptr + 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 2);
                k = RightShift_UNIT(k, in_ptr + 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 3);
                k = RightShift_UNIT(k, in_ptr + 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 4);
                k = RightShift_UNIT(k, in_ptr + 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 5);
                k = RightShift_UNIT(k, in_ptr + 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 6);
                k = RightShift_UNIT(k, in_ptr + 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 7);
                in_ptr += 8;
                out_ptr += 8;
            }

            if (t_count & 0x4)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                k = RightShift_UNIT(k, in_ptr + 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 1);
                k = RightShift_UNIT(k, in_ptr + 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 2);
                k = RightShift_UNIT(k, in_ptr + 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 3);
                in_ptr += 4;
                out_ptr += 4;
            }

            if (t_count & 0x2)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                k = RightShift_UNIT(k, in_ptr + 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 1);
                in_ptr += 2;
                out_ptr += 2;
            }

            if (t_count & 0x1)
            {
                k = RightShift_UNIT(k, in_ptr + 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr + 0);
                in_ptr += 1;
                out_ptr += 1;
            }

            *out_ptr = k;
            out_buf.Region(in_buf.BLOCK_COUNT - n_word_count).Clear();
        }
    }

    __inline static __UNIT_TYPE LeftShift_UNIT(__UNIT_TYPE k, __UNIT_TYPE* in_p, _UINT32_T n_lshift_bit_count, _UINT32_T n_rshift_bit_count, __UNIT_TYPE* out_p)
    {
        __UNIT_TYPE data = in_p[0];
        k |= data >> n_rshift_bit_count;
        out_p[0] = k;
        k = data << n_lshift_bit_count;
        return (k);
    }

    static void LeftShift_Imp(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T& out_buf)
    {
#ifdef _DEBUG
        if (in_buf.BLOCK_COUNT == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;LeftShift_Imp;1");
        if (in_buf.BLOCK_COUNT > 0 && in_buf.BLOCK[in_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;LeftShift_Imp;2");
        if (out_buf.BLOCK_COUNT < in_buf.BLOCK_COUNT + n / __UNIT_TYPE_BIT_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;LeftShift_Imp;3");
#endif
        __UNIT_TYPE n_word_count = n / __UNIT_TYPE_BIT_COUNT;
        _UINT32_T n_lshift_bit_count = n % __UNIT_TYPE_BIT_COUNT;
        if (n_lshift_bit_count == 0)
        {
            // シフト数がちょうどワード境界分であれば単にワード単位のデータ移動のみ行う。
            out_buf.Region(n_word_count).ReverseCopyFrom(in_buf);
            out_buf.Region(0, n_word_count).Clear();
        }
        else
        {
            __UNIT_TYPE* in_ptr = in_buf.BLOCK + in_buf.BLOCK_COUNT - 1;
            __UNIT_TYPE* out_ptr = out_buf.BLOCK + in_buf.BLOCK_COUNT - 1 + n_word_count;
            _UINT32_T n_rshift_bit_count = __UNIT_TYPE_BIT_COUNT - n_lshift_bit_count;
            __UNIT_TYPE k;
            {
                // 最上位 1 ワードのシフト
                // シフト結果の最上位 1 ワードが 0 ならば、その 1 ワードは w_buf に格納しない
                __UNIT_TYPE data = in_ptr[0];
                k = data >> n_rshift_bit_count;
                if (k == 0)
                    out_buf.Region(in_buf.BLOCK_COUNT + n_word_count).Clear();
                else
                {
#ifdef _DEBUG
                    if (out_buf.BLOCK_COUNT <= in_buf.BLOCK_COUNT + n_word_count)
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;LeftShift_Imp;1");
#endif
                    out_ptr[1] = k;
                    out_buf.Region(in_buf.BLOCK_COUNT + n_word_count + 1).Clear();
                }
                k = data << n_lshift_bit_count;
            }
            __UNIT_TYPE t_count = in_buf.BLOCK_COUNT - 1;
            __UNIT_TYPE count = t_count >> 5;
            while (count > 0)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                k = LeftShift_UNIT(k, in_ptr - 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 1);
                k = LeftShift_UNIT(k, in_ptr - 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 2);
                k = LeftShift_UNIT(k, in_ptr - 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 3);
                k = LeftShift_UNIT(k, in_ptr - 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 4);
                k = LeftShift_UNIT(k, in_ptr - 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 5);
                k = LeftShift_UNIT(k, in_ptr - 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 6);
                k = LeftShift_UNIT(k, in_ptr - 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 7);
                k = LeftShift_UNIT(k, in_ptr - 9, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 8);
                k = LeftShift_UNIT(k, in_ptr - 10, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 9);
                k = LeftShift_UNIT(k, in_ptr - 11, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 10);
                k = LeftShift_UNIT(k, in_ptr - 12, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 11);
                k = LeftShift_UNIT(k, in_ptr - 13, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 12);
                k = LeftShift_UNIT(k, in_ptr - 14, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 13);
                k = LeftShift_UNIT(k, in_ptr - 15, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 14);
                k = LeftShift_UNIT(k, in_ptr - 16, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 15);
                k = LeftShift_UNIT(k, in_ptr - 17, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 16);
                k = LeftShift_UNIT(k, in_ptr - 18, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 17);
                k = LeftShift_UNIT(k, in_ptr - 19, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 18);
                k = LeftShift_UNIT(k, in_ptr - 20, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 19);
                k = LeftShift_UNIT(k, in_ptr - 21, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 20);
                k = LeftShift_UNIT(k, in_ptr - 22, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 21);
                k = LeftShift_UNIT(k, in_ptr - 23, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 22);
                k = LeftShift_UNIT(k, in_ptr - 24, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 23);
                k = LeftShift_UNIT(k, in_ptr - 25, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 24);
                k = LeftShift_UNIT(k, in_ptr - 26, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 25);
                k = LeftShift_UNIT(k, in_ptr - 27, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 26);
                k = LeftShift_UNIT(k, in_ptr - 28, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 27);
                k = LeftShift_UNIT(k, in_ptr - 29, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 28);
                k = LeftShift_UNIT(k, in_ptr - 30, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 29);
                k = LeftShift_UNIT(k, in_ptr - 31, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 30);
                k = LeftShift_UNIT(k, in_ptr - 32, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 31);
                in_ptr -= 32;
                out_ptr -= 32;
                --count;
            }

            if (t_count & 0x10)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                k = LeftShift_UNIT(k, in_ptr - 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 1);
                k = LeftShift_UNIT(k, in_ptr - 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 2);
                k = LeftShift_UNIT(k, in_ptr - 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 3);
                k = LeftShift_UNIT(k, in_ptr - 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 4);
                k = LeftShift_UNIT(k, in_ptr - 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 5);
                k = LeftShift_UNIT(k, in_ptr - 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 6);
                k = LeftShift_UNIT(k, in_ptr - 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 7);
                k = LeftShift_UNIT(k, in_ptr - 9, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 8);
                k = LeftShift_UNIT(k, in_ptr - 10, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 9);
                k = LeftShift_UNIT(k, in_ptr - 11, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 10);
                k = LeftShift_UNIT(k, in_ptr - 12, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 11);
                k = LeftShift_UNIT(k, in_ptr - 13, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 12);
                k = LeftShift_UNIT(k, in_ptr - 14, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 13);
                k = LeftShift_UNIT(k, in_ptr - 15, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 14);
                k = LeftShift_UNIT(k, in_ptr - 16, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 15);
                in_ptr -= 16;
                out_ptr -= 16;
            }

            if (t_count & 0x8)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                k = LeftShift_UNIT(k, in_ptr - 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 1);
                k = LeftShift_UNIT(k, in_ptr - 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 2);
                k = LeftShift_UNIT(k, in_ptr - 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 3);
                k = LeftShift_UNIT(k, in_ptr - 5, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 4);
                k = LeftShift_UNIT(k, in_ptr - 6, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 5);
                k = LeftShift_UNIT(k, in_ptr - 7, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 6);
                k = LeftShift_UNIT(k, in_ptr - 8, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 7);
                in_ptr -= 8;
                out_ptr -= 8;
            }

            if (t_count & 0x4)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                k = LeftShift_UNIT(k, in_ptr - 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 1);
                k = LeftShift_UNIT(k, in_ptr - 3, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 2);
                k = LeftShift_UNIT(k, in_ptr - 4, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 3);
                in_ptr -= 4;
                out_ptr -= 4;
            }

            if (t_count & 0x2)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                k = LeftShift_UNIT(k, in_ptr - 2, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 1);
                in_ptr -= 2;
                out_ptr -= 2;
            }

            if (t_count & 0x1)
            {
                k = LeftShift_UNIT(k, in_ptr - 1, n_lshift_bit_count, n_rshift_bit_count, out_ptr - 0);
                in_ptr -= 1;
                out_ptr -= 1;
            }
            *out_ptr = k;
            out_buf.Region(0, n_word_count).Clear();
        }
    }

    void BasicOperatorEngine::RightShift(_UBASIC_T inout_buf, __UNIT_TYPE n)
    {
        _UBASIC_T in_buf = inout_buf.Shrink();
        if (n == 0)
        {
            // nop
        }
        else if (in_buf.BLOCK_COUNT == 0)
        {
            // nop
        }
        else if (n >= in_buf.BLOCK_COUNT * __UNIT_TYPE_BIT_COUNT)
            in_buf.Clear();
        else
            RightShift_Imp(in_buf, n, inout_buf);
    }

    void BasicOperatorEngine::RightShift(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T out_buf)
    {
#ifdef _DEBUG
        if (in_buf.BLOCK_COUNT > 0 && in_buf.BLOCK[in_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;BasicOperatorEngine::RightShift;1");
#endif
        if (n == 0)
            out_buf.CopyFrom(in_buf);
        else if (n >= in_buf.BLOCK_COUNT * __UNIT_TYPE_BIT_COUNT)
            out_buf.Clear();
        else
            RightShift_Imp(in_buf, n, out_buf);
    }

    void BasicOperatorEngine::LeftShift(_UBASIC_T inout_buf, __UNIT_TYPE n)
    {
        _UBASIC_T in_buf = inout_buf.Shrink();
        if (n == 0)
        {
            // nop
        }
        else if (in_buf.BLOCK_COUNT == 0)
        {
            // nop
        }
        else
            LeftShift_Imp(in_buf, n, inout_buf);
    }

    void BasicOperatorEngine::LeftShift(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T out_buf)
    {
#ifdef _DEBUG
        if (in_buf.BLOCK_COUNT > 0 && in_buf.BLOCK[in_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_shift.cpp;BasicOperatorEngine::LeftShift;1");
#endif
        if (n == 0)
            out_buf.CopyFrom(in_buf);
        else if (in_buf.BLOCK_COUNT == 0)
            out_buf.Clear();
        else
            LeftShift_Imp(in_buf, n, out_buf);
    }
}

/*
 * END OF FILE
 */