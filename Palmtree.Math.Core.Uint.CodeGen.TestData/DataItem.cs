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
using System.Xml;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    public abstract class DataItem
        : IDataItem
    {
        public abstract string Type { get; }

        public virtual bool IsNull => false;

        public virtual bool IsUBigInt => false;

        public virtual bool IsInt32 => false;

        public virtual bool IsUInt32 => false;

        public virtual bool IsUInt64 => false;

        public virtual bool IsXString => false;

        public virtual bool IsNumberFormatInfo => false;

        public virtual bool IsException => false;

        public virtual NullDataItem ToNull()
        {
            throw new InvalidCastException();
        }

        public virtual UBigIntDataItem ToUBigInt()
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
    }
}


/*
 * END OF FILE
 */