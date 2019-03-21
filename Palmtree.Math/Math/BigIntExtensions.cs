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
    public static class BigIntExtensions
    {
        #region パブリックメソッド

        public static BigInt ToBigInt(this byte[] array)
        {
            return (new BigInt(BigInt.EngineObject.FromByteArray(array)));
        }

        public static BigInt ToBigInt(this UInt32 u)
        {
            return (new BigInt(BigInt.EngineObject.From(u)));
        }

        public static BigInt ToBigInt(this UInt64 u)
        {
            return (new BigInt(BigInt.EngineObject.From(u)));
        }

        public static BigInt ToBigInt(this Int32 u)
        {
            return (new BigInt(BigInt.EngineObject.From(u)));
        }

        public static BigInt ToBigInt(this Int64 u)
        {
            return (new BigInt(BigInt.EngineObject.From(u)));
        }

        public static BigInt ToBigInt(this UBigInt u)
        {
            return (new BigInt(BigInt.EngineObject.From(u.Handle)));
        }

        public static BigInt Add(this UInt32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this UInt64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u, v.Handle)));
        }

        public static BigInt Add(this UBigInt u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Add(u.Handle, v.Handle)));
        }

        public static BigInt Subtruct(this UInt32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this UInt64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u, v.Handle)));
        }

        public static BigInt Subtruct(this UBigInt u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Subtruct(u.Handle, v.Handle)));
        }

        public static BigInt Multiply(this UInt32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this UInt64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static BigInt Multiply(this UBigInt u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.Multiply(u.Handle, v.Handle)));
        }

        public static BigInt Divide(this UInt32 u, BigInt v)
        {
            UInt32 r;
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt Divide(this UInt64 u, BigInt v)
        {
            UInt64 r;
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt Divide(this Int32 u, BigInt v)
        {
            Int32 r;
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt Divide(this Int64 u, BigInt v)
        {
            Int64 r;
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt Divide(this UBigInt u, BigInt v)
        {
            Core.UBigIntHandle r;
            return (new BigInt(BigInt.EngineObject.DivRem(u.Handle, v.Handle, out r)));
        }

        public static UInt32 Remainder(this UInt32 u, BigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static UInt64 Remainder(this UInt64 u, BigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static Int32 Remainder(this Int32 u, BigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static Int64 Remainder(this Int64 u, BigInt v)
        {
            return (BigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static UBigInt Remainder(this UBigInt u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.Remainder(u.Handle, v.Handle)));
        }

        public static BigInt DivRem(this UInt32 u, BigInt v, out UInt32 r)
        {
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt DivRem(this UInt64 u, BigInt v, out UInt64 r)
        {
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt DivRem(this Int32 u, BigInt v, out Int32 r)
        {
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt DivRem(this Int64 u, BigInt v, out Int64 r)
        {
            return (new BigInt(BigInt.EngineObject.DivRem(u, v.Handle, out r)));
        }

        public static BigInt DivRem(this UBigInt u, BigInt v, out UBigInt r)
        {
            Core.UBigIntHandle r_handle;
            var q_hadnle = BigInt.EngineObject.DivRem(u.Handle, v.Handle, out r_handle);
            r = new UBigInt(r_handle);
            return (new BigInt(q_hadnle));
        }

        // UInt32.Equals(object o) などが先にHITしてしまい、以下のオーバーロードは使用されることはないことが判明したため、廃止する。
#if false
        public static bool Equals(this UInt32 u, BigInt v)
        {
            return (BigInt.EngineObject.Equals(u, v.Handle));
        }

        public static bool Equals(this UInt64 u, BigInt v)
        {
            return (BigInt.EngineObject.Equals(u, v.Handle));
        }
#endif

        // UInt32.CompareTo(object o) などが先にHITしてしまい、以下のオーバーロードは使用されることはないことが判明したため、廃止する。
#if false
        public static int CompareTo(this UInt32 u, BigInt v)
        {
            return (BigInt.EngineObject.Compare(u, v.Handle));
        }

        public static int CompareTo(this UInt64 u, BigInt v)
        {
            return (BigInt.EngineObject.Compare(u, v.Handle));
        }
#endif

        public static int CompareTo(this UBigInt u, BigInt v)
        {
            return (BigInt.EngineObject.Compare(u.Handle, v.Handle));
        }

        public static UInt32 BitwiseAnd(this UInt32 u, BigInt v)
        {
            return (BigInt.EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UInt64 BitwiseAnd(this UInt64 u, BigInt v)
        {
            return (BigInt.EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static BigInt BitwiseAnd(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static BigInt BitwiseAnd(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static UBigInt BitwiseAnd(this UBigInt u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u.Handle, v.Handle)));
        }

        public static BigInt BitwiseOr(this UInt32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static BigInt BitwiseOr(this UInt64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static BigInt BitwiseOr(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static BigInt BitwiseOr(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseOr(u, v.Handle)));
        }

        public static BigInt BitwiseOr(this UBigInt u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.BitwiseOr(u.Handle, v.Handle)));
        }

        public static BigInt ExclusiveOr(this UInt32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this UInt64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this Int32 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this Int64 u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u, v.Handle)));
        }

        public static BigInt ExclusiveOr(this UBigInt u, BigInt v)
        {
            return (new BigInt(BigInt.EngineObject.ExclusiveOr(u.Handle, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UInt32 u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UInt64 u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this Int32 u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this Int64 u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UBigInt u, BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.GreatestCommonDivisor(u.Handle, v.Handle)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */