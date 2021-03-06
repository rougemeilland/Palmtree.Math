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


namespace Palmtree.Math
{
    partial struct BigInt
    {
        #region パブリックメソッド

        public UBigInt Abs()
        {
            return (new UBigInt(EngineObject.Abs(Handle)));
        }

        public BigInt Negate()
        {
            return (new BigInt(EngineObject.Negate(Handle)));
        }

        public BigInt OneComplement()
        {
            return (new BigInt(EngineObject.OneComplement(Handle)));
        }

        public BigInt Pow(UInt32 e)
        {
            return (new BigInt(EngineObject.Pow(Handle, e)));
        }

        public static BigInt Pow(Int32 v, UInt32 e)
        {
            return (new BigInt(EngineObject.Pow(v, e)));
        }

        public static BigInt Pow(Int64 v, UInt32 e)
        {
            return (new BigInt(EngineObject.Pow(v, e)));
        }

        public static BigInt Pow(BigInt v, UInt32 e)
        {
            return (new BigInt(EngineObject.Pow(v.Handle, e)));
        }

        public Rational Pow(Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(Handle, e)));
        }

        public Rational Invert()
        {
            return (new Rational(Rational.EngineObject.Invert(Handle)));
        }

        public static BigInt operator ~(BigInt x)
        {
            return (new BigInt(EngineObject.OneComplement(x.Handle)));
        }

        public static BigInt operator -(BigInt x)
        {
            return (new BigInt(EngineObject.Negate(x.Handle)));
        }

        public static BigInt operator +(BigInt x)
        {
            return (x);
        }

        #endregion
    }
}


/*
 * END OF FILE
 */