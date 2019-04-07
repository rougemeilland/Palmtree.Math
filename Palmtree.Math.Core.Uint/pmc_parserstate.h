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


#pragma once

#ifndef PMC_PARSER_STATE_H
#define PMC_PARSER_STATE_H


#include "pmc_uint_internal.h"
#include "pmc_stringio.h"


namespace Palmtree::Math::Core::Internal
{

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
        ParserState(const wchar_t* in_ptr, _UINT32_T number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* sign, wchar_t* int_part_buf, size_t int_part_buf_size, wchar_t* frac_part_buf, size_t frac_part_buf_size, SIGN_T* exponent_sign, wchar_t* exp_part_buf, size_t exp_part_buf_size);
        ~ParserState();
        bool ParseAsDecimalNumberString();
        bool ParseAsHexNumberString();

    private:
        void ParseAsIntegerPartNumberSequence();
        void ParseAsFractionPartNumberSequence();
        bool ParseAsExponentPartNumberSequence();
    };

}

#endif


/*
 * END OF FILE
 */