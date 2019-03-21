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

    PMC_STATUS_CODE PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false)
    {
        PMC_STATUS_CODE rc;
        if (source == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"source");
        if (o == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o");
        ResourceHolderSINT root;
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_abs;
        if ((rc = ep_uint.TryParseForSINT(source, number_styles, format_option, &o_sign, &o_abs)) != PMC_STATUS_OK)
            return (rc);
        root.HookNumber(o_abs);
        NUMBER_OBJECT_SINT* no = root.AllocateNumber(o_sign, o_abs);
        *o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(o_abs);
        root.UnlinkNumber(no);
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */