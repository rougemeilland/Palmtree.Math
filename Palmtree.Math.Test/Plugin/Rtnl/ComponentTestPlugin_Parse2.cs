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


using System.Globalization;

namespace Palmtree.Math.Test.Plugin.Rtnl
{
    class ComponentTestPlugin_Parse2
        : ComponentTestPluginBase_3_1
    {
        public ComponentTestPlugin_Parse2()
            : base("rtnl", "parse2", "test_data_parse2.xml")
        {
        }

        protected override IDataItem TestFunc(IDataItem p1, IDataItem p2, IDataItem p3)
        {
            var s = p1.ToXString().Value;
            var f = p2.ToInt32().Value;
            var n = p3.ToNumberFormatInfo().Value;
            var r = Rational.Parse(s, (NumberStyles)f, n);
            return (new RationalDataItem(r));
        }

        public override int Order => 102;
    }
}


/*
 * END OF FILE
 */