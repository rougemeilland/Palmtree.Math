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

namespace Palmtree.Math.Core
{
    internal class RationalHandle
        : IDisposable
    {
        private static RationalEngine _engine;
        private static IRationalDisposable _disposable_object;
        private bool _is_disposed;

        static RationalHandle()
        {
            _engine = new RationalEngine();
            _disposable_object = _engine;
        }

        public RationalHandle()
            : this(_engine.DefaultValueHandle)
        {
        }

        public RationalHandle(IntPtr native_handle)
        {
            _is_disposed = false;
            NativeHandle = native_handle;
            _disposable_object.CheckHandle(native_handle);
        }

        ~RationalHandle()
        {
            Dispose(false);
        }

        public IntPtr NativeHandle { get; private set; }

        protected virtual void Dispose(bool disposing)
        {
            if (!_is_disposed)
            {
                if (disposing)
                {
                    // マネージリソースの解放
                }

                // アンマネージリソースの解放
                if (NativeHandle != IntPtr.Zero)
                {
                    try
                    {
                        _disposable_object.Dispose(NativeHandle);
                    }
                    catch (Exception)
                    {
                        // 例外は無視する
                    }
                    finally
                    {
                        NativeHandle = IntPtr.Zero;
                    }
                }

                _is_disposed = true;
            }
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
    }
}


/*
 * END OF FILE
 */