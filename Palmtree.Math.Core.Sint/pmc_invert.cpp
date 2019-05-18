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

#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_SINT PMC_Invert_I(ThreadContext& tc, _INT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (v_sign == 0)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        SIGN_T r_numerator_sign = v_sign;
        *r_denominator = ep_uint.From(tc, v_abs);
        root.HookNumber(*r_denominator);
        NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_L(ThreadContext& tc, _INT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (v_sign == 0)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        SIGN_T r_numerator_sign = v_sign;
        *r_denominator = ep_uint.From(tc, v_abs);
        root.HookNumber(*r_denominator);
        NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_X(ThreadContext& tc, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        if (nv->SIGN == 0)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        SIGN_T r_numerator_sign = nv->SIGN;
        *r_denominator = ep_uint.Clone(tc, nv->ABS);
        root.HookNumber(*r_denominator);
        NUMBER_OBJECT_SINT* nr_numerator = r_numerator_sign >= 0 ? &number_object_sint_one : &number_object_sint_minus_one;
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_UI(ThreadContext& tc, _UINT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        if (v == 0)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        *r_denominator = ep_uint.From(tc, v);
        root.HookNumber(*r_denominator);
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_UL(ThreadContext& tc, _UINT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        if (v == 0)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        *r_denominator = ep_uint.From(tc, v);
        root.HookNumber(*r_denominator);
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_UX(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        if (v->FLAGS.IS_ZERO)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        *r_denominator = ep_uint.Clone(tc, v);
        root.HookNumber(*r_denominator);
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(&number_object_sint_one);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

    PMC_HANDLE_SINT PMC_Invert_R(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* r_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->IS_ZERO)
            throw DivisionByZeroException(L"0 の逆数は未定義です。");
        ResourceHolderSINT root(tc);
        SIGN_T r_numerator_sign = nv_numerator->SIGN;
        PMC_HANDLE_UINT r_numerator_abs = ep_uint.Clone(tc, v_denominator);
        root.HookNumber(r_numerator_abs);
        *r_denominator = ep_uint.Clone(tc, nv_numerator->ABS);
        root.HookNumber(*r_denominator);
        NUMBER_OBJECT_SINT* nr_numerator = root.AllocateNumber(r_numerator_sign, r_numerator_abs);
        PMC_HANDLE_SINT r_numerator = GET_NUMBER_HANDLE(nr_numerator);
        root.UnlinkNumber(nr_numerator);
        root.UnlinkNumber(*r_denominator);
        return (r_numerator);
    }

}


/*
 * END OF FILE
 */