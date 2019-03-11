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
using System.Linq;
using System.Xml;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    abstract class TestDataRendererPluginBase_3_1
        : TestDataRendererPluginBase
    {
        protected class TestDataItemContainer
        {
            public int Index { get; set; }
            public IDataItem Param1 { get; set; }
            public IDataItem Param2 { get; set; }
            public IDataItem Param3 { get; set; }
            public IDataItem Result1 { get; set; }
        }

        protected TestDataRendererPluginBase_3_1(string data_file_name)
            : base(data_file_name)
        {
        }

        protected abstract IEnumerable<TestDataItemContainer> TestDataItems { get; }

        protected override IEnumerable<XmlElement> GetDataItemRows(XmlDocument document)
        {
            return (TestDataItems
                     .Select(item => GetDataItemRow(document, item.Index, item.Param1, item.Param2, item.Param3, item.Result1)));
        }

        private static XmlElement GetDataItemRow(XmlDocument document, int index, IDataItem param1, IDataItem param2, IDataItem param3, IDataItem result1)
        {
            var row = document.CreateElement("dataitem");
            row.SetAttribute("index", index.ToString());
            AppendElement(row, (param1.ToXmlElement(document, "param1")));
            AppendElement(row, (param2.ToXmlElement(document, "param2")));
            AppendElement(row, (param3.ToXmlElement(document, "param3")));
            AppendElement(row, (result1.ToXmlElement(document, "result1")));

            return (row);
        }
    }
}


/*
 * END OF FILE
 */