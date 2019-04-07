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


#include "pmc_tostringformatter.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{
    ToStringFormatter::ToStringFormatter(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
    {
        _format_type = format_type;
        _precision = precision;
        _number_format_info = number_format_info;
        _omitted_trailing_sequential_zero = false;
    }

    void ToStringFormatter::Format(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, StringWriter * writer)
    {
        _precision = GetDefaultPrecisionValue(_precision);

        if (x_denominator->IS_ZERO)
            throw DivisionByZeroException(L"数値の分母が 0 になっています。");

        if (x_numerator->IS_ZERO)
        {
            // x == 0 の場合
            if (x_sign != 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;Formatter::Format;1");
            WritePrefix(x_sign, writer);
            WriteZeroValue(writer);
            WriteSuffix(x_sign, writer);
        }
        else
        {
            // x != 0 の場合
            if (x_sign == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;Formatter::Format;1");

            ResourceHolderUINT root;

            // 丸め処理をする
            _INT32_T exp;
            RoundValue(x_numerator, x_denominator, &x_numerator, &x_denominator, &exp);
            root.HookNumber(x_numerator);
            root.HookNumber(x_denominator);
            if (x_numerator->IS_ZERO)
            {
                // 丸めの結果が 0 になったら符号も 0 に変更する。
                x_sign = SIGN_ZERO;
                WritePrefix(x_sign, writer);
                WriteZeroValue(writer);
                WriteSuffix(x_sign, writer);
            }
            else
            {
                WritePrefix(x_sign, writer);
                FormatInternally(x_numerator, x_denominator, exp, writer);
                WriteSuffix(x_sign, writer);
            }
        }
    }

    void ToStringFormatter::FormatInternally(NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, _INT32_T exp, StringWriter * writer)
    {
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* frac_part_denominator = x_denominator;
        NUMBER_OBJECT_UINT* int_part;
        NUMBER_OBJECT_UINT* frac_part_numerator = PMC_DivRem_UX_UX_Imp(x_numerator, x_denominator, &int_part);
        root.HookNumber(int_part);
        root.HookNumber(frac_part_numerator);
        __UNIT_TYPE int_part_buffer_size = int_part->IS_ZERO ? 1 : PMC_FloorLog10_UX_Imp(int_part) + 1;
        int_part_buffer_size = int_part_buffer_size * 2 + 1; // 3桁区切り記号と終端ヌル文字の分のサイズを追加
        wchar_t* int_part_buffer = root.AllocateString(int_part_buffer_size);

        // 小数部の最大長は precision +3
        //    書式がg/Gの場合、指数部が -5 以下の場合は指数表現形式となるので小数部の長さは precision - 1
        //                     指数部が precision 以上の場合も指数表現形式となるので小数部の長さは precision - 1
        //                     それ以外の場合の小数部の長さは、指数部が -4 となる数値を固定小数点で表示した場合で、precision + 3 となる
        //    書式がg/G以外の場合、precisionは小数部の長さとして扱われるので、最大長は precision である
        // すべての書式を総合すると、小数部の長さは precision + 3 ということになる
        size_t frac_part_buffer_size = _precision + 3 + 1;

        wchar_t* frac_part_buffer = root.AllocateString(frac_part_buffer_size);
        wchar_t* top_of_int_part = ConstructIntegerPartNumberSequence(int_part, int_part_buffer, int_part_buffer_size);
        root.CheckString(int_part_buffer);
        ConstructFractionPartNumberSequence(frac_part_numerator, frac_part_denominator, GetFractionPartLength(), frac_part_buffer, frac_part_buffer_size);
        root.CheckString(frac_part_buffer);
        FormatNumberSequence(top_of_int_part, frac_part_buffer, exp, writer);
    }

    // 小数点以下の丸め処理 (および必要なら小数点位置の移動) を行います。
    void ToStringFormatter::RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT* * r_numerator, NUMBER_OBJECT_UINT* * r_denominator, _INT32_T * exp)
    {
        *r_numerator = PMC_Round_R_Imp(x_numerator, x_denominator, _precision, PMC_MIDPOINT_ROUNDING_HALF_EVEN, r_denominator);
        *exp = 0;
    }

    // 現在の書式における小数部の長さを返します。
    size_t ToStringFormatter::GetFractionPartLength()
    {
        return (_precision);
    }

    wchar_t * ToStringFormatter::ConstructIntegerPartNumberSequence(NUMBER_OBJECT_UINT* int_part, wchar_t * out_buf, size_t out_buf_count)
    {
        ReverseStringWriter simple_number_sequence_writer(out_buf, out_buf_count);

        while (true)
        {
#ifdef _M_IX86
            __UNIT_TYPE data = PMC_DivRem_UX_UI_Imp(int_part, _10n_base_number, &int_part);
#elif defined(_M_X64)
            __UNIT_TYPE data = PMC_DivRem_UX_UL_Imp(int_part, _10n_base_number, &int_part);
#else
#error unknown platform
#endif
            if (int_part->IS_ZERO)
            {
                WriteIntPartLeadingOneWord(&simple_number_sequence_writer, data);
                break;
            }
            WriteIntPartTrailingWord(&simple_number_sequence_writer, data);
        }
        return (simple_number_sequence_writer.GetString());
    }

    void ToStringFormatter::ConstructFractionPartNumberSequence(NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator, size_t max_fraction_part_length, wchar_t * out_buf, size_t out_buf_count)
    {
        StringWriter simple_number_sequence_writer(out_buf, out_buf_count);
        ResourceHolderUINT root;

        size_t fraction_part_length = max_fraction_part_length;

        while (!frac_part_numerator->IS_ZERO)
        {
#ifdef _M_IX86
            frac_part_numerator = PMC_Multiply_UX_UI_Imp(frac_part_numerator, _10n_base_number);
#elif defined(_M_X64)
            frac_part_numerator = PMC_Multiply_UX_UL_Imp(frac_part_numerator, _10n_base_number);
#else
#error unknown platform
#endif
            root.HookNumber(frac_part_numerator);
            NUMBER_OBJECT_UINT* digit;
            frac_part_numerator = PMC_DivRem_UX_UX_Imp(frac_part_numerator, frac_part_denominator, &digit);
            root.HookNumber(digit);
            root.HookNumber(frac_part_numerator);

            if (fraction_part_length >= digit_count_on_word)
            {
                // digit を digit_count_on_word 桁の 10 進整数として数字列を書き込む
                if (digit->UNIT_WORD_COUNT > 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformatter.cpp;ConstructFractionPartNumberSequence;1");
                __UNIT_TYPE digit_word = digit->BLOCK[0];
                WriteFracPartLeadingWord(&simple_number_sequence_writer, digit_word);
                fraction_part_length -= digit_count_on_word;
            }
            else
            {
                // digit を digit_count_on_word 桁の 10 進整数として、上位から fraction_part_length 桁だけ数字列を書き込む
                if (digit->UNIT_WORD_COUNT > 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformatter.cpp;ConstructFractionPartNumberSequence;2");
                __UNIT_TYPE digit_word = digit->BLOCK[0];
                WriteFracPartTrailingOneWord(&simple_number_sequence_writer, digit_word, fraction_part_length);
                fraction_part_length = 0;
                break;
            }
        }
        if (_omitted_trailing_sequential_zero)
        {
            // 末尾の連続する 0 を削除する指定がされている場合は削除する
            wchar_t* tail = out_buf + lstrlenW(out_buf);
            while (tail > out_buf && tail[-1] == L'0')
            {
                --tail;
                *tail = L'\0';
            }
        }
        else
        {
            // fraction_part_length 桁だけ '0' で埋める
            simple_number_sequence_writer.Write(L'0', fraction_part_length);
        }
    }

    // 整数部の最上位のワードを文字列化する。(途中で x が 0 になった場合は中断する)

    void ToStringFormatter::WriteIntPartLeadingOneWord(StringWriter * writer, __UNIT_TYPE x)
    {
        __UNIT_TYPE r;
        do
        {
            x = _DIVREM_UNIT(0, x, 10, &r);
            WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                IncrementDIV64Counter();
            else
                IncrementDIV32Counter();
#endif
        } while (x != 0);
    }

    // 整数部の上位から 2 ワード目以降を文字列化する。(途中で x が 0 になっても続行する)

    void ToStringFormatter::WriteIntPartTrailingWord(StringWriter * writer, __UNIT_TYPE x)
    {
        __UNIT_TYPE r;
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(10);
            else
                AddToDIV32Counter(10);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(5);
            else
                AddToDIV32Counter(5);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                AddToDIV64Counter(2);
            else
                AddToDIV32Counter(2);
#endif
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
        {
            x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
            WriteDigit(writer, (_UINT32_T)x);
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(r) == sizeof(_UINT64_T))
                IncrementDIV64Counter();
            else
                IncrementDIV32Counter();
#endif
        }
    }

    // 小数部の最下位のワードを文字列化する。(count 桁で打ち切る)

    void ToStringFormatter::WriteFracPartTrailingOneWord(StringWriter * writer, __UNIT_TYPE x, size_t count)
    {
        __UNIT_TYPE q;
#if _M_X64
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
        if (count <= 0) return; q = x; WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            IncrementDIV64Counter();
        else
            IncrementDIV32Counter();
#endif
    }

    // 小数部の最下位ワード以外のワードを文字列化する。(digit_count_on_word 桁だけ続ける)

    inline void ToStringFormatter::WriteFracPartLeadingWord(StringWriter * writer, __UNIT_TYPE x)
    {
        __UNIT_TYPE q;
#if _M_X64
        q = _DIVREM_UNIT(0, x, 1000000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 100000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 1000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 100000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 1000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 100000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 1000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
#endif
        q = _DIVREM_UNIT(0, x, 100000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 1000000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 100000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 1000U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 100U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = _DIVREM_UNIT(0, x, 10U, &x); WriteDigit(writer, (_UINT32_T)q);
        q = x; WriteDigit(writer, (_UINT32_T)q);
#ifdef ENABLED_PERFORMANCE_COUNTER
        if (sizeof(q) == sizeof(_UINT64_T))
            AddToDIV64Counter((int)digit_count_on_word);
        else
            AddToDIV32Counter((int)digit_count_on_word);
#endif
    }
    inline void ToStringFormatter::WriteDigit(StringWriter * writer, _UINT32_T d)
    {
        writer->Write(L'0' + d);
    }
}

/*
 * END OF FILE
 */