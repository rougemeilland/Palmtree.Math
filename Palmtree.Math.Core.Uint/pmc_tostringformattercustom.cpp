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


#include "pmc_tostringformattercustom.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_threadcontext.h"
#include "pmc_thousandseparatedstringwriter.h"
#include "pmc_string.h"
#include "pmc_lock.h"


namespace Palmtree::Math::Core::Internal::CustomFormat
{

    // 【実験結果】
    // %と‰の効果は重複してかかる。%が2個なら100*100倍、%と‰なら100*1000倍。%と‰はどこに書かれていてもそのとおりの場所で表示される。【例：(-1.23456789).ToString("0■%■0") => -12■%■3 】
    // '#', '0', '.', ','をまず抜き出して数値を文字列化し、そのあとで'#', '0'のある場所に数値をはめ込む、みたいな実装になっているらしい。
    // ⇒小数部は小数点を基準に上位から順に1文字ずつはめ込まれ、はめ込めなかった分は四捨五入されて必要ならば繰り上がる。
    // ⇒整数部は小数点を基準に下位から順に1文字ずつはめ込まれる。
    // '.'の後に書かれている','は無視される。また、最初の '0', '#' の前に書かれている ',' は無視される。
    // 整数部にて、'0'の後に書かれている'#'は'0'と解釈される。
    // 小数部にて、'0'の前に書かれている'#'は'0'と解釈される。
    // '.'の前に '0'または '#'が一つもない場合は、'#' が一つだけあると解釈される。
    // 整数部の符号は最初の '#', '0'の前にどんなテキストがあろうとあらゆるテキストの最初に表示される。正値のときに自動的には'+'は表示されない。
    // Eの構文解析に失敗した場合はEは(そしてその次の+あるいは-も)一般テキストとしてそのまま表示される。
    // ⇒【例：(1.23456789).ToString("0.0E+#0  000") => 1.2E+34  568】
    // 逆に、構文として正しければEはどこに記述されていてもその場所のまま表示される。
    // ⇒【例：(-0.0123456789).ToString("0.0E+0  000") => -1.2E-2  346】
    // '.' が複数ある場合は最初のものを除いて無視される。【例：(-0.0123456789).ToString("0.0 00.00") => -0.0 1235】
    // 三つ目の';'の後の文字列は数値の符号が何であっても表示されない。つまり無視される。


#ifdef _M_IX86
    static const __UNIT_TYPE _10n_base_number = 1000000000U; // 10^9
    static const size_t _digit_count_on_word = 9;
#elif defined (_M_X64)
    static const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
    static const size_t _digit_count_on_word = 19;
#else
#error unknown platform
#endif

    FormatToken::FormatToken()
        : BidirectionalListHeader<FormatToken>(this)
    {
    }

    FormatToken::~FormatToken()
    {
    }

    void FormatToken::Remove(ThreadContext& tc)
    {
        Lock lock_obj;
        BidirectionalListHeader::Remove();
        delete this;
        tc.DecrementTypeBAllocationCount();
    }

    LiteralToken * FormatToken::ToLiteral()
    {
        return (nullptr);
    }

    IntPartPlaceHolderToken * FormatToken::ToIntPartPlaceHolder()
    {
        return (nullptr);
    }

    DecimalSeparaterToken * FormatToken::ToDecimalSeparater()
    {
        return (nullptr);
    }

    FracPartPlaceHolderToken * FormatToken::ToFracPartPlaceHolder()
    {
        return (nullptr);
    }

    ExponentToken * FormatToken::ToExponent()
    {
        return (nullptr);
    }

    PercentToken * FormatToken::ToPercent()
    {
        return (nullptr);
    }

    void FormatToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;FormatToken::Format;1");
    }

    int FormatToken::StringCount()
    {
        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;FormatToken::StringCount;1");
    }

    SectionToken * FormatToken::ToSection()
    {
        return (nullptr);
    }

    SectionToken::SectionToken(ThreadContext& tc)
        : _tc(tc), _section_root(), _10_factor(0), _enabled_grouping(false), _max_int_part_length(0), _min_int_part_length(0), _max_frac_part_length(0), _min_frac_part_length(0), _decimal_point_separater(nullptr), _exponent_part(nullptr), _auto_negative_sign(true)
    {
    }

    SectionToken::~SectionToken()
    {
        while (_section_root.Next() != &_section_root)
        {
            _section_root.Next()->Remove(_tc);
        }
    }

    SectionToken * SectionToken::ToSection()
    {
        return (this);
    }

    void SectionToken::Parse(bool auto_negative_sign)
    {
        _auto_negative_sign = auto_negative_sign;

        // format を前から走査する
        bool found_int_part_zero = false;
        int count_percent = 0;
        int count_permille = 0;
        int count_int_part_zero = 0;
        int count_frac_part_zero_or_sharp = 0;
        for (FormatToken* p = _section_root.Next(); p != &_section_root; p = p->Next())
        {
            PercentToken* pp = p->ToPercent();
            if (pp != nullptr)
            {
                // '%' と '‰' の数を数える
                switch (pp->GetLetter())
                {
                case L'%':
                    ++count_percent;
                    break;
                case L'‰':
                    ++count_permille;
                    break;
                default:
                    break;
                }
            }
            IntPartPlaceHolderToken* ip = p->ToIntPartPlaceHolder();
            if (ip != nullptr)
            {
                // 最初の '0' の後の '#' はすべて '0' に置き換える
                switch (ip->GetLetter())
                {
                case L'0':
                    found_int_part_zero = true;
                    ++count_int_part_zero;
                    break;
                case L'#':
                    if (found_int_part_zero)
                    {
                        ip->SetLetter(L'0');
                        ++count_int_part_zero;
                    }
                    break;
                default:
                    break;
                }
            }
            FracPartPlaceHolderToken* fp = p->ToFracPartPlaceHolder();
            if (fp != nullptr)
            {
                // 最後の '0' の前の '#' はすべて '0' に置き換える
                switch (fp->GetLetter())
                {
                case L'0':
                case L'#':
                    fp->SetIndex(count_frac_part_zero_or_sharp);
                    ++count_frac_part_zero_or_sharp;
                    break;
                default:
                    break;
                }
            }
        }

        // format を後ろから走査する
        bool found_frac_part_zero = false;
        bool found_int_part_zero_or_sharp = false;
        int count_int_part_trailing_commma = 0;
        int count_int_part_zero_or_sharp = 0;
        int count_frac_part_zero = 0;
        for (FormatToken* p = _section_root.Prev(); p != &_section_root; p = p->Prev())
        {
            IntPartPlaceHolderToken* ip = p->ToIntPartPlaceHolder();
            if (ip != nullptr)
            {
                // 最下位にある連続した ',' の数を数える
                // 
                switch (ip->GetLetter())
                {
                case L'0':
                case L'#':
                    found_int_part_zero_or_sharp = true;
                    ++count_int_part_zero_or_sharp;
                    ip->SetIndex(count_int_part_zero_or_sharp);
                    break;
                case L',':
                    if (found_int_part_zero_or_sharp)
                        _enabled_grouping = true;
                    else
                        ++count_int_part_trailing_commma;
                    break;
                default:
                    break;
                }
            }
            FracPartPlaceHolderToken* fp = p->ToFracPartPlaceHolder();
            if (fp != nullptr)
            {
                // 最後の '0' の前の '#' はすべて '0' に置き換える
                switch (fp->GetLetter())
                {
                case L'0':
                    found_frac_part_zero = true;
                    ++count_frac_part_zero;
                    break;
                case L'#':
                    if (found_frac_part_zero)
                    {
                        fp->SetLetter(L'0');
                        ++count_frac_part_zero;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        _min_int_part_length = count_int_part_zero;
        _min_frac_part_length = count_frac_part_zero;
        _max_int_part_length = count_int_part_zero_or_sharp;
        _max_frac_part_length = count_frac_part_zero_or_sharp;
        _10_factor = count_percent * 2 + 3 * (count_permille - count_int_part_trailing_commma);
    }

    void SectionToken::Format(SectionToken * alternative_section, const PMC_NUMBER_FORMAT_INFO& format_option, SIGN_T x_sign, NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, StringWriter& writer)
    {
        if (x_sign == 0)
            WriteZeroValue(format_option, writer);
        else
        {
            WriteNonZeroValue(x_sign, x_numerator, x_denominator, alternative_section, format_option, writer);
        }
    }

    void SectionToken::AppendLiteral(const wchar_t * reference, int reference_count)
    {
        LiteralToken* token = new LiteralToken(reference, reference_count);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
    }

    void SectionToken::AppendIntPartPlaceHolder(const PMC_NUMBER_FORMAT_INFO& format_option, bool first, const wchar_t digit)
    {
        IntPartPlaceHolderToken* token = new IntPartPlaceHolderToken(format_option, first, digit);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
    }

    void SectionToken::AppendDecimalSeparaterToken(const PMC_NUMBER_FORMAT_INFO& format_option)
    {
        DecimalSeparaterToken* token = new DecimalSeparaterToken(format_option);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
        _decimal_point_separater = token;
    }

    void SectionToken::AppendFracPartPlaceHolder(const wchar_t digit)
    {
        FracPartPlaceHolderToken* token = new FracPartPlaceHolderToken(digit);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
    }

    void SectionToken::AppendExponent(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t header, int zero_count)
    {
        ExponentToken* token = new ExponentToken(format_option, header, L'\0', zero_count);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
        _exponent_part = token;
    }

    void SectionToken::AppendExponent(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t header, wchar_t sign, int zero_count)
    {
        ExponentToken* token = new ExponentToken(format_option, header, sign, zero_count);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
        _exponent_part = token;
    }

    void SectionToken::AppendPercent(const PMC_NUMBER_FORMAT_INFO& format_option, const wchar_t digit)
    {
        PercentToken* token = new PercentToken(format_option, digit);
        _tc.IncrementTypeBAllocationCount();
        _section_root.AddBefore(token);
    }

    bool SectionToken::IsEmpty()
    {
        return (_section_root.Next() == &_section_root);
    }

    void SectionToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;SectionToken::Format;1");
    }

    int SectionToken::StringCount()
    {
        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;SectionToken::StringCount;1");
    }

    void SectionToken::WriteZeroValue(const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter & writer)
    {
        if (_exponent_part != nullptr)
        {
            // 指数表現の場合

            WriteZeroValueByExponential(format_option, writer);
        }
        else
        {
            // 固定小数点表現の場合

            WriteZeroValueByFixedPoint(format_option, writer);
        }
    }

    void SectionToken::WriteZeroValueByFixedPoint(const PMC_NUMBER_FORMAT_INFO & format_option, StringWriter & writer)
    {
        ResourceHolderUINT root(_tc);

        // 整数部の文字列化
        size_t int_buf_length = _min_int_part_length * 2 + 1;
        wchar_t* int_buf = root.AllocateString(int_buf_length);
        ReverseStringWriter int_buf_writer(int_buf, int_buf_length);
        ThousandSeparatedStringWriter t_int_buf_writer(int_buf_writer, _enabled_grouping ? L'N' : L'D', format_option);
        t_int_buf_writer.Write(L'0', _min_int_part_length);
        root.CheckString(int_buf);

        // 小数部の文字列化
        size_t frac_buf_length = _min_frac_part_length + 1;
        wchar_t* frac_buf = root.AllocateString(frac_buf_length);
        StringWriter frac_buf_writer(frac_buf, frac_buf_length);
        frac_buf_writer.Write(L'0', _min_frac_part_length);
        root.CheckString(frac_buf);

        // カスタム数値書式文字列のプレースホルダに適用する
        ApplyPlaceHolder(SIGN_ZERO, t_int_buf_writer.GetString(), frac_buf_writer.GetString(), 0, format_option, writer);
    }

    void SectionToken::WriteZeroValueByExponential(const PMC_NUMBER_FORMAT_INFO & format_option, StringWriter & writer)
    {
        ResourceHolderUINT root(_tc);

        // 整数部の文字列化
        size_t int_buf_length = _max_int_part_length * 2 + 1;
        wchar_t* int_buf = root.AllocateString(int_buf_length);
        ReverseStringWriter int_buf_writer(int_buf, int_buf_length);
        ThousandSeparatedStringWriter t_int_buf_writer(int_buf_writer, _enabled_grouping ? L'N' : L'D', format_option);
        t_int_buf_writer.Write(L'0', _max_int_part_length);
        root.CheckString(int_buf);

        // 小数部の文字列化
        size_t frac_buf_length = _min_frac_part_length + 1;
        wchar_t* frac_buf = root.AllocateString(frac_buf_length);
        StringWriter frac_buf_writer(frac_buf, frac_buf_length);
        frac_buf_writer.Write(L'0', _min_frac_part_length);
        root.CheckString(frac_buf);

        // カスタム数値書式文字列のプレースホルダに適用する
        ApplyPlaceHolder(SIGN_ZERO, t_int_buf_writer.GetString(), frac_buf_writer.GetString(), 0, format_option, writer);
    }

    void SectionToken::WriteNonZeroValue(SIGN_T x_sign, NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, SectionToken * alternative_section, const PMC_NUMBER_FORMAT_INFO & format_option, StringWriter & writer)
    {
        if (_exponent_part != nullptr)
        {
            // 指数表記の場合

            WriteNonZeroValueByExponential(x_sign, x_numerator, x_denominator, alternative_section, format_option, writer);
        }
        else
        {
            // 固定小数点表記の場合

            WriteNonZeroValueByFixedPoint(x_sign, x_numerator, x_denominator, alternative_section, format_option, writer);
        }
    }

    void SectionToken::WriteNonZeroValueByFixedPoint(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, SectionToken* alternative_section, const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter& writer)
    {
        ResourceHolderUINT root(_tc);

        // 小数部を丸める
        x_numerator = PMC_Round_R_Imp(_tc, x_numerator, x_denominator, _max_frac_part_length + _10_factor, PMC_GetDefaultRoundingMode(), &x_denominator);
        root.HookNumber(x_numerator);
        root.HookNumber(x_denominator);

        // 丸めた結果の数値が 0 である場合、代替セクションパーサに処理を委譲する
        if (x_sign != 0 && x_numerator->IS_ZERO)
        {
            if (alternative_section != nullptr)
                alternative_section->Format(nullptr, format_option, SIGN_ZERO, x_numerator, x_denominator, writer);
        }
        else
        {
            // _10_factor を数値に反映させる
            Times10n_R(root, x_numerator, x_denominator, _10_factor, &x_numerator, &x_denominator);

            // x を整数部と小数部に分ける
            NUMBER_OBJECT_UINT* t_int_part;
            NUMBER_OBJECT_UINT* t_frac_part_numerator = PMC_DivRem_UX_UX_Imp(_tc, x_numerator, x_denominator, &t_int_part);
            NUMBER_OBJECT_UINT* t_frac_part_denominator = x_denominator;
            root.HookNumber(t_int_part);
            root.HookNumber(t_frac_part_numerator);

            // 整数部の文字列化
            size_t int_buf_length = t_int_part->UNIT_WORD_COUNT * (_digit_count_on_word + 1) * 2 + 1 + 1; // 桁区切り文字を考慮して余分に獲得する
            wchar_t* int_buf = root.AllocateString(int_buf_length);
            ReverseStringWriter int_buf_writer(int_buf, int_buf_length);
            ThousandSeparatedStringWriter t_int_buf_writer(int_buf_writer, _enabled_grouping ? L'N' : L'D', format_option);
            PMC_LToA_Imp(_tc, t_int_part, t_int_buf_writer);
            root.CheckString(int_buf);

            // 小数部の文字列化
            size_t frac_buf_length = _max_frac_part_length + 1;
            wchar_t* frac_buf = root.AllocateString(frac_buf_length);
            StringWriter frac_buf_writer(frac_buf, frac_buf_length);
            PMC_FToA_Imp(_tc, t_frac_part_numerator, t_frac_part_denominator, _max_frac_part_length, frac_buf_writer);
            root.CheckString(frac_buf);

            // カスタム数値書式文字列のプレースホルダに適用する
            ApplyPlaceHolder(x_sign, t_int_buf_writer.GetString(), frac_buf_writer.GetString(), 0, format_option, writer);
        }
    }

    void SectionToken::WriteNonZeroValueByExponential(SIGN_T x_sign, NUMBER_OBJECT_UINT* x_numerator, NUMBER_OBJECT_UINT* x_denominator, SectionToken* alternative_section, const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter& writer)
    {
        ResourceHolderUINT root(_tc);

        int x_int_part_length = PMC_FloorLog10_R_Imp(_tc, x_numerator, x_denominator) + 1;
        // 現在の整数部の桁数は x_int_part_length 桁で、さらに追加して小数部を何桁表示する必要があるか。
        // 合計で表示する桁数は _max_int_part_length + _max_frac_part_length であるので、表示する必要のある小数部の桁数 x_frac_part_length は
        int x_frac_part_length = _max_int_part_length + _max_frac_part_length - x_int_part_length;
        // である。

        // 小数部を丸める
        x_numerator = PMC_Round_R_Imp(_tc, x_numerator, x_denominator, x_frac_part_length, PMC_GetDefaultRoundingMode(), &x_denominator);
        root.HookNumber(x_numerator);
        root.HookNumber(x_denominator);

        // 丸めた結果の数値が 0 である場合、代替セクションパーサに処理を委譲する
        if (x_sign != 0 && x_numerator->IS_ZERO)
        {
            if (alternative_section != nullptr)
                alternative_section->Format(nullptr, format_option, SIGN_ZERO, x_numerator, x_denominator, writer);
        }
        else
        {
            // 稀に丸めにより整数部の桁数が 1 増えていることがあるので、再計算する
            x_int_part_length = PMC_FloorLog10_R_Imp(_tc, x_numerator, x_denominator) + 1;

            // 整数部が _max_int_part_length になるよう仮数と指数を調整する。
            int exp_part = _10_factor + x_int_part_length - _max_int_part_length;
            Times10n_R(root, x_numerator, x_denominator,  _max_int_part_length - x_int_part_length, &x_numerator, &x_denominator);

            // x を整数部と小数部に分ける
            NUMBER_OBJECT_UINT* t_int_part;
            NUMBER_OBJECT_UINT* t_frac_part_numerator = PMC_DivRem_UX_UX_Imp(_tc, x_numerator, x_denominator, &t_int_part);
            NUMBER_OBJECT_UINT* t_frac_part_denominator = x_denominator;
            root.HookNumber(t_int_part);
            root.HookNumber(t_frac_part_numerator);

            // 整数部の文字列化
            size_t int_buf_length = t_int_part->UNIT_WORD_COUNT * (_digit_count_on_word + 1) * 2 + 1 + 1; // 桁区切り文字を考慮して余分に獲得する
            wchar_t* int_buf = root.AllocateString(int_buf_length);
            ReverseStringWriter int_buf_writer(int_buf, int_buf_length);
            ThousandSeparatedStringWriter t_int_buf_writer(int_buf_writer, _enabled_grouping ? L'N' : L'D', format_option);
            PMC_LToA_Imp(_tc, t_int_part, t_int_buf_writer);
            root.CheckString(int_buf);

            // 小数部の文字列化
            size_t frac_buf_length = _max_frac_part_length + 1;
            wchar_t* frac_buf = root.AllocateString(frac_buf_length);
            StringWriter frac_buf_writer(frac_buf, frac_buf_length);
            PMC_FToA_Imp(_tc, t_frac_part_numerator, t_frac_part_denominator, _max_frac_part_length, frac_buf_writer);
            root.CheckString(frac_buf);

            // カスタム数値書式文字列のプレースホルダに適用する
            ApplyPlaceHolder(x_sign, t_int_buf_writer.GetString(), frac_buf_writer.GetString(), exp_part, format_option, writer);
        }
    }

    void SectionToken::Times10n_R(ResourceHolderUINT& root, NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, int e, NUMBER_OBJECT_UINT ** r_numerator, NUMBER_OBJECT_UINT ** r_denominator)
    {
        *r_numerator = x_numerator;
        *r_denominator = x_denominator;
        if (e > 0)
        {
            NUMBER_OBJECT_UINT* factor = PMC_Pow10_UI_Imp(_tc, e);
            root.HookNumber(factor);
            *r_numerator = PMC_Multiply_UX_UX_Imp(_tc, PMC_MULTIPLICATION_METHOD_AUTO, *r_numerator, factor);
            root.HookNumber(*r_numerator);
        }
        else if (e < 0)
        {
            NUMBER_OBJECT_UINT* factor = PMC_Pow10_UI_Imp(_tc, -e);
            root.HookNumber(factor);
            *r_denominator = PMC_Multiply_UX_UX_Imp(_tc, PMC_MULTIPLICATION_METHOD_AUTO, *r_denominator, factor);
            root.HookNumber(*r_denominator);
        }
        else
        {
        }
    }

    void SectionToken::ApplyPlaceHolder(SIGN_T sign, const wchar_t* int_part_buf, const wchar_t* frac_part_buf, int exp_part, const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter & writer)
    {
        ResourceHolderUINT root(_tc);

        // カスタム書式の小数点より前の文字の数(見積もり)
        size_t int_str_buf_length = lstrlenW(int_part_buf) + 1;
        for (FormatToken* p = _decimal_point_separater == nullptr ? _section_root.Prev() : _decimal_point_separater->Prev(); p != &_section_root; p = p->Prev())
            int_str_buf_length += p->StringCount();

        // カスタム書式の小数点より前を編集
        wchar_t* int_str_buf = root.AllocateString(int_str_buf_length);
        ReverseStringWriter int_str_buf_writer(int_str_buf, int_str_buf_length);
        ReverseStringReader int_buf_reader(int_part_buf);
        for (FormatToken* p = _decimal_point_separater == nullptr ? _section_root.Prev() : _decimal_point_separater->Prev(); p != &_section_root; p = p->Prev())
            p->Format(int_buf_reader, exp_part, int_str_buf_writer);
        root.CheckString(int_str_buf);

        // カスタム書式の小数点より後の文字の数(見積もり)
        size_t frac_str_buf_length = lstrlenW(frac_part_buf) + 1;
        if (_decimal_point_separater != nullptr)
        {
            for (FormatToken* p = _decimal_point_separater->Next(); p != &_section_root; p = p->Next())
                frac_str_buf_length += p->StringCount();
        }

        // カスタム書式の小数点より後を編集
        wchar_t* frac_str_buf = root.AllocateString(frac_str_buf_length);
        StringWriter frac_str_buf_writer(frac_str_buf, frac_str_buf_length);
        if (_decimal_point_separater != nullptr)
        {
            StringReader frac_buf_reader(frac_part_buf);
            for (FormatToken* p = _decimal_point_separater->Next(); p != &_section_root; p = p->Next())
                p->Format(frac_buf_reader, exp_part, frac_str_buf_writer);
            root.CheckString(frac_str_buf);
        }

        // 編集したパーツを結合する
        if (_auto_negative_sign && sign < 0 && (int_part_buf[0] != L'\0' || frac_part_buf[0] != L'\0'))
            writer.Write(format_option.NegativeSign);
        writer.Write(int_str_buf_writer.GetString());
        if (_decimal_point_separater != nullptr)
        {
            if (_max_int_part_length <= 0)
                writer.Write(int_part_buf);
            if (frac_part_buf[0] != L'\0' || _min_frac_part_length > 0)
                _decimal_point_separater->Format(format_option, writer);
        }
        writer.Write(frac_str_buf_writer.GetString());
    }

    LiteralToken::LiteralToken(const wchar_t * reference, int reference_count)
    {
        _reference = reference;
        _reference_count = reference_count;
    }

    LiteralToken * LiteralToken::ToLiteral()
    {
        return (this);
    }

    void LiteralToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        writer.Write(_reference, _reference_count);
    }

    int LiteralToken::StringCount()
    {
        return (_reference_count);
    }

    IntPartPlaceHolderToken::IntPartPlaceHolderToken(const PMC_NUMBER_FORMAT_INFO& format_option, bool first, wchar_t letter)
        : _format_option(format_option), _first(first), _index(0), _letter(letter)
    {
    }

    wchar_t IntPartPlaceHolderToken::GetLetter()
    {
        return (_letter);
    }

    void IntPartPlaceHolderToken::SetLetter(wchar_t letter)
    {
        _letter = letter;
    }

    int IntPartPlaceHolderToken::GetIndex()
    {
        return (_index);
    }

    void IntPartPlaceHolderToken::SetIndex(int index)
    {
        _index = index;
    }

    IntPartPlaceHolderToken * IntPartPlaceHolderToken::ToIntPartPlaceHolder()
    {
        return (this);
    }

    void IntPartPlaceHolderToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        bool break_loop = false;
        while (!break_loop)
        {
            switch (source_reader.PeekChar())
            {
            case L'\0':
                if (_letter == L'0')
                    writer.Write(L'0');
                break_loop = true;
                break;
            case L'0':
            case L'1':
            case L'2':
            case L'3':
            case L'4':
            case L'5':
            case L'6':
            case L'7':
            case L'8':
            case L'9':
                writer.Write(source_reader.ReadChar());
                break_loop = true;
                break;
            default:
                // グループ区切り文字の場合にこのルートに到着する
                writer.Write(source_reader.ReadChar());
                break;
            }
        }
        if (_first)
        {
            // 最上位桁の場合
            // source_reader に残っているものをすべて出力する
            writer.Write(source_reader);
        }
    }

    int IntPartPlaceHolderToken::StringCount()
    {
        return (_letter == L'0' ? 1 : 0);
    }

    DecimalSeparaterToken::DecimalSeparaterToken(const PMC_NUMBER_FORMAT_INFO& format_option)
        : _format_option(format_option)
    {
    }

    DecimalSeparaterToken * DecimalSeparaterToken::ToDecimalSeparater()
    {
        return (this);
    }

    void DecimalSeparaterToken::Format(const PMC_NUMBER_FORMAT_INFO& format_option, StringWriter & writer)
    {
        writer.Write(format_option.Number.DecimalSeparator);
    }

    void DecimalSeparaterToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        writer.Write(_format_option.Number.DecimalSeparator);
    }

    int DecimalSeparaterToken::StringCount()
    {
        return (lstrlenW(_format_option.Number.DecimalSeparator));
    }

    FracPartPlaceHolderToken::FracPartPlaceHolderToken(wchar_t letter)
        : _letter(letter), _index(0)
    {
    }

    FracPartPlaceHolderToken * FracPartPlaceHolderToken::ToFracPartPlaceHolder()
    {
        return (this);
    }

    wchar_t FracPartPlaceHolderToken::GetLetter()
    {
        return (_letter);
    }

    void FracPartPlaceHolderToken::SetLetter(wchar_t letter)
    {
        _letter = letter;
    }

    int FracPartPlaceHolderToken::GetIndex()
    {
        return (_index);
    }

    void FracPartPlaceHolderToken::SetIndex(int index)
    {
        _index = index;
    }

    void FracPartPlaceHolderToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        switch (source_reader.PeekChar())
        {
        case L'\0':
            if (_letter == L'0')
                writer.Write(L'0');
            break;
        case L'0':
        case L'1':
        case L'2':
        case L'3':
        case L'4':
        case L'5':
        case L'6':
        case L'7':
        case L'8':
        case L'9':
            writer.Write(source_reader.ReadChar());
            break;
        default:
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;FracPartPlaceHolderToken::Format;1");
        }
    }

    int FracPartPlaceHolderToken::StringCount()
    {
        return (_letter == L'0' ? 1 : 0);
    }

    ExponentToken::ExponentToken(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t header, wchar_t sign, int zero_count)
        : _format_option(format_option), _header(header), _sign(sign), _zero_count(zero_count)
    {
    }

    ExponentToken * ExponentToken::ToExponent()
    {
        return (this);
    }

    void ExponentToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        // Q: 指数部の桁数は最大何桁あればよいか？
        // A: 指数の論理的な最大値は 8* 2^64。10進数での桁数は Log10 を適用して Log10(2) * 67 ⇒ 約 20.17。よって最大で 21 桁と見積もれる。
        wchar_t exp_format[22];
        wsprintfW(exp_format, L"%%c%%s%%0%dd", _zero_count);
        wchar_t exp_buf[1 + 1+ 21 + 1];
        if (exponent > 0)
            wsprintfW(exp_buf, exp_format, _header, _sign == L'+' ? L"+" : L"", exponent);
        else if (exponent == 0)
            wsprintfW(exp_buf, exp_format, _header, L"", exponent);
        else
            wsprintfW(exp_buf, exp_format, _header, L"-", -exponent);
        writer.Write(exp_buf);
    }

    int ExponentToken::StringCount()
    {
        return (1 + 1 + 21); //  指数値の長さは論理上では最大 21 桁
    }

    PercentToken::PercentToken(const PMC_NUMBER_FORMAT_INFO& format_option, wchar_t letter)
        : _format_option(format_option), _letter(letter)
    {
    }

    wchar_t PercentToken::GetLetter()
    {
        return (_letter);
    }

    PercentToken * PercentToken::ToPercent()
    {
        return (this);
    }

    void PercentToken::Format(StringReader & source_reader, int exponent, StringWriter & writer)
    {
        switch (_letter)
        {
        case L'%':
            writer.Write(_format_option.PercentSymbol);
            break;
        case L'‰':
            writer.Write(_format_option.PerMilleSymbol);
            break;
        default:
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;PercentToken::Format;1");
        }
    }

    int PercentToken::StringCount()
    {
        switch (_letter)
        {
        case L'%':
            return (lstrlenW(_format_option.PercentSymbol));
        case L'‰':
            return (lstrlenW(_format_option.PerMilleSymbol));
            break;
        default:
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostringformattercustom.cpp;PercentToken::StringCount;1");
        }
    }

    ToStringFormatterCustom::ToStringFormatterCustom(ThreadContext& tc, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option)
        : _tc(tc), _root(), _format(format), _format_option(*format_option), _section0_root(nullptr), _section1_root(nullptr), _section2_root(nullptr)
    {
        Parse();
        while (_section2_root == nullptr)
            AppendSection();
        bool auto_negative_sign = _section1_root->IsEmpty();
        _section0_root->Parse(auto_negative_sign);
        _section1_root->Parse(auto_negative_sign);
        _section2_root->Parse(auto_negative_sign);
    }

    ToStringFormatterCustom::~ToStringFormatterCustom()
    {
        while (_root.Next() != &_root)
        {
            _root.Next()->Remove(_tc);
        }
    }

    void ToStringFormatterCustom::Format(SIGN_T x_sign, NUMBER_OBJECT_UINT * x_numerator, NUMBER_OBJECT_UINT * x_denominator, StringWriter& writer)
    {
        SectionToken* zero_value_section = !_section2_root->IsEmpty() ? _section2_root : _section0_root;
        if (x_sign > 0)
            _section0_root->Format(zero_value_section, _format_option, x_sign, x_numerator, x_denominator, writer);
        else if (x_sign < 0)
        {
            if (!_section1_root->IsEmpty())
                _section1_root->Format(zero_value_section, _format_option, x_sign, x_numerator, x_denominator, writer);
            else
                _section0_root->Format(zero_value_section, _format_option, x_sign, x_numerator, x_denominator, writer);
        }
        else
        {
            if (!_section2_root->IsEmpty())
                _section2_root->Format(zero_value_section, _format_option, x_sign, x_numerator, x_denominator, writer);
            else
                _section0_root->Format(zero_value_section, _format_option, x_sign, x_numerator, x_denominator, writer);
        }
    }

    SectionToken * ToStringFormatterCustom::AppendSection()
    {
        SectionToken* token = new SectionToken(_tc);
        _tc.IncrementTypeBAllocationCount();
        _root.AddBefore(token);
        if (_section0_root == nullptr)
            _section0_root = token;
        else if (_section1_root == nullptr)
            _section1_root = token;
        else if (_section2_root == nullptr)
            _section2_root = token;
        else
        {
        }
        return (token);
    }

    void ToStringFormatterCustom::Parse()
    {
        SectionToken* current_sention = AppendSection();
        const wchar_t* ptr = _format;
        bool found_zero_or_sharp = false;
        bool found_exp = false;
        bool found_decimal_point = false;
        while (*ptr != L'\0')
        {
            switch (*ptr)
            {
            case L'0':
            case L'#':
                if (found_decimal_point)
                {
                    // 既に小数点が見つかっている場合は小数部とみなして出力する
                    current_sention->AppendFracPartPlaceHolder(*ptr);
                    ++ptr;
                }
                else
                {
                    // まだ小数点が見つかっていない場合は整数部とみなして出力する
                    current_sention->AppendIntPartPlaceHolder(_format_option, !found_zero_or_sharp, *ptr);
                    ++ptr;
                }
                found_zero_or_sharp = true;
                break;
            case L'.':
                ++ptr;
                if (!found_decimal_point)
                {
                    // 最初の '.' のみ出力する
                    current_sention->AppendDecimalSeparaterToken(_format_option);
                    // 以降の '0' / '#' を小数部とみなすようフラグを立てる
                    found_decimal_point = true;
                }
                break;
            case L',':
                if (found_decimal_point)
                {
                    // 既に小数点が見つかっている場合は無視する
                    ++ptr;
                }
                else if (!found_zero_or_sharp)
                {
                    // まだ '0' あるいは '#' が見つかっていない場合は捨てる
                    ++ptr;
                }
                else
                {
                    // 整数部の一部として出力する
                    current_sention->AppendIntPartPlaceHolder(_format_option, false, *ptr);
                    ++ptr;
                }
                break;
            case L'%':
                // '%' を出力する
                current_sention->AppendPercent(_format_option, *ptr);
                ++ptr;
                break;
            case L'‰':
                // '‰' を出力する
                current_sention->AppendPercent(_format_option, *ptr);
                ++ptr;
                break;
            case L'E':
            case L'e':
                if (found_exp)
                {
                    // 既に指数部が見つかっている場合は文字列リテラルとみなして出力する
                    current_sention->AppendLiteral(ptr, 1);
                    ++ptr;
                }
                else
                {
                    // 指数部を解析する
                    wchar_t exp_header = *ptr;
                    wchar_t exp_sign;
                    ++ptr;
                    switch (*ptr)
                    {
                    case L'+':
                    case L'-':
                        // 'e'/'E'の後に符号が見つかった
                        exp_sign = *ptr;
                        ++ptr;
                        if (*ptr == L'0')
                        {
                            // 少なくとも 1 つの '0' が見つかった == 指数の書式が正しい

                            // 'e'/'E', 符号, 後続のすべての '0' を指数部として出力する
                            current_sention->AppendExponent(_format_option, exp_header, exp_sign, SkipZero(ptr));
                            found_exp = true;
                        }
                        else
                        {
                            // 'e'/'E', 符号の後に'0'が見つからない == 指数部の書式に誤りがある
                            // すでに見つかった 'e'/'E' と符号は文字列リテラルとみなして出力する
                            current_sention->AppendLiteral(ptr - 2, 2);
                        }
                        break;
                    case L'0':
                        // 'e'/'E'の後に少なくとも 1 つの '0' が見つかった == 指数の書式が正しい
                        // 'e'/'E', 符号, 後続のすべての '0' を指数部として出力する
                        current_sention->AppendExponent(_format_option, exp_header, SkipZero(ptr));
                        found_exp = true;
                        break;
                    default:
                        // 'e'/'E'の後に符号も'0'も見つからない == 指数部の書式に誤りがある
                        // すでに見つかった 'e'/'E' は文字列リテラルとみなして出力する
                        current_sention->AppendLiteral(ptr - 1, 1);
                        break;
                    }
                }
                break;
            case L'\\':
                ++ptr;
                // 次の 1 文字を文字列リテラルとみなして出力する
                if (*ptr != L'\0')
                {
                    current_sention->AppendLiteral(ptr, 1);
                    ++ptr;
                }
                break;
            case L'\'':
                ++ptr;
                // 次にシングルクォートが見つかるまですべての文字をリテラルとみなして出力する ('\' によるエスケープは不可)
                {
                    const wchar_t* ptr2 = ptr;
                    while (*ptr2 != L'\0' && *ptr2 != '\'')
                        ++ptr2;
                    current_sention->AppendLiteral(ptr, (int)(ptr2 - ptr));
                    ptr = *ptr2 == L'\0' ? ptr2 : ptr2 + 1;
                }
                break;
            case ';':
                ++ptr;
                // 新たなセクションを作る
                current_sention = AppendSection();
                // 状態変数を初期化する
                found_zero_or_sharp = false;
                found_exp = false;
                found_decimal_point = false;
                break;
            default:
                // 文字列リテラルとみなして出力する
                current_sention->AppendLiteral(ptr, 1);
                ++ptr;
                break;
            }
        }
    }

    int ToStringFormatterCustom::SkipZero(const wchar_t *& ptr)
    {
        int zero_count = 0;
        while (*ptr == L'0')
        {
            ++ptr;
            ++zero_count;
        }
        return (zero_count);
    }

}


/*
 * END OF FILE
 */