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
    partial struct BigInt
    {
        #region パブリックメソッド

        public static BigInt DivRem(UInt32 u, BigInt v, out UInt32 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt DivRem(UInt64 u, BigInt v, out UInt64 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt DivRem(Int32 u, BigInt v, out Int32 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt DivRem(Int64 u, BigInt v, out Int64 r)
        {
            var q = EngineObject.DivRem(u, v.Handle, out r);
            return (new BigInt(q));
        }

        public static BigInt DivRem(UBigInt u, BigInt v, out UBigInt r)
        {
            Core.UBigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(u.Handle, v.Handle, out r_handle);
            r = new UBigInt(r_handle);
            return (new BigInt(q_handle));
        }

        public static BigInt DivRem(BigInt u, UInt32 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(u.Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public static BigInt DivRem(BigInt u, UInt64 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(u.Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public static BigInt DivRem(BigInt u, Int32 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(u.Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public static BigInt DivRem(BigInt u, Int64 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(u.Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public static BigInt DivRem(BigInt u, UBigInt v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(u.Handle, v.Handle, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q_handle));
        }

        public static BigInt DivRem(BigInt u, BigInt v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(u.Handle, v.Handle, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q_handle));
        }

        public BigInt DivRem(UInt32 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public BigInt DivRem(UInt64 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public BigInt DivRem(Int32 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public BigInt DivRem(Int64 v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q = EngineObject.DivRem(Handle, v, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q));
        }

        public BigInt DivRem(UBigInt v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(Handle, v.Handle, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q_handle));
        }

        public BigInt DivRem(BigInt v, out BigInt r)
        {
            Core.BigIntHandle r_handle;
            var q_handle = EngineObject.DivRem(Handle, v.Handle, out r_handle);
            r = new BigInt(r_handle);
            return (new BigInt(q_handle));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */