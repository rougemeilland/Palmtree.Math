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
using System.Numerics;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    public class UInt32DataItem
        : DataItem
    {
        public UInt32DataItem(UInt32 value)
        {
            Value = value;
        }

        public UInt32DataItem(BigInteger value)
        {
            if (value < UInt32.MinValue || value > UInt32.MaxValue)
                throw new ApplicationException();
            Value = (UInt32)value;
        }

        public override string Type => "uint32";

        public UInt32 Value { get; }

        public override bool IsUInt32 => true;

        public override UBigIntDataItem ToUBigInt()
        {
            return (new UBigIntDataItem((BigInteger)Value));
        }

        public override UInt32DataItem ToUInt32()
        {
            return (this);
        }

        public override UInt64DataItem ToUInt64()
        {
            return (new UInt64DataItem((UInt64)Value));
        }

        public override XStringDataItem ToXString()
        {
            return (new XStringDataItem(Value.ToString()));
        }

        public override bool Equals(object o)
        {
            if (o == null)
                return (false);
            if (GetType() != o.GetType())
                return (false);
            return (Value == ((UInt32DataItem)o).Value);
        }

        public override int GetHashCode()
        {
            return (Value.GetHashCode());
        }

        protected override string SerializeValue()
        {
            return (Value.ToString());
        }
    }
}


/*
 * END OF FILE
 */