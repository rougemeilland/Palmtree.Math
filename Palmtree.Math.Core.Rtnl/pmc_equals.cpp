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


namespace Palmtree::Math::Core::Internal
{

    bool PMC_Equals_I_R(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_L_R(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (nv->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(u, nv->NUMERATOR));
    }

    bool PMC_Equals_R_I(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_L(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        return (nu->DENOMINATOR->FLAGS.IS_ONE && ep_sint.Equals(nu->NUMERATOR, v));
    }

    bool PMC_Equals_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        return (ep_sint.Equals(nu->NUMERATOR, nv->NUMERATOR) && ep_uint.Equals(nu->DENOMINATOR, nv->DENOMINATOR));
    }


}


/*
 * END OF FILE
 */