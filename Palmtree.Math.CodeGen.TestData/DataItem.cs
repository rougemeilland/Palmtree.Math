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
using System.Linq;
using System.Collections.Generic;
using System.Numerics;
using System.Xml;

namespace Palmtree.Math.CodeGen.TestData
{
    public abstract class DataItem
        : IDataItem
    {
        public abstract string Type { get; }

        public virtual bool IsNull => false;

        public virtual bool IsUInt32 => false;

        public virtual bool IsUInt64 => false;

        public virtual bool IsInt32 => false;

        public virtual bool IsInt64 => false;

        public virtual bool IsUBigInt => false;

        public virtual bool IsBigInt => false;

        public virtual bool IsRational => false;

        public virtual bool IsXString => false;

        public virtual bool IsNumberFormatInfo => false;

        public virtual bool IsException => false;

        public virtual NullDataItem ToNull()
        {
            throw new InvalidCastException();
        }

        public virtual BigIntDataItem ToBigInt()
        {
            throw new InvalidCastException();
        }

        public virtual UBigIntDataItem ToUBigInt()
        {
            throw new InvalidCastException();
        }

        public virtual RationalDataItem ToRational()
        {
            throw new InvalidCastException();
        }

        public virtual Int32DataItem ToInt32()
        {
            throw new InvalidCastException();
        }

        public virtual UInt32DataItem ToUInt32()
        {
            throw new InvalidCastException();
        }

        public virtual Int64DataItem ToInt64()
        {
            throw new InvalidCastException();
        }

        public virtual UInt64DataItem ToUInt64()
        {
            throw new InvalidCastException();
        }

        public virtual XStringDataItem ToXString()
        {
            throw new InvalidCastException();
        }

        public virtual NumberFormatInfoDataItem ToNumberFormatInfo()
        {
            throw new InvalidCastException();
        }

        public virtual ExceptionDataItem ToException()
        {
            throw new InvalidCastException();
        }

        protected abstract string SerializeValue();

        public XmlElement ToXmlElement(XmlDocument document, string name)
        {
            var text = SerializeValue();
            if (text == null)
                return (null);
            var element = document.CreateElement(name);
            element.InnerText = text;
            element.SetAttribute("type", Type);
            return (element);
        }

        protected static byte[] FromBigTintToByteArray(BigInteger value)
        {
            var header = value.Sign > 0 ? (byte)0x01 : value.Sign == 0 ? (byte)0x00 : (byte)0x03;
            var abs = BigInteger.Abs(value);
            var digits = new List<byte>();
            while (abs > 0)
            {
                var digit = abs & 0xff;
                digits.Add((byte)digit);
                abs = abs >> 8;
            }
            var digits_array = digits.ToArray();
            byte[] length_field;
            if (digits_array.LongLength <= 0xff)
            {
                length_field = new[] { (byte)digits_array.LongLength };
                header |= 0x00;
            }
            else if (digits_array.LongLength <= 0xffffL)
            {
                length_field = new[] { (byte)digits_array.LongLength, (byte)(digits_array.LongLength >> 8) };
                header |= 0x04;
            }
            else if (digits_array.LongLength <= 0xffffffffL)
            {
                length_field = new[] { (byte)digits_array.LongLength, (byte)(digits_array.LongLength >> 8), (byte)(digits_array.LongLength >> 16), (byte)(digits_array.LongLength >> 24) };
                header |= 0x08;
            }
            else
            {
                length_field = new[]
                {
                    (byte)digits_array.LongLength, (byte)(digits_array.LongLength >> 8), (byte)(digits_array.LongLength >> 16), (byte)(digits_array.LongLength >> 24),
                    (byte)(digits_array.LongLength >> 32),(byte)(digits_array.LongLength >> 40),(byte)(digits_array.LongLength >> 48),(byte)(digits_array.LongLength >> 56),
                };
                header |= 0x0c;
            }
            return (new[] { header }.Concat(length_field).Concat(digits).ToArray());
        }

        protected static byte[] FromRationalToByteArray(BigInteger numerator, BigInteger denominator)
        {
            return (new[] { (byte)0x10 }.Concat(FromBigTintToByteArray(numerator).Concat(FromBigTintToByteArray(denominator))).ToArray());
        }

    }
}


/*
 * END OF FILE
 */