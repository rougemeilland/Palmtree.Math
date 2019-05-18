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

    SIGN_T PMC_Compare_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = ep_sint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = ep_sint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = ep_sint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT u_numerator = ep_uint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT u_numerator = ep_uint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT u_numerator = ep_uint.Multiply(tc, u, nv->DENOMINATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = nv->NUMERATOR;
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = nu->NUMERATOR;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(tc, nu->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

    SIGN_T PMC_Compare_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT u_numerator = ep_sint.Multiply(tc, nv->DENOMINATOR, nu->NUMERATOR);
        root.HookNumber(u_numerator);
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(tc, nu->DENOMINATOR, nv->NUMERATOR);
        root.HookNumber(v_numerator);
        return (ep_sint.Compare(u_numerator, v_numerator));
    }

}


/*
 * END OF FILE
 */