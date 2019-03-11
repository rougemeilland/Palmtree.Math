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
using System.Linq;
using System.Xml.Linq;

namespace Palmtree.Math.Core.Uint.Test
{
    public abstract class DataItem
        : IDataItem
    {
        public abstract string Type { get; }

        public virtual bool IsNull => false;

        public virtual bool IsUBigInt => false;

        public virtual bool IsInt32 => false;

        public virtual bool IsUInt32 => false;

        public virtual bool IsUInt64 => false;

        public virtual bool IsXString => false;

        public virtual bool IsNumberFormatInfo => false;

        public virtual bool IsException => false;

        public static IDataItem FromXElement(XElement element)
        {
            if (element == null)
                return (new NullDataItem());
            var type = element.Attribute("type").Value;
            var text = element.Value;
            switch (type)
            {
                case "int32":
                    return (new Int32DataItem(Int32.Parse(text)));
                case "uint32":
                    return (new UInt32DataItem(UInt32.Parse(text)));
                case "uint64":
                    return (new UInt64DataItem(UInt64.Parse(text)));
                case "ubigint":
                    {
                        var bytes = text.Split(',').Select(x => byte.Parse(x, NumberStyles.HexNumber)).ToArray();
                        var p = UBigInt.FromByteArray(bytes);
                        return (new UBigIntDataItem(p));
                    }
                case "string":
                    return (new XStringDataItem(text));
                case "numberformatinfo":
                    {
                        var dic = text.Split(':')
                                  .Where(line => line != "")
                                  .Select(line => line.Split('='))
                                  .Select(columns =>
                                  {
                                      if (columns.Length != 2)
                                          throw new ApplicationException();
                                      var key = columns[0];
                                      var value = columns[1].Replace("&#58;", ":").Replace("&#61;", "=").Replace("&amp;", "&");
                                      return (new { key, value });
                                  })
                                  .ToDictionary(item => item.key, item => item.value);
                        var culture = dic.ContainsKey("CultureName") ? CultureInfo.CreateSpecificCulture(dic["CultureName"]) : CultureInfo.InvariantCulture;
                        foreach (var key_value in dic)
                        {
                            switch (key_value.Key)
                            {
                                case "CurrencyDecimalDigits":
                                    culture.NumberFormat.CurrencyDecimalDigits = int.Parse(key_value.Value);
                                    break;

                                case "CurrencyDecimalSeparator":
                                    culture.NumberFormat.CurrencyDecimalSeparator = key_value.Value;
                                    break;

                                case "CurrencyGroupSeparator":
                                    culture.NumberFormat.CurrencyGroupSeparator = key_value.Value;
                                    break;

                                case "CurrencyGroupSizes":
                                    culture.NumberFormat.CurrencyGroupSizes = key_value.Value.Select(c => c - '0').ToArray();
                                    break;

                                case "CurrencyNegativePattern":
                                    culture.NumberFormat.CurrencyNegativePattern = int.Parse(key_value.Value);
                                    break;

                                case "CurrencyPositivePattern":
                                    culture.NumberFormat.CurrencyPositivePattern = int.Parse(key_value.Value);
                                    break;

                                case "CurrencySymbol":
                                    culture.NumberFormat.CurrencySymbol = key_value.Value;
                                    break;

                                case "NegativeSign":
                                    culture.NumberFormat.NegativeSign = key_value.Value;
                                    break;

                                case "NumberDecimalDigits":
                                    culture.NumberFormat.NumberDecimalDigits = int.Parse(key_value.Value);
                                    break;

                                case "NumberDecimalSeparator":
                                    culture.NumberFormat.NumberDecimalSeparator = key_value.Value;
                                    break;

                                case "NumberGroupSeparator":
                                    culture.NumberFormat.NumberGroupSeparator = key_value.Value;
                                    break;

                                case "NumberGroupSizes":
                                    culture.NumberFormat.NumberGroupSizes = key_value.Value.Select(c => c - '0').ToArray();
                                    break;

                                case "NumberNegativePattern":
                                    culture.NumberFormat.NumberNegativePattern = int.Parse(key_value.Value);
                                    break;

                                case "PercentDecimalDigits":
                                    culture.NumberFormat.PercentDecimalDigits = int.Parse(key_value.Value);
                                    break;

                                case "PercentDecimalSeparator":
                                    culture.NumberFormat.PercentDecimalSeparator = key_value.Value;
                                    break;

                                case "PercentGroupSeparator":
                                    culture.NumberFormat.PercentGroupSeparator = key_value.Value;
                                    break;

                                case "PercentGroupSizes":
                                    culture.NumberFormat.PercentGroupSizes = key_value.Value.Select(c => c - '0').ToArray();
                                    break;

                                case "PercentNegativePattern":
                                    culture.NumberFormat.PercentNegativePattern = int.Parse(key_value.Value);
                                    break;

                                case "PercentPositivePattern":
                                    culture.NumberFormat.PercentPositivePattern = int.Parse(key_value.Value);
                                    break;

                                case "PercentSymbol":
                                    culture.NumberFormat.PercentSymbol = key_value.Value;
                                    break;

                                case "PerMilleSymbol":
                                    culture.NumberFormat.PerMilleSymbol = key_value.Value;
                                    break;

                                case "PositiveSign":
                                    culture.NumberFormat.PositiveSign = key_value.Value;
                                    break;
                            }
                        }
                        return (new NumberFormatInfoDataItem(text, culture.NumberFormat));
                    }
                case "exception":
                    switch (text.ToLower())
                    {
                        case "overflowexception":
                            return (new ExceptionDataItem(typeof(OverflowException)));
                        case "argumentexception":
                            return (new ExceptionDataItem(typeof(ArgumentException)));
                        case "argumentnullexception":
                            return (new ExceptionDataItem(typeof(ArgumentNullException)));
                        case "formatexception":
                            return (new ExceptionDataItem(typeof(FormatException)));
                        case "dividebyzeroexception":
                            return (new ExceptionDataItem(typeof(DivideByZeroException)));
                        case "arithmeticexception":
                            return (new ExceptionDataItem(typeof(ArithmeticException)));
                        default:
                            throw new ApplicationException();
                    }
                default:
                    throw new ApplicationException();
            }
        }

        public virtual NullDataItem ToNull()
        {
            throw new InvalidCastException();
        }

        public virtual UBigIntDataItem ToUBigInt()
        {
            throw new InvalidCastException();
        }

        public virtual Int32DataItem ToInt32()
        {
            throw new InvalidCastException();
        }

        public virtual UInt32DataItem ToUInt32()
        {
            throw new InvalidCastException();
        }

        public virtual UInt64DataItem ToUInt64()
        {
            throw new InvalidCastException();
        }

        public virtual XStringDataItem ToXString()
        {
            throw new InvalidCastException();
        }

        public virtual ExceptionDataItem ToException()
        {
            throw new InvalidCastException();
        }

        public virtual NumberFormatInfoDataItem ToNumberFormatInfo()
        {
            throw new InvalidCastException();
        }

        public abstract string ToSummaryString();
    }
}


/*
 * END OF FILE
 */