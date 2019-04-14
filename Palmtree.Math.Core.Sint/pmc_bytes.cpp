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

    PMC_HANDLE_UINT PMC_FromByteArray_RTNL(ThreadContext& tc, const unsigned char * buffer, size_t count, PMC_HANDLE_SINT * o_numerator) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        ResourceHolderSINT root(tc);
        SIGN_T o_numerator_sign;
        PMC_HANDLE_UINT no_numerator_abs;
        PMC_HANDLE_UINT o_denominator = ep_uint.FromByteArray_RTNL(tc, buffer, count, &o_numerator_sign, &no_numerator_abs);
        root.HookNumber(no_numerator_abs);
        root.HookNumber(o_denominator);
        NUMBER_OBJECT_SINT* no_numerator = root.AllocateNumber(o_numerator_sign, no_numerator_abs);
        *o_numerator = GET_NUMBER_HANDLE(no_numerator);
        root.UnlinkNumber(no_numerator);
        root.UnlinkNumber(o_denominator);
        return (o_denominator);
    }

    PMC_HANDLE_SINT PMC_FromByteArray_SINT(ThreadContext& tc, const unsigned char* buffer, size_t count)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        ResourceHolderSINT root(tc);
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_abs = ep_uint.FromByteArray_SINT(tc, buffer, count, &o_sign);
        root.HookNumber(o_abs);
        NUMBER_OBJECT_SINT* no = root.AllocateNumber(o_sign, o_abs);
        PMC_HANDLE_SINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    size_t PMC_ToByteArray_R(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_SINT* np_numerator = GET_NUMBER_OBJECT(p_numerator, L"p_numerator");
        if (p_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"p_denominator");
        size_t count = ep_uint.ToByteArray(np_numerator->SIGN, np_numerator->ABS, p_denominator, buffer, buffer_size);
        return (count);
    }

    size_t PMC_ToByteArray_X(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        size_t count = ep_uint.ToByteArray(np->SIGN, np->ABS, buffer, buffer_size);
        return (count);
    }

}


/*
 * END OF FILE
 */