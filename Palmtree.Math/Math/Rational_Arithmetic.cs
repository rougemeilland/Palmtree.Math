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

        public Rational Abs()
        {
            return (new Rational(EngineObject.Abs(Handle)));
        }

        public BigInt Ceiling()
        {
            return (new BigInt(EngineObject.Ceiling(Handle)));
        }

        public BigInt Floor()
        {
            return (new BigInt(EngineObject.Floor(Handle)));
        }

        public Rational Pow(Int32 e)
        {
            return (new Rational(EngineObject.Pow(Handle, e)));
        }

        public static Rational Pow(Int32 v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v, e)));
        }

        public static Rational Pow(Int64 v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v, e)));
        }

        public static Rational Pow(BigInt v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v.Handle, e)));
        }

        public static Rational Pow(UInt32 v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v, e)));
        }

        public static Rational Pow(UInt64 v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v, e)));
        }

        public static Rational Pow(UBigInt v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v.Handle, e)));
        }

        public static Rational Pow(Rational v, Int32 e)
        {
            return (new Rational(EngineObject.Pow(v.Handle, e)));
        }

        public Rational Invert()
        {
            return (new Rational(EngineObject.Invert(Handle)));
        }

        public static Rational Invert(Int32 u)
        {
            return (new Rational(EngineObject.Invert(u)));
        }

        public static Rational Invert(Int64 u)
        {
            return (new Rational(EngineObject.Invert(u)));
        }

        public static Rational Invert(BigInt u)
        {
            return (new Rational(EngineObject.Invert(u.Handle)));
        }

        public static Rational Invert(UInt32 u)
        {
            return (new Rational(EngineObject.Invert(u)));
        }

        public static Rational Invert(UInt64 u)
        {
            return (new Rational(EngineObject.Invert(u)));
        }

        public static Rational Invert(UBigInt u)
        {
            return (new Rational(EngineObject.Invert(u.Handle)));
        }

        public static Rational Invert(Rational u)
        {
            return (new Rational(EngineObject.Invert(u.Handle)));
        }

        public Rational Negate()
        {
            return (new Rational(EngineObject.Negate(Handle)));
        }

        public BigInt Round(MidpointRounding mode)
        {
            return (new BigInt(EngineObject.Round(Handle, mode)));
        }

        public BigInt Round(RoundingMode mode)
        {
            return (new BigInt(EngineObject.Round(Handle, mode)));
        }

        public Rational Round(Int32 decimals, MidpointRounding mode)
        {
            return (new Rational(EngineObject.Round(Handle, decimals, mode)));
        }

        public Rational Round(Int32 decimals, RoundingMode mode)
        {
            return (new Rational(EngineObject.Round(Handle, decimals, mode)));
        }

        public Int32 FloorLog10()
        {
            return (EngineObject.FloorLog10(Handle));
        }

        public static Rational operator -(Rational x)
        {
            return (new Rational(EngineObject.Negate(x.Handle)));
        }

        public static Rational operator +(Rational x)
        {
            return (x);
        }

        #endregion
    }
}


/*
 * END OF FILE
 */