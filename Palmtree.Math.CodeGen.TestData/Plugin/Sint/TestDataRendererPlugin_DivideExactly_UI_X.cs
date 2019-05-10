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

namespace Palmtree.Math.CodeGen.TestData.Plugin.Sint
{
    class TestDataRendererPlugin_DivideExactly_UI_X
        : TestDataRendererPluginBase_2_1
    {
        public TestDataRendererPlugin_DivideExactly_UI_X()
            : base("sint", "test_data_divideexactly_ui_x.xml")
        {

        }

        protected override IEnumerable<BigInteger> AdditionalUBigIntDataSource
        {
            get
            {
                return (new[]
                {
                    (BigInteger)3,
                    BigInteger.Parse("1") << 8,
                    BigInteger.Parse("1") << 16,
                    BigInteger.Parse("1") << 32,
                    BigInteger.Parse("1") << 64,
                    BigInteger.Parse("1") << 128,
                    BigInteger.Parse("1234567890") << 8,
                    BigInteger.Parse("1234567890") << 16,
                    BigInteger.Parse("1234567890") << 32,
                    BigInteger.Parse("1234567890") << 64,
                    BigInteger.Parse("1234567890") << 128,
                    BigInteger.Parse("12345678901234567890") << 8,
                    BigInteger.Parse("12345678901234567890") << 16,
                    BigInteger.Parse("12345678901234567890") << 32,
                    BigInteger.Parse("12345678901234567890") << 64,
                    BigInteger.Parse("12345678901234567890") << 128,
                    BigInteger.Parse("1") * BigInteger.Pow(10, 2),
                    BigInteger.Parse("1") * BigInteger.Pow(10, 4),
                    BigInteger.Parse("1") * BigInteger.Pow(10, 8),
                    BigInteger.Parse("1") * BigInteger.Pow(10, 16),
                    BigInteger.Parse("1") * BigInteger.Pow(10, 32),
                    BigInteger.Parse("1234567890") * BigInteger.Pow(10, 2),
                    BigInteger.Parse("1234567890") * BigInteger.Pow(10, 4),
                    BigInteger.Parse("1234567890") * BigInteger.Pow(10, 8),
                    BigInteger.Parse("1234567890") * BigInteger.Pow(10, 16),
                    BigInteger.Parse("1234567890") * BigInteger.Pow(10, 32),
                    BigInteger.Parse("12345678901234567890") * BigInteger.Pow(10, 2),
                    BigInteger.Parse("12345678901234567890") * BigInteger.Pow(10, 4),
                    BigInteger.Parse("12345678901234567890") * BigInteger.Pow(10, 8),
                    BigInteger.Parse("12345678901234567890") * BigInteger.Pow(10, 16),
                    BigInteger.Parse("12345678901234567890") * BigInteger.Pow(10, 32),
                });
            }
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (UInt32DataSource
                        .SelectMany(p1 => BigIntDataSource, (p1, p2) => new { p1, p2 })
                        .Select(item =>
                        {
                            if (item.p2 == 0)
                                return (new
                                {
                                    p1 = (IDataItem)new UInt32DataItem(item.p1),
                                    p2 = (IDataItem)new BigIntDataItem(item.p2),
                                    r1 = (IDataItem)new ExceptionDataItem(typeof(DivideByZeroException)),
                                });
                            else if (item.p1 % item.p2 != 0)
                                return (new
                                {
                                    p1 = (IDataItem)new UInt32DataItem(item.p1),
                                    p2 = (IDataItem)new BigIntDataItem(item.p2),
                                    r1 = (IDataItem)new ExceptionDataItem(typeof(ArithmeticException)),
                                });
                            else
                                return (new
                                {
                                    p1 = (IDataItem)new UInt32DataItem(item.p1),
                                    p2 = (IDataItem)new BigIntDataItem(item.p2),
                                    r1 = (IDataItem)new BigIntDataItem(item.p1 / item.p2),
                                });
                        })
                        .Zip(Enumerable.Range(0, int.MaxValue),
                             (item, index) => new TestDataItemContainer
                             {
                                 Index = index,
                                 Param1 = item.p1,
                                 Param2 = item.p2,
                                 Result1 = item.r1,
                             }));
            }
        }
    }
}


/*
 * END OF FILE
 */