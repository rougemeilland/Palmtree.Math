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

namespace Palmtree.Math.Core.Uint.Test.Plugin
{
    // テスト対象である Equals のオーバーロードは以下の理由により使用されることはないことが判明したため、テストも取りやめる。
    // 理由： テスト対象のオーバーロードより優先して UInt32.Equals(object o) あるいは UInt64.Equals(object o) が実行されてしまい、テスト対象のオーバーロードが呼び出されることがなくなってしまっていることが判明したため。
#if false
    class ComponentTestPlugin_Equals_I_X
        : ComponentTestPluginBase_2_1
    {
        public ComponentTestPlugin_Equals_I_X()
            : base("equals_i_x", "test_data_equality_i_x.xml")
        {
        }

        protected override IDataItem TestFunc(IDataItem p1, IDataItem p2)
        {
            var u = p1.ToUInt32().Value;
            var v = p2.ToUBigInt().Value;
            try
            {
                var w = u.Equals(v);
                return (new UInt32DataItem(w ? 1U : 0U));
            }
            catchx (Exception ex)
            {
                return (new ExceptionDataItem(ex.GetType()));
            }
        }
    }
#endif
}


/*
 * END OF FILE
 */