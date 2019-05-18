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

    static void OneCompliment_And_BitwiseAnd_UX_UX(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T& w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;2");
        if (u_buf.BLOCK_COUNT > v_buf.BLOCK_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;3");
        if (v_buf.BLOCK_COUNT < 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;3");
#endif
        const __UNIT_TYPE* u_ptr = u_buf.BLOCK;
        const __UNIT_TYPE* v_ptr = v_buf.BLOCK;
        __UNIT_TYPE* w_ptr = w_buf.BLOCK;
        __UNIT_TYPE u_buf_count = u_buf.BLOCK_COUNT;

        __UNIT_TYPE count = u_buf_count >> 5;
        while (count > 0)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            w_ptr[8] = ~u_ptr[8] & v_ptr[8];
            w_ptr[9] = ~u_ptr[9] & v_ptr[9];
            w_ptr[10] = ~u_ptr[10] & v_ptr[10];
            w_ptr[11] = ~u_ptr[11] & v_ptr[11];
            w_ptr[12] = ~u_ptr[12] & v_ptr[12];
            w_ptr[13] = ~u_ptr[13] & v_ptr[13];
            w_ptr[14] = ~u_ptr[14] & v_ptr[14];
            w_ptr[15] = ~u_ptr[15] & v_ptr[15];
            w_ptr[16] = ~u_ptr[16] & v_ptr[16];
            w_ptr[17] = ~u_ptr[17] & v_ptr[17];
            w_ptr[18] = ~u_ptr[18] & v_ptr[18];
            w_ptr[19] = ~u_ptr[19] & v_ptr[19];
            w_ptr[20] = ~u_ptr[20] & v_ptr[20];
            w_ptr[21] = ~u_ptr[21] & v_ptr[21];
            w_ptr[22] = ~u_ptr[22] & v_ptr[22];
            w_ptr[23] = ~u_ptr[23] & v_ptr[23];
            w_ptr[24] = ~u_ptr[24] & v_ptr[24];
            w_ptr[25] = ~u_ptr[25] & v_ptr[25];
            w_ptr[26] = ~u_ptr[26] & v_ptr[26];
            w_ptr[27] = ~u_ptr[27] & v_ptr[27];
            w_ptr[28] = ~u_ptr[28] & v_ptr[28];
            w_ptr[29] = ~u_ptr[29] & v_ptr[29];
            w_ptr[30] = ~u_ptr[30] & v_ptr[30];
            w_ptr[31] = ~u_ptr[31] & v_ptr[31];
            u_ptr += 32;
            v_ptr += 32;
            w_ptr += 32;
            --count;
        }

        if (u_buf_count & 0x10)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            w_ptr[8] = ~u_ptr[8] & v_ptr[8];
            w_ptr[9] = ~u_ptr[9] & v_ptr[9];
            w_ptr[10] = ~u_ptr[10] & v_ptr[10];
            w_ptr[11] = ~u_ptr[11] & v_ptr[11];
            w_ptr[12] = ~u_ptr[12] & v_ptr[12];
            w_ptr[13] = ~u_ptr[13] & v_ptr[13];
            w_ptr[14] = ~u_ptr[14] & v_ptr[14];
            w_ptr[15] = ~u_ptr[15] & v_ptr[15];
            u_ptr += 16;
            v_ptr += 16;
            w_ptr += 16;
        }

        if (u_buf_count & 0x8)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            u_ptr += 8;
            v_ptr += 8;
            w_ptr += 8;
        }

        if (u_buf_count & 0x4)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            u_ptr += 4;
            v_ptr += 4;
            w_ptr += 4;
        }

        if (u_buf_count & 0x2)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            u_ptr += 2;
            v_ptr += 2;
            w_ptr += 2;
        }

        if (u_buf_count & 0x1)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            u_ptr += 1;
            v_ptr += 1;
            w_ptr += 1;
        }

        w_buf.Region(u_buf_count).CopyFrom(v_buf.Region(u_buf_count));
    }

    void BasicOperatorEngine::OneCompliment_And_BitwiseAnd(__UNIT_TYPE u, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_1W;1");
        if (v_buf.BLOCK_COUNT < 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_1W;2");
#endif
        if (u == 0)
            w_buf.CopyFrom(v_buf);
        else if (v_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else
        {
            w_buf.BLOCK[0] = ~u & v_buf.BLOCK[0];
            w_buf.Region(1).CopyFrom(v_buf.Region(1));
        }
    }

    void BasicOperatorEngine::OneCompliment_And_BitwiseAnd(__UNIT_TYPE u_hi, __UNIT_TYPE u_lo, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;1");
        if (v_buf.BLOCK_COUNT < 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_onecompliment_and_bitwiseand.cpp;OneCompliment_And_BitwiseAnd_2W;2");
#endif
        if (u_hi == 0)
            OneCompliment_And_BitwiseAnd(u_lo, v_buf, w_buf);
        else if (v_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else if (v_buf.BLOCK_COUNT == 1)
        {
            w_buf.BLOCK[0] = ~u_lo & v_buf.BLOCK[0];
            w_buf.Region(1).Clear();
        }
        else
        {
            w_buf.BLOCK[0] = ~u_lo & v_buf.BLOCK[0];
            w_buf.BLOCK[1] = ~u_hi & v_buf.BLOCK[1];
            w_buf.Region(2).CopyFrom(v_buf.Region(2));
        }
    }

    void BasicOperatorEngine::OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v, __UNIT_TYPE & w)
    {
        if (v == 0)
            w = 0;
        else if (u_buf.BLOCK_COUNT == 0)
            w = v;
        else
            w = ~u_buf.BLOCK[0] & v;
    }

    void BasicOperatorEngine::OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE & w_hi, __UNIT_TYPE & w_lo)
    {
        if (v_hi == 0)
        {
            OneCompliment_And_BitwiseAnd(u_buf, v_lo, w_lo);
            w_hi = 0;
        }
        else if (u_buf.BLOCK_COUNT == 0)
        {
            w_lo = v_lo;
            w_hi = v_hi;
        }
        else if (u_buf.BLOCK_COUNT == 1)
        {
            w_lo = ~u_buf.BLOCK[0] & v_lo;
            w_hi = v_hi;
        }
        else
        {
            w_lo = ~u_buf.BLOCK[0] & v_lo;
            w_hi = ~u_buf.BLOCK[1] & v_hi;
        }
    }

    void BasicOperatorEngine::OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
        if (u_buf.BLOCK_COUNT == 0)
            w_buf.CopyFrom(v_buf);
        else if (v_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else if (u_buf.BLOCK_COUNT >= v_buf.BLOCK_COUNT)
            OneCompliment_And_BitwiseAnd_UX_UX(u_buf.Region(0, v_buf.BLOCK_COUNT).Shrink(), v_buf, w_buf);
        else
            OneCompliment_And_BitwiseAnd_UX_UX(u_buf, v_buf, w_buf);
    }

}

/*
 * END OF FILE
 */