using System;
using System.Globalization;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Palmtree.Math.CodeGen.TestData
{
    public class MiniRational
    {
        static MiniRational()
        {
        }

        public MiniRational(decimal x)
        {
            var n = x;
            var d = 1UL;
            var count = 32;
            while (System.Math.Ceiling(n) != System.Math.Floor(n))
            {
                n *= 10000;
                d *= 10000;
                --count;
                if (count <= 0)
                    throw new ApplicationException();
            }
            var numerator = (BigInteger)n;
            var denominator = (BigInteger)d;
            var gcd = BigInteger.GreatestCommonDivisor(BigInteger.Abs(numerator), denominator);
            numerator /= gcd;
            denominator /= gcd;
            Numerator = numerator;
            Denominator = denominator;
        }

        public MiniRational(double x)
        {
            var n = x;
            var d = 1UL;
            var count = 32;
            while (System.Math.Ceiling(n) != System.Math.Floor(n))
            {
                n *= 256;
                d *= 256;
                --count;
                if (count <= 0)
                    throw new ApplicationException();
            }
            var numerator = (BigInteger)n;
            var denominator = (BigInteger)d;
            var gcd = BigInteger.GreatestCommonDivisor(BigInteger.Abs(numerator), denominator);
            numerator /= gcd;
            denominator /= gcd;
            Numerator = numerator;
            Denominator = denominator;
        }

        public MiniRational(BigInteger numerator, BigInteger denominator)
        {
            if (denominator == 0)
                throw new DivideByZeroException();
            if (denominator < 0)
            {
                numerator = -numerator;
                denominator = -denominator;
            }
            var gcd = BigInteger.GreatestCommonDivisor(BigInteger.Abs(numerator), denominator);
            numerator /= gcd;
            denominator /= gcd;
            Numerator = numerator;
            Denominator = denominator;
        }

        public MiniRational Abs()
        {
            return (new MiniRational(BigInteger.Abs(Numerator), Denominator));
        }

        public BigInteger Ceiling()
        {
            var q = Numerator / Denominator;
            return (q < this ? q + 1 : q);
        }

        public BigInteger Floor()
        {
            var q = Numerator / Denominator;
            return (q > this ? q - 1 : q);
        }

        public static MiniRational From(MiniRational x)
        {
            return (x);
        }

        public static MiniRational Invert(MiniRational x)
        {
            return (new MiniRational(x.Denominator, x.Numerator));
        }

        private static decimal Round五捨六入(decimal x)
        {
            var sign = 1;
            if (x < 0)
            {
                sign = -1;
                x = -x;
            }
            var truncate_x = System.Math.Truncate(x);
            var delta_x = x - truncate_x;
            if (delta_x <= 0.5m)
                return (sign * truncate_x);
            else
                return (sign * (truncate_x + 1));
        }

        public BigInteger Round(int mode)
        {
            var x = this;
            var n = x.Numerator;
            var d = x.Denominator;
            int sign = 1;
            if (n < 0)
            {
                sign = -1;
                n = -n;
            }
            var int_part = n / d;
            var frac_part = new MiniRational(n, d) - int_part;
            if (frac_part < 0 || frac_part >= 1)
                throw new ApplicationException();
            var half = new MiniRational(1, 2);
            var lower_value = int_part;
            var upper_value = frac_part > 0 ? int_part + 1 : int_part;


            switch (mode)
            {
                case 0:     // 数値が 2 つの数値の中間に位置する場合、最も近い偶数方向に丸められる。
                    if (frac_part < half)
                        return (sign * lower_value);
                    else if (frac_part > half)
                        return (sign * upper_value);
                    else if (lower_value.IsEven)
                        return (sign * lower_value);
                    else
                        return (sign * upper_value);

                case 1:     // 数値が 2 つの数値の中間に位置する場合、0 から遠い方の近似値に丸められる。
                    if (frac_part < half)
                        return (sign * lower_value);
                    else
                        return (sign * upper_value);

                case 1001:  // 正の無限大に近づくように丸められる。
                    return (sign >= 0 ?  sign * upper_value : sign * lower_value);

                case 1002:  // 0 に近づくように丸められる。
                    return (sign * lower_value);

                case 1003:  // 負の無限大に近づくように丸められる。
                    return (sign >= 0 ? sign * lower_value : sign * upper_value);

                case 1004:  // 数値が 2 つの数値の中間に位置する場合、0 から近い方の近似値に丸められる。
                    if (frac_part <= half)
                        return (sign * lower_value);
                    else
                        return (sign * upper_value);

                case 1005:  // 0 から離れるように丸められる。
                    return (sign * upper_value);
                default:
                    throw new ApplicationException();
            }
        }

        public MiniRational Round(int decimals, int mode)
        {
            switch (mode)
            {
                case 0:     // 数値が 2 つの数値の中間に位置する場合、最も近い偶数方向に丸められる。
                case 1:     // 数値が 2 つの数値の中間に位置する場合、0 から遠い方の近似値に丸められる。
                case 1001:  // 正の無限大に近づくように丸められる。
                case 1002:  // 0 に近づくように丸められる。
                case 1003:  // 負の無限大に近づくように丸められる。
                case 1004:  // 数値が 2 つの数値の中間に位置する場合、0 から近い方の近似値に丸められる。
                case 1005:  // 0 から離れるように丸められる。
                    if (decimals >= 0)
                    {
                        var factor = BigInteger.Pow(10, decimals);
                        return ((MiniRational)(this * factor).Round(mode) / factor);
                    }
                    else
                    {
                        var factor = BigInteger.Pow(10, -decimals);
                        return ((MiniRational)(this / factor).Round(mode) * factor);
                    }
                default:
                    throw new ApplicationException();
            }
        }

        private static BigInteger ToBigInt_Imp(MiniRational x)
        {
            int sign;
            BigInteger n;
            BigInteger d;
            if (x.Numerator >= 0)
            {
                sign = 1;
                n = x.Numerator;
                d = x.Denominator;
            }
            else
            {
                sign = -1;
                n = -x.Numerator;
                d = x.Denominator;
            }

            // Truncate する
            var int_part = n / d;
            var frac_part = new MiniRational(n - int_part * d, d);
            if (frac_part < 0 || frac_part >= 1)
                throw new ApplicationException();
            return (sign * int_part);
        }

        public Int32 ToInt32()
        {
            return ((Int32)ToBigInt_Imp(this));
        }

        public Int64 ToInt64()
        {
            return ((Int64)ToBigInt_Imp(this));
        }

        public UInt32 ToUInt32()
        {
            return ((UInt32)ToBigInt_Imp(this));
        }

        public UInt64 ToUInt64()
        {
            return ((UInt64)ToBigInt_Imp(this));
        }

        public BigInteger ToBigInt()
        {
            return (ToBigInt_Imp(this));
        }

        public BigInteger ToUBigInt()
        {
            var r = ToBigInt_Imp(this);
            if (r < 0)
                throw new OverflowException();
            return (r);
        }

        public static MiniRational Pow(MiniRational x, int n)
        {
            if (n >= 0)
                return (new MiniRational(BigInteger.Pow(x.Numerator, n), BigInteger.Pow(x.Denominator, n)));
            else
                return (new MiniRational(BigInteger.Pow(x.Denominator, -n), BigInteger.Pow(x.Numerator, -n)));
        }

        public int CompareTo(MiniRational x)
        {
            return ((Numerator * x.Denominator).CompareTo(x.Numerator * Denominator));
        }

        public static int Compare(MiniRational u, MiniRational v)
        {
            return (u.CompareTo(v));
        }

        public override bool Equals(object x)
        {
            if (x == null)
                return (false);
            if (x is Int32)
                return (Numerator.ToString().Equals(x.ToString()) && Denominator.Equals(1));
            if (x is UInt32)
                return (Numerator.ToString().Equals(x.ToString()) && Denominator.Equals(1));
            if (x is Int64)
                return (Numerator.ToString().Equals(x.ToString()) && Denominator.Equals(1));
            if (x is UInt64)
                return (Numerator.ToString().Equals(x.ToString()) && Denominator.Equals(1));
            if (x is BigInteger)
                return (Numerator.ToString().Equals(x.ToString()) && Denominator.Equals(1));
            if (x is MiniRational)
                return (Numerator.Equals(((MiniRational)x).Numerator) && Denominator.Equals(((MiniRational)x).Denominator));
            throw new ApplicationException();
        }

        public string ToString(string format, IFormatProvider provider)
        {
            int precision;
            var format_type = ParseFormat(format, provider, out precision);
            var value = (double)Numerator / (double)Denominator;
            int sign = 1;
            if (value < 0)
            {
                sign = -1;
                value = -value;
            }
            double value_round_even;
            switch (format_type.ToLower())
            {
                case "c":
                case "f":
                case "n":
                case "p":
                    value_round_even = System.Math.Round(value, precision, MidpointRounding.ToEven);
                    break;
                case "e":
                    value_round_even = 指数表記で丸め(value, precision);
                    break;
                case "g":
                    value_round_even = 指数表記で丸め(value, precision - 1);
                    break;
                default:
                    throw new ApplicationException();
            }
            return ((sign * value_round_even).ToString(format, provider));
        }

        private static double 指数表記で丸め(double value, int precision)
        {
            if (value == 0)
                return (0);
            double value_round_even;
            int exp = 0;
            while (value >= 10)
            {
                value /= 10;
                exp++;
            }
            while (value < 1)
            {
                value *= 10;
                exp--;
            }
            value_round_even = System.Math.Round(value, precision, MidpointRounding.ToEven);
            while (exp > 0)
            {
                value_round_even *= 10;
                --exp;
            }
            while (exp < 0)
            {
                value_round_even /= 10;
                ++exp;
            }

            return (value_round_even);
        }

        private static string ParseFormat(string format, IFormatProvider provider, out int precision)
        {
            if (string.IsNullOrEmpty(format))
                format = "G";
            var number_format = provider as NumberFormatInfo;
            var format_type = format.Substring(0, 1);
            var precision_str = format.Substring(1);
            if (precision_str == "")
            {
                switch (format_type.ToLower())
                {
                    case "c":
                        precision_str = number_format.CurrencyDecimalDigits.ToString();
                        break;
                    case "f":
                    case "n":
                        precision_str = number_format.NumberDecimalDigits.ToString();
                        break;
                    case "p":
                        precision_str = number_format.PercentDecimalDigits.ToString();
                        break;
                    case "e":
                        precision_str = "6";
                        break;
                    case "g":
                        precision_str = "15";
                        break;
                    default:
                        throw new ApplicationException();
                }
            }
            precision = int.Parse(precision_str);
            if (format_type.ToLower() == "g" && precision == 0)
                precision = 15;
            return (format_type);
        }

        public static MiniRational Parse(string s, NumberStyles style, IFormatProvider provider)
        {
            return (new MiniRational(decimal.Parse(s, style, provider)));
        }

        public static bool TryParse(string s, NumberStyles style, IFormatProvider provider, out MiniRational value)
        {
            decimal value_double;
            var result = decimal.TryParse(s, style, provider, out value_double);
            value = new MiniRational(value_double);
            return (result);
        }

        public static implicit operator MiniRational(int x)
        {
            return (new MiniRational(x, 1));
        }

        public static implicit operator MiniRational(uint x)
        {
            return (new MiniRational(x, 1));
        }

        public static implicit operator MiniRational(long x)
        {
            return (new MiniRational(x, 1));
        }

        public static implicit operator MiniRational(ulong x)
        {
            return (new MiniRational(x, 1));
        }

        public static implicit operator MiniRational(BigInteger x)
        {
            return (new MiniRational(x, 1));
        }

        public static implicit operator MiniRational(double x)
        {
            return (new MiniRational(x));
        }

        public static implicit operator MiniRational(decimal x)
        {
            return (new MiniRational(x));
        }

        public static MiniRational operator +(MiniRational u, MiniRational v)
        {
            return (new MiniRational(u.Numerator * v.Denominator + u.Denominator * v.Numerator, u.Denominator * v.Denominator));
        }

        public static MiniRational operator -(MiniRational u, MiniRational v)
        {
            return (new MiniRational(u.Numerator * v.Denominator - u.Denominator * v.Numerator, u.Denominator * v.Denominator));
        }

        public static MiniRational operator *(MiniRational u, MiniRational v)
        {
            return (new MiniRational(u.Numerator * v.Numerator, u.Denominator * v.Denominator));
        }

        public static MiniRational operator /(MiniRational u, MiniRational v)
        {
            return (new MiniRational(u.Numerator * v.Denominator, u.Denominator * v.Numerator));
        }

        public static bool operator ==(MiniRational u, MiniRational v)
        {
            return (u.Equals(v));
        }

        public static bool operator !=(MiniRational u, MiniRational v)
        {
            return (!u.Equals(v));
        }

        public static bool operator >(MiniRational u, MiniRational v)
        {
            return (u.CompareTo(v) > 0);
        }

        public static bool operator <(MiniRational u, MiniRational v)
        {
            return (u.CompareTo(v) < 0);
        }

        public static bool operator >=(MiniRational u, MiniRational v)
        {
            return (u.CompareTo(v) >= 0);
        }

        public static bool operator <=(MiniRational u, MiniRational v)
        {
            return (u.CompareTo(v) <= 0);
        }

        public override int GetHashCode()
        {
            return (Numerator.GetHashCode() ^ Denominator.GetHashCode());
        }

        public BigInteger Numerator { get; }
        public BigInteger Denominator { get; }

    }
}
