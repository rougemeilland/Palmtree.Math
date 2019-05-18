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

#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_RTNL PMC_Pow_I_I(ThreadContext& tc, _INT32_T v, _INT32_T e) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Pow_L_I(ThreadContext& tc, _INT64_T v, _INT32_T e) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }


    PMC_HANDLE_RTNL PMC_Pow_X_I(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Pow_UI_I(ThreadContext& tc, _UINT32_T v, _INT32_T e) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Pow_UL_I(ThreadContext& tc, _UINT64_T v, _INT32_T e) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Pow_UX_I(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, v, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Pow_R_I(ThreadContext& tc, PMC_HANDLE_RTNL v, _INT32_T e) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.Pow(tc, nv->NUMERATOR, nv->DENOMINATOR, e, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

}


/*
 * END OF FILE
 */