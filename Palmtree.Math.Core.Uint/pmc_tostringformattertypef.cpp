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


#include "pmc_tostringformattertypef.h"
#include "pmc_resourceholder_uint.h"


namespace Palmtree::Math::Core::Internal
{

    ToStringFormatterTypeF::ToStringFormatterTypeF(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : ToStringFormatter(format_type, precision, number_format_info)
    {
    }

    int ToStringFormatterTypeF::GetDefaultPrecisionValue(int specified_precision)
    {
        return (specified_precision >= 0 ? specified_precision : _number_format_info->Number.DecimalDigits);
    }

    void ToStringFormatterTypeF::WriteZeroValue(StringWriter& writer)
    {
        writer.Write(L'0');
        if (_precision > 0)
        {
            writer.Write(_number_format_info->Number.DecimalSeparator);
            writer.Write(L'0', _precision);
        }
    }

    void ToStringFormatterTypeF::WritePrefix(SIGN_T x_sign, StringWriter& writer)
    {
        if (x_sign < 0)
            writer.Write(_number_format_info->NegativeSign);
    }

    void ToStringFormatterTypeF::FormatNumberSequence(const wchar_t * int_part, const wchar_t * frac_part, _INT32_T exp, StringWriter& writer)
    {
        writer.Write(int_part);
        if (_precision > 0 && frac_part[0] != L'\0')
        {
            writer.Write(_number_format_info->Number.DecimalSeparator);
            writer.Write(frac_part);
        }
    }

    void ToStringFormatterTypeF::WriteSuffix(SIGN_T x_sign, StringWriter& writer)
    {
    }

}


/*
 * END OF FILE
 */