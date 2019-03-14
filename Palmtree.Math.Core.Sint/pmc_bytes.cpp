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

    PMC_HANDLE_SINT __PMC_CALL PMC_FromByteArray(const unsigned char* buffer, size_t count)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        if (count < 1)
            throw ArgumentException(L"空の配列が与えられています。");
        ResourceHolderSINT root;
        char o_sign;
        PMC_HANDLE_UINT o_abs = ep_uint.FromByteArrayForSINT(buffer, count, &o_sign);
        root.HookNumber(o_abs);
        NUMBER_OBJECT_SINT* o = root.AllocateNumber(o_sign, o_abs);
        root.UnlinkNumber(o_abs);
        root.UnlinkNumber(o);
        return ((PMC_HANDLE_SINT)o);
    }

    size_t __PMC_CALL PMC_ToByteArray(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size)
    {
        if (p == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        NUMBER_OBJECT_SINT* np = (NUMBER_OBJECT_SINT*)p;
        CheckNumber(np);
        size_t count = ep_uint.ToByteArrayForSINT(np->SIGN, np->ABS, buffer, buffer_size);
        return (count);
    }

}


/*
 * END OF FILE
 */