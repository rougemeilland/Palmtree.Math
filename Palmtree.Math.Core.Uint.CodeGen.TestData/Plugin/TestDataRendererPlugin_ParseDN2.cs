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
    // Parse: 基本的な文字列⇒整数変換に着目したテストデータ
    class TestDataRendererPlugin_ParseDN2
        : TestDataRendererPluginBase_3_1
    {
        public TestDataRendererPlugin_ParseDN2()
            : base("test_data_parsedn2.xml")
        {

        }

        private IEnumerable<string> StringDataSource
        {
            get
            {
                var b = "1234567890";
                b = b + b;
                b = b + b;
                b = b + b;
                b = b + b;
                b = b + b;
                b = b + b;
                return (new[]
                {
                    "{0}{1}",
                    "  {0}{1}",
                    "{0}{1}  ",
                    "  {0}{1}  ",
                }
                .SelectMany(item => new[]
                {
                    b.Substring(0, 5),
                    b.Substring(0, 8),
                    b.Substring(0, 9),
                    b.Substring(0, 10),
                    b.Substring(0, 18),
                    b.Substring(0, 19),
                    b.Substring(0, 20),
                    b.Substring(0, 37),
                    b.Substring(0, 38),
                    b.Substring(0, 39),
                    b.Substring(0, 76),
                    b.Substring(0, 77),
                    b.Substring(0, 78),
                    b.Substring(0, 153),
                    b.Substring(0, 154),
                    b.Substring(0, 155),
                }, (space_format, int_part) => new { space_format, int_part })
                .SelectMany(item => new[]
                {
                    "",
                    "0",
                    "00",
                    "0000",
                    "00000000",
                    "0000000000000000",
                    "00000000000000000000000000000000",
                }, (item, leading_zeros) => new { item.space_format, item.int_part, leading_zeros })
                .Select(item => string.Format(item.space_format, item.leading_zeros, item.int_part)));
            }
        }

        private IEnumerable<NumberStyles> NumberStyleDataSource
        {
            get
            {
                return (new[] { NumberStyles.None, NumberStyles.AllowLeadingSign }
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowLeadingWhite }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowTrailingWhite }, (flag1, flag2) => flag1 | flag2));
            }
        }

        private IEnumerable<CultureInfo> CultureInfoDataSource
        {
            get
            {
                return (new[] { "" }
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
                                            var r1 = BigInteger.Parse(item.p1, item.p2, p3.NumberFormat);
                                            return (new
                                            {
                                                p1 = (IDataItem)new XStringDataItem(item.p1),
                                                p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                r1 = (IDataItem)new UBigIntDataItem(r1),
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
                             }));
            }
        }
    }
}


/*
 * END OF FILE
 */