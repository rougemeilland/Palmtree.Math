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


namespace Palmtree.Math.Core.Uint.Test.Plugin
{
    class ComponentTestPlugin_static_DivRem_X_X
        : ComponentTestPluginBase_2_2
    {
        public ComponentTestPlugin_static_DivRem_X_X()
            : base("static_divrem_x_x", "test_data_divrem_x_x.xml")
        {
        }

        protected override IDataItem TestFunc(IDataItem p1, IDataItem p2, out IDataItem r2)
        {
            var u = p1.ToUBigInt().Value;
            var v = p2.ToUBigInt().Value;
            UBigInt r;
            var q = UBigInt.DivRem(u, v, out r);
            r2 = new UBigIntDataItem(r);
            return (new UBigIntDataItem(q));
        }
    }
}


/*
 * END OF FILE
 */