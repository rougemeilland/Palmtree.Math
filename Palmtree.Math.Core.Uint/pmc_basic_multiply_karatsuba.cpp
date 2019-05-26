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
#include "pmc_multiply_karatsuba.h"
#include "pmc_multiply_classic.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_exception.h"
#include "pmc_basic.h"
#include "pmc_signedunitarray.h"
#include "pmc_inline_func.h"

#ifdef _M_IX86
#define WORD_COUNT_THRESHOLD_CLASSIC    (32768U)                // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x80000000U)           // 現実的に利用可能なユーザメモリの最大サイズ
#elif defined(_M_X64)
#define WORD_COUNT_THRESHOLD_CLASSIC    (32768U)                // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x8000000000000000UL)  // 現実的に利用可能なユーザメモリの最大サイズ
#else
#error unknown platform
#endif

namespace Palmtree::Math::Core::Internal::Multiply::Karatsuba
{

    using namespace Palmtree::Math::Core::Internal::Basic;

    static void Multiply_UX_UX_Karatsuba(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count);

    static bool CalculateTempBufferSize(bool fixed, __UNIT_TYPE u_buf_count, __UNIT_TYPE v_buf_count, __UNIT_TYPE & buffer_size)
    {
        if (u_buf_count < v_buf_count)
            return (CalculateTempBufferSize(fixed, v_buf_count, u_buf_count, buffer_size));

        if (!fixed && v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC)
        {
            buffer_size = 0;
            return (false);
        }

        if (u_buf_count <= 1)
        {
            buffer_size = 0;
            return (false);
        }
        __UNIT_TYPE n_half = _DIVIDE_CEILING_UNIT(u_buf_count, 2);

        __UNIT_TYPE size1;
        if (CalculateTempBufferSize(fixed, n_half, _MINIMUM_UNIT(v_buf_count, n_half), size1))
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

    static void Add_Debug(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        __UNIT_TYPE backup_u_buf_length = u_buf_count;
        __UNIT_TYPE* backup_u_buf = new __UNIT_TYPE[backup_u_buf_length];
        _COPY_MEMORY_UNIT(backup_u_buf, u_buf, u_buf_count);

        __UNIT_TYPE verification_buf_length = u_buf_count;
        __UNIT_TYPE* verification_buf = new __UNIT_TYPE[verification_buf_length];

        Palmtree::Math::Core::Internal::Basic::Add(u_buf, u_buf_count, v_buf, v_buf_count);

        Palmtree::Math::Core::Internal::Basic::USubtruct(u_buf, __Shrink(u_buf, u_buf_count), v_buf, v_buf_count, verification_buf, verification_buf_length);

        if (!Equals(verification_buf, __Shrink(verification_buf, verification_buf_length), backup_u_buf, __Shrink(backup_u_buf, backup_u_buf_length)))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Add_Debug;1");
        delete[] backup_u_buf;
        delete[] verification_buf;
#else
        Palmtree::Math::Core::Internal::Basic::Add(u_buf, u_buf_count, v_buf, v_buf_count);
#endif
    }

    static void Add_Debug(SIGNED_UNIT_ARRAY& u_buf, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count)
    {
#ifdef _DEBUG
        __UNIT_TYPE backup_u_buf_length = u_buf.WORD_COUNT;
        __UNIT_TYPE* backup_u_buf = new __UNIT_TYPE[backup_u_buf_length];
        _COPY_MEMORY_UNIT(backup_u_buf, u_buf.BLOCK, u_buf.WORD_COUNT);
        SIGNED_UNIT_ARRAY backup_u(u_buf.SIGN, backup_u_buf, backup_u_buf_length);

        __UNIT_TYPE verification_buf_length = u_buf.BLOCK_COUNT;
        __UNIT_TYPE* verification_buf = new __UNIT_TYPE[verification_buf_length];
        SIGNED_UNIT_ARRAY verification(verification_buf, verification_buf_length);

        SIGNED_UNIT_ARRAY v(v_buf, v_buf_count);

        Palmtree::Math::Core::Internal::Basic::Add(u_buf, v_buf, v_buf_count);

        Palmtree::Math::Core::Internal::Basic::Subtruct(u_buf, v, verification);

        if (verification.SIGN != backup_u.SIGN || !Equals(verification.BLOCK, verification.WORD_COUNT, backup_u.BLOCK, backup_u.WORD_COUNT))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Add_Debug;1");
        delete[] backup_u_buf;
        delete[] verification_buf;
#else
        Palmtree::Math::Core::Internal::Basic::Add(u_buf, v_buf, v_buf_count);
#endif
    }

    static void Subtruct_Debug(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, SIGNED_UNIT_ARRAY& w_buf)
    {
        Subtruct(u_buf, u_buf_count, v_buf, v_buf_count, w_buf);
#ifdef _DEBUG
        __UNIT_TYPE verification_buf_length = u_buf_count + v_buf_count;
        __UNIT_TYPE* verification_buf = new __UNIT_TYPE[verification_buf_length];
        SIGNED_UNIT_ARRAY v(v_buf, v_buf_count);
        SIGNED_UNIT_ARRAY verification(verification_buf, verification_buf_length);
        Palmtree::Math::Core::Internal::Basic::Add(w_buf, v, verification);
        if (verification.SIGN < 0 || !Equals(u_buf, u_buf_count, verification.BLOCK, verification.WORD_COUNT))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Subtruct_Debug;1");
        delete[] verification_buf;
#endif
    }

    static void Multiply_UX_UX_Karatsuba_Debug(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
        Multiply_UX_UX_Karatsuba(fixed, current_temp_buf_ptr, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
#ifdef _DEBUG
        __UNIT_TYPE __classic_buf_length = u_buf_count + v_buf_count;
        __UNIT_TYPE* __classic_buf = new __UNIT_TYPE[__classic_buf_length];
        if (u_buf_count == 0 || v_buf_count == 0)
            _ZERO_MEMORY_UNIT(__classic_buf, __classic_buf_length);
        else
            Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, __classic_buf, __classic_buf_length);
        const __UNIT_TYPE __out_buf_count = __Shrink(__classic_buf, __classic_buf_length);
        if (!Equals(w_buf, __Shrink(w_buf, w_buf_count), __classic_buf, __out_buf_count))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba_Debug;1");
        delete[] __classic_buf;
#endif
    }

    static void Multiply_Debug(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (w_buf_count < u_buf_count + v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply;1");
#endif
        if (u_buf_count >= v_buf_count)
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, u_buf_count + v_buf_count);
        else
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, v_buf, v_buf_count, u_buf, u_buf_count, w_buf, u_buf_count + v_buf_count);
        _ZERO_MEMORY_UNIT(w_buf + (u_buf_count + v_buf_count), w_buf_count - (u_buf_count + v_buf_count));
    }

    static void Multiply_Debug(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, SIGNED_UNIT_ARRAY& u, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, SIGNED_UNIT_ARRAY& w)
    {
#ifdef _DEBUG
        if (w.BLOCK_COUNT < u.WORD_COUNT + v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply;1");
#endif
        if (u.WORD_COUNT >= v_buf_count)
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, u.BLOCK, u.WORD_COUNT, v_buf, v_buf_count, w.BLOCK, u.WORD_COUNT + v_buf_count);
        else
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, v_buf, v_buf_count, u.BLOCK, u.WORD_COUNT, w.BLOCK, u.WORD_COUNT + v_buf_count);
        _ZERO_MEMORY_UNIT(w.BLOCK + (u.WORD_COUNT + v_buf_count), w.BLOCK_COUNT - (u.WORD_COUNT + v_buf_count));
        w.WORD_COUNT = u.WORD_COUNT + v_buf_count;
        w.SIGN = u.SIGN;
        w.Shrink();
    }

    static void Multiply_Debug(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, SIGNED_UNIT_ARRAY& u, SIGNED_UNIT_ARRAY& v, SIGNED_UNIT_ARRAY& w)
    {
#ifdef _DEBUG
        if (w.BLOCK_COUNT < u.WORD_COUNT + v.WORD_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply;1");
#endif
        if (u.WORD_COUNT >= v.WORD_COUNT)
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, u.BLOCK, u.WORD_COUNT, v.BLOCK, v.WORD_COUNT, w.BLOCK, u.WORD_COUNT + v.WORD_COUNT);
        else
            Multiply_UX_UX_Karatsuba_Debug(fixed, current_temp_buf_ptr, v.BLOCK, v.WORD_COUNT, u.BLOCK, u.WORD_COUNT, w.BLOCK, u.WORD_COUNT + v.WORD_COUNT);
        _ZERO_MEMORY_UNIT(w.BLOCK + (u.WORD_COUNT + v.WORD_COUNT), w.BLOCK_COUNT - (u.WORD_COUNT + v.WORD_COUNT));
        w.WORD_COUNT = u.WORD_COUNT + v.WORD_COUNT;
        w.SIGN = PRODUCT_SIGN(u.SIGN, v.SIGN);
        w.Shrink();
    }

    static void Multiply_UX_UX_Karatsuba(bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif
        if (!fixed && v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC)
        {
            // 桁数が閾値より小さい場合は classic 法で計算する

            Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
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
            if (w_buf_count < 2)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif
            w_buf[0] = _MULTIPLY_UNIT(u_buf[0], v_buf[0], &w_buf[1]);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(w_buf[0]) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
            _ZERO_MEMORY_UNIT(w_buf + 2, w_buf_count - 2);
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
            __UNIT_TYPE* const u_buf_hi = u_buf_lo + u_buf_lo_length;
            const __UNIT_TYPE u_buf_lo_count = __Shrink(u_buf_lo, u_buf_lo_length);
            const __UNIT_TYPE u_buf_hi_count = __Shrink(u_buf_hi, u_buf_hi_length);

            const __UNIT_TYPE v_buf_lo_length = _MINIMUM_UNIT(v_buf_count, n_half);
            const __UNIT_TYPE v_buf_hi_length = v_buf_count - v_buf_lo_length;
            __UNIT_TYPE* const v_buf_lo = v_buf;
            __UNIT_TYPE* const v_buf_hi = v_buf_lo + v_buf_lo_length;
            const __UNIT_TYPE v_buf_lo_count = __Shrink(v_buf_lo, v_buf_lo_length);
            const __UNIT_TYPE v_buf_hi_count = __Shrink(v_buf_hi, v_buf_hi_length);

            const __UNIT_TYPE t1_buf_length = n_half;
            const __UNIT_TYPE t2_buf_length = n_half;
            const __UNIT_TYPE t3_buf_length = n_half * 2 + 1;
            __UNIT_TYPE* const t1_buf = current_temp_buf_ptr; current_temp_buf_ptr += t1_buf_length;
            __UNIT_TYPE* const t2_buf = current_temp_buf_ptr; current_temp_buf_ptr += t2_buf_length;
            __UNIT_TYPE* const t3_buf = current_temp_buf_ptr; current_temp_buf_ptr += t3_buf_length;
            SIGNED_UNIT_ARRAY t1(t1_buf, t1_buf_length);
            SIGNED_UNIT_ARRAY t2(t2_buf, t2_buf_length);
            SIGNED_UNIT_ARRAY t3(t3_buf, t3_buf_length);

            const __UNIT_TYPE w_buf_lo_length = n_half * 2;
            const __UNIT_TYPE w_buf_hi_length = w_buf_count - w_buf_lo_length;
            __UNIT_TYPE* const w_buf_lo = w_buf;
            __UNIT_TYPE* const w_buf_hi = w_buf_lo + w_buf_lo_length;

            const __UNIT_TYPE w_buf_mid_length = w_buf_count - n_half;
            __UNIT_TYPE* const w_buf_mid = w_buf + n_half;

            Multiply_Debug(fixed, current_temp_buf_ptr, u_buf_lo, u_buf_lo_count, v_buf_lo, v_buf_lo_count, w_buf_lo, w_buf_lo_length);
            const __UNIT_TYPE w_buf_lo_count = __Shrink(w_buf_lo, w_buf_lo_length);

            if (v_buf_hi_count > 0)
            {
                // v_buf_hi が 0 ではない場合

                Multiply_Debug(fixed, current_temp_buf_ptr, u_buf_hi, u_buf_hi_count, v_buf_hi, v_buf_hi_count, w_buf_hi, w_buf_hi_length);
                _ZERO_MEMORY_UNIT(w_buf_hi + (u_buf_hi_count + v_buf_hi_count), w_buf_hi_length - (u_buf_hi_count + v_buf_hi_count));

                const __UNIT_TYPE w_buf_hi_count = __Shrink(w_buf_hi, w_buf_hi_length);

                Subtruct_Debug(u_buf_lo, u_buf_lo_count, u_buf_hi, u_buf_hi_count, t1);
                Subtruct_Debug(v_buf_lo, v_buf_lo_count, v_buf_hi, v_buf_hi_count, t2);

                Multiply_Debug(fixed, current_temp_buf_ptr, t1, t2, t3);
                t3.Negate();

                Add_Debug(t3, w_buf_hi, w_buf_hi_count);
                Add_Debug(t3, w_buf_lo, w_buf_lo_count);

                if (t3.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;3");

                Add_Debug(w_buf_mid, w_buf_mid_length, t3.BLOCK, t3.WORD_COUNT);
            }
            else
            {
                // v_buf_hi が 0 の場合

                _ZERO_MEMORY_UNIT(w_buf_hi, w_buf_hi_length);

                Subtruct_Debug(u_buf_lo, u_buf_lo_count, u_buf_hi, u_buf_hi_count, t1);

                Multiply_Debug(fixed, current_temp_buf_ptr, t1, v_buf_lo, v_buf_lo_count, t3);
                t3.Negate();

                Add_Debug(t3, w_buf_lo, w_buf_lo_count);

                if (t3.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;3");

                Add_Debug(w_buf_mid, w_buf_mid_length, t3.BLOCK, t3.WORD_COUNT);
            }
        }
    }

    void Multiply_UX_UX(ThreadContext& tc, bool fixed, __UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count)
    {
        if (!fixed && (u_buf_count < WORD_COUNT_THRESHOLD_CLASSIC || v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC))
            Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        else
        {
            __UNIT_TYPE temp_buffer_count;
            if (CalculateTempBufferSize(fixed, u_buf_count, v_buf_count, temp_buffer_count) || temp_buffer_count > MAX_USER_MEMORY_SIZE / __UNIT_TYPE_BYTE_COUNT)
            {
                // Karatsuba 法に必要な一時メモリ領域のサイズが __UNIT_TYPE (==size_t) で表現できる範囲を超えた場合、
                // 仕方がないので代わりに古典的算法を実行する
                Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
            }
            else
            {
                ResourceHolderUINT root(tc);

                __UNIT_TYPE* temp_buf = root.AllocateBlock(temp_buffer_count);
                Multiply_Debug(fixed, temp_buf, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
            }
        }
    }

}


/*
 * END OF FILE
 */