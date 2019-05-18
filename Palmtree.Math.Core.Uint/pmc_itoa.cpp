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

#include "pmc_string.h"
#include "pmc_resourceholder_uint.h"
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

    static void WriteDigit(_UINT32_T d, StringWriter& writer)
    {
        writer.Write(L'0' + d);
    }

    // 数値 x を10進文字列として writer へ書き込む (数値が 0 の場合は何も書き込まない)
    void PMC_ItoA(__UNIT_TYPE x, ReverseStringWriter& writer)
    {
        if (x == 0)
            return;

        __UNIT_TYPE r;
        do
        {
            x = _DIVREM_UNIT(0, x, 10, &r);
            WriteDigit((_UINT32_T)r, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                IncrementDIV64Counter();
            else
                IncrementDIV32Counter();
#endif
        } while (x != 0);
    }

    // 整数部の上位から 2 ワード目以降を文字列化する。(途中で x が 0 になっても続行する)
    static void WriteIntPartTrailingWord(__UNIT_TYPE x, ReverseStringWriter& writer)
    {
        __UNIT_TYPE r;
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(10);
            else
                AddToDIV32Counter(10);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(5);
            else
                AddToDIV32Counter(5);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(2);
            else
                AddToDIV32Counter(2);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit((_UINT32_T)r, writer);
            WriteDigit((_UINT32_T)x, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                IncrementDIV64Counter();
            else
                IncrementDIV32Counter();
#endif
        }
    }

    // 数値 int_part を10進文字列として writer へ書き込む (数値が 0 の場合は何も書き込まない)
    void PMC_LToA_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* int_part, ReverseStringWriter& writer)
    {
        if (int_part->IS_ZERO)
            return;

        ResourceHolderUINT root(tc);

        while (true)
        {
#ifdef _M_IX86
            __UNIT_TYPE data = PMC_DivRem_UX_UI_Imp(tc, int_part, _10n_base_number, &int_part);
#elif defined(_M_X64)
            __UNIT_TYPE data = PMC_DivRem_UX_UL_Imp(tc, int_part, _10n_base_number, &int_part);
#else
#error unknown platform
#endif
            root.HookNumber(int_part);
            if (int_part->IS_ZERO)
            {
                PMC_ItoA(data, writer);
                break;
            }
            else
                WriteIntPartTrailingWord(data, writer);
        }
    }


    // 小数部の最下位のワードを文字列化する。(count 桁になるか、あるいは x== 0 で打ち切る)
    static void WriteFracPartTrailingOneWord(__UNIT_TYPE x, size_t count, StringWriter& writer)
    {
        __UNIT_TYPE q;
#ifdef _M_X64
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 1000UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 100UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = _DIVREM_UNIT(0, x, 10UL, &x); WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (x == 0 || count <= 0) return; q = x; WriteDigit((_UINT32_T)q, writer); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
    }

    // 小数部の最下位ワード以外のワードを文字列化する。(_digit_count_on_word 桁だけ続ける)
    static void WriteFracPartLeadingWord(__UNIT_TYPE x, StringWriter& writer)
    {
        __UNIT_TYPE q;
#ifdef _M_X64
        q = _DIVREM_UNIT(0, x, 1000000000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 100000000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10000000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 1000000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 100000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 1000000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 100000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10000000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 1000000000U, &x); WriteDigit((_UINT32_T)q, writer);
#endif
        q = _DIVREM_UNIT(0, x, 100000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 1000000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 100000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 1000U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 100U, &x); WriteDigit((_UINT32_T)q, writer);
        q = _DIVREM_UNIT(0, x, 10U, &x); WriteDigit((_UINT32_T)q, writer);
        q = x; WriteDigit((_UINT32_T)q, writer);
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            AddToDIV64Counter((int)_digit_count_on_word);
        else
            AddToDIV32Counter((int)_digit_count_on_word);
#endif
    }

    // frac_part を最大で max_fraction_part_length 桁だけ文字列化する。末尾の 0 は省略する。
    void PMC_FToA_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator, size_t max_fraction_part_length, StringWriter& simple_number_sequence_writer)
    {
        if (frac_part_numerator->IS_ZERO)
            return;

        ResourceHolderUINT root(tc);

        size_t fraction_part_length = max_fraction_part_length;

        while (true)
        {
#ifdef _M_IX86
            frac_part_numerator = PMC_Multiply_UX_UI_Imp(tc, frac_part_numerator, _10n_base_number);
#elif defined(_M_X64)
            frac_part_numerator = PMC_Multiply_UX_UL_Imp(tc, frac_part_numerator, _10n_base_number);
#else
#error unknown platform
#endif
            root.HookNumber(frac_part_numerator);
            NUMBER_OBJECT_UINT* digit;
            frac_part_numerator = PMC_DivRem_UX_UX_Imp(tc, frac_part_numerator, frac_part_denominator, &digit);
            root.HookNumber(digit);
            root.HookNumber(frac_part_numerator);

            if (!frac_part_numerator->IS_ZERO && fraction_part_length >= _digit_count_on_word)
            {
                // digit を _digit_count_on_word 桁の 10 進整数として数字列を書き込む
                if (digit->UNIT_WORD_COUNT > 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_itoa.cpp;PMC_FToA_Imp;1");
                __UNIT_TYPE digit_word = digit->IS_ZERO ? 0 : digit->BLOCK[0];
                WriteFracPartLeadingWord(digit_word, simple_number_sequence_writer);
                fraction_part_length -= _digit_count_on_word;
            }
            else
            {
                // digit を _digit_count_on_word 桁の 10 進整数として、上位から fraction_part_length 桁だけ数字列を書き込む
                if (digit->UNIT_WORD_COUNT > 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_itoa.cpp;PMC_FToA_Imp;2");
                __UNIT_TYPE digit_word = digit->IS_ZERO ? 0 : digit->BLOCK[0];
                WriteFracPartTrailingOneWord(digit_word, fraction_part_length, simple_number_sequence_writer);
                break;
            }
        }
    }

}

/*
 * END OF FILE
 */