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
using System.Globalization;
using System.Linq;
using System.Numerics;


namespace Palmtree.Math.CodeGen.TestData.Plugin.Uint
{
    class TestDataRendererPlugin_ToStringR
        : TestDataRendererPluginBase_3_1
    {
        public TestDataRendererPlugin_ToStringR()
            : base("uint", "test_data_tostringr.xml")
        {

        }

        private IEnumerable<BigInteger> NumberDataSource
        {
            get
            {
                return (new[] { 0UL, 12UL, 12345UL, 123456789UL }.Select(n => (BigInteger)n));
            }
        }

        private IEnumerable<string> FormatDataSource
        {
            get
            {
                return (new[] { "r", "R" }
                             .SelectMany(type => new[] { -1, 0, 5, 10 }, (type, width) => string.Format("{0}{1}", type, width >= 0 ? width.ToString() : "")));
            }
        }

        private IEnumerable<CultureInfo> CultureDataSource
        {
            get
            {
                return (new[] { "ja-JP" }
                        .Select(item => CultureInfo.CreateSpecificCulture(item)));
            }
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (NumberDataSource
                        .SelectMany(p1 => FormatDataSource, (p1, p2) => new { p1, p2 })
                        .SelectMany(item => CultureDataSource,
                                    (item, p3) =>
                                    {
                                        return (new
                                        {
                                            p1 = (IDataItem)new UBigIntDataItem(item.p1),
                                            p2 = (IDataItem)new XStringDataItem(item.p2),
                                            p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                            // 精度指定子は無視されるのが仕様的には正しいのでそのようなテストデータを作る
                                            r1 = (IDataItem)new XStringDataItem(item.p1.ToString(item.p2.Substring(0, 1), p3.NumberFormat)),
                                        });
                                    })
                        .Zip(Enumerable.Range(0, int.MaxValue),
                             (item, index) => new TestDataItemContainer
                             {
                                 Index = index,
                                 Param1 = item.p1,
                                 Param2 = item.p2,
                                 Param3 = item.p3,
                                 Result1 = item.r1,
                             }));
            }
        }
    }
}


/*
 * END OF FILE
 */