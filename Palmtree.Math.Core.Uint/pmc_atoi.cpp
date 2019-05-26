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

#include <windows.h>
#include "pmc_string.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_parser.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

#ifdef _M_IX86
    static const __UNIT_TYPE _10n_base_number = 1000000000U; // 10^9
    static const size_t _digit_count_on_word = 9;
#elif defined (_M_X64)
    static const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
    static const size_t _digit_count_on_word = 19;
#else
#error unknown platform
#endif

    __inline static __UNIT_TYPE MultiplyAndAdd1Word(__UNIT_TYPE k, __UNIT_TYPE u, __UNIT_TYPE* w_buf)
    {
        __UNIT_TYPE t_hi;
        __UNIT_TYPE t_lo = _MULTIPLY_UNIT(u, _10n_base_number, &t_hi);
        _ADD_UNIT(_ADD_UNIT(0, t_lo, k, w_buf), t_hi, 0, &k);
        return (k);
    }

    static __UNIT_TYPE* MultiplyAndAdd(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE x)
    {
        __UNIT_TYPE* u_ptr = u_buf;
        __UNIT_TYPE u_count= u_buf_count;
        __UNIT_TYPE k = x;
        __UNIT_TYPE count = u_count >> 5;
        while (count > 0)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            k = MultiplyAndAdd1Word(k, u_ptr[1], &u_ptr[1]);
            k = MultiplyAndAdd1Word(k, u_ptr[2], &u_ptr[2]);
            k = MultiplyAndAdd1Word(k, u_ptr[3], &u_ptr[3]);
            k = MultiplyAndAdd1Word(k, u_ptr[4], &u_ptr[4]);
            k = MultiplyAndAdd1Word(k, u_ptr[5], &u_ptr[5]);
            k = MultiplyAndAdd1Word(k, u_ptr[6], &u_ptr[6]);
            k = MultiplyAndAdd1Word(k, u_ptr[7], &u_ptr[7]);
            k = MultiplyAndAdd1Word(k, u_ptr[8], &u_ptr[8]);
            k = MultiplyAndAdd1Word(k, u_ptr[9], &u_ptr[9]);
            k = MultiplyAndAdd1Word(k, u_ptr[10], &u_ptr[10]);
            k = MultiplyAndAdd1Word(k, u_ptr[11], &u_ptr[11]);
            k = MultiplyAndAdd1Word(k, u_ptr[12], &u_ptr[12]);
            k = MultiplyAndAdd1Word(k, u_ptr[13], &u_ptr[13]);
            k = MultiplyAndAdd1Word(k, u_ptr[14], &u_ptr[14]);
            k = MultiplyAndAdd1Word(k, u_ptr[15], &u_ptr[15]);
            k = MultiplyAndAdd1Word(k, u_ptr[16], &u_ptr[16]);
            k = MultiplyAndAdd1Word(k, u_ptr[17], &u_ptr[17]);
            k = MultiplyAndAdd1Word(k, u_ptr[18], &u_ptr[18]);
            k = MultiplyAndAdd1Word(k, u_ptr[19], &u_ptr[19]);
            k = MultiplyAndAdd1Word(k, u_ptr[20], &u_ptr[20]);
            k = MultiplyAndAdd1Word(k, u_ptr[21], &u_ptr[21]);
            k = MultiplyAndAdd1Word(k, u_ptr[22], &u_ptr[22]);
            k = MultiplyAndAdd1Word(k, u_ptr[23], &u_ptr[23]);
            k = MultiplyAndAdd1Word(k, u_ptr[24], &u_ptr[24]);
            k = MultiplyAndAdd1Word(k, u_ptr[25], &u_ptr[25]);
            k = MultiplyAndAdd1Word(k, u_ptr[26], &u_ptr[26]);
            k = MultiplyAndAdd1Word(k, u_ptr[27], &u_ptr[27]);
            k = MultiplyAndAdd1Word(k, u_ptr[28], &u_ptr[28]);
            k = MultiplyAndAdd1Word(k, u_ptr[29], &u_ptr[29]);
            k = MultiplyAndAdd1Word(k, u_ptr[30], &u_ptr[30]);
            k = MultiplyAndAdd1Word(k, u_ptr[31], &u_ptr[31]);
            u_ptr += 32;
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(32);
            else
                AddToMULTI64Counter(32);
#endif
        }

        if (u_count & 0x10)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            k = MultiplyAndAdd1Word(k, u_ptr[1], &u_ptr[1]);
            k = MultiplyAndAdd1Word(k, u_ptr[2], &u_ptr[2]);
            k = MultiplyAndAdd1Word(k, u_ptr[3], &u_ptr[3]);
            k = MultiplyAndAdd1Word(k, u_ptr[4], &u_ptr[4]);
            k = MultiplyAndAdd1Word(k, u_ptr[5], &u_ptr[5]);
            k = MultiplyAndAdd1Word(k, u_ptr[6], &u_ptr[6]);
            k = MultiplyAndAdd1Word(k, u_ptr[7], &u_ptr[7]);
            k = MultiplyAndAdd1Word(k, u_ptr[8], &u_ptr[8]);
            k = MultiplyAndAdd1Word(k, u_ptr[9], &u_ptr[9]);
            k = MultiplyAndAdd1Word(k, u_ptr[10], &u_ptr[10]);
            k = MultiplyAndAdd1Word(k, u_ptr[11], &u_ptr[11]);
            k = MultiplyAndAdd1Word(k, u_ptr[12], &u_ptr[12]);
            k = MultiplyAndAdd1Word(k, u_ptr[13], &u_ptr[13]);
            k = MultiplyAndAdd1Word(k, u_ptr[14], &u_ptr[14]);
            k = MultiplyAndAdd1Word(k, u_ptr[15], &u_ptr[15]);
            u_ptr += 16;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(16);
            else
                AddToMULTI64Counter(16);
#endif
        }

        if (u_count & 0x8)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            k = MultiplyAndAdd1Word(k, u_ptr[1], &u_ptr[1]);
            k = MultiplyAndAdd1Word(k, u_ptr[2], &u_ptr[2]);
            k = MultiplyAndAdd1Word(k, u_ptr[3], &u_ptr[3]);
            k = MultiplyAndAdd1Word(k, u_ptr[4], &u_ptr[4]);
            k = MultiplyAndAdd1Word(k, u_ptr[5], &u_ptr[5]);
            k = MultiplyAndAdd1Word(k, u_ptr[6], &u_ptr[6]);
            k = MultiplyAndAdd1Word(k, u_ptr[7], &u_ptr[7]);
            u_ptr += 8;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(8);
            else
                AddToMULTI64Counter(8);
#endif
        }

        if (u_count & 0x4)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            k = MultiplyAndAdd1Word(k, u_ptr[1], &u_ptr[1]);
            k = MultiplyAndAdd1Word(k, u_ptr[2], &u_ptr[2]);
            k = MultiplyAndAdd1Word(k, u_ptr[3], &u_ptr[3]);
            u_ptr += 4;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(4);
            else
                AddToMULTI64Counter(4);
#endif
        }

        if (u_count & 0x2)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            k = MultiplyAndAdd1Word(k, u_ptr[1], &u_ptr[1]);
            u_ptr += 2;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }

        if (u_count & 0x1)
        {
            k = MultiplyAndAdd1Word(k, u_ptr[0], &u_ptr[0]);
            u_ptr += 1;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }

        if (k > 0)
        {
            u_ptr[0] = k;
            u_ptr += 1;
        }

        return (u_ptr);
    }

    static __UNIT_TYPE BuildLeading1WordFromDecimalString(const wchar_t* in_ptr, __UNIT_TYPE count)
    {
        __UNIT_TYPE x = 0;
        while (count > 0)
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }
        return (x);
    }

    static __UNIT_TYPE Build1WordFromDecimalString(const wchar_t* in_ptr)
    {
        __UNIT_TYPE x = ParseDecimalDigit(*in_ptr++);
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                AddToMULTI32Counter(10);
            else
                AddToMULTI64Counter(10);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                AddToMULTI32Counter(5);
            else
                AddToMULTI64Counter(5);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }
        return (x);
    }

    // 16進数の数値を表す文字列から整数部を抽出する。
    // 10進整数を表す文字列を、word_digit_count 毎に 1 ワードずつ分割してバイナリー化し、out_buf に格納する。
    static void BuildBinaryFromDecimalString(const wchar_t* source, __UNIT_TYPE* out_buf, __UNIT_TYPE out_buf_count)
    {
#ifdef _M_IX86
        int word_digit_count = 9;
#elif defined(_M_X64)
        int word_digit_count = 19;
#else
#error unknown platform
#endif
        const wchar_t* in_ptr = source;
        __UNIT_TYPE* out_ptr = out_buf;
        __UNIT_TYPE source_count = lstrlenW(source);
        int r = source_count % word_digit_count;
        if (r > 0)
        {
            *out_ptr++ = BuildLeading1WordFromDecimalString(in_ptr, r);
            in_ptr += r;
            source_count -= r;
        }
        while (source_count > 0)
        {
            *out_ptr++ = Build1WordFromDecimalString(in_ptr);
            in_ptr += word_digit_count;
            source_count -= word_digit_count;
        }
        _ZERO_MEMORY_UNIT(out_ptr, out_buf + out_buf_count - out_ptr);
    }

    static void ConvertCardinalNumber(ThreadContext& tc, __UNIT_TYPE* in_buf, __UNIT_TYPE in_buf_count, __UNIT_TYPE* out_buf, __UNIT_TYPE out_buf_count)
    {
        ResourceHolderUINT root(tc);
        __UNIT_TYPE* work_buf = root.AllocateBlock(in_buf_count + 1);
        __UNIT_TYPE work_buf_count = 1;
        work_buf[0] = in_buf[0];
        __UNIT_TYPE* in_ptr = in_buf + 1;
        __UNIT_TYPE in_count = in_buf_count - 1;
        while (in_count > 0)
        {
            __UNIT_TYPE* w_tail = MultiplyAndAdd(work_buf, work_buf_count, *in_ptr);
            work_buf_count = w_tail - work_buf;
            ++in_ptr;
            --in_count;
        }
#ifdef _DEBUG
        root.CheckBlock(work_buf);
#endif
        _COPY_MEMORY_UNIT(out_buf, work_buf, work_buf_count);
        _ZERO_MEMORY_UNIT(out_buf + work_buf_count, out_buf_count - work_buf_count);
    }

    NUMBER_OBJECT_UINT* PMC_AToL_Imp(ThreadContext& tc, const wchar_t* source)
    {
        ResourceHolderUINT root(tc);
        // 整数部を 10^word_digit_count を基数としたバイト列に変換する
        __UNIT_TYPE bin_buf_count = _DIVIDE_CEILING_SIZE(lstrlenW(source), _digit_count_on_word);
        __UNIT_TYPE* bin_buf = root.AllocateBlock(bin_buf_count);
        BuildBinaryFromDecimalString(source, bin_buf, bin_buf_count);

        // 10^word_digit_count を基数としたバイト列を 10 を基数としたバイト列に変換する
        NUMBER_OBJECT_UINT* nr = root.AllocateNumber(bin_buf_count);
        _ZERO_MEMORY_UNIT(nr->BLOCK, nr->BLOCK_COUNT);
        ConvertCardinalNumber(tc, bin_buf, bin_buf_count, nr->BLOCK, nr->BLOCK_COUNT);
#ifdef _DEBUG
        root.CheckNumber(nr);
#endif
        CommitNumber(tc, nr);

        if (nr->IS_ZERO)
        {
            nr = &number_object_uint_zero;
            root.HookNumber(nr);
        }
        root.UnlinkNumber(nr);
        return (nr);
    }

    __UNIT_TYPE PMC_AToI(const wchar_t* source)
    {
        __UNIT_TYPE x = 0;
        while (*source != L'\0')
        {
            x = x * 10 + ParseDecimalDigit(*source);
            ++source;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(x) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }
        return (x);
    }

    PMC_HANDLE_UINT PMC_AToL(ThreadContext& tc, const wchar_t* source)
    {
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nr = PMC_AToL_Imp(tc, source);
        root.HookNumber(nr);
        PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_STATUS_CODE Initialize_AToI(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}

/*
 * END OF FILE
 */