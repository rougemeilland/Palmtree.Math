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
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Xml.Linq;

namespace Palmtree.Math.Core.Uint.Test
{
    abstract class ComponentTestPluginBase_1_1
        : ComponentTestPluginBase
    {
        protected class ComponentTestItem
            : ComponentTestItemBase
        {
            private IDataItem _p1;
            private IDataItem _r1;
            private Func<IDataItem, IDataItem>_func;

            public ComponentTestItem(string data_file_name, int index, IDataItem param1, IDataItem result1, Func<IDataItem, IDataItem> func)
                : base(data_file_name, index, result1)
            {
                _p1 = param1;
                _r1 = result1;
                _func = func;
            }

            [HandleProcessCorruptedStateExceptions]
            protected override bool TestProc(out string summary)
            {
                try
                {
                    var actual_result1 = _func(_p1);
                    var desired_result1 = _r1;
                    summary = string.Format("({0}) => ({1}) [{2}]",
                                            string.Join(", ", new[] { _p1 }.Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { _r1 }.Where(r => !r.IsNull).Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { actual_result1 }.Select(p => p.ToSummaryString())));
                    var result = !desired_result1.IsException && actual_result1.Equals(desired_result1);
                    if (!result)
                        return (false);
                    return (true);
                }
                catch (Exception ex)
                {
                    summary = string.Format("({0}) => ({1}) [{2}]",
                                            string.Join(", ", new[] { _p1 }.Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { _r1 }.Where(r => !r.IsNull).Select(p => p.ToSummaryString())),
                                            new ExceptionDataItem(ex.GetType(), ex.Message).ToSummaryString());
                    throw;
                }
            }
        }

        protected ComponentTestPluginBase_1_1(string plugin_nam, string data_file_name)
            : base(plugin_nam, data_file_name)
        {
        }

        protected abstract IDataItem TestFunc(IDataItem p1);

        protected override IComponentTestItem ParseFromXml(XElement element)
        {
            var index = int.Parse(element.Attribute("index").Value);
            var param1 = DataItem.FromXElement(element.Element("param1"));
            var result1 = DataItem.FromXElement(element.Element("result1"));
            return (new ComponentTestItem(PluginName, index, param1, result1, TestFunc));
        }
    }
}


/*
 * END OF FILE
 */