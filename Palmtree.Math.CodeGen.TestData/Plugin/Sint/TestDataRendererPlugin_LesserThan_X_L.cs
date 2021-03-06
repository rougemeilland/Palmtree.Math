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


using System;
using System.Collections.Generic;
using System.Linq;

namespace Palmtree.Math.CodeGen.TestData.Plugin.Sint
{
    class TestDataRendererPlugin_LesserThan_X_L
        : TestDataRendererPluginBase_2_1
    {
        public TestDataRendererPlugin_LesserThan_X_L()
            : base("sint", "test_data_lesserthan_x_l.xml")
        {

        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (BigIntDataSource
                        .SelectMany(p1 => Int64DataSource,
                                    (p1, p2) => new
                                    {
                                        p1 = (IDataItem)new BigIntDataItem(p1),
                                        p2 = (IDataItem)new Int64DataItem(p2),
                                        r1 = (IDataItem)new UInt32DataItem(p1 < p2 ? 1U : 0U),
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