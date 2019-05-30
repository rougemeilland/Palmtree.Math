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
    partial class BigIntEngine
    {
        #region ネイティブ関数の宣言

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Abs_X(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Add_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UI_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UL_X(UInt64 u, IntPtr v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_UI(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_UL(IntPtr u, UInt64 v, out UInt64 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseAnd_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_BitwiseOr_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_CheckHandle_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_CheckHandle_X(IntPtr p);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Clone_X(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_I_UX(Int32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_I_X(Int32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_L_UX(Int64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_L_X(Int64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_UI_X(UInt32 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_UL_X(UInt64 u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_UX_I(IntPtr u, Int32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_UX_L(IntPtr u, Int64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_UX_X(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_I(IntPtr u, Int32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_L(IntPtr u, Int64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_UI(IntPtr u, UInt32 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_UL(IntPtr u, UInt64 v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_UX(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Compare_X_X(IntPtr u, IntPtr v, out Int32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Decrement_X(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Dispose_UX(IntPtr p);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Dispose_X(IntPtr p);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_I_UX(Int32 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_I_X(Int32 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_L_UX(Int64 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_L_X(Int64 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UI_X(UInt32 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UL_X(UInt64 u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_I(IntPtr u, Int32 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_L(IntPtr u, Int64 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_UX_X(IntPtr u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_I(IntPtr u, Int32 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_L(IntPtr u, Int64 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_UI(IntPtr u, UInt32 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_UL(IntPtr u, UInt64 v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_UX(IntPtr u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivideExactly_X_X(IntPtr u, IntPtr v, out IntPtr q);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_I_UX(Int32 u, IntPtr v, out IntPtr q, out Int32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_I_X(Int32 u, IntPtr v, out IntPtr q, out Int32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_L_UX(Int64 u, IntPtr v, out IntPtr q, out Int64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_L_X(Int64 u, IntPtr v, out IntPtr q, out Int64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_UI_X(UInt32 u, IntPtr v, out IntPtr q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_UL_X(UInt64 u, IntPtr v, out IntPtr q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_I(IntPtr u, Int32 v, out IntPtr q, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_L(IntPtr u, Int64 v, out IntPtr q, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_UX_X(IntPtr u, IntPtr v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_I(IntPtr u, Int32 v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_L(IntPtr u, Int64 v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_UI(IntPtr u, UInt32 v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_UL(IntPtr u, UInt64 v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_UX(IntPtr u, IntPtr v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_DivRem_X_X(IntPtr u, IntPtr v, out IntPtr q, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_I_UX(Int32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_I_X(Int32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_L_UX(Int64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_L_X(Int64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_UI_X(UInt32 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_UL_X(UInt64 u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_UX_I(IntPtr u, Int32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_UX_L(IntPtr u, Int64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_UX_X(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_I(IntPtr u, Int32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_L(IntPtr u, Int64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_UI(IntPtr u, UInt32 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_UL(IntPtr u, UInt64 v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_UX(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Equals_X_X(IntPtr u, IntPtr v, out UInt32 w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ExclusiveOr_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_From_I(Int32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_From_L(Int64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_From_UI(UInt32 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_From_UL(UInt64 x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_From_UX(IntPtr x, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_FromByteArray(byte[] buffer, int count, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GetConstantValue_I(Int32 type, out IntPtr value);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GetHashCode_X(IntPtr p, out Int32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetPerformanceCounter(string key, out Int64 value);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_GreatestCommonDivisor_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Increment_X(IntPtr x, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_IS_EVEN(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_IS_MINUS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_IS_ONE(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_IS_POWER_OF_TWO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_IS_ZERO(IntPtr p, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_UI(IntPtr p, UInt32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_L(IntPtr p, Int64 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_LeftShift_X_UL(IntPtr p, UInt64 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Modulo_I_UX(Int32 u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Modulo_L_UX(Int64 u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Modulo_X_UI(IntPtr u, UInt32 v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Modulo_X_UL(IntPtr u, UInt64 v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Modulo_X_UX(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Multiply_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Negate_UX(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Negate_X(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_OneComplement_UX(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_OneComplement_X(IntPtr u, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Pow_I_UI(Int32 x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Pow_L_UI(Int64 x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Pow_X_UI(IntPtr x, UInt32 n, out IntPtr v);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_I_UX(Int32 u, IntPtr v, out Int32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_I_X(Int32 u, IntPtr v, out Int32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_L_UX(Int64 u, IntPtr v, out Int64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_L_X(Int64 u, IntPtr v, out Int64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_UI_X(UInt32 u, IntPtr v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_UL_X(UInt64 u, IntPtr v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_I(IntPtr u, Int32 v, out UInt32 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_L(IntPtr u, Int64 v, out UInt64 r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_UX_X(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_I(IntPtr u, Int32 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_L(IntPtr u, Int64 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_UI(IntPtr u, UInt32 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_UL(IntPtr u, UInt64 v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_UX(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Remainder_X_X(IntPtr u, IntPtr v, out IntPtr r);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_RightShift_X_I(IntPtr p, Int32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_RightShift_X_UI(IntPtr p, UInt32 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_RightShift_X_L(IntPtr p, Int64 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_RightShift_X_UL(IntPtr p, UInt64 n, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_I_UX(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_I_X(Int32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_L_UX(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_L_X(Int64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UI_X(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UI_UX(UInt32 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UL_X(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UL_UX(UInt64 u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_UX_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_I(IntPtr u, Int32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_L(IntPtr u, Int64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_UI(IntPtr u, UInt32 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_UL(IntPtr u, UInt64 v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_UX(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_Subtruct_X_X(IntPtr u, IntPtr v, out IntPtr w);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToInt32_X(IntPtr p, out Int32 o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToInt64_X(IntPtr p, out Int64 o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToUInt32_X(IntPtr p, out UInt32 o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToUInt64_X(IntPtr p, out UInt64 o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToUBigInt_X(IntPtr p, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern Int32 PMCCS_ToByteArray(IntPtr p, IntPtr buffer, int buffer_size, out Int32 size);

        [DllImport("Palmtree.Math.Core.Sint.dll")]
        private static extern UInt32 PMCCS_SINT_Initialize();

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_GetConfigurationSettings(string key, StringBuilder value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_Parse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_ToString_X(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, StringBuilder buffer, int buffer_size, out int size);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode)]
        private static extern Int32 PMCCS_TryParse(string source, int number_styles, [In]PMC_NUMBER_FORMAT_INFO format_option, out IntPtr o);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_GetConfigurationSettings")]
        private static extern Int32 PMCCS_GetConfigurationSettingCount(string key, IntPtr value_buffer, int value_buffer_size, out Int32 count);

        [DllImport("Palmtree.Math.Core.Sint.dll", CharSet = CharSet.Unicode, EntryPoint = "PMCCS_ToString_X")]
        private static extern Int32 PMCCS_GetStringCount_X(IntPtr x, string format, [In]PMC_NUMBER_FORMAT_INFO format_option, IntPtr buffer, int buffer_size, out int size);

        #endregion
    }
}


/*
 * END OF FILE
 */