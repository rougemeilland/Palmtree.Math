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

    bool BasicOperatorEngine::Equals(_UBASIC_T u_buf, __UNIT_TYPE v)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_equals.cpp;BasicOperatorEngine::Equals;1");
#endif
        if (v == 0)
            return (u_buf.BLOCK_COUNT == 0);
        else if (u_buf.BLOCK_COUNT != 1)
            return (false);
        else
            return (u_buf.BLOCK[0] == v);
    }

    bool BasicOperatorEngine::Equals(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_equals.cpp;BasicOperatorEngine::Equals;1");
#endif
        if (v_hi == 0)
            return (Equals(u_buf, v_lo));
        else if (u_buf.BLOCK_COUNT != 2)
            return (false);
        else
            return (u_buf.BLOCK[1] == v_hi && u_buf.BLOCK[0] == v_lo);
    }

    bool BasicOperatorEngine::Equals(_UBASIC_T u_buf, _UBASIC_T v_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_equals.cpp;BasicOperatorEngine::Equals;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_equals.cpp;BasicOperatorEngine::Equals;2");
#endif
        if (v_buf.BLOCK_COUNT == 0)
            return (u_buf.BLOCK_COUNT == 0);
        else if (u_buf.BLOCK_COUNT != v_buf.BLOCK_COUNT)
            return (false);
        else
        {
            __UNIT_TYPE* u_ptr = u_buf.BLOCK;
            __UNIT_TYPE* v_ptr = v_buf.BLOCK;
            __UNIT_TYPE count = u_buf.BLOCK_COUNT;
            while (count > 0)
            {
                if (*u_ptr != *v_ptr)
                    return (false);
                ++u_ptr;
                ++v_ptr;
                --count;
            }
            return (true);
        }
    }

}

/*
 * END OF FILE
 */