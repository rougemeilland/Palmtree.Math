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


using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.CodeGen.TestData.Plugin.Rtnl
{
    class TestDataRendererPlugin_From_DECIMAL
        : TestDataRendererPluginBase_1_1
    {
        public TestDataRendererPlugin_From_DECIMAL()
            : base("rtnl", "test_data_from_decimal.xml")
        {
        }

        private IEnumerable<decimal> DecimalDataSource
        {
            get
            {
                return (new[]
                {
                    new decimal(1, 0, 0, true, 28),
                    new decimal(1, 0, 0, false, 28),
                    0m,
                    12.345m,
                    -12.345m,
                    123450m,
                    -123450m,
                    0.012345m,
                    -0.012345m,
                    decimal.MaxValue,
                    decimal.MinValue,
                }
                .OrderBy(d => d));
            }
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (DecimalDataSource
                        .Select(p1 => new
                        {
                            p1 = (IDataItem)new DecimalDataItem(p1),
                            r1 = (IDataItem)new RationalDataItem(MiniRational.From(p1)),
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