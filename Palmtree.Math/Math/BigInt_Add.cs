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
    partial struct BigInt
    {
        #region パブリックメソッド

        public BigInt Increment()
        {
            return (new BigInt(EngineObject.Increment(Handle)));
        }

        public BigInt Add(Int32 v)
        {
            return (new BigInt(EngineObject.Add(Handle, v)));
        }

        public BigInt Add(Int64 v)
        {
            return (new BigInt(EngineObject.Add(Handle, v)));
        }

        public BigInt Add(UInt32 v)
        {
            return (new BigInt(EngineObject.Add(Handle, v)));
        }

        public BigInt Add(UInt64 v)
        {
            return (new BigInt(EngineObject.Add(Handle, v)));
        }

        public BigInt Add(UBigInt v)
        {
            return (new BigInt(EngineObject.Add(Handle, v.Handle)));
        }

        public BigInt Add(BigInt v)
        {
            return (new BigInt(EngineObject.Add(Handle, v.Handle)));
        }

        public Rational Add(Rational v)
        {
            return (new Rational(Rational.EngineObject.Add(Handle, v.Handle)));
        }

        public static BigInt operator ++(BigInt x)
        {
            return (new BigInt(EngineObject.Increment(x.Handle)));
        }

        public static BigInt operator +(Int32 u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u, v.Handle)));
        }

        public static BigInt operator +(Int64 u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u, v.Handle)));
        }

        public static BigInt operator +(UInt32 u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u, v.Handle)));
        }

        public static BigInt operator +(UInt64 u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u, v.Handle)));
        }

        public static BigInt operator +(UBigInt u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v.Handle)));
        }

        public static BigInt operator +(BigInt u, Int32 v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v)));
        }

        public static BigInt operator +(BigInt u, Int64 v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v)));
        }

        public static BigInt operator +(BigInt u, UInt32 v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v)));
        }

        public static BigInt operator +(BigInt u, UInt64 v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v)));
        }

        public static BigInt operator +(BigInt u, UBigInt v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v.Handle)));
        }

        public static BigInt operator +(BigInt u, BigInt v)
        {
            return (new BigInt(EngineObject.Add(u.Handle, v.Handle)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */