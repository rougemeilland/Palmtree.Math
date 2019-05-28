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
#include "pmc_signedunitarray.h"
#include "pmc_inline_func.h"

#ifdef _M_IX86
#define WORD_COUNT_THRESHOLD_KARATSUBA  (8192)                  // u_buf と v_buf のどちらかのワード長がこの値未満ならば karatsuba 法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x80000000U)           // 現実的に利用可能なユーザメモリの最大サイズ
#elif defined(_M_X64)
#define WORD_COUNT_THRESHOLD_KARATSUBA  (16384)                 // u_buf と v_buf のどちらかのワード長がこの値未満ならば karatsuba 法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x8000000000000000UL)  // 現実的に利用可能なユーザメモリの最大サイズ
#else
#error unknown platform
#endif

namespace Palmtree::Math::Core::Internal::Multiply::ToomCook
{

    using namespace Palmtree::Math::Core::Internal::Basic;

    static void Multiply_UX_UX_ToomCook(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count);

    static bool CalculateTempBufferSize(bool fixed, __UNIT_TYPE u_buf_count, __UNIT_TYPE v_buf_count, __UNIT_TYPE & buffer_size)
    {
        if (u_buf_count < v_buf_count)
            return (CalculateTempBufferSize(fixed, v_buf_count, u_buf_count, buffer_size));

        if (u_buf_count <= 4)
        {
            buffer_size = 0;
            return (false);
        }

        if (!fixed && v_buf_count < WORD_COUNT_THRESHOLD_KARATSUBA)
        {
            buffer_size = 0;
            return (false);
        }

        __UNIT_TYPE n_one_third = _DIVIDE_CEILING_UNIT(u_buf_count, 3);

        __UNIT_TYPE size1;
        if (CalculateTempBufferSize(fixed, n_one_third + 1, _MINIMUM_UNIT(v_buf_count, n_one_third) + 1, size1))
        {
            buffer_size = 0;
            return (true);
        }

        if (n_one_third > ((__UNIT_TYPE)-1 - 12U) / 12U)
        {
            // 12 * n_one_third + 12 が __UNIT_TYPE で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
        __UNIT_TYPE size2 = 12 * n_one_third + 12;

        if (n_one_third > ((__UNIT_TYPE)-1 - 2U) / 2U)
        {
            // 2 * n_one_third + 2 が __UNIT_TYPE で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
        __UNIT_TYPE size3 = 2 * n_one_third + 2;

        buffer_size = _MAXIMUM_UNIT(size1, size3);
        if (_ADD_UNIT(0, buffer_size, size2, &buffer_size))
        {
            // total_size += size2 で桁あふれが起きた場合
            buffer_size = 0;
            return (true);
        }

        return (false);
    }

    __inline static void MultiplyBy3(SIGNED_UNIT_ARRAY& u, __UNIT_TYPE* work_buf, __UNIT_TYPE work_buf_count)
    {
        LeftShift(u.BLOCK, u.WORD_COUNT, 1, work_buf, work_buf_count);
        Add(u.BLOCK, u.BLOCK_COUNT, work_buf, __Shrink(work_buf, work_buf_count));
        u.WORD_COUNT += 1;
        u.Shrink();
    }

    __inline static void DivideExactlyBy2(SIGNED_UNIT_ARRAY& u)
    {
        if (u.BLOCK_COUNT == 0)
        {
            // nop
        }
        else
        {
            if (u.BLOCK[0] & 1)
                throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
            RightShift(u, 1);
        }
    }

    static void Multiply_UX_UX_ToomCook_Debug(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
        Multiply_UX_UX_ToomCook(tc, fixed, current_temp_buf_ptr, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
#ifdef _DEBUG
        __UNIT_TYPE __classic_buf_length = u_buf_count + v_buf_count;
        __UNIT_TYPE* __classic_buf = new __UNIT_TYPE[__classic_buf_length];
        if (u_buf_count == 0 || v_buf_count == 0)
            _ZERO_MEMORY_UNIT(__classic_buf, __classic_buf_length);
        else
            Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, __classic_buf, __classic_buf_length);
        const __UNIT_TYPE __out_buf_count = __Shrink(__classic_buf, __classic_buf_length);
        if (!Equals(w_buf, __Shrink(w_buf, w_buf_count), __classic_buf, __out_buf_count))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook_Debug;1");
        delete[] __classic_buf;
#endif
    }

    static void Multiply_Debug(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (w_buf_count < u_buf_count + v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_Debug;1");
#endif
        if (u_buf_count >= v_buf_count)
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, u_buf_count + v_buf_count);
        else
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, v_buf, v_buf_count, u_buf, u_buf_count, w_buf, u_buf_count + v_buf_count);
        _ZERO_MEMORY_UNIT(w_buf + (u_buf_count + v_buf_count), w_buf_count - (u_buf_count + v_buf_count));
    }

    static void Multiply_Debug(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, SIGNED_UNIT_ARRAY& w)
    {
#ifdef _DEBUG
        if (w.BLOCK_COUNT < u_buf_count + v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_Debug;1");
#endif
        if (u_buf_count >= v_buf_count)
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, u_buf, u_buf_count, v_buf, v_buf_count, w.BLOCK, u_buf_count + v_buf_count);
        else
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, v_buf, v_buf_count, u_buf, u_buf_count, w.BLOCK, u_buf_count + v_buf_count);
        _ZERO_MEMORY_UNIT(w.BLOCK + (u_buf_count + v_buf_count), w.BLOCK_COUNT - (u_buf_count + v_buf_count));
        w.WORD_COUNT = u_buf_count + v_buf_count;
        w.SIGN = SIGN_POSITIVE;
        w.Shrink();
    }

    static void Multiply_Debug(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, SIGNED_UNIT_ARRAY& u, SIGNED_UNIT_ARRAY& v, SIGNED_UNIT_ARRAY& w)
    {
#ifdef _DEBUG
        if (w.BLOCK_COUNT < u.WORD_COUNT + v.WORD_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_Debug;1");
#endif
        if (u.WORD_COUNT >= v.WORD_COUNT)
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, u.BLOCK, u.WORD_COUNT, v.BLOCK, v.WORD_COUNT, w.BLOCK, u.WORD_COUNT + v.WORD_COUNT);
        else
            Multiply_UX_UX_ToomCook_Debug(tc, fixed, current_temp_buf_ptr, v.BLOCK, v.WORD_COUNT, u.BLOCK, u.WORD_COUNT, w.BLOCK, u.WORD_COUNT + v.WORD_COUNT);
        _ZERO_MEMORY_UNIT(w.BLOCK + (u.WORD_COUNT + v.WORD_COUNT), w.BLOCK_COUNT - (u.WORD_COUNT + v.WORD_COUNT));
        w.WORD_COUNT = u.WORD_COUNT + v.WORD_COUNT;
        w.SIGN = PRODUCT_SIGN(u.SIGN, v.SIGN);
        w.Shrink();
    }

    static void Multiply_UX_UX_ToomCook(ThreadContext& tc, bool fixed, __UNIT_TYPE * current_temp_buf_ptr, __UNIT_TYPE * u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE * w_buf, __UNIT_TYPE w_buf_count)
    {
#ifdef _DEBUG
        if (u_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;1");
#endif
        if (v_buf_count == 0)
        {
            // u_buf と v_buf の少なくともどちらかが 0 の場合

            // 0 を返す
            _ZERO_MEMORY_UNIT(w_buf, w_buf_count);
        }
        else if (u_buf_count <= 4)
        {
            // u_buf と v_buf がともに 4 ワード以下の場合
            // u_buf が 3 分割できないことがあるので、強制的に Classic 法に切り替える
            Palmtree::Math::Core::Internal::Multiply::Classic::Multiply_UX_UX(u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        }
        else if (!fixed && v_buf_count < WORD_COUNT_THRESHOLD_KARATSUBA)
        {
            // 桁数が閾値より小さい場合は karatsuba 法で計算する

            Palmtree::Math::Core::Internal::Multiply::Karatsuba::Multiply_UX_UX(tc, false, u_buf, u_buf_count, v_buf, v_buf_count, w_buf, w_buf_count);
        }
        else
        {
            // u_buf と v_buf の少なくともどちらかが 5 ワード以上の場合

#ifdef _DEBUG
            if (w_buf_count != u_buf_count + v_buf_count)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;2");
#endif

            const __UNIT_TYPE n_one_third = _DIVIDE_CEILING_UNIT(u_buf_count, 3);
#ifdef _DEBUG
            if (n_one_third <= 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;3");
#endif

            // 変数の割り当て

            const __UNIT_TYPE u0_buf_length = n_one_third;
            __UNIT_TYPE* const u0_buf = u_buf;
            const __UNIT_TYPE u0_buf_count = __Shrink(u0_buf, u0_buf_length);

            const __UNIT_TYPE u1_buf_length = n_one_third;
            __UNIT_TYPE* const u1_buf = u0_buf + u0_buf_length;
            const __UNIT_TYPE u1_buf_count = __Shrink(u1_buf, u1_buf_length);

            const __UNIT_TYPE u2_buf_length = u_buf_count - (u0_buf_length + u1_buf_length);
            __UNIT_TYPE* const u2_buf = u1_buf + u1_buf_length;
            const __UNIT_TYPE u2_buf_count = __Shrink(u2_buf, u2_buf_length);

            const __UNIT_TYPE v0_buf_length = _MINIMUM_UNIT(v_buf_count, n_one_third);
            __UNIT_TYPE* const v0_buf = v_buf;
            const __UNIT_TYPE v0_buf_count = __Shrink(v0_buf, v0_buf_length);

            const __UNIT_TYPE v1_buf_length = _MINIMUM_UNIT(v_buf_count - v0_buf_length, n_one_third);
            __UNIT_TYPE* const v1_buf = v0_buf + v0_buf_length;
            const __UNIT_TYPE v1_buf_count = __Shrink(v1_buf, v1_buf_length);

            const __UNIT_TYPE v2_buf_length = v_buf_count - (v0_buf_length + v1_buf_length);
            __UNIT_TYPE* const v2_buf = v1_buf + v1_buf_length;
            const __UNIT_TYPE v2_buf_count = __Shrink(v2_buf, v2_buf_length);

            //const __UNIT_TYPE w0_buf_length = n_one_third * 2;
            //__UNIT_TYPE* const w0_buf = w_buf;

            const __UNIT_TYPE w1_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const w1_buf = current_temp_buf_ptr; current_temp_buf_ptr += w1_buf_length;
            SIGNED_UNIT_ARRAY w1(w1_buf, w1_buf_length);

            const __UNIT_TYPE w2_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const w2_buf = current_temp_buf_ptr; current_temp_buf_ptr += w2_buf_length;
            SIGNED_UNIT_ARRAY w2(w2_buf, w2_buf_length);

            const __UNIT_TYPE w3_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const w3_buf = current_temp_buf_ptr; current_temp_buf_ptr += w3_buf_length;
            SIGNED_UNIT_ARRAY w3(w3_buf, w3_buf_length);

            //const __UNIT_TYPE w4_buf_length = w_buf_count - n_one_third * 4;
            //__UNIT_TYPE* const w4_buf = w_buf + n_one_third * 4;

            const __UNIT_TYPE Uinfinity_buf_count = u2_buf_count;
            __UNIT_TYPE* const Uinfinity_buf = u2_buf;

            const __UNIT_TYPE U2_buf_length = w3_buf_length / 2;
            __UNIT_TYPE* const U2_buf = w3_buf;

            const __UNIT_TYPE U1_buf_length = w2_buf_length / 2;
            __UNIT_TYPE* const U1_buf = w2_buf;

            const __UNIT_TYPE Uminus1_buf_length = w1_buf_length / 2;
            __UNIT_TYPE* const Uminus1_buf = w1_buf;
            SIGNED_UNIT_ARRAY Uminus1(Uminus1_buf, Uminus1_buf_length);

            const __UNIT_TYPE U0_buf_count = u0_buf_count;
            __UNIT_TYPE* const U0_buf = u0_buf;

            const __UNIT_TYPE Vinfinity_buf_count = v2_buf_count;
            __UNIT_TYPE* const Vinfinity_buf = v2_buf;

            const __UNIT_TYPE V2_buf_length = w3_buf_length - U2_buf_length;
            __UNIT_TYPE* const V2_buf = w3_buf + U2_buf_length;

            const __UNIT_TYPE V1_buf_length = w2_buf_length - U1_buf_length;
            __UNIT_TYPE* const V1_buf = w2_buf + U1_buf_length;

            const __UNIT_TYPE Vminus1_buf_length = w1_buf_length - Uminus1_buf_length;
            __UNIT_TYPE* const Vminus1_buf = w1_buf + Uminus1_buf_length;
            SIGNED_UNIT_ARRAY Vminus1(Vminus1_buf, Vminus1_buf_length);

            const __UNIT_TYPE V0_buf_count = v0_buf_count;
            __UNIT_TYPE* const V0_buf = v0_buf;

            const __UNIT_TYPE Winfinity_buf_length = w_buf_count - n_one_third * 4;
            __UNIT_TYPE* const Winfinity_buf = w_buf + n_one_third * 4;

            const __UNIT_TYPE W2_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const W2_buf = current_temp_buf_ptr; current_temp_buf_ptr += W2_buf_length;

            const __UNIT_TYPE W1_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const W1_buf = current_temp_buf_ptr; current_temp_buf_ptr += W1_buf_length;

            const __UNIT_TYPE Wminus1_buf_length = n_one_third * 2 + 2;
            __UNIT_TYPE* const Wminus1_buf = current_temp_buf_ptr; current_temp_buf_ptr += Wminus1_buf_length;
            SIGNED_UNIT_ARRAY Wminus1(Wminus1_buf, Wminus1_buf_length);

            const __UNIT_TYPE W0_buf_length = n_one_third * 2;
            __UNIT_TYPE* const W0_buf = w_buf;

            if (v2_buf_count > 0)
            {
                // v の長さが n_one_third * 2 より大きい場合

                // var Uinfinity = u2;
                // nop

                // var U2 = (((u2 << 1) + u1) << 1) + u0;
                LeftShift(u2_buf, u2_buf_count, 1, U2_buf, U2_buf_length);
                Add(U2_buf, U2_buf_length, u1_buf, u1_buf_count);
                LeftShift(U2_buf, U2_buf_length, 1);
                Add(U2_buf, U2_buf_length, u0_buf, u0_buf_count);
                const __UNIT_TYPE U2_buf_count = __Shrink(U2_buf, U2_buf_length);

                // var U1 = u2 + u1 + u0;
                Add(u2_buf, u2_buf_count, u1_buf, u1_buf_count, U1_buf, U1_buf_length);
                Add(U1_buf, U1_buf_length, u0_buf, u0_buf_count);
                const __UNIT_TYPE U1_buf_count = __Shrink(U1_buf, U1_buf_length);

                // var U0 = u0;
                // nop

                // var Uminus1 = u2 - u1 + u0;
                Subtruct(u2_buf, u2_buf_count, u1_buf, u1_buf_count, Uminus1);
                Add(Uminus1, u0_buf, u0_buf_count);

                // var Vinfinity = v2;
                // nop

                // var V2 = (((v2 << 1) + v1) << 1) + v0;
                LeftShift(v2_buf, v2_buf_count, 1, V2_buf, V2_buf_length);
                Add(V2_buf, V2_buf_length, v1_buf, v1_buf_count);
                LeftShift(V2_buf, V2_buf_length, 1);
                Add(V2_buf, V2_buf_length, v0_buf, v0_buf_count);
                const __UNIT_TYPE V2_buf_count = __Shrink(V2_buf, V2_buf_length);

                // var V1 = v2 + v1 + v0;
                Add(v2_buf, v2_buf_count, v1_buf, v1_buf_count, V1_buf, V1_buf_length);
                Add(V1_buf, V1_buf_length, v0_buf, v0_buf_count);
                const __UNIT_TYPE V1_buf_count = __Shrink(V1_buf, V1_buf_length);

                // var V0 = v0;
                // nop

                // var V_minus1 = v2 - v1 + v0;
                Subtruct(v2_buf, v2_buf_count, v1_buf, v1_buf_count, Vminus1);
                Add(Vminus1, v0_buf, v0_buf_count);

                // var Winfinity = Uinfinity * Vinfinity;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, Uinfinity_buf, Uinfinity_buf_count, Vinfinity_buf, Vinfinity_buf_count, Winfinity_buf, Winfinity_buf_length);
                const __UNIT_TYPE Winfinity_buf_count = __Shrink(Winfinity_buf, Winfinity_buf_length);

                // var W2 = U2 * V2;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U2_buf, U2_buf_count, V2_buf, V2_buf_count, W2_buf, W2_buf_length);
                const __UNIT_TYPE W2_buf_count = __Shrink(W2_buf, W2_buf_length);

                // var W1 = U1 * V1;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U1_buf, U1_buf_count, V1_buf, V1_buf_count, W1_buf, W1_buf_length);
                const __UNIT_TYPE W1_buf_count = __Shrink(W1_buf, W1_buf_length);

                // var W0 = U0 * V0;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U0_buf, U0_buf_count, V0_buf, V0_buf_count, W0_buf, W0_buf_length);
                const __UNIT_TYPE W0_buf_count = __Shrink(W0_buf, W0_buf_length);

                // var Wminus1 = Uminus1 * Vminus1;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, Uminus1, Vminus1, Wminus1);

                // 3 による完全除算のための作業域
                const __UNIT_TYPE work_buf_length = n_one_third * 2 + 2;
                __UNIT_TYPE* const work_buf = current_temp_buf_ptr; current_temp_buf_ptr += work_buf_length;
                SIGNED_UNIT_ARRAY work(work_buf, work_buf_length);

                // var w4 = Winfinity;
                // nop

                // var w3 = ((-(Winfinity << 2) - W1 + W0) * 3 + W2 - Wminus1).DivideExactly(6);
                LeftShift(Winfinity_buf, Winfinity_buf_count, 2, w3);
                w3.Negate();
                Subtruct(w3, W1_buf, W1_buf_count);
                Add(w3, W0_buf, W0_buf_count);
                MultiplyBy3(w3, work_buf, work_buf_length);
                Add(w3, W2_buf, W2_buf_count);
                Subtruct(w3, Wminus1);
                DivideExactlyBy2(w3);
                DivideExactlyBy3(w3, work_buf, work_buf_length);
                if (w3.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;5");

                // var w2 = (((-(Winfinity + W0)) << 1) + W1 + Wminus1).DivideExactly(2);
                Add(Winfinity_buf, Winfinity_buf_count, W0_buf, W0_buf_count, w2);
                w2.Negate();
                LeftShift(w2, 1);
                Add(w2, W1_buf, W1_buf_count);
                Add(w2, Wminus1);
                DivideExactlyBy2(w2);
                if (w2.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;6");

                // var w1 = (((((Winfinity << 1) + W1) << 1) - W0) * 3 - (Wminus1 << 1) - W2).DivideExactly(6);
                LeftShift(Winfinity_buf, Winfinity_buf_count, 1, w1);
                Add(w1, W1_buf, W1_buf_count);
                LeftShift(w1, 1);
                Subtruct(w1, W0_buf, W0_buf_count);
                MultiplyBy3(w1, work_buf, work_buf_length);
                LeftShift(Wminus1, 1, work);
                Subtruct(w1, work);
                Subtruct(w1, W2_buf, W2_buf_count);
                DivideExactlyBy2(w1);
                DivideExactlyBy3(w1, work_buf, work_buf_length);
                if (w1.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;7");

                // var w0 = W0;
                // nop

                // var w = (w4 << (n_one_third * 4)) + (w3 << (n_one_third * 3)) + (w2 << (n_one_third * 2)) + (w1 << n_one_third) + w0;
#ifdef _DEBUG
                if (w_buf_count < n_one_third * 4)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;8");
#endif
                _ZERO_MEMORY_UNIT(w_buf + n_one_third * 2, n_one_third * 2);
                Add(w_buf + n_one_third * 3, w_buf_count - n_one_third * 3, w3.BLOCK, w3.WORD_COUNT);
                Add(w_buf + n_one_third * 2, w_buf_count - n_one_third * 2, w2.BLOCK, w2.WORD_COUNT);
                Add(w_buf + n_one_third * 1, w_buf_count - n_one_third * 1, w1.BLOCK, w1.WORD_COUNT);
            }
            else if (v1_buf_count > 0)
            {
                // v の長さが n_one_third * 2 以下でありかつ n_one_third * 1 より大きい場合

                // var Uinfinity = u2;
                // nop

                // var U2 = (((u2 << 1) + u1) << 1) + u0;
                LeftShift(u2_buf, u2_buf_count, 1, U2_buf, U2_buf_length);
                Add(U2_buf, U2_buf_length, u1_buf, u1_buf_count);
                LeftShift(U2_buf, U2_buf_length, 1);
                Add(U2_buf, U2_buf_length, u0_buf, u0_buf_count);
                const __UNIT_TYPE U2_buf_count = __Shrink(U2_buf, U2_buf_length);

                // var U1 = u2 + u1 + u0;
                Add(u2_buf, u2_buf_count, u1_buf, u1_buf_count, U1_buf, U1_buf_length);
                Add(U1_buf, U1_buf_length, u0_buf, u0_buf_count);
                const __UNIT_TYPE U1_buf_count = __Shrink(U1_buf, U1_buf_length);

                // var U0 = u0;
                // nop

                // var Uminus1 = u2 - u1 + u0;
                Subtruct(u2_buf, u2_buf_count, u1_buf, u1_buf_count, Uminus1);
                Add(Uminus1, u0_buf, u0_buf_count);

                // var V2 = (v1 << 1) + v0;
                LeftShift(v1_buf, v1_buf_count, 1, V2_buf, V2_buf_length);
                Add(V2_buf, V2_buf_length, v0_buf, v0_buf_count);
                const __UNIT_TYPE V2_buf_count = __Shrink(V2_buf, V2_buf_length);

                // var V1 = v1 + v0;
                Add(v1_buf, v1_buf_count, v0_buf, v0_buf_count, V1_buf, V1_buf_length);
                const __UNIT_TYPE V1_buf_count = __Shrink(V1_buf, V1_buf_length);

                // var V0 = v0;
                // nop

                // var V_minus1 = - v1 + v0;
                Subtruct(v0_buf, v0_buf_count, v1_buf, v1_buf_count, Vminus1);

                // var W2 = U2 * V2;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U2_buf, U2_buf_count, V2_buf, V2_buf_count, W2_buf, W2_buf_length);
                const __UNIT_TYPE W2_buf_count = __Shrink(W2_buf, W2_buf_length);

                // var W1 = U1 * V1;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U1_buf, U1_buf_count, V1_buf, V1_buf_count, W1_buf, W1_buf_length);
                const __UNIT_TYPE W1_buf_count = __Shrink(W1_buf, W1_buf_length);

                // var W0 = U0 * V0;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, U0_buf, U0_buf_count, V0_buf, V0_buf_count, W0_buf, W0_buf_length);
                const __UNIT_TYPE W0_buf_count = __Shrink(W0_buf, W0_buf_length);

                // var Wminus1 = Uminus1 * Vminus1;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, Uminus1, Vminus1, Wminus1);

                // 3 による完全除算のための作業域
                const __UNIT_TYPE work_buf_length = n_one_third * 2 + 2;
                __UNIT_TYPE* const work_buf = current_temp_buf_ptr; current_temp_buf_ptr += work_buf_length;
                SIGNED_UNIT_ARRAY work(work_buf, work_buf_length);

                // var w4 = Winfinity;
                // nop

                // var w3 = ((- W1 + W0) * 3 + W2 - Wminus1).DivideExactly(6);
                Subtruct(W0_buf, W0_buf_count, W1_buf, W1_buf_count, w3);
                MultiplyBy3(w3, work_buf, work_buf_length);
                Add(w3, W2_buf, W2_buf_count);
                Subtruct(w3, Wminus1);
                DivideExactlyBy2(w3);
                DivideExactlyBy3(w3, work_buf, work_buf_length);
                if (w3.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;9");

                // var w2 = (-(W0 << 1) + W1 + Wminus1).DivideExactly(2);
                LeftShift(W0_buf, W0_buf_count, 1, w2);
                w2.Negate();
                Add(w2, W1_buf, W1_buf_count);
                Add(w2, Wminus1);
                DivideExactlyBy2(w2);
                if (w2.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;10");

                // var w1 = (((W1 << 1) - W0) * 3 - (Wminus1 << 1) - W2).DivideExactly(6);
                LeftShift(W1_buf, W1_buf_count, 1, w1);
                Subtruct(w1, W0_buf, W0_buf_count);
                MultiplyBy3(w1, work_buf, work_buf_length);
                LeftShift(Wminus1, 1, work);
                Subtruct(w1, work);
                Subtruct(w1, W2_buf, W2_buf_count);
                DivideExactlyBy2(w1);
                DivideExactlyBy3(w1, work_buf, work_buf_length);
                if (w1.SIGN < 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;11");

                // var w0 = W0;
                // nop

                // var w = (w3 << (n_one_third * 3)) + (w2 << (n_one_third * 2)) + (w1 << n_one_third) + w0;
#ifdef _DEBUG
                if (w_buf_count < n_one_third * 3)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;12");
#endif
                _ZERO_MEMORY_UNIT(w_buf + n_one_third * 2, w_buf_count - n_one_third * 2);
                Add(w_buf + n_one_third * 3, w_buf_count - n_one_third * 3, w3.BLOCK, w3.WORD_COUNT);
                Add(w_buf + n_one_third * 2, w_buf_count - n_one_third * 2, w2.BLOCK, w2.WORD_COUNT);
                Add(w_buf + n_one_third * 1, w_buf_count - n_one_third * 1, w1.BLOCK, w1.WORD_COUNT);
            }
            else
            {
                // v の長さが n_one_third * 1 以下でありかつ 0 より大きい場合

                // var w2 = u2 * v0;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, u2_buf, u2_buf_count, v0_buf, v0_buf_count, w2);
                const __UNIT_TYPE W2_buf_count = __Shrink(W2_buf, W2_buf_length);

                // var w1 = u1 * v0;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, u1_buf, u1_buf_count, v0_buf, v0_buf_count, w1);
                const __UNIT_TYPE W1_buf_count = __Shrink(W1_buf, W1_buf_length);

                // var w0 = u0 * v0;
                Multiply_Debug(tc, fixed, current_temp_buf_ptr, u0_buf, u0_buf_count, V0_buf, V0_buf_count, W0_buf, W0_buf_length);
                const __UNIT_TYPE W0_buf_count = __Shrink(W0_buf, W0_buf_length);

                // var w = (w2 << (n_one_third * 2)) + (w1 << n_one_third) + w0;
#ifdef _DEBUG
                if (w_buf_count < n_one_third * 2)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply_toomcook.cpp;Multiply_UX_UX_ToomCook;16");
#endif
                _ZERO_MEMORY_UNIT(w_buf + n_one_third * 2, w_buf_count - n_one_third * 2);
                Add(w_buf + n_one_third * 2, w_buf_count - n_one_third * 2, w2.BLOCK, w2.WORD_COUNT);
                Add(w_buf + n_one_third * 1, w_buf_count - n_one_third * 1, w1.BLOCK, w1.WORD_COUNT);
            }
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