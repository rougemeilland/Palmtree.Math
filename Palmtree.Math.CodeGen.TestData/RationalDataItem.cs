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
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.CodeGen.TestData
{
    public class RationalDataItem
        : DataItem
    {
        public RationalDataItem(MiniRational x)
        {
            NumeratorValue = x.Numerator;
            DenominatorValue = x.Denominator;
        }

        public override string Type => "rational";

        public BigInteger NumeratorValue { get; }
        public BigInteger DenominatorValue { get; }

        public override bool IsRational => true;

        public override RationalDataItem ToRational()
        {
            return (this);
        }

        public override XStringDataItem ToXString()
        {
            return (new XStringDataItem(string.Format("{0}/{1}", NumeratorValue, DenominatorValue)));
        }

        public override bool Equals(object o)
        {
            if (o == null)
                return (false);
            if (GetType() != o.GetType())
                return (false);
            return (NumeratorValue == ((RationalDataItem)o).NumeratorValue && DenominatorValue == ((RationalDataItem)o).DenominatorValue);
        }

        public override int GetHashCode()
        {
            return (NumeratorValue.GetHashCode() ^ DenominatorValue.GetHashCode());
        }

        protected override string SerializeValue()
        {
            return (string.Join(",", FromRationalToByteArray(NumeratorValue, DenominatorValue).Select(n => string.Format("{0:x02}", n))));
        }
    }
}


/*
 * END OF FILE
 */