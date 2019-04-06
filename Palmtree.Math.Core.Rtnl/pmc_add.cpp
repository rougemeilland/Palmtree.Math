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

    static NUMBER_OBJECT_RTNL* PMC_Add_R_UI_Imp(NUMBER_OBJECT_RTNL* u, _UINT32_T v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_UL_Imp(NUMBER_OBJECT_RTNL* u, _UINT64_T v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_UX_Imp(NUMBER_OBJECT_RTNL* u, PMC_HANDLE_UINT v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT v_numerator = ep_uint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_I_Imp(NUMBER_OBJECT_RTNL* u, _INT32_T v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_L_Imp(NUMBER_OBJECT_RTNL* u, _INT64_T v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_X_Imp(NUMBER_OBJECT_RTNL* u, PMC_HANDLE_SINT v)
    {
        // 分子と分母が既約であればこの加算によって共通因数は発生しないため約分は省略する。
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(u->DENOMINATOR, v);
        root.HookNumber(v_numerator);
        PMC_HANDLE_SINT numerator = ep_sint.Add(u->NUMERATOR, v_numerator);
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = ep_uint.Clone(u->DENOMINATOR);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    static NUMBER_OBJECT_RTNL* PMC_Add_R_R_Imp(NUMBER_OBJECT_RTNL* u, NUMBER_OBJECT_RTNL* v)
    {
        // GCD の計算をできるだけ避けるため、明らかに約分が不要なパターンを調べる
        if (u->DENOMINATOR->FLAGS.IS_ONE)
            return (PMC_Add_R_X_Imp(v, u->NUMERATOR));
        else if (v->DENOMINATOR->FLAGS.IS_ONE)
            return (PMC_Add_R_X_Imp(u, v->NUMERATOR));
        else
        {
            // ここからが約分が必要になるルート

            ResourceHolderRTNL root;

            // 分子と分母を求める
            PMC_HANDLE_SINT u_numerator = ep_sint.Multiply(u->NUMERATOR, v->DENOMINATOR);
            root.HookNumber(u_numerator);
            PMC_HANDLE_SINT v_numerator = ep_sint.Multiply(v->NUMERATOR, u->DENOMINATOR);
            root.HookNumber(v_numerator);
            PMC_HANDLE_SINT numerator = ep_sint.Add(u_numerator, v_numerator);
            root.HookNumber(numerator);
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(u->DENOMINATOR, v->DENOMINATOR);
            root.HookNumber(denominator);

            // 分子と分母の共通因数を求める
            PMC_HANDLE_UINT gcd = ep_sint.GreatestCommonDivisor(numerator, denominator);
            if (!gcd->FLAGS.IS_ONE)
            {
                // 分子と分母の GCD が 1 ではない場合 (既約ではない場合)、分子と分母をそれぞれ GCD で割って新たな分子と分母を得る。
                numerator = DivideExactly(root, numerator, gcd);
                root.HookNumber(numerator);
                denominator = DivideExactly(root, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator);
            root.UnlinkNumber(nw);
            return (nw);
        }
    }

    __inline static PMC_HANDLE_RTNL EPILOGUE(ResourceHolderRTNL& root, NUMBER_OBJECT_RTNL* nr)
    {
        root.HookNumber(nr);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Add_I_R(_INT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_I_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_L_R(_INT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_L_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_X_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UI_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UL_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UX_Imp(nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_I(PMC_HANDLE_RTNL u, _INT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_I_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_L(PMC_HANDLE_RTNL u, _INT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_L_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_X_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UI_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UL_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_UX_Imp(nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Add_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Add_R_R_Imp(nu, nv)));
    }

}

/*
 * END OF FILE
 */