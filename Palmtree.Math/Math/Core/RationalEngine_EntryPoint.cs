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

    partial class RationalEngine
    {
        #region パブリックメソッド

        #region Abs 関数

        public RationalHandle Abs(RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Abs_R(v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region Add 関数

        public RationalHandle Add(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_I_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_L_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UI_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UL_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_I(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_L(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_UI(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_UL(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Add(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_R_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region Ceiling 関数

        public BigIntHandle Ceiling(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Ceiling_R(value.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region Clone 関数

        public RationalHandle Clone(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Clone_R(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        #endregion

        #region Compare 関数

        public Int32 Compare(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_I_R(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_L_R(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_R(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UI_R(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UL_R(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_R(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_I(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_L(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_X(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_UI(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_UL(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_UX(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_R_R(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        #endregion

        #region Divide 関数

        public RationalHandle Divide(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_I_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_L_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_X_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_UI_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_UL_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_UX_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_I(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_L(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_UI(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_UL(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Divide(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Divide_R_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region Equals 関数

        public bool Equals(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_I_R(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_L_R(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_R(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UI_R(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UL_R(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_R(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_I(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_L(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_X(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_UI(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_UL(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_UX(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_R_R(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        #endregion

        #region Floor 関数

        public BigIntHandle Floor(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Floor_R(value.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region FloorLog10 関数

        public Int32 FloorLog10(RationalHandle v)
        {
            Int32 r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FloorLog10_R(v.NativeHandle, out r));
            return (r);
        }

        #endregion

        #region FromByteArray 関数

        public RationalHandle FromByteArray(byte[] data)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FromByteArray(data, data.Length, out IntPtr r));
            return (new RationalHandle(r));
        }

        #endregion

        #region From 関数

        public RationalHandle From(decimal value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_DECIMAL(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(double value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_DOUBLE(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(Int32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_I(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(Int64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_L(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_X(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(UInt32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UI(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(UInt64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UL(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle From(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UX(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        #endregion

        #region GetAllocatedMemorySize 関数

        public UInt64 GetAllocatedMemorySize()
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetAllocatedMemorySize(out UInt64 r));
            return (r);
        }

        #endregion

        #region GetConfigurationSettings 関数

        public string GetConfigurationSettings(string key)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConfigurationSettingCount(key, IntPtr.Zero, 0, out Int32 needed_capacity));
            var value_buffer = new StringBuilder(needed_capacity);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConfigurationSettings(key, value_buffer, value_buffer.Capacity, out needed_capacity));
            return (value_buffer.ToString());
        }

        #endregion

        #region 定数

        public IntPtr DefaultValueHandle
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_ZERO, out IntPtr r));
                return (r);
            }
        }

        public RationalHandle Zero
        {
            get
            {
                return (new RationalHandle(DefaultValueHandle));
            }
        }

        public RationalHandle MinusOne
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_MINUS_ONE, out IntPtr r));
                return (new RationalHandle(r));
            }
        }

        public RationalHandle One
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_ONE, out IntPtr r));
                return (new RationalHandle(r));
            }
        }

        #endregion

        #region GetHashCode 関数

        public Int32 GetHashCode(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetHashCode_R(value.NativeHandle, out Int32 r));
            return (r);
        }

        #endregion

        #region GetPerformanceCounter 関数

        public Int64 GetPerformanceCounter(string key)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetPerformanceCounter(key, out Int64 w));
            return (w);
        }

        #endregion

        #region 検査関数

        public bool IsInteger(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_INT(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsMinusOne(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_MINUS_ONE(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsOne(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ONE(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsZero(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ZERO(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        #endregion

        #region Invert 関数

        public RationalHandle Invert(Int32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_I(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(Int64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_L(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_X(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(UInt32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_UI(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(UInt64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_UL(value, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_UX(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        public RationalHandle Invert(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Invert_R(value.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        #endregion

        #region Multiply 関数

        public RationalHandle Multiply(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_I_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_L_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UI_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UL_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_I(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_L(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_UI(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_UL(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Multiply(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_R_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region Negate 関数

        public RationalHandle Negate(RationalHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Negate_R(x.NativeHandle, out IntPtr r));
            return (new RationalHandle(r));
        }

        #endregion

        #region Parse 関数

        public RationalHandle Parse(string source, NumberStyles number_style, NumberFormatInfo number_format_info)
        {
            var native_number_style = (Int32)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Parse(source, native_number_style, native_number_format_info, out IntPtr r_handle));
            return (new RationalHandle(r_handle));
        }

        #endregion

        #region Power 関数

        public RationalHandle Pow(Int32 x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_I_I(x, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(Int64 x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_L_I(x, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(BigIntHandle x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_X_I(x.NativeHandle, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(UInt32 x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UI_I(x, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(UInt64 x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UL_I(x, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(UBigIntHandle x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_UX_I(x.NativeHandle, n, out v));
            return (new RationalHandle(v));
        }

        public RationalHandle Pow(RationalHandle x, Int32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_R_I(x.NativeHandle, n, out v));
            return (new RationalHandle(v));
        }

        #endregion

        #region Round 関数

        public BigIntHandle Round(RationalHandle u, MidpointRounding mode)
        {
            var native_mode = (Int32)mode;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Round_R(u.NativeHandle, native_mode, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Round(RationalHandle u, RoundingMode mode)
        {
            var native_mode = (Int32)mode;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Round_R(u.NativeHandle, native_mode, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public RationalHandle Round(RationalHandle u, Int32 decimals, MidpointRounding mode)
        {
            var native_mode = (Int32)mode;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Round_R_I(u.NativeHandle, decimals, native_mode, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Round(RationalHandle u, int decimals, RoundingMode mode)
        {
            var native_mode = (Int32)mode;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Round_R_I(u.NativeHandle, decimals, native_mode, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region Subtruct 関数

        public RationalHandle Subtruct(Int32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_I_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(Int64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_L_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(BigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(UInt32 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UI_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(UInt64 u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UL_R(u, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(UBigIntHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_I(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_L(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_UI(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_UL(u.NativeHandle, v, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        public RationalHandle Subtruct(RationalHandle u, RationalHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_R_R(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new RationalHandle(w));
        }

        #endregion

        #region ToByteArray 関数

        public byte[] ToByteArray(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToByteArray(value.NativeHandle, IntPtr.Zero, 0, out Int32 byte_array_count));
            var temp_buf = Marshal.AllocCoTaskMem(Marshal.SizeOf(typeof(byte)) * byte_array_count);
            try
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_ToByteArray(value.NativeHandle, temp_buf, byte_array_count, out Int32 r));
                var result_array = new byte[byte_array_count];
                Marshal.Copy(temp_buf, result_array, 0, byte_array_count);
                return (result_array);
            }
            finally
            {
                Marshal.FreeCoTaskMem(temp_buf);
            }
        }

        #endregion

        #region ToString 関数

        public string ToString(RationalHandle value, string format, NumberFormatInfo number_format_info)
        {
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetStringCount_R(value.NativeHandle, format, native_number_format_info, IntPtr.Zero, 0, out Int32 string_builder_capacity));
            string_builder_capacity += 1; // 終端ヌル文字の分だけ増やす
            var temp_buf = new StringBuilder(string_builder_capacity);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToString_R(value.NativeHandle, format, native_number_format_info, temp_buf, temp_buf.Capacity, out Int32 r));
            return (temp_buf.ToString());
        }

        #endregion

        #region To 関数

        public decimal ToDecimal(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToDecimal_R(value.NativeHandle, out decimal r));
            return (r);
        }

        public double ToDouble(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToDouble_R(value.NativeHandle, out double r));
            return (r);
        }

        public Int32 ToInt32(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt32_R(value.NativeHandle, out Int32 r));
            return (r);
        }

        public Int64 ToInt64(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt64_R(value.NativeHandle, out Int64 r));
            return (r);
        }

        public BigIntHandle ToBigInt(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToBigInt_R(value.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public UInt32 ToUInt32(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt32_R(value.NativeHandle, out UInt32 r));
            return (r);
        }

        public UInt64 ToUInt64(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt64_R(value.NativeHandle, out UInt64 r));
            return (r);
        }

        public UBigIntHandle ToUBigInt(RationalHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUBigInt_R(value.NativeHandle, out IntPtr r));
            return (new UBigIntHandle(r));
        }

        #endregion

        #region TryParse 関数

        public bool TryParse(string source, NumberStyles number_style, NumberFormatInfo number_format_info, out RationalHandle value)
        {
            var native_number_style = (Int32)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_TryParse(source, native_number_style, native_number_format_info, out IntPtr value_handle));
            if (value_handle == IntPtr.Zero)
            {
                value = null;
                return (false);
            }
            value = new RationalHandle(value_handle);
            return (true);
        }

        #endregion

        #region GenerateRationalRandomValue 関数

        public RationalHandle GenerateRationalRandomValue(RandomStateObjectHandle x, UInt32 bit_count)
        {
            IntPtr r;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GenerateRationalRandomValue(x.NativeHandle, bit_count, out r));
            return (new RationalHandle(r));
        }

        #endregion

        #endregion
    }
}


/*
 * END OF FILE
 */