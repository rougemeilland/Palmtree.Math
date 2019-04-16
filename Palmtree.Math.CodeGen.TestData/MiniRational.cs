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
            var r = new MiniRational(-1, BigInteger.Parse("2000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000", NumberStyles.AllowHexSpecifier));
            var d = r.ToDouble();
        }

        public MiniRational(decimal x)
        {
            var bits = decimal.GetBits(x);
            var n = ((BigInteger)(UInt32)bits[2] << 64) | ((BigInteger)(UInt32)bits[1] << 32) | (BigInteger)(UInt32)bits[0];
            if ((bits[3] & 0x80000000) != 0)
                n = -n;
            var d = BigInteger.Pow(10, (byte)((bits[3] >> 16) & 0x7f));
            Numerator = n;
            Denominator = d;
            var gcd = BigInteger.GreatestCommonDivisor(BigInteger.Abs(Numerator), Denominator);
            Numerator /= gcd;
            Denominator /= gcd;
            if (Denominator <= 0)
                throw new ApplicationException();
        }

        public MiniRational(double x)
        {
            var n = x;
            var d = BigInteger.One;
            var count = 200;
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
            if (Denominator <= 0)
                throw new ApplicationException();
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
            if (Denominator <= 0)
                throw new ApplicationException();
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
                    return (sign >= 0 ? sign * upper_value : sign * lower_value);

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

        public decimal ToDecimal()
        {
            if (Numerator == 0)
                return (0m);
            var sign = Numerator.Sign;
            var n = BigInteger.Abs(Numerator) * BigInteger.Pow(10, 28);
            var d = Denominator;
            var scale = 28;
            var limit = (BigInteger.One << 96) - 1;
            while (scale > 0 && n > d * limit)
            {
                --scale;
                if (n % 10 == 0)
                    n /= 10;
                else
                    d *= 10;
            }
            if (n > d * limit)
                throw new OverflowException();
            // この時点で 0 <= scale <= 127 かつ 0 < n/d <= limit
            var int_part = n / d;
            var frac_part_n = n % d;
            var frac_part_d = d;
            var frac_part_n2 = frac_part_n * 2;
            if (frac_part_n2 > frac_part_d)
                ++int_part;
            else if (frac_part_n2 < frac_part_d)
            {
            }
            else
            {
                if (int_part.IsEven)
                {
                }
                else
                {
                    ++int_part;
                }
            }
            if (int_part > limit)
                throw new OverflowException();

            while (int_part % 10 == 0 && scale > 0)
            {
                int_part /= 10;
                --scale;
            }

            return (new decimal((int)(uint)(int_part & 0xffffffff),
                                (int)(uint)((int_part >> 32) & 0xffffffff),
                                (int)(uint)((int_part >> 64) & 0xffffffff),
                                sign < 0,
                                (byte)scale));
        }

        public double ToDouble()
        {
            var sign = Numerator.Sign;
            var n = BigInteger.Abs(Numerator) << 1022;
            var d = Denominator;
            var scale = -1022;
            while (n.IsEven && d.IsEven)
            {
                n >>= 1;
                d >>= 1;
            }
            if (n < d)
            {
                // 非正規化数を返・・・したいのだが c# では非正規化数は表現できないので、0を返す。大丈夫か？
                return (0d);
            }
            while (scale < 1023 && n >= 2 * d)
            {
                if (n.IsEven)
                    n >>= 1;
                else
                    d <<= 1;
                ++scale;
            }
            if (n >= 2 * d)
                return (sign < 0 ? double.NegativeInfinity : double.PositiveInfinity);
            var int_part = (n << 52) / d;
            var frac_part_n = (n << 52) % d;
            var frac_part_d = d;
            // 整数部の丸め
            if (frac_part_n * 2 > frac_part_d)
            {
                ++int_part;
            }
            else if (frac_part_n * 2 < frac_part_d)
            {
            }
            else
            {
                if (int_part.IsEven)
                {
                }
                else
                {
                    ++int_part;
                }
            }
            if (int_part >= (BigInteger.One << 53))
            {
                int_part >>= 1;
                ++scale;
            }
            if (int_part < (BigInteger.One << 52) || int_part >= (BigInteger.One << 53))
                throw new ApplicationException(string.Format("エラー: Numerator={0}, Denominator={1}", Numerator, Denominator));
            if (scale > 1023 || scale < -1022)
                throw new ApplicationException();
            scale -= 52;
            var r = (double)int_part;
            if (scale > 0)
                r *= (double)(BigInteger.One << scale);
            else if (scale < 0)
                r /= (double)(BigInteger.One << -scale);
            else
            {
            }
            if (sign < 0)
                r = -r;
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
            var value = (double)Numerator / (double)Denominator;
            return (value.ToString(format, provider));
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
