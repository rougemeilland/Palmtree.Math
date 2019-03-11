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


using System;
using System.Linq;
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace Palmtree.Math.Core
{
    internal enum PMC_STATUS_CODE
    {
        PMC_STATUS_OK = 0,
        PMC_STATUS_ARGUMENT_ERROR = -1,
        PMC_STATUS_ARGUMENT_NULL_ERROR = -2,
        PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR = -3,
        PMC_STATUS_OVERFLOW = -4,
        PMC_STATUS_DIVISION_BY_ZERO = -5,
        PMC_STATUS_ARITHMETIC_ERROR = -6,
        PMC_STATUS_FORMAT_ERROR = -7,
        PMC_STATUS_INSUFFICIENT_BUFFER = -8,
        PMC_STATUS_NOT_ENOUGH_MEMORY = -9,
        PMC_STATUS_NOT_SUPPORTED = -10,
        PMC_STATUS_INTERNAL_ERROR = -256,
        PMC_STATUS_BAD_BUFFER = -257,
    }

    internal enum PMC_CONSTANT_CODE
    {
        PMC_CONSTANT_ZERO = 1,
        PMC_CONSTANT_ONE = 2,
        PMC_CONSTANT_MINUS_ONE = 3,
    }

    [Flags]
    internal enum PMC_NUMBER_STYLE_CODE
    {
        PMC_NUMBER_STYLE_NONE = 0x0000,                   // スタイル要素 =先行する空白、後続の空白、桁区切り記号、小数点の記号など, を解析対象の文字列に含めることができないことを示す。
        PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE = 0x0001,    // 先行する空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
        PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE = 0x0002,   // 末尾の空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
        PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN = 0x0004,     // 数値文字列に先行する符号を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN = 0x0008,    // 数値文字列に後続する符号を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_PARENTHESES = 0x0010,      // 数値文字列にその数値を囲む一組の括弧を使用できることを示す。括弧は解析対象の文字列が負の値を表すことを示す。
        PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT = 0x0020,    // 数値文字列に小数点を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_THOUSANDS = 0x0040,        // 先行する空白文字を解析対象の文字列に使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL = 0x0100,  // 数字文字列に通貨記号を含めることができることを示す。
        PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER = 0x0200,    // 数値文字列が16進数を表すことを示す。
        PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER = 0x01000000,       // 数値文字列に負の符号または負数を示すカッコを含むことを許可する
        PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING = 0x02000000,   // 変換時にエラーを検出した場合に例外で通知することを許可する
    }

    [StructLayout(LayoutKind.Sequential)]
    internal class PMC_STATISTICS_INFO
    {
        #region パブリックフィールド

        public UInt32 COUNT_MULTI64; // 32bit * 32bit => 64bitの乗算の回数
        public UInt32 COUNT_MULTI32; // 16bit * 16bit => 32bitの乗算の回数
        public UInt32 COUNT_DIV64;   // 64bit / 32bit => 32bitの除算の回数
        public UInt32 COUNT_DIV32;   // 32bit / 16bit => 16bitの除算の回数

        #endregion

        #region コンストラクタ

        public PMC_STATISTICS_INFO()
        {
            COUNT_MULTI64 = 0;
            COUNT_MULTI32 = 0;
            COUNT_DIV64 = 0;
            COUNT_DIV32 = 0;
        }

        #endregion
    }


    [StructLayout(LayoutKind.Sequential)]
    internal class PMC_CONFIGURATION_INFO
    {
        #region パブリックフィールド

        public byte MEMORY_VERIFICATION_ENABLED; // 未使用

        #endregion

        #region コンストラクタ

        public PMC_CONFIGURATION_INFO()
        {
            MEMORY_VERIFICATION_ENABLED = 0;
        }

        #endregion
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    internal struct PMC_DECIMAL_NUMBER_FORMAT_INFO
    {
        #region パブリックフィールド

        public int DecimalDigits;       // 数値の小数点以下の既定の桁数として解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string DecimalSeparator; // 数値の整数部と小数部との区切り文字と解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string GroupSeparator;   // 数値をグループで区切る場合の区切り文字と解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string GroupSizes;       // 数値をグループで区切る場合のグループの大きさを示す文字の集合と解釈される。
        public int NegativePattern;     // 負数を表示する場合のパターンを示す番号。
        public int PositivePattern;     // 正数を表示する場合のパターンを示す番号。

        #endregion

        #region コンストラクタ

        public PMC_DECIMAL_NUMBER_FORMAT_INFO(int decimal_digits, string decimal_separator, string group_separator, int[] group_sizes, int negative_pattern, int positive_pattern)
        {
            DecimalDigits = decimal_digits;
            if (decimal_separator.Length > 16)
                throw new InternalErrorException();
            DecimalSeparator = decimal_separator;
            if (group_separator.Length > 16)
                throw new InternalErrorException();
            GroupSeparator = group_separator;
            if (group_sizes.Length > 10)
                throw new InternalErrorException();
            GroupSizes = string.Concat(group_sizes);
            NegativePattern = negative_pattern;
            PositivePattern = positive_pattern;
        }

        #endregion
    }

    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    internal class PMC_NUMBER_FORMAT_INFO
    {
        #region パブリックフィールド

        public PMC_DECIMAL_NUMBER_FORMAT_INFO Currency; // 通貨量の数値を表示する場合に使用される情報。
        public PMC_DECIMAL_NUMBER_FORMAT_INFO Number;   // 一般的な数値を表示する場合に使用される情報。
        public PMC_DECIMAL_NUMBER_FORMAT_INFO Percent;  // パーセント値を表示する場合に使用される情報。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string CurrencySymbol;                   // 通貨記号として使用される文字列。既定値は "¤"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string NegativeSign;                     // 負数であることを示す文字列。既定値は "-"。            
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PositiveSign;                     // 正数であることを示す文字列。既定値は "+"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PercentSymbol;                    // パーセント記号として使用する文字列。既定値は "%"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PerMilleSymbol;                   // パーミル記号として使用する文字列。既定値は "\u2030"。

        #endregion

        #region コンストラクタ

        public PMC_NUMBER_FORMAT_INFO(NumberFormatInfo source)
        {
            Currency = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.CurrencyDecimalDigits, source.CurrencyDecimalSeparator, source.CurrencyGroupSeparator, source.CurrencyGroupSizes, source.CurrencyNegativePattern, source.CurrencyPositivePattern);
            Number = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.NumberDecimalDigits, source.NumberDecimalSeparator, source.NumberGroupSeparator, source.NumberGroupSizes, source.NumberNegativePattern, -1);
            Percent = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.PercentDecimalDigits, source.PercentDecimalSeparator, source.PercentGroupSeparator, source.PercentGroupSizes, source.PercentNegativePattern, source.PercentPositivePattern);
            if (source.CurrencySymbol.Length > 16)
                throw new InternalErrorException();
            CurrencySymbol = source.CurrencySymbol;
            if (source.NegativeSign.Length > 16)
                throw new InternalErrorException();
            NegativeSign = source.NegativeSign;
            if (source.PercentSymbol.Length > 16)
                throw new InternalErrorException();
            PercentSymbol = source.PercentSymbol;
            if (source.PerMilleSymbol.Length > 16)
                throw new InternalErrorException();
            PerMilleSymbol = source.PerMilleSymbol;
            if (source.PositiveSign.Length > 16)
                throw new InternalErrorException();
            PositiveSign = source.PositiveSign;
        }

        #endregion

    }

    public class StatisticsInfo
    {
        #region コンストラクタ

        internal StatisticsInfo(PMC_STATISTICS_INFO source)
        {
            Multi64Count = source.COUNT_MULTI64;
            Multi32Count = source.COUNT_MULTI32;
            Div64Count = source.COUNT_DIV64;
            Div32Count = source.COUNT_DIV32;
        }

        #endregion

        #region パブリックプロパティ

        public UInt32 Multi64Count { get; }
        public UInt32 Multi32Count { get; }
        public UInt32 Div64Count { get; }
        public UInt32 Div32Count { get; }

        #endregion

    }


    internal class UBigIntEngine
            : IUBigIntDisposable
    {
        #region WIN32 API の宣言

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool SetDllDirectory(string lpPathName);

        #endregion

        #region コンストラクタ

        static UBigIntEngine()
        {
            var this_assembly = typeof(UBigIntEngine).Assembly;
            var this_assembly_path = this_assembly.Location;
            var base_directory_path = Path.GetDirectoryName(this_assembly_path);
            string sub_dir;
            if (IntPtr.Size == 8)
                sub_dir = "x64";
            else if (IntPtr.Size == 4)
                sub_dir = "x86";
            else
                throw new PlatformNotSupportedException();
            var dll_dir_path = Path.Combine(base_directory_path, sub_dir);
            if (!SetDllDirectory(dll_dir_path))
            {
                int error = Marshal.GetLastWin32Error();
                throw new InternalErrorException(string.Format("SetDllDirectory がエラーを通知しました。: errno={0}", error));
            }
            PMC_CONFIGURATION_INFO conf = new PMC_CONFIGURATION_INFO();
            if (PMCCS_UINT_Initialize(conf) == 0)
                throw new InternalErrorException("DLL 'Palmtree.Math.Core.Uint.dll' の初期化に失敗しました。");
        }

        #endregion

        #region パブリックメソッド

        public string GetConfigurationSettings(string key)
        {
            int needed_capacity;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConfigurationSettingCount(key, IntPtr.Zero, 0, out needed_capacity));
            var value_buffer = new StringBuilder(needed_capacity);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConfigurationSettings(key, value_buffer, value_buffer.Capacity, out needed_capacity));
            return (value_buffer.ToString());
        }

        public bool IsEven(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_EVEN(value.NativeHandle, out r));
            return (r != 0);
        }

        public bool IsOne(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ONE(value.NativeHandle, out r));
            return (r != 0);
        }

        public bool IsPowerOfTwo(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_POWER_OF_TWO(value.NativeHandle, out r));
            return (r != 0);
        }

        public bool IsZero(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ZERO(value.NativeHandle, out r));
            return (r != 0);
        }

        public Int32 GetHashCode(UBigIntHandle value)
        {
            Int32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GET_HASH_CODE(value.NativeHandle, out r));
            return (r);
        }

        public StatisticsInfo GetStatisticsInfo()
        {
            var buf = new PMC_STATISTICS_INFO();
            PMCCS_GetStatisticsInfo(buf);
            return (new StatisticsInfo(buf));
        }

        public UBigIntHandle From(UInt32 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_I(value, out r));
            return (new UBigIntHandle(r, this));
        }

        public UBigIntHandle From(UInt64 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_L(value, out r));
            return (new UBigIntHandle(r, this));
        }

        public void Dispose(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Dispose(value.NativeHandle));
        }

        public UBigIntHandle Zero
        {
            get
            {
                IntPtr r;
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((int)PMC_CONSTANT_CODE.PMC_CONSTANT_ZERO, out r));
                return (new UBigIntHandle(r, this));
            }
        }

        public UBigIntHandle One
        {
            get
            {
                IntPtr r;
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((int)PMC_CONSTANT_CODE.PMC_CONSTANT_ONE, out r));
                return (new UBigIntHandle(r, this));
            }
        }

        public UBigIntHandle FromByteArray(byte[] data)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FromByteArray(data, data.Length, out r));
            return (new UBigIntHandle(r, this));
        }

        public byte[] ToByteArray(UBigIntHandle value)
        {
            Int32 byte_array_count;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToByteArray(value.NativeHandle, IntPtr.Zero, 0, out byte_array_count));
            var temp_buf = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(byte)) * byte_array_count);
            try
            {
                Int32 r;
                HandleResultCode((PMC_STATUS_CODE)PMCCS_ToByteArray(value.NativeHandle, temp_buf, byte_array_count, out r));
                var result_array = new byte[byte_array_count];
                Marshal.Copy(temp_buf, result_array, 0, byte_array_count);
                return (result_array);
            }
            finally
            {
                Marshal.FreeCoTaskMem(temp_buf);
            }
        }

        public UBigIntHandle Clone(UBigIntHandle value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Clone_X(value.NativeHandle, out r));
            return (new UBigIntHandle(r, this));
        }

        public UInt64 GetAllocatedMemorySize()
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetAllocatedMemorySize(out r));
            return (r);
        }

        public UInt32 ToUInt32(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_To_X_I(value.NativeHandle, out r));
            return (r);
        }

        public UInt64 ToUInt64(UBigIntHandle value)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_To_X_L(value.NativeHandle, out r));
            return (r);
        }

        public string ToString(UBigIntHandle value, string format, NumberFormatInfo number_format_info)
        {
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info != null ? number_format_info : CultureInfo.CurrentCulture.NumberFormat);
            Int32 string_builder_capacity;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetStringCount(value.NativeHandle, format, native_number_format_info, IntPtr.Zero, 0, out string_builder_capacity));
            string_builder_capacity += 1; // 終端ヌル文字の分だけ増やす
            var temp_buf = new StringBuilder(string_builder_capacity);
            Int32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToString(value.NativeHandle, format, native_number_format_info, temp_buf, temp_buf.Capacity, out r));
            return (temp_buf.ToString());
        }

        public UBigIntHandle Parse(string source, NumberStyles number_style, NumberFormatInfo number_format_info)
        {
            var native_number_style = (int)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info != null ? number_format_info : CultureInfo.CurrentCulture.NumberFormat);
            IntPtr r_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Parse(source, native_number_style, native_number_format_info, out r_handle));
            return (new UBigIntHandle(r_handle, this));
        }

        public bool TryParse(string source, NumberStyles number_style, NumberFormatInfo number_format_info, out UBigIntHandle value)
        {
            var native_number_style = (int)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info != null ? number_format_info : CultureInfo.CurrentCulture.NumberFormat);
            UInt32 r_result;
            IntPtr value_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_TryParse(source, native_number_style, native_number_format_info, out value_handle, out r_result));
            if (r_result == 0)
            {
                value = null;
                return (false);
            }
            value =  new UBigIntHandle(value_handle, this);
            return (true);
        }

        public UBigIntHandle Add(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_I_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Add(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_L_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Add(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Add(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Add(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UInt32 Subtruct(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_I_X(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt64 Subtruct(UInt64 u, UBigIntHandle v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_L_X(u, v.NativeHandle, out w));
            return (w);
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Multiply(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_I_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Multiply(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_L_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Multiply(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Multiply(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Multiply(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UInt32 DivRem(UInt32 u, UBigIntHandle v, out UInt32 r)
        {
            UInt32 q;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_I_X(u, v.NativeHandle, out q, out r));
            return (q);
        }

        public UInt64 DivRem(UInt64 u, UBigIntHandle v, out UInt64 r)
        {
            UInt64 q;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_L_X(u, v.NativeHandle, out q, out r));
            return (q);
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UInt32 v, out UInt32 r)
        {
            IntPtr q_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_I(u.NativeHandle, v, out q_handle, out r));
            return (new UBigIntHandle(q_handle, this));
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UInt64 v, out UInt64 r)
        {
            IntPtr q_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_L(u.NativeHandle, v, out q_handle, out r));
            return (new UBigIntHandle(q_handle, this));
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UBigIntHandle v, out UBigIntHandle r)
        {
            IntPtr q_handle;
            IntPtr r_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_X(u.NativeHandle, v.NativeHandle, out q_handle, out r_handle));
            r = new UBigIntHandle(r_handle, this);
            return (new UBigIntHandle(q_handle, this));
        }

        public UInt32 Remainder(UInt32 u, UBigIntHandle v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_I_X(u, v.NativeHandle, out r));
            return (r);
        }

        public UInt64 Remainder(UInt64 u, UBigIntHandle v)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_L_X(u, v.NativeHandle, out r));
            return (r);
        }

        public UInt32 Remainder(UBigIntHandle u, UInt32 v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_I(u.NativeHandle, v, out r));
            return (r);
        }

        public UInt64 Remainder(UBigIntHandle u, UInt64 v)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_L(u.NativeHandle, v, out r));
            return (r);
        }

        public UBigIntHandle Remainder(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_X(u.NativeHandle, v.NativeHandle, out r));
            return (new UBigIntHandle(r, this));
        }

        public UBigIntHandle RightShift(UBigIntHandle x, Int32 n)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_X_I(x.NativeHandle, n, out r));
            return (new UBigIntHandle(r, this));
        }

        public UBigIntHandle LeftShift(UBigIntHandle x, Int32 n)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_X_I(x.NativeHandle, n, out r));
            return (new UBigIntHandle(r, this));
        }

        public UInt32 BitwiseAnd(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_I_X(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt64 BitwiseAnd(UInt64 u, UBigIntHandle v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_L_X(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt32 BitwiseAnd(UBigIntHandle u, UInt32 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_I(u.NativeHandle, v, out w));
            return (w);
        }

        public UInt64 BitwiseAnd(UBigIntHandle u, UInt64 v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_L(u.NativeHandle, v, out w));
            return (w);
        }

        public UBigIntHandle BitwiseAnd(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle BitwiseOr(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_I_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle BitwiseOr(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_L_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle ExclusiveOr(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_I_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle ExclusiveOr(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_L_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public Int32 Compare(UInt32 u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_I_X(u, v.NativeHandle, out w));
            return (w);
        }

        public Int32 Compare(UInt64 u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_L_X(u, v.NativeHandle, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UInt32 v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_I(u.NativeHandle, v, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UInt64 v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_L(u.NativeHandle, v, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (w);
        }

        public bool Equals(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_I_X(u, v.NativeHandle, out w));
            return (w != 0);
        }

        public bool Equals(UInt64 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_L_X(u, v.NativeHandle, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UInt32 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_I(u.NativeHandle, v, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UInt64 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_L(u.NativeHandle, v, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (w != 0);
        }

        public UBigIntHandle GreatestCommonDivisor(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_I_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle GreatestCommonDivisor(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_L_X(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_I(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_L(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_X(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w, this));
        }

        public UBigIntHandle Pow(UBigIntHandle x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_X_I(x.NativeHandle, n, out v));
            return (new UBigIntHandle(v, this));
        }

        public UBigIntHandle Pow(UBigIntHandle x, UInt64 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_X_L(x.NativeHandle, n, out v));
            return (new UBigIntHandle(v, this));
        }

        public UBigIntHandle ModPow(UBigIntHandle v, UBigIntHandle e, UBigIntHandle m)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ModPow_X_X_X(v.NativeHandle, e.NativeHandle, m.NativeHandle, out r));
            return (new UBigIntHandle(r, this));
        }

        public UBigIntHandle TimesPow(UInt32 v, UInt32 e)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_TimesOfExponentOf10(v, e, out r));
            return (new UBigIntHandle(r, this));
        }

        public UInt32 FloorLog10(UBigIntHandle v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Floor_Log10(v.NativeHandle, out r));
            return (r);
        }

        #endregion

        #region プライベートメソッド

        private static void HandleResultCode(PMC_STATUS_CODE result_code)
        {
            switch (result_code)
            {
                case PMC_STATUS_CODE. PMC_STATUS_OK:
                    return;
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_ERROR:
                    throw new ArgumentException();
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_NULL_ERROR:
                    throw new ArgumentNullException();
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR:
                    throw new ArgumentOutOfRangeException();
                case PMC_STATUS_CODE.PMC_STATUS_OVERFLOW:
                    throw new OverflowException();
                case PMC_STATUS_CODE.PMC_STATUS_DIVISION_BY_ZERO:
                    throw new DivideByZeroException();
                case PMC_STATUS_CODE.PMC_STATUS_ARITHMETIC_ERROR:
                    throw new ArithmeticException();
                case PMC_STATUS_CODE.PMC_STATUS_FORMAT_ERROR:
                    throw new FormatException();
                case PMC_STATUS_CODE.PMC_STATUS_INSUFFICIENT_BUFFER:
                    throw new InsufficientBufferException();
                case PMC_STATUS_CODE.PMC_STATUS_NOT_ENOUGH_MEMORY:
                    throw new InsufficientMemoryException();
                case PMC_STATUS_CODE.PMC_STATUS_NOT_SUPPORTED:
                    throw new NotSupportedException();
                case PMC_STATUS_CODE.PMC_STATUS_INTERNAL_ERROR:
                    throw new InternalErrorException();
                case PMC_STATUS_CODE.PMC_STATUS_BAD_BUFFER:
                    throw new BadBufferException();
                default:
                    throw new InternalErrorException(string.Format("未知の例外が発生しました。: code={0}", result_code));
            }
        }

        #endregion

        #region ネイティブ関数の宣言

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_UINT_Initialize(PMC_CONFIGURATION_INFO info);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern UInt32 PMCCS_GetConfigurationSettings(string key, StringBuilder value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_GetConfigurationSettings")]
        private static extern UInt32 PMCCS_GetConfigurationSettingCount(string key, IntPtr value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_EVEN(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_POWER_OF_TWO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ZERO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GET_HASH_CODE(IntPtr p, out Int32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern void PMCCS_GetStatisticsInfo([Out]PMC_STATISTICS_INFO p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_I(UInt32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_L(UInt64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Dispose(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetConstantValue_I(Int32 type, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_FromByteArray(byte[] buffer, int count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToByteArray(IntPtr p, IntPtr buffer, int buffer_size, out Int32 size);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Clone_X(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetAllocatedMemorySize(out UInt64 size);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_To_X_I(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_To_X_L(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_ToString(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, StringBuilder buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_ToString")]
        private static extern Int32 PMCCS_GetStringCount(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, IntPtr buffer, int buffer_size, out int size);

        /*
        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetStringCount(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, out int size);
        */

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_Parse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_TryParse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o, out UInt32 result);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_I_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_L_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_I_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_L_X(UInt64 u, IntPtr v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_I_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_L_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_I_X(UInt32 u, IntPtr v, out UInt32 q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_L_X(UInt64 u, IntPtr v, out UInt64 q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_X_I(IntPtr u, UInt32 v, out IntPtr q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_X_L(IntPtr u, UInt64 v, out IntPtr q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_X_X(IntPtr u, IntPtr v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_I_X(UInt32 u, IntPtr v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_L_X(UInt64 u, IntPtr v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_X_I(IntPtr u, UInt32 v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_X_L(IntPtr u, UInt64 v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_X_X(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_RightShift_X_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_I_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_L_X(UInt64 u, IntPtr v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_I(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_L(IntPtr u, UInt64 v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_I_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_L_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_I_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_L_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_I_X(UInt32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_L_X(UInt64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_X_I(IntPtr u, UInt32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_X_L(IntPtr u, UInt64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_X_X(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_Equals_I_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_Equals_L_X(UInt64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_Equals_X_I(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_Equals_X_L(IntPtr u, UInt64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_Equals_X_X(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_I_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_L_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_I(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_L(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_X_I(IntPtr x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_X_L(IntPtr x, UInt64 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ModPow_X_X_X(IntPtr v, IntPtr e, IntPtr m, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_TimesOfExponentOf10(UInt32 v, UInt32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Floor_Log10(IntPtr v, out UInt32 r);

        #endregion

    }
}


/*
 * END OF FILE
 */