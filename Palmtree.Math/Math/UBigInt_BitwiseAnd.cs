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
    partial struct UBigInt
    {
        #region パブリックメソッド

        public UInt32 BitwiseAnd(UInt32 v)
        {
            return (EngineObject.BitwiseAnd(Handle, v));
        }

        public UInt64 BitwiseAnd(UInt64 v)
        {
            return (EngineObject.BitwiseAnd(Handle, v));
        }

        public UBigInt BitwiseAnd(UBigInt v)
        {
            return (new UBigInt(EngineObject.BitwiseAnd(Handle, v.Handle)));
        }

        public UBigInt BitwiseAnd(Int32 v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(Handle, v)));
        }

        public UBigInt BitwiseAnd(Int64 v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(Handle, v)));
        }

        public UBigInt BitwiseAnd(BigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(Handle, v.Handle)));
        }

        public static UInt32 operator &(UInt32 u, UBigInt v)
        {
            return (EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UInt64 operator &(UInt64 u, UBigInt v)
        {
            return (EngineObject.BitwiseAnd(u, v.Handle));
        }

        public static UInt32 operator &(UBigInt u, UInt32 v)
        {
            return (EngineObject.BitwiseAnd(u.Handle, v));
        }

        public static UInt64 operator &(UBigInt u, UInt64 v)
        {
            return (EngineObject.BitwiseAnd(u.Handle, v));
        }

        public static UBigInt operator &(UBigInt u, UBigInt v)
        {
            return (new UBigInt(EngineObject.BitwiseAnd(u.Handle, v.Handle)));
        }

        public static UBigInt operator &(Int32 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static UBigInt operator &(Int64 u, UBigInt v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u, v.Handle)));
        }

        public static UBigInt operator &(UBigInt u, Int32 v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u.Handle, v)));
        }

        public static UBigInt operator &(UBigInt u, Int64 v)
        {
            return (new UBigInt(BigInt.EngineObject.BitwiseAnd(u.Handle, v)));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */