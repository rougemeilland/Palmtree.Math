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
    partial struct UBigInt
    {
        #region パブリックメソッド

        public UBigInt Pow(UInt32 e)
        {
            return (new UBigInt(EngineObject.Pow(Handle, e)));
        }

        public Rational Pow(Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(Handle, e)));
        }

        public static UBigInt Pow(UInt32 v, UInt32 e)
        {
            return (new UBigInt(EngineObject.Pow(v, e)));
        }

        public static UBigInt Pow(UInt64 v, UInt32 e)
        {
            return (new UBigInt(EngineObject.Pow(v, e)));
        }

        public static UBigInt Pow(UBigInt v, UInt32 e)
        {
            return (new UBigInt(EngineObject.Pow(v.Handle, e)));
        }

        public static Rational Pow(UBigInt v, Int32 e)
        {
            return (new Rational(Rational.EngineObject.Pow(v.Handle, e)));
        }

        public Rational Invert()
        {
            return (new Rational(Rational.EngineObject.Invert(Handle)));
        }

        public UBigInt ModPow(UBigInt e, UBigInt m)
        {
            return (new UBigInt(EngineObject.ModPow(Handle, e.Handle, m.Handle)));
        }

        public UInt32 FloorLog10()
        {
            return (EngineObject.FloorLog10(Handle));
        }

        public BigInt Negate()
        {
            return (new BigInt(BigInt.EngineObject.Negate(Handle)));
        }

        public BigInt OneComplement()
        {
            return (new BigInt(BigInt.EngineObject.OneComplement(Handle)));
        }

        public static BigInt operator ~(UBigInt x)
        {
            return (new BigInt(BigInt.EngineObject.OneComplement(x.Handle)));
        }

        public static BigInt operator -(UBigInt x)
        {
            return (new BigInt(BigInt.EngineObject.Negate(x.Handle)));
        }

        public static UBigInt operator +(UBigInt x)
        {
            return (x);
        }

        /// <summary>
        /// 拡張ユークリッド互除法を使用して、不定方程式 a * x + b * y = GCD(a, b), a > 0, b > 0 を満たす x および y を求めます。
        /// この数値は変数 a として使用されます。
        /// </summary>
        /// <param name="b">不定方程式の変数 b です。</param>
        /// <returns>
        /// 計算結果を表す<see cref="Tuple{UBigInt, BigInt, BigInt}"/>オブジェクトです。
        /// オブジェクトの第一要素は a と b の最大公約数、第二要素は不定方程式における変数 x、第三要素は不定方程式における変数 y です。
        /// </returns>
        public Tuple<UBigInt, BigInt, BigInt> ExtendedEuclideanAlgorithm(UBigInt b)
        {
            var a = this;
            if (a.IsZero)
                throw new ArgumentOutOfRangeException();
            if (b.IsZero)
                throw new ArgumentOutOfRangeException();
            var previous_x = BigInt.One;
            var previous_y = BigInt.Zero;
            var current_x = BigInt.Zero;
            var current_y = BigInt.One;
            while (!b.IsZero)
            {
                UBigInt next_b;
                var q = a.DivRem(b, out next_b);
                var next_x = previous_x - q * current_x;
                var next_y = previous_y - q * current_y;
                a = b;
                b = next_b;
                previous_x = current_x;
                current_x = next_x;
                previous_y = current_y;
                current_y = next_y;
            }
            return (new Tuple<UBigInt, BigInt, BigInt>(a, previous_x, previous_y));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */