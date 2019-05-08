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


#include "pmc.h"
#include "pmc_cpuid.h"


#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
#endif

#pragma region マクロの定義
#define countof(x)  (sizeof(x)/sizeof(*(x)))

#define PMC_SIGNATURE (((_UINT32_T)'I' << 24) | ((_UINT32_T)'c' << 16) | ((_UINT32_T)'M' << 8) | (_UINT32_T)'p')
#define PMC_UINT_SIGNATURE (((_UINT32_T)'T' << 24) | ((_UINT32_T)'n' << 16) | ((_UINT32_T)'i' << 8) | (_UINT32_T)'U')
#define PMC_SINT_SIGNATURE (((_UINT32_T)'t' << 24) | ((_UINT32_T)'N' << 16) | ((_UINT32_T)'I' << 8) | (_UINT32_T)'s')
#define PMC_RTNL_SIGNATURE (((_UINT32_T)'L' << 24) | ((_UINT32_T)'n' << 16) | ((_UINT32_T)'t' << 8) | (_UINT32_T)'R')
#define PMC_SFMT_SIGNATURE (((_UINT32_T)'t' << 24) | ((_UINT32_T)'M' << 16) | ((_UINT32_T)'F' << 8) | (_UINT32_T)'s')
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

#pragma region インライン関数

    __inline static SIGN_T INVERT_SIGN(SIGN_T sign)
    {
        return ((SIGN_T)-(int)sign);
    }

    __inline static SIGN_T PRODUCT_SIGN(SIGN_T u_sign, SIGN_T v_sign)
    {
        if (u_sign == 0)
            return (SIGN_ZERO);
        else if (u_sign > 0)
            return (v_sign);
        else
            return (INVERT_SIGN(v_sign));
    }

    // 整数値の符号と絶対値を取得する
    __inline static _UINT32_T GET_ABS_32(_INT32_T u, SIGN_T* sign)
    {
        if (u > 0)
        {
            *sign = SIGN_POSITIVE;
            return ((_UINT32_T)u);
        }
        else if (u == 0)
        {
            *sign = SIGN_ZERO;
            return (0);
        }
        else
        {
            *sign = SIGN_NEGATIVE;
            return ((_UINT32_T)u == 0x80000000U ? 0x80000000U : (_UINT32_T)-u);
        }
    }

    // 整数値の符号と絶対値を取得する
    __inline static _UINT64_T GET_ABS_64(_INT64_T u, SIGN_T* sign)
    {
        if (u > 0)
        {
            *sign = SIGN_POSITIVE;
            return ((_UINT64_T)u);
        }
        else if (u == 0)
        {
            *sign = SIGN_ZERO;
            return (0);
        }
        else
        {
            *sign = SIGN_NEGATIVE;
            return ((_UINT64_T)u == 0x8000000000000000UL ? 0x8000000000000000UL : (_UINT64_T)-u);
        }
    }

#pragma endregion

#ifdef __cplusplus
}
#endif

#endif /* PMC_INTERNAL_H */


/*
 * END OF FILE
 */