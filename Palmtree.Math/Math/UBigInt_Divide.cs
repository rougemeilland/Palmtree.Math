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

        public UBigInt Divide(UInt32 v)
        {
            UInt32 r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new UBigInt(q));
        }

        public UBigInt Divide(UInt64 v)
        {
            UInt64 r;
            var q = EngineObject.DivRem(Handle, v, out r);
            return (new UBigInt(q));
        }

        public UBigInt Divide(UBigInt v)
        {
            Core.UBigIntHandle r;
            var q = EngineObject.DivRem(Handle, v.Handle, out r);
            return (new UBigInt(q));
        }

        public static UInt32 operator /(UInt32 u, UBigInt v)
        {
            UInt32 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UInt64 operator /(UInt64 u, UBigInt v)
        {
            UInt64 r;
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (q);
        }

        public static UBigInt operator /(UBigInt u, UInt32 v)
        {
            UInt32 r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new UBigInt(q));
        }

        public static UBigInt operator /(UBigInt u, UInt64 v)
        {
            UInt64 r;
            var q = EngineObject.DivRem(u.Handle, v, out r);
            return (new UBigInt(q));
        }

        public static UBigInt operator /(UBigInt u, UBigInt v)
        {
            Core.UBigIntHandle r;
            var q = EngineObject.DivRem(u.Handle, v.Handle, out r);
            return (new UBigInt(q));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */