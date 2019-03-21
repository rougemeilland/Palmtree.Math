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
    PMC_HANDLE_SINT PMC_OneComplement_UX(PMC_HANDLE_UINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");

        // 恒等式 -x == ~x + 1 より x~ == -(x + 1) となるので、これを利用する

        if (x->FLAGS.IS_ZERO)
        {
            // x == 0 の場合
            return (GET_NUMBER_HANDLE(&number_object_sint_minus_one));
        }
        else
        {
            // x > 0 の場合
            ResourceHolderSINT root;
            PMC_HANDLE_UINT r_abs = ep_uint.Increment(x);
            root.HookNumber(r_abs);
            NUMBER_OBJECT_SINT* nr = root.AllocateNumber(SIGN_NEGATIVE, r_abs);
            PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(r_abs);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

    PMC_HANDLE_SINT PMC_OneComplement_X(PMC_HANDLE_SINT x) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");

        // 恒等式 -x == ~x + 1 より x~ == -(x + 1) となるので、これを利用する

        if (nx->SIGN == 0)
        {
            // x == 0 の場合
            return (GET_NUMBER_HANDLE(&number_object_sint_minus_one));
        }
        else if (nx->SIGN > 0)
        {
            // x > 0 の場合

            // abs(x) == x なので、x~ == -(abs(x) + 1) である。
            ResourceHolderSINT root;
            PMC_HANDLE_UINT r_abs = ep_uint.Increment(nx->ABS);
            root.HookNumber(r_abs);
            NUMBER_OBJECT_SINT* nr = root.AllocateNumber(SIGN_NEGATIVE, r_abs);
            PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(r_abs);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // x < 0 の場合

            // abs(x) == -x なので、x~ == abs(x) - 1 である。
            ResourceHolderSINT root;
            PMC_HANDLE_UINT r_abs = ep_uint.Decrement(nx->ABS);
            root.HookNumber(r_abs);
            NUMBER_OBJECT_SINT* nr = root.AllocateNumber(SIGN_POSITIVE, r_abs);
            PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(r_abs);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

}

/*
 * END OF FILE
 */