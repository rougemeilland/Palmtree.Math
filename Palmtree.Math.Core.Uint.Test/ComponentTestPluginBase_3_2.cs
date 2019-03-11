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
    abstract class ComponentTestPluginBase_3_2
        : ComponentTestPluginBase
    {
        protected delegate IDataItem _func_3_2(IDataItem param1, IDataItem param2, IDataItem param3, out IDataItem result2);

        protected class ComponentTestItem
            : ComponentTestItemBase
        {
            private IDataItem _p1;
            private IDataItem _p2;
            private IDataItem _p3;
            private IDataItem _r1;
            private IDataItem _r2;
            private _func_3_2 _func;

            public ComponentTestItem(string data_file_name, int index, IDataItem param1, IDataItem param2, IDataItem param3, IDataItem result1, IDataItem result2, _func_3_2 func)
                : base(data_file_name, index, result1)
            {
                _p1 = param1;
                _p2 = param2;
                _p3 = param3;
                _r1 = result1;
                _r2 = result2;
                _func = func;
            }

            [HandleProcessCorruptedStateExceptions]
            protected override bool TestProc(out string summary)
            {
                try
                {
                    IDataItem actual_result2;
                    var actual_result1 = _func(_p1, _p2, _p3, out actual_result2);
                    var desired_result1 = _r1;
                    var desired_result2 = _r2;
                    summary = string.Format("({0}) => ({1}) [{2}]",
                                            string.Join(", ", new[] { _p1, _p2, _p3 }.Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { _r1, _r2 }.Where(r => !r.IsNull).Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { actual_result1, actual_result2 }.Select(p => p.ToSummaryString())));
                    var result = !desired_result1.IsException && actual_result1.Equals(desired_result1) && actual_result2.Equals(desired_result2);
                    if (!result)
                        return (false);
                    return (true);
                }
                catch (Exception ex)
                {
                    summary = string.Format("({0}) => ({1}) [{2}]",
                                            string.Join(", ", new[] { _p1, _p2, _p3 }.Select(p => p.ToSummaryString())),
                                            string.Join(", ", new[] { _r1, _r2 }.Where(r => !r.IsNull).Select(p => p.ToSummaryString())),
                                            new ExceptionDataItem(ex.GetType(), ex.Message).ToSummaryString());
                    throw;
                }
            }
        }

        protected ComponentTestPluginBase_3_2(string plugin_nam, string data_file_name)
            : base(plugin_nam, data_file_name)
        {
        }

        protected abstract IDataItem TestFunc(IDataItem p1, IDataItem p2, IDataItem p3, out IDataItem r2);

        protected override IComponentTestItem ParseFromXml(XElement element)
        {
            var index = int.Parse(element.Attribute("index").Value);
            var param1 = DataItem.FromXElement(element.Element("param1"));
            var param2 = DataItem.FromXElement(element.Element("param2"));
            var param3 = DataItem.FromXElement(element.Element("param3"));
            var result1 = DataItem.FromXElement(element.Element("result1"));
            var result2 = DataItem.FromXElement(element.Element("result2"));
            return (new ComponentTestItem(PluginName, index, param1, param2, param3, result1, result2, TestFunc));
        }
    }
}


/*
 * END OF FILE
 */