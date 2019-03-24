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

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT t = ep_uint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT64_T v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT t = ep_uint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_UINT v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT t = ep_uint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT32_T v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT t = ep_sint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT64_T v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT t = ep_sint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT t = ep_sint.Multiply(u_denominator, v);
        root.UnlinkNumber(t);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(u_numerator, t) : ep_sint.Subtruct(t, u_numerator);
        return (numerator);
    }

    __inline static PMC_HANDLE_SINT SubtructNumerator(SIGN_T sign, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT t1 = ep_sint.Multiply(v_denominator, u_numerator);
        root.UnlinkNumber(t1);
        PMC_HANDLE_SINT t2 = ep_sint.Multiply(u_denominator, v_numerator);
        root.UnlinkNumber(t2);
        PMC_HANDLE_SINT numerator = sign >= 0 ? ep_sint.Subtruct(t1, t2) : ep_sint.Subtruct(t2, t1);
        return (numerator);
    }

    __inline static NUMBER_OBJECT_RTNL* ALLOCATE_NUMBER(ResourceHolderRTNL& root, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator, bool f_reduce)
    {
        root.HookNumber(numerator);
        root.HookNumber(denominator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, denominator, f_reduce);
        root.UnlinkNumber(numerator);
        root.UnlinkNumber(denominator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    __inline static NUMBER_OBJECT_RTNL* ALLOCATE_NUMBER(ResourceHolderRTNL& root, PMC_HANDLE_SINT numerator)
    {
        root.HookNumber(numerator);
        NUMBER_OBJECT_RTNL* nw = root.AllocateNumber(numerator, number_handle_uint_one);
        root.UnlinkNumber(numerator);
        root.UnlinkNumber(nw);
        return (nw);
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_UI_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, _UINT32_T v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_UL_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, _UINT64_T v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_UX_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, PMC_HANDLE_UINT v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_I_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, _INT32_T v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_L_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, _INT64_T v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_X_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, PMC_HANDLE_SINT v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, ep_sint.Subtruct(u->NUMERATOR, v)));
        }
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v), u->DENOMINATOR, false));
        }
    }

    __inline static NUMBER_OBJECT_RTNL* PMC_Subtruct_R_R_Imp(SIGN_T sign, NUMBER_OBJECT_RTNL* u, NUMBER_OBJECT_RTNL* v)
    {
        if (u->DENOMINATOR->FLAGS.IS_ONE)
            return (PMC_Subtruct_R_X_Imp(INVERT_SIGN(sign), v, u->NUMERATOR));
        else if (v->DENOMINATOR->FLAGS.IS_ONE)
            return (PMC_Subtruct_R_X_Imp(sign, u, v->NUMERATOR));
        else
        {
            ResourceHolderRTNL root;
            return (ALLOCATE_NUMBER(root, SubtructNumerator(sign, u->NUMERATOR, u->DENOMINATOR, v->NUMERATOR, v->DENOMINATOR), ep_uint.Multiply(u->DENOMINATOR, v->DENOMINATOR), true));
        }
    }

    __inline static PMC_HANDLE_RTNL EPILOGUE(ResourceHolderRTNL& root, NUMBER_OBJECT_RTNL* nr)
    {
        root.HookNumber(nr);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Subtruct_I_R(_INT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_I_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_L_R(_INT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_L_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_X_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UI_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UL_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UX_Imp(SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_I(PMC_HANDLE_RTNL u, _INT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_I_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_L(PMC_HANDLE_RTNL u, _INT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_L_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_X_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UI_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UL_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_UX_Imp(SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_RTNL PMC_Subtruct_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v)
    {
        NUMBER_OBJECT_RTNL* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_RTNL* nv = GET_NUMBER_OBJECT(u, L"v");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, PMC_Subtruct_R_R_Imp(SIGN_POSITIVE, nu, nv)));
    }

}

/*
 * END OF FILE
 */