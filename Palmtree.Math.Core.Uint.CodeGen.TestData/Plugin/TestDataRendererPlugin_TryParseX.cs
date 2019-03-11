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
    // TryParse: 16進数文字列に着目したテストデータ
    class TestDataRendererPlugin_TryParseX
        : TestDataRendererPluginBase_3_2
    {
        public TestDataRendererPlugin_TryParseX()
            : base("test_data_tryparsex.xml")
        {

        }

        private IEnumerable<string> StringDataSource
        {
            get
            {
                var b = "123456789abcdef0";
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
                    b.Substring(0, 4),
                    b.Substring(0, 7),
                    b.Substring(5, 8),
                    b.Substring(10, 9),
                    b.Substring(0, 15),
                    b.Substring(5, 16),
                    b.Substring(10, 17),
                    b.Substring(0, 31),
                    b.Substring(5, 32),
                    b.Substring(10, 33),
                    b.Substring(0, 63),
                    b.Substring(5, 64),
                    b.Substring(10, 65),
                    b.Substring(0, 127),
                    b.Substring(5, 128),
                    b.Substring(10, 129),
                }, (format, i) => new { format, i })
                .SelectMany(item => new[]
                {
                    "",
                    "0",
                    "00",
                    "0000",
                    "00000000",
                    "0000000000000000",
                    "00000000000000000000000000000000",
                    "f",
                    "ff",
                    "ffff",
                    "ffffffff",
                    "ffffffffffffffff",
                    "ffffffffffffffffffffffffffffffff",
                }, (item, zero) => new { item.format, item.i, zero })
                .Select(item => string.Format(item.format, item.zero, item.i))
                .SelectMany(item => new[] { item.ToLower(), item.ToUpper() })
                .Distinct()
                .OrderBy(item => item.Length)
                .ThenBy(item => item)
                .ToArray());
            }
        }

        private IEnumerable<NumberStyles> NumberStyleDataSource
        {
            get
            {
                return (new[]
                {
                    NumberStyles.AllowHexSpecifier,
                    NumberStyles.AllowHexSpecifier | NumberStyles.AllowLeadingWhite,
                    NumberStyles.AllowHexSpecifier | NumberStyles.AllowTrailingWhite,
                    NumberStyles.AllowHexSpecifier | NumberStyles.AllowLeadingWhite | NumberStyles.AllowTrailingWhite,
                });
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

        private static string 符号なし整数に変換(string s)
        {
            s = s
                .Replace(" 8", " 08")
                .Replace(" 9", " 09")
                .Replace(" a", " 0a")
                .Replace(" b", " 0b")
                .Replace(" c", " 0c")
                .Replace(" d", " 0d")
                .Replace(" e", " 0e")
                .Replace(" f", " 0f")
                .Replace(" A", " 0A")
                .Replace(" B", " 0B")
                .Replace(" C", " 0C")
                .Replace(" D", " 0D")
                .Replace(" E", " 0E")
                .Replace(" F", " 0F");
            if ("89abcdefABCDEF".Contains(s[0]))
                s = "0" + s;
            return (s);
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
                                            BigInteger r2;
                                            var r1 = BigInteger.TryParse(符号なし整数に変換(item.p1), item.p2, p3.NumberFormat, out r2);
                                            if (r1 && r2 < 0)
                                            {
                                                return (new
                                                {
                                                    p1 = (IDataItem)new XStringDataItem(item.p1),
                                                    p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                    p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                    r1 = (IDataItem)new ExceptionDataItem(typeof(OverflowException)),
                                                    r2 = (IDataItem)new NullDataItem(),
                                                });
                                            }
                                            else
                                            {
                                                return (new
                                                {
                                                    p1 = (IDataItem)new XStringDataItem(item.p1),
                                                    p2 = (IDataItem)new Int32DataItem((int)item.p2),
                                                    p3 = (IDataItem)new NumberFormatInfoDataItem(p3),
                                                    r1 = (IDataItem)new UInt32DataItem(r1 ? 1 : 0),
                                                    r2 = (IDataItem)new UBigIntDataItem(r2),
                                                });
                                            }
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