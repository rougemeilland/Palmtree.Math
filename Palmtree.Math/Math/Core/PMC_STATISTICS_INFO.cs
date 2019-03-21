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
using System.Runtime.InteropServices;

namespace Palmtree.Math.Core
{
    [StructLayout(LayoutKind.Sequential)]
    internal class PMC_STATISTICS_INFO
    {
        #region パブリックフィールド

        public UInt32 COUNT_MULTI64; // 32bit * 32bit => 64bitの乗算の回数
        public UInt32 COUNT_MULTI32; // 16bit * 16bit => 32bitの乗算の回数
        public UInt32 COUNT_DIV64;   // 64bit / 32bit => 32bitの除算の回数
        public UInt32 COUNT_DIV32;   // 32bit / 16bit => 16bitの除算の回数

        #endregion

        #region コンストラクタ

        public PMC_STATISTICS_INFO()
        {
            COUNT_MULTI64 = 0;
            COUNT_MULTI32 = 0;
            COUNT_DIV64 = 0;
            COUNT_DIV32 = 0;
        }

        #endregion
    }

}


/*
 * END OF FILE
 */