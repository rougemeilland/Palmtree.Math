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
using System.Globalization;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData.Plugin
{
    // TryParse: カルチャの違いによる動作に着目したテストデータ
    class TestDataRendererPlugin_TryParseDN1
        : TestDataRendererPluginBase_3_2
    {
        public TestDataRendererPlugin_TryParseDN1()
            : base("test_data_tryparsedn1.xml")
        {

        }

        private IEnumerable<string> StringDataSource
        {
            get
            {
                return (new[]
                {
                    "",
                    "1234567890",
                    "1\u0020234\u0020567\u0020890",
                    "1\u00a0234\u00a0567\u00a0890",
                    "1,234,567,890",
                    "1.234.567.890",
                }
                .SelectMany(item => new[]
                {
                    "{0}{1}",
                    "({0}{1})",
                    "+{0}{1}",
                    "-{0}{1}",
                    "{0}{1}+",
                    "{0}{1}-",
                }, (int_part, sign_format) => new { int_part, sign_format })
                .SelectMany(item => new[]
                {
                    "",
                    ".",
                    ".00",
                    ",00",
                    ".54",
                    ",54",
                }, (item, frac_part) => new { item.int_part, item.sign_format, frac_part })
                .Select(item => string.Format(item.sign_format, item.int_part, item.frac_part)));
            }
        }

        private IEnumerable<NumberStyles> NumberStyleDataSource
        {
            get
            {
                return (new[] { NumberStyles.None, NumberStyles.AllowLeadingSign }
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowTrailingSign }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowParentheses }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowThousands }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowDecimalPoint }, (flag1, flag2) => flag1 | flag2));
            }
        }

        private IEnumerable<CultureInfo> CultureInfoDataSource
        {
            get
            {
                return (new[] { "ja-JP", "fr-FR", "de-DE" }
                        .Select(name => CultureInfo.CreateSpecificCulture(name)));
            }
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                return (StringDataSource
                        .SelectMany(p1 => NumberStyleDataSource, (p1, p2) => new { p1, p2 })
                        .SelectMany(item => CultureInfoDataSource,
                                    (item, p3) =>
                                    {
                                        try
                                        {
                                            UInt64 r2;
                                            var r1 = UInt64.TryParse(item.p1, item.p2, p3.NumberFormat, out r2);
                                            return (new
                                            {
                                                p1 = (IDataItem)new XStringDataItem(item.p1),
                                                p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                r1 = (IDataItem)new UInt32DataItem(r1 ? 1 : 0),
                                                r2 = (IDataItem)new UBigIntDataItem(r2),
                                            });
                                        }
                                        catch (Exception ex)
                                        {
                                            return (new
                                            {
                                                p1 = (IDataItem)new XStringDataItem(item.p1),
                                                p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                r1 = (IDataItem)new ExceptionDataItem(ex.GetType()),
                                                r2 = (IDataItem)new NullDataItem(),
                                            });
                                        }
                                    })
                        .Zip(Enumerable.Range(0, int.MaxValue),
                             (item, index) => new TestDataItemContainer
                             {
                                 Index = index,
                                 Param1 = item.p1,
                                 Param2 = item.p2,
                                 Param3 = item.p3,
                                 Result1 = item.r1,
                                 Result2 = item.r2,
                             }));
            }
        }
    }
}


/*
 * END OF FILE
 */