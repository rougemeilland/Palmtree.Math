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
#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T r_sign, PMC_HANDLE_UINT r_abs)
    {
        root.HookNumber(r_abs);
        NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
        root.UnlinkNumber(nr);
        return (nr);
    }

    static NUMBER_OBJECT_SINT* RightSift_Imp(NUMBER_OBJECT_SINT* p, _INT32_T n)
    {
        SIGN_T n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        if (n_sign == 0)
            return (DuplicateNumber_X(p));
        else if (n_sign > 0)
        {
            if (p->SIGN == 0)
                return (&number_object_sint_zero);
            else if (p->SIGN > 0)
            {
                // 正の数を右シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.RightShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
            else
            {
                // 負の数を右シフト
                ResourceHolderSINT root;
                PMC_HANDLE_UINT p2 = ep_uint.Decrement(p->ABS);
                root.HookNumber(p2);
                PMC_HANDLE_UINT p3 = ep_uint.RightShift(p2, GET_INT_32(SIGN_POSITIVE, n_abs));
                root.HookNumber(p3);
                PMC_HANDLE_UINT r_abs = ep_uint.Increment(p3);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, r_abs));
            }
        }
        else
        {
            if (p->SIGN == 0)
                return (&number_object_sint_zero);
            else if (p->SIGN > 0)
            {
                // 正の数を左シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.LeftShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
            else
            {
                // 負の数を左シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.LeftShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
        }
    }
    
    static NUMBER_OBJECT_SINT* LeftSift_Imp(NUMBER_OBJECT_SINT* p, _INT32_T n)
    {
        SIGN_T n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        if (n_sign == 0)
            return (DuplicateNumber_X(p));
        else if (n_sign < 0)
        {
            if (p->SIGN == 0)
                return (&number_object_sint_zero);
            else if (p->SIGN > 0)
            {
                // 正の数を右シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.RightShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
            else
            {
                // 負の数を右シフト
                ResourceHolderSINT root;
                PMC_HANDLE_UINT p2 = ep_uint.Decrement(p->ABS);
                root.HookNumber(p2);
                PMC_HANDLE_UINT p3 = ep_uint.RightShift(p2, GET_INT_32(SIGN_POSITIVE, n_abs));
                root.HookNumber(p3);
                PMC_HANDLE_UINT r_abs = ep_uint.Increment(p3);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, r_abs));
            }
        }
        else
        {
            if (p->SIGN == 0)
                return (&number_object_sint_zero);
            else if (p->SIGN > 0)
            {
                // 正の数を右シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.LeftShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
            else
            {
                // 負の数を左シフト

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.LeftShift(p->ABS, GET_INT_32(SIGN_POSITIVE, n_abs))));
            }
        }
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, NUMBER_OBJECT_SINT* nr)
    {
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_LeftShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderSINT root;
        return (EPILOGUE(root, LeftSift_Imp(np, n)));
    }

    PMC_HANDLE_SINT PMC_RightShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        ResourceHolderSINT root;
        return (EPILOGUE(root, RightSift_Imp(np, n)));
    }

}

/*
 * END OF FILE
 */