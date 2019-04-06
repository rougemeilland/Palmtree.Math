﻿/*
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
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_STATISTICS_INFO_UINT statistics_info;

    _UINT64_T PMC_GetPerformanceCounter(const wchar_t* key)
    {
        if (lstrcmpW(key, L"div32count") == 0)
            return (statistics_info.COUNT_DIV32);
        if (lstrcmpW(key, L"div64count") == 0)
            return (statistics_info.COUNT_DIV64);
        if (lstrcmpW(key, L"multi32count") == 0)
            return (statistics_info.COUNT_MULTI32);
        if (lstrcmpW(key, L"multi32count") == 0)
            return (statistics_info.COUNT_MULTI64);
        if (lstrcmpW(key, L"allocateblock") == 0)
            return (statistics_info.COUNT_ALLOCATE_BLOCK);
        if (lstrcmpW(key, L"allocatenumberobject") == 0)
            return (statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT);
        if (lstrcmpW(key, L"allocatenumber") == 0)
            return (statistics_info.COUNT_ALLOCATE_NUMBER);
        if (lstrcmpW(key, L"hooknumberux") == 0)
            return (statistics_info.COUNT_HOOK_NUMBER);
        throw KeyNotFoundException(L"未知のキーが渡されました。");
    }

}

/*
 * END OF FILE
 */