


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


#include "pmc_resourceholder_rtnl.h"
#include "pmc_rtnl_internal.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_SINT PMC_Round_R(PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        return (ep_sint.Round(nx->NUMERATOR, nx->DENOMINATOR, mode));
    }

    PMC_HANDLE_RTNL PMC_Round_R_I(PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Round(nx->NUMERATOR, nx->DENOMINATOR, decimals, mode, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_Floor_R(PMC_HANDLE_RTNL x)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        return (ep_sint.Round(nx->NUMERATOR, nx->DENOMINATOR, PMC_MIDPOINT_ROUNDING_FLOOR));
    }

    PMC_HANDLE_SINT PMC_Ceiling_R(PMC_HANDLE_RTNL x)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        return (ep_sint.Round(nx->NUMERATOR, nx->DENOMINATOR, PMC_MIDPOINT_ROUNDING_CEILING));
    }
}


/*
 * END OF FILE
 */