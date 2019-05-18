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

    __inline static SIGN_T CompareWord(__UNIT_TYPE u, __UNIT_TYPE v)
    {
        if (u == v)
            return (SIGN_ZERO);
        else if (u > v)
            return (SIGN_POSITIVE);
        else
            return (SIGN_NEGATIVE);
    }

    SIGN_T BasicOperatorEngine::Compare(_UBASIC_T u_buf, __UNIT_TYPE v)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
#endif
        if (u_buf.BLOCK_COUNT == 0)
            return (v == 0 ? SIGN_ZERO : SIGN_NEGATIVE);
        else if (v == 0)
            return (SIGN_POSITIVE);
        else if (u_buf.BLOCK_COUNT == 1)
            return (CompareWord(u_buf.BLOCK[0], v));
        else
            return (SIGN_POSITIVE);
    }

    SIGN_T BasicOperatorEngine::Compare(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
#endif
        if (v_hi == 0)
            return (Compare(u_buf, v_lo));
        else if (u_buf.BLOCK_COUNT < 2)
            return (SIGN_NEGATIVE);
        else if (u_buf.BLOCK_COUNT == 2)
        {
            SIGN_T c = CompareWord(u_buf.BLOCK[1], v_hi);
            if (c == 0)
                return (CompareWord(u_buf.BLOCK[0], v_lo));
            else
                return (c);
        }
        else
            return (SIGN_POSITIVE);
    }

    SIGN_T BasicOperatorEngine::Compare(_UBASIC_T u_buf, _UBASIC_T v_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_compare.cpp;BasicOperatorEngine::Compare;2");
#endif
        if (u_buf.BLOCK_COUNT == v_buf.BLOCK_COUNT)
        {
            __UNIT_TYPE* u_ptr = &u_buf.BLOCK[u_buf.BLOCK_COUNT];
            __UNIT_TYPE* v_ptr = &v_buf.BLOCK[v_buf.BLOCK_COUNT];
            __UNIT_TYPE count = u_buf.BLOCK_COUNT;
            while (count > 0)
            {
                --u_ptr;
                --v_ptr;
                --count;
                SIGN_T c = CompareWord(*u_ptr, *v_ptr);
                if (c != 0)
                    return (c);
            }
            return (SIGN_ZERO);
        }
        else if (u_buf.BLOCK_COUNT > v_buf.BLOCK_COUNT)
            return (SIGN_POSITIVE);
        else
            return (SIGN_NEGATIVE);
    }

}

/*
 * END OF FILE
 */