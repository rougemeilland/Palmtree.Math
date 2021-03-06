﻿/*
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
#include "pmc_tostringformattertypee.h"
#include "pmc_resourceholder_uint.h"

namespace Palmtree::Math::Core::Internal
{

    static SIGN_T Compare_R_UI(ThreadContext& tc, NUMBER_OBJECT_UINT* u_numerator, NUMBER_OBJECT_UINT* u_denominator, _UINT32_T v)
    {
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* v2 = PMC_Multiply_UX_UI_Imp(tc, u_denominator, v);
        root.HookNumber(v2);
        return (PMC_Compare_UX_UX_Imp(u_numerator, v2));
    }

    ToStringFormatterTypeE::ToStringFormatterTypeE(ThreadContext& tc, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO * number_format_info)
        : ToStringFormatter(tc, format_type, precision, number_format_info)
    {
    }

    int ToStringFormatterTypeE::GetDefaultPrecisionValue(int specified_precision)
    {
        return (specified_precision >= 0 ? specified_precision : 6);
    }

    void ToStringFormatterTypeE::WriteZeroValue(StringWriter& writer)
    {
        writer.Write(L'0');
        if (_precision > 0)
        {
            writer.Write(_number_format_info->Number.DecimalSeparator);
            writer.Write(L'0', _precision);
        }
        writer.Write(_format_type);
        writer.Write(L"+000");
    }

    void ToStringFormatterTypeE::RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT** r_numerator, NUMBER_OBJECT_UINT** r_denominator, _INT32_T * exp)
    {
        ResourceHolderUINT root(_tc);
        // 最上位桁が 1 の位になるように 10 のべき乗をかけるあるいは割って、桁をずらす。
        *exp = PMC_FloorLog10_R_Imp(_tc, x_numerator, x_denominator);
        if (*exp == 0)
        {
            *r_numerator = x_numerator;
            *r_denominator = x_denominator;
        }
        else if (*exp > 0)
        {
            NUMBER_OBJECT_UINT* factor = PMC_Pow10_UI_Imp(_tc, *exp);
            root.HookNumber(factor);
            *r_numerator = x_numerator;
            *r_denominator = PMC_Multiply_UX_UX_Imp(_tc, PMC_MULTIPLICATION_METHOD_AUTO, x_denominator, factor);
            root.HookNumber(*r_denominator);
        }
        else
        {
            NUMBER_OBJECT_UINT* factor = PMC_Pow10_UI_Imp(_tc, -*exp);
            root.HookNumber(factor);
            *r_numerator = PMC_Multiply_UX_UX_Imp(_tc, PMC_MULTIPLICATION_METHOD_AUTO, x_numerator, factor);
            root.HookNumber(*r_numerator);
            *r_denominator = x_denominator;
        }
        // 桁を丸める
        *r_numerator = PMC_Round_R_Imp(_tc, *r_numerator, *r_denominator, _precision, PMC_GetDefaultRoundingMode(), r_denominator);
        root.HookNumber(*r_numerator);
        root.HookNumber(*r_denominator);
        // 桁を丸めた結果繰り上がりによって最上位桁が 10 の位になってしまった場合は、更に 1 桁だけ桁をずらす
        if (Compare_R_UI(_tc, *r_numerator, *r_denominator, 10U) >= 0)
        {
            *r_denominator = PMC_Multiply_UX_UI_Imp(_tc, *r_denominator, 10U);
            root.HookNumber(*r_denominator);
            *exp = *exp + 1;
        }
        root.UnlinkNumber(*r_numerator);
        root.UnlinkNumber(*r_denominator);
    }

    inline void ToStringFormatterTypeE::WritePrefix(SIGN_T x_sign, StringWriter& writer)
    {
        if (x_sign < 0)
            writer.Write(_number_format_info->NegativeSign);
    }

    void ToStringFormatterTypeE::FormatNumberSequence(const wchar_t * int_part, const wchar_t * frac_part, _INT32_T exp, StringWriter& writer)
    {
#ifdef _DEBUG
        if (lstrlenW(int_part) != 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;FormatterTypeE::FormatNumberSequence;1");
#endif
        writer.Write(int_part);
        if (_precision > 0 && frac_part[0] != L'\0')
        {
            writer.Write(_number_format_info->Number.DecimalSeparator);
            writer.Write(frac_part);
        }
        writer.Write(_format_type); // 'e' or 'E'
        if (exp >= 0)
        {
            writer.Write(_number_format_info->PositiveSign);
        }
        else
        {
            writer.Write(_number_format_info->NegativeSign);
            exp = -exp;
        }

        // 指数部を文字列化するために必要な領域の大きさについて
        // sizeof(w_char_t) == 2 であるため、アドレス空間が 64bit の環境における指数部の論理的な上限値は 2^63 (^はべき乗演算子)
        // なので、指数部を10進数表記した場合の論理的な桁数の上限値は ceil(63 * log(2) / log(10)) ==> 19 となる。
        // 同様に、32bit アドレス空間においては、指数部桁数の論理的上限値は ceil(31 * log(2) / log(10)) ==> 10 となる。

#ifdef _M_IX86 
        wchar_t exp_buf[10 + 1];
#elif defined(_M_X64)
        wchar_t exp_buf[19 + 1];
#else
#error unknown platform
#endif
        wsprintfW(exp_buf, L"%03d", exp);
        writer.Write(exp_buf);
    }

    void ToStringFormatterTypeE::WriteSuffix(SIGN_T x_sign, StringWriter& writer)
    {
    }

}

/*
 * END OF FILE
 */