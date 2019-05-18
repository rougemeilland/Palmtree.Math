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

    PMC_HANDLE_SINT PMC_GenerateBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderSINT root(tc);

        PMC_HANDLE_UINT r_abs = ep_uint.GenerateUBigIntRandomValue(tc, handle, bit_count);
        root.HookNumber(r_abs);
        NUMBER_OBJECT_SINT* nr = root.AllocateNumber(SIGN_POSITIVE, r_abs);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_GenerateBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderSINT root(tc);

        PMC_HANDLE_UINT r_abs = ep_uint.GenerateUBigIntCryptoRandomValue(tc, data, bit_count);
        root.HookNumber(r_abs);
        NUMBER_OBJECT_SINT* nr = root.AllocateNumber(SIGN_POSITIVE, r_abs);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

}


/*
 * END OF FILE
 */