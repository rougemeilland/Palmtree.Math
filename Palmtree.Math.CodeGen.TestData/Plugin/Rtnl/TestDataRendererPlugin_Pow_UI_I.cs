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
using System;
using System.Numerics;

namespace Palmtree.Math.CodeGen.TestData.Plugin.Rtnl
{
    class TestDataRendererPlugin_Pow_UI_I
        : TestDataRendererPluginBase_2_1
    {
        public TestDataRendererPlugin_Pow_UI_I()
            : base("rtnl", "test_data_pow_ui_i.xml")
        {

        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (UInt32DataSource
                        .SelectMany(p1 => ExponentDataSource,
                                    (p1, p2) =>
                                    {
                                        if (p1 == 0 && p2 == 0)
                                        {
                                            return (new
                                            {
                                                p1 = (IDataItem)new UInt32DataItem(p1),
                                                p2 = (IDataItem)new Int32DataItem(p2),
                                                r1 = (IDataItem)new ExceptionDataItem(typeof(ArithmeticException)),
                                            });
                                        }
                                        else if (p1 == 0 && p2 < 0)
                                        {
                                            return (new
                                            {
                                                p1 = (IDataItem)new UInt32DataItem(p1),
                                                p2 = (IDataItem)new Int32DataItem(p2),
                                                r1 = (IDataItem)new ExceptionDataItem(typeof(DivideByZeroException)),
                                            });
                                        }
                                        else
                                        {
                                            return (new
                                            {
                                                p1 = (IDataItem)new UInt32DataItem(p1),
                                                p2 = (IDataItem)new Int32DataItem(p2),
                                                r1 = (IDataItem)new RationalDataItem(MiniRational.Pow(p1, p2)),
                                            });
                                        }
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