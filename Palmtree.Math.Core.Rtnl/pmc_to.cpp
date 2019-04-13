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


#include <windows.h>
#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"


namespace Palmtree::Math::Core::Internal
{
    PMC_HANDLE_SINT PMC_SplitIntoIntAndFraction(NUMBER_OBJECT_RTNL* x, NUMBER_OBJECT_RTNL** frac_part)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT int_part;
        PMC_HANDLE_SINT frac_part_numerator = ep_sint.DivRem(x->NUMERATOR, x->DENOMINATOR, &int_part);
        root.HookNumber(int_part);
        root.HookNumber(frac_part_numerator);
        PMC_HANDLE_UINT frac_part_denominator = ep_uint.Clone(x->DENOMINATOR);
        root.HookNumber(frac_part_denominator);
        *frac_part = root.AllocateNumber(frac_part_numerator, frac_part_denominator);
        root.HookNumber(*frac_part);
        root.UnlinkNumber(int_part);
        root.UnlinkNumber(*frac_part);
        return (int_part);
    }

    _UINT32_T PMC_ToUInt32_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        root.HookNumber(nr);
        _UINT32_T r = ep_sint.ToUInt32(nr);
        return (r);
    }

    _INT32_T PMC_ToInt32_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        root.HookNumber(nr);
        _INT32_T r = ep_sint.ToInt32(nr);
        return (r);
    }

    _UINT64_T PMC_ToUInt64_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        root.HookNumber(nr);
        _UINT64_T r = ep_sint.ToUInt64(nr);
        return (r);
    }

    _INT64_T PMC_ToInt64_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        root.HookNumber(nr);
        _INT64_T r = ep_sint.ToInt64(nr);
        return (r);
    }

    PMC_HANDLE_UINT PMC_ToUBigInt_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        root.HookNumber(nr);
        PMC_HANDLE_UINT r = ep_sint.ToUBigInt(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_ToBigInt_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        PMC_HANDLE_SINT r = ep_sint.Round(np->NUMERATOR, np->DENOMINATOR, PMC_MIDPOINT_ROUNDING_TRUNCATE);
        return (r);
    }

    DECIMAL PMC_ToDecimal_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        return (ep_sint.ToDecimal(np->NUMERATOR, np->DENOMINATOR));
    }

    double PMC_ToDouble_R(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        return (ep_sint.ToDouble(np->NUMERATOR, np->DENOMINATOR));
    }


}


/*
 * END OF FILE
 */