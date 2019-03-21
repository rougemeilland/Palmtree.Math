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
using System.Globalization;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace Palmtree.Math.Core
{

    partial class UBigIntEngine
    {
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

        public void CheckHandle(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_CheckHandle_X(value.NativeHandle));
        }

        public void Dispose(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Dispose_X(value.NativeHandle));
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
            IntPtr value_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_TryParse(source, native_number_style, native_number_format_info, out value_handle));
            if (value_handle == IntPtr.Zero)
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

        public UBigIntHandle Increment(UBigIntHandle x)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Increment_X(x.NativeHandle, out r));
            return (new UBigIntHandle(r, this));
        }

        public UBigIntHandle Decrement(UBigIntHandle x)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Decrement_X(x.NativeHandle, out r));
            return (new UBigIntHandle(r, this));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */