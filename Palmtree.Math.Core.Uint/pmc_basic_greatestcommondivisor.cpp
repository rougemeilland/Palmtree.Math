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

    static void GreatestCommonDivisor_Imp(BasicOperatorEngine& ep, _UBASIC_T u_buf, _UBASIC_T v_buf, __UNIT_TYPE k, _UBASIC_T& w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT != v_buf.BLOCK_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_greatestcommondivisor.cpp;GreatestCommonDivisor_Imp;1");
        if (u_buf.BLOCK_COUNT == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_greatestcommondivisor.cpp;GreatestCommonDivisor_Imp;2");
#endif
        __UNIT_TYPE* u = u_buf.BLOCK;
        __UNIT_TYPE* v = v_buf.BLOCK;
        __UNIT_TYPE word_count = u_buf.BLOCK_COUNT;
        for (;;)
        {
            while (word_count > 0 && u[word_count - 1] == 0 && v[word_count - 1] == 0)
                --word_count;
            if (word_count <= 0)
            {
                // このルートへの到達はあり得ないはず。
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_basic_greatestcommondivisor.cpp;GreatestCommonDivisor_Imp;3");
            }
            int c = ep.Compare(_UBASIC_T(u, word_count).Shrink(), _UBASIC_T(v, word_count).Shrink());
            if (c == 0)
            {
                // u == v の場合

                // u を GCD として復帰
                ep.LeftShift(_UBASIC_T(u, word_count).Shrink(), k, w_buf);
                return;
            }
            if (c < 0)
            {
                __UNIT_TYPE* tt = u;
                u = v;
                v = tt;
            }
            // この時点で u > v かつ u と v はともに奇数である

            ep.USubtruct(_UBASIC_T(u, word_count), _UBASIC_T(v, word_count).Shrink());

            // この時点で u は偶数

            // u が奇数になるまで u を右シフトする
            _UBASIC_T temp_u = _UBASIC_T(u, word_count);
            ep.RightShift(temp_u, temp_u.TZCount());
        }
    }

    void BasicOperatorEngine::GreatestCommonDivisor(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T work_u_buf, _UBASIC_T work_v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;2");
        if (work_u_buf.BLOCK_COUNT < _MAXIMUM_UNIT( u_buf.BLOCK_COUNT, v_buf.BLOCK_COUNT))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
        if (work_v_buf.BLOCK_COUNT < _MAXIMUM_UNIT(u_buf.BLOCK_COUNT, v_buf.BLOCK_COUNT))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
#endif
        if (u_buf.BLOCK_COUNT == 0)
        {
            if (v_buf.BLOCK_COUNT == 0)
                throw ArithmeticException(L"0 と 0 の GCD は未定義です。");
            else
                w_buf.CopyFrom(v_buf);
        }
        else
        {
            if (v_buf.BLOCK_COUNT == 0)
                w_buf.CopyFrom(u_buf);
            else
            {
                __UNIT_TYPE u_buf_tzcnt = u_buf.TZCount();
                __UNIT_TYPE v_buf_tzcnt = v_buf.TZCount();
                __UNIT_TYPE k = _MINIMUM_UNIT(u_buf_tzcnt, v_buf_tzcnt);
                RightShift(u_buf, u_buf_tzcnt, work_u_buf);
                RightShift(v_buf, v_buf_tzcnt, work_v_buf);
                GreatestCommonDivisor_Imp(*this, work_u_buf, work_v_buf, k, w_buf);
            }
        }
    }

}

/*
 * END OF FILE
 */