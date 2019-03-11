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

        public static UBigInt From(UInt32 x)
        {
            return (new UBigInt(EngineObject.From(x)));
        }

        public static UBigInt From(UInt64 x)
        {
            return (new UBigInt(EngineObject.From(x)));
        }

        public static explicit operator UBigInt(UInt32 x)
        {
            return (new UBigInt(EngineObject.From(x)));
        }

        public static explicit operator UBigInt(UInt64 x)
        {
            return (new UBigInt(EngineObject.From(x)));
        }

        public UInt32 ToUInt32()
        {
            return (EngineObject.ToUInt32(Handle));
        }

        public UInt64 ToUInt64()
        {
            return (EngineObject.ToUInt64(Handle));
        }

        public static explicit operator UInt32(UBigInt x)
        {
            return (EngineObject.ToUInt32(x.Handle));
        }

        public static explicit operator UInt64(UBigInt x)
        {
            return (EngineObject.ToUInt64(x.Handle));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */