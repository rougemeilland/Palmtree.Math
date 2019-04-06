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

        public BigInt Divide(UInt32 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new BigInt(q));
        }

        public BigInt Divide(UInt64 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new BigInt(q));
        }

        public BigInt Divide(Int32 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new BigInt(q));
        }

        public BigInt Divide(Int64 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new BigInt(q));
        }

        public BigInt Divide(UBigInt v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v.Handle, out r);
            return (new BigInt(q));
        }

        public BigInt Divide(BigInt v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(Handle, v.Handle, out r);
            return (new BigInt(q));
        }

        public Rational Divide(Rational v)
        {
            return (new Rational(Rational.EngineObject.Divide(Handle, v.Handle)));
        }

        public static BigInt operator /(UInt32 u, BigInt v)
        {
            UInt32 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(UInt64 u, BigInt v)
        {
            UInt64 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(Int32 u, BigInt v)
        {
            Int32 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(Int64 u, BigInt v)
        {
            Int64 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(UBigInt u, BigInt v)
        {
            Core.UBigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, UInt32 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, UInt64 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, Int32 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, Int64 v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, UBigInt v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt operator /(BigInt u, BigInt v)
        {
            Core.BigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v.Handle, out r);
            return (new BigInt(q));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */