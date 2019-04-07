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


#include "pmc_parserstate.h"
#include "pmc_parser.h"


namespace Palmtree::Math::Core::Internal
{

    ParserState::ParserState(const wchar_t * in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * sign, wchar_t * int_part_buf, size_t int_part_buf_size, wchar_t * frac_part_buf, size_t frac_part_buf_size, SIGN_T * exponent_sign, wchar_t * exp_part_buf, size_t exp_part_buf_size)
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

    bool ParserState::ParseAsHexNumberString()
    {
        if (_number_styles & PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE)
            _source.SkipSpace();
        ParseAsIntegerPartNumberSequence();
        if (_number_styles & PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE)
            _source.SkipSpace();
        if (_source.PeekChar() != L'\0')
            return (false);
        return (true);
    }

    bool ParserState::ParseAsExponentPartNumberSequence()
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

    void ParserState::ParseAsFractionPartNumberSequence()
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

    void ParserState::ParseAsIntegerPartNumberSequence()
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

    bool ParserState::ParseAsDecimalNumberString()
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

    ParserState::~ParserState()
    {
    }

}


/*
 * END OF FILE
 */