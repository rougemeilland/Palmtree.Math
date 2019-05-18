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
#include "pmc_tostringformattertypec.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_thousandseparatedstringwriter.h"

namespace Palmtree::Math::Core::Internal
{
    ToStringFormatterTypeC::ToStringFormatterTypeC(ThreadContext& tc, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : ToStringFormatter(tc, L'C', precision, number_format_info)
    {
    }
    
    int ToStringFormatterTypeC::GetDefaultPrecisionValue(int specified_precision)
    {
        return (specified_precision >= 0 ? specified_precision : _number_format_info->Currency.DecimalDigits);
    }
    
    void ToStringFormatterTypeC::WriteZeroValue(StringWriter& writer)
    {
        writer.Write(L'0');
        if (_precision > 0)
        {
            writer.Write(_number_format_info->Currency.DecimalSeparator);
            writer.Write(L'0', _precision);
        }
    }
    
    void ToStringFormatterTypeC::WritePrefix(SIGN_T x_sign, StringWriter& writer)
    {
        if (x_sign >= 0)
        {
            switch (_number_format_info->Currency.PositivePattern)
            {
            case 0:
            default:
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 1:
                break;
            case 2:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L' ');
                break;
            case 3:
                break;
            }
        }
        else
        {
            switch (_number_format_info->Currency.NegativePattern)
            {
            case 0:
            default:
                writer.Write(L'(');
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 1:
                writer.Write(_number_format_info->NegativeSign);
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 2:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 3:
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 4:
                writer.Write(L'(');
                break;
            case 5:
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 9:
                writer.Write(_number_format_info->NegativeSign);
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L' ');
                break;
            case 10:
                break;
            case 11:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L' ');
                break;
            case 12:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L' ');
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 13:
                break;
            case 14:
                writer.Write(L'(');
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L' ');
                break;
            case 15:
                writer.Write(L'(');
                break;
            }
        }
    }
    
    void ToStringFormatterTypeC::FormatNumberSequence(const wchar_t * int_part, const wchar_t * frac_part, _INT32_T exp, StringWriter& writer)
    {
        ResourceHolderUINT root(_tc);
        ReverseStringReader r_reader(int_part);
        size_t work_buf_len = lstrlenW(int_part) * 2 + 1 + _precision + 1;
        wchar_t* work_buf = root.AllocateString(work_buf_len);
        ReverseStringWriter r_writer(work_buf, work_buf_len);
        ThousandSeparatedStringWriter t_writer(r_writer, _format_type, *_number_format_info);
        t_writer.Write(r_reader);
        writer.Write(t_writer.GetString());
        if (_precision > 0 && frac_part[0] != L'\0')
        {
            writer.Write(_number_format_info->Currency.DecimalSeparator);
            writer.Write(frac_part);
        }
    }
    
    void ToStringFormatterTypeC::WriteSuffix(SIGN_T x_sign, StringWriter& writer)
    {
        if (x_sign >= 0)
        {
            switch (_number_format_info->Currency.PositivePattern)
            {
            case 0:
            default:
                break;
            case 1:
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 2:
                break;
            case 3:
                writer.Write(L' ');
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            }
        }
        else
        {
            switch (_number_format_info->Currency.NegativePattern)
            {
            case 0:
            default:
                writer.Write(L')');
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 4:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L')');
                break;
            case 5:
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 6:
                writer.Write(_number_format_info->NegativeSign);
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 7:
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 8:
                writer.Write(L' ');
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 9:
                break;
            case 10:
                writer.Write(L' ');
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 11:
                writer.Write(_number_format_info->NegativeSign);
                break;
            case 12:
                break;
            case 13:
                writer.Write(_number_format_info->NegativeSign);
                writer.Write(L' ');
                writer.Write(_number_format_info->CurrencySymbol);
                break;
            case 14:
                writer.Write(L')');
                break;
            case 15:
                writer.Write(L' ');
                writer.Write(_number_format_info->CurrencySymbol);
                writer.Write(L')');
                break;
            }
        }
    }
}

/*
 * END OF FILE
 */