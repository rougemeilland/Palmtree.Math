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

#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{
    BasicOperatorEngine basic_ep;

    _UBASIC_T _UBASIC_T::Shrink1()
    {
        if (BLOCK[BLOCK_COUNT - 1] != 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;_UBASIC_T::Shrink1;1");
        __UNIT_TYPE count = BLOCK_COUNT;
        while (count > 1 && BLOCK[count - 2] == 0)
            --count;
        return (_UBASIC_T(BLOCK, count));
    }

    _BASIC_T _UBASIC_T::ToSigned() const
    {
        return (_BASIC_T(SIGN_POSITIVE, *this));
    }

    __UNIT_TYPE _UBASIC_T::TZCount() const
    {
        __UNIT_TYPE* ptr = BLOCK;
        __UNIT_TYPE count = BLOCK_COUNT;
        int tz_count = 0;
        while (count > 0)
        {
            if (*ptr != 0)
                return (tz_count + _TZCNT_ALT_UNIT(*ptr));
            tz_count += __UNIT_TYPE_BIT_COUNT;
            ++ptr;
            --count;
        }
        return (0);
    }

    _BASIC_T::_BASIC_T(SIGN_T sign, _UBASIC_T abs)
        :  SIGN(sign), ABS(abs)
    {
    }

    _BASIC_T::~_BASIC_T()
    {
    }

    void _BASIC_T::Clear()
    {
        SIGN = SIGN_ZERO;
        ABS.Clear();
    }

    void _BASIC_T::Negate()
    {
        SIGN = INVERT_SIGN(SIGN);
    }

    BasicOperatorEngine::BasicOperatorEngine()
    {
    }

    BasicOperatorEngine::~BasicOperatorEngine()
    {
    }

    void BasicOperatorEngine::Add(_BASIC_T & u_buf, _BASIC_T v_buf)
    {
        if (u_buf.SIGN == 0)
        {
            u_buf.ABS.CopyFrom(v_buf.ABS);
            u_buf.SIGN = v_buf.SIGN;
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.ABS, v_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Add;1");
            }
            else
            {
                SIGN_T c = Compare(u_buf.ABS.Shrink(), v_buf.ABS);
                if (c == 0)
                    u_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    UNegativeSubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_NEGATIVE;
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
                SIGN_T c = Compare(v_buf.ABS, u_buf.ABS.Shrink());
                if (c == 0)
                    u_buf.Clear();
                else if (c > 0)
                {
                    UNegativeSubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_NEGATIVE;
                }
            }
            else
            {
                if (Add(u_buf.ABS, v_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Add;2");
            }
        }
    }

    void BasicOperatorEngine::Add(_BASIC_T u_buf, _BASIC_T v_buf, _BASIC_T& w_buf)
    {
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
                w_buf.Clear();
            else
            {
                w_buf.ABS.CopyFrom(v_buf.ABS);
                w_buf.SIGN = v_buf.SIGN;
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN >= 0)
            {
                if (Add(u_buf.ABS, v_buf.ABS, w_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Add;1");
                w_buf.SIGN = SIGN_POSITIVE;
            }
            else
            {
                SIGN_T c = Compare(u_buf.ABS, v_buf.ABS);
                if (c == 0)
                    w_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(u_buf.ABS, v_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(v_buf.ABS, u_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_NEGATIVE;
                }
            }
        }
        else
        {
            if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(v_buf.ABS, u_buf.ABS);
                if (c == 0)
                    w_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(v_buf.ABS, u_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(u_buf.ABS, v_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_NEGATIVE;
                }
            }
            else
            {
                if (Add(u_buf.ABS, v_buf.ABS, w_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Add;2");
                w_buf.SIGN = SIGN_NEGATIVE;
            }
        }
    }

    void BasicOperatorEngine::Subtruct(_BASIC_T & u_buf, _BASIC_T v_buf)
    {
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
            {
                // nop
            }
            else
            {
                u_buf.ABS.CopyFrom(v_buf.ABS);
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
                SIGN_T c = Compare(u_buf.ABS, v_buf.ABS);
                if (c == 0)
                    u_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    UNegativeSubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_NEGATIVE;
                }
            }
            else
            {
                if (Add(u_buf.ABS, v_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Subtruct;1");
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
                if (Add(u_buf.ABS, v_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Subtruct;2");
            }
            else
            {
                SIGN_T c = Compare(v_buf.ABS, u_buf.ABS);
                if (c == 0)
                    u_buf.Clear();
                else if (c > 0)
                {
                    UNegativeSubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(u_buf.ABS, v_buf.ABS);
                    u_buf.SIGN = SIGN_NEGATIVE;
                }
            }
        }
    }

    void BasicOperatorEngine::Subtruct(_BASIC_T u_buf, _BASIC_T v_buf, _BASIC_T& w_buf)
    {
        if (u_buf.SIGN == 0)
        {
            if (v_buf.SIGN == 0)
                w_buf.Clear();
            else if (v_buf.SIGN > 0)
            {
                w_buf.ABS.CopyFrom(v_buf.ABS);
                w_buf.SIGN = SIGN_NEGATIVE;
            }
            else
            {
                w_buf.ABS.CopyFrom(v_buf.ABS);
                w_buf.SIGN = SIGN_POSITIVE;
            }
        }
        else if (u_buf.SIGN > 0)
        {
            if (v_buf.SIGN == 0)
            {
                w_buf.ABS.CopyFrom(u_buf.ABS);
                w_buf.SIGN = SIGN_POSITIVE;
            }
            else if (v_buf.SIGN > 0)
            {
                SIGN_T c = Compare(u_buf.ABS, v_buf.ABS);
                if (c == 0)
                    w_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(u_buf.ABS, v_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(v_buf.ABS, u_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_NEGATIVE;
                }
            }
            else
            {
                if (Add(u_buf.ABS, v_buf.ABS, w_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Subtruct;1");
                w_buf.SIGN = SIGN_POSITIVE;
            }
        }
        else
        {
            if (v_buf.SIGN == 0)
            {
                w_buf.ABS.CopyFrom(u_buf.ABS);
                w_buf.SIGN = SIGN_POSITIVE;
            }
            else if (v_buf.SIGN > 0)
            {
                if (Add(u_buf.ABS, v_buf.ABS, w_buf.ABS))
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic.cpp;BasicOperatorEngine::Subtruct;2");
                w_buf.SIGN = SIGN_NEGATIVE;
            }
            else
            {
                SIGN_T c = Compare(v_buf.ABS, u_buf.ABS);
                if (c == 0)
                    w_buf.Clear();
                else if (c > 0)
                {
                    USubtruct(v_buf.ABS, u_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_POSITIVE;
                }
                else
                {
                    USubtruct(u_buf.ABS, v_buf.ABS, w_buf.ABS);
                    w_buf.SIGN = SIGN_NEGATIVE;
                }
            }
        }
    }

    void BasicOperatorEngine::DivideExactlyBy3(_BASIC_T u_buf, _UBASIC_T work_u_buf, _BASIC_T & q_buf)
    {
        DivideExactlyBy3(u_buf.ABS, work_u_buf, q_buf.ABS);
        q_buf.SIGN = SIGN_POSITIVE;
    }

    void BasicOperatorEngine::RightShift(_BASIC_T & inout_buf, __UNIT_TYPE n)
    {
        RightShift(inout_buf.ABS, n);
    }

    void BasicOperatorEngine::RightShift(_BASIC_T in_buf, __UNIT_TYPE n, _BASIC_T & out_buf)
    {
        RightShift(in_buf.ABS, n, out_buf.ABS);
        out_buf.SIGN = in_buf.SIGN;
    }

    void BasicOperatorEngine::LeftShift(_BASIC_T & inout_buf, __UNIT_TYPE n)
    {
        LeftShift(inout_buf.ABS, n);
    }

    void BasicOperatorEngine::LeftShift(_BASIC_T in_buf, __UNIT_TYPE n, _BASIC_T & out_buf)
    {
        LeftShift(in_buf.ABS, n, out_buf.ABS);
        out_buf.SIGN = in_buf.SIGN;
    }

}


/*
 * END OF FILE
 */