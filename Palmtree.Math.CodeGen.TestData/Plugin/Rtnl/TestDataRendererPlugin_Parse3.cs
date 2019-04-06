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
using System.Globalization;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.CodeGen.TestData.Plugin.Rtnl
{
    // TryParse: 小数の動作に着目したテストデータ
    class TestDataRendererPlugin_Parse3
        : TestDataRendererPluginBase_3_1
    {
        public TestDataRendererPlugin_Parse3()
            : base("rtnl", "test_data_parse3.xml")
        {

        }

        private IEnumerable<string> StringDataSource
        {
            get
            {
                var exponents = new[]
                {
                    "",
                    "e0",
                    "E0",
                    "e5",
                    "E5",
                    "e+5",
                    "E+5",
                    "e-5",
                    "E-5",
                    "e+1234",
                    "E+1234",
                };
                var values = new[]
                {
                    "",
                    "0",
                    ".0",
                    "0.",
                    "123.",
                    "123.00",
                    "123.45",
                    "123.50",
                    "123.65",
                    "999.999999999",
                    "12345",
                    "12,345",
                };
                var number_format = CultureInfo.InvariantCulture.NumberFormat;
                var signs = new[] { number_format.PositiveSign, number_format.NegativeSign };
                //var leading_spaces = new[] { "", " " };
                //var trailing_spaces = new[] { "", " " };
                var currency_symbol = number_format.CurrencySymbol;

                return (values
                        .SelectMany(value => exponents, (value, exponent) => value + exponent)
                        .Distinct());
            }
        }

        private IEnumerable<NumberStyles> NumberStyleDataSource
        {
            get
            {
                return (new[] { NumberStyles.None, NumberStyles.AllowLeadingSign }
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowTrailingSign }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowLeadingWhite }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowTrailingWhite }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowThousands }, (flag1, flag2) => flag1 | flag2)
                        .SelectMany(flag => new[] { NumberStyles.None, NumberStyles.AllowDecimalPoint }, (flag1, flag2) => flag1 | flag2));
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
                                            var r1 = MiniRational.Parse(item.p1, item.p2, p3.NumberFormat);
                                            return (new
                                            {
                                                p1 = (IDataItem)new XStringDataItem(item.p1),
                                                p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                r1 = (IDataItem)new RationalDataItem(r1),
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