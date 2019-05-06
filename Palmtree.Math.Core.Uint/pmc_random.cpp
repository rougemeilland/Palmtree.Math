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
#include "pmc_resourceholder_uint.h"
#include "pmc_sfmt.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    _UINT32_T PMC_GenerateUInt32RandomValue(PMC_HANDLE_SFMT handle)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        return (PMCSFMT_GenerateUInt32RandomValue(state->STATE));
    }

    _UINT64_T PMC_GenerateUInt64RandomValue(PMC_HANDLE_SFMT handle)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        return (PMCSFMT_GenerateUInt64RandomValue(state->STATE));
    }

    double PMC_GenerateDoubleRandomValue(PMC_HANDLE_SFMT handle)
    {
        // double のビット構成：
        // +-----+-----+-----+-----+-----+-----+-----+-----+
        // | 0 0 | 0 f | f f | f f | f f | f f | f f | f f |
        // +-----+-----+-----+-----+-----+-----+-----+-----+
        // | | 指数 | 仮数部
        // 符号

        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
#ifdef _M_IX86
        // 仮数の初期値となる乱数を取得する
        _UINT32_T mantissa_lo = PMCSFMT_GenerateUInt32RandomValue(state->STATE);
        _UINT32_T mantissa_hi = PMCSFMT_GenerateUInt32RandomValue(state->STATE);

        // scale の初期値を取得する
        double invert_scale = 0x8000000000000000 * 2.0;

        // 有効桁数が 53bit 未満の間繰り返す
        while (mantissa_hi < 0x00100000)
        {
            // 下位桁に補充する追加の乱数を取得する
            _UINT32_T additional_mantissa = PMCSFMT_GenerateUInt32RandomValue(state->STATE);

            // 仮数を左に 11bit シフトし、失われた下位 11ビット に追加の乱数を設定する
            mantissa_hi = (mantissa_hi << 11) | (mantissa_lo >> (32 - 11));
            mantissa_lo = (mantissa_lo << 11) | (additional_mantissa & 0x7ff);

            // scaleを 11bit 分だけずらす
            invert_scale *= 0x800;
        }

        // 仮数と scale を合成して復帰値とする
        return ((mantissa_hi * (double)0x100000000 + mantissa_lo) / invert_scale);
#elif defined(_M_X64)
        // 仮数の初期値となる乱数を取得する
        _UINT64_T mantissa = PMCSFMT_GenerateUInt64RandomValue(state->STATE);

        // scale の初期値を取得する
        double invert_scale = 0x8000000000000000 * 2.0;
        
        // 有効桁数が 53bit 未満の間繰り返す
        while (mantissa < 0x0010000000000000)
        {
            // 下位桁に補充する追加の乱数を取得する
            _UINT64_T additional_mantissa = PMCSFMT_GenerateUInt32RandomValue(state->STATE);

            // 仮数を左に 11bit シフトし、失われた下位 11ビット に追加の乱数を設定する
            mantissa = (mantissa << 11) | (additional_mantissa & 0x7ff);

            // scaleを 11bit 分だけずらす
            invert_scale *= 0x800;
        }

        // 仮数と scale を合成して復帰値とする
        return (mantissa / invert_scale);
#else
#error unknown platform
#endif
    }

    PMC_HANDLE_UINT PMC_GenerateUBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderUINT root(tc);

        NUMBER_OBJECT_UINT* nr = root.AllocateNumber(bit_count);
        for (__UNIT_TYPE index = 0; index < nr->BLOCK_COUNT; ++index)
        {
#ifdef _M_IX86
            nr->BLOCK[index] = PMCSFMT_GenerateUInt32RandomValue(state->STATE);
#elif defined(_M_X64)
            nr->BLOCK[index] = PMCSFMT_GenerateUInt64RandomValue(state->STATE);
#else
#error unknown platform
#endif
        }
        if (nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT > (__UNIT_TYPE)bit_count)
        {
            int shift_count = (int)(__UNIT_TYPE_BIT_COUNT - nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT + bit_count);
            __UNIT_TYPE mask = (1UL << shift_count) - 1;
            nr->BLOCK[nr->BLOCK_COUNT - 1] &= mask;
        }
#ifdef _DEBUG
        root.CheckNumber(nr);
#endif
        CommitNumber(tc, nr);
        if (nr->IS_ZERO)
        {
            root.DeallocateNumber(nr);
            nr = &number_object_uint_zero;
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            return (r);
        }
        else
        {
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_GenerateUBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderUINT root(tc);

        NUMBER_OBJECT_UINT* nr = root.AllocateNumber(bit_count);
        size_t byte_count = (bit_count + 7) / 8;
        _COPY_MEMORY_BYTE(nr->BLOCK, data, byte_count);
        if (nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT > (__UNIT_TYPE)bit_count)
        {
            int shift_count = (int)(__UNIT_TYPE_BIT_COUNT - nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT + bit_count);
            __UNIT_TYPE mask = (1UL << shift_count) - 1;
            nr->BLOCK[nr->BLOCK_COUNT - 1] &= mask;
        }
#ifdef _DEBUG
        root.CheckNumber(nr);
#endif
        CommitNumber(tc, nr);
        if (nr->IS_ZERO)
        {
            root.DeallocateNumber(nr);
            nr = &number_object_uint_zero;
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            return (r);
        }
        else
        {
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

}


/*
 * END OF FILE
 */