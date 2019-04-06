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
    partial class BigInt
    {
        #region パブリックメソッド

        public static BigInt From(Int32 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static BigInt From(Int64 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static BigInt From(UInt32 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static BigInt From(UInt64 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static BigInt From(UBigInt x)
        {
            return (new BigInt(EngineObject.From(x.Handle)));
        }

        public static BigInt From(Rational x)
        {
            return (new BigInt(Rational.EngineObject.ToBigInt(x.Handle)));
        }

        public static explicit operator BigInt(Int32 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static explicit operator BigInt(Int64 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static explicit operator BigInt(UInt32 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static explicit operator BigInt(UInt64 x)
        {
            return (new BigInt(EngineObject.From(x)));
        }

        public static explicit operator BigInt(UBigInt x)
        {
            return (new BigInt(EngineObject.From(x.Handle)));
        }

        public static explicit operator BigInt(Rational x)
        {
            return (new BigInt(Rational.EngineObject.ToBigInt(x.Handle)));
        }

        public Int32 ToInt32()
        {
            return (EngineObject.ToInt32(Handle));
        }

        public Int64 ToInt64()
        {
            return (EngineObject.ToInt64(Handle));
        }

        public UInt32 ToUInt32()
        {
            return (EngineObject.ToUInt32(Handle));
        }

        public UInt64 ToUInt64()
        {
            return (EngineObject.ToUInt64(Handle));
        }

        public UBigInt ToUBigInt()
        {
            return (new UBigInt(EngineObject.ToUBigInt(Handle)));
        }

        public Rational ToRational()
        {
            return (new Rational(Rational.EngineObject.From(Handle)));
        }

        public static explicit operator Int32(BigInt x)
        {
            return (EngineObject.ToInt32(x.Handle));
        }

        public static explicit operator Int64(BigInt x)
        {
            return (EngineObject.ToInt64(x.Handle));
        }

        public static explicit operator UInt32(BigInt x)
        {
            return (EngineObject.ToUInt32(x.Handle));
        }

        public static explicit operator UInt64(BigInt x)
        {
            return (EngineObject.ToUInt64(x.Handle));
        }

        public static explicit operator UBigInt(BigInt x)
        {
            return (new UBigInt(EngineObject.ToUBigInt(x.Handle)));
        }

        public static explicit operator Rational(BigInt x)
        {
            return (new Rational(Rational.EngineObject.From(x.Handle)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */