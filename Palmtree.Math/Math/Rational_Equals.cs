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
    partial class Rational
    {
        #region パブリックメソッド

        public bool Equals(Int32 v)
        {
            return (EngineObject.Equals(Handle, v));
        }

        public bool Equals(Int64 v)
        {
            return (EngineObject.Equals(Handle, v));
        }

        public bool Equals(BigInt v)
        {
            return (EngineObject.Equals(Handle, v.Handle));
        }

        public bool Equals(UInt32 v)
        {
            return (EngineObject.Equals(Handle, v));
        }

        public bool Equals(UInt64 v)
        {
            return (EngineObject.Equals(Handle, v));
        }

        public bool Equals(UBigInt v)
        {
            return (EngineObject.Equals(Handle, v.Handle));
        }

        public bool Equals(Rational v)
        {
            return (EngineObject.Equals(Handle, v.Handle));
        }

        public static bool operator ==(Int32 u, Rational v)
        {
            return (EngineObject.Equals(u, v.Handle));
        }

        public static bool operator ==(Int64 u, Rational v)
        {
            return (EngineObject.Equals(u, v.Handle));
        }

        public static bool operator ==(BigInt u, Rational v)
        {
            return (EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator ==(UInt32 u, Rational v)
        {
            return (EngineObject.Equals(u, v.Handle));
        }

        public static bool operator ==(UInt64 u, Rational v)
        {
            return (EngineObject.Equals(u, v.Handle));
        }

        public static bool operator ==(UBigInt u, Rational v)
        {
            return (EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator ==(Rational u, Int32 v)
        {
            return (EngineObject.Equals(u.Handle, v));
        }

        public static bool operator ==(Rational u, Int64 v)
        {
            return (EngineObject.Equals(u.Handle, v));
        }

        public static bool operator ==(Rational u, BigInt v)
        {
            return (EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator ==(Rational u, UInt32 v)
        {
            return (EngineObject.Equals(u.Handle, v));
        }

        public static bool operator ==(Rational u, UInt64 v)
        {
            return (EngineObject.Equals(u.Handle, v));
        }

        public static bool operator ==(Rational u, UBigInt v)
        {
            return (EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator ==(Rational u, Rational v)
        {
            return (EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator !=(Int32 u, Rational v)
        {
            return (!EngineObject.Equals(u, v.Handle));
        }

        public static bool operator !=(Int64 u, Rational v)
        {
            return (!EngineObject.Equals(u, v.Handle));
        }

        public static bool operator !=(BigInt u, Rational v)
        {
            return (!EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator !=(UInt32 u, Rational v)
        {
            return (!EngineObject.Equals(u, v.Handle));
        }

        public static bool operator !=(UInt64 u, Rational v)
        {
            return (!EngineObject.Equals(u, v.Handle));
        }

        public static bool operator !=(UBigInt u, Rational v)
        {
            return (!EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator !=(Rational u, Int32 v)
        {
            return (!EngineObject.Equals(u.Handle, v));
        }

        public static bool operator !=(Rational u, Int64 v)
        {
            return (!EngineObject.Equals(u.Handle, v));
        }

        public static bool operator !=(Rational u, BigInt v)
        {
            return (!EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator !=(Rational u, UInt32 v)
        {
            return (!EngineObject.Equals(u.Handle, v));
        }

        public static bool operator !=(Rational u, UInt64 v)
        {
            return (!EngineObject.Equals(u.Handle, v));
        }

        public static bool operator !=(Rational u, UBigInt v)
        {
            return (!EngineObject.Equals(u.Handle, v.Handle));
        }

        public static bool operator !=(Rational u, Rational v)
        {
            return (!EngineObject.Equals(u.Handle, v.Handle));
        }

        public override bool Equals(object o)
        {
            if (o is Int32)
                return (EngineObject.Equals(Handle, (Int32)o));
            if (o is Int64)
                return (EngineObject.Equals(Handle, (Int64)o));
            if (o is BigInt)
                return (EngineObject.Equals(Handle, ((BigInt)o).Handle));
            if (o is UInt32)
                return (EngineObject.Equals(Handle, (UInt32)o));
            if (o is UInt64)
                return (EngineObject.Equals(Handle, (UInt64)o));
            if (o is UBigInt)
                return (EngineObject.Equals(Handle, ((UBigInt)o).Handle));
            if (o is Rational)
                return (EngineObject.Equals(Handle, ((Rational)o).Handle));
            return (false);
        }

        public override int GetHashCode()
        {
            return (EngineObject.GetHashCode(Handle));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */