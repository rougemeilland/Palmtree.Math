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
    partial class UBigInt
    {
        #region パブリックメソッド

        public static UInt32 DivRem(UInt32 u, UBigInt v, out UInt32 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UInt64 DivRem(UInt64 u, UBigInt v, out UInt64 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UBigInt DivRem(UBigInt u, UInt32 v, out UInt32 r)
        {
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new UBigInt(q));
        }

        public static UBigInt DivRem(UBigInt u, UInt64 v, out UInt64 r)
        {
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new UBigInt(q));
        }

        public static UBigInt DivRem(UBigInt u, UBigInt v, out UBigInt r)
        {
            Core.UBigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(u.Handle, v.Handle, out r_handle);
            r = new UBigInt(r_handle);
            return (new UBigInt(q_handle));
        }

        public UBigInt DivRem(UInt32 v, out UInt32 r)
        {
            var q_handle = EngineObject.DivRem(Handle, v, out r);
            return (new UBigInt(q_handle));
        }

        public UBigInt DivRem(UInt64 v, out UInt64 r)
        {
            var q_handle = EngineObject.DivRem(Handle, v, out r);
            return (new UBigInt(q_handle));
        }

        public UBigInt DivRem(UBigInt v, out UBigInt r)
        {
            Core.UBigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(Handle, v.Handle, out r_handle);
            r = new UBigInt(r_handle);
            return (new UBigInt(q_handle));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */