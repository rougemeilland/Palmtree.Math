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
#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"


namespace Palmtree::Math::Core::Internal
{
    PMC_HANDLE_RTNL PMC_FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        ResourceHolderRTNL root(tc);
        PMC_HANDLE_SINT o_numerator;
        PMC_HANDLE_UINT o_denominator = ep_sint.FromByteArray_RTNL(tc, buffer, count, &o_numerator);
        root.HookNumber(o_numerator);
        root.HookNumber(o_denominator);
        NUMBER_OBJECT_RTNL* no = root.AllocateNumber(o_numerator, o_denominator);
        PMC_HANDLE_RTNL o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    size_t PMC_ToByteArray_R(PMC_HANDLE_RTNL p, unsigned char* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        size_t count = ep_sint.ToByteArray(np->NUMERATOR, np->DENOMINATOR, buffer, buffer_size);
        return (count);
    }
}


/*
 * END OF FILE
 */