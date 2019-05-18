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

#include <math.h>
#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"

namespace Palmtree::Math::Core::Internal
{

    static PMC_HANDLE_RTNL EPILOGUE(ResourceHolderRTNL& root, PMC_HANDLE_SINT numerator) noexcept(false)
    {
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = number_handle_uint_one;
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(numerator, denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_From_I(ThreadContext& tc, _INT32_T x) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.From(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_L(ThreadContext& tc, _INT64_T x) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.From(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_UI(ThreadContext& tc, _UINT32_T x) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.From(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_UL(ThreadContext& tc, _UINT64_T x) noexcept(false)
    {
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.From(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.From(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_X(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        ResourceHolderRTNL root(tc);
        return (EPILOGUE(root, ep_sint.Clone(tc, x)));
    }

    PMC_HANDLE_RTNL PMC_From_DECIMAL(ThreadContext& tc, DECIMAL x) noexcept(false)
    {
        ResourceHolderRTNL root(tc);

        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.From(tc, x, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_From_DOUBLE(ThreadContext& tc, double x) noexcept(false)
    {
        if (!isfinite(x))
            throw OverflowException(L"与えられた数値が無限大または NAN のため変換できません。");

        ResourceHolderRTNL root(tc);

        PMC_HANDLE_UINT r_denominator;
        PMC_HANDLE_SINT r_numerator = ep_sint.From(tc, x, &r_denominator);
        root.HookNumber(r_numerator);
        root.HookNumber(r_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(r_numerator, r_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

}


/*
 * END OF FILE
 */