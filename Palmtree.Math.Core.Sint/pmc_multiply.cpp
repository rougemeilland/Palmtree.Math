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

    static NUMBER_OBJECT_SINT* MultiplyU_X_I_Imp(char w_sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_I_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply_X_I(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* MultiplyU_X_L_Imp(char w_sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_L_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply_X_L(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* MultiplyU_X_X_Imp(char w_sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_X_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply_X_X(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(nv->SIGN, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(nv->SIGN, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(-nv->SIGN, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(nv->SIGN, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(nv->SIGN, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(-nv->SIGN, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // u != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_X_Imp(nv->SIGN, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                // abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(1, nu->ABS, v));
                    
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                // -abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(v_sign, nu->ABS, v_abs));

            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_I_Imp(-v_sign, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                // -abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(v_sign, nu->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * abs(v) を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_L_Imp(-v_sign, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
            
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u != 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                // u * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_X_Imp(nu->SIGN, nu->ABS, v));
            }

        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Multiply_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_X_Imp(nv->SIGN, nu->ABS, nv->ABS));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return ((PMC_HANDLE_SINT)MultiplyU_X_X_Imp(-nv->SIGN, nu->ABS, nv->ABS));
            }
        }
    }

}


/*
 * END OF FILE
 */