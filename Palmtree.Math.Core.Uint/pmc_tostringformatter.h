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


#pragma once

#ifndef PMC_TOSTRING_FORMATTER_H
#define PMC_TOSTRING_FORMATTER_H


#include "pmc_uint_internal.h"
#include "pmc_stringio.h"


namespace Palmtree::Math::Core::Internal
{

    class ToStringFormatter
    {
    private:
#ifdef _M_IX86
        const __UNIT_TYPE _10n_base_number = 1000000000U; // 10^9
        const size_t digit_count_on_word = 9;
#elif defined (_M_X64)
        const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
        const size_t digit_count_on_word = 19;
#else
#error unknown platform
#endif

    protected:
        wchar_t _format_type;
        int _precision;
        const PMC_NUMBER_FORMAT_INFO* _number_format_info;
        bool _omitted_trailing_sequential_zero; // 最下位の連続する 0 を省略する (書式 g/G の場合のみ)

    protected:
        ToStringFormatter(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info);

    public:
        void Format(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, StringWriter& writer);

    protected:
        virtual int GetDefaultPrecisionValue(int specified_precision) = 0;

        virtual void FormatInternally(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, _INT32_T exp, StringWriter& writer);

        // 0 値を表す文字列を writer に設定します。
        virtual void WriteZeroValue(StringWriter& writer) = 0;

        // 小数点以下の丸め処理 (および必要なら小数点位置の移動) を行います。
        virtual void RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT** r_numerator, NUMBER_OBJECT_UINT** r_denominator, _INT32_T* exp);

        // 現在の書式における小数部の長さを返します。
        virtual size_t GetFractionPartLength();

        // 数値の前に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
        virtual void WritePrefix(SIGN_T x_sign, StringWriter& writer) = 0;

        // 整数部を表す単純な数字列を書式に応じて変換し、StringWriterに書き込みます。(例: precision に応じた 0 パディング、3桁区切り、小数点、小数、指数表記、など)
        virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter& writer) = 0;

        // 数値の後に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
        virtual void WriteSuffix(SIGN_T x_sign, StringWriter& writer) = 0;

    private:
        wchar_t* ConstructIntegerPartNumberSequence(NUMBER_OBJECT_UINT* int_part, wchar_t* out_buf, size_t out_buf_count);

        void ConstructFractionPartNumberSequence(NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator, size_t max_fraction_part_length, wchar_t* out_buf, size_t out_buf_count);

    };

}


#endif


/*
 * END OF FILE
 */