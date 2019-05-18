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

#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"

namespace Palmtree::Math::Core::Internal
{
    size_t PMC_ToString_X(ThreadContext& tc, PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        return (ep_uint.ToString(tc, nx->SIGN, nx->ABS, format, format_option, buffer, buffer_size));
    }

    size_t PMC_ToString_R(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_SINT* nx_numerator = GET_NUMBER_OBJECT(x_numerator, L"x_numerator");
        if (x_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x_denominator");
        return (ep_uint.ToString(tc, nx_numerator->SIGN, nx_numerator->ABS, x_denominator, format, format_option, buffer, buffer_size));
    }

    void  PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false)
    {
        return (ep_uint.InitializeNumberFormatInfo(info));
    }

}


/*
 * END OF FILE
 */