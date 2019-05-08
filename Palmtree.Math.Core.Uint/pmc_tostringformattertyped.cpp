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
#include "pmc_tostringformattertyped.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_thousandseparatedstringwriter.h"


namespace Palmtree::Math::Core::Internal
{

    ToStringFormatterTypeD::ToStringFormatterTypeD(ThreadContext& tc, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : ToStringFormatter(tc, L'N', precision, number_format_info)
    {
    }

    int ToStringFormatterTypeD::GetDefaultPrecisionValue(int specified_precision)
    {
        return (specified_precision >= 0 ? specified_precision : 0);
    }

    void ToStringFormatterTypeD::WriteZeroValue(StringWriter& writer)
    {
        writer.Write(L'0', _precision < 1 ? 1 : _precision);
    }

    void ToStringFormatterTypeD::WritePrefix(SIGN_T x_sign, StringWriter& writer)
    {
        if (x_sign >= 0)
        {
        }
        else
        {
            writer.Write(_number_format_info->NegativeSign);
        }
    }

    size_t ToStringFormatterTypeD::GetFractionPartLength()
    {
        return (0);
    }

    void ToStringFormatterTypeD::FormatNumberSequence(const wchar_t * int_part, const wchar_t * frac_part, _INT32_T exp, StringWriter& writer)
    {
        int digit_count = lstrlenW(int_part);
        if (digit_count < _precision)
            writer.Write(L'0', _precision - digit_count);
        writer.Write(int_part);
    }

    void ToStringFormatterTypeD::WriteSuffix(SIGN_T x_sign, StringWriter& writer)
    {
    }

}


/*
 * END OF FILE
 */