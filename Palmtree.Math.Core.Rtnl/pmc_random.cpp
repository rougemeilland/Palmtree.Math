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


#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_RTNL PMC_GenerateRationalRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderRTNL root(tc);

        PMC_HANDLE_SINT r_numerator = ep_sint.GenerateBigIntRandomValue(tc, handle, bit_count);
        root.HookNumber(r_numerator);
        PMC_HANDLE_UINT r_denominator = ep_uint.LeftShift(tc, number_handle_uint_one, bit_count);
        root.HookNumber(r_denominator);
        PMC_HANDLE_UINT gcd = ep_sint.GreatestCommonDivisor(tc, r_numerator, r_denominator);
        root.HookNumber(gcd);
        if (!gcd->FLAGS.IS_ONE)
        {
            r_numerator = ep_sint.DivideExactly(tc, r_numerator, gcd);
            root.HookNumber(r_numerator);
            r_denominator = ep_uint.DivideExactly(tc, r_denominator, gcd);
            root.HookNumber(r_denominator);
        }
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_GenerateRationalCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderRTNL root(tc);

        PMC_HANDLE_SINT r_numerator = ep_sint.GenerateBigIntCryptoRandomValue(tc, data, bit_count);
        root.HookNumber(r_numerator);
        PMC_HANDLE_UINT r_denominator = ep_uint.LeftShift(tc, number_handle_uint_one, bit_count);
        root.HookNumber(r_denominator);
        PMC_HANDLE_UINT gcd = ep_sint.GreatestCommonDivisor(tc, r_numerator, r_denominator);
        root.HookNumber(gcd);
        if (!gcd->FLAGS.IS_ONE)
        {
            r_numerator = ep_sint.DivideExactly(tc, r_numerator, gcd);
            root.HookNumber(r_numerator);
            r_denominator = ep_uint.DivideExactly(tc, r_denominator, gcd);
            root.HookNumber(r_denominator);
        }
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

}


/*
 * END OF FILE
 */