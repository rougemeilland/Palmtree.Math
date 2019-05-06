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


using Palmtree.Math;
using System;

namespace Palmtree.Security.Cryptography
{
    public class CryptoRandom
        : IDisposable
    { 
        #region プライベートフィールド

        private bool _is_disposed;
        private System.Security.Cryptography.RNGCryptoServiceProvider _engine;

        #endregion

        #region コンストラクタ

        public CryptoRandom()
        {
            _is_disposed = false;
            _engine = new System.Security.Cryptography.RNGCryptoServiceProvider();
        }

        ~CryptoRandom()
        {
            Dispose(false);
        }

        #endregion

        #region パブリックメソッド

        public UInt32 GenerateUint32()
        {
            var data = new byte[4];
            _engine.GetBytes(data);
            return (BitConverter.ToUInt32(data, 0));
        }

        public UInt64 GenerateUint64()
        {
            var data = new byte[8];
            _engine.GetBytes(data);
            return (BitConverter.ToUInt64(data, 0));
        }

        public UBigInt GenerateUBigInt(Int32 bit_count)
        {
            if (bit_count <= 0)
                throw new ArgumentOutOfRangeException();
            var data = new byte[(bit_count + 7) / 8];
            _engine.GetBytes(data);
            return (new UBigInt(UBigInt.EngineObject.GenerateUBigIntCryptoRandomValue(data, bit_count)));
        }

        public Rational GenerateRational(Int32 bit_count)
        {
            if (bit_count <= 0)
                throw new ArgumentOutOfRangeException();
            var data = new byte[(bit_count + 7) / 8];
            _engine.GetBytes(data);
            return (new Rational(Rational.EngineObject.GenerateRationalCryptoRandomValue(data, bit_count)));
        }

        public double GenerateDouble()
        {
            // まず、64bit 分だけのデータを取得して UInt64型 の数値を得てこれを仮数とし、指数を 0 に初期化する
            var mantissa_bytes = new byte[8];
            _engine.GetBytes(mantissa_bytes);
            var mantissa = BitConverter.ToUInt64(mantissa_bytes, 0);
            var exponent = 1U;

            // 仮数の最上位 8bit が 0 である場合に以下の処理を繰り返す
            while ((mantissa & 0xff00000000000000UL) == 0)
            {
                // 新たに乱数を 8bit だけ取得する
                var additional_byte = new byte[1];
                _engine.GetBytes(additional_byte);

                // 仮数を左に 8bit だけシフトし、最下位 8bit に上記で得た乱数を追加する。また、指数を 8 だけ増やす。
                mantissa <<= 8;
                mantissa |= additional_byte[0];
                exponent += 8U;
            }

            // 仮数の最上位 bit が 0 である場合に以下の処理を繰り返す
            while ((mantissa & 0x8000000000000000UL) == 0)
            {
                // 仮数を左に 1bit だけシフトし、指数を 1 だけ増やす。
                mantissa <<= 1;
                exponent += 1U;
            }

            // この時点の仮数の上位 53bit と指数を結合して double 値とする。
            double result = ConstructDoubleValue(mantissa >> 11, exponent);

            return (result);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion

        #region プロテクテッドメソッド

        protected virtual void Dispose(bool disposing)
        {
            if (!_is_disposed)
            {
                if (disposing)
                {
                    // マネージドリソースの解放
                    if (_engine != null)
                    {
                        _engine.Dispose();
                        _engine = null;
                    }
                }

                // アンマネージドリソースの解放

                _is_disposed = true;
            }
        }

        #endregion

        #region プライベートメソッド

        private static double ConstructDoubleValue(UInt64 mantissa, UInt32 exponent)
        {
            exponent += 52U;
            var result = (double)mantissa;
            while (exponent >= 32)
            {
                result /= 0x0000000100000000UL;
                exponent -= 32;
            }
            if ((exponent & 0x10) != 0)
                result /= 0x10000U;
            if ((exponent & 0x8) != 0)
                result /= 0x100U;
            if ((exponent & 0x4) != 0)
                result /= 0x10U;
            if ((exponent & 0x2) != 0)
                result /= 0x4U;
            if ((exponent & 0x1) != 0)
                result /= 0x2U;

            if (result < 0 || result >= 1.0)
                throw new InternalErrorException();
            return result;
        }

        #endregion

    }
}


/*
 * END OF FILE
 */
