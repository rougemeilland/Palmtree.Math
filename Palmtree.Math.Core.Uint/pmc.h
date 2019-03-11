/*
 * The MIT License
 *
 * Copyright 2018 Palmtree Software.
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


#pragma once

#ifndef PMC_H
#define PMC_H

#ifdef __GNUC__
#include <stdint.h>
#endif

#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
    extern "C"
    {
#endif

#pragma region マクロの定義
#define __PMC_CALL  __stdcall
#ifdef  __PMC_INTERNAL_H
#define PMC_EXPORT __declspec(dllexport)
#else
#define PMC_EXPORT
#endif

#define PMC_STATUS_OK                           (0)
#define PMC_STATUS_ARGUMENT_ERROR               (-1)
#define PMC_STATUS_ARGUMENT_NULL_ERROR          (-2)
#define PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR  (-3)
#define PMC_STATUS_OVERFLOW                     (-4)
#define PMC_STATUS_DIVISION_BY_ZERO             (-5)
#define PMC_STATUS_ARITHMETIC_ERROR             (-6)
#define PMC_STATUS_FORMAT_ERROR                 (-7)
#define PMC_STATUS_INSUFFICIENT_BUFFER          (-8)
#define PMC_STATUS_NOT_ENOUGH_MEMORY            (-9)
#define PMC_STATUS_NOT_SUPPORTED                (-10)
#define PMC_STATUS_INTERNAL_ERROR               (-256)
#define PMC_STATUS_BAD_BUFFER                   (-257)

#define PMC_CONSTANT_ZERO       (1)
#define PMC_CONSTANT_ONE        (2)
#define PMC_CONSTANT_MINUS_ONE  (3)

#define PMC_NUMBER_STYLE_NONE                   (0x0000)    // スタイル要素 (先行する空白、後続の空白、桁区切り記号、小数点の記号など) を解析対象の文字列に含めることができないことを示す。
#define PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE    (0x0001)    // 先行する空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
#define PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE   (0x0002)    // 末尾の空白文字を解析対象の文字列に使用できることを示す。有効な空白文字の Unicode 値は、U+0009、U+000A、U+000B、U+000C、U+000D、および U+0020 である。
#define PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN     (0x0004)    // 数値文字列に先行する符号を使用できることを示す。
#define PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN    (0x0008)    // 数値文字列に後続する符号を使用できることを示す。
#define PMC_NUMBER_STYLE_ALLOW_PARENTHESES      (0x0010)    // 数値文字列にその数値を囲む一組の括弧を使用できることを示す。括弧は解析対象の文字列が負の値を表すことを示す。
#define PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT    (0x0020)    // 数値文字列に小数点を使用できることを示す。
#define PMC_NUMBER_STYLE_ALLOW_THOUSANDS        (0x0040)    // 先行する空白文字を解析対象の文字列に使用できることを示す。
#define PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL  (0x0100)    // 数字文字列に通貨記号を含めることができることを示す。
#define PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER    (0x0200)    // 数値文字列が16進数を表すことを示す。
#define PMC_NUMBER_STYLE_ALLOW_SIGNED_INTEGER       (0x01000000)    // 数値文字列に負の符号または負数を示すカッコを含むことを許可する
#define PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING   (0x02000000)    // 変換時にエラーを検出した場合に例外で通知することを許可する
#pragma endregion


#pragma region 型の定義
#ifdef _MSC_VER
        typedef __int16 _INT16_T;
        typedef __int32 _INT32_T;
        typedef __int64 _INT64_T;
        typedef unsigned __int8 _BYTE_T;
        typedef unsigned __int16 _UINT16_T;
        typedef unsigned __int32 _UINT32_T;
        typedef unsigned __int64 _UINT64_T;
#elif defined(__GNUC__)
        typedef int16_t _INT16_T;
        typedef int32_t _INT32_T;
        typedef int64_t _INT64_T;
        typedef uint8_t _BYTE_T;
        typedef uint16_t _UINT16_T;
        typedef uint32_t _UINT32_T;
        typedef uint64_t _UINT64_T;
#else
#error unknown compiler
#endif

        typedef struct __tag_PMC_CONFIGURATION_INFO
        {
            unsigned char MEMORY_VERIFICATION_ENABLED; // 未使用
        } PMC_CONFIGURATION_INFO;


        typedef _INT32_T PMC_STATUS_CODE;

        typedef _INT32_T PMC_CONSTANT_VALUE_CODE;

        typedef _INT32_T PMC_NUMBER_STYLE_CODE;

        typedef struct __tag_PMC_STATISTICS_INFO
        {
            long COUNT_MULTI64; // 32bit * 32bit => 64bitの乗算の回数
            long COUNT_MULTI32; // 16bit * 16bit => 32bitの乗算の回数
            long COUNT_DIV64;   // 64bit / 32bit => 32bitの除算の回数
            long COUNT_DIV32;   // 32bit / 16bit => 16bitの除算の回数
        } PMC_STATISTICS_INFO;

        typedef struct __tag_PMC_DECIMAL_NUMBER_FORMAT_INFO
        {
            int         DecimalDigits;          // 数値の小数点以下の既定の桁数として解釈される。
            wchar_t     DecimalSeparator[17];   // 数値の整数部と小数部との区切り文字と解釈される。
            wchar_t     GroupSeparator[17];     // 数値をグループで区切る場合の区切り文字と解釈される。
            wchar_t     GroupSizes[11];         // 数値をグループで区切る場合のグループの大きさを示す文字の集合と解釈される。
            int         NegativePattern;        // 負数を表示する場合のパターンを示す番号。
            int         PositivePattern;        // 正数を表示する場合のパターンを示す番号。
        } PMC_DECIMAL_NUMBER_FORMAT_INFO;

        typedef struct __tag_PMC_NUMBER_FORMAT_INFO
        {
            PMC_DECIMAL_NUMBER_FORMAT_INFO  Currency;           // 通貨量の数値を表示する場合に使用される情報。
            PMC_DECIMAL_NUMBER_FORMAT_INFO  Number;             // 一般的な数値を表示する場合に使用される情報。
            PMC_DECIMAL_NUMBER_FORMAT_INFO  Percent;            // パーセント値を表示する場合に使用される情報。
            wchar_t                         CurrencySymbol[17]; // 通貨記号として使用される文字列。既定値は "¤"。
            wchar_t                         NegativeSign[17];   // 負数であることを示す文字列。既定値は "-"。            
            wchar_t                         PositiveSign[17];   // 正数であることを示す文字列。既定値は "+"。
            wchar_t                         PercentSymbol[17];  // パーセント記号として使用する文字列。既定値は "%"。
            wchar_t                         PerMilleSymbol[17]; // パーミル記号として使用する文字列。既定値は "\u2030"。
        } PMC_NUMBER_FORMAT_INFO;
#pragma endregion


#ifdef __cplusplus
    }
}
#endif

#endif /* PMC_H */


/*
 * END OF FILE
 */

