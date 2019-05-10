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
using System.Runtime.InteropServices;
using System.Text;

namespace Palmtree.Math.Core
{
    partial class UBigIntEngine
    {
        #region ネイティブ関数の宣言

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Add_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UI_UX(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UL_UX(UInt64 u, IntPtr v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_UI(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_UL(IntPtr u, UInt64 v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_CheckHandle_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Clone_UX(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_UI_UX(UInt32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_UL_UX(UInt64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_UX_UI(IntPtr u, UInt32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_UX_UL(IntPtr u, UInt64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Compare_UX_UX(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Decrement_UX(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Dispose_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UI_UX(UInt32 u, IntPtr v, out UInt32 q);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UL_UX(UInt64 u, IntPtr v, out UInt64 q);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_UI(IntPtr u, UInt32 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_UL(IntPtr u, UInt64 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_UX(IntPtr u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_UI_UX(UInt32 u, IntPtr v, out UInt32 q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_UL_UX(UInt64 u, IntPtr v, out UInt64 q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_UI(IntPtr u, UInt32 v, out IntPtr q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_UL(IntPtr u, UInt64 v, out IntPtr q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_UX(IntPtr u, IntPtr v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_UI_UX(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_UL_UX(UInt64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_UX_UI(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_UX_UL(IntPtr u, UInt64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_UX_UX(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_FloorLog10_UX(IntPtr v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_FromByteArray(byte[] buffer, int count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_I(Int32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_L(Int64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_UI(UInt32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_UL(UInt64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GET_HASH_CODE(IntPtr p, out Int32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_GetConfigurationSettings")]
        private static extern Int32 PMCCS_GetConfigurationSettingCount(string key, IntPtr value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetConfigurationSettings(string key, StringBuilder value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetConstantValue_I(Int32 type, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetDefaultRoundingMode(out Int32 value);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetPerformanceCounter(string key, out Int64 value);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_ToString_UX")]
        private static extern Int32 PMCCS_GetStringCount_UX(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, IntPtr buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_EVEN(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_POWER_OF_TWO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ZERO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Increment_UX(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_LeftShift_UX_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ModPow_UX_UX_UX(IntPtr v, IntPtr e, IntPtr m, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Multiply_I_UX_UX(Int32 method, IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_Parse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_UI_UI(UInt32 x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_UL_UI(UInt64 x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_UX_UI(IntPtr x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_UI_UX(UInt32 u, IntPtr v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_UL_UX(UInt64 u, IntPtr v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_UI(IntPtr u, UInt32 v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_UL(IntPtr u, UInt64 v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_UX(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_RightShift_UX_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_SetDefaultRoundingMode(Int32 mode);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_UI_UX(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_UL_UX(UInt64 u, IntPtr v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToByteArray(IntPtr p, IntPtr buffer, int buffer_size, out Int32 size);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToInt32_UX(IntPtr p, out Int32 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToInt64_UX(IntPtr p, out Int64 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToUInt32_UX(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToUInt64_UX(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_ToString_UX(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, StringBuilder buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_TryParse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_UINT_Initialize();

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_AllocateRandomStateObjectFromUInt32(UInt32 seed, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_AllocateRandomStateObjectFromUInt32Array(UInt32[] init_key, Int32 key_length, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_CheckHandle_SFMT(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Dispose_SFMT(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GenerateUInt32RandomValue(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GenerateUInt64RandomValue(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GenerateDoubleRandomValue(IntPtr p, out double o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GenerateUBigIntRandomValue(IntPtr handle, Int32 bit_count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_GenerateUBigIntCryptoRandomValue(byte[] data, Int32 bit_count, out IntPtr value);

        #endregion
    }
}


/*
 * END OF FILE
 */