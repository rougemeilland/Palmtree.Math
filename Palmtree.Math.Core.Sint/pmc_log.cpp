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

#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"

namespace Palmtree::Math::Core::Internal
{

    _INT32_T PMC_FloorLog10_R(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN <= 0)
            throw ArithmeticException(L"負または 0 の数値に対する対数は未定義です。");
        return (ep_uint.FloorLog10(tc, nv_numerator->ABS, v_denominator));
    }

}


/*
 * END OF FILE
 */