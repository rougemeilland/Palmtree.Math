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


namespace Palmtree.Math.CodeGen.TestData.Plugin.Rtnl
{
    class TestDataRendererPlugin_Invert_R
        : TestDataRendererPluginBase_1_1
    {
        public TestDataRendererPlugin_Invert_R()
            : base("rtnl", "test_data_invert_r.xml")
        {

        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (RationalDataSource
                        .Select(p1 =>
                        {
                            if (p1 == 0)
                            {
                                return (new
                                {
                                    p1 = (IDataItem)new RationalDataItem(p1),
                                    r1 = (IDataItem)new ExceptionDataItem(typeof(DivideByZeroException)),
                                });
                            }
                            else
                            {
                                return (new
                                {
                                    p1 = (IDataItem)new RationalDataItem(p1),
                                    r1 = (IDataItem)new RationalDataItem(MiniRational.Invert(p1)),
                                });
                            }
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