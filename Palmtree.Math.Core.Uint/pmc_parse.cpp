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
#include "pmc_parser.h"
#include "pmc_string.h"
#include "pmc_parserstate.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{
    namespace DecimalParser
    {

        // 10進数の数値を表す文字列を符号、整数部、小数部に分解する。数値が明らかに正である場合は *flag に 1、明らかに負である場合は *flag に -1 が格納され、数値が正か 0 か明らかには判断できない場合は *flag に 1 が格納される。
        static int ParseAsDecimalNumberString(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size, SIGN_T* exponent_sign, wchar_t* exp_part_buf, size_t exp_part_buf_size)
        {
            ParserState state(in_ptr, number_styles, format_option, sign, int_part_buf, int_part_buf_size, frac_part_buf, frac_part_buf_size, exponent_sign, exp_part_buf, exp_part_buf_size);
            return (state.ParseAsDecimalNumberString());
        }

        static PMC_STATUS_CODE TryParseAsDecimal(const wchar_t* source, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, NUMBER_OBJECT_UINT** o_int_part, NUMBER_OBJECT_UINT** o_frac_part_numerator, NUMBER_OBJECT_UINT** o_frac_part_denominator)
        {
            ResourceHolderUINT root;

            __UNIT_TYPE source_len = lstrlenW(source);

            size_t int_part_buf_count = source_len + 1;
            wchar_t* int_part_buf = root.AllocateString(int_part_buf_count);
            size_t frac_part_buf_count = source_len + 1;
            wchar_t* frac_part_buf = root.AllocateString(frac_part_buf_count);
            size_t exp_part_buf_count = source_len + 1;
            wchar_t* exp_part_buf = root.AllocateString(frac_part_buf_count);
            SIGN_T exponent_sign;
            bool result_parsing = ParseAsDecimalNumberString(source, number_styles, format_option, sign, int_part_buf, int_part_buf_count, frac_part_buf, frac_part_buf_count, &exponent_sign, exp_part_buf, exp_part_buf_count);
            root.CheckString(int_part_buf);
            root.CheckString(frac_part_buf);
            root.CheckString(exp_part_buf);
            if (!result_parsing)
                return (PMC_STATUS_FORMAT_ERROR);
            if (int_part_buf[0] == L'\0' && (frac_part_buf[0] == L'\0' || frac_part_buf[0] == L'.' && frac_part_buf[1] == L'\0'))
            {
                // 整数部と小数部がともに空ならばエラーとする
                return (PMC_STATUS_FORMAT_ERROR);
            }


            if (*sign < 0 && frac_part_buf[0] != L'\0')
            {
                // 符号なし/あり整数の解析中で、負の符号が含まれていて、かつ小数部が存在する場合はエラー (OverflowException) とする。(小数点のみや小数部が '0' の連続のみでも存在するうちに入る)
                // ※エラーの条件がそうなっている根拠は不明だが実際問題として uint.Parse などではそうなっているため、それに合わせる。

                if ((number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER) == 0)
                {
                    // 負数が許可されていない場合

                    return (PMC_STATUS_OVERFLOW);
                }
            }

            if (int_part_buf[0] == L'0')
            {
                // 整数部の先行する 0 を削除する
                wchar_t* s_ptr = int_part_buf;
                wchar_t* d_ptr = int_part_buf;
                while (*s_ptr == L'0')
                    ++s_ptr;
                for (;;)
                {
                    *d_ptr = *s_ptr;
                    if (*s_ptr == L'\0')
                        break;
                    ++s_ptr;
                    ++d_ptr;
                }
            }

            // 小数部の末尾の 0 を削除する
            wchar_t* frac_ptr = frac_part_buf + lstrlenW(frac_part_buf);
            while (frac_ptr > frac_part_buf && frac_ptr[-1] == L'0')
                --frac_ptr;
            *frac_ptr = L'\0';

            if (int_part_buf[0] == L'\0')
            {
                // 整数部が空である場合

                // 整数部に 0 を設定する
                int_part_buf[0] = L'0';
                int_part_buf[1] = L'\0';
            }

            // 整数部単純数字列から整数部を構築
            NUMBER_OBJECT_UINT* t_int_part = PMC_AToL_Imp(int_part_buf);
            root.HookNumber(t_int_part);

            // 小数部の分子・分母を構築
            wchar_t* frac_part_ptr = frac_part_buf[0] == L'.' ? frac_part_buf + 1 : frac_part_buf;
            NUMBER_OBJECT_UINT* t_frac_part_numerator;
            NUMBER_OBJECT_UINT* t_frac_part_denominator;
            if (*frac_part_ptr == L'\0')
            {
                // 小数部単純数字列が空の場合は、分子に 0 、分母に 1 を設定する
                t_frac_part_numerator = &number_object_uint_zero;
                root.HookNumber(t_frac_part_numerator);
                t_frac_part_denominator = &number_object_uint_one;
                root.HookNumber(t_frac_part_denominator);
            }
            else
            {
                // 小数部単純数字列から小数部の分子を構築
                t_frac_part_numerator = PMC_AToL_Imp(frac_part_ptr);
                root.HookNumber(t_frac_part_numerator);

                // 小数部単純数字列の桁数から小数部の母数を構築
                t_frac_part_denominator = PMC_Pow10_UI_Imp(lstrlenW(frac_part_ptr));
                root.HookNumber(t_frac_part_denominator);
            }

            if (exp_part_buf[0] != L'\0')
            {
                // 指数部の符号および単純数字列から小数部の分子または分母を補正
                _UINT64_T exponent_value = PMC_AToI(exp_part_buf);
                if (exponent_value > 0xffffffffU)
                    throw OverflowException(L"大きすぎるあるいは小さすぎる数値を変換しようとしました。");
                NUMBER_OBJECT_UINT* exponent_factor = PMC_Pow10_UI_Imp((_UINT32_T)exponent_value);
                if (exponent_sign > 0)
                {
                    // 指数が正の場合

                    // 整数部と小数部を加算した分子と分母を求める
                    NUMBER_OBJECT_UINT* n = PMC_Multiply_UX_UX_Imp(t_int_part, t_frac_part_denominator);
                    root.HookNumber(n);
                    n = PMC_Add_UX_UX_Imp(n, t_frac_part_numerator);
                    root.HookNumber(n);
                    NUMBER_OBJECT_UINT* d = t_frac_part_denominator;

                    // 分子に指数を反映させる
                    n = PMC_Multiply_UX_UX_Imp(n, exponent_factor);
                    root.HookNumber(n);

                    // 再び整数部と小数部に分ける
                    t_frac_part_numerator = PMC_DivRem_UX_UX_Imp(n, d, &t_int_part);
                    t_frac_part_denominator = d;
                    root.HookNumber(t_int_part);
                    root.HookNumber(t_frac_part_numerator);
                }
                else if (exponent_sign < 0)
                {
                    // 指数が負の場合

                    // 整数部と小数部を加算した分子と分母を求める
                    NUMBER_OBJECT_UINT* n = PMC_Multiply_UX_UX_Imp(t_int_part, t_frac_part_denominator);
                    root.HookNumber(n);
                    n = PMC_Add_UX_UX_Imp(n, t_frac_part_numerator);
                    root.HookNumber(n);
                    NUMBER_OBJECT_UINT* d = t_frac_part_denominator;

                    // 分子に指数を反映させる
                    d = PMC_Multiply_UX_UX_Imp(d, exponent_factor);
                    root.HookNumber(d);

                    // 再び整数部と小数部に分ける
                    t_frac_part_numerator = PMC_DivRem_UX_UX_Imp(n, d, &t_int_part);
                    t_frac_part_denominator = d;
                    root.HookNumber(t_int_part);
                    root.HookNumber(t_frac_part_numerator);
                }
                else
                {
                    // 指数が 0 の場合

                    // 何もしない
                }
            }

            // o を約分する
            NUMBER_OBJECT_UINT* o_gcd = PMC_GreatestCommonDivisor_UX_UX_Imp(t_frac_part_numerator, t_frac_part_denominator);
            root.HookNumber(o_gcd);
            if (!o_gcd->IS_ONE)
            {
                t_frac_part_numerator = PMC_DivideExactly_UX_UX_Imp(t_frac_part_numerator, o_gcd);
                root.HookNumber(t_frac_part_numerator);
                t_frac_part_denominator = PMC_DivideExactly_UX_UX_Imp(t_frac_part_denominator, o_gcd);
                root.HookNumber(t_frac_part_denominator);
            }

            if (t_int_part->IS_ZERO && t_frac_part_numerator->IS_ZERO)
            {
                // o の絶対値が 0 の場合は符号を 0 に 修正する
                *sign = SIGN_ZERO;
            }

            *o_int_part = t_int_part;
            *o_frac_part_numerator = t_frac_part_numerator;
            *o_frac_part_denominator = t_frac_part_denominator;
            root.UnlinkNumber(*o_int_part);
            root.UnlinkNumber(*o_frac_part_numerator);
            root.UnlinkNumber(*o_frac_part_denominator);
            return (PMC_STATUS_OK);
        }

    }

    namespace HexaDecimalParser
    {
        static __UNIT_TYPE BuildLeading1WordFromHexString(wchar_t* in_ptr, __UNIT_TYPE count)
        {
            __UNIT_TYPE x = ParseHexDigit(*in_ptr);
            ++in_ptr;
            --count;
            while (count > 0)
            {
                x = x * 16 + ParseHexDigit(*in_ptr);
                ++in_ptr;
                --count;
            }
            return (x);
        }

        static __UNIT_TYPE Build1WordFromHexString(wchar_t* in_ptr)
        {
            __UNIT_TYPE x = ParseHexDigit(*in_ptr++);
            if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
            {
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
            }
            if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
            {
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
            }
            if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
            {
                x = x * 16 + ParseHexDigit(*in_ptr++);
                x = x * 16 + ParseHexDigit(*in_ptr++);
            }
            if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
            {
                x = x * 16 + ParseHexDigit(*in_ptr++);
            }
            return (x);
        }

        static void BuildBinaryFromHexString(wchar_t* source, __UNIT_TYPE* out_buf)
        {
            int word_digit_count = __UNIT_TYPE_BIT_COUNT / 4;
            __UNIT_TYPE source_count = lstrlenW(source);
            wchar_t* in_ptr = source;
            __UNIT_TYPE* out_ptr = out_buf + _DIVIDE_CEILING_UNIT(source_count, word_digit_count) - 1;
            int r = source_count % word_digit_count;
            if (r > 0)
            {
                *out_ptr-- = BuildLeading1WordFromHexString(in_ptr, r);
                in_ptr += r;
                source_count -= r;
            }
            while (source_count > 0)
            {
                *out_ptr-- = Build1WordFromHexString(in_ptr);
                in_ptr += word_digit_count;
                source_count -= word_digit_count;
            }
        }

        static int ParseAsHexNumberString(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* int_part_buf, size_t int_part_buf_size)
        {
            SIGN_T sign;
            wchar_t frac_part[1];
            SIGN_T exp_sign;
            wchar_t exp_part[1];
            ParserState state(in_ptr, number_styles, format_option, &sign, int_part_buf, int_part_buf_size, frac_part, countof(frac_part), &exp_sign, exp_part, countof(exp_part));
            return (state.ParseAsHexNumberString());
        }

        static PMC_STATUS_CODE TryParseAsHexaDecimal(const wchar_t* source, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, NUMBER_OBJECT_UINT** o_abs)
        {
            ResourceHolderUINT root;
            __UNIT_TYPE source_len = lstrlenW(source);
            size_t int_part_buf_size = source_len + 1;
            wchar_t* int_part_buf = root.AllocateString(source_len + 1);
            int result_parsing = ParseAsHexNumberString(source, number_styles, format_option, int_part_buf, int_part_buf_size);
            root.CheckString(int_part_buf);
            if (!result_parsing || int_part_buf[0] == L'\0')
                return (PMC_STATUS_FORMAT_ERROR);

            // 先頭 1 文字が 8～F であれば負数とみなす
            if (ParseHexDigit(int_part_buf[0]) >= 8)
            {
                // 先頭 1 文字が 8～F であれば負数とみなす
                if (!(number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER))
                {
                    // 負数が許可されていないにもかかわらず先頭文字が'8'～'F'である場合

                    // そのまま正数として扱う
                    *o_sign = SIGN_POSITIVE;
                }
                else
                {
                    // 負数が許可されていて先頭文字が'8'～'F'である場合

                    // 負数として扱う
                    *o_sign = SIGN_NEGATIVE;
                }
            }
            else
            {
                // 先頭 1 文字が 0～7 であれば正数とみなす
                *o_sign = SIGN_POSITIVE;
            }

            __UNIT_TYPE o_bit_count = lstrlenW(int_part_buf) * 4;
            *o_abs = root.AllocateNumber(o_bit_count);
            BuildBinaryFromHexString(int_part_buf, (*o_abs)->BLOCK);
            root.CheckNumber(*o_abs);
            root.DeallocateString(int_part_buf);
            if (*o_sign < 0)
            {
                // 負数の場合

                int lzcnt = o_bit_count % __UNIT_TYPE_BIT_COUNT;
                if (lzcnt != 0)
                {
                    __UNIT_TYPE padding = (__UNIT_TYPE)-1 << lzcnt;
                    (*o_abs)->BLOCK[(*o_abs)->BLOCK_COUNT - 1] |= padding;
                }

                // 配列 (*o_abs)->BLOCK の内容をビット反転してインクリメントする
                char carry = 1;
                __UNIT_TYPE* p = (*o_abs)->BLOCK;
                __UNIT_TYPE count = (*o_abs)->BLOCK_COUNT;
                while (count > 0)
                {
                    carry = _ADD_UNIT(carry, ~*p, 0, p);
                    ++p;
                    --count;
                }
            }
            CommitNumber(*o_abs);
            if ((*o_abs)->IS_ZERO)
            {
                root.DeallocateNumber(*o_abs);
                *o_sign = SIGN_ZERO;
                *o_abs = &number_object_uint_zero;
            }
            else
                root.UnlinkNumber(*o_abs);
            return (PMC_STATUS_OK);
        }
    }

    static PMC_STATUS_CODE PMC_TryParse_Imp(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, NUMBER_OBJECT_UINT** o_int_part, NUMBER_OBJECT_UINT** o_frac_part_numerator, NUMBER_OBJECT_UINT** o_frac_part_denominator) noexcept(false)
    {
        ResourceHolderUINT root;
        if (number_styles & PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER)
        {
            // 16進数の場合

            // 許可されている組み合わせのフラグ
            _UINT32_T mask = PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER | PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE | PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE | PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER;

            // 許可されていないフラグが指定されていればエラー
            if (number_styles & ~mask)
                throw ArgumentException(L"引数 number_styles に許可されていない組み合わせのフラグが指定されました。");

            PMC_STATUS_CODE result = HexaDecimalParser::TryParseAsHexaDecimal(source, number_styles, format_option, o_sign, o_int_part);
            if (result == PMC_STATUS_OK)
            {
                *o_frac_part_numerator = &number_object_uint_zero;
                *o_frac_part_denominator = &number_object_uint_one;
            }
            return (result);
        }
        else
        {
            // 10進数の場合
            return (DecimalParser::TryParseAsDecimal(source, number_styles, format_option, o_sign, o_int_part, o_frac_part_numerator, o_frac_part_denominator));
        }
    }

    PMC_STATUS_CODE PMC_TryParse_UINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o) noexcept(false)
    {
        ResourceHolderUINT root;
        SIGN_T o_sign;
        NUMBER_OBJECT_UINT* o_int_part;
        NUMBER_OBJECT_UINT* o_frac_part_numerator;
        NUMBER_OBJECT_UINT* o_frac_part_denominator;
        PMC_STATUS_CODE result = PMC_TryParse_Imp(source, number_styles, format_option, &o_sign, &o_int_part, &o_frac_part_numerator, &o_frac_part_denominator);
        if (result != PMC_STATUS_OK)
            return (result);
        root.HookNumber(o_int_part);
        root.HookNumber(o_frac_part_numerator);
        root.HookNumber(o_frac_part_denominator);
        if (o_sign < 0)
            return (PMC_STATUS_OVERFLOW);
        if (!o_frac_part_numerator->IS_ZERO)
            return (PMC_STATUS_OVERFLOW);
        *o = GET_NUMBER_HANDLE(o_int_part);
        root.UnlinkNumber(o_int_part);
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE PMC_TryParse_SINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, PMC_HANDLE_UINT* o_abs) noexcept(false)
    {
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* o_int_part;
        NUMBER_OBJECT_UINT* o_frac_part_numerator;
        NUMBER_OBJECT_UINT* o_frac_part_denominator;
        PMC_STATUS_CODE result = PMC_TryParse_Imp(source, number_styles | PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER, format_option, o_sign, &o_int_part, &o_frac_part_numerator, &o_frac_part_denominator);
        if (result != PMC_STATUS_OK)
            return (result);
        root.HookNumber(o_int_part);
        root.HookNumber(o_frac_part_numerator);
        root.HookNumber(o_frac_part_denominator);
        if (!o_frac_part_numerator->IS_ZERO)
            return (PMC_STATUS_OVERFLOW);
        *o_abs = GET_NUMBER_HANDLE(o_int_part);
        root.UnlinkNumber(o_int_part);
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE PMC_TryParse_RTNL(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        ResourceHolderUINT root;
        SIGN_T o_sign;
        NUMBER_OBJECT_UINT* o_int_part;
        NUMBER_OBJECT_UINT* o_frac_part_numerator;
        NUMBER_OBJECT_UINT* o_frac_part_denominator;
        PMC_STATUS_CODE result = PMC_TryParse_Imp(source, number_styles | PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER, format_option, &o_sign, &o_int_part, &o_frac_part_numerator, &o_frac_part_denominator);
        if (result != PMC_STATUS_OK)
            return (result);
        root.HookNumber(o_int_part);
        root.HookNumber(o_frac_part_numerator);
        root.HookNumber(o_frac_part_denominator);

        // 分子と分母を計算する
        NUMBER_OBJECT_UINT* no_numerator_abs = PMC_Multiply_UX_UX_Imp(o_int_part, o_frac_part_denominator);
        root.HookNumber(no_numerator_abs);
        no_numerator_abs = PMC_Add_UX_UX_Imp(no_numerator_abs, o_frac_part_numerator);
        root.HookNumber(no_numerator_abs);
        NUMBER_OBJECT_UINT* no_denominator = o_frac_part_denominator;

        // 分子と分母の GCD を計算する
        NUMBER_OBJECT_UINT* gcd = PMC_GreatestCommonDivisor_UX_UX_Imp(no_numerator_abs, no_denominator);
        root.HookNumber(gcd);
        if (!gcd->IS_ONE)
        {
            // GCDが 1 ではない(==分子と分母が既約ではない)場合、分子と分母をそれぞれ GCD で割る

            no_numerator_abs = PMC_DivideExactly_UX_UX_Imp(no_numerator_abs, gcd);
            root.HookNumber(no_numerator_abs);
            no_denominator = PMC_DivideExactly_UX_UX_Imp(no_denominator, gcd);
            root.HookNumber(no_denominator);
        }
        *o_numerator_sign = o_sign;
        *o_numerator_abs = GET_NUMBER_HANDLE(no_numerator_abs);
        *o_denominator = GET_NUMBER_HANDLE(no_denominator);
        root.UnlinkNumber(no_numerator_abs);
        root.UnlinkNumber(no_denominator);
        return (PMC_STATUS_OK);
    }

}

/*
 * END OF FILE
 */