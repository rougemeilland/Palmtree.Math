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


#include "pmc_thousandseparatedstringwriter.h"


namespace Palmtree::Math::Core::Internal
{

    ThousandSeparatedStringWriter::ThousandSeparatedStringWriter(ReverseStringWriter& native_writer, wchar_t format_type, const PMC_NUMBER_FORMAT_INFO& format_option)
        : StringWriter(nullptr, nullptr, nullptr), _native_writer(native_writer)
    {
        _native_writer = native_writer;
        const PMC_DECIMAL_NUMBER_FORMAT_INFO* decimal_info;
        if (format_type == L'C')
        {
            decimal_info = &format_option.Currency;
            _is_supported_thousand = true;
        }
        else if (format_type == L'P')
        {
            decimal_info = &format_option.Percent;
            _is_supported_thousand = true;
        }
        else if (format_type == L'N')
        {
            decimal_info = &format_option.Number;
            _is_supported_thousand = true;
        }
        else
        {
            decimal_info = &format_option.Number;
            _is_supported_thousand = false;
        }

        const wchar_t* in_ptr = decimal_info->GroupSeparator;

        _current_group = &decimal_info->GroupSizes[0];
        _group_separator = decimal_info->GroupSeparator;
        _current_group_size = *_current_group - L'0';
        _current_group_index = 0;
    }

    void ThousandSeparatedStringWriter::Write(wchar_t c)
    {
        if (_is_supported_thousand && c >= L'0' && c <= L'9')
        {
            // 桁区切りをサポートする場合
            if (_current_group_size > 0 && _current_group_index >= _current_group_size)
            {
                // 現在のグループ幅が 0 ではなく、かつ既に出力した文字数がグループ幅に達した場合

                // グループ区切り文字を出力してから与えられた文字を出力する
                _native_writer.Write(_group_separator);
                _native_writer.Write(c);
                _current_group_index = 1;

                // 次のグループが存在すればそのグループに移行する
                if (_current_group[1] != L'\0')
                {
                    _current_group += 1;
                    _current_group_size = _current_group[0] - L'0';
                }
            }
            else
            {
                // 現在のグループの幅が 0 であるかあるいは出力した文字数がグループ幅に達していない場合
                _native_writer.Write(c);
                _current_group_index += 1;
            }
        }
        else
        {
            // 桁区切りをサポートしない場合

            _native_writer.Write(c);
        }
    }

    void ThousandSeparatedStringWriter::Write(const wchar_t * str)
    {
        while (*str != L'\0')
            Write(*str++);
    }

    wchar_t * ThousandSeparatedStringWriter::GetString()
    {
        return (_native_writer.GetString());
    }

}


/*
 * END OF FILE
 */