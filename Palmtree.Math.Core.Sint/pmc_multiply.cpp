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


namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_SINT* MultiplyU_X_I_Imp(SIGN_T w_sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_I_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* MultiplyU_X_L_Imp(SIGN_T w_sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_L_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* MultiplyU_X_X_Imp(SIGN_T w_sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply.cpp;MultiplyU_X_X_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Multiply(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* Multiply_UX_I_Imp(PMC_HANDLE_UINT u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_I_Imp(v_sign, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_UX_L_Imp(PMC_HANDLE_UINT u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_L_Imp(v_sign, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_UI_Imp(NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_I_Imp(SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_I_Imp(SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_I_Imp(NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_I_Imp(v_sign, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_I_Imp(INVERT_SIGN(v_sign), u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_UL_Imp(NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_L_Imp(SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_L_Imp(SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_L_Imp(NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_L_Imp(v_sign, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_L_Imp(INVERT_SIGN(v_sign), u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_UX_Imp(NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_X_Imp(SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_X_Imp(SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Multiply_X_X_Imp(NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // abs(u) * v を返す
                return (MultiplyU_X_X_Imp(v->SIGN, u->ABS, v->ABS));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                // 0 を返す
                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                // -abs(u) * v を返す
                return (MultiplyU_X_X_Imp(INVERT_SIGN(v->SIGN), u->ABS, v->ABS));
            }
        }
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, NUMBER_OBJECT_SINT* nw)
    {
        root.HookNumber(nw);
        PMC_HANDLE_SINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_SINT PMC_Multiply_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UI_Imp(nv, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_I_Imp(nv, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_UX_I_Imp(v, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UL_Imp(nv, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_L_Imp(nv, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_UX_L_Imp(v, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UX_Imp(nv, u)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UI_Imp(nu, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_I_Imp(nu, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_UX_I_Imp(u, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UL_Imp(nu, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_L_Imp(nu, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_UX_L_Imp(u, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_UX_Imp(nu, v)));
    }

    PMC_HANDLE_SINT PMC_Multiply_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        return (EPILOGUE(root, Multiply_X_X_Imp(nu, nv)));
    }

}


/*
 * END OF FILE
 */