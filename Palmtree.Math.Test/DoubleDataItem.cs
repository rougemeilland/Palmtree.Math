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


using System.Globalization;
using System.Linq;

namespace Palmtree.Math.Test
{
    public class DoubleDataItem
        : DataItem
    {
        public DoubleDataItem(double value)
        {
            Value = value;
        }

        public override string Type => "double";

        public double Value { get; }

        public override bool IsDouble => true;

        public override DoubleDataItem ToDouble()
        {
            return (this);
        }

        public override bool Equals(object o)
        {
            if (o == null)
                return (false);
            if (GetType() != o.GetType())
                return (false);
            var delta1 = System.Math.Max(System.Math.Abs(Value) / (1L << 48), 2.2250738585072014e-308 * 2);
            var delta2 = System.Math.Max(System.Math.Abs(((DoubleDataItem)o).Value) / (1L << 48), 2.2250738585072014e-308 * 2);
            double delta;
            if (delta1 > 0)
            {
                if (delta2 > 0)
                    delta = System.Math.Min(delta1, delta2);
                else
                    delta = delta1;
            }
            else
            {
                if (delta2 > 0)
                    delta = delta2;
                else
                    delta = 0.0d;
            }
            return (System.Math.Abs(Value - ((DoubleDataItem)o).Value) <= delta);
        }

        public override int GetHashCode()
        {
            return (Value.GetHashCode());
        }

        public override string ToSummaryString()
        {
            return (string.Format("{0:g17}d", Value));
        }
    }
}


/*
 * END OF FILE
 */