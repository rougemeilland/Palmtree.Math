


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

    PMC_HANDLE_SINT PMC_Round_R(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        NUMBER_OBJECT_SINT* nx_numerator = GET_NUMBER_OBJECT(x_numerator, L"x_numerator");
        if (x_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x_denominator");
        ResourceHolderSINT root;
        PMC_HANDLE_UINT r_abs = ep_uint.RoundZero(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, mode);
        root.HookNumber(r_abs);
        NUMBER_OBJECT_SINT* nr = root.AllocateNumber(nx_numerator->SIGN, r_abs);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_Round_R_I(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator)
    {
        NUMBER_OBJECT_SINT* nx_numerator = GET_NUMBER_OBJECT(x_numerator, L"x_numerator");
        if (x_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x_denominator");
        ResourceHolderSINT root;
        PMC_HANDLE_UINT r_numerator_abs = ep_uint.Round(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, decimals, mode, r_denominator);
        root.HookNumber(r_numerator_abs);
        root.HookNumber(*r_denominator);
        NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(nx_numerator->SIGN, r_numerator_abs);
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
        root.UnlinkNumber(*r_denominator);
        root.UnlinkNumber(nr_numerator);
        return (r_numerator);
    }

}


/*
 * END OF FILE
 */