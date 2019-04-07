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


#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_stringio.h"
#include "pmc_tostringformattertypec.h"
#include "pmc_tostringformattertyped.h"
#include "pmc_tostringformattertypee.h"
#include "pmc_tostringformattertypef.h"
#include "pmc_tostringformattertypeg.h"
#include "pmc_tostringformattertypen.h"
#include "pmc_tostringformattertypep.h"
#include "pmc_tostringformattertypex.h"


namespace Palmtree::Math::Core::Internal
{

    static PMC_NUMBER_FORMAT_INFO default_number_format_option;

    static size_t ToStringC(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeC formatter(precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringD(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeD formatter(precision, format_option);
        formatter.Format(x_sign, x_numerator, &number_object_uint_one, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringE(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeE formatter(format_type, precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringF(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeF formatter(format_type, precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringG(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeG formatter(format_type, precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringN(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeN formatter(precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }


    static size_t ToStringP(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeP formatter(precision, format_option);
        formatter.Format(x_sign, x_numerator, x_denominator, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringX(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        StringWriter writer(buffer, buffer_size);
        ToStringFormatterTypeX formatter(format_type, precision, format_option);
        formatter.Format(x_sign, x_abs, &writer);
        return (writer.GetLength());
    }

    static size_t ToStringCustom(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        throw FormatException(L"書式に誤りがあります。");
    }

    __inline static bool __IS_ALPHA(wchar_t c)
    {
        if (c >= L'A' && c <= L'Z')
            return (true);
        if (c >= L'a' && c <= L'z')
            return (true);
        return (false);
    }

    __inline static bool __IS_DIGIT(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (true);
        return (false);
    }

    static bool ParseStandardFormat(const wchar_t* format, wchar_t* format_type, int* precision)
    {
        if (format == nullptr)
        {
            *format_type = L'D';
            *precision = -1;
            return (true);
        }
        else if (format[0] == L'\0')
        {
            *format_type = L'D';
            *precision = -1;
            return (true);
        }
        else if (__IS_ALPHA(format[0]) && format[1] == L'\0')
        {
            *format_type = format[0];
            *precision = -1;
            return (true);
        }
        else if (__IS_ALPHA(format[0]) && __IS_DIGIT(format[1]) && format[2] == L'\0')
        {
            *format_type = format[0];
            *precision = format[1] - L'0';
            return (true);
        }
        else if (__IS_ALPHA(format[0]) && __IS_DIGIT(format[1]) && __IS_DIGIT(format[2]) && format[3] == L'\0')
        {
            *format_type = format[0];
            *precision = (format[1] - L'0') * 10 + (format[2] - L'0');
            return (true);
        }
        else
            return (false);
    }

    static size_t PMC_ToString_Imp(SIGN_T x_numerator_sign, NUMBER_OBJECT_UINT* x_numerator_abs, NUMBER_OBJECT_UINT* x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        wchar_t format_type;
        int precision;
        if (!ParseStandardFormat(format, &format_type, &precision))
            return (ToStringCustom(x_numerator_sign, x_numerator_abs, x_denominator, format, format_option, buffer, buffer_size));
        else
        {
            switch (format_type)
            {
            case L'c':
            case L'C':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringC(x_numerator_sign, x_numerator_abs, x_denominator, L'C', precision, format_option, buffer, buffer_size));
            case L'd':
            case L'D':
                if (x_denominator != nullptr)
                    throw FormatException(L"書式 D が使用できない数値型です。");
                return (ToStringD(x_numerator_sign, x_numerator_abs, L'D', precision, format_option, buffer, buffer_size));
            case L'e':
            case L'E':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringE(x_numerator_sign, x_numerator_abs, x_denominator, format_type, precision, format_option, buffer, buffer_size));
            case L'f':
            case L'F':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringF(x_numerator_sign, x_numerator_abs, x_denominator, L'F', precision, format_option, buffer, buffer_size));
            case L'g':
            case L'G':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringG(x_numerator_sign, x_numerator_abs, x_denominator, format_type, precision, format_option, buffer, buffer_size));
            case L'n':
            case L'N':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringN(x_numerator_sign, x_numerator_abs, x_denominator, L'N', precision, format_option, buffer, buffer_size));
            case L'p':
            case L'P':
                if (x_denominator == nullptr)
                    x_denominator = &number_object_uint_one;
                return (ToStringP(x_numerator_sign, x_numerator_abs, x_denominator, L'P', precision, format_option, buffer, buffer_size));
            case L'r':
            case L'R':
                if (x_denominator != nullptr)
                    throw FormatException(L"書式 R が使用できない数値型です。");
                return (ToStringD(x_numerator_sign, x_numerator_abs, L'D', 0, format_option, buffer, buffer_size));
            case L'x':
            case L'X':
                if (x_denominator != nullptr)
                    throw FormatException(L"書式 X が使用できない数値型です。");
                return (ToStringX(x_numerator_sign, x_numerator_abs, format_type, precision, format_option, buffer, buffer_size));
            default:
                throw FormatException(L"未知の書式指定子です。");
            }
        }
    }

    size_t PMC_ToString_UX(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nx = GET_NUMBER_OBJECT(x, L"x");
        return (PMC_ToString_Imp(nx->IS_ZERO ? SIGN_ZERO : SIGN_POSITIVE, nx, nullptr, format, format_option, buffer, buffer_size));
    }

    size_t PMC_ToString_X(SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_UINT* nx_abs = GET_NUMBER_OBJECT(x_abs, L"x_abs");
        return (PMC_ToString_Imp(x_sign, nx_abs, nullptr, format, format_option, buffer, buffer_size));
    }

    size_t PMC_ToString_R(SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_UINT* nx_numerator_abs = GET_NUMBER_OBJECT(x_numerator_abs, L"x_numerator_abs");
        NUMBER_OBJECT_UINT* nx_denominator = GET_NUMBER_OBJECT(x_denominator, L"x_denominator");
        return (PMC_ToString_Imp(x_numerator_sign, nx_numerator_abs, nx_denominator, format, format_option, buffer, buffer_size));
    }

    void InitializeNumberFormatoInfo(PMC_NUMBER_FORMAT_INFO* info)
    {
        info->Currency.DecimalDigits = 2;
        lstrcpyW(info->Currency.DecimalSeparator, L".");
        lstrcpyW(info->Currency.GroupSeparator, L",");
        lstrcpyW(info->Currency.GroupSizes, L"3");
        info->Currency.NegativePattern = 0;
        info->Currency.PositivePattern = 0;

        info->Number.DecimalDigits = 2;
        lstrcpyW(info->Number.DecimalSeparator, L".");
        lstrcpyW(info->Number.GroupSeparator, L",");
        lstrcpyW(info->Number.GroupSizes, L"3");
        info->Number.NegativePattern = 1;
        info->Number.PositivePattern = -1; // 未使用

        info->Percent.DecimalDigits = 2;
        lstrcpyW(info->Percent.DecimalSeparator, L".");
        lstrcpyW(info->Percent.GroupSeparator, L",");
        lstrcpyW(info->Percent.GroupSizes, L"3");
        info->Percent.NegativePattern = 0;
        info->Percent.PositivePattern = 0;

        lstrcpyW(info->CurrencySymbol, L"\u00a4");
        lstrcpyW(info->NegativeSign, L"-");
        lstrcpyW(info->PercentSymbol, L"%");
        lstrcpyW(info->PerMilleSymbol, L"\u2030");
        lstrcpyW(info->PositiveSign, L"+");
    }

    void PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info)
    {
        InitializeNumberFormatoInfo(info);
    }

    PMC_STATUS_CODE Initialize_ToString(PROCESSOR_FEATURES *feature)
    {
        InitializeNumberFormatoInfo(&default_number_format_option);

        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */