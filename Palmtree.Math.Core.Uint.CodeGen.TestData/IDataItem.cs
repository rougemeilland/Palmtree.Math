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


using System.Xml;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    public interface IDataItem
    {
        string Type { get; }
        NullDataItem ToNull();
        UBigIntDataItem ToUBigInt();
        Int32DataItem ToInt32();
        UInt32DataItem ToUInt32();
        UInt64DataItem ToUInt64();
        XStringDataItem ToXString();
        NumberFormatInfoDataItem ToNumberFormatInfo();
        ExceptionDataItem ToException();
        bool IsNull { get; }
        bool IsUBigInt { get; }
        bool IsInt32 { get; }
        bool IsUInt32 { get; }
        bool IsUInt64 { get; }
        bool IsXString { get; }
        bool IsNumberFormatInfo { get; }
        bool IsException { get; }
        XmlElement ToXmlElement(XmlDocument document, string name);
    }
}


/*
 * END OF FILE
 */