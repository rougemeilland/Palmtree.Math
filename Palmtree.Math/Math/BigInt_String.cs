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


using System;
using System.Globalization;


namespace Palmtree.Math
{
    partial struct BigInt
    {
        #region パブリックメソッド

        public static BigInt Parse(string value)
        {
            return (Parse(value, NumberStyles.Integer, null));
        }

        public static BigInt Parse(string value, NumberStyles style)
        {
            return (Parse(value, style, null));
        }

        public static BigInt Parse(string value, IFormatProvider provider)
        {
            return (Parse(value, NumberStyles.Integer, provider));
        }

        public static BigInt Parse(string value, NumberStyles style, IFormatProvider provider)
        {
            if (provider as NumberFormatInfo == null)
                provider = CultureInfo.CurrentCulture.NumberFormat;
            return (new BigInt(EngineObject.Parse(value, style, provider as NumberFormatInfo)));
        }

        public static bool TryParse(string value, out BigInt result)
        {
            return (TryParse(value, NumberStyles.Integer, null, out result));
        }

        public static bool TryParse(string value, NumberStyles style, IFormatProvider provider, out BigInt result)
        {
            if (provider as NumberFormatInfo == null)
                provider = CultureInfo.CurrentCulture.NumberFormat;
            Core.BigIntHandle r;
            if (!EngineObject.TryParse(value, style, provider as NumberFormatInfo, out r))
            {
                result = BigInt.Zero;
                return (false);
            }
            result = new BigInt(r);
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
            if (format == null)
                format = "G";
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

        private static string ToString(Core.BigIntHandle handle, string format, NumberFormatInfo provider)
        {
            return (EngineObject.ToString(handle, format, provider));
        }

        #endregion
    }
}


/*
 * END OF FILE
 */