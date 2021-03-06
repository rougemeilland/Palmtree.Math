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

#pragma once

#ifndef PMC_RTNL_H
#define PMC_RTNL_H

#include "pmc_uint.h"
#include "pmc_sint.h"

#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
#endif

#ifdef PALMTREEMATHCORERTNL_EXPORTS
#define __DLLEXPORT_RTNL __declspec(dllexport)
#else
#define __DLLEXPORT_RTNL __declspec(dllimport)
#endif

#pragma region 型の定義
    union __tag_PMC_HANDLE_RTNL
    {
        const struct __tag_RTNL_FLAGS
        {
            unsigned    IS_SHARED : 1;          // 本ハンドルが静的に割り当てられていて開放不要ならばTRUE
            unsigned    IS_INT : 1;             // 数値が整数なら TRUE
            unsigned    IS_ZERO : 1;            // 数値が 0 なら TRUE
            unsigned    IS_ONE : 1;             // 数値が 1 なら TRUE
            unsigned    IS_MINUS_ONE : 1;       // 数値が -1 なら TRUE
        } FLAGS;
#ifdef _M_IX86
        _UINT32_T __dummy;
#elif defined(_M_X64)
        _UINT64_T __dummy;
#else
#error unknown platform
#endif
    };
    typedef union __tag_PMC_HANDLE_RTNL* PMC_HANDLE_RTNL;

#pragma endregion


#ifdef __cplusplus
}
#endif

#endif /* PMC_SINT_H */
