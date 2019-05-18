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
#include "pmc_resourceholder_rtnl.h"
#include "pmc_rtnl_internal.h"

namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_RTNL* PMC_Divide_UI_R_Imp(ThreadContext& tc, _UINT32_T u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_UL_R_Imp(ThreadContext& tc, _UINT64_T u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_UX_R_Imp(ThreadContext& tc, PMC_HANDLE_UINT u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_I_R_Imp(ThreadContext& tc, _INT32_T u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_L_R_Imp(ThreadContext& tc, _INT64_T u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_X_R_Imp(ThreadContext& tc, PMC_HANDLE_SINT u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, _UINT32_T v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, _UINT64_T v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, PMC_HANDLE_UINT v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_I_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, _INT32_T v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_L_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, _INT64_T v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_X_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, PMC_HANDLE_SINT v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_RTNL* PMC_Divide_R_R_Imp(ThreadContext& tc, NUMBER_OBJECT_RTNL* u, NUMBER_OBJECT_RTNL* v)
    {
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_UINT w_denominator;
        PMC_HANDLE_SINT w_numerator = ep_sint.DivideRational(tc, u->NUMERATOR, u->DENOMINATOR, v->NUMERATOR, v->DENOMINATOR, &w_denominator);
        root.HookNumber(w_numerator);
        root.HookNumber(w_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(w_numerator, w_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    __inline static PMC_HANDLE_RTNL EPILOGUE(ResourceHolderRTNL& root, NUMBER_OBJECT_RTNL* nr)
    {
        root.HookNumber(nr);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Divide_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_I_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_L_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_X_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_UI_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_UL_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_UX_R_Imp(tc, u, nv)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_I_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_L_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_X_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_UI_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_UL_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_UX_Imp(tc, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Divide_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, PMC_Divide_R_R_Imp(tc, nu, nv)));
    }

}

/*
 * END OF FILE
 */