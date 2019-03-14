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
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    NUMBER_OBJECT_SINT* From_I_Imp(char x_sign, _UINT32_T x_abs)
    {
        if (x_sign == 0)
            return (&number_object_sint_zero);
        else
        {
            ResourceHolderSINT root;
            PMC_HANDLE_UINT o_abs = ep_uint.From_I(x_abs);
            root.HookNumber(o_abs);
            NUMBER_OBJECT_SINT* o = root.AllocateNumber(x_sign, o_abs);
            root.UnlinkNumber(o_abs);
            return (o);
        }
        return (PMC_STATUS_OK);
    }

    NUMBER_OBJECT_SINT* From_L_Imp(char x_sign, _UINT64_T x_abs)
    {
        if (x_sign == 0)
            return (&number_object_sint_zero);
        else
        {
            ResourceHolderSINT root;
            PMC_HANDLE_UINT o_abs = ep_uint.From_L(x_abs);
            root.HookNumber(o_abs);
            NUMBER_OBJECT_SINT* o = root.AllocateNumber(x_sign, o_abs);
            root.UnlinkNumber(o_abs);
            return (o);
        }
        return (PMC_STATUS_OK);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_From_UI(_UINT32_T x)
    {
        return ((PMC_HANDLE_SINT)From_I_Imp(x == 0 ? 0 : 1, x));
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_From_I(_INT32_T x)
    {
        char x_sign;
        _UINT32_T x_abs = GET_ABS_32(x, &x_sign);
        return ((PMC_HANDLE_SINT)From_I_Imp(x_sign, x_abs));
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_From_UL(_UINT64_T x)
    {
        return ((PMC_HANDLE_SINT)From_L_Imp(x == 0 ? 0 : 1, x));
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_From_L(_INT64_T x)
    {
        char x_sign;
        _UINT64_T x_abs = GET_ABS_64(x, &x_sign);
        return ((PMC_HANDLE_SINT)From_L_Imp(x_sign, x_abs));
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_From_UX(PMC_HANDLE_UINT x)
    {
        return ((PMC_HANDLE_SINT)DuplicateNumber_UX(x));
    }

}


/*
 * END OF FILE
 */