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

#ifndef PMC_SIGNEDUNITARRAY_H
#define PMC_SIGNEDUNITARRAY_H

#include "pmc_basic.h"

namespace Palmtree::Math::Core::Internal::Basic
{

    class SIGNED_UNIT_ARRAY
    {
    public:
        SIGN_T SIGN;
        __UNIT_TYPE* const BLOCK;
        const __UNIT_TYPE BLOCK_COUNT;
        __UNIT_TYPE WORD_COUNT;
    public:
        SIGNED_UNIT_ARRAY(__UNIT_TYPE* buf, __UNIT_TYPE buf_count)
            : SIGN(buf_count > 0 ? SIGN_POSITIVE : SIGN_ZERO), BLOCK(buf), BLOCK_COUNT(buf_count), WORD_COUNT(buf_count)
        {
        }

        SIGNED_UNIT_ARRAY(SIGN_T sign, __UNIT_TYPE* buf, __UNIT_TYPE buf_count)
            : SIGN(sign), BLOCK(buf), BLOCK_COUNT(buf_count), WORD_COUNT(buf_count)
        {
        }

    private :
        // コピーコンストラクタは呼び出し禁止
        SIGNED_UNIT_ARRAY(const SIGNED_UNIT_ARRAY& p);

    public:
        ~SIGNED_UNIT_ARRAY()
        {
        }

    public:
        void Shrink()
        {
            WORD_COUNT = __Shrink(BLOCK, WORD_COUNT);
            if (WORD_COUNT == 0)
                SIGN = SIGN_ZERO;
        }

        void Negate()
        {
            SIGN = INVERT_SIGN(SIGN);
        }

    private:
        // 代入演算子は呼び出し禁止
        SIGNED_UNIT_ARRAY& operator = (const SIGNED_UNIT_ARRAY& p);
    };

    // u_buf += v_buf;
    __inline static void Add(SIGNED_UNIT_ARRAY& u_buf, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;1");
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;2");
#endif
        if (u_buf.SIGN == 0)
        {
            if (v_buf_count == 0)
            {
                // nop
            }
            else
            {
                _COPY_MEMORY_UNIT(u_buf.BLOCK, v_buf, v_buf_count);
                u_buf.WORD_COUNT = v_buf_count;
                u_buf.SIGN = SIGN_POSITIVE;
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf_count == 0)
            {
                // nop
            }
            else
            {
                if (Add(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf, v_buf_count))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;3");
                u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                u_buf.Shrink();
            }
        }
        else
        {
            if (v_buf_count == 0)
            {
                // nop
            }
            else
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf, v_buf_count);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(u_buf.BLOCK, u_buf.BLOCK_COUNT);
                    u_buf.WORD_COUNT = 0;
                    u_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf, v_buf_count);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.Shrink();
                }
                else
                {
                    UNegativeSubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf, v_buf_count);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.SIGN = SIGN_POSITIVE;
                    u_buf.Shrink();
                }
            }
        }
    }

    // u_buf += v_buf;
    __inline static void Add(SIGNED_UNIT_ARRAY& u_buf, SIGNED_UNIT_ARRAY& v_buf)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;1");
        if (v_buf.WORD_COUNT > 0 && v_buf.BLOCK[v_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;2");
#endif
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else
            {
                _COPY_MEMORY_UNIT(u_buf.BLOCK, v_buf.BLOCK, v_buf.WORD_COUNT);
                u_buf.WORD_COUNT = v_buf.WORD_COUNT;
                u_buf.SIGN = v_buf.SIGN;
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;3");
                u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                u_buf.Shrink();
            }
            else
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(u_buf.BLOCK, u_buf.BLOCK_COUNT);
                    u_buf.WORD_COUNT = 0;
                    u_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.Shrink();
                }
                else
                {
                    UNegativeSubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.SIGN = SIGN_NEGATIVE;
                    u_buf.Shrink();
                }
            }
        }
        else
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(u_buf.BLOCK, u_buf.BLOCK_COUNT);
                    u_buf.WORD_COUNT = 0;
                    u_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.Shrink();
                }
                else
                {
                    UNegativeSubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.SIGN = SIGN_POSITIVE;
                    u_buf.Shrink();
                }
            }
            else
            {
                if (Add(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;4");
                u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                u_buf.Shrink();
            }
        }
    }

    // w_buf = u_buf + v_buf;
    __inline static void Add(SIGNED_UNIT_ARRAY& u_buf, SIGNED_UNIT_ARRAY& v_buf, SIGNED_UNIT_ARRAY& w_buf)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;1");
        if (v_buf.WORD_COUNT > 0 && v_buf.BLOCK[v_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;2");
#endif
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
            {
                _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                w_buf.WORD_COUNT = 0;
                w_buf.SIGN = SIGN_ZERO;
            }
            else
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, v_buf.BLOCK, v_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + v_buf.WORD_COUNT, w_buf.BLOCK_COUNT - v_buf.WORD_COUNT);
                w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                w_buf.SIGN = v_buf.SIGN;
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, u_buf.BLOCK, u_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + u_buf.WORD_COUNT, w_buf.BLOCK_COUNT - u_buf.WORD_COUNT);
                w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                w_buf.SIGN = u_buf.SIGN;
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;3");
                w_buf.WORD_COUNT = w_buf.BLOCK_COUNT;
                w_buf.SIGN = SIGN_POSITIVE;
                w_buf.Shrink();
            }
            else
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = 0;
                    w_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_POSITIVE;
                    w_buf.Shrink();
                }
                else
                {
                    USubtruct(v_buf.BLOCK, v_buf.WORD_COUNT, u_buf.BLOCK, u_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_NEGATIVE;
                    w_buf.Shrink();
                }
            }
        }
        else
        {
            if (v_buf.SIGN == 0)
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, u_buf.BLOCK, u_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + u_buf.WORD_COUNT, w_buf.BLOCK_COUNT - u_buf.WORD_COUNT);
                w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                w_buf.SIGN = u_buf.SIGN;
            }
            else if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = 0;
                    w_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_NEGATIVE;
                    w_buf.Shrink();
                }
                else
                {
                    USubtruct(v_buf.BLOCK, v_buf.WORD_COUNT, u_buf.BLOCK, u_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_POSITIVE;
                    w_buf.Shrink();
                }
            }
            else
            {
                if (Add(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Add;4");
                w_buf.WORD_COUNT = w_buf.BLOCK_COUNT;
                w_buf.SIGN = SIGN_NEGATIVE;
                w_buf.Shrink();
            }
        }
    }

    // u_buf -= v_buf;
    __inline static void Subtruct(SIGNED_UNIT_ARRAY& u_buf, SIGNED_UNIT_ARRAY& v_buf)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;1");
        if (v_buf.WORD_COUNT > 0 && v_buf.BLOCK[v_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;2");
#endif
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else
            {
                _COPY_MEMORY_UNIT(u_buf.BLOCK, v_buf.BLOCK, v_buf.WORD_COUNT);
                u_buf.WORD_COUNT = v_buf.WORD_COUNT;
                u_buf.SIGN = INVERT_SIGN(v_buf.SIGN);
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    u_buf.WORD_COUNT = 0;
                    u_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.Shrink();
                }
                else
                {
                    UNegativeSubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.SIGN = SIGN_NEGATIVE;
                    u_buf.Shrink();
                }
            }
            else
            {
                if (Add(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;3");
                u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                u_buf.Shrink();
            }
        }
        else
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;4");
                u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                u_buf.Shrink();
            }
            else
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    u_buf.WORD_COUNT = 0;
                    u_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    UNegativeSubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.SIGN = SIGN_POSITIVE;
                    u_buf.Shrink();
                }
                else
                {
                    USubtruct(u_buf.BLOCK, u_buf.BLOCK_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                    u_buf.WORD_COUNT = u_buf.BLOCK_COUNT;
                    u_buf.Shrink();
                }
            }
        }
    }

    // w_buf = u_buf - v_buf;
    __inline static void Subtruct(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, SIGNED_UNIT_ARRAY& w_buf)
    {
#ifdef _DEBUG
        if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;1");
        if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;2");
#endif
        if (u_buf_count == 0)
        {
            if (v_buf_count == 0)
            {
                _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                w_buf.WORD_COUNT = 0;
                w_buf.SIGN = SIGN_ZERO;
            }
            else
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, v_buf, v_buf_count);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + v_buf_count, w_buf.BLOCK_COUNT - v_buf_count);
                w_buf.WORD_COUNT = v_buf_count;
                w_buf.SIGN = SIGN_NEGATIVE;
            }
        }
        else
        {
            if (v_buf_count == 0)
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, u_buf, u_buf_count);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + u_buf_count, w_buf.BLOCK_COUNT - u_buf_count);
                w_buf.WORD_COUNT = u_buf_count;
                w_buf.SIGN = SIGN_POSITIVE;
            }
            else
            {
                SIGN_T c = Compare(u_buf, u_buf_count, v_buf, v_buf_count);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = 0;
                    w_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf, u_buf_count, v_buf, v_buf_count, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = u_buf_count;
                    w_buf.SIGN = SIGN_POSITIVE;
                    w_buf.Shrink();
                }
                else
                {
                    USubtruct(v_buf, v_buf_count, u_buf, u_buf_count, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = v_buf_count;
                    w_buf.SIGN = SIGN_NEGATIVE;
                    w_buf.Shrink();
                }
            }
        }
    }

    // w_buf = u_buf - v_buf;
    __inline static void Subtruct(SIGNED_UNIT_ARRAY& u_buf, SIGNED_UNIT_ARRAY& v_buf, SIGNED_UNIT_ARRAY& w_buf)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;1");
        if (v_buf.WORD_COUNT > 0 && v_buf.BLOCK[v_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;2");
#endif
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
            {
                _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                w_buf.WORD_COUNT = 0;
                w_buf.SIGN = SIGN_ZERO;
            }
            else
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, v_buf.BLOCK, v_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + v_buf.WORD_COUNT, w_buf.BLOCK_COUNT - v_buf.WORD_COUNT);
                w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                w_buf.SIGN = INVERT_SIGN(v_buf.SIGN);
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, u_buf.BLOCK, u_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + u_buf.WORD_COUNT, w_buf.BLOCK_COUNT - u_buf.WORD_COUNT);
                w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                w_buf.SIGN = u_buf.SIGN;
            }
            else if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = 0;
                    w_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_POSITIVE;
                    w_buf.Shrink();
                }
                else
                {
                    USubtruct(v_buf.BLOCK, v_buf.WORD_COUNT, u_buf.BLOCK, u_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_NEGATIVE;
                    w_buf.Shrink();
                }
            }
            else
            {
                if (Add(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;3");
                w_buf.WORD_COUNT = w_buf.BLOCK_COUNT;
                w_buf.SIGN = SIGN_POSITIVE;
                w_buf.Shrink();
            }
        }
        else
        {
            if (v_buf.SIGN == 0)
            {
                _COPY_MEMORY_UNIT(w_buf.BLOCK, u_buf.BLOCK, u_buf.WORD_COUNT);
                _ZERO_MEMORY_UNIT(w_buf.BLOCK + u_buf.WORD_COUNT, w_buf.BLOCK_COUNT - u_buf.WORD_COUNT);
                w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                w_buf.SIGN = u_buf.SIGN;
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;Subtruct;4");
                w_buf.WORD_COUNT = w_buf.BLOCK_COUNT;
                w_buf.SIGN = SIGN_NEGATIVE;
                w_buf.Shrink();
            }
            else
            {
                SIGN_T c = Compare(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT);
                if (c == 0)
                {
                    _ZERO_MEMORY_UNIT(w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = 0;
                    w_buf.SIGN = SIGN_ZERO;
                }
                else if (c > 0)
                {
                    USubtruct(u_buf.BLOCK, u_buf.WORD_COUNT, v_buf.BLOCK, v_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = u_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_NEGATIVE;
                    w_buf.Shrink();
                }
                else
                {
                    USubtruct(v_buf.BLOCK, v_buf.WORD_COUNT, u_buf.BLOCK, u_buf.WORD_COUNT, w_buf.BLOCK, w_buf.BLOCK_COUNT);
                    w_buf.WORD_COUNT = v_buf.WORD_COUNT;
                    w_buf.SIGN = SIGN_POSITIVE;
                    w_buf.Shrink();
                }
            }
        }
    }

    // u_buf /= 3;
    __inline static void DivideExactlyBy3(SIGNED_UNIT_ARRAY& u_buf, __UNIT_TYPE* work_u_buf, __UNIT_TYPE work_u_buf_count)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;DivideExactlyBy3;1");
#endif
        DivideExactlyBy3(u_buf.BLOCK, u_buf.WORD_COUNT, work_u_buf, work_u_buf_count, u_buf.BLOCK, u_buf.BLOCK_COUNT);
        u_buf.Shrink();
    }

    // q_buf = u_buf / 3;
    __inline static void DivideExactlyBy3(SIGNED_UNIT_ARRAY& u_buf, __UNIT_TYPE* work_u_buf, __UNIT_TYPE work_u_buf_count, SIGNED_UNIT_ARRAY& q_buf)
    {
#ifdef _DEBUG
        if (u_buf.WORD_COUNT > 0 && u_buf.BLOCK[u_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;DivideExactlyBy3;1");
#endif
        DivideExactlyBy3(u_buf.BLOCK, u_buf.WORD_COUNT, work_u_buf, work_u_buf_count, q_buf.BLOCK, q_buf.BLOCK_COUNT);
        q_buf.WORD_COUNT = u_buf.WORD_COUNT;
        q_buf.SIGN = u_buf.SIGN;
        q_buf.Shrink();
    }

    // u_buf >>= n;
    __inline static void RightShift(SIGNED_UNIT_ARRAY& inout_buf, __UNIT_TYPE n)
    {
#ifdef _DEBUG
        if (inout_buf.WORD_COUNT > 0 && inout_buf.BLOCK[inout_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;RightShift;1");
#endif
        RightShift(inout_buf.BLOCK, inout_buf.WORD_COUNT, n);
        inout_buf.Shrink();
    }

    // r_buf = u_buf >> n;
    __inline static void RightShift(SIGNED_UNIT_ARRAY& in_buf, __UNIT_TYPE n, SIGNED_UNIT_ARRAY& out_buf)
    {
#ifdef _DEBUG
        if (in_buf.WORD_COUNT > 0 && in_buf.BLOCK[in_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;RightShift;1");
#endif
        RightShift(in_buf.BLOCK, in_buf.WORD_COUNT, n, out_buf.BLOCK, out_buf.BLOCK_COUNT);
        __UNIT_TYPE n_word = n / __UNIT_TYPE_BIT_COUNT;
        out_buf.WORD_COUNT = in_buf.WORD_COUNT >= n_word ? in_buf.WORD_COUNT - n_word : 0;
        out_buf.SIGN = in_buf.SIGN;
        out_buf.Shrink();
    }

    // u_buf <<= n;
    __inline static void LeftShift(SIGNED_UNIT_ARRAY& inout_buf, __UNIT_TYPE n)
    {
#ifdef _DEBUG
        if (inout_buf.WORD_COUNT > 0 && inout_buf.BLOCK[inout_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;RightShift;1");
#endif
        LeftShift(inout_buf.BLOCK, inout_buf.BLOCK_COUNT, n);
        inout_buf.WORD_COUNT = inout_buf.BLOCK_COUNT;
        inout_buf.Shrink();
    }

    // r_buf = u_buf << n;
    __inline static void LeftShift(SIGNED_UNIT_ARRAY& in_buf, __UNIT_TYPE n, SIGNED_UNIT_ARRAY& out_buf)
    {
#ifdef _DEBUG
        if (in_buf.WORD_COUNT > 0 && in_buf.BLOCK[in_buf.WORD_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_signedunitarray.h;RightShift;1");
#endif
        LeftShift(in_buf.BLOCK, in_buf.WORD_COUNT, n, out_buf.BLOCK, out_buf.BLOCK_COUNT);
        __UNIT_TYPE n_word = _DIVIDE_CEILING_UNIT(n, __UNIT_TYPE_BIT_COUNT);
        out_buf.WORD_COUNT = _MINIMUM_UNIT(in_buf.WORD_COUNT + n_word, out_buf.BLOCK_COUNT);
        out_buf.SIGN = in_buf.SIGN;
        out_buf.Shrink();
    }

}

#endif

/*
 * END OF FILE
 */