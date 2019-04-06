/*
 * The MIT License
 *
 * Copyright 2018 Palmtree Software.
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
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    _INT32_T PMC_ToInt32_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(_UINT32_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt32_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT32_T) * 8)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        if (np->BLOCK[0] > 0x7fffffffU)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        return ((_INT32_T)np->BLOCK[0]);
    }

    _INT64_T PMC_ToInt64_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(_UINT64_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT64_T) * 8)
            throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        else
        {
            if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT)
            {
                // 値が 1 ワードで表現できる場合
                if (np->BLOCK[0] > 0x7fffffffffffffffUL)
                    throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
                return (np->BLOCK[0]);
            }
            else if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT * 2)
            {
                // 値が 2 ワードで表現できる場合
                if (np->BLOCK[1] > 0x7fffffffUL)
                    throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
                return (_FROMWORDTODWORD((_UINT32_T)np->BLOCK[1], (_UINT32_T)np->BLOCK[0]));
            }
            else
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;2");
        }
    }

    _UINT32_T PMC_ToUInt32_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(_UINT32_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt32_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT32_T) * 8)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        return (np->IS_ZERO ? 0 : (_UINT32_T)np->BLOCK[0]);
    }

    _UINT64_T PMC_ToUInt64_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(_UINT64_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT64_T) * 8)
            throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        else
        {
            if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT)
            {
                // 値が 1 ワードで表現できる場合
                return (np->BLOCK[0]);
            }
            else if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT * 2)
            {
                // 値が 2 ワードで表現できる場合
                return (_FROMWORDTODWORD((_UINT32_T)np->BLOCK[1], (_UINT32_T)np->BLOCK[0]));
            }
            else
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;2");
        }
    }

    PMC_STATUS_CODE Initialize_To(PROCESSOR_FEATURES *feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */