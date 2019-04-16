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


using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.CodeGen.TestData.Plugin.Rtnl
{
    class TestDataRendererPlugin_ToStringCustom1
        : TestDataRendererPluginBase_3_1
    {
        public TestDataRendererPlugin_ToStringCustom1()
            : base("rtnl", "test_data_tostringcustom1.xml")
        {
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                var source = new[]
                {
                    new { value = -12.345d, format = @"#0.0#;(#0.0#)", culture = "ja-JP" },
                    new { value = -12.345d, format = @"#0.0#;(#0.0#);-\0-", culture = "ja-JP" },
                    new { value = 0d, format = @"#0.0#;(#0.0#)", culture = "ja-JP" },
                    new { value = 0d, format = @"#0.0#;(#0.0#);-\0-", culture = "ja-JP" },
                    new { value = 0.03697d, format = @"#0.00‰", culture = "ja-JP" },
                    new { value = 0.03697d, format = @"#0.00‰", culture = "ru-RU" },
                    new { value = 0.3697d, format = @"##.0 %", culture = "el-GR" },
                    new { value = 0.3697d, format = @"##.0 %", culture = "ja-JP" },
                    new { value = 0.3697d, format = @"%#0.00", culture = "el-GR" },
                    new { value = 0.3697d, format = @"%#0.00", culture = "ja-JP" },
                    new { value = 0.45678d, format = @"#.##", culture = "ja-JP" },
                    new { value = 0.45678d, format = @"#.##", culture = "fr-FR" },
                    new { value = 0.45678d, format = @"0.00", culture = "ja-JP" },
                    new { value = 0.45678d, format = @"0.00", culture = "fr-FR" },
                    new { value = 1.8901385E-16d, format = @"0.0e+00", culture = "ja-JP" },
                    new { value = 12.345d, format = @"#0.0#;(#0.0#)", culture = "ja-JP" },
                    new { value = 12.345d, format = @"#0.0#;(#0.0#);-\0-", culture = "ja-JP" },
                    new { value = 1234.5678d, format = @"#####", culture = "ja-JP" },
                    new { value = 1234.5678d, format = @"00000", culture = "ja-JP" },
                    new { value = 1503.92311d, format = @"0.0##e+00", culture = "ja-JP" },
                    new { value = 2147483647d, format = @"##,#", culture = "ja-JP" },
                    new { value = 2147483647d, format = @"##,#", culture = "es-ES" },
                    new { value = 2147483647d, format = @"#,#,,", culture = "ja-JP" },
                    new { value = 2147483647d, format = @"#,#,,", culture = "es-ES" },
                    new { value = 68d, format = @"# 'degrees'", culture = "ja-JP" },
                    new { value = 68d, format = @"# °", culture = "ja-JP" },
                    new { value = 68d, format = @"#' degrees'", culture = "ja-JP" },
                    new { value = 987654d, format = @"#0.0e0", culture = "ja-JP" },
                    new { value = 987654d, format = @"\###00\#", culture = "ja-JP" },
                    new { value = 123d, format = "00000", culture = "ja-JP" },
                    new { value = 1.2d, format = "0.00", culture = "ja-JP" },
                    new { value = 1.2d, format = "00.00", culture = "ja-JP" },
                    new { value = 1.2d, format = "00.00", culture = "fr-FR" },
                    new { value = .56d, format = "0.0", culture = "ja-JP" },
                    new { value = 1234567890d, format = "0,0", culture = "ja-JP" },
                    new { value = 1234567890d, format = "0,0", culture = "fr-FR" },
                    new { value = 1234567890.123456d, format = "0,0.0", culture = "ja-JP" },
                    new { value = 1234.567890d, format = "0,0.00", culture = "ja-JP" },
                    new { value = 1.2d, format = "#.##", culture = "ja-JP" },
                    new { value = 123d, format = "#####", culture = "ja-JP" },
                    new { value = 123456d, format = "[##-##-##]", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#", culture = "ja-JP" },
                    new { value = 1234567890d, format = "(###) ###-####", culture = "ja-JP" },
                    new { value = 1.2d, format = "0.00", culture = "ja-JP" },
                    new { value = 1.2d, format = "00.00", culture = "ja-JP" },
                    new { value = 1.2d, format = "00.00", culture = "fr-FR" },
                    new { value = .086d, format = "#0.##%", culture = "ja-JP" },
                    new { value = 86000d, format = "0.###E+0", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#,#", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#,##0,,", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#,,", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#,,,", culture = "ja-JP" },
                    new { value = 1234567890d, format = "#,##0,,", culture = "ja-JP" },
                    new { value = .086d, format = "#0.##%", culture = "ja-JP" },
                    new { value = .00354d, format = "#0.## ‰", culture = "ja-JP" },
                    new { value = 86000d, format = "0.###E+0", culture = "ja-JP" },
                    new { value = 86000d, format = "0.###E+000", culture = "ja-JP" },
                    new { value = 86000d, format = "0.###E-000", culture = "ja-JP" },
                    new { value = 123d, format = "\\#\\#\\# ##0 dollars and \\0\\0 cents \\#\\#\\#", culture = "ja-JP" },
                    new { value = 123d, format = @"\#\#\# ##0 dollars and \0\0 cents \#\#\#", culture = "ja-JP" },
                    new { value = 123d, format = "\\\\\\\\\\\\ ##0 dollars and \\0\\0 cents \\\\\\\\\\\\", culture = "ja-JP" },
                    new { value = 123d, format = @"\\\\\\ ##0 dollars and \0\0 cents \\\\\\", culture = "ja-JP" },
                    new { value = 1234d, format = "##;(##);**Zero**", culture = "ja-JP" },
                    new { value = -1234d, format = "##;(##);**Zero**", culture = "ja-JP" },
                    new { value = 0d, format = "##;(##);**Zero**", culture = "ja-JP" },
                };
                return (source
                        .Select(item => new { p1 = item.value, p2 = item.format, p3 = CultureInfo.GetCultureInfo(item.culture) })
                        .Select(item =>
                                    {
                                        return (new
                                        {
                                            p1 = (IDataItem)new RationalDataItem(item.p1),
                                            p2 = (IDataItem)new XStringDataItem(item.p2),
                                            p3 = (IDataItem)new NumberFormatInfoDataItem(item.p3),
                                            r1 = (IDataItem)new XStringDataItem(item.p1.ToString(item.p2, item.p3.NumberFormat)),
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