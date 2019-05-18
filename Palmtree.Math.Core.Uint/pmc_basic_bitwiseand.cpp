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

    static void BitwiseAnd_UX_UX(__UNIT_TYPE* u, __UNIT_TYPE*v, __UNIT_TYPE*w, __UNIT_TYPE w_count)
    {
        __UNIT_TYPE count = w_count >> 5;
        while (count != 0)
        {
            w[0] = u[0] & v[0];
            w[1] = u[1] & v[1];
            w[2] = u[2] & v[2];
            w[3] = u[3] & v[3];
            w[4] = u[4] & v[4];
            w[5] = u[5] & v[5];
            w[6] = u[6] & v[6];
            w[7] = u[7] & v[7];
            w[8] = u[8] & v[8];
            w[9] = u[9] & v[9];
            w[10] = u[10] & v[10];
            w[11] = u[11] & v[11];
            w[12] = u[12] & v[12];
            w[13] = u[13] & v[13];
            w[14] = u[14] & v[14];
            w[15] = u[15] & v[15];
            w[16] = u[16] & v[16];
            w[17] = u[17] & v[17];
            w[18] = u[18] & v[18];
            w[19] = u[19] & v[19];
            w[20] = u[20] & v[20];
            w[21] = u[21] & v[21];
            w[22] = u[22] & v[22];
            w[23] = u[23] & v[23];
            w[24] = u[24] & v[24];
            w[25] = u[25] & v[25];
            w[26] = u[26] & v[26];
            w[27] = u[27] & v[27];
            w[28] = u[28] & v[28];
            w[29] = u[29] & v[29];
            w[30] = u[30] & v[30];
            w[31] = u[31] & v[31];
            u += 32;
            v += 32;
            w += 32;
            --count;
        }

        if (w_count & 0x10)
        {
            w[0] = u[0] & v[0];
            w[1] = u[1] & v[1];
            w[2] = u[2] & v[2];
            w[3] = u[3] & v[3];
            w[4] = u[4] & v[4];
            w[5] = u[5] & v[5];
            w[6] = u[6] & v[6];
            w[7] = u[7] & v[7];
            w[8] = u[8] & v[8];
            w[9] = u[9] & v[9];
            w[10] = u[10] & v[10];
            w[11] = u[11] & v[11];
            w[12] = u[12] & v[12];
            w[13] = u[13] & v[13];
            w[14] = u[14] & v[14];
            w[15] = u[15] & v[15];
            u += 16;
            v += 16;
            w += 16;
        }

        if (w_count & 0x8)
        {
            w[0] = u[0] & v[0];
            w[1] = u[1] & v[1];
            w[2] = u[2] & v[2];
            w[3] = u[3] & v[3];
            w[4] = u[4] & v[4];
            w[5] = u[5] & v[5];
            w[6] = u[6] & v[6];
            w[7] = u[7] & v[7];
            u += 8;
            v += 8;
            w += 8;
        }

        if (w_count & 0x4)
        {
            w[0] = u[0] & v[0];
            w[1] = u[1] & v[1];
            w[2] = u[2] & v[2];
            w[3] = u[3] & v[3];
            u += 4;
            v += 4;
            w += 4;
        }

        if (w_count & 0x2)
        {
            w[0] = u[0] & v[0];
            w[1] = u[1] & v[1];
            u += 2;
            v += 2;
            w += 2;
        }

        if (w_count & 0x1)
        {
            w[0] = u[0] & v[0];
            u += 1;
            v += 1;
            w += 1;
        }
    }

    void BasicOperatorEngine::BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v, __UNIT_TYPE & w)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;BasicOperatorEngine::Compare;1");
#endif
        if (u_buf.BLOCK_COUNT == 0)
            w = 0;
        else
            w = u_buf.BLOCK[0] & v;
    }

    void BasicOperatorEngine::BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE & w_hi, __UNIT_TYPE & w_lo)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseand.cpp;BasicOperatorEngine::BitwiseAnd;1");
#endif
        if (u_buf.BLOCK_COUNT == 0)
        {
            w_lo = 0;
            w_hi = 0;
        }
        else if (u_buf.BLOCK_COUNT == 1)
        {
            w_lo = u_buf.BLOCK[0] & v_lo;
            w_hi = 0;
        }
        else
        {
            w_lo = u_buf.BLOCK[0] & v_lo;
            w_hi = u_buf.BLOCK[1] & v_hi;
        }
    }

    void BasicOperatorEngine::BitwiseAnd(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseand.cpp;BasicOperatorEngine::BitwiseAnd;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_bitwiseand.cpp;BasicOperatorEngine::BitwiseAnd;2");
#endif
        if (u_buf.BLOCK_COUNT < v_buf.BLOCK_COUNT)
            BitwiseAnd(v_buf, u_buf, w_buf);
        else
        {
            BitwiseAnd_UX_UX(u_buf.BLOCK, v_buf.BLOCK, w_buf.BLOCK, v_buf.BLOCK_COUNT);
            w_buf.Region(v_buf.BLOCK_COUNT).Clear();
        }
    }

}

/*
 * END OF FILE
 */