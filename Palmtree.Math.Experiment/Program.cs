using System;
using System.Globalization;
using System.Linq;
using System.Numerics;

namespace Palmtree.Math.Experiment
{
    class Program
    {
        static void Main(string[] args)
        {
            //ModPowの障害調査コード();

            //DivRemの障害調査コード();

            // 数字の書式に含まれる各種記号の文字数_通貨記号は複数文字のカルチャあり_正負符号と小数点と3桁区切りカンマとパーセント記号パーミル記号は2文字以上のカルチャはない();

            //Currency_Number_PercentによってDecimalSeparatorあるいはGeoupSeparatorが異なるカルチャはいくつか存在する();


            var x1 = typeof(UInt32).IsSubclassOf(typeof(Exception));
            Console.WriteLine(typeof(UInt32).Name);
            Console.WriteLine(typeof(UInt32).FullName);
            Console.WriteLine(typeof(ApplicationException).Name);
            Console.WriteLine(typeof(ApplicationException).FullName);
            var x2 = typeof(ApplicationException).IsSubclassOf(typeof(Exception));

            try
            {
                throw new ApplicationException();
            }
            catch (Exception ex)
            {
                Console.WriteLine(string.Format("ex.GetType()='{0}'", ex.GetType()));
            }

            Console.ReadLine();
        }

        private static void Currency_Number_PercentによってDecimalSeparatorあるいはGeoupSeparatorが異なるカルチャはいくつか存在する()
        {
            var texts = CultureInfo.GetCultures(CultureTypes.AllCultures)
                        .Where(culture => culture.NumberFormat.CurrencyDecimalSeparator != culture.NumberFormat.NumberDecimalSeparator ||
                                          culture.NumberFormat.CurrencyGroupSeparator != culture.NumberFormat.NumberGroupSeparator ||
                                          culture.NumberFormat.CurrencyDecimalSeparator != culture.NumberFormat.PercentDecimalSeparator ||
                                          culture.NumberFormat.CurrencyGroupSeparator != culture.NumberFormat.PercentGroupSeparator)
                        .Select(culture => string.Format("{0},{1}/{2}/{3}/{4}/{5}/{6}/{7}/{8}/{9}/{10}/{11}",
                                                         culture.Name,
                                                         culture.NumberFormat.PositiveSign,
                                                         culture.NumberFormat.NegativeSign,
                                                         culture.NumberFormat.CurrencySymbol,
                                                         culture.NumberFormat.PercentSymbol,
                                                         culture.NumberFormat.PerMilleSymbol,
                                                         culture.NumberFormat.CurrencyDecimalSeparator,
                                                         culture.NumberFormat.CurrencyGroupSeparator,
                                                         culture.NumberFormat.NumberDecimalSeparator,
                                                         culture.NumberFormat.NumberGroupSeparator,
                                                         culture.NumberFormat.PercentDecimalSeparator,
                                                         culture.NumberFormat.PercentGroupSeparator));
            foreach (var text in texts)
                Console.WriteLine(text);
        }

        private static void 数字の書式に含まれる各種記号の文字数_通貨記号は複数文字のカルチャあり_正負符号と小数点と3桁区切りカンマとパーセント記号パーミル記号は2文字以上のカルチャはない()
        {
            var texts = CultureInfo.GetCultures(CultureTypes.AllCultures)
                        .Where(culture => culture.NumberFormat.CurrencyDecimalSeparator.Length >= 2 ||
                                          culture.NumberFormat.CurrencyGroupSeparator.Length >= 2 ||
                                          //culture.NumberFormat.CurrencySymbol.Length >= 2 ||
                                          culture.NumberFormat.NegativeSign.Length >= 2 ||
                                          culture.NumberFormat.NumberDecimalSeparator.Length >= 2 ||
                                          culture.NumberFormat.NumberGroupSeparator.Length >= 2 ||
                                          culture.NumberFormat.PercentDecimalSeparator.Length >= 2 ||
                                          culture.NumberFormat.PercentGroupSeparator.Length >= 2 ||
                                          culture.NumberFormat.PercentSymbol.Length >= 2 ||
                                          culture.NumberFormat.PerMilleSymbol.Length >= 2 ||
                                          culture.NumberFormat.PositiveSign.Length >= 2)
                        .Select(culture => string.Format("{0},{1}/{2}/{3}/{4}/{5}/{6}/{7}/{8}/{9}/{10}/{11}",
                                                         culture.Name,
                                                         culture.NumberFormat.PositiveSign,
                                                         culture.NumberFormat.NegativeSign,
                                                         culture.NumberFormat.CurrencySymbol,
                                                         culture.NumberFormat.PercentSymbol,
                                                         culture.NumberFormat.PerMilleSymbol,
                                                         culture.NumberFormat.CurrencyDecimalSeparator,
                                                         culture.NumberFormat.CurrencyGroupSeparator,
                                                         culture.NumberFormat.NumberDecimalSeparator,
                                                         culture.NumberFormat.NumberGroupSeparator,
                                                         culture.NumberFormat.PercentDecimalSeparator,
                                                         culture.NumberFormat.PercentGroupSeparator));
            foreach (var text in texts)
                Console.WriteLine(text);
        }

        private static void NativeDigitsにUTF16で複数文字から構成される文字を持つカルチャが存在しないことの確認()
        {
            var NativeDigitが0123456789ではないカルチャの一覧 = CultureInfo.GetCultures(CultureTypes.AllCultures)
                    .Select(culture => new { name = culture.Name, digits = string.Concat(culture.NumberFormat.NativeDigits) })
                    .Where(item => item.digits != "0123456789")
                    .Select(item => new
                    {
                        text = string.Format("{0}: {1}({2})", item.name, item.digits, string.Join(", ", item.digits.Select(c => string.Format("U+{0:x4}", (int)c)))),
                        digits = item.digits,
                    });
            foreach (var item in NativeDigitが0123456789ではないカルチャの一覧.Where(item => item.digits.Length != 10))
                Console.WriteLine(item.text);
        }

        private static void DivRemの障害調査コード()
        {
            var u = BigInteger.Parse("99999999999999999999999999999999999999999999999999999999981110534068521419145216000000000000000000000000000000000000892029807941224925661617625565249246047764459999999999999999999999999999999999982159403841175501486773314328474458653301145600000000000000000000000000000000000089202980794122492566123983624661967443066881");
            var v = BigInteger.Parse("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
            var desired_q = u / v;
            var desired_r = u % v;
            BigInteger actual_q;
            BigInteger actual_r;

            DivRem(u, v, out actual_q, out actual_r);

            if (desired_q != actual_q)
                throw new ApplicationException();
            if (desired_r != actual_r)
                throw new ApplicationException();
        }

        private static void DivRem(BigInteger u, BigInteger v, out BigInteger q, out BigInteger r)
        {
            if (u == 0)
                throw new ApplicationException();
            if (v == 0)
                throw new ApplicationException();

            var u_buf = u.To__UNIT_TYPEArray();
            var v_buf = v.To__UNIT_TYPEArray();

            if (u_buf.Length < v_buf.Length)
            {
                q = 0;
                r = u;
            }
            else  if (v_buf.Length == 1)
            {
                var q_buf = new UInt32[u_buf.Length];
                UInt32 temp_r;
                DivRem_X_1W(u_buf, v_buf[0], q_buf, out temp_r);
                q = q_buf.ToBigInteger();
                r = new[] { temp_r }.ToBigInteger();
            }
            else
            {
                UInt32[] q_buf;
                UInt32[] r_buf;
                DivRem_X_X( u_buf, v_buf, out q_buf, out r_buf);
                q = q_buf.ToBigInteger();
                r = r_buf.ToBigInteger();
            }
        }

        private static void DivRem_X_X(UInt32[] u_buf, UInt32[] v_buf, out UInt32[] q_buf, out UInt32[] r_buf)
        {
            var n_plus_m = u_buf.Length;
            var n = v_buf.Length;
            var m = n_plus_m - n;
            Console.WriteLine("uとvのシフト");
            Console.WriteLine(string.Format("  u: {0}", u_buf.ToBigInteger().Dump()));
            Console.WriteLine(string.Format("  v: {0}", v_buf.ToBigInteger().Dump()));
            var d_factor = v_buf[v_buf.Length - 1].LZCNT();
            u_buf = (u_buf.ToBigInteger() << d_factor).To__UNIT_TYPEArray().Padding(n + m + 1);
            v_buf = (v_buf.ToBigInteger() << d_factor).To__UNIT_TYPEArray();
            Console.WriteLine(string.Format("  ⇒u: {0}", u_buf.ToBigInteger().Dump()));
            Console.WriteLine(string.Format("  ⇒v: {0}", v_buf.ToBigInteger().Dump()));
            if (u_buf.Length != n_plus_m + 1)
                throw new ApplicationException();
            if (v_buf.Length != n)
                throw new ApplicationException();
            if ((v_buf[v_buf.Length - 1] & 0x80000000U) == 0)
                throw new ApplicationException();
            var q_array = new UInt32[m + 1];
            for (var q_index = m ; q_index >= 0; --q_index)
            {
                var uj = u_buf[n + q_index];
                var uj1 = u_buf[n + q_index - 1];
                var uj2 = u_buf[n + q_index - 2];
                var v1 = v_buf[n - 1];
                var v2 = v_buf[n - 2];
                var q_ = Qの決定(uj, uj1, uj2, v1, v2);

                Console.WriteLine("uの減算");
                Console.WriteLine(string.Format("  u: {0}", u_buf.ToBigInteger().Dump()));
                Console.WriteLine(string.Format("  v: {0}", v_buf.ToBigInteger().Dump()));
                Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
                var temp_u = u_buf.ToBigInteger();
                var temp_v = v_buf.ToBigInteger() << (32 * q_index);
                temp_u -= temp_v * q_;
                Console.WriteLine(string.Format("  ⇒u: {0}", temp_u.Dump()));
                if (temp_u < 0)
                {
                    Console.WriteLine("uの加え戻しとq_の更新");
                    Console.WriteLine(string.Format("  u: {0}", temp_u.Dump()));
                    --q_;
                    temp_u += temp_v;
                    Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
                    Console.WriteLine(string.Format("  ⇒u: {0}", temp_u.Dump()));
                }
                if (temp_u >= temp_v)
                    throw new ApplicationException();
                if (temp_u < 0)
                    throw new ApplicationException();
                u_buf = temp_u.To__UNIT_TYPEArray().Padding(n + m + 1);
                q_array[q_index] = q_;
                Console.WriteLine("qの現在値");
                Console.WriteLine(string.Format("  q: {0}", q_array.ToBigInteger().Dump()));
            }
            q_buf = q_array;
            r_buf = (u_buf.ToBigInteger() >> d_factor).To__UNIT_TYPEArray();
            Console.WriteLine("計算終了");
            Console.WriteLine(string.Format("  q: {0}", q_buf.ToBigInteger().Dump()));
            Console.WriteLine(string.Format("  r: {0}", r_buf.ToBigInteger().Dump()));
        }

        private static uint Qの決定(uint uj, uint uj1, uint uj2, uint v1, uint v2)
        {
            var q_ = uj == v1 ? 0xffffffffU : (UInt32)(new[] { uj1, uj }.ToBigInteger() / v1);

            Console.WriteLine("q_ の計算");
            Console.WriteLine(string.Format("  uj: 0x{0:x8}", uj));
            Console.WriteLine(string.Format("  uj1: 0x{0:x8}", uj1));
            Console.WriteLine(string.Format("  v1: 0x{0:x8}", v1));
            Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
            if (Qの検査(q_, uj, uj1, uj2, v1, v2))
            {
                --q_;
                Console.WriteLine("q_ の更新");
                Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
                if (Qの検査(q_, uj, uj1, uj2, v1, v2))
                {
                    --q_;
                    Console.WriteLine("q_ の更新");
                    Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
                }
            }
            return (q_);
        }

        private static bool Qの検査(UInt32 q_, UInt32 uj, UInt32 uj1, UInt32 uj2, UInt32 v1, UInt32 v2)
        {
            Console.WriteLine("q_ の検査");
            Console.WriteLine(string.Format("  q_: 0x{0:x8}", q_));
            Console.WriteLine(string.Format("  uj: 0x{0:x8}", uj));
            Console.WriteLine(string.Format("  uj1: 0x{0:x8}", uj1));
            Console.WriteLine(string.Format("  uj2: 0x{0:x8}", uj2));
            Console.WriteLine(string.Format("  v1: 0x{0:x8}", v1));
            Console.WriteLine(string.Format("  v2: 0x{0:x8}", v2));
            var 左辺 = new[] { v2, v1 }.ToBigInteger() * q_;
            var 右辺 = new[] { uj2, uj1, uj }.ToBigInteger();
            Console.WriteLine(string.Format("  result: {0}", 左辺 > 右辺 ? "0x00000001" : "0x00000000"));
            return (左辺 > 右辺);
        }

        private static void DivRem_X_1W(uint[] u_buf, uint v, uint[] q_buf, out UInt32 r_buf)
        {
            var r = BigInteger.Zero;
            for (var index = u_buf.Length; index > 0; --index)
            {
                var t = (r << 32) | u_buf[index - 1];
                r = t % v;
                q_buf[index - 1] = (UInt32)(t / v);
            }
            r_buf = (UInt32)r;
        }

        private static UInt32 _DIVREM_UNIT(UInt32 u_hi, UInt32 u_lo, UInt32 v, out UInt32 r)
        {
            var u = (new BigInteger(u_hi) << 32) | u_lo;
            r = (UInt32)(u % v);
            return ((UInt32)(u / v));
        }

        private static void ModPowの障害調査コード()
        {
            var v = BigInteger.Parse("99999999999999999999999999999999999999999999999999999999999999999999999999999999");
            var e = BigInteger.Parse("9999999999");
            var m = BigInteger.Parse("9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999");
            var desired_r = BigInteger.ModPow(v, e, m);
            var actual_r = EmurateModPow(v, e, m);
            Console.WriteLine(string.Format("desired_r={0}", desired_r));
            Console.WriteLine(string.Format(" actual_r={0}", actual_r));
            Console.WriteLine(string.Format(" actual_r{0}desired_r", actual_r == desired_r ? "==" : "!="));
            Console.ReadLine();
        }

        private static BigInteger EmurateModPow(BigInteger v, BigInteger e, BigInteger m)
        {
            v = v % m;
            var e_mask = BigInteger.One;
            while (e_mask < e)
                e_mask <<= 1;
            e_mask >>= 1;
            var u = BigInteger.One;
            while (e_mask != 0)
            {
                Console.WriteLine("w := u * u");
                Console.WriteLine(string.Format("  u: {0}", u.Dump()));
                u = u * u;
                Console.WriteLine(string.Format("  w: {0}", u.Dump()));

                Console.WriteLine("w := u % m");
                Console.WriteLine(string.Format("  u: {0}", u.Dump()));
                Console.WriteLine(string.Format("  m: {0}", m.Dump()));
                u = u % m;
                Console.WriteLine(string.Format("  w: {0}", u.Dump()));

                Console.WriteLine("bit check");
                Console.WriteLine(string.Format("  e & e_mask: {0}", (e & e_mask).Dump()));
                if ((e & e_mask) != 0)
                {
                    Console.WriteLine("w := u * v");
                    Console.WriteLine(string.Format("  u: {0}", u.Dump()));
                    Console.WriteLine(string.Format("  v: {0}", v.Dump()));
                    u = u * v;
                    Console.WriteLine(string.Format("  w: {0}", u.Dump()));

                    Console.WriteLine("w := u % m");
                    Console.WriteLine(string.Format("  u: {0}", u.Dump()));
                    Console.WriteLine(string.Format("  m: {0}", m.Dump()));
                    u = u % m;
                    Console.WriteLine(string.Format("  w: {0}", u.Dump()));
                }
                e_mask >>= 1;
            }
            var actual_r = u;
            return actual_r;
        }
    }
}
