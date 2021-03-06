﻿/*
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

    partial class BigIntEngine
    {
        #region パブリックメソッド

        #region Abs 関数

        public UBigIntHandle Abs(BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Abs_X(v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        #endregion

        #region Add 関数

        public BigIntHandle Add(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Add(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Add_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        #endregion

        #region BitwiseAnd 関数

        public BigIntHandle BitwiseAnd(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseAnd(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public UInt32 BitwiseAnd(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UI_X(u, v.NativeHandle, out UInt32 w));
            return (w);
        }

        public UInt64 BitwiseAnd(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UL_X(u, v.NativeHandle, out UInt64 w));
            return (w);
        }

        public UBigIntHandle BitwiseAnd(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public BigIntHandle BitwiseAnd(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseAnd(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public UInt32 BitwiseAnd(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_UI(u.NativeHandle, v, out UInt32 w));
            return (w);
        }

        public UInt64 BitwiseAnd(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_UL(u.NativeHandle, v, out UInt64 w));
            return (w);
        }

        public UBigIntHandle BitwiseAnd(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public BigIntHandle BitwiseAnd(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public UBigIntHandle BitwiseAnd(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseAnd(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseAnd(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle BitwiseAnd(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseAnd_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        #endregion

        #region BitwiseOr 関数

        public BigIntHandle BitwiseOr(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle BitwiseOr(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_BitwiseOr_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        #endregion

        #region Clone 関数

        public BigIntHandle Clone(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Clone_X(value.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region Compare 関数

        public Int32 Compare(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_I_X(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_L_X(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UI_X(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UL_X(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_X(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_I(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_L(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_UI(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_UL(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_UX(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_X_X(u.NativeHandle, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_I_UX(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_L_UX(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_I(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        public Int32 Compare(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Compare_UX_L(u.NativeHandle, v, out Int32 w));
            return (w);
        }

        #endregion

        #region Decrement 関数

        public BigIntHandle Decrement(BigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Decrement_X(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region DivideExactly 関数

        public BigIntHandle DivideExactly(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_I_X(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_L_X(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_UI_X(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_UL_X(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_I(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_L(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_UI(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_UL(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_X_X(u.NativeHandle, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_I_UX(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_L_UX(u, v.NativeHandle, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_UX_I(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivideExactly(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivideExactly_UX_L(u.NativeHandle, v, out IntPtr q_handle));
            return (new BigIntHandle(q_handle));
        }

        #endregion

        #region DivRem 関数

        public BigIntHandle DivRem(Int32 u, BigIntHandle v, out Int32 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_I_X(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(Int64 u, BigIntHandle v, out Int64 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_L_X(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(UInt32 u, BigIntHandle v, out UInt32 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UI_X(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(UInt64 u, BigIntHandle v, out UInt64 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UL_X(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(UBigIntHandle u, BigIntHandle v, out UBigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr q_handle, out IntPtr r_handle));
            r = new UBigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, Int32 v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_I(u.NativeHandle, v, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, Int64 v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_L(u.NativeHandle, v, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, UInt32 v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_UI(u.NativeHandle, v, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, UInt64 v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_UL(u.NativeHandle, v, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, UBigIntHandle v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(BigIntHandle u, BigIntHandle v, out BigIntHandle r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_X_X(u.NativeHandle, v.NativeHandle, out IntPtr q_handle, out IntPtr r_handle));
            r = new BigIntHandle(r_handle);
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(Int32 u, UBigIntHandle v, out Int32 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_I_UX(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(Int64 u, UBigIntHandle v, out Int64 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_L_UX(u, v.NativeHandle, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(UBigIntHandle u, Int32 v, out UInt32 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_I(u.NativeHandle, v, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        public BigIntHandle DivRem(UBigIntHandle u, Int64 v, out UInt64 r)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_DivRem_UX_L(u.NativeHandle, v, out IntPtr q_handle, out r));
            return (new BigIntHandle(q_handle));
        }

        #endregion

        #region Equals 関数

        public bool Equals(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_I_X(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_L_X(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UI_X(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UL_X(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_X(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_I(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_L(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_UI(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_UL(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_UX(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_X_X(u.NativeHandle, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_I_UX(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_L_UX(u, v.NativeHandle, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_I(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        public bool Equals(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Equals_UX_L(u.NativeHandle, v, out UInt32 w));
            return (w != 0);
        }

        #endregion

        #region ExclusiveOr 関数

        public BigIntHandle ExclusiveOr(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle ExclusiveOr(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ExclusiveOr_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        #endregion

        #region FromByteArray 関数

        public BigIntHandle FromByteArray(byte[] data)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_FromByteArray(data, data.Length, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region From 関数

        public BigIntHandle From(Int32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_I(value, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle From(Int64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_L(value, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle From(UInt32 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UI(value, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle From(UInt64 value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UL(value, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle From(UBigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_From_UX(value.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
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

        public BigIntHandle Zero
        {
            get
            {
                return (new BigIntHandle(DefaultValueHandle));
            }
        }

        public BigIntHandle One
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_ONE, out IntPtr r));
                return (new BigIntHandle(r));
            }
        }

        public BigIntHandle MinusOne
        {
            get
            {
                HandleResultCode((PMC_STATUS_CODE)PMCCS_GetConstantValue_I((Int32)PMC_CONSTANT_CODE.PMC_CONSTANT_MINUS_ONE, out IntPtr r));
                return (new BigIntHandle(r));
            }
        }

        #endregion

        #region GetHashCode 関数

        public Int32 GetHashCode(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetHashCode_X(value.NativeHandle, out Int32 r));
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

        #region GreatestCommonDivisor 関数

        public UBigIntHandle GreatestCommonDivisor(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_I_X(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_L_X(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_I(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_L(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle GreatestCommonDivisor(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GreatestCommonDivisor_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        #endregion

        #region 検査関数

        public bool IsEven(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_EVEN(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsMinusOne(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_MINUS_ONE(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsOne(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ONE(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsPowerOfTwo(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_POWER_OF_TWO(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        public bool IsZero(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_IS_ZERO(value.NativeHandle, out UInt32 r));
            return (r != 0);
        }

        #endregion

        #region Increment 関数

        public BigIntHandle Increment(BigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Increment_X(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region LeftShift 関数

        public BigIntHandle LeftShift(BigIntHandle x, Int32 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_X_I(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle LeftShift(BigIntHandle x, UInt32 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_X_UI(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle LeftShift(BigIntHandle x, Int64 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_X_L(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle LeftShift(BigIntHandle x, UInt64 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_LeftShift_X_UL(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region Modulo 関数

        public UInt32 Modulo(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Modulo_X_UI(u.NativeHandle, v, out UInt32 w));
            return (w);
        }

        public UInt64 Modulo(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Modulo_X_UL(u.NativeHandle, v, out UInt64 w));
            return (w);
        }

        public UBigIntHandle Modulo(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Modulo_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Modulo(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Modulo_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        public UBigIntHandle Modulo(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Modulo_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new UBigIntHandle(w));
        }

        #endregion

        #region Multiply 関数

        public BigIntHandle Multiply(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Multiply(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Multiply_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        #endregion

        #region Negate 関数

        public BigIntHandle Negate(UBigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Negate_UX(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Negate(BigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Negate_X(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region OneComplement 関数

        public BigIntHandle OneComplement(UBigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_OneComplement_UX(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle OneComplement(BigIntHandle x)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_OneComplement_X(x.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region Power 関数

        public BigIntHandle Pow(Int32 x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_I_UI(x, n, out v));
            return (new BigIntHandle(v));
        }

        public BigIntHandle Pow(Int64 x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_L_UI(x, n, out v));
            return (new BigIntHandle(v));
        }

        public BigIntHandle Pow(BigIntHandle x, UInt32 n)
        {
            IntPtr v;
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Pow_X_UI(x.NativeHandle, n, out v));
            return (new BigIntHandle(v));
        }

        #endregion

        #region Remainder 関数

        public Int32 Remainder(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_I_X(u, v.NativeHandle, out Int32 r));
            return (r);
        }

        public Int64 Remainder(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_L_X(u, v.NativeHandle, out Int64 r));
            return (r);
        }

        public UInt32 Remainder(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UI_X(u, v.NativeHandle, out UInt32 r));
            return (r);
        }

        public UInt64 Remainder(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UL_X(u, v.NativeHandle, out UInt64 r));
            return (r);
        }

        public UBigIntHandle Remainder(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr r));
            return (new UBigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_I(u.NativeHandle, v, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_L(u.NativeHandle, v, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_UI(u.NativeHandle, v, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_UL(u.NativeHandle, v, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle Remainder(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_X_X(u.NativeHandle, v.NativeHandle, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public Int32 Remainder(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_I_UX(u, v.NativeHandle, out Int32 w));
            return (w);
        }

        public Int64 Remainder(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_L_UX(u, v.NativeHandle, out Int64 w));
            return (w);
        }

        public UInt32 Remainder(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_I(u.NativeHandle, v, out UInt32 w));
            return (w);
        }

        public UInt64 Remainder(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Remainder_UX_L(u.NativeHandle, v, out UInt64 w));
            return (w);
        }

        #endregion

        #region RightShift 関数

        public BigIntHandle RightShift(BigIntHandle x, Int32 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_X_I(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle RightShift(BigIntHandle x, UInt32 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_X_UI(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle RightShift(BigIntHandle x, Int64 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_X_L(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        public BigIntHandle RightShift(BigIntHandle x, UInt64 n)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_RightShift_X_UL(x.NativeHandle, n, out IntPtr r));
            return (new BigIntHandle(r));
        }

        #endregion

        #region Subtruct 関数

        public BigIntHandle Subtruct(Int32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_I_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(Int64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_L_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UInt32 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UI_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UInt32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UI_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UInt64 u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UL_X(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UInt64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UL_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(BigIntHandle u, BigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_X_X(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(Int32 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_I_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(Int64 u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_L_UX(u, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, Int32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_I(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, Int64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_L(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, UInt32 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UI(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, UInt64 v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UL(u.NativeHandle, v, out IntPtr w));
            return (new BigIntHandle(w));
        }

        public BigIntHandle Subtruct(UBigIntHandle u, UBigIntHandle v)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Subtruct_UX_UX(u.NativeHandle, v.NativeHandle, out IntPtr w));
            return (new BigIntHandle(w));
        }

        #endregion

        #region ToByteArray 関数

        public byte[] ToByteArray(BigIntHandle value)
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

        public string ToString(BigIntHandle value, string format, NumberFormatInfo number_format_info)
        {
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_GetStringCount_X(value.NativeHandle, format, native_number_format_info, IntPtr.Zero, 0, out Int32 string_builder_capacity));
            string_builder_capacity += 1; // 終端ヌル文字の分だけ増やす
            var temp_buf = new StringBuilder(string_builder_capacity);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToString_X(value.NativeHandle, format, native_number_format_info, temp_buf, temp_buf.Capacity, out Int32 r));
            return (temp_buf.ToString());
        }

        #endregion

        #region To 関数

        public Int32 ToInt32(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt32_X(value.NativeHandle, out Int32 r));
            return (r);
        }

        public UInt32 ToUInt32(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt32_X(value.NativeHandle, out UInt32 r));
            return (r);
        }

        public Int64 ToInt64(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToInt64_X(value.NativeHandle, out Int64 r));
            return (r);
        }

        public UInt64 ToUInt64(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUInt64_X(value.NativeHandle, out UInt64 r));
            return (r);
        }

        public UBigIntHandle ToUBigInt(BigIntHandle value)
        {
            HandleResultCode((PMC_STATUS_CODE)PMCCS_ToUBigInt_X(value.NativeHandle, out IntPtr r));
            return (new UBigIntHandle(r));
        }

        #endregion

        #region TryParse 関数

        public BigIntHandle Parse(string source, NumberStyles number_style, NumberFormatInfo number_format_info)
        {
            var native_number_style = (Int32)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_Parse(source, native_number_style, native_number_format_info, out IntPtr r_handle));
            return (new BigIntHandle(r_handle));
        }

        public bool TryParse(string source, NumberStyles number_style, NumberFormatInfo number_format_info, out BigIntHandle value)
        {
            var native_number_style = (Int32)number_style;
            var native_number_format_info = new PMC_NUMBER_FORMAT_INFO(number_format_info ?? CultureInfo.CurrentCulture.NumberFormat);
            HandleResultCode((PMC_STATUS_CODE)PMCCS_TryParse(source, native_number_style, native_number_format_info, out IntPtr value_handle));
            if (value_handle == IntPtr.Zero)
            {
                value = null;
                return (false);
            }
            value = new BigIntHandle(value_handle);
            return (true);
        }

        #endregion

        #endregion
    }
}


/*
 * END OF FILE
 */
