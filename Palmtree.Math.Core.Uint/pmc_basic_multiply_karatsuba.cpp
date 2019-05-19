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

#ifdef _DEBUG
#include <iostream>
#endif
#include "pmc_basic_multiply_karatsuba.h"
#include "pmc_basic_multiply_classic.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_exception.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

#ifdef _M_IX86
#define WORD_COUNT_THRESHOLD_CLASSIC    (32768)                 // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x80000000U)           // 現実的に利用可能なユーザメモリの最大サイズ
#elif defined(_M_X64)
#define WORD_COUNT_THRESHOLD_CLASSIC    (32768)                 // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x8000000000000000U)   // 現実的に利用可能なユーザメモリの最大サイズ
#else
#error unknown platform
#endif
namespace Palmtree::Math::Core::Internal::Multiply::Karatsuba
{

    KaratsubaMultiplicationEngine::KaratsubaMultiplicationEngine(bool fixed, Palmtree::Math::Core::Internal::Multiply::Classic::ClassicMultiplicationEngine& classic_engine, BasicOperatorEngine & basic_ep)
        : _fixed(fixed), _classic_engine(classic_engine), _basic_ep(basic_ep)
    {
    }

    KaratsubaMultiplicationEngine::~KaratsubaMultiplicationEngine()
    {
    }

    void KaratsubaMultiplicationEngine::Multiply_UX_UX(ThreadContext & tc, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T & w_buf)
    {
        if (!_fixed && (u_buf.BLOCK_COUNT < WORD_COUNT_THRESHOLD_CLASSIC || v_buf.BLOCK_COUNT < WORD_COUNT_THRESHOLD_CLASSIC))
            _classic_engine.Multiply_UX_UX(u_buf, v_buf, w_buf);
        else
        {
            __UNIT_TYPE temp_buffer_count;
            if (CalculateTempBufferSize(u_buf.BLOCK_COUNT, v_buf.BLOCK_COUNT, temp_buffer_count) || temp_buffer_count > MAX_USER_MEMORY_SIZE / __UNIT_TYPE_BYTE_COUNT)
            {
                // Karatsuba 法に必要な一時メモリ領域のサイズが __UNIT_TYPE (==size_t) で表現できる範囲を超えた場合、
                // 仕方がないので代わりに古典的算法を実行する
                _classic_engine.Multiply_UX_UX(u_buf, v_buf, w_buf);
            }
            else
            {
                ResourceHolderUINT root(tc);

                _UBASIC_T temp_buf = root.AllocateBlock(temp_buffer_count);
#if false
                if (u_buf.BLOCK_COUNT >= v_buf.BLOCK_COUNT)
                    Multiply_UX_UX_Karatsuba(root, temp_buf, 0, u_buf, v_buf, w_buf);
                else
                    Multiply_UX_UX_Karatsuba(root, temp_buf, 0, v_buf, u_buf, w_buf);
#else
                if (u_buf.BLOCK_COUNT >= v_buf.BLOCK_COUNT)
                    Multiply_UX_UX_Karatsuba(temp_buf.BLOCK, u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.BLOCK_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                else
                    Multiply_UX_UX_Karatsuba(temp_buf.BLOCK, v_buf.BLOCK, v_buf.BLOCK_COUNT, u_buf.BLOCK, u_buf.BLOCK_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
#endif
            }
        }
    }

    bool KaratsubaMultiplicationEngine::CalculateTempBufferSize(__UNIT_TYPE u_buf_count, __UNIT_TYPE v_buf_count, __UNIT_TYPE & buffer_size)
    {
        if (!_fixed && (u_buf_count < WORD_COUNT_THRESHOLD_CLASSIC || v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC))
        {
            buffer_size = 0;
            return (false);
        }

        if (u_buf_count < v_buf_count)
            return (CalculateTempBufferSize(v_buf_count, u_buf_count, buffer_size));
        if (u_buf_count <= 1)
        {
            buffer_size = 0;
            return (false);
        }
        __UNIT_TYPE n_half = _DIVIDE_CEILING_UNIT(u_buf_count, 2);

        __UNIT_TYPE size1;
        if (CalculateTempBufferSize(n_half, _MINIMUM_UNIT(v_buf_count, n_half), size1))
        {
            buffer_size = 0;
            return (true);
        }

#ifdef _M_IX86
        if (n_half > (0xffffffffU - 1U) / 4U)
        {
            // 4 * n + 1 が 32bit 符号なし整数で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
#elif defined(_M_X64)
        if (n_half > (0xffffffffffffffffUL - 1U) / 4U)
        {
            // 4 * n + 1 が 64bit 符号なし整数で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
#else
#error unknown platform
#endif
        __UNIT_TYPE size2 = 4 * n_half + 1;

        buffer_size = size1;
        if (_ADD_UNIT(0, buffer_size, size2, &buffer_size))
        {
            // total_size += size2 で桁あふれが起きた場合
            buffer_size = 0;
            return (true);
        }

        return (false);
    }

    static __UNIT_TYPE ShrinkBuffer(__UNIT_TYPE* buf, __UNIT_TYPE buf_count)
    {
        while (buf_count > 0 && buf[buf_count - 1] == 0)
            --buf_count;
        return (buf_count);
    }

    static SIGN_T Compare(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Compare;1");
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Compare;2");
#endif
        if (u_buf_count > v_buf_count)
            return (SIGN_POSITIVE);
        if (u_buf_count < v_buf_count)
            return (SIGN_NEGATIVE);
        __UNIT_TYPE count = u_buf_count;
        __UNIT_TYPE* uptr = u_buf + u_buf_count - 1;
        __UNIT_TYPE* vptr = v_buf + v_buf_count - 1;
        while (count > 0)
        {
            if (*uptr > *vptr)
                return (SIGN_POSITIVE);
            if (*uptr < *vptr)
                return (SIGN_NEGATIVE);
            --uptr;
            --vptr;
            --count;
        }
        return (SIGN_ZERO);
    }

    static void Add(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Add;1");
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Add;2");
#endif
        __UNIT_TYPE* uptr = u_buf;
        __UNIT_TYPE* vptr = v_buf;
        __UNIT_TYPE u_count = u_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        __CARRY_T c = 0;

        __UNIT_TYPE count = v_count >> 5;
        while (count > 0)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            c = _ADD_UNIT(c, uptr[1], vptr[1], &uptr[1]);
            c = _ADD_UNIT(c, uptr[2], vptr[2], &uptr[2]);
            c = _ADD_UNIT(c, uptr[3], vptr[3], &uptr[3]);
            c = _ADD_UNIT(c, uptr[4], vptr[4], &uptr[4]);
            c = _ADD_UNIT(c, uptr[5], vptr[5], &uptr[5]);
            c = _ADD_UNIT(c, uptr[6], vptr[6], &uptr[6]);
            c = _ADD_UNIT(c, uptr[7], vptr[7], &uptr[7]);
            c = _ADD_UNIT(c, uptr[8], vptr[8], &uptr[8]);
            c = _ADD_UNIT(c, uptr[9], vptr[9], &uptr[9]);
            c = _ADD_UNIT(c, uptr[10], vptr[10], &uptr[10]);
            c = _ADD_UNIT(c, uptr[11], vptr[11], &uptr[11]);
            c = _ADD_UNIT(c, uptr[12], vptr[12], &uptr[12]);
            c = _ADD_UNIT(c, uptr[13], vptr[13], &uptr[13]);
            c = _ADD_UNIT(c, uptr[14], vptr[14], &uptr[14]);
            c = _ADD_UNIT(c, uptr[15], vptr[15], &uptr[15]);
            c = _ADD_UNIT(c, uptr[16], vptr[16], &uptr[16]);
            c = _ADD_UNIT(c, uptr[17], vptr[17], &uptr[17]);
            c = _ADD_UNIT(c, uptr[18], vptr[18], &uptr[18]);
            c = _ADD_UNIT(c, uptr[19], vptr[19], &uptr[19]);
            c = _ADD_UNIT(c, uptr[20], vptr[20], &uptr[20]);
            c = _ADD_UNIT(c, uptr[21], vptr[21], &uptr[21]);
            c = _ADD_UNIT(c, uptr[22], vptr[22], &uptr[22]);
            c = _ADD_UNIT(c, uptr[23], vptr[23], &uptr[23]);
            c = _ADD_UNIT(c, uptr[24], vptr[24], &uptr[24]);
            c = _ADD_UNIT(c, uptr[25], vptr[25], &uptr[25]);
            c = _ADD_UNIT(c, uptr[26], vptr[26], &uptr[26]);
            c = _ADD_UNIT(c, uptr[27], vptr[27], &uptr[27]);
            c = _ADD_UNIT(c, uptr[28], vptr[28], &uptr[28]);
            c = _ADD_UNIT(c, uptr[29], vptr[29], &uptr[29]);
            c = _ADD_UNIT(c, uptr[30], vptr[30], &uptr[30]);
            c = _ADD_UNIT(c, uptr[31], vptr[31], &uptr[31]);
            uptr += 32;
            vptr += 32;
            --count;
        }

        if (v_count & 0x10)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            c = _ADD_UNIT(c, uptr[1], vptr[1], &uptr[1]);
            c = _ADD_UNIT(c, uptr[2], vptr[2], &uptr[2]);
            c = _ADD_UNIT(c, uptr[3], vptr[3], &uptr[3]);
            c = _ADD_UNIT(c, uptr[4], vptr[4], &uptr[4]);
            c = _ADD_UNIT(c, uptr[5], vptr[5], &uptr[5]);
            c = _ADD_UNIT(c, uptr[6], vptr[6], &uptr[6]);
            c = _ADD_UNIT(c, uptr[7], vptr[7], &uptr[7]);
            c = _ADD_UNIT(c, uptr[8], vptr[8], &uptr[8]);
            c = _ADD_UNIT(c, uptr[9], vptr[9], &uptr[9]);
            c = _ADD_UNIT(c, uptr[10], vptr[10], &uptr[10]);
            c = _ADD_UNIT(c, uptr[11], vptr[11], &uptr[11]);
            c = _ADD_UNIT(c, uptr[12], vptr[12], &uptr[12]);
            c = _ADD_UNIT(c, uptr[13], vptr[13], &uptr[13]);
            c = _ADD_UNIT(c, uptr[14], vptr[14], &uptr[14]);
            c = _ADD_UNIT(c, uptr[15], vptr[15], &uptr[15]);
            uptr += 16;
            vptr += 16;
        }

        if (v_count & 0x8)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            c = _ADD_UNIT(c, uptr[1], vptr[1], &uptr[1]);
            c = _ADD_UNIT(c, uptr[2], vptr[2], &uptr[2]);
            c = _ADD_UNIT(c, uptr[3], vptr[3], &uptr[3]);
            c = _ADD_UNIT(c, uptr[4], vptr[4], &uptr[4]);
            c = _ADD_UNIT(c, uptr[5], vptr[5], &uptr[5]);
            c = _ADD_UNIT(c, uptr[6], vptr[6], &uptr[6]);
            c = _ADD_UNIT(c, uptr[7], vptr[7], &uptr[7]);
            uptr += 8;
            vptr += 8;
        }

        if (v_count & 0x4)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            c = _ADD_UNIT(c, uptr[1], vptr[1], &uptr[1]);
            c = _ADD_UNIT(c, uptr[2], vptr[2], &uptr[2]);
            c = _ADD_UNIT(c, uptr[3], vptr[3], &uptr[3]);
            uptr += 4;
            vptr += 4;
        }

        if (v_count & 0x2)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            c = _ADD_UNIT(c, uptr[1], vptr[1], &uptr[1]);
            uptr += 2;
            vptr += 2;
        }

        if (v_count & 0x1)
        {
            c = _ADD_UNIT(c, uptr[0], vptr[0], &uptr[0]);
            uptr += 1;
            vptr += 1;
        }

        u_count -= v_count;
        while (u_count > 0 && c)
        {
            c = _ADD_UNIT(c, uptr[0], 0, &uptr[0]);
            ++uptr;
            --u_count;
        }

        if (c)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Add;3");
    }

    static void USubtruct(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;1");
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;2");
#endif
        __UNIT_TYPE* uptr = u_buf;
        __UNIT_TYPE* vptr = v_buf;
        __UNIT_TYPE u_count = u_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        __BORROW_T b = 0;

        __UNIT_TYPE count = v_count >> 5;
        while (count > 0)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, uptr[8], vptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, uptr[9], vptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, uptr[10], vptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, uptr[11], vptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, uptr[12], vptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, uptr[13], vptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, uptr[14], vptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, uptr[15], vptr[15], &uptr[15]);
            b = _SUBTRUCT_UNIT(b, uptr[16], vptr[16], &uptr[16]);
            b = _SUBTRUCT_UNIT(b, uptr[17], vptr[17], &uptr[17]);
            b = _SUBTRUCT_UNIT(b, uptr[18], vptr[18], &uptr[18]);
            b = _SUBTRUCT_UNIT(b, uptr[19], vptr[19], &uptr[19]);
            b = _SUBTRUCT_UNIT(b, uptr[20], vptr[20], &uptr[20]);
            b = _SUBTRUCT_UNIT(b, uptr[21], vptr[21], &uptr[21]);
            b = _SUBTRUCT_UNIT(b, uptr[22], vptr[22], &uptr[22]);
            b = _SUBTRUCT_UNIT(b, uptr[23], vptr[23], &uptr[23]);
            b = _SUBTRUCT_UNIT(b, uptr[24], vptr[24], &uptr[24]);
            b = _SUBTRUCT_UNIT(b, uptr[25], vptr[25], &uptr[25]);
            b = _SUBTRUCT_UNIT(b, uptr[26], vptr[26], &uptr[26]);
            b = _SUBTRUCT_UNIT(b, uptr[27], vptr[27], &uptr[27]);
            b = _SUBTRUCT_UNIT(b, uptr[28], vptr[28], &uptr[28]);
            b = _SUBTRUCT_UNIT(b, uptr[29], vptr[29], &uptr[29]);
            b = _SUBTRUCT_UNIT(b, uptr[30], vptr[30], &uptr[30]);
            b = _SUBTRUCT_UNIT(b, uptr[31], vptr[31], &uptr[31]);
            uptr += 32;
            vptr += 32;
            --count;
        }

        if (v_count & 0x10)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, uptr[8], vptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, uptr[9], vptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, uptr[10], vptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, uptr[11], vptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, uptr[12], vptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, uptr[13], vptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, uptr[14], vptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, uptr[15], vptr[15], &uptr[15]);
            uptr += 16;
            vptr += 16;
        }

        if (v_count & 0x8)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &uptr[7]);
            uptr += 8;
            vptr += 8;
        }

        if (v_count & 0x4)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &uptr[3]);
            uptr += 4;
            vptr += 4;
        }

        if (v_count & 0x2)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &uptr[1]);
            uptr += 2;
            vptr += 2;
        }

        if (v_count & 0x1)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &uptr[0]);
            uptr += 1;
            vptr += 1;
        }

        u_count -= v_count;
        while (u_count > 0 && b)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], 0, &uptr[0]);
            ++uptr;
            --u_count;
        }

        if (b)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;3");
    }

    static void USubtruct(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;1");
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;2");
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;3");
        if (w_buf_count < u_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;4");
#endif
        __UNIT_TYPE* uptr = u_buf;
        __UNIT_TYPE* vptr = v_buf;
        __UNIT_TYPE* wptr = w_buf;
        __UNIT_TYPE u_count = u_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        __BORROW_T b = 0;

        __UNIT_TYPE count = v_count >> 5;
        while (count > 0)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &wptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &wptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &wptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &wptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &wptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &wptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &wptr[7]);
            b = _SUBTRUCT_UNIT(b, uptr[8], vptr[8], &wptr[8]);
            b = _SUBTRUCT_UNIT(b, uptr[9], vptr[9], &wptr[9]);
            b = _SUBTRUCT_UNIT(b, uptr[10], vptr[10], &wptr[10]);
            b = _SUBTRUCT_UNIT(b, uptr[11], vptr[11], &wptr[11]);
            b = _SUBTRUCT_UNIT(b, uptr[12], vptr[12], &wptr[12]);
            b = _SUBTRUCT_UNIT(b, uptr[13], vptr[13], &wptr[13]);
            b = _SUBTRUCT_UNIT(b, uptr[14], vptr[14], &wptr[14]);
            b = _SUBTRUCT_UNIT(b, uptr[15], vptr[15], &wptr[15]);
            b = _SUBTRUCT_UNIT(b, uptr[16], vptr[16], &wptr[16]);
            b = _SUBTRUCT_UNIT(b, uptr[17], vptr[17], &wptr[17]);
            b = _SUBTRUCT_UNIT(b, uptr[18], vptr[18], &wptr[18]);
            b = _SUBTRUCT_UNIT(b, uptr[19], vptr[19], &wptr[19]);
            b = _SUBTRUCT_UNIT(b, uptr[20], vptr[20], &wptr[20]);
            b = _SUBTRUCT_UNIT(b, uptr[21], vptr[21], &wptr[21]);
            b = _SUBTRUCT_UNIT(b, uptr[22], vptr[22], &wptr[22]);
            b = _SUBTRUCT_UNIT(b, uptr[23], vptr[23], &wptr[23]);
            b = _SUBTRUCT_UNIT(b, uptr[24], vptr[24], &wptr[24]);
            b = _SUBTRUCT_UNIT(b, uptr[25], vptr[25], &wptr[25]);
            b = _SUBTRUCT_UNIT(b, uptr[26], vptr[26], &wptr[26]);
            b = _SUBTRUCT_UNIT(b, uptr[27], vptr[27], &wptr[27]);
            b = _SUBTRUCT_UNIT(b, uptr[28], vptr[28], &wptr[28]);
            b = _SUBTRUCT_UNIT(b, uptr[29], vptr[29], &wptr[29]);
            b = _SUBTRUCT_UNIT(b, uptr[30], vptr[30], &wptr[30]);
            b = _SUBTRUCT_UNIT(b, uptr[31], vptr[31], &wptr[31]);
            uptr += 32;
            vptr += 32;
            wptr += 32;
            --count;
        }

        if (v_count & 0x10)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &wptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &wptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &wptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &wptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &wptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &wptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &wptr[7]);
            b = _SUBTRUCT_UNIT(b, uptr[8], vptr[8], &wptr[8]);
            b = _SUBTRUCT_UNIT(b, uptr[9], vptr[9], &wptr[9]);
            b = _SUBTRUCT_UNIT(b, uptr[10], vptr[10], &wptr[10]);
            b = _SUBTRUCT_UNIT(b, uptr[11], vptr[11], &wptr[11]);
            b = _SUBTRUCT_UNIT(b, uptr[12], vptr[12], &wptr[12]);
            b = _SUBTRUCT_UNIT(b, uptr[13], vptr[13], &wptr[13]);
            b = _SUBTRUCT_UNIT(b, uptr[14], vptr[14], &wptr[14]);
            b = _SUBTRUCT_UNIT(b, uptr[15], vptr[15], &wptr[15]);
            uptr += 16;
            vptr += 16;
            wptr += 16;
        }

        if (v_count & 0x8)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &wptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &wptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &wptr[3]);
            b = _SUBTRUCT_UNIT(b, uptr[4], vptr[4], &wptr[4]);
            b = _SUBTRUCT_UNIT(b, uptr[5], vptr[5], &wptr[5]);
            b = _SUBTRUCT_UNIT(b, uptr[6], vptr[6], &wptr[6]);
            b = _SUBTRUCT_UNIT(b, uptr[7], vptr[7], &wptr[7]);
            uptr += 8;
            vptr += 8;
            wptr += 8;
        }

        if (v_count & 0x4)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &wptr[1]);
            b = _SUBTRUCT_UNIT(b, uptr[2], vptr[2], &wptr[2]);
            b = _SUBTRUCT_UNIT(b, uptr[3], vptr[3], &wptr[3]);
            uptr += 4;
            vptr += 4;
            wptr += 4;
        }

        if (v_count & 0x2)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            b = _SUBTRUCT_UNIT(b, uptr[1], vptr[1], &wptr[1]);
            uptr += 2;
            vptr += 2;
            wptr += 2;
        }

        if (v_count & 0x1)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], vptr[0], &wptr[0]);
            uptr += 1;
            vptr += 1;
            wptr += 1;
        }

        u_count -= v_count;
        while (u_count > 0 && b)
        {
            b = _SUBTRUCT_UNIT(b, uptr[0], 0, &wptr[0]);
            ++uptr;
            ++wptr;
            --u_count;
        }

        if (b)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtruct;5");

        _COPY_MEMORY_UNIT(wptr, uptr, u_count);
        _ZERO_MEMORY_UNIT(w_buf + u_buf_count, w_buf_count - u_buf_count);
    }

    static void USubtructNegative(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtructNegative;2");
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtructNegative;3");
#endif
        __UNIT_TYPE* uptr = u_buf;
        __UNIT_TYPE* vptr = v_buf;
        __UNIT_TYPE u_count = u_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        __BORROW_T b = 0;

        __UNIT_TYPE count = v_count >> 5;
        while (count > 0)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, vptr[1], uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, vptr[2], uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, vptr[3], uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, vptr[4], uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, vptr[5], uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, vptr[6], uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, vptr[7], uptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, vptr[8], uptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, vptr[9], uptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, vptr[10], uptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, vptr[11], uptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, vptr[12], uptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, vptr[13], uptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, vptr[14], uptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, vptr[15], uptr[15], &uptr[15]);
            b = _SUBTRUCT_UNIT(b, vptr[16], uptr[16], &uptr[16]);
            b = _SUBTRUCT_UNIT(b, vptr[17], uptr[17], &uptr[17]);
            b = _SUBTRUCT_UNIT(b, vptr[18], uptr[18], &uptr[18]);
            b = _SUBTRUCT_UNIT(b, vptr[19], uptr[19], &uptr[19]);
            b = _SUBTRUCT_UNIT(b, vptr[20], uptr[20], &uptr[20]);
            b = _SUBTRUCT_UNIT(b, vptr[21], uptr[21], &uptr[21]);
            b = _SUBTRUCT_UNIT(b, vptr[22], uptr[22], &uptr[22]);
            b = _SUBTRUCT_UNIT(b, vptr[23], uptr[23], &uptr[23]);
            b = _SUBTRUCT_UNIT(b, vptr[24], uptr[24], &uptr[24]);
            b = _SUBTRUCT_UNIT(b, vptr[25], uptr[25], &uptr[25]);
            b = _SUBTRUCT_UNIT(b, vptr[26], uptr[26], &uptr[26]);
            b = _SUBTRUCT_UNIT(b, vptr[27], uptr[27], &uptr[27]);
            b = _SUBTRUCT_UNIT(b, vptr[28], uptr[28], &uptr[28]);
            b = _SUBTRUCT_UNIT(b, vptr[29], uptr[29], &uptr[29]);
            b = _SUBTRUCT_UNIT(b, vptr[30], uptr[30], &uptr[30]);
            b = _SUBTRUCT_UNIT(b, vptr[31], uptr[31], &uptr[31]);
            vptr += 32;
            uptr += 32;
            --count;
        }

        if (v_count & 0x10)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, vptr[1], uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, vptr[2], uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, vptr[3], uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, vptr[4], uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, vptr[5], uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, vptr[6], uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, vptr[7], uptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, vptr[8], uptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, vptr[9], uptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, vptr[10], uptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, vptr[11], uptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, vptr[12], uptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, vptr[13], uptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, vptr[14], uptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, vptr[15], uptr[15], &uptr[15]);
            vptr += 16;
            uptr += 16;
        }

        if (v_count & 0x8)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, vptr[1], uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, vptr[2], uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, vptr[3], uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, vptr[4], uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, vptr[5], uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, vptr[6], uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, vptr[7], uptr[7], &uptr[7]);
            vptr += 8;
            uptr += 8;
        }

        if (v_count & 0x4)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, vptr[1], uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, vptr[2], uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, vptr[3], uptr[3], &uptr[3]);
            vptr += 4;
            uptr += 4;
        }

        if (v_count & 0x2)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, vptr[1], uptr[1], &uptr[1]);
            vptr += 2;
            uptr += 2;
        }

        if (v_count & 0x1)
        {
            b = _SUBTRUCT_UNIT(b, vptr[0], uptr[0], &uptr[0]);
            vptr += 1;
            uptr += 1;
        }

        u_count -= v_count;
        count = u_count >> 5;
        while (count > 0)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[15], &uptr[15]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[16], &uptr[16]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[17], &uptr[17]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[18], &uptr[18]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[19], &uptr[19]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[20], &uptr[20]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[21], &uptr[21]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[22], &uptr[22]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[23], &uptr[23]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[24], &uptr[24]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[25], &uptr[25]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[26], &uptr[26]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[27], &uptr[27]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[28], &uptr[28]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[29], &uptr[29]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[30], &uptr[30]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[31], &uptr[31]);
            uptr += 32;
            --count;
        }

        if (u_count & 0x10)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[7], &uptr[7]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[8], &uptr[8]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[9], &uptr[9]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[10], &uptr[10]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[11], &uptr[11]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[12], &uptr[12]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[13], &uptr[13]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[14], &uptr[14]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[15], &uptr[15]);
            uptr += 16;
        }

        if (u_count & 0x8)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[3], &uptr[3]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[4], &uptr[4]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[5], &uptr[5]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[6], &uptr[6]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[7], &uptr[7]);
            uptr += 8;
        }

        if (u_count & 0x4)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[1], &uptr[1]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[2], &uptr[2]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[3], &uptr[3]);
            uptr += 4;
        }

        if (u_count & 0x2)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            b = _SUBTRUCT_UNIT(b, 0, uptr[1], &uptr[1]);
            uptr += 2;
        }

        if (u_count & 0x1)
        {
            b = _SUBTRUCT_UNIT(b, 0, uptr[0], &uptr[0]);
            uptr += 1;
        }

        if (b)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;USubtructNegative;4");
    }

    static SIGN_T Add(SIGN_T u_sign, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count)
    {
        if (u_sign >= 0)
        {
            Add(u_buf, u_buf_count, v_buf, v_buf_count);
            return (SIGN_POSITIVE);
        }
        else if (Compare(u_buf, ShrinkBuffer(u_buf, u_buf_count), v_buf, v_buf_count) >= 0)
        {
            USubtruct(u_buf, u_buf_count, v_buf, v_buf_count);
            return (SIGN_NEGATIVE);
        }
        else
        {
            USubtructNegative(u_buf, u_buf_count, v_buf, v_buf_count);
            return (SIGN_POSITIVE);
        }
    }

    static SIGN_T Subtruct(__UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
        if (Compare(u_buf, u_buf_count, v_buf, v_buf_count) >= 0)
        {
            USubtruct(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
            return (SIGN_POSITIVE);
        }
        else
        {
            USubtruct(v_buf, v_buf_count, u_buf, u_buf_count, w_buf, w_buf_count);
            return (SIGN_NEGATIVE);
        }
    }

    void KaratsubaMultiplicationEngine::Multiply_UX_UX_Karatsuba(__UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif
        if (!_fixed && v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC)
        {
            // 桁数が閾値より小さい場合は classic 法で計算する

            _classic_engine.Multiply_UX_UX(_UBASIC_T(u_buf, u_buf_count), _UBASIC_T(v_buf, v_buf_count), _UBASIC_T(w_buf, w_buf_count));
        }
        else if (v_buf_count == 0)
        {
            // u_buf と v_buf の少なくともどちらかが 0 の場合

            // 0 を返す
            _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
        }
        else if (u_buf_count == 1)
        {
            // u_buf と v_buf がともに 1 ワード長の場合

#ifdef _DEBUG
            if (w_buf_count != 2)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif
            w_buf[0] = _MULTIPLY_UNIT(u_buf[0], v_buf[0], &w_buf[1]);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(w_buf[0]) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }
        else
        {
            // u_buf と v_buf の少なくともどちらかが 2 ワード以上の場合

#ifdef _DEBUG
            if (w_buf_count != u_buf_count + v_buf_count)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif

            const __UNIT_TYPE n_half = _DIVIDE_CEILING_UNIT(u_buf_count, 2);
#ifdef _DEBUG
            if (n_half <= 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;2");
#endif

            const __UNIT_TYPE u_buf_lo_length = n_half;
            const __UNIT_TYPE u_buf_hi_length = u_buf_count - u_buf_lo_length;
            __UNIT_TYPE* const u_buf_lo = u_buf;
            __UNIT_TYPE* const u_buf_hi = u_buf + u_buf_lo_length;
            const __UNIT_TYPE u_buf_lo_count = ShrinkBuffer(u_buf_lo, u_buf_lo_length);
            const __UNIT_TYPE u_buf_hi_count = ShrinkBuffer(u_buf_hi, u_buf_hi_length);

            const __UNIT_TYPE v_buf_lo_length = _MINIMUM_UNIT(v_buf_count, n_half);
            const __UNIT_TYPE v_buf_hi_length = v_buf_count - v_buf_lo_length;
            __UNIT_TYPE* const v_buf_lo = v_buf;
            __UNIT_TYPE* const v_buf_hi = v_buf + v_buf_lo_length;
            const __UNIT_TYPE v_buf_lo_count = ShrinkBuffer(v_buf_lo, v_buf_lo_length);
            const __UNIT_TYPE v_buf_hi_count = ShrinkBuffer(v_buf_hi, v_buf_hi_length);

            const __UNIT_TYPE t1_buf_length = n_half;
            const __UNIT_TYPE t2_buf_length = n_half;
            const __UNIT_TYPE t3_buf_length = n_half * 2 + 1;
            __UNIT_TYPE* const t1_buf = current_temp_buf_ptr; current_temp_buf_ptr += t1_buf_length;
            __UNIT_TYPE* const t2_buf = current_temp_buf_ptr; current_temp_buf_ptr += t2_buf_length;
            __UNIT_TYPE* const t3_buf = current_temp_buf_ptr; current_temp_buf_ptr += t3_buf_length;

            const __UNIT_TYPE w_buf_lo_length = n_half * 2;
            const __UNIT_TYPE w_buf_hi_length = w_buf_count - w_buf_lo_length;
            __UNIT_TYPE* const w_buf_lo = w_buf;
            __UNIT_TYPE* const w_buf_hi = w_buf + w_buf_lo_length;

            const __UNIT_TYPE w_buf_mid_length = w_buf_count - n_half;
            __UNIT_TYPE* const w_buf_mid = w_buf + n_half;

            if (u_buf_lo_count >= v_buf_lo_count)
                Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, u_buf_lo, u_buf_lo_count, v_buf_lo, v_buf_lo_count, w_buf_lo, u_buf_lo_count + v_buf_lo_count);
            else
                Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, v_buf_lo, v_buf_lo_count, u_buf_lo, u_buf_lo_count, w_buf_lo, u_buf_lo_count + v_buf_lo_count);
            _ZERO_MEMORY_UNIT(w_buf_lo + (u_buf_lo_count + v_buf_lo_count), w_buf_lo_length - (u_buf_lo_count + v_buf_lo_count));
            const __UNIT_TYPE w_buf_lo_count = ShrinkBuffer(w_buf_lo, w_buf_lo_length);

            if (v_buf_hi_count > 0)
            {
                if (u_buf_hi_count >= v_buf_hi_count)
                    Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, u_buf_hi, u_buf_hi_count, v_buf_hi, v_buf_hi_count, w_buf_hi, u_buf_hi_count + v_buf_hi_count);
                else
                    Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, v_buf_hi, v_buf_hi_count, u_buf_hi, u_buf_hi_count, w_buf_hi, u_buf_hi_count + v_buf_hi_count);
                _ZERO_MEMORY_UNIT(w_buf_hi + (u_buf_hi_count + v_buf_hi_count), w_buf_hi_length - (u_buf_hi_count + v_buf_hi_count));
            }
            else
                _ZERO_MEMORY_UNIT(w_buf_hi, w_buf_hi_length);
            const __UNIT_TYPE w_buf_hi_count = ShrinkBuffer(w_buf_hi, w_buf_hi_length);

            SIGN_T t3_sign = SIGN_NEGATIVE;
            if (Subtruct(u_buf_hi, u_buf_hi_count, u_buf_lo, u_buf_lo_count, t1_buf, t1_buf_length) < 0)
                t3_sign = INVERT_SIGN(t3_sign);
            const __UNIT_TYPE t1_buf_count = ShrinkBuffer(t1_buf, t1_buf_length);

            if (Subtruct(v_buf_hi, v_buf_hi_count, v_buf_lo, v_buf_lo_count, t2_buf, t2_buf_length) < 0)
                t3_sign = INVERT_SIGN(t3_sign);
            const __UNIT_TYPE t2_buf_count = ShrinkBuffer(t2_buf, t2_buf_length);

            if (t1_buf_count >= t2_buf_count)
                Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, t1_buf, t1_buf_count, t2_buf, t2_buf_count, t3_buf, t1_buf_count + t2_buf_count);
            else
                Multiply_UX_UX_Karatsuba(current_temp_buf_ptr, t2_buf, t2_buf_count, t1_buf, t1_buf_count, t3_buf, t1_buf_count + t2_buf_count);
            _ZERO_MEMORY_UNIT(t3_buf + (t1_buf_count + t2_buf_count), t3_buf_length - (t1_buf_count + t2_buf_count));

            t3_sign = Add(t3_sign, t3_buf, t3_buf_length, w_buf_hi, w_buf_hi_count);

            t3_sign = Add(t3_sign, t3_buf, t3_buf_length, w_buf_lo, w_buf_lo_count);

            const __UNIT_TYPE t3_buf_count = ShrinkBuffer(t3_buf, t3_buf_length);

            if (t3_sign < 0 && t3_buf_count > 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;3");

            Add(w_buf_mid, w_buf_mid_length, t3_buf, t3_buf_count);
        }
    }

}


/*
 * END OF FILE
 */