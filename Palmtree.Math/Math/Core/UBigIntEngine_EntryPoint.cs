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

        public Int64 GetPerformanceCounter(string key)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetPerformanceCounter(key, out Int64 w));
            return (w);
        }

        public UBigIntHandle From(Int32 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_I(value, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle From(Int64 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_L(value, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle From(UInt32 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UI(value, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle From(UInt64 value)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UL(value, out r));
            return (new UBigIntHandle(r));
        }

        public void CheckHandle(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_CheckHandle_UX(value.NativeHandle));
        }

        public IntPtr DefaultValueHandle
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_ZERO, out IntPtr r));
                return (r);
            }
        }

        public UBigIntHandle Zero
        {
            get
            {
                return (new UBigIntHandle(DefaultValueHandle));
            }
        }

        public UBigIntHandle One
        {
            get
            {
                IntPtr r;
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((int)PMC_CONSTANT_CODE.PMC_CONSTANT_ONE, out r));
                return (new UBigIntHandle(r));
            }
        }

        public RoundingMode DefaultRoundingMode
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetDefaultRoundingMode(out Int32 mode));
                return ((RoundingMode)mode);
            }

            set
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_SetDefaultRoundingMode((int)value));
            }
        }

        public UBigIntHandle FromByteArray(byte[] data)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FromByteArray(data, data.Length, out r));
            return (new UBigIntHandle(r));
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
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Clone_UX(value.NativeHandle, out r));
            return (new UBigIntHandle(r));
        }

        public Int32 ToInt32(UBigIntHandle value)
        {
            Int32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt32_UX(value.NativeHandle, out r));
            return (r);
        }

        public Int64 ToInt64(UBigIntHandle value)
        {
            Int64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt64_UX(value.NativeHandle, out r));
            return (r);
        }

        public UInt32 ToUInt32(UBigIntHandle value)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt32_UX(value.NativeHandle, out r));
            return (r);
        }

        public UInt64 ToUInt64(UBigIntHandle value)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt64_UX(value.NativeHandle, out r));
            return (r);
        }

        public string ToString(UBigIntHandle value, string format, NumberFormatInfo number_format_info)
        {
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info != null ? number_format_info : CultureInfo.CurrentCulture.NumberFormat);
            Int32 string_builder_capacity;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetStringCount_UX(value.NativeHandle, format, native_number_format_info, IntPtr.Zero, 0, out string_builder_capacity));
            string_builder_capacity += 1; // 終端ヌル文字の分だけ増やす
            var temp_buf = new StringBuilder(string_builder_capacity);
            Int32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToString_UX(value.NativeHandle, format, native_number_format_info, temp_buf, temp_buf.Capacity, out r));
            return (temp_buf.ToString());
        }

        public UBigIntHandle Parse(string source, NumberStyles number_style, NumberFormatInfo number_format_info)
        {
            var native_number_style = (int)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info != null ? number_format_info : CultureInfo.CurrentCulture.NumberFormat);
            IntPtr r_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Parse(source, native_number_style, native_number_format_info, out r_handle));
            return (new UBigIntHandle(r_handle));
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
            value =  new UBigIntHandle(value_handle);
            return (true);
        }

        public UBigIntHandle Add(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UI_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Add(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UL_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Add(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Add(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Add(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UInt32 Subtruct(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UI_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt64 Subtruct(UInt64 u, UBigIntHandle v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UL_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Subtruct(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Multiply(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UI_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Multiply(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UL_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Multiply(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Multiply(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Multiply(MultiplicationMethod method, UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_I_UX_UX((Int32)method, u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UInt32 DivRem(UInt32 u, UBigIntHandle v, out UInt32 r)
        {
            UInt32 q;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UI_UX(u, v.NativeHandle, out q, out r));
            return (q);
        }

        public UInt64 DivRem(UInt64 u, UBigIntHandle v, out UInt64 r)
        {
            UInt64 q;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UL_UX(u, v.NativeHandle, out q, out r));
            return (q);
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UInt32 v, out UInt32 r)
        {
            IntPtr q_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_UI(u.NativeHandle, v, out q_handle, out r));
            return (new UBigIntHandle(q_handle));
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UInt64 v, out UInt64 r)
        {
            IntPtr q_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_UL(u.NativeHandle, v, out q_handle, out r));
            return (new UBigIntHandle(q_handle));
        }

        public UBigIntHandle DivRem(UBigIntHandle u, UBigIntHandle v, out UBigIntHandle r)
        {
            IntPtr q_handle;
            IntPtr r_handle;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_UX(u.NativeHandle, v.NativeHandle, out q_handle, out r_handle));
            r = new UBigIntHandle(r_handle);
            return (new UBigIntHandle(q_handle));
        }

        public UInt32 Remainder(UInt32 u, UBigIntHandle v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UI_UX(u, v.NativeHandle, out r));
            return (r);
        }

        public UInt64 Remainder(UInt64 u, UBigIntHandle v)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UL_UX(u, v.NativeHandle, out r));
            return (r);
        }

        public UInt32 Remainder(UBigIntHandle u, UInt32 v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_UI(u.NativeHandle, v, out r));
            return (r);
        }

        public UInt64 Remainder(UBigIntHandle u, UInt64 v)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_UL(u.NativeHandle, v, out r));
            return (r);
        }

        public UBigIntHandle Remainder(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_UX(u.NativeHandle, v.NativeHandle, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle RightShift(UBigIntHandle x, Int32 n)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_UX_I(x.NativeHandle, n, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle LeftShift(UBigIntHandle x, Int32 n)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_UX_I(x.NativeHandle, n, out r));
            return (new UBigIntHandle(r));
        }

        public UInt32 BitwiseAnd(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UI_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt64 BitwiseAnd(UInt64 u, UBigIntHandle v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UL_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public UInt32 BitwiseAnd(UBigIntHandle u, UInt32 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_UI(u.NativeHandle, v, out w));
            return (w);
        }

        public UInt64 BitwiseAnd(UBigIntHandle u, UInt64 v)
        {
            UInt64 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_UL(u.NativeHandle, v, out w));
            return (w);
        }

        public UBigIntHandle BitwiseAnd(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseOr(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UI_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseOr(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UL_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseOr(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle ExclusiveOr(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UI_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle ExclusiveOr(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UL_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle ExclusiveOr(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public Int32 Compare(UInt32 u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UI_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public Int32 Compare(UInt64 u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UL_UX(u, v.NativeHandle, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UInt32 v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_UI(u.NativeHandle, v, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UInt64 v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_UL(u.NativeHandle, v, out w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, UBigIntHandle v)
        {
            Int32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (w);
        }

        public bool Equals(UInt32 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UI_UX(u, v.NativeHandle, out w));
            return (w != 0);
        }

        public bool Equals(UInt64 u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UL_UX(u, v.NativeHandle, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UInt32 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_UI(u.NativeHandle, v, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UInt64 v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_UL(u.NativeHandle, v, out w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, UBigIntHandle v)
        {
            UInt32 w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (w != 0);
        }

        public UBigIntHandle GreatestCommonDivisor(UInt32 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UI_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UInt64 u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UL_UX(u, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UInt32 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_UI(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UInt64 v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_UL(u.NativeHandle, v, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, UBigIntHandle v)
        {
            IntPtr w;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_UX(u.NativeHandle, v.NativeHandle, out w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Pow(UInt32 x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UI_UI(x, n, out v));
            return (new UBigIntHandle(v));
        }

        public UBigIntHandle Pow(UInt64 x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UL_UI(x, n, out v));
            return (new UBigIntHandle(v));
        }

        public UBigIntHandle Pow(UBigIntHandle x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UX_UI(x.NativeHandle, n, out v));
            return (new UBigIntHandle(v));
        }

        public UBigIntHandle ModPow(UBigIntHandle v, UBigIntHandle e, UBigIntHandle m)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ModPow_UX_UX_UX(v.NativeHandle, e.NativeHandle, m.NativeHandle, out r));
            return (new UBigIntHandle(r));
        }

        public UInt32 FloorLog10(UBigIntHandle v)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FloorLog10_UX(v.NativeHandle, out r));
            return (r);
        }

        public UBigIntHandle Increment(UBigIntHandle x)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Increment_UX(x.NativeHandle, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle Decrement(UBigIntHandle x)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Decrement_UX(x.NativeHandle, out r));
            return (new UBigIntHandle(r));
        }

        public RandomStateObjectHandle AllocateRandomStateObject(UInt32 x)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_AllocateRandomStateObjectFromUInt32(x, out r));
            return (new RandomStateObjectHandle(r));
        }

        public RandomStateObjectHandle AllocateRandomStateObject(UInt32[] init_key)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_AllocateRandomStateObjectFromUInt32Array(init_key, init_key.Length, out r));
            return (new RandomStateObjectHandle(r));
        }

        public UInt32 GenerateUInt32RandomValue(RandomStateObjectHandle x)
        {
            UInt32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateUInt32RandomValue(x.NativeHandle, out r));
            return (r);
        }

        public UInt64 GenerateUInt64RandomValue(RandomStateObjectHandle x)
        {
            UInt64 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateUInt64RandomValue(x.NativeHandle, out r));
            return (r);
        }

        public double GenerateDoubleRandomValue(RandomStateObjectHandle x)
        {
            double r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateDoubleRandomValue(x.NativeHandle, out r));
            return (r);
        }

        public UBigIntHandle GenerateUBigIntRandomValue(RandomStateObjectHandle x, Int32 bit_count)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateUBigIntRandomValue(x.NativeHandle, bit_count, out r));
            return (new UBigIntHandle(r));
        }

        public UBigIntHandle GenerateUBigIntCryptoRandomValue(byte[] data, Int32 bit_count)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateUBigIntCryptoRandomValue(data, bit_count, out r));
            return (new UBigIntHandle(r));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */