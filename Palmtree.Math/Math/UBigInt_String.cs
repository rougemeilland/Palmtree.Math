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
using System.Globalization;


namespace Palmtree.Math
{
    partial class UBigInt
    {
        #region パブリックメソッド

        public static UBigInt Parse(string value)
        {
            return (Parse(value, NumberStyles.Integer, null));
        }

        public static UBigInt Parse(string value, NumberStyles style)
        {
            return (Parse(value, style, null));
        }

        public static UBigInt Parse(string value, IFormatProvider provider)
        {
            return (Parse(value, NumberStyles.Integer, provider));
        }

        public static UBigInt Parse(string value, NumberStyles style, IFormatProvider provider)
        {
            if (provider as NumberFormatInfo == null)
                provider = CultureInfo.CurrentCulture.NumberFormat;
            return (new UBigInt(EngineObject.Parse(value, style, provider as NumberFormatInfo)));
        }

        public static bool TryParse(string value, out UBigInt result)
        {
            return (TryParse(value, NumberStyles.Integer, null, out result));
        }

        public static bool TryParse(string value, NumberStyles style, IFormatProvider provider, out UBigInt result)
        {
            if (provider as NumberFormatInfo == null)
                provider = CultureInfo.CurrentCulture.NumberFormat;
            Core.UBigIntHandle r;
            if (!EngineObject.TryParse(value, style, provider as NumberFormatInfo, out r))
            {
                result = UBigInt.Zero;
                return (false);
            }
            result = new UBigInt(r);
            return (true);
        }

        public override string ToString()
        {
            return (ToString(null, null));
        }

        public string ToString(IFormatProvider provider)
        {
            return (ToString(null, provider));
        }

        public string ToString(string format)
        {
            return (ToString(format, null));
        }

        public string ToString(string format, IFormatProvider provider)
        {
            if (provider == null)
                provider = CultureInfo.CurrentCulture.NumberFormat;
            if (provider is NumberFormatInfo)
                return ToString(Handle, format, provider as NumberFormatInfo);
            else
            {
                var custom_formatter = provider.GetFormat(this.GetType()) as ICustomFormatter;
                if (custom_formatter != null)
                    return (custom_formatter.Format(format, this, provider));
                else
                {
                    // provider が NumberFormatInfo ではなく、かつ ICustomFormatter が実装されていないプロバイダである場合
                    // 他にどうしようもないので、CultureInfo.CurrentCulture.NumberFormat をプロバイダとして文字列に変換する

                    return (ToString(Handle, format, CultureInfo.CurrentCulture.NumberFormat));
                }
            }
        }

        #endregion

        #region プライベートメソッド

        private static string ToString(Core.UBigIntHandle handle, string format, NumberFormatInfo provider)
        {
            if (_tostring_format_pattern.IsMatch(format))
                return (EngineObject.ToString(handle, format, provider));
            else
                return (ToStringCustomFormat(handle, format, provider));
        }

        private static string ToStringCustomFormat(Core.UBigIntHandle handle, string format, NumberFormatInfo provider)
        {
            // 【実験結果】
            // %と‰の効果は重複してかかる。%が2個なら100*100倍、%と‰なら100*1000倍。%と‰はどこに書かれていてもそのとおりの場所で表示される。【例：(-1.23456789).ToString("0■%■0") => -12■%■3 】
            // '#', '0', '.', ','をまず抜き出して数値を文字列化し、そのあとで'#', '0'のある場所に数値をはめ込む、みたいな実装になっているらしい。
            // ⇒小数部は小数点を基準に上位から順に1文字ずつはめ込まれ、はめ込めなかった分は四捨五入されて必要ならば繰り上がる。
            // ⇒整数部は小数点を基準に下位から順に1文字ずつはめ込まれる。
            // '.'の後に書かれている','は無視される。また、最初の '0', '#' の前に書かれている ',' は無視される。
            // 整数部にて、'0'の後に書かれている'#'は'0'と解釈される。
            // 小数部にて、'0'の前に書かれている'#'は'0'と解釈される。
            // '.'の前に '0'または '#'が一つもない場合は、'#' が一つだけあると解釈される。
            // 整数部の符号は最初の '#', '0'の前にどんなテキストがあろうとあらゆるテキストの最初に表示される。正値のときに自動的には'+'は表示されない。
            // Eの構文解析に失敗した場合はEは(そしてその次の+あるいは-も)一般テキストとしてそのまま表示される。
            // ⇒【例：(1.23456789).ToString("0.0E+#0  000") => 1.2E+34  568】
            // 逆に、構文として正しければEはどこに記述されていてもその場所のまま表示される。
            // ⇒【例：(-0.0123456789).ToString("0.0E+0  000") => -1.2E-2  346】
            // '.' が複数ある場合は最初のものを除いて無視される。【例：(-0.0123456789).ToString("0.0 00.00") => -0.0 1235】
            // 三つ目の';'の後の文字列は数値の符号が何であっても表示されない。つまり無視される。

            throw new NotSupportedException();
        }

        #endregion
    }
}


/*
 * END OF FILE
 */