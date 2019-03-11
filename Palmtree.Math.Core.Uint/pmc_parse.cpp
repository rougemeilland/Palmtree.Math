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
#include "pmc_exception.h"
#include "pmc_stringio.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static PMC_NUMBER_FORMAT_INFO default_number_format_option;
    static __UNIT_TYPE* (*fp_MultiplyAndAdd)(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE x);

    static int ParseDecimalDigit(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (c - L'0');
        return (-1);
    }

    static int ParseHexDigit(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (c - L'0');

        if (c >= L'a' && c <= L'f')
            return (c - L'a' + 10);

        if (c >= L'A' && c <= L'F')
            return (c - L'A' + 10);
        return (-1);
    }

    class ParserState
    {
    private:
        StringReader _source;
        StringWriter _int_part;
        StringWriter _frac_part;
        _UINT32_T _number_styles;
        char* _sign;
        wchar_t _currency_symbol[17];
        wchar_t _positive_sign[17];
        wchar_t _negative_sign[17];
        wchar_t _decimal_separator[17];
        wchar_t _group_separator[17];
        wchar_t _secondary_group_separator[17];
        //bool _エラーを例外で通知する;
        //bool _負数を許可する;

    public:
        ParserState(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size)
            : _source(in_ptr), _int_part(int_part_buf, int_part_buf_size), _frac_part(frac_part_buf, frac_part_buf_size)
        {
            _sign = sign;
            _number_styles = number_styles;
            //_エラーを例外で通知する = (_number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING) != 0;
            //_負数を許可する = (_number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER) != 0;
            *_sign = 1;

            // 通貨単位の設定
            if (countof(_currency_symbol) < lstrlenW(format_option->CurrencySymbol) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;1");
            lstrcpyW(_currency_symbol, format_option->CurrencySymbol);

            // 符号文字の設定
            if (countof(_positive_sign) < lstrlenW(format_option->PositiveSign) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;2");
            lstrcpyW(_positive_sign, format_option->PositiveSign);
            if (countof(_negative_sign) < lstrlenW(format_option->NegativeSign) + 1)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;3");
            lstrcpyW(_negative_sign, format_option->NegativeSign);

            // 小数点/3桁区切り文字の設定
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL)
            {
                if (countof(_decimal_separator) < lstrlenW(format_option->Currency.DecimalSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;4");
                lstrcpyW(_decimal_separator, format_option->Currency.DecimalSeparator);
                if (countof(_group_separator) < lstrlenW(format_option->Currency.GroupSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;5");
                lstrcpyW(_group_separator, format_option->Currency.GroupSeparator);
            }
            else
            {
                if (countof(_decimal_separator) < lstrlenW(format_option->Number.DecimalSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;6");
                lstrcpyW(_decimal_separator, format_option->Number.DecimalSeparator);
                if (countof(_group_separator) < lstrlenW(format_option->Number.GroupSeparator) + 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse;ParserState::ParserState;7");
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

        int ParseAsDecimalNumberString()
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
                    *_sign = 1;
                    _source.SkipString(_positive_sign);
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = -1;
                    _source.SkipString(_negative_sign);
                    if (ParseDecimalDigit(_source.PeekChar()) >= 0)
                        ParseAsIntegerPartNumberSequence();
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT) && _source.StartsWith(_decimal_separator))
                    {
                        _source.SkipString(_decimal_separator);
                        _frac_part.Write(L'.');
                        ParseAsFractionPartNumberSequence();
                    }
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
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                    {
                        *_sign = 1;
                        _source.SkipString(_positive_sign);
                    }
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = -1;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
            }
            else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_PARENTHESES) && _source.StartsWith(L"(") /*&& 負数のエラーチェック()*/)
            {
                *_sign = -1;
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
                *_sign = 1;
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
                *_sign = -1;
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
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                {
                    _source.SkipString(L" ");
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                    {
                        _source.SkipString(_currency_symbol);
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = 1;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = -1;
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
                            *_sign = 1;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = -1;
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
                        *_sign = 1;
                        _source.SkipString(_positive_sign);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = -1;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                {
                    *_sign = 1;
                    _source.SkipString(_positive_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = -1;
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
                if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE) && _source.StartsWith(L" "))
                {
                    _source.SkipString(L" ");
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                    {
                        _source.SkipString(_currency_symbol);
                        if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                        {
                            *_sign = 1;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = -1;
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
                            *_sign = 1;
                            _source.SkipString(_positive_sign);
                        }
                        else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                        {
                            *_sign = -1;
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
                        *_sign = 1;
                        _source.SkipString(_positive_sign);
                    }
                    else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                    {
                        *_sign = -1;
                        _source.SkipString(_negative_sign);
                    }
                    else
                    {
                    }
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_positive_sign))
                {
                    *_sign = 1;
                    _source.SkipString(_positive_sign);
                    if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL) && _source.StartsWith(_currency_symbol))
                        _source.SkipString(_currency_symbol);
                }
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN) && _source.StartsWith(_negative_sign) /*&& 負数のエラーチェック()*/)
                {
                    *_sign = -1;
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
                return (0);
            return (1);
        }

        int ParseAsHexNumberString()
        {
            if (_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE)
                _source.SkipSpace();
            ParseAsIntegerPartNumberSequence();
            if (_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE)
                _source.SkipSpace();
            if (_source.PeekChar() != L'\0')
                return (0);
            return (1);
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
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER) && ParseHexDigit(c) >= 0)
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
                else if ((_number_styles & PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER) && ParseHexDigit(c) >= 0)
                {
                    _frac_part.Write(c);
                    _source.Progress();
                }
                else
                    break;
            }
        }
    };

    // 10進数の数値を表す文字列を符号、整数部、小数部に分解する。数値が明らかに正である場合は *flag に 1、明らかに負である場合は *flag に -1 が格納され、数値が正か 0 か明らかには判断できない場合は *flag に 1 が格納される。
    static int ParseAsDecimalNumberString(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size)
    {
        ParserState state(in_ptr, number_styles, format_option, sign, int_part_buf, int_part_buf_size, frac_part_buf, frac_part_buf_size);
        return (state.ParseAsDecimalNumberString());
    }

    static __UNIT_TYPE BuildLeading1WordFromDecimalString(wchar_t* in_ptr, __UNIT_TYPE count)
    {
        __UNIT_TYPE x = 0;
        while (count > 0)
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            --count;
        }
        return (x);
    }

    static __UNIT_TYPE Build1WordFromDecimalString(wchar_t* in_ptr)
    {
        __UNIT_TYPE x = ParseDecimalDigit(*in_ptr++);
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
        }
        if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
        {
            x = x * 10 + ParseDecimalDigit(*in_ptr++);
        }
        return (x);
    }

    // 16進数の数値を表す文字列から整数部を抽出する。
    // 10進整数を表す文字列を、word_digit_count 毎に 1 ワードずつ分割してバイナリー化し、out_buf に格納する。
    static void BuildBinaryFromDecimalString(wchar_t* source, __UNIT_TYPE* out_buf, __UNIT_TYPE* out_buf_count)
    {
#ifdef _M_IX86
        int word_digit_count = 9;
#elif defined(_M_X64)
        int word_digit_count = 19;
#else
#error unknown platform
#endif
        wchar_t* in_ptr = source;
        __UNIT_TYPE* out_ptr = out_buf;
        __UNIT_TYPE source_count = lstrlenW(source);
        int r = source_count % word_digit_count;
        if (r > 0)
        {
            *out_ptr++ = BuildLeading1WordFromDecimalString(in_ptr, r);
            in_ptr += r;
            source_count -= r;
        }
        while (source_count > 0)
        {
            *out_ptr++ = Build1WordFromDecimalString(in_ptr);
            in_ptr += word_digit_count;
            source_count -= word_digit_count;
        }
        *out_buf_count = out_ptr - out_buf;
    }

    __inline static __UNIT_TYPE MultiplyAndAdd1Word_using_ADC_MUL(__UNIT_TYPE k, __UNIT_TYPE u, __UNIT_TYPE* w_buf)
    {
#ifdef _M_IX86
        __UNIT_TYPE base_value = 1000000000U; // 10^9
#elif defined(_M_X64)
        __UNIT_TYPE base_value = 10000000000000000000UL; // 10^19
#else
#error unknown platform
#endif
        __UNIT_TYPE t_hi;
        __UNIT_TYPE t_lo = _MULTIPLY_UNIT(u, base_value, &t_hi);
        _ADD_UNIT(_ADD_UNIT(0, t_lo, k, w_buf), t_hi, 0, &k);
        return (k);
    }

    __inline static __UNIT_TYPE MultiplyAndAdd1Word_using_ADCX_MULX(__UNIT_TYPE k, __UNIT_TYPE u, __UNIT_TYPE* w_buf)
    {
#ifdef _M_IX86
        __UNIT_TYPE base_value = 1000000000U; // 10^9
#elif defined(_M_X64)
        __UNIT_TYPE base_value = 10000000000000000000UL; // 10^19
#else
#error unknown platform
#endif
        __UNIT_TYPE t_hi;
        __UNIT_TYPE t_lo = _MULTIPLYX_UNIT(u, base_value, &t_hi);
        _ADDX_UNIT(_ADDX_UNIT(0, t_lo, k, w_buf), t_hi, 0, &k);
        return (k);
    }

    static __UNIT_TYPE* MultiplyAndAdd_using_ADC_MUL(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE x)
    {
        __UNIT_TYPE k = x;
        __UNIT_TYPE count = u_count >> 5;
        while (count > 0)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[7], &u_buf[7]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[8], &u_buf[8]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[9], &u_buf[9]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[10], &u_buf[10]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[11], &u_buf[11]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[12], &u_buf[12]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[13], &u_buf[13]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[14], &u_buf[14]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[15], &u_buf[15]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[16], &u_buf[16]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[17], &u_buf[17]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[18], &u_buf[18]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[19], &u_buf[19]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[20], &u_buf[20]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[21], &u_buf[21]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[22], &u_buf[22]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[23], &u_buf[23]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[24], &u_buf[24]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[25], &u_buf[25]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[26], &u_buf[26]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[27], &u_buf[27]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[28], &u_buf[28]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[29], &u_buf[29]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[30], &u_buf[30]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[31], &u_buf[31]);
            u_buf += 32;
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(32);
            else
                AddToMULTI64Counter(32);
#endif
        }

        if (u_count & 0x10)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[7], &u_buf[7]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[8], &u_buf[8]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[9], &u_buf[9]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[10], &u_buf[10]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[11], &u_buf[11]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[12], &u_buf[12]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[13], &u_buf[13]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[14], &u_buf[14]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[15], &u_buf[15]);
            u_buf += 16;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(16);
            else
                AddToMULTI64Counter(16);
#endif
        }

        if (u_count & 0x8)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[7], &u_buf[7]);
            u_buf += 8;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(8);
            else
                AddToMULTI64Counter(8);
#endif
        }

        if (u_count & 0x4)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[3], &u_buf[3]);
            u_buf += 4;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(4);
            else
                AddToMULTI64Counter(4);
#endif
        }

        if (u_count & 0x2)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[1], &u_buf[1]);
            u_buf += 2;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }

        if (u_count & 0x1)
        {
            k = MultiplyAndAdd1Word_using_ADC_MUL(k, u_buf[0], &u_buf[0]);
            u_buf += 1;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }

        if (k > 0)
        {
            u_buf[0] = k;
            u_buf += 1;
        }

        return (u_buf);
    }

    static __UNIT_TYPE* MultiplyAndAdd_using_ADCX_MULX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE x)
    {
        __UNIT_TYPE k = x;
        __UNIT_TYPE count = u_count >> 5;
        while (count > 0)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[7], &u_buf[7]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[8], &u_buf[8]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[9], &u_buf[9]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[10], &u_buf[10]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[11], &u_buf[11]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[12], &u_buf[12]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[13], &u_buf[13]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[14], &u_buf[14]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[15], &u_buf[15]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[16], &u_buf[16]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[17], &u_buf[17]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[18], &u_buf[18]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[19], &u_buf[19]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[20], &u_buf[20]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[21], &u_buf[21]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[22], &u_buf[22]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[23], &u_buf[23]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[24], &u_buf[24]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[25], &u_buf[25]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[26], &u_buf[26]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[27], &u_buf[27]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[28], &u_buf[28]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[29], &u_buf[29]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[30], &u_buf[30]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[31], &u_buf[31]);
            u_buf += 32;
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(32);
            else
                AddToMULTI64Counter(32);
#endif
        }

        if (u_count & 0x10)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[7], &u_buf[7]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[8], &u_buf[8]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[9], &u_buf[9]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[10], &u_buf[10]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[11], &u_buf[11]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[12], &u_buf[12]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[13], &u_buf[13]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[14], &u_buf[14]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[15], &u_buf[15]);
            u_buf += 16;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(16);
            else
                AddToMULTI64Counter(16);
#endif
        }

        if (u_count & 0x8)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[3], &u_buf[3]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[4], &u_buf[4]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[5], &u_buf[5]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[6], &u_buf[6]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[7], &u_buf[7]);
            u_buf += 8;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(8);
            else
                AddToMULTI64Counter(8);
#endif
        }

        if (u_count & 0x4)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[1], &u_buf[1]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[2], &u_buf[2]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[3], &u_buf[3]);
            u_buf += 4;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(4);
            else
                AddToMULTI64Counter(4);
#endif
        }

        if (u_count & 0x2)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[1], &u_buf[1]);
            u_buf += 2;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }

        if (u_count & 0x1)
        {
            k = MultiplyAndAdd1Word_using_ADCX_MULX(k, u_buf[0], &u_buf[0]);
            u_buf += 1;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }

        if (k > 0)
        {
            u_buf[0] = k;
            u_buf += 1;
        }

        return (u_buf);
    }

    static void ConvertCardinalNumber(__UNIT_TYPE* in_buf, __UNIT_TYPE in_buf_count, __UNIT_TYPE* out_buf)
    {
        ResourceHolderUINT root;
        __UNIT_TYPE* work_buf = root.AllocateBlock(__UNIT_TYPE_BIT_COUNT * (in_buf_count + 1));
        __UNIT_TYPE work_buf_count = 1;
        work_buf[0] = in_buf[0];
        ++in_buf;
        --in_buf_count;
        while (in_buf_count > 0)
        {
            __UNIT_TYPE* w_tail = (*fp_MultiplyAndAdd)(work_buf, work_buf_count, *in_buf);
            work_buf_count = w_tail - work_buf;
            ++in_buf;
            --in_buf_count;
        }
        root.CheckBlock(work_buf);
        _COPY_MEMORY_UNIT(out_buf, work_buf, work_buf_count);
    }

    static PMC_STATUS_CODE TryParseDN(const wchar_t* source, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, NUMBER_HEADER** o_abs, _UINT32_T* result)
    {
#ifdef _M_IX86
        int word_digit_count = 9;
#elif defined(_M_X64)
        int word_digit_count = 19;
#else
#error unknown platform
#endif

        ResourceHolderUINT root;

        __UNIT_TYPE source_len = lstrlenW(source);

        size_t int_part_buf_count = source_len + 1;
        wchar_t* int_part_buf = root.AllocateString(int_part_buf_count);
        size_t frac_part_buf_count = source_len + 1;
        wchar_t* frac_part_buf = root.AllocateString(frac_part_buf_count);
        bool result_parsing = ParseAsDecimalNumberString(source, number_styles, format_option, o_sign, int_part_buf, int_part_buf_count, frac_part_buf, frac_part_buf_count);
        root.CheckString(int_part_buf);
        root.CheckString(frac_part_buf);
        if (!result_parsing)
        {
            *result = 0;
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                return (PMC_STATUS_FORMAT_ERROR);
            return (PMC_STATUS_OK);
        }
        if (int_part_buf[0] == L'\0' && (frac_part_buf[0] == L'\0' || frac_part_buf[0] == L'.' && frac_part_buf[1] == L'\0'))
        {
            // 整数部と小数部がともに空ならばエラーとする
            *result = 0;
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                return (PMC_STATUS_FORMAT_ERROR);
            return (PMC_STATUS_OK);
        }

        if (*o_sign < 0 && frac_part_buf[0] != L'\0')
        {
            // 負の符号が含まれていて、かつ小数部が存在する場合はエラー (OverflowException) とする。(小数点のみや小数部が '0' の連続のみでも存在するうちに入る)
            // ※エラーの条件がそうなっている根拠は不明だが実際問題として uint.Parse などではそうなっているため、それに合わせる。

            if ((number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER) == 0)
            {
                // 負数が許可されていない場合

                *result = 0;
                if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                    return (PMC_STATUS_OVERFLOW);
                return (PMC_STATUS_OK);
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

        // 小数部が 0 ではない場合、エラーとする
        if (!(frac_part_buf[0] == L'\0' || frac_part_buf[0] == L'.' && frac_part_buf[1] == L'\0'))
        {
            *result = 0;
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                return (PMC_STATUS_OVERFLOW);
            return (PMC_STATUS_OK);
        }

        if (int_part_buf[0] == L'\0')
        {
            // 整数部が空である場合

            // 符号を 0 に 修正する
            *o_sign = 0;

            // 整数部に 0 を設定する
            int_part_buf[0] = L'0';
            int_part_buf[1] = L'\0';
        }

        if (*o_sign < 0)
        {
            // 数値が負である場合

            if ((number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER) == 0)
            {
                // 負数が許可されていない場合

                *result = 0;
                if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                    return (PMC_STATUS_OVERFLOW);
                return (PMC_STATUS_OK);
            }
        }

        // 小数部は捨てる
        root.DeallocateString(frac_part_buf);

        // 整数部を 10^word_digit_count を基数としたバイト列に変換する
        __UNIT_TYPE* bin_buf = root.AllocateBlock(_DIVIDE_CEILING_SIZE(lstrlenW(int_part_buf), word_digit_count) * __UNIT_TYPE_BIT_COUNT);
        __UNIT_TYPE bin_buf_count;
        BuildBinaryFromDecimalString(int_part_buf, bin_buf, &bin_buf_count);
        root.CheckBlock(bin_buf);
        root.DeallocateString(int_part_buf);

        // 10^word_digit_count を基数としたバイト列を 10 を基数としたバイト列に変換する
        __UNIT_TYPE o_bit_count = bin_buf_count * __UNIT_TYPE_BIT_COUNT;
        *o_abs = root.AllocateNumber(o_bit_count);
        ConvertCardinalNumber(bin_buf, bin_buf_count, (*o_abs)->BLOCK);
        root.CheckNumber(*o_abs);
        root.DeallocateBlock(bin_buf);
        CommitNumber(*o_abs);
        if ((*o_abs)->IS_ZERO)
        {
            root.DeallocateNumber(*o_abs);
            *o_abs = &number_zero;
        }
        else
            root.UnlinkNumber(*o_abs);
#ifdef _DEBUG
        if (*o_sign != 0 && *o_sign != 1 && *o_sign != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;TryParseDN;1");
        if (*o_sign == 0 && !(*o_abs)->IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;TryParseDN;2");
        if (*o_sign != 0 && (*o_abs)->IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_parse.cpp;TryParseDN;3");
#endif
        *result = 1;
        return (PMC_STATUS_OK);
    }

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
        char dummy_sign;
        ParserState state(in_ptr, number_styles, format_option, &dummy_sign, int_part_buf, int_part_buf_size, nullptr, 0);
        return (state.ParseAsHexNumberString());
    }

    static PMC_STATUS_CODE TryParseX(const wchar_t* source, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, NUMBER_HEADER** o_abs, _UINT32_T* result)
    {
        ResourceHolderUINT root;
        __UNIT_TYPE source_len = lstrlenW(source);
        size_t int_part_buf_size = source_len + 1;
        wchar_t* int_part_buf = root.AllocateString(source_len + 1);
        int result_parsing = ParseAsHexNumberString(source, number_styles, format_option, int_part_buf, int_part_buf_size);
        root.CheckString(int_part_buf);
        if (!result_parsing || int_part_buf[0] == L'\0')
        {
            *result = 0;
            if (number_styles & PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING)
                return (PMC_STATUS_FORMAT_ERROR);
            return (PMC_STATUS_OK);
        }

        // 先頭 1 文字が 8～F であれば負数とみなす
        if (ParseHexDigit(int_part_buf[0]) >= 8)
        {
            // 先頭 1 文字が 8～F であれば負数とみなす
            if (!(number_styles & PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER))
            {
                // 負数が許可されていないにもかかわらず先頭文字が'8'～'F'である場合

                // そのまま正数として扱う
                *o_sign = 1;
            }
            else
            {
                // 負数が許可されていて先頭文字が'8'～'F'である場合

                // 負数として扱う
                *o_sign = -1;
            }
        }
        else
        {
            // 先頭 1 文字が 0～7 であれば正数とみなす
            *o_sign = 1;
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
            *o_sign = 0;
            *o_abs = &number_zero;
        }
        else
            root.UnlinkNumber(*o_abs);
        *result = 1;
        return (PMC_STATUS_OK);
    }

    static PMC_STATUS_CODE PMC_TryParse_Imp(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, NUMBER_HEADER** o_abs, _UINT32_T* result)
    {
        ResourceHolderUINT root;
        if (number_styles & PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER)
        {
            // 16進数の場合

            // 許可されている組み合わせのフラグ
            _UINT32_T mask = PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER | PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE | PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE | PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING | PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER;

            // 許可されていないフラグが指定されていればエラー
            if (number_styles & ~mask)
                throw ArgumentException(L"引数number_stylesに許可されていない組み合わせのフラグが指定されました。");

            PMC_STATUS_CODE err = TryParseX(source, number_styles, format_option, o_sign, o_abs, result);
            if (err != PMC_STATUS_OK || !*result)
                return (err);
            root.HookNumber(*o_abs);
        }
        else
        {
            // 10進数の場合
            PMC_STATUS_CODE err = TryParseDN(source, number_styles, format_option, o_sign, o_abs, result);
            if (err != PMC_STATUS_OK || !*result)
                return (err);
            root.HookNumber(*o_abs);
        }
#ifdef _DEBUG
        CheckNumber(*o_abs);
#endif
        root.UnlinkNumber(*o_abs);
        *result = 1;
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE __PMC_CALL PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o, _UINT32_T* result) noexcept(false)
    {
        if (source == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"source");
        if (o == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"o");
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        ResourceHolderUINT root;
        char o_sign;
        NUMBER_HEADER* o_abs;
        PMC_STATUS_CODE err = PMC_TryParse_Imp(source, number_styles, format_option, &o_sign, &o_abs, result);
        if (err != PMC_STATUS_OK || !*result)
        {
            *result = 0;
            return (err);
        }
        root.HookNumber(o_abs);
        if (o_sign < 0)
        {
            // 負数は表現できないのでエラーとする
            *result = 0;
            return (PMC_STATUS_OVERFLOW);
        }
        *o = (PMC_HANDLE_UINT)o_abs;
        root.UnlinkNumber(o_abs);
        *result = 1;
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE __PMC_CALL PMC_TryParseForSINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, PMC_HANDLE_UINT* o_abs, _UINT32_T* result)
    {
        if (source == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"source");
        if (o_sign == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"o_sign");
        if (o_abs == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"o_abs");
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        NUMBER_HEADER* no_abs;
        PMC_STATUS_CODE err = PMC_TryParse_Imp(source, number_styles, format_option, o_sign, &no_abs, result);
        if (err != PMC_STATUS_OK)
        {
            *result = 0;
            return (err);
        }
        *o_abs = (PMC_HANDLE_UINT)no_abs;
        *result = 1;
        return (PMC_STATUS_OK);
    }

    PMC_STATUS_CODE Initialize_Parse(PROCESSOR_FEATURES* feature)
    {
        InitializeNumberFormatoInfo(&default_number_format_option);

        if (feature->PROCESSOR_FEATURE_ADX && feature->PROCESSOR_FEATURE_BMI2)
            fp_MultiplyAndAdd = MultiplyAndAdd_using_ADCX_MULX;
        else
            fp_MultiplyAndAdd = MultiplyAndAdd_using_ADC_MUL;

        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */