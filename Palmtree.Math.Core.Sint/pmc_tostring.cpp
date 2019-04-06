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
            const size_t digit_count_on_word = 9;
#elif defined (_M_X64)
            const __UNIT_TYPE _10n_base_number = 10000000000000000000UL; // 10^19
            const size_t digit_count_on_word = 19;
#else
#error unknown platform
#endif

        protected:
            wchar_t _format_type;
            int _precision;
            const PMC_NUMBER_FORMAT_INFO* _number_format_info;
            bool _omitted_trailing_sequential_zero; // 最下位の連続する 0 を省略する (書式 g/G の場合のみ)

        protected:
            Formatter(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
            {
                _format_type = format_type;
                _precision = precision;
                _number_format_info = number_format_info;
                _omitted_trailing_sequential_zero = false;
            }

        public:
            void Format(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, StringWriter* writer)
            {
                _precision = GetDefaultPrecisionValue(_precision);

                if (x_denominator->FLAGS.IS_ZERO)
                    throw DivisionByZeroException(L"数値の分母が 0 になっています。");

                if (x_numerator->FLAGS.IS_ZERO)
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

                    ResourceHolderSINT root;

                    // 丸め処理をする
                    _INT32_T exp;
                    RoundValue(x_numerator, x_denominator, &x_numerator, &x_denominator, &exp);
                    root.HookNumber(x_numerator);
                    root.HookNumber(x_denominator);
                    if (x_numerator->FLAGS.IS_ZERO)
                    {
                        // 丸めの結果が 0 になったら符号も 0 に変更する。
                        x_sign = SIGN_ZERO;
                        WritePrefix(x_sign, writer);
                        WriteZeroValue(writer);
                        WriteSuffix(x_sign, writer);
                    }
                    else
                    {
                        WritePrefix(x_sign, writer);
                        FormatInternally(x_numerator, x_denominator, exp, writer);
                        WriteSuffix(x_sign, writer);
                    }
                }
            }

        protected:
            virtual int GetDefaultPrecisionValue(int specified_precision) = 0;

            virtual void FormatInternally(PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, _INT32_T exp, StringWriter* writer)
            {
                ResourceHolderSINT root;
                //_INT32_T exp;
                //RoundValue(x_numerator, x_denominator, &x_numerator, &x_denominator, &exp);
                //root.HookNumber(x_numerator);
                //root.HookNumber(x_denominator);
                PMC_HANDLE_UINT frac_part_denominator = x_denominator;
                PMC_HANDLE_UINT int_part;
                PMC_HANDLE_UINT frac_part_numerator = ep_uint.DivRem(x_numerator, x_denominator, &int_part);
                root.HookNumber(int_part);
                root.HookNumber(frac_part_numerator);
                __UNIT_TYPE int_part_buffer_size = int_part->FLAGS.IS_ZERO ? 1 : ep_uint.FloorLog10(int_part) + 1;
                int_part_buffer_size = int_part_buffer_size * 2 + 1; // 3桁区切り記号と終端ヌル文字の分のサイズを追加
                wchar_t* int_part_buffer = root.AllocateString(int_part_buffer_size);

                // 小数部の最大長は precision +3
                //    書式がg/Gの場合、指数部が -5 以下の場合は指数表現形式となるので小数部の長さは precision - 1
                //                     指数部が precision 以上の場合も指数表現形式となるので小数部の長さは precision - 1
                //                     それ以外の場合の小数部の長さは、指数部が -4 となる数値を固定小数点で表示した場合で、precision + 3 となる
                //    書式がg/G以外の場合、precisionは小数部の長さとして扱われるので、最大長は precision である
                // すべての書式を総合すると、小数部の長さは precision + 3 ということになる
                size_t frac_part_buffer_size = _precision + 3 + 1;

                wchar_t* frac_part_buffer = root.AllocateString(frac_part_buffer_size);
                wchar_t* top_of_int_part = ConstructIntegerPartNumberSequence(int_part, int_part_buffer, int_part_buffer_size);
                root.CheckString(int_part_buffer);
                ConstructFractionPartNumberSequence(frac_part_numerator, frac_part_denominator, GetFractionPartLength(), frac_part_buffer, frac_part_buffer_size);
                root.CheckString(frac_part_buffer);
                FormatNumberSequence(top_of_int_part, frac_part_buffer, exp, writer);
            }

            // 0 値を表す文字列を writer に設定します。
            virtual void WriteZeroValue(StringWriter* writer) = 0;

            // 小数点以下の丸め処理 (および必要なら小数点位置の移動) を行います。
            virtual void RoundValue(PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_HANDLE_UINT* r_numerator, PMC_HANDLE_UINT* r_denominator, _INT32_T* exp)
            {
                *r_numerator = ep_uint.Round(x_numerator, x_denominator, _precision, PMC_MIDPOINT_ROUNDING_HALF_EVEN, r_denominator);
                *exp = 0;
            }

            // 現在の書式における小数部の長さを返します。
            virtual size_t GetFractionPartLength()
            {
                return (_precision);
            }

            // 数値の前に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
            virtual void WritePrefix(SIGN_T x_sign, StringWriter* writer) = 0;

            // 整数部を表す単純な数字列を書式に応じて変換し、StringWriterに書き込みます。(例: precision に応じた 0 パディング、3桁区切り、小数点、小数、指数表記、など)
            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) = 0;

            // 数値の後に表示される文字列を書き込みます。(例: 符号、通貨記号、など)
            virtual void WriteSuffix(SIGN_T x_sign, StringWriter* writer) = 0;

        private:
            wchar_t* ConstructIntegerPartNumberSequence(PMC_HANDLE_UINT int_part, wchar_t* out_buf, size_t out_buf_count)
            {
                ReverseStringWriter simple_number_sequence_writer(out_buf, out_buf_count);

                while (true)
                {
                    __UNIT_TYPE data = ep_uint.DivRem(int_part, _10n_base_number, &int_part);
                    if (int_part->FLAGS.IS_ZERO)
                    {
                        WriteIntPartLeadingOneWord(&simple_number_sequence_writer, data);
                        break;
                    }
                    WriteIntPartTrailingWord(&simple_number_sequence_writer, data);
                }
                return (simple_number_sequence_writer.GetString());
            }

            void ConstructFractionPartNumberSequence(PMC_HANDLE_UINT frac_part_numerator, PMC_HANDLE_UINT frac_part_denominator, size_t max_fraction_part_length, wchar_t* out_buf, size_t out_buf_count)
            {
                StringWriter simple_number_sequence_writer(out_buf, out_buf_count);
                ResourceHolderSINT root;

                size_t fraction_part_length = max_fraction_part_length;

                while (!frac_part_numerator->FLAGS.IS_ZERO)
                {
                    frac_part_numerator = ep_uint.Multiply(frac_part_numerator, _10n_base_number);
                    root.HookNumber(frac_part_numerator);
                    PMC_HANDLE_UINT digit;
                    frac_part_numerator = ep_uint.DivRem(frac_part_numerator, frac_part_denominator, &digit);
                    root.HookNumber(digit);
                    root.HookNumber(frac_part_numerator);

                    if (fraction_part_length >= digit_count_on_word)
                    {
                        // digit を digit_count_on_word 桁の 10 進整数として数字列を書き込む
#ifdef _M_IX86
                        __UNIT_TYPE digit_word = ep_uint.ToUInt32(digit);
                        WriteFracPartLeadingWord(&simple_number_sequence_writer, digit_word);
#elif defined(_M_X64)
                        __UNIT_TYPE digit_word = ep_uint.ToUInt64(digit);
                        WriteFracPartLeadingWord(&simple_number_sequence_writer, digit_word);
#else
#error unknown platform
#endif
                        fraction_part_length -= digit_count_on_word;
                    }
                    else
                    {
                        // digit を digit_count_on_word 桁の 10 進整数として、上位から fraction_part_length 桁だけ数字列を書き込む
#ifdef _M_IX86
                        __UNIT_TYPE digit_word = ep_uint.ToUInt32(digit);
                        WriteFracPartTrailingOneWord(&simple_number_sequence_writer, digit_word, fraction_part_length);
#elif defined(_M_X64)
                        __UNIT_TYPE digit_word = ep_uint.ToUInt64(digit);
                        WriteFracPartTrailingOneWord(&simple_number_sequence_writer, digit_word, fraction_part_length);
#else
#error unknown platform
#endif
                        fraction_part_length = 0;
                        break;
                    }
                }
                if (_omitted_trailing_sequential_zero)
                {
                    // 末尾の連続する 0 を削除する指定がされている場合は削除する
                    wchar_t* tail = out_buf + lstrlenW(out_buf);
                    while (tail > out_buf && tail[-1] == L'0')
                    {
                        --tail;
                        *tail = L'\0';
                    }
                }
                else
                {
                    // fraction_part_length 桁だけ '0' で埋める
                    simple_number_sequence_writer.Write(L'0', fraction_part_length);
                }
            }

            // 整数部の最上位のワードを文字列化する。(途中で x が 0 になった場合は中断する)
            void WriteIntPartLeadingOneWord(StringWriter* writer, __UNIT_TYPE x)
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

            // 整数部の上位から 2 ワード目以降を文字列化する。(途中で x が 0 になっても続行する)
            void WriteIntPartTrailingWord(StringWriter* writer, __UNIT_TYPE x)
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

            // 小数部の最下位のワードを文字列化する。(count 桁で打ち切る)
            void WriteFracPartTrailingOneWord(StringWriter* writer, __UNIT_TYPE x, size_t count)
            {
                __UNIT_TYPE q;
#if _M_X64
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 1000UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 100UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = _DIVREM_UNIT(0, x, 10UL, &x); WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
                if (count <= 0) return; q = x; WriteDigit(writer, (_UINT32_T)q); --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    IncrementDIV64Counter(digit_count_on_word);
                else
                    IncrementDIV32Counter(digit_count_on_word);
#endif
            }

            // 小数部の最下位ワード以外のワードを文字列化する。(digit_count_on_word 桁だけ続ける)
            void WriteFracPartLeadingWord(StringWriter* writer, __UNIT_TYPE x)
            {
                __UNIT_TYPE q;
#if _M_X64
                q = _DIVREM_UNIT(0, x, 1000000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 100000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 1000000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 100000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 1000000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 100000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 1000000000U, &x); WriteDigit(writer, (_UINT32_T)q);
#endif
                q = _DIVREM_UNIT(0, x, 100000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 1000000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 100000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 1000U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 100U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = _DIVREM_UNIT(0, x, 10U, &x); WriteDigit(writer, (_UINT32_T)q);
                q = x; WriteDigit(writer, (_UINT32_T)q);
#ifdef ENABLED_PERFORMANCE_COUNTER
                if (sizeof(r) == sizeof(_UINT64_T))
                    AddToDIV64Counter(digit_count_on_word);
                else
                    AddToDIV32Counter(digit_count_on_word);
#endif
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
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision >= 0 ? specified_precision : _number_format_info->Currency.DecimalDigits);
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

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
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
                        writer->Write(_number_format_info->CurrencySymbol);
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

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
                ResourceHolderSINT root;
                ReverseStringReader r_reader(int_part);
                size_t work_buf_len = lstrlenW(int_part) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0 && frac_part[0] != L'\0')
                {
                    writer->Write(_number_format_info->Currency.DecimalSeparator);
                    writer->Write(frac_part);
                }
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
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

        class FormatterTypeE
            : public Formatter
        {
        public:
            FormatterTypeE(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(format_type, precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision >= 0 ? specified_precision : 6);
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

            static SIGN_T Compare_R_UI(PMC_HANDLE_UINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v)
            {
                ResourceHolderSINT root;
                PMC_HANDLE_UINT v2 = ep_uint.Multiply(v, u_denominator);
                root.HookNumber(v2);
                return (ep_uint.Compare(u_numerator, v2));
            }

            virtual void RoundValue(PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_HANDLE_UINT* r_numerator, PMC_HANDLE_UINT* r_denominator, _INT32_T* exp)
            {
                ResourceHolderSINT root;
                // 最上位桁が 1 の位になるように 10 のべき乗をかけるあるいは割って、桁をずらす。
                *exp = ep_uint.FloorLog10(x_numerator, x_denominator);
                if (*exp == 0)
                {
                    *r_numerator = x_numerator;
                    *r_denominator = x_denominator;
                }
                else if (*exp > 0)
                {
                    PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, *exp);
                    *r_numerator = x_numerator;
                    *r_denominator = ep_uint.Multiply(x_denominator, factor);
                    root.HookNumber(*r_denominator);
                }
                else
                {
                    PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, -*exp);
                    *r_numerator = ep_uint.Multiply(x_numerator, factor);
                    root.HookNumber(*r_numerator);
                    *r_denominator = x_denominator;
                }
                // 桁を丸める
                *r_numerator = ep_uint.Round(*r_numerator, *r_denominator, _precision, PMC_MIDPOINT_ROUNDING_HALF_EVEN, r_denominator);
                root.HookNumber(*r_numerator);
                root.HookNumber(*r_denominator);
                // 桁を丸めた結果繰り上がりによって最上位桁が 10 の位になってしまった場合は、更に 1 桁だけ桁をずらす
                if (Compare_R_UI(*r_numerator, *r_denominator, 10U) >= 0)
                {
                    *r_denominator = ep_uint.Multiply(*r_denominator, 10U);
                    root.HookNumber(*r_denominator);
                    *exp = *exp + 1;
                }
                root.UnlinkNumber(*r_numerator);
                root.UnlinkNumber(*r_denominator);
            }

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
#ifdef _DEBUG
                if (lstrlenW( int_part) != 1)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;FormatterTypeE::FormatNumberSequence;1");
#endif
                writer->Write(int_part);
                if (_precision > 0 && frac_part[0] != L'\0')
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(frac_part);
                }
                writer->Write(_format_type); // 'e' or 'E'
                if (exp >= 0)
                {
                    writer->Write(_number_format_info->PositiveSign);
                }
                else
                {
                    writer->Write(_number_format_info->NegativeSign);
                    exp = -exp;
                }

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
                wsprintfW(exp_buf, L"%03d", exp);
                writer->Write(exp_buf);
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
            {
            }
        };

        class FormatterTypeF
            : public Formatter
        {
        public:
            FormatterTypeF(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(format_type, precision, number_format_info)
            {
            }

        protected:
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision >= 0 ? specified_precision : _number_format_info->Number.DecimalDigits);
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

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
                writer->Write(int_part);
                if (_precision > 0 && frac_part[0] != L'\0')
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(frac_part);
                }
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
            {
            }
        };

        class FormatterTypeG
            : public Formatter
        {
            /*
                g/G指定時の注意
                1)小数部の最下位の連続する0は省略される
                2)精度指定子は「有効桁数」と解釈される。
                3)精度指定子が0の場合は既定の精度(15)となる
                4)指数が-5より大きく精度指定子より小さい場合は固定小数表記、それ以外の場合は指数表記で表示される。
                5)数値が0の場合は1)と4)よりにより単に0と表示される。
                6)指数表記の場合、指数部は最低でも2桁表示される。
            */

        private:
            bool _is_exponential_format;

        public:
            FormatterTypeG(wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* number_format_info)
                : Formatter(format_type, precision, number_format_info)
            {
                _omitted_trailing_sequential_zero = true;
                _is_exponential_format = true;
            }

        protected:
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision > 0 ? specified_precision : 15);
            }

            virtual void WriteZeroValue(StringWriter * writer) override
            {
                writer->Write(L'0');
            }

            static SIGN_T Compare_R_UI(PMC_HANDLE_UINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v)
            {
                ResourceHolderSINT root;
                PMC_HANDLE_UINT v2 = ep_uint.Multiply(v, u_denominator);
                root.HookNumber(v2);
                return (ep_uint.Compare(u_numerator, v2));
            }

            virtual void RoundValue(PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_HANDLE_UINT* r_numerator, PMC_HANDLE_UINT* r_denominator, _INT32_T* exp)
            {
                ResourceHolderSINT root;
                // 最上位桁が 1 の位になるように 10 のべき乗をかけるあるいは割って、桁をずらす。
                *exp = ep_uint.FloorLog10(x_numerator, x_denominator);
                if (*exp == 0)
                {
                    *r_numerator = x_numerator;
                    *r_denominator = x_denominator;
                }
                else if (*exp > 0)
                {
                    PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, *exp);
                    *r_numerator = x_numerator;
                    *r_denominator = ep_uint.Multiply(x_denominator, factor);
                    root.HookNumber(*r_denominator);
                }
                else
                {
                    PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, -*exp);
                    *r_numerator = ep_uint.Multiply(x_numerator, factor);
                    root.HookNumber(*r_numerator);
                    *r_denominator = x_denominator;
                }
#if _DEBUG
                // この時点で数値は1以上10未満であるはず
                if (Compare_R_UI(*r_numerator, *r_denominator, 1U) < 0 || Compare_R_UI(*r_numerator, *r_denominator, 10U) >= 0)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;FormatterTypeG::RoundValue;1");
#endif
                // 桁を丸める
                *r_numerator = ep_uint.Round(*r_numerator, *r_denominator, _precision - 1, PMC_MIDPOINT_ROUNDING_HALF_EVEN, r_denominator);
                root.HookNumber(*r_numerator);
                root.HookNumber(*r_denominator);
                // 桁を丸めた結果繰り上がりによって最上位桁が 10 の位になってしまった場合は、更に 1 桁だけ桁をずらす
                if (Compare_R_UI(*r_numerator, *r_denominator, 10U) >= 0)
                {
                    *r_denominator = ep_uint.Multiply(*r_denominator, 10U);
                    root.HookNumber(*r_denominator);
                    *exp = *exp + 1;
                }
                if (*exp > -5 && *exp < _precision)
                {
                    // 固定小数点表記に戻す
                    _is_exponential_format = false;
                    if (*exp == 0)
                    {
                        // nop
                    }
                    else if (*exp > 0)
                    {
                        PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, *exp);
                        *r_numerator = ep_uint.Multiply(*r_numerator, factor);
                        root.HookNumber(*r_numerator);
                        *exp = 0;
                    }
                    else
                    {
                        PMC_HANDLE_UINT factor = ep_uint.Pow(number_handle_uint_ten, -*exp);
                        *r_denominator = ep_uint.Multiply(*r_denominator, factor);
                        root.HookNumber(*r_denominator);
                        *exp = 0;
                    }
                }
                // 分子と分母の最大公約数を求める
                PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(*r_numerator, *r_denominator);
                root.HookNumber(gcd);
                if (!gcd->FLAGS.IS_ONE)
                {
                    // 最大公約数が 1 ではない (既約ではない) 場合

                    // 分子と分母をそれぞれ最大公約数で割る
                    *r_numerator = ep_uint.DivideExactly(*r_numerator, gcd);
                    root.HookNumber(*r_numerator);
                    *r_denominator = ep_uint.DivideExactly(*r_denominator, gcd);
                    root.HookNumber(*r_denominator);
                }

                root.UnlinkNumber(*r_numerator);
                root.UnlinkNumber(*r_denominator);
            }

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
            {
                if (x_sign < 0)
                    writer->Write(_number_format_info->NegativeSign);
            }

            virtual size_t GetFractionPartLength() override
            {
                return (_precision + 3);
            }

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
                if (_is_exponential_format)
                {
#ifdef _DEBUG
                    if (lstrlenW(int_part) != 1)
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_tostring.cpp;FormatterTypeG::FormatNumberSequence;1");
#endif
                    writer->Write(int_part);
                    if (_precision > 0 && frac_part[0] != L'\0')
                    {
                        writer->Write(_number_format_info->Number.DecimalSeparator);
                        writer->Write(frac_part);
                    }
                    writer->Write(_format_type - (L'G' - L'E'));
                    if (exp >= 0)
                    {
                        writer->Write(_number_format_info->PositiveSign);
                    }
                    else
                    {
                        writer->Write(_number_format_info->NegativeSign);
                        exp = -exp;
                    }

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
                    wsprintfW(exp_buf, L"%02d", exp);
                    writer->Write(exp_buf);
                }
                else
                {
                    writer->Write(int_part);
                    if (_precision > 0 && frac_part[0] != L'\0')
                    {
                        writer->Write(_number_format_info->Number.DecimalSeparator);
                        writer->Write(frac_part);
                    }
                }
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
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
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision >= 0 ? specified_precision : _number_format_info->Number.DecimalDigits);
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

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
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

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
                ResourceHolderSINT root;
                ReverseStringReader r_reader(int_part);
                size_t work_buf_len = lstrlenW(int_part) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0 && frac_part[0] != L'\0')
                {
                    writer->Write(_number_format_info->Number.DecimalSeparator);
                    writer->Write(frac_part);
                }
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
            {
                if (x_sign >= 0)
                {
                }
                else
                {
                    switch (_number_format_info->Number.NegativePattern)
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
            virtual int GetDefaultPrecisionValue(int specified_precision) override
            {
                return (specified_precision >= 0 ? specified_precision : _number_format_info->Percent.DecimalDigits);
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

            virtual void RoundValue(PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_HANDLE_UINT* r_numerator, PMC_HANDLE_UINT* r_denominator, _INT32_T* exp)
            {

                ResourceHolderSINT root;
                *r_numerator = x_numerator;
                *r_denominator = x_denominator;

                // 桁を丸める
                *r_numerator = ep_uint.Round(*r_numerator, *r_denominator, _precision, PMC_MIDPOINT_ROUNDING_HALF_EVEN, r_denominator);
                root.HookNumber(*r_numerator);
                root.HookNumber(*r_denominator);
                *exp = 0;

                // x を 100 倍する
                *r_numerator = ep_uint.Multiply(*r_numerator, 100U);
                //root.HookNumber(*r_numerator); // 直後に unlink があるので、ともに省略する。

                //root.UnlinkNumber(*r_numerator);
                root.UnlinkNumber(*r_denominator);
            }

            virtual void WritePrefix(SIGN_T x_sign, StringWriter * writer) override
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

            virtual void FormatNumberSequence(const wchar_t* int_part, const wchar_t* frac_part, _INT32_T exp, StringWriter* writer) override
            {
                ResourceHolderSINT root;
                ReverseStringReader r_reader(int_part);
                size_t work_buf_len = lstrlenW(int_part) * 2 + 1 + _precision + 1;
                wchar_t* work_buf = root.AllocateString(work_buf_len);
                ReverseStringWriter r_writer(work_buf, work_buf_len);
                ThousandSeparatedStringWriter t_writer(&r_writer, _format_type, _number_format_info);
                while (r_reader.PeekChar() != L'\0')
                    t_writer.Write(r_reader.ReadChar());
                writer->Write(t_writer.GetString());
                if (_precision > 0 && frac_part[0] != L'\0')
                {
                    writer->Write(_number_format_info->Percent.DecimalSeparator);
                    writer->Write(frac_part);
                }
            }

            virtual void WriteSuffix(SIGN_T x_sign, StringWriter * writer) override
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

        static size_t ToStringC(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeC formatter(precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringE(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeE formatter(format_type, precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringF(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeF formatter(format_type, precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringG(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeG formatter(format_type, precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }

        static size_t ToStringN(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeN formatter(precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }


        static size_t ToStringP(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, wchar_t format_type, int precision, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
        {
            StringWriter writer(buffer, buffer_size);
            FormatterTypeP formatter(precision, format_option);
            formatter.Format(x_sign, x_numerator, x_denominator, &writer);
            return (writer.GetLength());
        }

    }

    namespace CustomFormatter
    {

        static size_t ToStringCustom(SIGN_T x_sign, PMC_HANDLE_UINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
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

    size_t PMC_ToString_R(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_SINT* nx_numerator = GET_NUMBER_OBJECT(x_numerator, L"x_numerator");
        if (format_option == nullptr)
            format_option = &default_number_format_option;
        wchar_t format_type;
        int precision;
        if (!ParseStandardFormat(format, &format_type, &precision))
            return (CustomFormatter::ToStringCustom(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, format, format_option, buffer, buffer_size));
        else
        {
            switch (format_type)
            {
            case L'c':
            case L'C':
                return (DecimalFromatter::ToStringC(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, L'C', precision, format_option, buffer, buffer_size));
            case L'e':
            case L'E':
                return (DecimalFromatter::ToStringE(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, format_type, precision, format_option, buffer, buffer_size));
            case L'f':
            case L'F':
                return (DecimalFromatter::ToStringF(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, L'F', precision, format_option, buffer, buffer_size));
            case L'g':
            case L'G':
                return (DecimalFromatter::ToStringG(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, format_type, precision, format_option, buffer, buffer_size));
            case L'n':
            case L'N':
                return (DecimalFromatter::ToStringN(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, L'N', precision, format_option, buffer, buffer_size));
            case L'p':
            case L'P':
                return (DecimalFromatter::ToStringP(nx_numerator->SIGN, nx_numerator->ABS, x_denominator, L'P', precision, format_option, buffer, buffer_size));
            default:
                throw FormatException(L"未知の書式指定子です。");
            }
        }
    }

    size_t PMC_ToString_X(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        size_t count = ep_uint.ToStringForSINT(nx->SIGN, nx->ABS, format, format_option, buffer, buffer_size);
        return (count);
    }

    void PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false)
    {
        ep_uint.InitializeNumberFormatInfo(info);
    }

    PMC_STATUS_CODE Initialize_ToString()
    {
        PMC_InitializeNumberFormatInfo(&default_number_format_option);

        return (PMC_STATUS_OK);
    }

}

/*
 * END OF FILE
 */