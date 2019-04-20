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
    public class Random
        : IDisposable
    {
        #region プライベートフィールド

        private bool _is_disposed;
        private Core.RandomStateObjectHandle _random_state_object_handle;

        #endregion

        #region コンストラクタ

        static Random()
        {
            EngineObject = new Core.UBigIntEngine();
        }

        private Random(Core.RandomStateObjectHandle random_state_object_handle)
        {
            _is_disposed = false;
            _random_state_object_handle = random_state_object_handle;
        }

        public Random(UInt32 seed)
            : this(EngineObject.AllocateRandomStateObject(seed))
        {
        }

        public Random(UInt32[] init_key)
            : this(EngineObject.AllocateRandomStateObject(init_key))
        {
        }

        ~Random()
        {
            Dispose(false);
        }

        #endregion

        #region パブリックメソッド

        public UInt32 GenerateUint32()
        {
            return (EngineObject.GenerateUInt32RandomValue(_random_state_object_handle));
        }

        public UInt64 GenerateUint64()
        {
            return (EngineObject.GenerateUInt64RandomValue(_random_state_object_handle));
        }

        public UBigInt GenerateUBigInt(Int32 bit_count)
        {
            return (new UBigInt(EngineObject.GenerateUBigIntRandomValue(_random_state_object_handle, bit_count)));
        }

        public Rational GenerateRational(Int32 bit_count)
        {
            return (new Rational(Rational.EngineObject.GenerateRationalRandomValue(_random_state_object_handle, bit_count)));
        }

        public double GenerateDouble()
        {
            return (EngineObject.GenerateDoubleRandomValue(_random_state_object_handle));
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion

        #region インターナルプロパティ

        internal static Core.UBigIntEngine EngineObject { get; private set; }

        #endregion

        #region プロテクテッドメソッド

        #endregion

        protected virtual void Dispose(bool disposing)
        {
            if (!_is_disposed)
            {
                if (disposing)
                {
                    // マネージドリソースの解放
                    if (_random_state_object_handle != null)
                    {
                        _random_state_object_handle.Dispose();
                        _random_state_object_handle = null;
                    }
                }

                // アンマネージドリソースの解放

                _is_disposed = true;
            }
        }

    }
}


/*
 * END OF FILE
 */
