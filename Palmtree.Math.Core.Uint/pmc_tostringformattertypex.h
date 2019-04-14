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

#ifndef PMC_TOSTRING_FORMATTER_TYPE_X_H
#define PMC_TOSTRING_FORMATTER_TYPE_X_H


#include "pmc_uint_internal.h"
#include "pmc_stringio.h"


namespace Palmtree::Math::Core::Internal
{

    class ToStringFormatterTypeX
    {
    private:
        ThreadContext& _tc;
        wchar_t _format_type;
        int _precision;
        const PMC_NUMBER_FORMAT_INFO* _number_format_info;
        const wchar_t* _character_set;
    public:
        ToStringFormatterTypeX(ThreadContext& tc, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info);
        void Format(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_abs, StringWriter& writer);

    protected:
        int GetDefaultPrecisionValue(int specified_precision);
        void WriteZeroValue(StringWriter& writer);
        void WriteValue(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_abs, StringWriter& writer);
    };
}


#endif


/*
 * END OF FILE
 */