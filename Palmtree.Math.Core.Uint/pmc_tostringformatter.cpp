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
#include "pmc_tostringformatter.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_threadcontext.h"
#include "pmc_string.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{
    ToStringFormatter::ToStringFormatter(ThreadContext& tc, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : _tc(tc)
    {
        _format_type = format_type;
        _precision = precision;
        _number_format_info = number_format_info;
        _omitted_trailing_sequential_zero = false;
    }

    void ToStringFormatter::Format(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, StringWriter& writer)
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

            ResourceHolderUINT root(_tc);

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

    void ToStringFormatter::FormatInternally(NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, _INT32_T exp, StringWriter& writer)
    {
        ResourceHolderUINT root(_tc);
        NUMBER_OBJECT_UINT* frac_part_denominator = x_denominator;
        NUMBER_OBJECT_UINT* int_part;
        NUMBER_OBJECT_UINT* frac_part_numerator = PMC_DivRem_UX_UX_Imp(_tc, x_numerator, x_denominator, &int_part);
        root.HookNumber(int_part);
        root.HookNumber(frac_part_numerator);
        __UNIT_TYPE int_part_buffer_size = int_part->IS_ZERO ? 1 : PMC_FloorLog10_UX_Imp(_tc, int_part) + 1;
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
#ifdef _DEBUG
        root.CheckString(int_part_buffer);
#endif
        ConstructFractionPartNumberSequence(frac_part_numerator, frac_part_denominator, GetFractionPartLength(), frac_part_buffer, frac_part_buffer_size);
#ifdef _DEBUG
        root.CheckString(frac_part_buffer);
#endif
        FormatNumberSequence(top_of_int_part, frac_part_buffer, exp, writer);
    }

    // 小数点以下の丸め処理 (および必要なら小数点位置の移動) を行います。
    void ToStringFormatter::RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT* * r_numerator, NUMBER_OBJECT_UINT* * r_denominator, _INT32_T * exp)
    {
        *r_numerator = PMC_Round_R_Imp(_tc, x_numerator, x_denominator, _precision, PMC_GetDefaultRoundingMode(), r_denominator);
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
        if (int_part->IS_ZERO)
            simple_number_sequence_writer.Write(L"0");
        else
            PMC_LToA_Imp(_tc, int_part, simple_number_sequence_writer);
        return (simple_number_sequence_writer.GetString());
    }

    void ToStringFormatter::ConstructFractionPartNumberSequence(NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator, size_t max_fraction_part_length, wchar_t * out_buf, size_t out_buf_count)
    {
        StringWriter simple_number_sequence_writer(out_buf, out_buf_count);
        PMC_FToA_Imp(_tc, frac_part_numerator, frac_part_denominator, max_fraction_part_length, simple_number_sequence_writer);
        if (!_omitted_trailing_sequential_zero)
        {
            // fraction_part_length 桁だけ '0' で埋める
            size_t written_digit_count = lstrlenW(out_buf);
            if (written_digit_count < max_fraction_part_length)
                simple_number_sequence_writer.Write(L'0', max_fraction_part_length - written_digit_count);
        }
    }

}

/*
 * END OF FILE
 */