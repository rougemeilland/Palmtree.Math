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

#ifndef PMC_INLINE_FUNC_H
#define PMC_INLINE_FUNC_H


#include <windows.h>
#include <intrin.h>
#include "pmc_internal.h"


#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
    extern "C"
    {
#endif


        __inline static void _COPY_MEMORY_BYTE(void* d, const void* s, size_t count)
        {
            __movsb((unsigned char*)d, (const unsigned char*)s, count);
        }

        __inline static void _COPY_MEMORY_32(_UINT32_T* d, const _UINT32_T* s, _UINT32_T count)
        {
            __movsd((unsigned long *)d, (unsigned long *)s, (unsigned long)count);
        }

#ifdef _M_X64
        __inline static void _COPY_MEMORY_64(_UINT64_T* d, const _UINT64_T* s, _UINT64_T count)
        {
            __movsq(d, s, count);
        }
#endif

        __inline static void _COPY_MEMORY_UNIT(__UNIT_TYPE* d, const __UNIT_TYPE* s, __UNIT_TYPE count)
        {
#ifdef _M_IX86
            __movsd((unsigned long *)d, (unsigned long *)s, (unsigned long)count);
#elif defined(_M_X64)
            __movsq(d, s, count);
#else
#error unknown platform
#endif
        }

        __inline static void _ZERO_MEMORY_BYTE(void* d, size_t count)
        {
            __stosb((unsigned char*)d, 0, count);
        }

        __inline static void _ZERO_MEMORY_16(_UINT16_T* d, size_t count)
        {
            __stosw(d, 0, count);
        }

        __inline static void _ZERO_MEMORY_32(_UINT32_T* d, size_t count)
        {
            __stosd((unsigned long*)d, 0, count);
        }

#ifdef _M_X64
        __inline static void _ZERO_MEMORY_64(_UINT64_T* d, size_t count)
        {
            __stosq(d, 0, count);
        }
#endif

        __inline static void _ZERO_MEMORY_UNIT(__UNIT_TYPE* d, __UNIT_TYPE count)
        {
#ifdef _M_IX86
            __stosd((unsigned long*)d, 0, (unsigned long)count);
#elif defined(_M_X64)
            __stosq(d, 0, count);
#else
#error unknown platform
#endif
        }

        __inline static void _FILL_MEMORY_BYTE(void* d, unsigned char x, size_t count)
        {
            __stosb((unsigned char*)d, x, count);
        }

        __inline static void _FILL_MEMORY_16(_UINT16_T* d, _UINT16_T x, size_t count)
        {
            __stosw((_UINT16_T*)d, x, count);
        }

        __inline static void _FILL_MEMORY_32(_UINT32_T* d, _UINT32_T x, size_t count)
        {
            __stosd((unsigned long*)d, x, count);
        }

#ifdef _M_X64
        __inline static void _FILL_MEMORY_64(_UINT64_T* d, _UINT64_T x, size_t count)
        {
            __stosq(d, x, count);
        }
#endif

        __inline static void _FILL_MEMORY_UNIT(__UNIT_TYPE* d, __UNIT_TYPE x, __UNIT_TYPE count)
        {
#ifdef _M_IX86
            __stosd((unsigned long*)d, x, (unsigned long)count);
#elif defined(_M_X64)
            __stosq(d, x, count);
#else
#error unknown platform
#endif
        }

        __inline static _UINT64_T _FROMWORDTODWORD(_UINT32_T value_high, _UINT32_T value_low)
        {
            return (((_UINT64_T)value_high << 32) | value_low);
        }

        __inline static _UINT32_T _FROMDWORDTOWORD(_UINT64_T value, _UINT32_T *result_high)
        {
            *result_high = (_UINT32_T)(value >> 32);
            return ((_UINT32_T)value);
        }

        __inline static __UNIT_TYPE _MAKE_MASK_UNIT(int bits)
        {
            return (((__UNIT_TYPE)1UL << bits) - 1);
        }

        __inline static __UNIT_TYPE _DIVIDE_CEILING_UNIT(__UNIT_TYPE u, __UNIT_TYPE v)
        {
            return ((u + v - 1) / v);
        }

        __inline static size_t _DIVIDE_CEILING_SIZE(size_t u, size_t v)
        {
            return ((u + v - 1) / v);
        }

        __inline static __UNIT_TYPE _MAXIMUM_UNIT(__UNIT_TYPE x, __UNIT_TYPE y)
        {
            return (x >= y ? x : y);
        }

        __inline static __UNIT_TYPE _MINIMUM_UNIT(__UNIT_TYPE x, __UNIT_TYPE y)
        {
            return (x <= y ? x : y);
        }

        __inline static char _ADD_UNIT(char carry, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE* w)
        {
#ifdef _M_IX86
            return (_addcarry_u32(carry, u, v, w));
#elif defined(_M_X64)
            return (_addcarry_u64(carry, u, v, w));
#else
#error unknown platform
#endif
        }

        __inline static char _ADDX_UNIT(char carry, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE* w)
        {
#ifdef _M_IX86
            return (_addcarryx_u32(carry, u, v, w));
#elif defined(_M_X64)
            return (_addcarryx_u64(carry, u, v, w));
#else
#error unknown platform
#endif
        }

        __inline static char _SUBTRUCT_UNIT(char borrow, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE* w)
        {
#ifdef _M_IX86
            return (_subborrow_u32(borrow, u, v, w));
#elif defined(_M_X64)
            return (_subborrow_u64(borrow, u, v, w));
#else
#error unknown platform
#endif
        }

        __inline static __UNIT_TYPE _MULTIPLY_UNIT(__UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE* w_hi)
        {
#ifdef _M_IX86
#ifdef _MSC_VER
            return (_FROMDWORDTOWORD((_UINT64_T)u * v, w_hi));
#elif defined(__GNUC__)
            _UINT32_T w_lo;
            __asm__("mull %3": "=a"(w_lo), "=d"(*w_hi) : "0"(u), "rm"(v));
            return (w_lo);
#else
#error unknown compiler
#endif
#elif defined(_M_X64)
            return (_umul128(u, v, w_hi));
#else
#error unknown platform
#endif
        }

        __inline static __UNIT_TYPE _MULTIPLYX_UNIT(__UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE* w_hi)
        {
#ifdef _MSC_VER
#ifdef _M_IX86
            return (_FROMDWORDTOWORD((_UINT64_T)u * v, w_hi));
#elif defined(_M_X64)
            return (_mulx_u64(u, v, w_hi));
#else
#error unknown platform
#endif
#elif defined(__GNUC__)
#ifdef _M_IX86
            _UINT32_T w_lo;
            __asm__("mulxl %3, %0, %1" : "=r"(w_lo), "=r"(*w_hi), "+d"(u) : "rm"(v));
            return (w_lo);
#elif defined(_M_X64)
            _UINT64_T w_lo;
            __asm__("mulxq %3, %0, %1" : "=r"(w_lo), "=r"(*w_hi), "+d"(u) : "rm"(v));
            return (w_lo);
#else
#error unknown platform
#endif
#else
#error unknown compiler
#endif
        }

        // ワード除算関数。一般的な用途向けである。
#ifdef _MSC_VER
#ifdef _M_IX86
        __inline static __UNIT_TYPE _DIVREM_UNIT(__UNIT_TYPE u_high, __UNIT_TYPE u_low, __UNIT_TYPE v, __UNIT_TYPE *r)
        {
            // 64bit/32bitの除算を行う組み込み関数は実装されていない。
            _UINT64_T t = _FROMWORDTODWORD(u_high, u_low);
            *r = (_UINT32_T)(t % v);
            return ((_UINT32_T)(t / v));
        }
#elif defined(_M_X64)
        extern __UNIT_TYPE _DIVREM_UNIT(__UNIT_TYPE u_high, __UNIT_TYPE u_low, __UNIT_TYPE v, __UNIT_TYPE *r);
#else
#error unknown platform
#endif
#elif defined(__GNUC__)
        __inline static __UNIT_TYPE _DIVREM_UNIT(__UNIT_TYPE u_high, __UNIT_TYPE u_low, __UNIT_TYPE v, __UNIT_TYPE *r)
        {
            __UNIT_TYPE q;
#ifdef _M_IX86
            __asm__("divl %4": "=a"(q), "=d"(*r) : "0"(u_low), "1"(u_high), "rm"(v));
#elif defined(_M_X64)
            __asm__("divq %4": "=a"(q), "=d"(*r) : "0"(u_low), "1"(u_high), "rm"(v));
#else
#error unknown platform
#endif
            return (q);
        }
#else
#error unknown compiler
#endif

    // ワード除算関数。除算において除数が一桁しかない場合の古典的算法で繰り返し使用される。
#ifdef _MSC_VER
#ifdef _M_IX86
        __inline static __UNIT_TYPE _DIVREM_SINGLE_UNIT(__UNIT_TYPE r, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE *q)
        {
            // 64bit/32bitの除算を行う組み込み関数は実装されていない。
            _UINT64_T t = _FROMWORDTODWORD(r, u);
            *q = (_UINT32_T)(t / v);
            return ((_UINT32_T)(t % v));
        }
#elif defined(_M_X64)
        extern __UNIT_TYPE _DIVREM_SINGLE_UNIT(__UNIT_TYPE r, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE *q);
#else
#error unknown platform
#endif
#elif defined(__GNUC__)
        __inline static __UNIT_TYPE _DIVREM_SINGLE_UNIT(__UNIT_TYPE r, __UNIT_TYPE u, __UNIT_TYPE v, __UNIT_TYPE *q)
        {
#ifdef _M_IX86
            __asm__("divl %4": "=a"(*q), "=d"(r) : "0"(u), "1"(r), "rm"(v));
#elif defined(_M_X64)
            __asm__("divq %4": "=a"(*q), "=d"(r) : "0"(u), "1"(r), "rm"(v));
#else
#error unknown platform
#endif
            return (r);
        }
#else
#error unknown compiler
#endif

        __inline static void _MEMCPY_UNIT(__UNIT_TYPE* dst, __UNIT_TYPE* src, size_t count)
        {
#ifdef _M_IX86
            __movsd((unsigned long *)dst, (const unsigned long *)src, count);
#elif defined(_M_X64)
            __movsq(dst, src, count);
#else
#error unknown platform
#endif
        }

        __inline static __UNIT_TYPE _ROTATE_L_UNIT(__UNIT_TYPE x, int count)
        {
#ifdef _M_IX86
            return (_rotl(x, count));
#elif defined(_M_X64)
            return (_rotl64(x, count));
#else
#error unknown platform
#endif
        }

        __inline static __UNIT_TYPE _ROTATE_R_UNIT(__UNIT_TYPE x, int count)
        {
#ifdef _M_IX86
            return (_rotr(x, count));
#elif defined(_M_X64)
            return (_rotr64(x, count));
#else
#error unknown platform
#endif
        }

        __inline static int _POPCNT_UNIT(__UNIT_TYPE value)
        {
#ifdef _M_IX86
            return (__popcnt(value));
#elif defined(_M_X64)
            return ((int)__popcnt64(value));
#else
#error unknown platform
#endif
        }

        __inline static int _POPCNT_ALT_UNIT(__UNIT_TYPE x)
        {
#ifdef _M_IX86
            x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
            x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
            x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
            x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
            x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
#elif defined(_M_X64)
            x = (x & 0x5555555555555555) + ((x >> 1) & 0x5555555555555555);
            x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
            x = (x & 0x0f0f0f0f0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f0f0f0f0f);
            x = (x & 0x00ff00ff00ff00ff) + ((x >> 8) & 0x00ff00ff00ff00ff);
            x = (x & 0x0000ffff0000ffff) + ((x >> 16) & 0x0000ffff0000ffff);
            x = (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);
#else
#error unknown platform
#endif
            return((int)x);
        }

        __inline static int _LZCNT_32(_UINT32_T value)
        {
            return (_lzcnt_u32(value));
        }

#ifdef _M_X64
        __inline static int _LZCNT_64(_UINT64_T value)
        {
            return ((int)_lzcnt_u64(value));
        }
#endif

        __inline static int _LZCNT_UNIT(__UNIT_TYPE value)
        {
#ifdef _M_IX86
            return (_lzcnt_u32(value));
#elif defined(_M_X64)
            return ((int)_lzcnt_u64(value));
#else
#error unknown platform
#endif
        }

        __inline static int _LZCNT_ALT_8(unsigned char x)
        {
            if (x == 0)
                return (sizeof(x) * 8);
            DWORD pos;
#ifdef _MSC_VER
            _BitScanReverse(&pos, x);
#elif defined(__GNUC__)
            __asm__("bsrl %1, %0" : "=r"(pos) : "rm"((_UINT32_T)x));
#else
#error unknown compiler
#endif
            return ((unsigned char)(sizeof(x) * 8 - 1 - pos));
        }

        __inline static int _LZCNT_ALT_32(_UINT32_T x)
        {
            if (x == 0)
                return (sizeof(x) * 8);
            DWORD pos;
#ifdef _MSC_VER
            _BitScanReverse(&pos, x);
#elif defined(__GNUC__)
            __asm__("bsrl %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
            return (sizeof(x) * 8 - 1 - pos);
        }

#ifdef _M_X64
        __inline static int _LZCNT_ALT_64(_UINT64_T x)
        {
            if (x == 0)
                return (sizeof(x) * 8);
#ifdef _MSC_VER
            DWORD pos;
            _BitScanReverse64(&pos, x);
#elif defined(__GNUC__)
            _UINT64_T pos;
            __asm__("bsrq %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
            return (sizeof(x) * 8 - 1 - pos);
        }
#endif

        __inline static int _LZCNT_ALT_UNIT(__UNIT_TYPE x)
        {
            if (x == 0)
                return (sizeof(x) * 8);
#ifdef _M_IX86
            DWORD pos;
#ifdef _MSC_VER
            _BitScanReverse(&pos, x);
#elif defined(__GNUC__)
            __asm__("bsrl %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
#elif defined(_M_X64)
#ifdef _MSC_VER
            DWORD pos;
            _BitScanReverse64(&pos, x);
#elif defined(__GNUC__)
            _UINT64_T pos;
            __asm__("bsrq %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
#else
#error unknown platform
#endif
            return (sizeof(x) * 8 - 1 - pos);
        }

        __inline static int _TZCNT_UNIT(__UNIT_TYPE x)
        {
#ifdef _M_IX86
            return (_tzcnt_u32(x));
#elif defined(_M_X64)
            return ((int)_tzcnt_u64(x));
#else
#error unknown platform
#endif
        }

        __inline static int _TZCNT_ALT_USING_POPCNT_UNIT(__UNIT_TYPE x)
        {
#ifdef _M_IX86
            return(__popcnt(~x & (x - 1)));
#elif defined(_M_X64)
            return((int)__popcnt64(~x & (x - 1)));
#else
#error unknown platform
#endif
        }

        __inline static int _TZCNT_ALT_UNIT(__UNIT_TYPE x)
        {
            if (x == 0)
                return (sizeof(x) * 8);
#ifdef _M_IX86
            DWORD pos;
#ifdef _MSC_VER
            _BitScanForward(&pos, x);
#elif defined(__GNUC__)
            __asm__("bsfl %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
#elif defined(_M_X64)
#ifdef _MSC_VER
            DWORD pos;
            _BitScanForward64(&pos, x);
#elif defined(__GNUC__)
            _UINT64_T pos;
            __asm__("bsfq %1, %0" : "=r"(pos) : "rm"(x));
#else
#error unknown compiler
#endif
#else
#error unknown platform
#endif
            return (pos);
        }

        // bit の並びを逆順にする
        __inline static _UINT32_T _REVERSE_BIT_ORDER_32(_UINT32_T x)
        {
            x = ((x & 0x55555555U) << 1) | ((x & 0xaaaaaaaaU) >> 1);
            x = ((x & 0x33333333U) << 2) | ((x & 0xccccccccU) >> 2);
            x = ((x & 0x0f0f0f0fU) << 4) | ((x & 0xf0f0f0f0U) >> 4);
            x = ((x & 0x00ff00ffU) << 8) | ((x & 0xff00ff00U) >> 8);
            x = (x << 16) | (x >> 16);
            return (x);
        }

#ifdef _M_X64
        // bit の並びを逆順にする
        __inline static _UINT64_T _REVERSE_BIT_ORDER_64(_UINT64_T x)
        {
            x = ((x & 0x5555555555555555UL) << 1) | ((x & 0xaaaaaaaaaaaaaaaaUL) >> 1);
            x = ((x & 0x3333333333333333UL) << 2) | ((x & 0xccccccccccccccccUL) >> 2);
            x = ((x & 0x0f0f0f0f0f0f0f0fUL) << 4) | ((x & 0xf0f0f0f0f0f0f0f0UL) >> 4);
            x = ((x & 0x00ff00ff00ff00ffUL) << 8) | ((x & 0xff00ff00ff00ff00UL) >> 8);
            x = ((x & 0x0000ffff0000ffffUL) << 16) | ((x & 0xffff0000ffff0000UL) >> 16);
            x = (x << 32) | (x >> 32);
            return (x);
        }
#endif

        // bit の並びを逆順にする
        __inline static __UNIT_TYPE _REVERSE_BIT_ORDER_UNIT(__UNIT_TYPE x)
        {
#ifdef _M_IX86
            x = ((x & 0x55555555U) << 1) | ((x & 0xaaaaaaaaU) >> 1);
            x = ((x & 0x33333333U) << 2) | ((x & 0xccccccccU) >> 2);
            x = ((x & 0x0f0f0f0fU) << 4) | ((x & 0xf0f0f0f0U) >> 4);
            x = ((x & 0x00ff00ffU) << 8) | ((x & 0xff00ff00U) >> 8);
            x = (x << 16) | (x >> 16);
#elif defined(_M_X64)
            x = ((x & 0x5555555555555555UL) << 1) | ((x & 0xaaaaaaaaaaaaaaaaUL) >> 1);
            x = ((x & 0x3333333333333333UL) << 2) | ((x & 0xccccccccccccccccUL) >> 2);
            x = ((x & 0x0f0f0f0f0f0f0f0fUL) << 4) | ((x & 0xf0f0f0f0f0f0f0f0UL) >> 4);
            x = ((x & 0x00ff00ff00ff00ffUL) << 8) | ((x & 0xff00ff00ff00ff00UL) >> 8);
            x = ((x & 0x0000ffff0000ffffUL) << 16) | ((x & 0xffff0000ffff0000UL) >> 16);
            x = (x << 32) | (x >> 32);
#else
#error unknown platform
#endif
            return (x);
        }

        // 整数値の符号と絶対値を取得する
        __inline static _UINT32_T GET_ABS_32(_INT32_T u, char*sign)
        {
            if (u > 0)
            {
                *sign = 1;
                return ((_UINT32_T)u);
            }
            else if (u == 0)
            {
                *sign = 0;
                return (0);
            }
            else
            {
                *sign = -1;
                return ((_UINT32_T)u == 0x80000000U ? 0x80000000U : (_UINT32_T)-u);
            }
        }

        // 整数値の符号と絶対値を取得する
        __inline static _UINT64_T GET_ABS_64(_INT64_T u, char*sign)
        {
            if (u > 0)
            {
                *sign = 1;
                return ((_UINT64_T)u);
            }
            else if (u == 0)
            {
                *sign = 0;
                return (0);
            }
            else
            {
                *sign = -1;
                return ((_UINT64_T)u == 0x8000000000000000UL ? 0x8000000000000000UL : (_UINT64_T)-u);
            }
        }

#ifdef __cplusplus
    }
}
#endif

#endif /* PMC_INLINE_FUNC_H */


/*
 * END OF FILE
 */