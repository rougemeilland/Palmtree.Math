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

        public static UInt32 Subtruct(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Subtruct(u, v.Handle));
        }

        public static UInt64 Subtruct(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Subtruct(u, v.Handle));
        }

        public static UBigInt Multiply(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static UBigInt Multiply(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.Multiply(u, v.Handle)));
        }

        public static UInt32 Divide(this UInt32 u, UBigInt v)
        {
            UInt32 r;
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UInt64 Divide(this UInt64 u, UBigInt v)
        {
            UInt64 r;
            var q = UBigInt.EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UInt32 Remainder(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Remainder(u, v.Handle));
        }

        public static UInt64 Remainder(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Remainder(u, v.Handle));
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

        // UInt32.Equals(object o) あるいは UInt64.Equals(object o) が先にHITしてしまい、以下のオーバーロードは使用されることはないことが判明したため、廃止する。
#if false
        public static bool Equals(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Equals(u, v.Handle));
        }

        public static bool Equals(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Equals(u, v.Handle));
        }
#endif

        // UInt32.CompareTo(object o) あるいは UInt64.CompareTo(object o) が先にHITしてしまい、以下のオーバーロードは使用されることはないことが判明したため、廃止する。
#if false
        public static int CompareTo(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Compare(u, v.Handle));
        }

        public static int CompareTo(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.Compare(u, v.Handle));
        }
#endif

        public static UInt32 BitwiseAnd(this UInt32 u, UBigInt v)
        {
            return (UBigInt.EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UInt64 BitwiseAnd(this UInt64 u, UBigInt v)
        {
            return (UBigInt.EngineObject.BitwiseAnd(u, v.Handle));
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

        public static UBigInt GreatestCommonDivisor(this UInt32 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt GreatestCommonDivisor(this UInt64 u, UBigInt v)
        {
            return (new UBigInt(UBigInt.EngineObject.GreatestCommonDivisor(u, v.Handle)));
        }

        public static UBigInt TimesPow(this UInt32 v, UInt32 e)
        {
            return (new UBigInt(UBigInt.EngineObject.TimesPow(v, e)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */