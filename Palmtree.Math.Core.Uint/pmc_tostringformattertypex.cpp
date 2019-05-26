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

#include "pmc_tostringformattertypex.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    static wchar_t hexadecimal_lower_digits[] = L"0123456789abcdef";
    static wchar_t hexadecimal_upper_digits[] = L"0123456789ABCDEF";

    static void OutputHexNumberSequenceOneWord(__UNIT_TYPE x, unsigned int skip_digit_len, const wchar_t* digit_table, StringWriter& writer)
    {
        if (sizeof(__UNIT_TYPE) > sizeof(_UINT64_T))
        {
            // 64bit を超える __UNIT_TYPE には未対応
            // 対応するには以降のコーディングを見直す必要がある
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_tostringformattertypex.cpp;OutputHexNumberSequenceOneWord;1");
        }
        unsigned int count = __UNIT_TYPE_BIT_COUNT / 4;
        if (skip_digit_len > 0)
        {
            x = _ROTATE_L_UNIT(x, 4 * skip_digit_len);
            count -= skip_digit_len;
        }
        if (count & 0x10)
        {
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
        }
        if (count & 0x8)
        {
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
        }
        if (count & 0x4)
        {
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
        }
        if (count & 0x2)
        {
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
        }
        if (count & 0x1)
        {
            x = _ROTATE_L_UNIT(x, 4); writer.Write(digit_table[x & 0x0f]);
        }
    }

    ToStringFormatterTypeX::ToStringFormatterTypeX(ThreadContext& tc, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : _tc(tc)
    {
        _format_type = format_type;
        _precision = GetDefaultPrecisionValue(precision);
        _number_format_info = number_format_info;
        _character_set = _format_type == L'X' ? hexadecimal_upper_digits : hexadecimal_lower_digits;
    }

    void ToStringFormatterTypeX::Format(SIGN_T x_sign, NUMBER_OBJECT_UINT * x_abs, StringWriter& writer)
    {
        if (x_abs->IS_ZERO)
        {
            // x == 0 の場合

            WriteZeroValue(writer);
        }
        else
        {
            // x != 0 の場合

            WriteValue(x_sign, x_abs, writer);
        }
    }

    int ToStringFormatterTypeX::GetDefaultPrecisionValue(int specified_precision)
    {
        return (specified_precision >= 0 ? specified_precision : 0);
    }

    void ToStringFormatterTypeX::WriteZeroValue(StringWriter& writer)
    {
        writer.Write(L'0', _precision < 1 ? 1 : _precision);
    }

    void ToStringFormatterTypeX::WriteValue(SIGN_T x_sign, NUMBER_OBJECT_UINT * x_abs, StringWriter& writer)
    {
        ResourceHolderUINT root(_tc);
        __UNIT_TYPE temp_buf_count = x_abs->UNIT_WORD_COUNT + 1;
        __UNIT_TYPE* temp_buf = root.AllocateBlock(temp_buf_count);
        __UNIT_TYPE output_len;
        wchar_t filling_char;
        if (x_sign >= 0)
        {
            // x >= 0 の場合

            _COPY_MEMORY_UNIT(temp_buf, x_abs->BLOCK, x_abs->UNIT_WORD_COUNT);
            _ZERO_MEMORY_UNIT(temp_buf + x_abs->UNIT_WORD_COUNT, temp_buf_count - x_abs->UNIT_WORD_COUNT);
            output_len = temp_buf_count * (__UNIT_TYPE_BIT_COUNT / 4);
            unsigned char* ptr = (unsigned char*)&temp_buf[temp_buf_count] - 1;
            while (ptr >= (unsigned char*)temp_buf)
            {
                if ((ptr[0] >> 4) != 0 || (ptr[0] & 0xf) >= 0x8)
                    break;
                // 最上位桁が '0' で、かつ次の桁が '0'～'7'である場合
                // ⇒最上位桁の '0' を削除する
                --output_len;

                if (&ptr[-1] < (unsigned char*)temp_buf)
                    break;

                if (ptr[0] != 0 || (ptr[-1] >> 4) >= 0x8)
                    break;
                // 最上位桁が '0' で、かつ次の桁が '0'～'7'である場合
                // ⇒最上位桁の '0' を削除する
                --output_len;

                --ptr;
            }
            filling_char = _character_set[0];
        }
        else
        {
            // x < 0 の場合

            __UNIT_TYPE *in_ptr = x_abs->BLOCK;
            __UNIT_TYPE *out_ptr = temp_buf;
            __UNIT_TYPE count1 = x_abs->UNIT_WORD_COUNT;
            __UNIT_TYPE count2 = temp_buf_count;
            __CARRY_T carry = 1;
            while (count1 > 0)
            {
                carry = _ADD_UNIT(carry, ~*in_ptr, 0, out_ptr);
                ++in_ptr;
                ++out_ptr;
                --count1;
                --count2;
            }
            while (count2 > 0)
            {
                carry = _ADD_UNIT(carry, (__UNIT_TYPE)-1, 0, out_ptr);
                ++in_ptr;
                ++out_ptr;
                --count2;
            }
            output_len = temp_buf_count * (__UNIT_TYPE_BIT_COUNT / 4);
            unsigned char* ptr = (unsigned char*)&temp_buf[temp_buf_count] - 1;
            while (ptr >= (unsigned char*)temp_buf)
            {
                if ((ptr[0] >> 4) != 0xf || (ptr[0] & 0xf) < 0x8)
                    break;
                // 最上位桁が 'F' で、かつ次の桁が '8'～'F'である場合
                // ⇒最上位桁の 'F' を削除する
                *ptr &= 0x0f;
                --output_len;

                if (&ptr[-1] < (unsigned char*)temp_buf)
                    break;

                if (ptr[0] != 0xf || (ptr[-1] >> 4) < 0x8)
                    break;
                // 最上位桁が 'F' で、かつ次の桁が '8'～'F'である場合
                // ⇒最上位桁の 'F' を削除する
                *ptr = 0;
                --output_len;

                --ptr;
            }
            filling_char = _character_set[15];
        }
#ifdef _DEBUG
        root.CheckBlock(temp_buf);
#endif

        // この時点で 合計桁数は output_len だけあることが判明

        // output_len 桁を格納するためのワード数を調べ、その隙間の桁数を leading_zero_digit_count とする

        unsigned int leading_zero_digit_count = (unsigned int)(_DIVIDE_CEILING_UNIT(output_len, __UNIT_TYPE_BIT_COUNT / 4) * (__UNIT_TYPE_BIT_COUNT / 4) - output_len);


        __UNIT_TYPE filling_digit_len; // 塗りつぶす上位桁の桁数
        __UNIT_TYPE total_length; // 出力する合計の桁数
        if (output_len < (__UNIT_TYPE)_precision)
        {
            filling_digit_len = _precision - output_len;
            total_length = _precision;
        }
        else
        {
            filling_digit_len = 0;
            total_length = output_len;
        }
        writer.Write(filling_char, filling_digit_len);

        __UNIT_TYPE* s_ptr = &temp_buf[_DIVIDE_CEILING_UNIT(output_len, __UNIT_TYPE_BIT_COUNT / 4) - 1];
        OutputHexNumberSequenceOneWord(*s_ptr, leading_zero_digit_count, _character_set, writer);
        --s_ptr;
        while (s_ptr >= temp_buf)
        {
            OutputHexNumberSequenceOneWord(*s_ptr, 0, _character_set, writer);
            --s_ptr;
        }
    }

}


/*
 * END OF FILE
 */