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
    partial class RationalEngine
    {
        #region ネイティブ関数の宣言

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Abs_R(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_I_R(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_L_R(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_R_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_UI_R(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_UL_R(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_UX_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Add_X_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Ceiling_R(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_CheckHandle_R(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_CheckHandle_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_CheckHandle_X(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Clone_R(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_I_R(Int32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_L_R(Int64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_I(IntPtr u, Int32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_L(IntPtr u, Int64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_R(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_UI(IntPtr u, UInt32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_UL(IntPtr u, UInt64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_UX(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_R_X(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_UI_R(UInt32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_UL_R(UInt64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_UX_R(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Compare_X_R(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Dispose_R(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Dispose_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Dispose_X(IntPtr p);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_I_R(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_L_R(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_R_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_UI_R(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_UL_R(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_UX_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Divide_X_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_I_R(Int32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_L_R(Int64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_I(IntPtr u, Int32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_L(IntPtr u, Int64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_R(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_UI(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_UL(IntPtr u, UInt64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_UX(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_R_X(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_UI_R(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_UL_R(UInt64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_UX_R(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Equals_X_R(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_FloorLog10_R(IntPtr v, out Int32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Floor_R(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_FromByteArray(byte[] buffer, int count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_I(Int32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_L(Int64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_UI(UInt32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_UL(UInt64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_UX(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_From_X(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_GetAllocatedMemorySize(out UInt64 size);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetConfigurationSettings(string key, StringBuilder value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_GetConfigurationSettings")]
        private static extern Int32 PMCCS_GetConfigurationSettingCount(string key, IntPtr value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_GetConstantValue_I(Int32 type, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_GetHashCode_R(IntPtr p, out Int32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetPerformanceCounter(string key, out Int64 value);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_IS_INT(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_IS_MINUS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_IS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_IS_ZERO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_I(Int32 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_L(Int64 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_R(IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_UI(UInt32 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_UL(UInt64 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_UX(IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Invert_X(IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_I_R(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_L_R(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_R_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_UI_R(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_UL_R(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_UX_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Multiply_X_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Negate_R(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_Parse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_I_I(Int32 v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_L_I(Int64 v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_R_I(IntPtr v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_UI_I(UInt32 v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_UL_I(UInt64 v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_UX_I(IntPtr v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Pow_X_I(IntPtr v, Int32 e, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Round_R(IntPtr x, Int32 mode, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Round_R_I(IntPtr x, Int32 decimals, Int32 mode, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_I_R(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_L_R(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_R_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_UI_R(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_UL_R(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_Subtruct_X_R(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToBigInt_R(IntPtr p, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToByteArray(IntPtr p, IntPtr buffer, int buffer_size, out Int32 size);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToInt32_R(IntPtr p, out Int32 o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToInt64_R(IntPtr p, out Int64 o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_ToString_R(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, StringBuilder buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_ToString_R")]
        private static extern Int32 PMCCS_GetStringCount_R(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, IntPtr buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToUBigInt_R(IntPtr p, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToUInt32_R(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern Int32 PMCCS_ToUInt64_R(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_TryParse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Rtnl.dll")]
        private static extern UInt32 PMCCS_RTNL_Initialize();


        #endregion
    }
}


/*
 * END OF FILE
 */
