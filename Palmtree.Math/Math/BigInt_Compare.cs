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

        public int CompareTo(UInt32 v)
        {
            return (EngineObject.Compare(Handle, v));
        }

        public int CompareTo(UInt64 v)
        {
            return (EngineObject.Compare(Handle, v));
        }

        public int CompareTo(Int32 v)
        {
            return (EngineObject.Compare(Handle, v));
        }

        public int CompareTo(Int64 v)
        {
            return (EngineObject.Compare(Handle, v));
        }

        public int CompareTo(UBigInt v)
        {
            return (EngineObject.Compare(Handle, v.Handle));
        }

        public int CompareTo(BigInt v)
        {
            return (EngineObject.Compare(Handle, v.Handle));
        }

        public int CompareTo(Rational v)
        {
            return (Rational.EngineObject.Compare(Handle, v.Handle));
        }

        int IComparable.CompareTo(object o)
        {
            if (o == null)
                return (1);
            if (o is Int32)
                return (EngineObject.Compare(Handle, (Int32)o));
            if (o is Int64)
                return (EngineObject.Compare(Handle, (Int64)o));
            if (o is BigInt)
                return (EngineObject.Compare(Handle, ((BigInt)o).Handle));
            if (o is UInt32)
                return (EngineObject.Compare(Handle, (UInt32)o));
            if (o is UInt64)
                return (EngineObject.Compare(Handle, (UInt64)o));
            if (o is UBigInt)
                return (EngineObject.Compare(Handle, ((UBigInt)o).Handle));
            if (o is Rational)
                return (Rational.EngineObject.Compare(Handle, ((Rational)o).Handle));
            throw new ArgumentException("BigInt 型と比較できないオブジェクトが与えられました。");
        }

        public static int Compare(UInt32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle));
        }

        public static int Compare(UInt64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle));
        }

        public static int Compare(Int32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle));
        }

        public static int Compare(Int64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle));
        }

        public static int Compare(UBigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle));
        }

        public static int Compare(BigInt u, UInt32 v)
        {
            return (EngineObject.Compare(u.Handle, v));
        }

        public static int Compare(BigInt u, UInt64 v)
        {
            return (EngineObject.Compare(u.Handle, v));
        }

        public static int Compare(BigInt u, Int32 v)
        {
            return (EngineObject.Compare(u.Handle, v));
        }

        public static int Compare(BigInt u, Int64 v)
        {
            return (EngineObject.Compare(u.Handle, v));
        }

        public static int Compare(BigInt u, UBigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle));
        }

        public static int Compare(BigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle));
        }

        public static bool operator >(UInt32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) > 0);
        }

        public static bool operator >(UInt64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) > 0);
        }

        public static bool operator >(Int32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) > 0);
        }

        public static bool operator >(Int64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) > 0);
        }

        public static bool operator >(UBigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) > 0);
        }

        public static bool operator >(BigInt u, UInt32 v)
        {
            return (EngineObject.Compare(u.Handle, v) > 0);
        }

        public static bool operator >(BigInt u, UInt64 v)
        {
            return (EngineObject.Compare(u.Handle, v) > 0);
        }

        public static bool operator >(BigInt u, Int32 v)
        {
            return (EngineObject.Compare(u.Handle, v) > 0);
        }

        public static bool operator >(BigInt u, Int64 v)
        {
            return (EngineObject.Compare(u.Handle, v) > 0);
        }

        public static bool operator >(BigInt u, UBigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) > 0);
        }

        public static bool operator >(BigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) > 0);
        }

        public static bool operator >=(UInt32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) >= 0);
        }

        public static bool operator >=(UInt64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) >= 0);
        }

        public static bool operator >=(Int32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) >= 0);
        }

        public static bool operator >=(Int64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) >= 0);
        }

        public static bool operator >=(UBigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) >= 0);
        }

        public static bool operator >=(BigInt u, UInt32 v)
        {
            return (EngineObject.Compare(u.Handle, v) >= 0);
        }

        public static bool operator >=(BigInt u, UInt64 v)
        {
            return (EngineObject.Compare(u.Handle, v) >= 0);
        }

        public static bool operator >=(BigInt u, Int32 v)
        {
            return (EngineObject.Compare(u.Handle, v) >= 0);
        }

        public static bool operator >=(BigInt u, Int64 v)
        {
            return (EngineObject.Compare(u.Handle, v) >= 0);
        }

        public static bool operator >=(BigInt u, UBigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) >= 0);
        }

        public static bool operator >=(BigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) >= 0);
        }

        public static bool operator <(UInt32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) < 0);
        }

        public static bool operator <(UInt64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) < 0);
        }

        public static bool operator <(Int32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) < 0);
        }

        public static bool operator <(Int64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) < 0);
        }

        public static bool operator <(UBigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) < 0);
        }

        public static bool operator <(BigInt u, UInt32 v)
        {
            return (EngineObject.Compare(u.Handle, v) < 0);
        }

        public static bool operator <(BigInt u, UInt64 v)
        {
            return (EngineObject.Compare(u.Handle, v) < 0);
        }

        public static bool operator <(BigInt u, Int32 v)
        {
            return (EngineObject.Compare(u.Handle, v) < 0);
        }

        public static bool operator <(BigInt u, Int64 v)
        {
            return (EngineObject.Compare(u.Handle, v) < 0);
        }

        public static bool operator <(BigInt u, UBigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) < 0);
        }

        public static bool operator <(BigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) < 0);
        }

        public static bool operator <=(UInt32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) <= 0);
        }

        public static bool operator <=(UInt64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) <= 0);
        }

        public static bool operator <=(Int32 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) <= 0);
        }

        public static bool operator <=(Int64 u, BigInt v)
        {
            return (EngineObject.Compare(u, v.Handle) <= 0);
        }

        public static bool operator <=(UBigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) <= 0);
        }

        public static bool operator <=(BigInt u, UInt32 v)
        {
            return (EngineObject.Compare(u.Handle, v) <= 0);
        }

        public static bool operator <=(BigInt u, UInt64 v)
        {
            return (EngineObject.Compare(u.Handle, v) <= 0);
        }

        public static bool operator <=(BigInt u, Int32 v)
        {
            return (EngineObject.Compare(u.Handle, v) <= 0);
        }

        public static bool operator <=(BigInt u, Int64 v)
        {
            return (EngineObject.Compare(u.Handle, v) <= 0);
        }

        public static bool operator <=(BigInt u, UBigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) <= 0);
        }

        public static bool operator <=(BigInt u, BigInt v)
        {
            return (EngineObject.Compare(u.Handle, v.Handle) <= 0);
        }

        #endregion
    }
}


/*
 * END OF FILE
 */