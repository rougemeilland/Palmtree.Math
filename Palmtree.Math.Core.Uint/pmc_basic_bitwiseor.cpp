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

    // 32bit 整数との OR 演算の実装。u_countは 0 であってはならない。v は 0 であってはならない。
    static void BitwiseOr_UX_1W(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf)
    {
        w_buf.BLOCK[0] = u_buf.BLOCK[0] | v;
        w_buf.Region(1).CopyFrom(u_buf.Region(1));
    }

    // 64bit 整数との OR 演算の実装。u_countは 0 であってはならない。v_hi は 0 であってはならない。
    static void BitwiseOr_UX_2W(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf)
    {
        if (u_buf.BLOCK_COUNT == 1)
        {
            w_buf.BLOCK[0] = u_buf.BLOCK[0] | v_lo;
            w_buf.BLOCK[1] = v_hi;
        }
        else
        {
            w_buf.BLOCK[0] = u_buf.BLOCK[0] | v_lo;
            w_buf.BLOCK[1] = u_buf.BLOCK[1] | v_hi;
            w_buf.Region(2).CopyFrom(u_buf.Region(2));
        }
    }

    // OR 演算の実装。u_countは 0 であってはならない。v_count は 0 であってはならない。u_count >= y_count でなければならない。
    static void BitwiseOr_UX_UX(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
        __UNIT_TYPE* u = u_buf.BLOCK;
        __UNIT_TYPE* v = v_buf.BLOCK;
        __UNIT_TYPE* w = w_buf.BLOCK;
        __UNIT_TYPE or_count = v_buf.BLOCK_COUNT;

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

        w_buf.Region(or_count).CopyFrom(u_buf.Region(or_count));
    }

    void BasicOperatorEngine::BitwiseOr(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseor.cpp;BasicOperatorEngine::BitwiseOr;1");
#endif
        if (v == 0)
            w_buf.CopyFrom(u_buf);
        else if (u_buf.BLOCK_COUNT == 0)
        {
            w_buf.BLOCK[0] = v;
            w_buf.Region(1).Clear();
        }
        else
            BitwiseOr_UX_1W(u_buf, v, w_buf);
    }

    void BasicOperatorEngine::BitwiseOr(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseor.cpp;BasicOperatorEngine::BitwiseOr;1");
#endif
        if (v_hi == 0)
            BitwiseOr(u_buf, v_lo, w_buf);
        else if (u_buf.BLOCK_COUNT == 0)
        {
            w_buf.BLOCK[0] = v_lo;
            w_buf.BLOCK[1] = v_hi;
            w_buf.Region(2).Clear();
        }
        else
            BitwiseOr_UX_2W(u_buf, v_hi, v_lo, w_buf);
    }

    void BasicOperatorEngine::BitwiseOr(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseor.cpp;BasicOperatorEngine::BitwiseOr;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseor.cpp;BasicOperatorEngine::BitwiseOr;2");
#endif
        if (u_buf.BLOCK_COUNT < v_buf.BLOCK_COUNT)
            BitwiseOr(v_buf, u_buf, w_buf);
        else if (v_buf.BLOCK_COUNT == 0)
            w_buf.CopyFrom(u_buf);
        else
            BitwiseOr_UX_UX(u_buf, v_buf, w_buf);
    }

}

/*
 * END OF FILE
 */