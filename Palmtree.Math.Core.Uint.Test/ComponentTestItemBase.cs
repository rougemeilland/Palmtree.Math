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
using System.Runtime.ExceptionServices;

namespace Palmtree.Math.Core.Uint.Test
{
    abstract class ComponentTestItemBase
         : IComponentTestItem
    {
        protected IDataItem _primary_result_value;

        public ComponentTestItemBase(string plugin_name, int index, IDataItem r1)
        {
            PluginName = plugin_name;
            Index = index;
            _primary_result_value = r1;
        }

        public string PluginName { get; }

        public int Index { get; }

        protected abstract bool TestProc(out string summary);

        [HandleProcessCorruptedStateExceptions]
        public bool DoTest(out string summary)
        {
            summary = null;
            try
            {
                return (TestProc(out summary));
            }
            catch (Exception ex)
            {
                var actual_exception = new ExceptionDataItem(ex.GetType(), ex.Message);
                var desierd_exception = _primary_result_value;
                var result = desierd_exception.IsException && actual_exception.Equals(desierd_exception);
                if (!result)
                    return (false);
                return (true);
            }
        }
    }
}


/*
 * END OF FILE
 */