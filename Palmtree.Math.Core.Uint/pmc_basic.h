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

#ifndef PMC_BASIC_H
#define PMC_BASIC_H

#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    class BasicOperatorEngine;
    class _BASIC_T;

    extern BasicOperatorEngine basic_ep;

    class _UBASIC_T
    {
    public:
        __UNIT_TYPE* const BLOCK;
        const __UNIT_TYPE BLOCK_COUNT;

    public:
        _UBASIC_T(__UNIT_TYPE* buf, __UNIT_TYPE buf_count)
            : BLOCK(buf), BLOCK_COUNT(buf_count)
        {
        }

        _UBASIC_T(NUMBER_OBJECT_UINT* buf)
            : BLOCK(buf->BLOCK), BLOCK_COUNT(buf->UNIT_WORD_COUNT)
        {
        }

        ~_UBASIC_T()
        {
        }

    public:
        _UBASIC_T Region(__UNIT_TYPE start)
        {
            if (start > BLOCK_COUNT)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::Region;1");
            return (_UBASIC_T(BLOCK + start, BLOCK_COUNT - start));
        }

        _UBASIC_T Region(__UNIT_TYPE start, __UNIT_TYPE count)
        {
            if (start > BLOCK_COUNT)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::Region;1");
            if (start + count > BLOCK_COUNT)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::Region;2");
            return (_UBASIC_T(BLOCK + start, count));
        }

        _UBASIC_T Shrink()
        {
            __UNIT_TYPE count = BLOCK_COUNT;
            while (count > 0 && BLOCK[count - 1] == 0)
                --count;
            return (_UBASIC_T(BLOCK, count));
        }

        _UBASIC_T Shrink1();

        void CopyFrom(_UBASIC_T buf)
        {
            if (BLOCK_COUNT < buf.BLOCK_COUNT)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::CopyFrom;1");
            _COPY_MEMORY_UNIT(BLOCK, buf.BLOCK, buf.BLOCK_COUNT);
            _ZERO_MEMORY_UNIT(BLOCK + buf.BLOCK_COUNT, BLOCK_COUNT - buf.BLOCK_COUNT);
        }

        void ReverseCopyFrom(_UBASIC_T buf)
        {
            if (BLOCK_COUNT < buf.BLOCK_COUNT)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::ReverseCopyFrom;1");
            _COPY_MEMORY_REV_UNIT(BLOCK, buf.BLOCK, buf.BLOCK_COUNT);
            _ZERO_MEMORY_UNIT(BLOCK + buf.BLOCK_COUNT, BLOCK_COUNT - buf.BLOCK_COUNT);
        }

        void Clear()
        {
            _ZERO_MEMORY_UNIT(BLOCK, BLOCK_COUNT);
        }

        void Fill(__UNIT_TYPE data)
        {
            _FILL_MEMORY_UNIT(BLOCK, data, BLOCK_COUNT);
        }

        _BASIC_T ToSigned() const;
        __UNIT_TYPE TZCount() const;
    };

    class _BASIC_T
    {
    public:
        SIGN_T SIGN;
        _UBASIC_T ABS;

    public:
        _BASIC_T(SIGN_T sign, _UBASIC_T abs);

    public:
        ~_BASIC_T();

    public:
        void Clear();
        void Negate();
    };

    class BasicOperatorEngine
    {
    public:
        BasicOperatorEngine();

        ~BasicOperatorEngine();

        // u_buf += c
        __CARRY_T Carry(__CARRY_T c, _UBASIC_T u_buf);

        // w_buf = u_buf + c;
        __CARRY_T Carry(__CARRY_T c, _UBASIC_T u_buf, _UBASIC_T w_buf);

        // u_buf += v_buf;
        __CARRY_T Add(_UBASIC_T u_buf, _UBASIC_T v_buf);

        // u_buf += v_buf;
        void Add(_BASIC_T& u_buf, _BASIC_T v_buf);

        // w_buf = u_buf + v;
        __CARRY_T Add(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf);

        // w_buf = u_buf + v;
        __CARRY_T Add(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf);

        // w_buf = u_buf + v_buf;
        __CARRY_T Add(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w_buf = u_buf + v_buf;
        void Add(_BASIC_T u_buf, _BASIC_T v_buf, _BASIC_T& w_buf);

        // u_buf -= c
        __BORROW_T Borrow(__BORROW_T c, _UBASIC_T u_buf);

        // w_buf = - u_buf - c;
        __BORROW_T Borrow(__BORROW_T c, _UBASIC_T u_buf, _UBASIC_T w_buf);

        // u_buf -= v_buf;
        void Subtruct(_BASIC_T& u_buf, _BASIC_T v_buf);

        // w_buf = u_buf - v_buf;
        void Subtruct(_BASIC_T u_buf, _BASIC_T v_buf, _BASIC_T& w_buf);

        // u_buf -= v_buf;
        void USubtruct(_UBASIC_T u_buf, _UBASIC_T v_buf);

        // w_buf = u_buf - v;
        void USubtruct(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf);

        // w_buf = u_buf - v;
        void USubtruct(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf);

        // w_buf = u - v_buf;
        void USubtruct(__UNIT_TYPE u, _UBASIC_T v_buf, __UNIT_TYPE& w);

        // w_buf = u - v_buf;
        void USubtruct(__UNIT_TYPE u_hi, __UNIT_TYPE u_lo, _UBASIC_T v_buf, __UNIT_TYPE& w_hi, __UNIT_TYPE& w_lo);

        // w_buf = u_buf - v_buf;
        void USubtruct(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // u_buf = v_buf - u_buf;
        void UNegativeSubtruct(_UBASIC_T u_buf, _UBASIC_T v_buf);

        // w_buf = u_buf * v;
        void Multiply(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf);

        // w_buf = u_buf * v;
        void Multiply(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf);

        // w_buf = u_buf * v_buf;
        void Multiply(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // q_buf = u_buf / v, r = u_buf % v;
        void DivRem(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T q_buf, __UNIT_TYPE& r);

        // q = u / v_buf, r = u % v_buf;
        void DivRem(__UNIT_TYPE u, _UBASIC_T v_buf, __UNIT_TYPE& q, __UNIT_TYPE& r);

        // q_buf = u_buf / v_buf, r_buf = u_buf % v_buf;
        void DivRem(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T work_v_buf, _UBASIC_T q_buf, _UBASIC_T r_buf);

        // q_buf = u / v_buf;
        void DivideExactly(__UNIT_TYPE u, _UBASIC_T v_buf, __UNIT_TYPE& q);

        // q_buf = u_buf / v_buf;
        void DivideExactly(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T work_u_buf, _UBASIC_T work_v_buf, _UBASIC_T q_buf);

        // u_buf /= 3;
        void DivideExactlyBy3(_BASIC_T& u_buf, _UBASIC_T work_u_buf);

        // q_buf = u_buf / 3;
        void DivideExactlyBy3(_UBASIC_T u_buf, _UBASIC_T work_u_buf, _UBASIC_T q_buf);

        // q_buf = u_buf / 3;
        void DivideExactlyBy3(_BASIC_T u_buf, _UBASIC_T work_u_buf, _BASIC_T& q_buf);

        // r = u_buf % v;
        void Remainder(_UBASIC_T u_buf, __UNIT_TYPE v, __UNIT_TYPE& r);

        // r = u % v_buf;
        void Remainder(__UNIT_TYPE u, _UBASIC_T v_buf, __UNIT_TYPE& r);

        // r_buf = u_buf % v_buf;
        void Remainder(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T work_v_buf, _UBASIC_T r_buf);

        // w_buf = GCD(u_buf, v_buf)
        void GreatestCommonDivisor(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T work_u_buf, _UBASIC_T work_v_buf, _UBASIC_T w_buf);

        // returns u_buf == v;
        bool Equals(_UBASIC_T u_buf, __UNIT_TYPE v);

        // returns u_buf == v;
        bool Equals(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo);

        // returns u_buf == v_buf;
        bool Equals(_UBASIC_T u_buf, _UBASIC_T v_buf);

        // returns u_buf > v ? 1 : u_buf < v ? -1 : 0;
        SIGN_T Compare(_UBASIC_T u_buf, __UNIT_TYPE v);

        // returns u_buf > v ? 1 : u_buf < v ? -1 : 0;
        SIGN_T Compare(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo);

        // returns u_buf > v_buf ? 1 : u_buf < v_buf ? -1 : 0;
        SIGN_T Compare(_UBASIC_T u_buf, _UBASIC_T v_buf);

        // w = u_buf & v;
        void BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v, __UNIT_TYPE& w);

        // w = u_buf & v;
        void BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE& w_hi, __UNIT_TYPE& w_lo);

        // w_buf = u_buf & v_buf;
        void BitwiseAnd(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w_buf = u_buf | v;
        void BitwiseOr(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf);

        // w_buf = u_buf | v;
        void BitwiseOr(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf);

        // w_buf = u_buf | v_buf;
        void BitwiseOr(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w_buf = u_buf ^ v;
        void ExclusiveOr(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf);

        // w_buf = u_buf ^ v;
        void ExclusiveOr(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf);

        // w_buf = u_buf ^ v_buf;
        void ExclusiveOr(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w_buf = ~u & v_buf;
        void OneCompliment_And_BitwiseAnd(__UNIT_TYPE u, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w_buf = ~u & v_buf;
        void OneCompliment_And_BitwiseAnd(__UNIT_TYPE u_hi, __UNIT_TYPE u_lo, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // w = ~u_buf & v;
        void OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v, __UNIT_TYPE& w);

        // w = ~u_buf & v;
        void OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE& w_hi, __UNIT_TYPE& w_lo);

        // w_buf = ~u_buf & v_buf;
        void OneCompliment_And_BitwiseAnd(_UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf);

        // u_buf >>= n;
        void RightShift(_UBASIC_T inout_buf, __UNIT_TYPE n);

        // u_buf >>= n;
        void RightShift(_BASIC_T& inout_buf, __UNIT_TYPE n);

        // r_buf = u_buf >> n;
        void RightShift(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T out_buf);

        // r_buf = u_buf >> n;
        void RightShift(_BASIC_T in_buf, __UNIT_TYPE n, _BASIC_T& out_buf);

        // u_buf <<= n;
        void LeftShift(_UBASIC_T inout_buf, __UNIT_TYPE n);

        // u_buf <<= n;
        void LeftShift(_BASIC_T& inout_buf, __UNIT_TYPE n);

        // r_buf = u_buf << n;
        void LeftShift(_UBASIC_T in_buf, __UNIT_TYPE n, _UBASIC_T out_buf);

        // r_buf = u_buf << n;
        void LeftShift(_BASIC_T in_buf, __UNIT_TYPE n, _BASIC_T& out_buf);
    };

}

#endif

/*
 * END OF FILE
 */