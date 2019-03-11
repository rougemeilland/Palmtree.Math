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
#include <math.h>
#include "pmc_exception.h"
#include "pmc_stringio.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static PMC_NUMBER_FORMAT_INFO default_number_format_option;

    namespace DecimalFromatter
    {

        class ThousandSeparatedStringWriter
            : public StringWriter
        {
        private:
            StringWriter* _native_writer;
            unsigned _is_supported_thousand : 1;
            const wchar_t* _group_separator;
            const wchar_t* _current_group;
            int _current_group_size;
            int _current_group_index;

        public:
            ThousandSeparatedStringWriter(StringWriter* native_writer, wchar_t format_type, const PMC_NUMBER_FORMAT_INFO* format_option)
                : StringWriter(nullptr, nullptr, nullptr)
            {
                _native_writer = native_writer;
                const PMC_DECIMAL_NUMBER_FORMAT_INFO* decimal_info;
                if (format_type == L'C')
                {
                    decimal_info = &format_option->Currency;
                    _is_supported_thousand = TRUE;
                }
                else if (format_type == L'P')
                {
                    decimal_info = &format_option->Percent;
                    _is_supported_thousand = TRUE;
                }
                else if (format_type == L'N')
                {
                    decimal_info = &format_option->Number;
                    _is_supported_thousand = TRUE;
                }
                else
                {
                    decimal_info = &format_option->Number;
                    _is_supported_thousand = FALSE;
                }

                const wchar_t* in_ptr = decimal_info->GroupSeparator;

                _current_group = &decimal_info->GroupSizes[0];
                _group_separator = decimal_info->GroupSeparator;
                _current_group_size = *_current_group - L'0';
                _current_group_index = 0;
            }

            virtual void Write(wchar_t c)
            {
                if (_is_supported_thousand && c >= L'0' && c <= L'9')
                {
                    // 桁区切りをサポートする場合
                    if (_current_group_size > 0 && _current_group_index >= _current_group_size)
                    {
                        // 現在のグループ幅が 0 ではなく、かつ既に出力した文字数がグループ幅に達した場合

                        // グループ区切り文字を出力してから与えられた文字を出力する
                        _native_writer->Write(_group_separator);
                        _native_writer->Write(c);
                        _current_group_index = 1;

                        // 次のグループが存在すればそのグループに移行する
                        if (_current_group[1] != L'\0')
                        {
                            _current_group += 1;
                            _current_group_size = _current_group[0] - L'0';
                        }
                    }
                    else
                    {
                        // 現在のグループの幅が 0 であるかあるいは出力した文字数がグループ幅に達していない場合
                        _native_writer->Write(c);
                        _current_group_index += 1;
                    }
                }
                else
                {
                    // 桁区切りをサポートしない場合

                    _native_writer->Write(c);
                }
            }

            virtual void Write(const wchar_t* str)
            {
                while (*str != L'\0')
                    Write(*str++);
            }

            virtual wchar_t* GetString()
            {
                return (_native_writer->GetString());
            }
        };

        class Formatter
        {
        private:
#ifdef _M_IX86
            const __UNIT_TYPE _10n_base_number = 1000000000U; // 10^9
            const int digit_count_on_word = 9;
#elif defined (_M_X64)
            const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
            const int digit_count_on_word = 19;
#else
#error unknown platform
#endif

        protected:
            wchar_t _format_type;
            int _precision;
            const PMC_NUMBER_FORMAT_INFO* _number_format_info;

        protected:
            Formatter(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
            {
                _format_type = format_type;
                _precision = precision;
                _number_format_info = number_format_info;
            }

        public:
            void Format(char x_sign, NUMBER_HEADER* x_abs, StringWriter* writer)
            {
                if (_precision < 0)
                    _precision = GetDefaultPrecisionValue();
                if (x_abs->IS_ZERO)
                {
                    // x == 0 の場合
                    if (x_sign != 0)
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;Formatter::Format;1");
                    WritePrefix(x_sign, writer);
                    WriteZeroValue(writer);
                    WriteSuffix(x_sign, writer);
                }
                else
                {
                    // x != 0 の場合
                    if (x_sign == 0)
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;Formatter::Format;1");

                    WritePrefix(x_sign, writer);
                    FormatInternally(x_abs, writer);
                    WriteSuffix(x_sign, writer);
                }
            }

        protected:
#if false
            virtual int GetDefaultPrecisionValue()
            {
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;Formatter::GetDefaultPrecisionValue;1");
            }
#else
            virtual int GetDefaultPrecisionValue() = 0;
#endif

            virtual void FormatInternally(NUMBER_HEADER* x_abs, StringWriter* writer)
            {
                ResourceHolderUINT root;
                __UNIT_TYPE _10n_based_number_bit_count = x_abs->UNIT_BIT_COUNT + _DIVIDE_CEILING_UNIT(x_abs->UNIT_BIT_COUNT, 8);
                __UNIT_TYPE* _10n_based_number_buf = root.AllocateBlock(_10n_based_number_bit_count);
                __UNIT_TYPE _10n_based_number_buf_count = ConvertAs10nBasedNumber(x_abs, _10n_based_number_buf);
                __UNIT_TYPE simple_number_sequence_buf_size = digit_count_on_word * _10n_based_number_buf_count + 1;
                wchar_t* simple_number_sequence = root.AllocateString(simple_number_sequence_buf_size);
                wchar_t* top_of_simple_number_sequence = ConstructSimpleNumberSequence(_10n_based_number_buf, _10n_based_number_buf_count, simple_number_sequence, simple_number_sequence_buf_size);
                root.DeallocateBlock(_10n_based_number_buf);
                FormatNumberSequence(top_of_simple_number_sequence, writer);
                root.DeallocateString(simple_number_sequence);
            }

            // 0 値を表す文字列を writer に設定します。
            virtual void WriteZeroValue(StringWriter* writer) = 0;

            // 数値の前に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
            virtual void WritePrefix(char x_sign, StringWriter* writer) = 0;

            // 単純な数字列を書式に応じて変換し、StringWriterに書き込みます。(例: precision に応じた 0 パディング、3桁区切り、など)
            virtual void FormatNumberSequence(const wchar_t* number_sequence_str, StringWriter* writer) = 0;

            // 数値の後に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
            virtual void WriteSuffix(char x_sign, StringWriter* writer) = 0;

        private:
            __UNIT_TYPE ConvertAs10nBasedNumber(NUMBER_HEADER* x, __UNIT_TYPE* r_buf)
            {
                ResourceHolderUINT root;
                __UNIT_TYPE work_bit_count = x->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                __UNIT_TYPE* u_ptr = root.AllocateBlock(work_bit_count);
                __UNIT_TYPE* q_ptr = root.AllocateBlock(work_bit_count);
                _COPY_MEMORY_UNIT(u_ptr, x->BLOCK, x->BLOCK_COUNT);
                __UNIT_TYPE* r_ptr = r_buf;
                __UNIT_TYPE work_u_count = _DIVIDE_CEILING_UNIT(work_bit_count, __UNIT_TYPE_BIT_COUNT);
                while (work_u_count > 0)
                {
                    root.ClearBlock(q_ptr);
                    __UNIT_TYPE r_value;
                    DivRem_X_1W(u_ptr, work_u_count, _10n_base_number, q_ptr, &r_value);
                    root.CheckBlock(q_ptr);
                    *r_ptr++ = r_value;
                    __UNIT_TYPE* temp = u_ptr;
                    u_ptr = q_ptr;
                    q_ptr = temp;
                    while (work_u_count > 0 && u_ptr[work_u_count - 1] == 0)
                        --work_u_count;
                }
                return (r_ptr - r_buf);
            }

            wchar_t* ConstructSimpleNumberSequence(__UNIT_TYPE* in_buf, __UNIT_TYPE in_buf_count, wchar_t* out_buf, size_t out_buf_count)
            {
                ReverseStringWriter simple_number_sequence_writer(out_buf, out_buf_count);

                __UNIT_TYPE* in_ptr = in_buf;
                __UNIT_TYPE in_count = in_buf_count - 1;
                while (in_count != 0)
                {
                    WriteTrailingWord(&simple_number_sequence_writer, *in_ptr);
                    ++in_ptr;
                    --in_count;
                }
                WriteLeadingOneWord(&simple_number_sequence_writer, *in_ptr);
                return (simple_number_sequence_writer.GetString());
            }

            // 最上位のワードを文字列化する。(途中で x が 0 になった場合は中断する)
            void WriteLeadingOneWord(StringWriter* writer, __UNIT_TYPE x)
            {
                __UNIT_TYPE r;
                do
                {
                    x = _DIVREM_UNIT(0, x, 10, &r);
                    WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(r) == sizeof(_UINT64_T))
                        IncrementDIV64Counter();
                    else
                        IncrementDIV32Counter();
#endif
                } while (x != 0);
            }

            // 上位から 2 ワード目以降を文字列化する。(途中で x が 0 になっても続行する)
            void WriteTrailingWord(StringWriter* writer, __UNIT_TYPE x)
            {
                __UNIT_TYPE r;
                if (sizeof(__UNIT_TYPE) >= sizeof(_UINT64_T))
                {
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(r) == sizeof(_UINT64_T))
                        AddToDIV64Counter(10);
                    else
                        AddToDIV32Counter(10);
#endif
                }
                if (sizeof(__UNIT_TYPE) >= sizeof(_UINT32_T))
                {
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(r) == sizeof(_UINT64_T))
                        AddToDIV64Counter(5);
                    else
                        AddToDIV32Counter(5);
#endif
                }
                if (sizeof(__UNIT_TYPE) >= sizeof(_UINT16_T))
                {
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(r) == sizeof(_UINT64_T))
                        AddToDIV64Counter(2);
                    else
                        AddToDIV32Counter(2);
#endif
                }
                if (sizeof(__UNIT_TYPE) >= sizeof(_BYTE_T))
                {
                    x = _DIVREM_UNIT(0, x, 10, &r); WriteDigit(writer, (_UINT32_T)r);
                    WriteDigit(writer, (_UINT32_T)x);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(r) == sizeof(_UINT64_T))
                        IncrementDIV64Counter();
                    else
                        IncrementDIV32Counter();
#endif
                }
            }

            void WriteDigit(StringWriter* writer, _UINT32_T d)
            {
                writer->Write(L'0' + d);
            }

        };

        class FormatterTypeC
            : public Formatter
        {
        public:
            FormatterTypeC(int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(L'C', precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (_number_format_info->Currency.DecimalDigits);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Currency.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                    switch (_number_format_info->Currency.PositivePattern)
                    {
                    case 0:
                    default:
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 1:
                        break;
                    case 2:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L' ');
                        break;
                    case 3:
                        break;
                    }
                }
                else
                {
                    switch (_number_format_info->Currency.NegativePattern)
                    {
                    case 0:
                    default:
                        writer->Write(L'(');
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 1:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 2:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 3:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 4:
                        writer->Write(L'(');
                        break;
                    case 5:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    case 8:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 9:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L' ');
                        break;
                    case 10:
                        break;
                    case 11:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L' ');
                        break;
                    case 12:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L' ');
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 13:
                        break;
                    case 14:
                        writer->Write(L'(');
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L' ');
                        break;
                    case 15:
                        writer->Write(L'(');
                        break;
                    }
                }
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                ResourceHolderUINT root;
                ReverseStringReader r_reader(number_sequence_str);
                size_t work_buf_len = lstrlenW(number_sequence_str) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Currency.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                    switch (_number_format_info->Currency.PositivePattern)
                    {
                    case 0:
                    default:
                        break;
                    case 1:
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 2:
                        break;
                    case 3:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    }
                }
                else
                {
                    switch (_number_format_info->Currency.NegativePattern)
                    {
                    case 0:
                    default:
                        writer->Write(L')');
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 4:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L')');
                        break;
                    case 5:
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 6:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 7:
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 8:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 9:
                        break;
                    case 10:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 11:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 12:
                        break;
                    case 13:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(L' ');
                        writer->Write(_number_format_info->CurrencySymbol);
                        break;
                    case 14:
                        writer->Write(L')');
                        break;
                    case 15:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->CurrencySymbol);
                        writer->Write(L')');
                        break;
                    }
                }
            }
        };

        class FormatterTypeD
            : public Formatter
        {
        public:
            FormatterTypeD(int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(L'D', precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (0);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0', _precision < 1 ? 1 : _precision);
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                writer->Write(L'0', _precision > lstrlenW(number_sequence_str) ? _precision - lstrlenW(number_sequence_str) : 0);
                writer->Write(number_sequence_str);
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
            }
        };

        class FormatterTypeE
            : public Formatter
        {
        public:
            FormatterTypeE(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(format_type, precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (6);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
                writer->Write(_format_type);
                writer->Write(L"+000");
            }

            virtual void FormatInternally(NUMBER_HEADER* x_abs, StringWriter* writer) override
            {
                ResourceHolderUINT root;
                size_t digit_count = (size_t)floor(PMC_Floor_Log10_Imp(x_abs)) + 1;
                if (digit_count >= (size_t)(_precision + 2))
                {
                    NUMBER_HEADER* fraction_number = PMC_TimesOfExponentOf10_Imp(5, digit_count - _precision - 2);
                    root.HookNumber(fraction_number);
                    NUMBER_HEADER* x2 = PMC_Add_X_X_Imp(x_abs, fraction_number);
                    root.HookNumber(x2);
                    Formatter::FormatInternally(x2, writer);
                }
                else
                    Formatter::FormatInternally(x_abs, writer);
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                StringReader reader(number_sequence_str);
                writer->Write(reader.ReadChar(L'0'));
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    for (int count = _precision; count > 0; --count)
                        writer->Write(reader.ReadChar(L'0'));
                }
                writer->Write(_format_type);
                writer->Write(_number_format_info->PositiveSign);
                size_t exponential_part = lstrlenW(number_sequence_str) - 1;

                // 指数部を文字列化するために必要な領域の大きさについて
                // sizeof(w_char_t) == 2 であるため、アドレス空間が 64bit の環境における指数部の論理的な上限値は 2^63 (^はべき乗演算子)
                // なので、指数部を10進数表記した場合の論理的な桁数の上限値は ceil(63 * log(2) / log(10)) ==> 19 となる。
                // 同様に、32bit アドレス空間においては、指数部桁数の論理的上限値は ceil(31 * log(2) / log(10)) ==> 10 となる。

#ifdef _M_IX86 
                wchar_t exp_buf[10 + 1];
#elif defined(_M_X64)
                wchar_t exp_buf[19 + 1];
#else
#error unknown platform
#endif
                wsprintfW(exp_buf, L"%03d", exponential_part);
                writer->Write(exp_buf);
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
            }
        };

        class FormatterTypeF
            : public Formatter
        {
        public:
            FormatterTypeF(int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(L'F', precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (_number_format_info->Number.DecimalDigits);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                writer->Write(number_sequence_str);
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
            }
        };

        class FormatterTypeN
            : public Formatter
        {
        public:
            FormatterTypeN(int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(L'N', precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (_number_format_info->Number.DecimalDigits);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                }
                else
                {
                    switch (_number_format_info->Number.NegativePattern)
                    {
                    case 0:
                        writer->Write(L'(');
                        break;
                    case 1:
                    default:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 2:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(L' ');
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    }
                }
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                ResourceHolderUINT root;
                ReverseStringReader r_reader(number_sequence_str);
                size_t work_buf_len = lstrlenW(number_sequence_str) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                }
                else
                {
                    switch (_number_format_info->Currency.NegativePattern)
                    {
                    case 0:
                        writer->Write(L')');
                        break;
                    case 1:
                    default:
                        break;
                    case 2:
                        break;
                    case 3:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 4:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    }
                }
            }
        };

        class FormatterTypeP
            : public Formatter
        {
        public:
            FormatterTypeP(int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(L'P', precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue() override
            {
                return (_number_format_info->Currency.DecimalDigits);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Currency.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void FormatInternally(NUMBER_HEADER* x_abs, StringWriter* writer) override
            {
                ResourceHolderUINT root;
                NUMBER_HEADER* x2_abs = PMC_Multiply_X_I_Imp(x_abs, 100);
                root.HookNumber(x2_abs);
                Formatter::FormatInternally(x2_abs, writer);
            }

            virtual void WritePrefix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                    switch (_number_format_info->Percent.PositivePattern)
                    {
                    case 0:
                    default:
                        break;
                    case 1:
                        break;
                    case 2:
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 3:
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(L' ');
                        break;
                    }
                }
                else
                {
                    switch (_number_format_info->Percent.NegativePattern)
                    {
                    case 0:
                    default:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 1:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 2:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 3:
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 4:
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(L' ');
                        break;
                    case 8:
                        break;
                    case 9:
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(L' ');
                        break;
                    case 10:
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(L' ');
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 11:
                        break;
                    }
                }
            }

            virtual void FormatNumberSequence(const wchar_t * number_sequence_str, StringWriter * writer) override
            {
                ResourceHolderUINT root;
                ReverseStringReader r_reader(number_sequence_str);
                size_t work_buf_len = lstrlenW(number_sequence_str) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0)
                {
                    writer->Write(_number_format_info->Currency.DecimalSeparator);
                    writer->Write(L'0', _precision);
                }
            }

            virtual void WriteSuffix(char x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                    switch (_number_format_info->Percent.PositivePattern)
                    {
                    case 0:
                    default:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 1:
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    }
                }
                else
                {
                    switch (_number_format_info->Percent.NegativePattern)
                    {
                    case 0:
                    default:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 1:
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 5:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    case 6:
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 7:
                        break;
                    case 8:
                        writer->Write(L' ');
                        writer->Write(_number_format_info->PercentSymbol);
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 9:
                        writer->Write(_number_format_info->NegativeSign);
                        break;
                    case 10:
                        break;
                    case 11:
                        writer->Write(_number_format_info->NegativeSign);
                        writer->Write(L' ');
                        writer->Write(_number_format_info->PercentSymbol);
                        break;
                    }
                }
            }
        };

        static size_t ToStringC(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeC formatter(precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringD(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeD formatter(precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringE(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeE formatter(format_type, precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringF(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeF formatter(precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringN(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeN formatter(precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }


        static size_t ToStringP(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeP formatter(precision, format_option);
            formatter.Format(x_sign, x_abs, &writer);
            return (writer.GetLength());
        }

    }

    namespace HexaDecimalFormatter
    {

        static wchar_t hexadecimal_lower_digits[] = L"0123456789abcdef";
        static wchar_t hexadecimal_upper_digits[] = L"0123456789ABCDEF";

        __inline static void OutputHexNumberSequenceOneWord(__UNIT_TYPE x, unsigned int skip_digit_len, wchar_t* digit_table, StringWriter* writer)
        {
            if (sizeof(__UNIT_TYPE) > sizeof(_UINT64_T))
            {
                // 64bit を超える __UNIT_TYPE には未対応
                // 対応するには以降のコーディングを見直す必要がある
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_tostring.cpp;OutputHexNumberSequenceOneWord;1");
            }
            unsigned int count = __UNIT_TYPE_BIT_COUNT / 4;
            if (skip_digit_len > 0)
            {
                x = _ROTATE_L_UNIT(x, 4 * skip_digit_len);
                count -= skip_digit_len;
            }
            if (count & 0x10)
            {
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
            }
            if (count & 0x8)
            {
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
            }
            if (count & 0x4)
            {
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
            }
            if (count & 0x2)
            {
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
            }
            if (count & 0x1)
            {
                x = _ROTATE_L_UNIT(x, 4); writer->Write(digit_table[x & 0x0f]);
            }
        }

        static size_t ToStringX(char x_sign, NUMBER_HEADER* x_abs, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            if (precision < 1)
                precision = 1;

            StringWriter writer(buffer, buffer_size);
            if (x_abs->IS_ZERO)
            {
                // x == 0 の場合
                // precision 桁だけ '0' を出力する。(precision == 0 であっても 1 桁だけは出力する)

                writer.Write(L'0', precision);
                return (writer.GetLength());
            }
            else
            {
                // x != 0 の場合
                ResourceHolderUINT root;
                __UNIT_TYPE temp_buf_bit_count = x_abs->UNIT_BIT_COUNT + 4;
                __UNIT_TYPE* temp_buf = root.AllocateBlock(temp_buf_bit_count);
                __UNIT_TYPE output_len;
                wchar_t filling_char;
                if (x_sign >= 0)
                {
                    // x >= 0 の場合

                    _COPY_MEMORY_UNIT(temp_buf, x_abs->BLOCK, x_abs->UNIT_WORD_COUNT);
                    __UNIT_TYPE temp_buf_word_count = _DIVIDE_CEILING_UNIT(temp_buf_bit_count, __UNIT_TYPE_BIT_COUNT);
                    output_len = temp_buf_word_count * (__UNIT_TYPE_BIT_COUNT / 4);
                    unsigned char* ptr = (unsigned char*)&temp_buf[temp_buf_word_count] - 1;
                    while (ptr >= (unsigned char*)temp_buf)
                    {
                        if ((ptr[0] >> 4) != 0 || (ptr[0] & 0xf) >= 0x8)
                            break;
                        // 最上位桁が '0' で、かつ次の桁が '0'～'7'である場合
                        // ⇒最上位桁の '0' を削除する
                        --output_len;

                        if (&ptr[-1] < (unsigned char*)temp_buf)
                            break;

                        if (ptr[0] != 0 || (ptr[-1] >> 4) >= 0x8)
                            break;
                        // 最上位桁が '0' で、かつ次の桁が '0'～'7'である場合
                        // ⇒最上位桁の '0' を削除する
                        --output_len;

                        --ptr;
                    }
                    filling_char = L'0';
                }
                else
                {
                    // x < 0 の場合

                    __UNIT_TYPE *in_ptr = x_abs->BLOCK;
                    __UNIT_TYPE *out_ptr = temp_buf;
                    __UNIT_TYPE count = x_abs->UNIT_WORD_COUNT;
                    char carry = 1;
                    while (count > 0)
                    {
                        carry = _ADD_UNIT(carry, ~*in_ptr, 0, out_ptr);
                        ++in_ptr;
                        ++out_ptr;
                        --count;
                    }
                    output_len = x_abs->UNIT_WORD_COUNT * (__UNIT_TYPE_BIT_COUNT / 4);
                    unsigned char* ptr = (unsigned char*)&temp_buf[x_abs->UNIT_WORD_COUNT] - 1;
                    while (ptr >= (unsigned char*)temp_buf)
                    {
                        if ((ptr[0] >> 4) != 0xf || (ptr[0] & 0xf) < 0x8)
                            break;
                        // 最上位桁が 'F' で、かつ次の桁が '8'～'F'である場合
                        // ⇒最上位桁の 'F' を削除する
                        *ptr &= 0x0f;
                        --output_len;

                        if (&ptr[-1] < (unsigned char*)temp_buf)
                            break;

                        if (ptr[0] == 0xf || (ptr[-1] >> 4) < 0x8)
                            break;
                        // 最上位桁が 'F' で、かつ次の桁が '8'～'F'である場合
                        // ⇒最上位桁の 'F' を削除する
                        *ptr = 0;
                        --output_len;

                        --ptr;
                    }
                    filling_char = format_type == L'X' ? L'F' : L'f';
                }
                root.CheckBlock(temp_buf);

                // この時点で 合計桁数は output_len だけあることが判明

                // output_len 桁を格納するためのワード数を調べ、その隙間の桁数を leading_zero_digit_count とする

                unsigned int leading_zero_digit_count = (unsigned int)(_DIVIDE_CEILING_UNIT(output_len, __UNIT_TYPE_BIT_COUNT / 4) * (__UNIT_TYPE_BIT_COUNT / 4) - output_len);


                __UNIT_TYPE filling_digit_len; // 塗りつぶす上位桁の桁数
                __UNIT_TYPE total_length; // 出力する合計の桁数
                if (output_len < (__UNIT_TYPE)precision)
                {
                    filling_digit_len = precision - output_len;
                    total_length = precision;
                }
                else
                {
                    filling_digit_len = 0;
                    total_length = output_len;
                }
                writer.Write(filling_char, filling_digit_len);

                __UNIT_TYPE* s_ptr = &temp_buf[_DIVIDE_CEILING_UNIT(output_len, __UNIT_TYPE_BIT_COUNT / 4) - 1];
                wchar_t* digit_table = format_type == L'X' ? hexadecimal_upper_digits : hexadecimal_lower_digits;
                OutputHexNumberSequenceOneWord(*s_ptr, leading_zero_digit_count, digit_table, &writer);
                --s_ptr;
                while (s_ptr >= temp_buf)
                {
                    OutputHexNumberSequenceOneWord(*s_ptr, 0, digit_table, &writer);
                    --s_ptr;
                }
                return (writer.GetLength());
            }
        }
    }

    namespace CustomFormatter
    {

        static size_t ToStringCustom(char x_sign, NUMBER_HEADER* x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
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

            throw NotSupportedException(L"カスタム書式によるToStringはサポートされていません。");
        }

    }

    __inline static BOOL __IS_ALPHA(wchar_t c)
    {
        if (c >= L'A' && c <= L'Z')
            return (TRUE);
        if (c >= L'a' && c <= L'z')
            return (TRUE);
        return (FALSE);
    }

    __inline static BOOL __IS_DIGIT(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (TRUE);
        return (FALSE);
    }

    static BOOL ParseStandardFormat(const wchar_t* format, wchar_t* format_type, int* precision)
    {
        if (format == nullptr)
        {
            *format_type = L'D';
            *precision = -1;
            return (TRUE);
        }
        else if (format[0] == L'\0')
        {
            *format_type = L'D';
            *precision = -1;
            return (TRUE);
        }
        else if (__IS_ALPHA(format[0]) && format[1] == L'\0')
        {
            *format_type = format[0];
            *precision = -1;
            return (TRUE);
        }
        else if (__IS_ALPHA(format[0]) && __IS_DIGIT(format[1]) && format[2] == L'\0')
        {
            *format_type = format[0];
            *precision = format[1] - L'0';
            return (TRUE);
        }
        else if (__IS_ALPHA(format[0]) && __IS_DIGIT(format[1]) && __IS_DIGIT(format[2]) && format[3] == L'\0')
        {
            *format_type = format[0];
            *precision = (format[1] - L'0') * 10 + (format[2] - L'0');
            return (TRUE);
        }
        else
            return (FALSE);
    }

    static size_t ToString_Imp(char x_sign, NUMBER_HEADER* x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        wchar_t format_type;
        int precision;
        if (!ParseStandardFormat(format, &format_type, &precision))
            return (CustomFormatter::ToStringCustom(x_sign, x_abs, format, format_option, buffer, buffer_size));
        else
        {
            switch (format_type)
            {
            case L'c':
            case L'C':
                return (DecimalFromatter::ToStringC(x_sign, x_abs, L'C', precision, format_option, buffer, buffer_size));
            case L'd':
            case L'D':
                return (DecimalFromatter::ToStringD(x_sign, x_abs, L'D', precision, format_option, buffer, buffer_size));
            case L'e':
            case L'E':
                return (DecimalFromatter::ToStringE(x_sign, x_abs, format_type, precision, format_option, buffer, buffer_size));
            case L'f':
            case L'F':
                return (DecimalFromatter::ToStringF(x_sign, x_abs, L'F', precision, format_option, buffer, buffer_size));
            case L'g':
            case L'G':
                return (DecimalFromatter::ToStringD(x_sign, x_abs, L'D', precision, format_option, buffer, buffer_size));
            case L'n':
            case L'N':
                return (DecimalFromatter::ToStringN(x_sign, x_abs, L'N', precision, format_option, buffer, buffer_size));
            case L'p':
            case L'P':
                return (DecimalFromatter::ToStringP(x_sign, x_abs, L'P', precision, format_option, buffer, buffer_size));
            case L'r':
            case L'R':
                return (DecimalFromatter::ToStringD(x_sign, x_abs, L'D', 0, format_option, buffer, buffer_size));
            case L'x':
            case L'X':
                return (HexaDecimalFormatter::ToStringX(x_sign, x_abs, format_type, precision, format_option, buffer, buffer_size));
            default:
                throw FormatException(L"未知の書式指定子です。");
            }
        }
    }

    size_t __PMC_CALL PMC_ToString(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"x");
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        NUMBER_HEADER* nx = (NUMBER_HEADER*)x;
        CheckNumber(nx);
        return (ToString_Imp(nx->IS_ZERO ? 0 : 1, nx, format, format_option, buffer, buffer_size));
    }

    void InitializeNumberFormatoInfo(PMC_NUMBER_FORMAT_INFO* info)
    {
        info->Currency.DecimalDigits = 2;
        lstrcpyW(info->Currency.DecimalSeparator, L".");
        lstrcpyW(info->Currency.GroupSeparator, L",");
        lstrcpyW(info->Currency.GroupSizes, L"3");
        info->Currency.NegativePattern = 0;
        info->Currency.PositivePattern = 0;

        info->Number.DecimalDigits = 2;
        lstrcpyW(info->Number.DecimalSeparator, L".");
        lstrcpyW(info->Number.GroupSeparator, L",");
        lstrcpyW(info->Number.GroupSizes, L"3");
        info->Number.NegativePattern = 1;
        info->Number.PositivePattern = -1; // 未使用

        info->Percent.DecimalDigits = 2;
        lstrcpyW(info->Percent.DecimalSeparator, L".");
        lstrcpyW(info->Percent.GroupSeparator, L",");
        lstrcpyW(info->Percent.GroupSizes, L"3");
        info->Percent.NegativePattern = 0;
        info->Percent.PositivePattern = 0;

        lstrcpyW(info->CurrencySymbol, L"\u00a4");
        lstrcpyW(info->NegativeSign, L"-");
        lstrcpyW(info->PercentSymbol, L"%");
        lstrcpyW(info->PerMilleSymbol, L"\u2030");
        lstrcpyW(info->PositiveSign, L"+");
    }

    void __PMC_CALL PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info)
    {
        InitializeNumberFormatoInfo(info);
    }

    PMC_STATUS_CODE Initialize_ToString(PROCESSOR_FEATURES *feature)
    {
        InitializeNumberFormatoInfo(&default_number_format_option);

        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */