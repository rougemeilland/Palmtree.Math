/*
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

#ifndef PMC_UINT_H
#define PMC_UINT_H

#include "pmc.h"

namespace Palmtree::Math::Core::Internal
{

#define __THROWS noexcept(false)

#ifdef PALMTREEMATHCOREUINT_EXPORTS
#define __DLLEXPORT_UINT __declspec(dllexport)
#else
#define __DLLEXPORT_UINT __declspec(dllimport)
#endif

#pragma region 型の定義
struct __tag_PMC_HANDLE_UINT
{
#ifdef _M_IX86
    const _UINT32_T HASH_CODE;  // ハッシュコード
#elif defined(_M_X64)
    const _UINT64_T HASH_CODE;  // ハッシュコード
#else
#error unknown platform
#endif
    const struct __tag_UINT_FLAGS
    {
        unsigned    IS_SHARED : 1;          // 本ハンドルが静的に割り当てられていて開放不要ならばTRUE
        unsigned    IS_ZERO : 1;            // 数値が 0 なら TRUE
        unsigned    IS_ONE : 1;             // 数値が 1 なら TRUE
        unsigned    IS_EVEN : 1;            // 数値が偶数なら TRUE
        unsigned    IS_POWER_OF_TWO : 1;    // 数値が 2 のべき乗なら TRUE
    } FLAGS;
#ifdef _M_IX86
    _UINT32_T __dummy;
#elif defined(_M_X64)
    _UINT64_T __dummy;
#else
#error unknown platform
#endif
};
typedef struct __tag_PMC_HANDLE_UINT* PMC_HANDLE_UINT;

struct __tag_PMC_HANDLE_SFMT
{
    _UINT64_T dummy;
};
typedef struct __tag_PMC_HANDLE_SFMT* PMC_HANDLE_SFMT;

#pragma endregion

}

#endif

/*
 * END OF FILE
 */