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

    static PMC_HANDLE_RTNL EPILOGUE(ResourceHolderRTNL& root, PMC_HANDLE_SINT numerator) noexcept(false)
    {
        root.HookNumber(numerator);
        PMC_HANDLE_UINT denominator = number_handle_uint_one;
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(numerator, denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_From_I(_INT32_T x) noexcept(false)
    {
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.From(x)));
    }

    PMC_HANDLE_RTNL PMC_From_L(_INT64_T x) noexcept(false)
    {
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.From(x)));
    }

    PMC_HANDLE_RTNL PMC_From_UI(_UINT32_T x) noexcept(false)
    {
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.From(x)));
    }

    PMC_HANDLE_RTNL PMC_From_UL(_UINT64_T x) noexcept(false)
    {
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.From(x)));
    }

    PMC_HANDLE_RTNL PMC_From_UX(PMC_HANDLE_UINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.From(x)));
    }

    PMC_HANDLE_RTNL PMC_From_X(PMC_HANDLE_SINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        ResourceHolderRTNL root;
        return (EPILOGUE(root, ep_sint.Clone(x)));
    }

}


/*
 * END OF FILE
 */