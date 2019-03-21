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


using System.Globalization;
using System.Runtime.InteropServices;

namespace Palmtree.Math.Core
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
    internal class PMC_NUMBER_FORMAT_INFO
    {
        #region パブリックフィールド

        public PMC_DECIMAL_NUMBER_FORMAT_INFO Currency; // 通貨量の数値を表示する場合に使用される情報。
        public PMC_DECIMAL_NUMBER_FORMAT_INFO Number;   // 一般的な数値を表示する場合に使用される情報。
        public PMC_DECIMAL_NUMBER_FORMAT_INFO Percent;  // パーセント値を表示する場合に使用される情報。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string CurrencySymbol;                   // 通貨記号として使用される文字列。既定値は "¤"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string NegativeSign;                     // 負数であることを示す文字列。既定値は "-"。            
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PositiveSign;                     // 正数であることを示す文字列。既定値は "+"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PercentSymbol;                    // パーセント記号として使用する文字列。既定値は "%"。
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 17)]
        public string PerMilleSymbol;                   // パーミル記号として使用する文字列。既定値は "\u2030"。

        #endregion

        #region コンストラクタ

        public PMC_NUMBER_FORMAT_INFO(NumberFormatInfo source)
        {
            Currency = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.CurrencyDecimalDigits, source.CurrencyDecimalSeparator, source.CurrencyGroupSeparator, source.CurrencyGroupSizes, source.CurrencyNegativePattern, source.CurrencyPositivePattern);
            Number = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.NumberDecimalDigits, source.NumberDecimalSeparator, source.NumberGroupSeparator, source.NumberGroupSizes, source.NumberNegativePattern, -1);
            Percent = new PMC_DECIMAL_NUMBER_FORMAT_INFO(source.PercentDecimalDigits, source.PercentDecimalSeparator, source.PercentGroupSeparator, source.PercentGroupSizes, source.PercentNegativePattern, source.PercentPositivePattern);
            if (source.CurrencySymbol.Length > 16)
                throw new InternalErrorException();
            CurrencySymbol = source.CurrencySymbol;
            if (source.NegativeSign.Length > 16)
                throw new InternalErrorException();
            NegativeSign = source.NegativeSign;
            if (source.PercentSymbol.Length > 16)
                throw new InternalErrorException();
            PercentSymbol = source.PercentSymbol;
            if (source.PerMilleSymbol.Length > 16)
                throw new InternalErrorException();
            PerMilleSymbol = source.PerMilleSymbol;
            if (source.PositiveSign.Length > 16)
                throw new InternalErrorException();
            PositiveSign = source.PositiveSign;
        }

        #endregion

    }

}


/*
 * END OF FILE
 */