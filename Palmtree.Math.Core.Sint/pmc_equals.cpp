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
#include "pmc_sint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    __inline static bool CHECK_RETURN_VALUE(bool value)
    {
        return (value);
    }

    bool PMC_Equals_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
            return (CHECK_RETURN_VALUE(nv->SIGN == 0));
        else if (nv->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(u, nv->ABS)));
    }

    bool PMC_Equals_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign != nv->SIGN)
            return (CHECK_RETURN_VALUE(0));
        return (CHECK_RETURN_VALUE(ep_uint.Equals(u_abs, nv->ABS)));
    }

    bool PMC_Equals_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
            return (CHECK_RETURN_VALUE(nv->SIGN == 0));
        else if (nv->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(u, nv->ABS)));
    }

    bool PMC_Equals_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign != nv->SIGN)
            return (CHECK_RETURN_VALUE(0));
        return (CHECK_RETURN_VALUE(ep_uint.Equals(u_abs, nv->ABS)));
    }

    bool PMC_Equals_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u->FLAGS.IS_ZERO)
            return (CHECK_RETURN_VALUE(nv->SIGN == 0));
        else if (nv->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(u, nv->ABS)));
    }

    bool PMC_Equals_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
            return (CHECK_RETURN_VALUE(nu->SIGN == 0));
        else if (nu->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, v)));
    }

    bool PMC_Equals_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN != v_sign)
            return (CHECK_RETURN_VALUE(0));
        return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, v_abs)));
    }

    bool PMC_Equals_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
            return (CHECK_RETURN_VALUE(nu->SIGN == 0));
        else if (nu->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, v)));
    }

    bool PMC_Equals_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN != v_sign)
            return (CHECK_RETURN_VALUE(0));
        return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, v_abs)));
    }

    bool PMC_Equals_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        if (v->FLAGS.IS_ZERO)
            return (CHECK_RETURN_VALUE(nu->SIGN == 0));
        else if (nu->SIGN <= 0)
            return (CHECK_RETURN_VALUE(0));
        else
            return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, v)));
    }

    bool PMC_Equals_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nu->SIGN != nv->SIGN)
            return (CHECK_RETURN_VALUE(0));
        return (CHECK_RETURN_VALUE(ep_uint.Equals(nu->ABS, nv->ABS)));
    }

}


/*
 * END OF FILE
 */