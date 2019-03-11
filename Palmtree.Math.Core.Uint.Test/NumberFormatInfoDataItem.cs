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


using System.Globalization;

namespace Palmtree.Math.Core.Uint.Test
{
    public class NumberFormatInfoDataItem
        : DataItem
    {
        string _serialized_text;

        public NumberFormatInfoDataItem(string serialized_text, NumberFormatInfo value)
        {
            _serialized_text = serialized_text;
            Value = value;
        }

        public override string Type => "numberformatinfo";

        public NumberFormatInfo Value { get; }

        public override bool IsNumberFormatInfo => true;

        public override NumberFormatInfoDataItem ToNumberFormatInfo()
        {
            return (this);
        }

        public override bool Equals(object o)
        {
            if (o == null)
                return (false);
            if (GetType() != o.GetType())
                return (false);
            return (_serialized_text == ((NumberFormatInfoDataItem)o)._serialized_text);
        }

        public override int GetHashCode()
        {
            return (_serialized_text.GetHashCode());
        }

        public override string ToSummaryString()
        {
            return (string.Format("<{0}>", _serialized_text));
        }
    }
}


/*
 * END OF FILE
 */