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

namespace Palmtree.Math.Core
{
    [Flags]
    internal enum PMC_NUMBER_STYLE_CODE
    {
        PMC_NUMBER_STYLE_NONE = 0x0000,                   // スタイル要素 =先行する空白、後続の空白、桁区切り記号、小数点の記号など, を解析対象の文字列に含めることができないことを示す。
        PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE = 0x0001,    // 先行する空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
        PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE = 0x0002,   // 末尾の空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
        PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN = 0x0004,     // 数値文字列に先行する符号を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN = 0x0008,    // 数値文字列に後続する符号を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_PARENTHESES = 0x0010,      // 数値文字列にその数値を囲む一組の括弧を使用できることを示す。括弧は解析対象の文字列が負の値を表すことを示す。
        PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT = 0x0020,    // 数値文字列に小数点を使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_THOUSANDS = 0x0040,        // 先行する空白文字を解析対象の文字列に使用できることを示す。
        PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL = 0x0100,  // 数字文字列に通貨記号を含めることができることを示す。
        PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER = 0x0200,    // 数値文字列が16進数を表すことを示す。
        PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER = 0x01000000,       // 数値文字列に負の符号または負数を示すカッコを含むことを許可する
    }
}


/*
 * END OF FILE
 */