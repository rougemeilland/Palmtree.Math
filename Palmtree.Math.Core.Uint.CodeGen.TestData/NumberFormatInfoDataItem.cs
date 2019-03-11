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
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    public class NumberFormatInfoDataItem
        : DataItem
    {
        private string _culture_name;
        private NumberFormatInfo _value;

        public NumberFormatInfoDataItem(string culture_name, NumberFormatInfo value)
        {
            _culture_name = culture_name;
            _value = value;
        }

        public NumberFormatInfoDataItem(CultureInfo culture)
            : this(culture.Name, culture.NumberFormat)
        {
        }

        public NumberFormatInfoDataItem()
            : this(CultureInfo.InvariantCulture.Name, CultureInfo.InvariantCulture.NumberFormat)
        {
        }

        public override string Type => "numberformatinfo";

        public NumberFormatInfo Value => _value;

        public override bool IsNumberFormatInfo => true;

        public override NumberFormatInfoDataItem ToNumberFormatInfo()
        {
            return (this);
        }

        public override bool Equals(object o)
        {
            if (o == null)
                return (false);
            if (GetType() != o.GetType())
                return (false);
            return (_value == ((NumberFormatInfoDataItem)o)._value);
        }

        public override int GetHashCode()
        {
            return (_value.GetHashCode());
        }

        protected override string SerializeValue()
        {
            var orig = _culture_name != null ? CultureInfo.GetCultureInfo(_culture_name).NumberFormat : new NumberFormatInfo();
            var 変更点 = new Dictionary<string, string>();

            if (!string.IsNullOrEmpty(_culture_name))
                変更点.Add("CultureName", _culture_name);
#if true
            if (orig.CurrencyDecimalDigits != _value.CurrencyDecimalDigits)
                変更点.Add("CurrencyDecimalDigits", _value.CurrencyDecimalDigits.ToString());

            if (orig.CurrencyDecimalSeparator != _value.CurrencyDecimalSeparator)
                変更点.Add("CurrencyDecimalSeparator", _value.CurrencyDecimalSeparator);

            if (orig.CurrencyGroupSeparator != _value.CurrencyGroupSeparator)
                変更点.Add("CurrencyGroupSeparator", _value.CurrencyGroupSeparator);

            if (string.Concat(orig.CurrencyGroupSizes) != string.Concat(_value.CurrencyGroupSizes))
                変更点.Add("CurrencyGroupSizes", string.Concat(_value.CurrencyGroupSizes));

            if (orig.CurrencyNegativePattern != _value.CurrencyNegativePattern)
                変更点.Add("CurrencyNegativePattern", _value.CurrencyNegativePattern.ToString());

            if (orig.CurrencyPositivePattern != _value.CurrencyPositivePattern)
                変更点.Add("CurrencyPositivePattern", _value.CurrencyPositivePattern.ToString());

            if (orig.CurrencySymbol != _value.CurrencySymbol)
                変更点.Add("CurrencySymbol", _value.CurrencySymbol);

            if (orig.NegativeSign != _value.NegativeSign)
                変更点.Add("NegativeSign", _value.NegativeSign);

            if (orig.NumberDecimalDigits != _value.NumberDecimalDigits)
                変更点.Add("NumberDecimalDigits", _value.NumberDecimalDigits.ToString());

            if (orig.NumberDecimalSeparator != _value.NumberDecimalSeparator)
                変更点.Add("NumberDecimalSeparator", _value.NumberDecimalSeparator);

            if (orig.NumberGroupSeparator != _value.NumberGroupSeparator)
                変更点.Add("NumberGroupSeparator", _value.NumberGroupSeparator);

            if (string.Concat(orig.NumberGroupSizes) != string.Concat(_value.NumberGroupSizes))
                変更点.Add("NumberGroupSizes", string.Concat(_value.NumberGroupSizes));

            if (orig.NumberNegativePattern != _value.NumberNegativePattern)
                変更点.Add("NumberNegativePattern", _value.NumberNegativePattern.ToString());

            if (orig.PercentDecimalDigits != _value.PercentDecimalDigits)
                変更点.Add("PercentDecimalDigits", _value.PercentDecimalDigits.ToString());

            if (orig.PercentDecimalSeparator != _value.PercentDecimalSeparator)
                変更点.Add("PercentDecimalSeparator", _value.PercentDecimalSeparator);

            if (orig.PercentGroupSeparator != _value.PercentGroupSeparator)
                変更点.Add("PercentGroupSeparator", _value.PercentGroupSeparator);

            if (string.Concat(orig.PercentGroupSizes) != string.Concat(_value.PercentGroupSizes))
                変更点.Add("PercentGroupSizes", string.Concat(_value.PercentGroupSizes));

            if (orig.PercentNegativePattern != _value.PercentNegativePattern)
                変更点.Add("PercentNegativePattern", _value.PercentNegativePattern.ToString());

            if (orig.PercentPositivePattern != _value.PercentPositivePattern)
                変更点.Add("PercentPositivePattern", _value.PercentPositivePattern.ToString());

            if (orig.PercentSymbol != _value.PercentSymbol)
                変更点.Add("PercentSymbol", _value.PercentSymbol);

            if (orig.PerMilleSymbol != _value.PerMilleSymbol)
                変更点.Add("PerMilleSymbol", _value.PerMilleSymbol);

            if (orig.PositiveSign != _value.PositiveSign)
                変更点.Add("PositiveSign", _value.PositiveSign);
#endif
            return (string.Join(":",
                                変更点
                                .Select(item => string.Format("{0}={1}",
                                                              item.Key,
                                                              EscapeString(item.Value)))));
        }

        private static string EscapeString(string s)
        {
            return (s.Replace("&", "&amp;").Replace("=", "&#61;").Replace(":", "&#58;"));
        }
    }
}


/*
 * END OF FILE
 */