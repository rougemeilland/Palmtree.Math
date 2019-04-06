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
#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"
#include "pmc_stringio.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

#ifdef _M_IX86
    static const __UNIT_TYPE _10n_base_number = 1000000000U; // 10^9
    static const size_t digit_count_on_word = 9;
#elif defined (_M_X64)
    static const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
    static const size_t digit_count_on_word = 19;
#else
#error unknown platform
#endif

    static PMC_NUMBER_FORMAT_INFO default_number_format_option;

    static int ParseDecimalDigit(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (c - L'0');
        return (-1);
    }

    class ParserState
    {
    private:
        StringReader _source;
        StringWriter _int_part;
        StringWriter _frac_part;
        StringWriter _exp_part;
        _UINT32_T _number_styles;
        SIGN_T* _sign;
        SIGN_T* _exponent_sign;
        wchar_t _currency_symbol[17];
        wchar_t _positive_sign[17];
        wchar_t _negative_sign[17];
        wchar_t _decimal_separator[17];
        wchar_t _group_separator[17];
        wchar_t _secondary_group_separator[17];

    public:
        ParserState(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size, SIGN_T* exponent_sign, wchar_t* exp_part_buf, size_t exp_part_buf_size)
            : _source(in_ptr), _int_part(int_part_buf, int_part_buf_size), _frac_part(frac_part_buf, frac_part_buf_size), _exp_part(exp_part_buf, exp_part_buf_size)
        {
            _sign = sign;
            _exponent_sign = exponent_sign;
            _number_styles = number_styles;
            *_sign = SIGN_POSITIVE;
            *_exponent_sign = SIGN_POSITIVE;

            // 通貨単位の設定
            if (countof(_currency_symbol) < lstrlenW(format_option->CurrencySymbol) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;1");
            lstrcpyW(_currency_symbol, format_option->CurrencySymbol);

            // 符号文字の設定
            if (countof(_positive_sign) < lstrlenW(format_option->PositiveSign) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;2");
            lstrcpyW(_positive_sign, format_option->PositiveSign);
            if (countof(_negative_sign) < lstrlenW(format_option->NegativeSign) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;3");
            lstrcpyW(_negative_sign, format_option->NegativeSign);

            // 小数点/3桁区切り文字の設定
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL)
            {
                if (countof(_decimal_separator) < lstrlenW(format_option->Currency.DecimalSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;4");
                lstrcpyW(_decimal_separator, format_option->Currency.DecimalSeparator);
                if (countof(_group_separator) < lstrlenW(format_option->Currency.GroupSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;5");
                lstrcpyW(_group_separator, format_option->Currency.GroupSeparator);
            }
            else
            {
                if (countof(_decimal_separator) < lstrlenW(format_option->Number.DecimalSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;6");
                lstrcpyW(_decimal_separator, format_option->Number.DecimalSeparator);
                if (countof(_group_separator) < lstrlenW(format_option->Number.GroupSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;ParserState::ParserState;7");
                lstrcpyW(_group_separator, format_option->Number.GroupSeparator);
            }
            if (lstrcmpW(_group_separator, L"\xa0") == 0)
                lstrcpyW(_secondary_group_separator, L"\x20");
            else
                lstrcpyW(_secondary_group_separator, _group_separator);
        }

        ~ParserState()
        {
        }

        bool ParseAsDecimalNumberString()
        {
            if (_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE)
                _source.SkipSpace();
            if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
            {
                _source.SkipString(_currency_symbol);
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE) && _source.StartsWith(L" "))
                    _source.SkipString(L" ");
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN) && _source.StartsWith(_positive_sign))
                {
                    *_sign = SIGN_POSITIVE;
                    _source.SkipString(_positive_sign);
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = SIGN_NEGATIVE;
                    _source.SkipString(_negative_sign);
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                }
                else
                {
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                    {
                        *_sign = SIGN_POSITIVE;
                        _source.SkipString(_positive_sign);
                    }
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = SIGN_NEGATIVE;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
            }
            else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_PARENTHESES) && _source.StartsWith(L"(") /*&& 負数のエラーチェック()*/)
            {
                *_sign = SIGN_NEGATIVE;
                _source.SkipString(L"(");

                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                {
                    _source.SkipString(_currency_symbol);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE) && _source.StartsWith(L" "))
                        _source.SkipString(L" ");
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                }
                else
                {
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                    {
                        _source.SkipString(L" ");
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                            _source.SkipString(_currency_symbol);
                    }
                }
                if (!_source.StartsWith(L")"))
                    return (0);
                _source.SkipString(L")");
            }
            else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN) && _source.StartsWith(_positive_sign))
            {
                *_sign = SIGN_POSITIVE;
                _source.SkipString(_positive_sign);
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                {
                    _source.SkipString(_currency_symbol);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE) && _source.StartsWith(L" "))
                        _source.SkipString(L" ");
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                }
                else
                {
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                    {
                        _source.SkipString(L" ");
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                            _source.SkipString(_currency_symbol);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                    else
                    {
                    }
                }
            }
            else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
            {
                *_sign = SIGN_NEGATIVE;
                _source.SkipString(_negative_sign);
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                {
                    _source.SkipString(_currency_symbol);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE) && _source.StartsWith(L" "))
                        _source.SkipString(L" ");
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                }
                else
                {
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                    if (!ParseAsExponentPartNumberSequence())
                        return (false);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                    {
                        _source.SkipString(L" ");
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                            _source.SkipString(_currency_symbol);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                    else
                    {
                    }
                }
            }
            else if (ParseDecimalDigit(_source.PeekChar()) >= 0)
            {
                ParseAsIntegerPartNumberSequence();
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                {
                    _source.SkipString(_decimal_separator);
                    _frac_part.Write(L'.');
                    ParseAsFractionPartNumberSequence();
                }
                if (!ParseAsExponentPartNumberSequence())
                    return (false);
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                {
                    _source.SkipString(L" ");
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                    {
                        _source.SkipString(_currency_symbol);
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = SIGN_POSITIVE;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = SIGN_NEGATIVE;
                            _source.SkipString(_negative_sign);
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = SIGN_POSITIVE;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = SIGN_NEGATIVE;
                            _source.SkipString(_negative_sign);
                        }
                        else
                        {
                        }
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                {
                    _source.SkipString(_currency_symbol);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                    {
                        *_sign = SIGN_POSITIVE;
                        _source.SkipString(_positive_sign);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = SIGN_NEGATIVE;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                {
                    *_sign = SIGN_POSITIVE;
                    _source.SkipString(_positive_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = SIGN_NEGATIVE;
                    _source.SkipString(_negative_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else
                {
                }
            }
            else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
            {
                _source.SkipString(_decimal_separator);
                _frac_part.Write(L'.');
                ParseAsFractionPartNumberSequence();
                if (!ParseAsExponentPartNumberSequence())
                    return (false);
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                {
                    _source.SkipString(L" ");
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                    {
                        _source.SkipString(_currency_symbol);
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = SIGN_POSITIVE;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = SIGN_NEGATIVE;
                            _source.SkipString(_negative_sign);
                        }
                        else
                        {
                        }
                    }
                    else
                    {
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = SIGN_POSITIVE;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = SIGN_NEGATIVE;
                            _source.SkipString(_negative_sign);
                        }
                        else
                        {
                        }
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                {
                    _source.SkipString(_currency_symbol);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                    {
                        *_sign = SIGN_POSITIVE;
                        _source.SkipString(_positive_sign);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = SIGN_NEGATIVE;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                {
                    *_sign = SIGN_POSITIVE;
                    _source.SkipString(_positive_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = SIGN_NEGATIVE;
                    _source.SkipString(_negative_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else
                {
                }
            }
            else
                return (0);
            if (_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE)
                _source.SkipSpace();
            if (_source.PeekChar() != L'\0')
                return (false);
            return (true);
        }

    private:
        /*
        bool 負数のエラーチェック()
        {
            if (_負数を許可する)
                return (true);
            if (_エラーを例外で通知する)
                throw OverflowException(L"負の数を表現する文字列を符号なし整数に変換しようとしました。");
            return (false);
        }
        */

        void ParseAsIntegerPartNumberSequence()
        {
            for (;;)
            {
                wchar_t c = _source.PeekChar();
                if (ParseDecimalDigit(c) >= 0)
                {
                    _int_part.Write(c);
                    _source.Progress();
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_THOUSANDS) && _source.StartsWith(_group_separator))
                    _source.SkipString(_group_separator);
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_THOUSANDS) && _source.StartsWith(_secondary_group_separator))
                    _source.SkipString(_secondary_group_separator);
                else
                    break;
            }
        }

        void ParseAsFractionPartNumberSequence()
        {
            for (;;)
            {
                wchar_t c = _source.PeekChar();
                if (ParseDecimalDigit(c) >= 0)
                {
                    _frac_part.Write(c);
                    _source.Progress();
                }
                else
                    break;
            }
        }

        bool ParseAsExponentPartNumberSequence()
        {
            wchar_t c = _source.PeekChar();
            if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_EXPONENT) && (c == L'e' || c == L'E'))
            {
                _source.Progress();

                // 符号の解析
                if (_source.StartsWith(_positive_sign))
                {
                    *_exponent_sign = SIGN_POSITIVE;
                    _source.SkipString(_positive_sign);
                }
                else if (_source.StartsWith(_negative_sign))
                {
                    *_exponent_sign = SIGN_NEGATIVE;
                    _source.SkipString(_negative_sign);
                }
                else
                {
                    // 符号なし
                }

                // 符号の次の最初の数字は必須

                wchar_t c = _source.PeekChar();
                if (ParseDecimalDigit(c) < 0)
                    return (false);
                _exp_part.Write(c);
                _source.Progress();
                for (;;)
                {
                    wchar_t c = _source.PeekChar();
                    if (ParseDecimalDigit(c) >= 0)
                    {
                        _exp_part.Write(c);
                        _source.Progress();
                    }
                    else
                        break;
                }
            }
            return (true);
        }

    };

    // 10進数の数値を表す文字列を符号、整数部、小数部に分解する。数値が明らかに正である場合は *flag に 1、明らかに負である場合は *flag に -1 が格納され、数値が正か 0 か明らかには判断できない場合は *flag に 1 が格納される。
    static int ParseAsDecimalNumberString(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size, SIGN_T* exponent_sign, wchar_t* exp_part_buf, size_t exp_part_buf_size)
    {
        ParserState state(in_ptr, number_styles, format_option, sign, int_part_buf, int_part_buf_size, frac_part_buf, frac_part_buf_size, exponent_sign, exp_part_buf, exp_part_buf_size);
        return (state.ParseAsDecimalNumberString());
    }

    static PMC_STATUS_CODE TryParse_Imp(const wchar_t* source, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, PMC_HANDLE_UINT* o_numerator, PMC_HANDLE_UINT* o_denominator)
    {
        ResourceHolderSINT root;

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
        PMC_HANDLE_UINT t_int_part = ep_uint.AToL(int_part_buf);
        root.HookNumber(t_int_part);

        // 小数部の分子・分母を構築
        wchar_t* frac_part_ptr = frac_part_buf[0] == L'.' ? frac_part_buf + 1 : frac_part_buf;
        PMC_HANDLE_UINT t_frac_part_numerator;
        PMC_HANDLE_UINT t_frac_part_denominator;
        if (*frac_part_ptr == L'\0')
        {
            // 小数部単純数字列が空の場合は、分子に 0 、分母に 1 を設定する
            t_frac_part_numerator = number_handle_uint_zero;
            root.HookNumber(t_frac_part_numerator);
            t_frac_part_denominator = number_handle_uint_one;
            root.HookNumber(t_frac_part_denominator);
        }
        else
        {
            // 小数部単純数字列から小数部の分子を構築
            t_frac_part_numerator = ep_uint.AToL(frac_part_ptr);
            root.HookNumber(t_frac_part_numerator);

            // 小数部単純数字列の桁数から小数部の母数を構築
            t_frac_part_denominator = ep_uint.Pow10(lstrlenW(frac_part_ptr));
            root.HookNumber(t_frac_part_denominator);
        }

        // 整数部と小数部の和を 1 つの有理数とする
        *o_numerator = ep_uint.Multiply(t_int_part, t_frac_part_denominator);
        root.HookNumber(*o_numerator);
        *o_numerator = ep_uint.Add(*o_numerator, t_frac_part_numerator);
        root.HookNumber(*o_numerator);
        *o_denominator = t_frac_part_denominator;

        if (exp_part_buf[0] != L'\0')
        {
            // 指数部の符号および単純数字列から小数部の分子または分母を補正
            _UINT64_T exponent_value = ep_uint.AToI(exp_part_buf);
            if (exponent_value > 0xffffffffU)
                throw OverflowException(L"大きすぎるあるいは小さすぎる数値を変換しようとしました。");
            PMC_HANDLE_UINT exponent_factor = ep_uint.Pow10((_UINT32_T)exponent_value);
            if (exponent_sign >= 0)
            {
                *o_numerator = ep_uint.Multiply(*o_numerator, exponent_factor);
                root.HookNumber(*o_numerator);
            }
            else
            {
                *o_denominator = ep_uint.Multiply(*o_denominator, exponent_factor);
                root.HookNumber(*o_denominator);
            }
        }

        // o を約分する
        PMC_HANDLE_UINT o_gcd = ep_uint.GreatestCommonDivisor(*o_numerator, *o_denominator);
        if (!o_gcd->FLAGS.IS_ONE)
        {
            *o_numerator = ep_uint.DivideExactly(*o_numerator, o_gcd);
            root.HookNumber(*o_numerator);
            *o_denominator = ep_uint.DivideExactly(*o_denominator, o_gcd);
            root.HookNumber(*o_denominator);
        }

        if ((*o_numerator)->FLAGS.IS_ZERO)
        {
            // o の絶対値が 0 の場合は符号を 0 に 修正する
            *sign = SIGN_ZERO;
        }

        root.UnlinkNumber(*o_numerator);
        root.UnlinkNumber(*o_denominator);
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o_numerator, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        if (source == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"source");
        if (o_numerator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o_numerator");
        if (o_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o_denominator");
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        ResourceHolderSINT root;
        SIGN_T o_numerator_sign;
        PMC_HANDLE_UINT o_numerator_abs;
        PMC_STATUS_CODE err = TryParse_Imp(source, number_styles, format_option, &o_numerator_sign, &o_numerator_abs, o_denominator);
        if (err != PMC_STATUS_OK)
            return (err);
        root.HookNumber(o_numerator_abs);
        root.HookNumber(*o_denominator);
        NUMBER_OBJECT_SINT* no_numerator = root.AllocateNumber(o_numerator_sign, o_numerator_abs);
        *o_numerator = GET_NUMBER_HANDLE(no_numerator);
        root.UnlinkNumber(*o_denominator);
        root.UnlinkNumber(no_numerator);
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false)
    {
        PMC_STATUS_CODE rc;
        if (source == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"source");
        if (o == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o");
        ResourceHolderSINT root;
        SIGN_T o_sign;
        PMC_HANDLE_UINT o_abs;
        if ((rc = ep_uint.TryParseForSINT(source, number_styles, format_option, &o_sign, &o_abs)) != PMC_STATUS_OK)
            return (rc);
        root.HookNumber(o_abs);
        NUMBER_OBJECT_SINT* no = root.AllocateNumber(o_sign, o_abs);
        *o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE Initialize_Parse()
    {
        ep_uint.InitializeNumberFormatInfo(&default_number_format_option);

        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */