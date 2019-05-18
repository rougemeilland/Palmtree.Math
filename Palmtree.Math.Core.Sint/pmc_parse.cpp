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

    PMC_STATUS_CODE PMC_TryParse_SINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false)
    {
        ResourceHolderSINT root(tc);
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_abs;
        PMC_STATUS_CODE result = ep_uint.TryParse_SINT(tc, source, number_styles, format_option, &o_sign, &o_abs);
        if (result == PMC_STATUS_OK)
        {
            root.HookNumber(o_abs);
            NUMBER_OBJECT_SINT* no = root.AllocateNumber(o_sign, o_abs);
            *o = GET_NUMBER_HANDLE(no);
            root.UnlinkNumber(no);
        }
        return (result);
    }

    PMC_STATUS_CODE PMC_TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o_numerator, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        ResourceHolderSINT root(tc);
        SIGN_T o_numerator_sign;
        PMC_HANDLE_UINT o_numerator_abs;
        PMC_STATUS_CODE result = ep_uint.TryParse_RTNL(tc, source, number_styles, format_option, &o_numerator_sign, &o_numerator_abs, o_denominator);
        if (result == PMC_STATUS_OK)
        {
            root.HookNumber(o_numerator_abs);
            root.HookNumber(*o_denominator);
            NUMBER_OBJECT_SINT* no_numerator = root.AllocateNumber(o_numerator_sign, o_numerator_abs);
            *o_numerator = GET_NUMBER_HANDLE(no_numerator);
            root.UnlinkNumber(no_numerator);
            root.UnlinkNumber(*o_denominator);
        }
        return (result);
    }

}


/*
 * END OF FILE
 */