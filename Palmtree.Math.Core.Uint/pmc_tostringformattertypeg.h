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

#ifndef PMC_TOSTRING_FORMATTER_TYPE_G_H
#define PMC_TOSTRING_FORMATTER_TYPE_G_H

#include "pmc_tostringformatter.h"

namespace Palmtree::Math::Core::Internal
{

    class ToStringFormatterTypeG
        : public ToStringFormatter
    {
        /*
            g/G�w�莞�̒���
            1)�������̍ŉ��ʂ̘A������0�͏ȗ������
            2)���x�w��q�́u�L�������v�Ɖ��߂����B
            3)���x�w��q��0�̏ꍇ�͊���̐��x(15)�ƂȂ�
            4)�w����-5���傫�����x�w��q��菬�����ꍇ�͌Œ菬���\�L�A����ȊO�̏ꍇ�͎w���\�L�ŕ\�������B
            5)���l��0�̏ꍇ��1)��4)���ɂ��P��0�ƕ\�������B
            6)�w���\�L�̏ꍇ�A�w�����͍Œ�ł�2���\�������B
        */

    private:
        bool _is_exponential_format;

    public:
        ToStringFormatterTypeG(ThreadContext& tc, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info);

    protected:
        virtual int GetDefaultPrecisionValue(int specified_precision) override;
        virtual void WriteZeroValue(StringWriter& writer) override;
        virtual void RoundValue(NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, NUMBER_OBJECT_UINT** r_numerator, NUMBER_OBJECT_UINT** r_denominator, _INT32_T* exp);
        virtual void WritePrefix(SIGN_T x_sign, StringWriter& writer) override;
        virtual size_t GetFractionPartLength() override;
        virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter& writer) override;
        virtual void WriteSuffix(SIGN_T x_sign, StringWriter& writer) override;
    };

}


#endif


/*
 * END OF FILE
 */