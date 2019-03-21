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

namespace Palmtree.Math.CodeGen.TestData.Plugin.Uint
{
    class TestDataRendererPlugin_Increment_X
        : TestDataRendererPluginBase_1_1
    {
        public TestDataRendererPlugin_Increment_X()
            : base("uint", "test_data_increment_x.xml")
        {

        }

        protected override IEnumerable<BigInteger> AdditionalUBigIntDataSource
        {
            get
            {
                return (new[]
                {
                    BigInteger.Zero,
                    BigInteger.One,
                    (BigInteger.One << 32) - 1,
                    BigInteger.One << 32,
                    (BigInteger.One << 64) - 1,
                    BigInteger.One << 64,
                });
            }
        }

        private static UInt32 FloorLog10(BigInteger x)
        {
            UInt32 count = 0;
            while (x > 0)
            {
                x /= 10;
                ++count;
            }
            return (count - 1);
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (UBigIntDataSource
                        .Select(p1 =>
                        {
                            return (new
                            {
                                p1 = (IDataItem)new UBigIntDataItem(p1),
                                r1 = (IDataItem)new UBigIntDataItem(p1 + 1),
                            });
                        })
                        .Zip(Enumerable.Range(0, int.MaxValue),
                             (item, index) => new TestDataItemContainer
                             {
                                 Index = index,
                                 Param1 = item.p1,
                                 Result1 = item.r1,
                             }));
            }
        }
    }
}


/*
 * END OF FILE
 */