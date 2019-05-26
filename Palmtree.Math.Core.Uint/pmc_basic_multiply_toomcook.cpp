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

#include "pmc_multiply_toomcook.h"
#include "pmc_multiply_karatsuba.h"
#include "pmc_multiply_classic.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_exception.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

#ifdef _M_IX86
#define WORD_COUNT_THRESHOLD_KARATSUBA  (0xffffffffU)           // u_buf と v_buf のどちらかのワード長がこの値未満ならば karatsuba 法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x80000000U)           // 現実的に利用可能なユーザメモリの最大サイズ
#elif defined(_M_X64)
#define WORD_COUNT_THRESHOLD_KARATSUBA  (0xffffffffffffffffUL)  // u_buf と v_buf のどちらかのワード長がこの値未満ならば karatsuba 法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x8000000000000000UL)  // 現実的に利用可能なユーザメモリの最大サイズ
#else
#error unknown platform
#endif

namespace Palmtree::Math::Core::Internal::Multiply::ToomCook
{

    using namespace Palmtree::Math::Core::Internal::Basic;

    static bool CalculateTempBufferSize(__UNIT_TYPE u_buf_count, __UNIT_TYPE v_buf_count, __UNIT_TYPE & buffer_size)
    {
        buffer_size = 0;
        return (true);
    }

    static void Multiply_UX_UX_ToomCook(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif
        if (!fixed && v_buf_count < WORD_COUNT_THRESHOLD_KARATSUBA)
        {
            // 桁数が閾値より小さい場合は karatsuba 法で計算する

            Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        }
        else if (v_buf_count == 0)
        {
            // u_buf と v_buf の少なくともどちらかが 0 の場合

            // 0 を返す
            _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
        }
        else if (u_buf_count <= 4)
        {
            // u_buf と v_buf がともに 4 ワード以下の場合

            Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        }
        else
        {
            // u_buf と v_buf の少なくともどちらかが 5 ワード以上の場合

#ifdef _DEBUG
            if (w_buf_count != u_buf_count + v_buf_count)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif

            const __UNIT_TYPE n_one_third = _DIVIDE_CEILING_UNIT(u_buf_count, 3);
#ifdef _DEBUG
            if (n_one_third <= 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;2");
#endif

            const __UNIT_TYPE u_buf_lo_length = n_one_third;
            const __UNIT_TYPE u_buf_mi_length = n_one_third;
            const __UNIT_TYPE u_buf_hi_length = u_buf_count - (u_buf_lo_length + u_buf_mi_length);
            __UNIT_TYPE* const u_buf_lo = u_buf;
            __UNIT_TYPE* const u_buf_mi = u_buf_lo + u_buf_lo_length;
            __UNIT_TYPE* const u_buf_hi = u_buf_mi + u_buf_mi_length;
            const __UNIT_TYPE u_buf_lo_count = __Shrink(u_buf_lo, u_buf_lo_length);
            const __UNIT_TYPE u_buf_mi_count = __Shrink(u_buf_mi, u_buf_mi_length);
            const __UNIT_TYPE u_buf_hi_count = __Shrink(u_buf_hi, u_buf_hi_length);

            const __UNIT_TYPE v_buf_lo_length = _MINIMUM_UNIT(v_buf_count, n_one_third);
            const __UNIT_TYPE v_buf_mi_length = _MINIMUM_UNIT(v_buf_count - v_buf_lo_length, n_one_third);
            const __UNIT_TYPE v_buf_hi_length = v_buf_count - (v_buf_lo_length + v_buf_mi_length);
            __UNIT_TYPE* const v_buf_lo = v_buf;
            __UNIT_TYPE* const v_buf_mi = v_buf_lo + v_buf_lo_length;
            __UNIT_TYPE* const v_buf_hi = v_buf_mi + v_buf_mi_length;
            const __UNIT_TYPE v_buf_lo_count = __Shrink(v_buf_lo, v_buf_lo_length);
            const __UNIT_TYPE v_buf_mi_count = __Shrink(v_buf_mi, v_buf_mi_length);
            const __UNIT_TYPE v_buf_hi_count = __Shrink(v_buf_hi, v_buf_hi_length);

            throw InternalErrorException(L"", L"");
#if false




            const __UNIT_TYPE t1_buf_length = n_one_third;
            const __UNIT_TYPE t2_buf_length = n_one_third;
            const __UNIT_TYPE t3_buf_length = n_one_third * 2 + 1;
            __UNIT_TYPE* const t1_buf = current_temp_buf_ptr; current_temp_buf_ptr += t1_buf_length;
            __UNIT_TYPE* const t2_buf = current_temp_buf_ptr; current_temp_buf_ptr += t2_buf_length;
            __UNIT_TYPE* const t3_buf = current_temp_buf_ptr; current_temp_buf_ptr += t3_buf_length;




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

#endif
        }
    }

    void Multiply_UX_UX(ThreadContext & tc, bool fixed, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
        if (u_buf_count <= 4 && v_buf_count <= 4)
        {
            // u_buf と v_buf がどちらも 4 ワード以下になると配列を 3 分割できないことがあるため、その場合は _fixed フラグの値にかかわらず Karatsuba に移行する
            Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        }
        else if (!fixed && (u_buf_count < WORD_COUNT_THRESHOLD_KARATSUBA || v_buf_count < WORD_COUNT_THRESHOLD_KARATSUBA))
            Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        else
        {
            __UNIT_TYPE temp_buffer_count;
            if (CalculateTempBufferSize(u_buf_count, v_buf_count, temp_buffer_count) || temp_buffer_count > MAX_USER_MEMORY_SIZE / __UNIT_TYPE_BYTE_COUNT)
            {
                // Karatsuba 法に必要な一時メモリ領域のサイズが __UNIT_TYPE (==size_t) で表現できる範囲を超えた場合、
                // 仕方がないので代わりに古典的算法を実行する
                Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
            }
            else
            {
                ResourceHolderUINT root(tc);

                __UNIT_TYPE* temp_buf = root.AllocateBlock(temp_buffer_count);
                if (u_buf_count >= v_buf_count)
                    Multiply_UX_UX_ToomCook(tc, fixed, temp_buf, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
                else
                    Multiply_UX_UX_ToomCook(tc, fixed, temp_buf, v_buf, v_buf_count, u_buf, u_buf_count, w_buf, w_buf_count);
            }
        }
    }

}


/*
 * END OF FILE
 */