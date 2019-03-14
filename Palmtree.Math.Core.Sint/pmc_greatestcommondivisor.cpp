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
#include "pmc_resourceholder_sint.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_I_X(u, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        ResourceHolderSINT root;
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_I_X(u_abs, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_L_X(u, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        ResourceHolderSINT root;
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_L_X(u_abs, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_X(u, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_I(nu->ABS, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        ResourceHolderSINT root;
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_I(nu->ABS, v_abs);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_L(nu->ABS, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        ResourceHolderSINT root;
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_L(nu->ABS, v_abs);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_X(nu->ABS, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_GreatestCommonDivisor_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.GreatestCommonDivisor_X_X(nu->ABS, nv->ABS);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_abs->FLAGS.IS_ZERO ? 0 : 1, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_SINT)w);
    }

}


/*
 * END OF FILE
 */