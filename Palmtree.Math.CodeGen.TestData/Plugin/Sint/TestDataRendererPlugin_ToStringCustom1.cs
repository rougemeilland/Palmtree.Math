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

namespace Palmtree.Math.CodeGen.TestData.Plugin.Sint
{
    class TestDataRendererPlugin_ToStringCustom1
        : TestDataRendererPluginBase_3_1
    {
        public TestDataRendererPlugin_ToStringCustom1()
            : base("sint", "test_data_tostringcustom1.xml")
        {
        }

        protected override IEnumerable<TestDataItemContainer> TestDataItems
        {
            get
            {
                var source = new[]
                {
                    new { value = 0L, format = @"#0.0#;(#0.0#)", culture = "ja-JP" },
                    new { value = 0L, format = @"#0.0#;(#0.0#);-\0-", culture = "ja-JP" },
                    new { value = 2147483647L, format = @"##,#", culture = "ja-JP" },
                    new { value = 2147483647L, format = @"##,#", culture = "es-ES" },
                    new { value = 2147483647L, format = @"#,#,,", culture = "ja-JP" },
                    new { value = 2147483647L, format = @"#,#,,", culture = "es-ES" },
                    new { value = 68L, format = @"# 'degrees'", culture = "ja-JP" },
                    new { value = 68L, format = @"# °", culture = "ja-JP" },
                    new { value = 68L, format = @"#' degrees'", culture = "ja-JP" },
                    new { value = 987654L, format = @"#0.0e0", culture = "ja-JP" },
                    new { value = 987654L, format = @"\###00\#", culture = "ja-JP" },
                    new { value = 123L, format = "00000", culture = "ja-JP" },
                    new { value = 1234567890L, format = "0,0", culture = "ja-JP" },
                    new { value = 1234567890L, format = "0,0", culture = "fr-FR" },
                    new { value = 123L, format = "#####", culture = "ja-JP" },
                    new { value = 123456L, format = "[##-##-##]", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#", culture = "ja-JP" },
                    new { value = 1234567890L, format = "(###) ###-####", culture = "ja-JP" },
                    new { value = 86000L, format = "0.###E+0", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#,#", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#,##0,,", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#,,", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#,,,", culture = "ja-JP" },
                    new { value = 1234567890L, format = "#,##0,,", culture = "ja-JP" },
                    new { value = 86000L, format = "0.###E+0", culture = "ja-JP" },
                    new { value = 86000L, format = "0.###E+000", culture = "ja-JP" },
                    new { value = 86000L, format = "0.###E-000", culture = "ja-JP" },
                    new { value = 123L, format = "\\#\\#\\# ##0 dollars and \\0\\0 cents \\#\\#\\#", culture = "ja-JP" },
                    new { value = 123L, format = @"\#\#\# ##0 dollars and \0\0 cents \#\#\#", culture = "ja-JP" },
                    new { value = 123L, format = "\\\\\\\\\\\\ ##0 dollars and \\0\\0 cents \\\\\\\\\\\\", culture = "ja-JP" },
                    new { value = 123L, format = @"\\\\\\ ##0 dollars and \0\0 cents \\\\\\", culture = "ja-JP" },
                    new { value = 1234L, format = "##;(##);**Zero**", culture = "ja-JP" },
                    new { value = -1234L, format = "##;(##);**Zero**", culture = "ja-JP" },
                    new { value = 0L, format = "##;(##);**Zero**", culture = "ja-JP" },
                };
                return (source
                        .Select(item => new { p1 = item.value, p2 = item.format, p3 = CultureInfo.GetCultureInfo(item.culture) })
                        .Select(item =>
                                    {
                                        return (new
                                        {
                                            p1 = (IDataItem)new BigIntDataItem(item.p1),
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