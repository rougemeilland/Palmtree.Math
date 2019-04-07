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


namespace Palmtree.Math
{
    public static class UBigIntExtensions
    {
        #region パブリックメソッド

        public static UBigInt ToUBigInt(this byte[] array)
        {
            return (new UBigInt(UBigInt.EngineObject.FromByteArray(array)));
        }

        public static UBigInt ToUBigInt(this UInt32 u)
        {
            return (new UBigInt(UBigInt.EngineObject.From(u)));
        }

        public static UBigInt ToUBigInt(this UInt64 u)
        {
            return (new UBigInt(UBigInt.EngineObject.From(u)));
        }

        public static UBigInt Add(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Add(u, v.Handle)));
        }

        public static UBigInt Add(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this Int32 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this Int64 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static UInt32 USubtruct(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Subtruct(u, v.Handle));
        }

        public static UInt64 USubtruct(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Subtruct(u, v.Handle));
        }

        public static BigInt Subtruct(this UInt32 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this UInt64 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this Int32 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this Int64 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static UBigInt Multiply(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static UBigInt Multiply(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this Int32 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this Int64 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static UInt32 Divide(this UInt32 u, UBigInt v)
        {
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out UInt32 r);
            return (q);
        }

        public static UInt64 Divide(this UInt64 u, UBigInt v)
        {
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out UInt64 r);
            return (q);
        }

        public static BigInt Divide(this Int32 u, UBigInt v)
        {
            var q_handle = BigInt.EngineObject.DivRem(u, v.Handle, out Int32 r);
            return (new BigInt(q_handle));
        }

        public static BigInt Divide(this Int64 u, UBigInt v)
        {
            var q_handle = BigInt.EngineObject.DivRem(u, v.Handle, out Int64 r);
            return (new BigInt(q_handle));
        }

        public static UInt32 Remainder(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static UInt64 Remainder(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static Int32 Remainder(this Int32 u, UBigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static Int64 Remainder(this Int64 u, UBigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static UInt32 DivRem(this UInt32 u, UBigInt v, out UInt32 r)
        {
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UInt64 DivRem(this UInt64 u, UBigInt v, out UInt64 r)
        {
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static BigInt DivRem(this Int32 u, UBigInt v, out Int32 r)
        {
            var q_handle = BigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q_handle));
        }

        public static BigInt DivRem(this Int64 u, UBigInt v, out Int64 r)
        {
            var q_handle = BigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q_handle));
        }

        public static UInt32 BitwiseAnd(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UInt64 BitwiseAnd(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UBigInt BitwiseAnd(this Int32 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static UBigInt BitwiseAnd(this Int64 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static UBigInt BitwiseOr(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static UBigInt BitwiseOr(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static UBigInt ExclusiveOr(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static UBigInt ExclusiveOr(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this Int32 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this Int64 u, UBigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this Int32 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this Int64 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt Pow(this UInt32 v, UInt32 e)
        {
            return (new UBigInt(UBigInt.EngineObject.Pow(v, e)));
        }

        public static UBigInt Pow(this UInt64 v, UInt32 e)
        {
            return (new UBigInt(UBigInt.EngineObject.Pow(v, e)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */