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
    public static class RationalExtensions
    {
        #region パブリックメソッド

        public static Rational ToRational(this byte[] array)
        {
            return (new Rational(Rational.EngineObject.FromByteArray(array)));
        }

        public static Rational ToRational(this Int32 u)
        {
            return (new Rational(Rational.EngineObject.From(u)));
        }

        public static Rational ToRational(this Int64 u)
        {
            return (new Rational(Rational.EngineObject.From(u)));
        }

        public static Rational ToRational(this UInt32 u)
        {
            return (new Rational(Rational.EngineObject.From(u)));
        }

        public static Rational ToRational(this UInt64 u)
        {
            return (new Rational(Rational.EngineObject.From(u)));
        }

        public static Rational Add(this Int32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Add(u, v.Handle)));
        }

        public static Rational Add(this Int64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Add(u, v.Handle)));
        }

        public static Rational Add(this UInt32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Add(u, v.Handle)));
        }

        public static Rational Add(this UInt64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Add(u, v.Handle)));
        }

        public static Rational Subtruct(this Int32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Subtruct(u, v.Handle)));
        }

        public static Rational Subtruct(this Int64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Subtruct(u, v.Handle)));
        }

        public static Rational Subtruct(this UInt32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Subtruct(u, v.Handle)));
        }

        public static Rational Subtruct(this UInt64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Subtruct(u, v.Handle)));
        }

        public static Rational Multiply(this Int32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Multiply(u, v.Handle)));
        }

        public static Rational Multiply(this Int64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Multiply(u, v.Handle)));
        }

        public static Rational Multiply(this UInt32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Multiply(u, v.Handle)));
        }

        public static Rational Multiply(this UInt64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Multiply(u, v.Handle)));
        }

        public static Rational Divide(this Int32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Divide(u, v.Handle)));
        }

        public static Rational Divide(this Int64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Divide(u, v.Handle)));
        }

        public static Rational Divide(this UInt32 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Divide(u, v.Handle)));
        }

        public static Rational Divide(this UInt64 u, Rational v)
        {
            return (new Rational(Rational.EngineObject.Divide(u, v.Handle)));
        }

        public static Rational Pow(this Int32 v, Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(v, e)));
        }

        public static Rational Pow(this Int64 v, Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(v, e)));
        }

        public static Rational Pow(this UInt32 v, Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(v, e)));
        }

        public static Rational Pow(this UInt64 v, Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(v, e)));
        }

        public static Rational Invert(this Int32 v)
        {
            return (new Rational(Rational.EngineObject.Invert(v)));
        }

        public static Rational Invert(this Int64 v)
        {
            return (new Rational(Rational.EngineObject.Invert(v)));
        }

        public static Rational Invert(this UInt32 v)
        {
            return (new Rational(Rational.EngineObject.Invert(v)));
        }

        public static Rational Invert(this UInt64 v)
        {
            return (new Rational(Rational.EngineObject.Invert(v)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */
