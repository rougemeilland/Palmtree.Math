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


#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"


namespace Palmtree::Math::Core::Internal
{

    _UINT32_T PMC_ToUInt32_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        char p_sign = np->SIGN;
        if (p_sign == 0)
        {
            // p == 0 の場合

            return (0);
        }
        else if (p_sign < 0)
        {
            // p < 0 の場合

            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        }
        else
        {
            // p >  0 の場合
            return (ep_uint.ToUInt32(np->ABS));
        }
    }

    _INT32_T PMC_ToInt32_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        SIGN_T p_sign = np->SIGN;
        _UINT32_T p_abs = ep_uint.ToUInt32(np->ABS);
        return (GET_INT_32(p_sign, p_abs));
    }

    _UINT64_T PMC_ToUInt64_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        char p_sign = np->SIGN;
        if (p_sign == 0)
        {
            // p == 0 の場合

            return (0);
        }
        else if (p_sign < 0)
        {
            // p < 0 の場合

            throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
        }
        else
        {
            // p >  0 の場合
            return (ep_uint.ToUInt64(np->ABS));
        }
    }

    _INT64_T PMC_ToInt64_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        SIGN_T p_sign = np->SIGN;
        _UINT64_T p_abs = ep_uint.ToUInt64(np->ABS);
        return (GET_INT_64(p_sign, p_abs));
    }

    PMC_HANDLE_UINT PMC_ToUBigInt_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        char p_sign = np->SIGN;
        if (p_sign == 0)
        {
            // p == 0 の場合

            return (number_handle_uint_zero);
        }
        else if (p_sign < 0)
        {
            // p < 0 の場合

            throw OverflowException(L"符号なし多倍長整数への型変換に失敗しました。");
        }
        else
        {
            // p >  0 の場合
            return (ep_uint.Clone(np->ABS));
        }
    }

}

/*
 * END OF FILE
 */