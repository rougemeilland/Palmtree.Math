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
using System.Xml.Linq;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Palmtree.Math.Core.Uint.Test
{
    abstract class ComponentTestPluginBase
        : IComponentTestPlugin
    {
        private string _data_file_path;

        protected ComponentTestPluginBase(string plugin_name, string data_file_name)
        {
            PluginName = plugin_name;
            _data_file_path = Path.Combine(Path.GetDirectoryName(typeof(ComponentTestPluginBase).Assembly.Location), "Data", data_file_name);
        }

        public string PluginName { get; }

        public IEnumerable<IComponentTestItem> TestItems
        {
            get
            {
                var document = XDocument.Load(_data_file_path);
                var root = document.Element("dataitems");
                return (root.Elements("dataitem")
                        .Select(element => new { element, index = element.Attribute("index") })
                        .Where(item => item.index != null)
                        .Select(item => ParseFromXml(item.element)));

            }
        }

        protected abstract IComponentTestItem ParseFromXml(XElement element);
    }
}


/*
 * END OF FILE
 */