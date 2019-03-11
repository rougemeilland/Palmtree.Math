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

namespace Palmtree.Math.Core.Uint.CodeGen.TestData.Plugin
{
    class TestDataRendererPlugin_Remainder_X_X
        : TestDataRendererPluginBase_2_1
    {
        public TestDataRendererPlugin_Remainder_X_X()
            : base("test_data_remainder_x_x.xml")
        {

        }

        protected override IEnumerable<BigInteger> AdditionalUBigIntDataSource
        {
            get
            {
                return (new[]
                {
                    new BigInteger(1) << 32,
                    (new BigInteger(1) << 32) + 1,
                    new BigInteger(1) << 64,
                    (new BigInteger(1) << 64) + 1,
                    BigInteger.Parse("99999999999999999999999999999999999999999999999999999999981110534068521419145216000000000000000000000000000000000000892029807941224925661617625565249246047764459999999999999999999999999999999999982159403841175501486773314328474458653301145600000000000000000000000000000000000089202980794122492566123983624661967443066881"),
                    BigInteger.Parse("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"),
                });
            }
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (UBigIntDataSource
                        .SelectMany(p1 => UBigIntDataSource,
                                    (p1, p2) =>
                                    {
                                        if (p2 != 0)
                                            return (new
                                            {
                                                p1 = (IDataItem)new UBigIntDataItem(p1),
                                                p2 = (IDataItem)new UBigIntDataItem(p2),
                                                r1 = (IDataItem)new UBigIntDataItem(p1 % p2),
                                            });
                                        else
                                            return (new
                                            {
                                                p1 = (IDataItem)new UBigIntDataItem(p1),
                                                p2 = (IDataItem)new UBigIntDataItem(p2),
                                                r1 = (IDataItem)new ExceptionDataItem(typeof(DivideByZeroException)),
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