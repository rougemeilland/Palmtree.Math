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

#ifndef PMC_TOSTRING_FORMATTER_CUSTOM_H
#define PMC_TOSTRING_FORMATTER_CUSTOM_H


#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_stringio.h"
#include "pmc_bidirectionallistheader.h"


namespace Palmtree::Math::Core::Internal::CustomFormat
{

    class SectionToken;
    class LiteralToken;
    class IntPartPlaceHolderToken;
    class DecimalSeparaterToken;
    class FracPartPlaceHolderToken;
    class ExponentToken;
    class PercentToken;

    class FormatToken
        : public BidirectionalListHeader<FormatToken>
    {
    public:
        FormatToken();
    private:
        FormatToken(const FormatToken& p);
    public:
        virtual ~FormatToken();
        void Remove(ThreadContext& tc);
        virtual SectionToken* ToSection();
        virtual LiteralToken* ToLiteral();
        virtual IntPartPlaceHolderToken* ToIntPartPlaceHolder();
        virtual DecimalSeparaterToken* ToDecimalSeparater();
        virtual FracPartPlaceHolderToken* ToFracPartPlaceHolder();
        virtual ExponentToken* ToExponent();
        virtual PercentToken* ToPercent();
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer);
        virtual int StringCount();
    };

    class SectionToken
        : public FormatToken
    {
    private:
        ThreadContext& _tc;
        FormatToken _section_root;
        int _10_factor;
        bool _enabled_grouping;
        int _max_int_part_length;
        int _min_int_part_length;
        int _max_frac_part_length;
        int _min_frac_part_length;
        bool _exists_multi_section;
        ExponentToken* _exponent_part;
        DecimalSeparaterToken* _decimal_point_separater;

    public:
        SectionToken(ThreadContext& tc);
        virtual ~SectionToken();
        virtual SectionToken* ToSection() override;
        void Parse(bool exists_multi_section);
        void Format(SectionToken* alternative_section, const PMC_NUMBER_FORMAT_INFO& format_option, SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, StringWriter& writer);
        void AppendLiteral(const wchar_t* reference, int reference_count);
        void AppendIntPartPlaceHolder(const PMC_NUMBER_FORMAT_INFO& format_option, bool first, const wchar_t digit);
        void AppendDecimalSeparaterToken(const PMC_NUMBER_FORMAT_INFO& format_option);
        void AppendFracPartPlaceHolder(const wchar_t digit);
        void AppendExponent(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t header, int zero_count);
        void AppendExponent(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t header, wchar_t sign, int zero_count);
        void AppendPercent(const PMC_NUMBER_FORMAT_INFO& format_option, const wchar_t digit);
        bool IsEmpty();
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;


    private:
        void WriteZeroValue(const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter& writer);
        void ApplyPlaceHolder(const PMC_NUMBER_FORMAT_INFO & format_option, const wchar_t* t_int_buf_writer, const wchar_t* frac_buf_writer, int exp, StringWriter & writer);
        void Times10n_R(ThreadContext& tc, ResourceHolderUINT& root, NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, int e, NUMBER_OBJECT_UINT ** r_numerator, NUMBER_OBJECT_UINT ** r_denominator);
    };

    class LiteralToken
        : public FormatToken
    {
    private:
        const wchar_t* _reference;
        int _reference_count;

    public:
        LiteralToken(const wchar_t* reference, int reference_count);
        virtual LiteralToken* ToLiteral() override;
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class IntPartPlaceHolderToken
        : public FormatToken
    {
    private:
        const PMC_NUMBER_FORMAT_INFO& _format_option;

    public:
        bool _first;
        int _index;
        wchar_t _letter;

        IntPartPlaceHolderToken(const PMC_NUMBER_FORMAT_INFO& _format_option, bool first, wchar_t letter);
        wchar_t GetLetter();
        void SetLetter(wchar_t letter);
        int GetIndex();
        void SetIndex(int index);
        virtual IntPartPlaceHolderToken* ToIntPartPlaceHolder() override;
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class DecimalSeparaterToken
        : public FormatToken
    {
    private:
        const PMC_NUMBER_FORMAT_INFO& _format_option;

    public:
        DecimalSeparaterToken(const PMC_NUMBER_FORMAT_INFO& _format_option);
        virtual DecimalSeparaterToken* ToDecimalSeparater() override;
        void Format(const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter& writer);
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class FracPartPlaceHolderToken
        : public FormatToken
    {
    public:
        wchar_t _letter;
        int _index;

        FracPartPlaceHolderToken(wchar_t letter);
        virtual FracPartPlaceHolderToken* ToFracPartPlaceHolder() override;
        wchar_t GetLetter();
        void SetLetter(wchar_t letter);
        int GetIndex();
        void SetIndex(int index);
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class ExponentToken
        : public FormatToken
    {
    public:
        const PMC_NUMBER_FORMAT_INFO& _format_option;
        wchar_t _header;
        wchar_t _sign;
        int _zero_count;

        ExponentToken(const PMC_NUMBER_FORMAT_INFO& _format_option, wchar_t header, wchar_t sign, int zero_count);
        virtual ExponentToken* ToExponent() override;
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class PercentToken
        : public FormatToken
    {
    public:
        const PMC_NUMBER_FORMAT_INFO& _format_option;
        wchar_t _letter;

        PercentToken(const PMC_NUMBER_FORMAT_INFO& _format_option, wchar_t letter);
        wchar_t GetLetter();
        virtual PercentToken* ToPercent() override;
        virtual void Format(StringReader& source_reader, int exponent, StringWriter& writer) override;
        virtual int StringCount() override;
    };

    class ToStringFormatterCustom
    {

    private:
        ThreadContext& _tc;
        const wchar_t* _format;
        const PMC_NUMBER_FORMAT_INFO& _format_option;
        FormatToken _root;
        SectionToken* _section0_root;
        SectionToken* _section1_root;
        SectionToken* _section2_root;

    public:
        ToStringFormatterCustom(ThreadContext& tc, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option);
        virtual ~ToStringFormatterCustom();
        void Format(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, StringWriter& writer);

    private:
        SectionToken* AppendSection();
        void Parse();
        int SkipZero(const wchar_t*& ptr);

        // コピーコンストラクタは呼び出し禁止
        ToStringFormatterCustom(const ToStringFormatterCustom& p);

    };

}


#endif


/*
 * END OF FILE
 */