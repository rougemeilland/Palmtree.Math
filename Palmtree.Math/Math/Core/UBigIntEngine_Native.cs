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
        private static extern Int32 PMCCS_CheckHandle_X(IntPtr p);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Clone_X(IntPtr x, out IntPtr o);

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
        private static extern Int32 PMCCS_Decrement_X(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Dispose_X(IntPtr p);

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
        private static extern Int32 PMCCS_Equals_I_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_L_X(UInt64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_X_I(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_X_L(IntPtr u, UInt64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Equals_X_X(IntPtr u, IntPtr v, out UInt32 w);

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
        private static extern Int32 PMCCS_Floor_Log10(IntPtr v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_FromByteArray(byte[] buffer, int count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_I(UInt32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_From_L(UInt64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GET_HASH_CODE(IntPtr p, out Int32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetAllocatedMemorySize(out UInt64 size);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_GetConfigurationSettings")]
        private static extern Int32 PMCCS_GetConfigurationSettingCount(string key, IntPtr value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetConfigurationSettings(string key, StringBuilder value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_GetConstantValue_I(Int32 type, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern void PMCCS_GetStatisticsInfo([Out]PMC_STATISTICS_INFO p);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_ToString")]
        private static extern Int32 PMCCS_GetStringCount(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, IntPtr buffer, int buffer_size, out int size);

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
        private static extern Int32 PMCCS_IS_EVEN(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_POWER_OF_TWO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_IS_ZERO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Increment_X(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ModPow_X_X_X(IntPtr v, IntPtr e, IntPtr m, out IntPtr r);

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

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_Parse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_X_I(IntPtr x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_Pow_X_L(IntPtr x, UInt64 n, out IntPtr v);

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
        private static extern Int32 PMCCS_TimesOfExponentOf10(UInt32 v, UInt32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_ToByteArray(IntPtr p, IntPtr buffer, int buffer_size, out Int32 size);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_To_X_I(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern Int32 PMCCS_To_X_L(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_ToString(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, StringBuilder buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Uint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_TryParse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Uint.dll")]
        private static extern UInt32 PMCCS_UINT_Initialize();

        #endregion
    }
}


/*
 * END OF FILE
 */