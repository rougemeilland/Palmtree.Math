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

#ifndef PMC_TOSTRING_FORMATTER_TYPE_P_H
#define PMC_TOSTRING_FORMATTER_TYPE_P_H

#include "pmc_tostringformatter.h"

namespace Palmtree::Math::Core::Internal
{

    class ToStringFormatterTypeP
        : public ToStringFormatter
    {
    public:
        ToStringFormatterTypeP(ThreadContext& tc, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info);

    protected:
        virtual int GetDefaultPrecisionValue(int specified_precision) override;
        virtual void WriteZeroValue(StringWriter& writer) override;
        virtual void RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT** r_numerator, NUMBER_OBJECT_UINT** r_denominator, _INT32_T* exp);
        virtual void WritePrefix(SIGN_T x_sign, StringWriter& writer) override;
        virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter& writer) override;
        virtual void WriteSuffix(SIGN_T x_sign, StringWriter& writer) override;

    };

}


#endif


/*
 * END OF FILE
 */