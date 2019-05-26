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

#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_multiply_classic.h"
#include "pmc_multiply_karatsuba.h"
#include "pmc_multiply_toomcook.h"
#include "pmc_multiply_schonHagestrassen.h"

namespace Palmtree::Math::Core::Internal
{

    namespace Basic
    {

        // w_buf = u_buf * v;
        void Multiply(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE v, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count)
        {
#ifdef _DEBUG
            if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;Multiply;1");
#endif
            if (v == 0)
                _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
            else if (u_buf_count == 0)
                _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
            else
                Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_1W(u_buf, u_buf_count, v, w_buf, w_buf_count);
        }


        // w_buf = u_buf * v;
        void Multiply(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count)
        {
#ifdef _DEBUG
            if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;Multiply;1");
#endif
            if (v_hi == 0)
                Multiply(u_buf, u_buf_count, v_lo, w_buf, w_buf_count);
            else if (u_buf_count == 0)
                _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
            else
                Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_2W(u_buf, u_buf_count, v_hi, v_lo, w_buf, w_buf_count);
        }


        // w_buf = u_buf * v_buf;
        void Multiply(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, __UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count)
        {
#ifdef _DEBUG
            if (u_buf_count > 0 && u_buf[u_buf_count - 1] == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;Multiply;1");
            if (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;Multiply;2");
#endif
            if (u_buf_count == 0)
                _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
            else if (v_buf_count == 0)
                _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
            else
            {
                switch (method)
                {
                case PMC_MULTIPLICATION_METHOD_AUTO:
                    return (Palmtree::Math::Core::Internal::Multiply::SchonHageStrassen::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count));
                case PMC_MULTIPLICATION_METHOD_CLASSIC:
                    return (Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count));
                case PMC_MULTIPLICATION_METHOD_KARATSUBA:
                    return (Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, true, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count));
                case PMC_MULTIPLICATION_METHOD_TOOMCOOK:
                    return (Palmtree::Math::Core::Internal::Multiply::ToomCook::Multiply_UX_UX(tc, true, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count));
                case PMC_MULTIPLICATION_METHOD_SCHONSTRASSEN:
                    return (Palmtree::Math::Core::Internal::Multiply::SchonHageStrassen::Multiply_UX_UX(tc, true, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count));
                default:
                    throw ArgumentException(L"methodが不正です。");
                }
            }
        }

    }

    PMC_STATUS_CODE Initialize_BasicMultiply(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */