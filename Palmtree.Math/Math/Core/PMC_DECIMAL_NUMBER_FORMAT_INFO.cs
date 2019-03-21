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


using System.Runtime.InteropServices;

namespace Palmtree.Math.Core
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    internal struct PMC_DECIMAL_NUMBER_FORMAT_INFO
    {
        #region パブリックフィールド

        public int DecimalDigits;       // 数値の小数点以下の既定の桁数として解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string DecimalSeparator; // 数値の整数部と小数部との区切り文字と解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string GroupSeparator;   // 数値をグループで区切る場合の区切り文字と解釈される。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 11)]
        public string GroupSizes;       // 数値をグループで区切る場合のグループの大きさを示す文字の集合と解釈される。
        public int NegativePattern;     // 負数を表示する場合のパターンを示す番号。
        public int PositivePattern;     // 正数を表示する場合のパターンを示す番号。

        #endregion

        #region コンストラクタ

        public PMC_DECIMAL_NUMBER_FORMAT_INFO(int decimal_digits, string decimal_separator, string group_separator, int[] group_sizes, int negative_pattern, int positive_pattern)
        {
            DecimalDigits = decimal_digits;
            if (decimal_separator.Length > 16)
                throw new InternalErrorException();
            DecimalSeparator = decimal_separator;
            if (group_separator.Length > 16)
                throw new InternalErrorException();
            GroupSeparator = group_separator;
            if (group_sizes.Length > 10)
                throw new InternalErrorException();
            GroupSizes = string.Concat(group_sizes);
            NegativePattern = negative_pattern;
            PositivePattern = positive_pattern;
        }

        #endregion
    }

}


/*
 * END OF FILE
 */