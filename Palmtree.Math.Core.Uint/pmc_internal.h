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


#pragma once

#ifndef PMC_INTERNAL_H
#define PMC_INTERNAL_H


#include <windows.h>
#include "pmc.h"
#include "pmc_cpuid.h"


#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
    extern "C"
    {
#endif

#pragma region マクロの定義
#define countof(x)  (sizeof(x)/sizeof(*(x)))

#define PMC_SIGNATURE (((_UINT32_T)'I' << 24) | ((_UINT32_T)'c' << 16) | ((_UINT32_T)'M' << 8) | (_UINT32_T)'p')
#define PMC_UINT_SIGNATURE (((_UINT32_T)'T' << 24) | ((_UINT32_T)'n' << 16) | ((_UINT32_T)'i' << 8) | (_UINT32_T)'U')
#define PMC_SINT_SIGNATURE (((_UINT32_T)'t' << 24) | ((_UINT32_T)'N' << 16) | ((_UINT32_T)'I' << 8) | (_UINT32_T)'s')
#pragma endregion


#pragma region 型の定義
#ifdef _M_IX86
        typedef _UINT32_T __UNIT_TYPE;
#elif defined(_M_X64)
        typedef _UINT64_T __UNIT_TYPE;
#else
#error unknown platform
#endif

#define __UNIT_TYPE_BYTE_COUNT (sizeof(__UNIT_TYPE))
#define __UNIT_TYPE_BIT_COUNT (sizeof(__UNIT_TYPE) * 8)
#pragma endregion


#ifdef __cplusplus
    }
}
#endif

#endif /* PMC_INTERNAL_H */


/*
 * END OF FILE
 */