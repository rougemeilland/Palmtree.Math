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
    partial struct Rational
    {
        #region パブリックメソッド

        public Rational Divide(Int32 v)
        {
            return (new Rational(EngineObject.Divide(Handle, v)));
        }

        public Rational Divide(Int64 v)
        {
            return (new Rational(EngineObject.Divide(Handle, v)));
        }

        public Rational Divide(BigInt v)
        {
            return (new Rational(EngineObject.Divide(Handle, v.Handle)));
        }

        public Rational Divide(UInt32 v)
        {
            return (new Rational(EngineObject.Divide(Handle, v)));
        }

        public Rational Divide(UInt64 v)
        {
            return (new Rational(EngineObject.Divide(Handle, v)));
        }

        public Rational Divide(UBigInt v)
        {
            return (new Rational(EngineObject.Divide(Handle, v.Handle)));
        }

        public Rational Divide(Rational v)
        {
            return (new Rational(EngineObject.Divide(Handle, v.Handle)));
        }

        public static Rational operator /(Int32 u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u, v.Handle)));
        }

        public static Rational operator /(Int64 u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u, v.Handle)));
        }

        public static Rational operator /(BigInt u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v.Handle)));
        }

        public static Rational operator /(UInt32 u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u, v.Handle)));
        }

        public static Rational operator /(UInt64 u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u, v.Handle)));
        }

        public static Rational operator /(UBigInt u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v.Handle)));
        }

        public static Rational operator /(Rational u, Int32 v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v)));
        }

        public static Rational operator /(Rational u, Int64 v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v)));
        }

        public static Rational operator /(Rational u, BigInt v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v.Handle)));
        }

        public static Rational operator /(Rational u, UInt32 v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v)));
        }

        public static Rational operator /(Rational u, UInt64 v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v)));
        }

        public static Rational operator /(Rational u, UBigInt v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v.Handle)));
        }

        public static Rational operator /(Rational u, Rational v)
        {
            return (new Rational(EngineObject.Divide(u.Handle, v.Handle)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */