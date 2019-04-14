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

    PMC_HANDLE_SINT PMC_From_UI(ThreadContext& tc, _UINT32_T x)
    {
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, SIGN_POSITIVE, x);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_From_I(ThreadContext& tc, _INT32_T x)
    {
        ResourceHolderSINT root(tc);
        SIGN_T x_sign;
        _UINT32_T x_abs = GET_ABS_32(x, &x_sign);
        NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, x_sign, x_abs);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_From_UL(ThreadContext& tc, _UINT64_T x)
    {
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, SIGN_POSITIVE, x);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_From_L(ThreadContext& tc, _INT64_T x)
    {
        ResourceHolderSINT root(tc);
        SIGN_T x_sign;
        _UINT64_T x_abs = GET_ABS_64(x, &x_sign);
        NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, x_sign, x_abs);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_From_UX(ThreadContext& tc, PMC_HANDLE_UINT x)
    {
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nr = From_X_Imp(tc, SIGN_POSITIVE, x);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_From_DECIMAL(ThreadContext& tc, DECIMAL x, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        ResourceHolderSINT root(tc);
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_numerator_abs = ep_uint.From(tc, x, &o_sign, o_denominator);
        root.HookNumber(o_numerator_abs);
        root.HookNumber(*o_denominator);
        NUMBER_OBJECT_SINT* no_numerator = root.AllocateNumber(o_numerator_abs->FLAGS.IS_ZERO ? SIGN_ZERO : o_sign, o_numerator_abs);
        PMC_HANDLE_SINT o_numerator = GET_NUMBER_HANDLE(no_numerator);
        root.UnlinkNumber(no_numerator);
        root.UnlinkNumber(*o_denominator);
        return (o_numerator);
    }

    PMC_HANDLE_SINT PMC_From_DOUBLE(ThreadContext& tc, double x, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        ResourceHolderSINT root(tc);
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_numerator_abs = ep_uint.From(tc, x, &o_sign, o_denominator);
        root.HookNumber(o_numerator_abs);
        root.HookNumber(*o_denominator);
        NUMBER_OBJECT_SINT* no_numerator = root.AllocateNumber(o_numerator_abs->FLAGS.IS_ZERO ? SIGN_ZERO : o_sign, o_numerator_abs);
        PMC_HANDLE_SINT o_numerator = GET_NUMBER_HANDLE(no_numerator);
        root.UnlinkNumber(no_numerator);
        root.UnlinkNumber(*o_denominator);
        return (o_numerator);
    }

}


/*
 * END OF FILE
 */