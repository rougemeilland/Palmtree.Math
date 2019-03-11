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
#include "pmc_exception.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    _UINT32_T __PMC_CALL PMC_To_X_I(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(_UINT32_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_To_X_I;1");
        }
        NUMBER_HEADER* np = (NUMBER_HEADER*)p;
        CheckNumber(np);
        if (np->UNIT_BIT_COUNT > sizeof(_UINT32_T) * 8)
            throw OverflowException(L"32bit整数への型変換に失敗しました。");
        return (np->IS_ZERO ? 0 : (_UINT32_T)np->BLOCK[0]);
    }

    _UINT64_T __PMC_CALL PMC_To_X_L(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(_UINT64_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_To_X_L;1");
        }
        NUMBER_HEADER* np = (NUMBER_HEADER*)p;
        CheckNumber(np);
        if (np->UNIT_BIT_COUNT > sizeof(_UINT64_T) * 8)
            throw OverflowException(L"64bit整数への型変換に失敗しました。");
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
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_To_X_L;2");
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