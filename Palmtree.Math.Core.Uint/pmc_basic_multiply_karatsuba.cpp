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
#define WORD_COUNT_THRESHOLD_CLASSIC    (65536)                 // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x80000000U)           // 現実的に利用可能なユーザメモリの最大サイズ
#elif defined(_M_X64)
#define WORD_COUNT_THRESHOLD_CLASSIC    (131072)                // u_buf と v_buf のどちらかのワード長がこの値未満ならば classic法 に切り替える
#define MAX_USER_MEMORY_SIZE            (0x8000000000000000U)   // 現実的に利用可能なユーザメモリの最大サイズ
#else
#error unknown platform
#endif
namespace Palmtree::Math::Core::Internal
{

    KaratsubaMultiplicationEngine::KaratsubaMultiplicationEngine(bool fixed, ClassicMultiplicationEngine& classic_engine, BasicOperatorEngine & basic_ep)
        : _fixed(fixed), _classic_engine(classic_engine), _basic_ep(basic_ep)
    {
    }

    KaratsubaMultiplicationEngine::~KaratsubaMultiplicationEngine()
    {
    }

    void KaratsubaMultiplicationEngine::Multiply_UX_UX(ThreadContext & tc, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T & w_buf)
    {
        if (u_buf.BLOCK_COUNT < WORD_COUNT_THRESHOLD_CLASSIC || v_buf.BLOCK_COUNT < WORD_COUNT_THRESHOLD_CLASSIC)
            _classic_engine.Multiply_UX_UX(u_buf, v_buf, w_buf);
        else
        {
            __UNIT_TYPE temp_buffer_count;
            if (CalculateTempBufferSize(u_buf.BLOCK_COUNT, v_buf.BLOCK_COUNT, temp_buffer_count) || temp_buffer_count > MAX_USER_MEMORY_SIZE/ __UNIT_TYPE_BIT_COUNT)
            {
                // Karatsuba 法に必要な一時メモリ領域のサイズが __UNIT_TYPE (==size_t) で表現できる範囲を超えた場合、
                // 仕方がないので代わりに古典的算法を実行する
                _classic_engine.Multiply_UX_UX(u_buf, v_buf, w_buf);
            }

            ResourceHolderUINT root(tc);

            _UBASIC_T temp_buf = root.AllocateBlock(temp_buffer_count);
            if (u_buf.BLOCK_COUNT >= v_buf.BLOCK_COUNT)
                Multiply_UX_UX_Karatsuba(root, temp_buf, 0, u_buf, v_buf, w_buf);
            else
                Multiply_UX_UX_Karatsuba(root, temp_buf, 0, v_buf, u_buf, w_buf);
        }
    }

    bool KaratsubaMultiplicationEngine::CalculateTempBufferSize(__UNIT_TYPE u_buf_count, __UNIT_TYPE v_buf_count, __UNIT_TYPE & buffer_size)
    {
        if (u_buf_count < v_buf_count)
            return (CalculateTempBufferSize(v_buf_count, u_buf_count, buffer_size));
        if (u_buf_count == 0)
        {
            buffer_size = 0;
            return (false);
        }
        if (_fixed && v_buf_count < WORD_COUNT_THRESHOLD_CLASSIC)
        {
            buffer_size = 0;
            return (false);
        }

        __UNIT_TYPE n = _DIVIDE_CEILING_UNIT(u_buf_count, 2);

        __UNIT_TYPE size1;
        if (CalculateTempBufferSize(n, _MINIMUM_UNIT(v_buf_count, n), size1))
        {
            buffer_size = 0;
            return (true);
        }

        __UNIT_TYPE size2;
        if (CalculateTempBufferSize(u_buf_count - n, v_buf_count - _MINIMUM_UNIT(v_buf_count, n), size2))
        {
            buffer_size = 0;
            return (true);
        }

#ifdef _M_IX86
#elif defined(_M_X64)
        if (n > 7158278810U)
        {
            // (n + 1) * 8 が 32bit 符号なし整数で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
#else
        if (n > 3074457345618258601UL)
        {
            // (n + 1) * 8 が 64bit 符号なし整数で表現できる範囲を超える場合
            buffer_size = 0;
            return (true);
        }
#error unknown platform
#endif
        __UNIT_TYPE size3 = (n + 1) * 10;

        __UNIT_TYPE total_size = size1;
        if (_ADD_UNIT(0, total_size, size2, &total_size))
        {
            // total_size += size2 で桁あふれが起きた場合
            buffer_size = 0;
            return (true);
        }
        if (_ADD_UNIT(0, total_size, size3, &total_size))
        {
            // total_size += size3 で桁あふれが起きた場合
            buffer_size = 0;
            return (true);
        }
        return (total_size);
    }

    void KaratsubaMultiplicationEngine::Multiply_UX_UX_Karatsuba(ResourceHolderUINT & root, _UBASIC_T temp_buf, __UNIT_TYPE current_temp_buf_index, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T & w_buf)
    {
#ifdef _DEBUG
        // u_buf >= v_buf でなければならない
        if (u_buf.BLOCK_COUNT < u_buf.BLOCK_COUNT)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;1");
#endif

        if (!_fixed && v_buf.BLOCK_COUNT < WORD_COUNT_THRESHOLD_CLASSIC)
        {
            // 桁数が閾値より小さい場合は classic 法で計算する

            _classic_engine.Multiply_UX_UX( u_buf, v_buf, w_buf);
        }
        else if (v_buf.BLOCK_COUNT == 0)
        {
            // u_buf と v_buf の少なくともどちらかが 0 の場合

            // 0 を返す
            w_buf.Clear();
        }
        else if (u_buf.BLOCK_COUNT == 1)
        {
            // u_buf と v_buf がともに 1 ワード長の場合
            w_buf.BLOCK[0] = _MULTIPLY_UNIT(u_buf.BLOCK[0], v_buf.BLOCK[0], &w_buf.BLOCK[1]);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(w_buf.BLOCK[0]) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
            w_buf.Region(2).Clear();
        }
        else
        {
            // u_buf と v_buf の少なくともどちらかが 2 ワード以上の場合

            __UNIT_TYPE n_half = _DIVIDE_CEILING_UNIT(u_buf.BLOCK_COUNT, 2);

            __UNIT_TYPE u_buf_lo_count = n_half;
            __UNIT_TYPE u_buf_hi_count = u_buf.BLOCK_COUNT - n_half;
            _UBASIC_T u_buf_lo = u_buf.Region(0, u_buf_lo_count);
            _UBASIC_T u_buf_hi = u_buf.Region(u_buf_lo_count);

            __UNIT_TYPE v_buf_lo_count = _MINIMUM_UNIT(v_buf.BLOCK_COUNT, n_half);
            __UNIT_TYPE v_buf_hi_count = v_buf.BLOCK_COUNT - n_half;
            _UBASIC_T v_buf_lo = v_buf.Region(0, v_buf_lo_count);
            _UBASIC_T v_buf_hi = v_buf.Region(v_buf_lo_count);

            _BASIC_T t1 = temp_buf.Region(current_temp_buf_index, n_half + 1).ToSigned(); current_temp_buf_index += n_half + 1;
            _BASIC_T t2 = temp_buf.Region(current_temp_buf_index, n_half + 1).ToSigned(); current_temp_buf_index += n_half + 1;
            _BASIC_T t3 = w_buf.Region(0, (n_half + 1) * 2).ToSigned();
            _UBASIC_T w_buf2 = temp_buf.Region(current_temp_buf_index, n_half * 4); current_temp_buf_index += n_half * 4;

            _UBASIC_T w_buf2_lo = w_buf2.Region(0, n_half * 2);
            _UBASIC_T w_buf2_hi = w_buf2.Region(n_half * 2);

            Multiply_UX_UX_Karatsuba(root, temp_buf, current_temp_buf_index, u_buf_lo.Shrink(), v_buf_lo.Shrink(), w_buf2_lo);
#ifdef _DEBUG
            root.CheckBlock(temp_buf);
#endif
            Multiply_UX_UX_Karatsuba(root, temp_buf, current_temp_buf_index, u_buf_hi.Shrink(), v_buf_hi.Shrink(), w_buf2_hi);
#ifdef _DEBUG
            root.CheckBlock(temp_buf);
#endif

            _basic_ep.Subtruct(u_buf_hi.ToSigned(), u_buf_lo.ToSigned(), t1);
            _basic_ep.Subtruct(v_buf_hi.ToSigned(), v_buf_lo.ToSigned(), t2);

            Multiply_UX_UX_Karatsuba(root, temp_buf, current_temp_buf_index, t1, t2, t3);
            t3.Negate();
#ifdef _DEBUG
            root.CheckBlock(temp_buf);
#endif

            _basic_ep.Add(t3, w_buf2_hi.ToSigned());
#ifdef _DEBUG
            root.CheckBlock(temp_buf);
#endif

            _basic_ep.Add(t3, w_buf2_lo.ToSigned());
#ifdef _DEBUG
            root.CheckBlock(temp_buf);
#endif


            if (t3.SIGN < 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_multiply_karatsuba.cpp;Multiply_UX_UX_Karatsuba;2");

            _basic_ep.Add(w_buf2.Region(n_half), t3.ABS);

            w_buf.CopyFrom(w_buf2.Shrink());
        }
    }

    void KaratsubaMultiplicationEngine::Multiply_UX_UX_Karatsuba(ResourceHolderUINT & root, _UBASIC_T temp_buf, __UNIT_TYPE current_temp_buf_index, _BASIC_T u_buf, _BASIC_T v_buf, _BASIC_T & w_buf)
    {
        Multiply_UX_UX_Karatsuba(root, temp_buf, current_temp_buf_index, u_buf.ABS.Shrink(), v_buf.ABS.Shrink(), w_buf.ABS);
        w_buf.SIGN = PRODUCT_SIGN(u_buf.SIGN, v_buf.SIGN);
    }

}


/*
 * END OF FILE
 */