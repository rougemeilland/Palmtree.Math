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

    PMC_HANDLE_SINT PMC_Pow_I_UI(ThreadContext& tc, _INT32_T v, _UINT32_T e) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                throw ArithmeticException(L"0 の 0 乗の値は未定義です。");
            }
            else
            {
                // e > 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_zero));
            }
        }
        else
        {
            // v != 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_one));
            }
            else
            {
                // e > 0 の場合

                ResourceHolderSINT root(tc);
                SIGN_T r_sign = v_sign < 0 && (e & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
                PMC_HANDLE_UINT r_abs = ep_uint.Pow(tc, v_abs, e);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_Pow_L_UI(ThreadContext& tc, _INT64_T v, _UINT32_T e) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                throw ArithmeticException(L"0 の 0 乗の値は未定義です。");
            }
            else
            {
                // e > 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_zero));
            }
        }
        else
        {
            // v != 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_one));
            }
            else
            {
                // e > 0 の場合

                ResourceHolderSINT root(tc);
                SIGN_T r_sign = v_sign < 0 && (e & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
                PMC_HANDLE_UINT r_abs = ep_uint.Pow(tc, v_abs, e);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_Pow_X_UI(ThreadContext& tc, PMC_HANDLE_SINT v, _UINT32_T e) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                throw ArithmeticException(L"0 の 0 乗の値は未定義です。");
            }
            else
            {
                // e > 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_zero));
            }
        }
        else
        {
            // v != 0 の場合

            if (e == 0)
            {
                // e == 0 の場合

                return (GET_NUMBER_HANDLE(&number_object_sint_one));
            }
            else
            {
                // e > 0 の場合

                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nv->SIGN < 0 && (e & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
                PMC_HANDLE_UINT r_abs = ep_uint.Pow(tc, nv->ABS, e);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_Pow_I_I(ThreadContext& tc, _INT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = v_sign < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v_abs, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (v_sign == 0)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = v_sign < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            *r_denominator = ep_uint.Pow(tc, v_abs, e_abs);
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_L_I(ThreadContext& tc, _INT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = v_sign < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v_abs, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (v_sign == 0)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = v_sign < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            *r_denominator = ep_uint.Pow(tc, v_abs, e_abs);
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_X_I(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = nv->SIGN < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, nv->ABS, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (nv->IS_ZERO)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = nv->SIGN < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            *r_denominator = ep_uint.Pow(tc, nv->ABS, e_abs);
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_UI_I(ThreadContext& tc, _UINT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (v == 0)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            *r_denominator = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(*r_denominator);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_UL_I(ThreadContext& tc, _UINT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (v == 0)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            *r_denominator = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(*r_denominator);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_UX_I(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = number_handle_uint_one;
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (v->FLAGS.IS_ZERO)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            *r_denominator = ep_uint.Pow(tc, v, e_abs);
            root.HookNumber(*r_denominator);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Pow_R_I(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        SIGN_T e_sign;
        _UINT32_T e_abs = GET_ABS_32(e, &e_sign);
        if (e_sign >= 0)
        {
            // e >= 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = nv_numerator->SIGN < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, nv_numerator->ABS, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = ep_uint.Pow(tc, v_denominator, e_abs);
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
        else
        {
            // e < 0 の場合

            if (nv_numerator->IS_ZERO)
                throw DivisionByZeroException(L"0 の逆数は未定義です。");
            ResourceHolderSINT root(tc);
            SIGN_T r_numerator_sign = nv_numerator->SIGN < 0 && (e_abs & 1) ? SIGN_NEGATIVE : SIGN_POSITIVE;
            PMC_HANDLE_UINT r_numerator_abs = ep_uint.Pow(tc, v_denominator, e_abs);
            root.HookNumber(r_numerator_abs);
            *r_denominator = ep_uint.Pow(tc, nv_numerator->ABS, e_abs);
            root.HookNumber(*r_denominator);
            NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
            PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
            root.UnlinkNumber(nr_numerator);
            root.UnlinkNumber(*r_denominator);
            return (r_numerator);
        }
    }

}


/*
 * END OF FILE
 */