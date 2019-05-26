using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Globalization;
using Palmtree.Math;
using Palmtree.Security.Cryptography;

namespace Palmtree.Math.CsLauncher
{
    class Program
    {

        static void Main(string[] args)
        {
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x01, 0x01 });
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x04, 0xd2, 0x02, 0x96, 0x49 });
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x08, 0xd2, 0x0a, 0x1f, 0xeb, 0x8c, 0xa9, 0x54, 0xab });
            //var u = UBigInt.FromByteArray(new byte[] { 0x01, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 });
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x09, 0xff, 0xff, 0x0f, 0x63, 0x2d, 0x5e, 0xc7, 0x6b, 0x05 });
            //var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x09, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 });
            //var u = BigInt.FromByteArray(new byte[] { 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            //var v = 1UL;
            //var u = 1234567890U;
            //var u = 4294967295U;
            //var u = 4294967296UL;
            //var u = 12345678901234567890UL;

            var u = UBigInt.FromByteArray(new byte[] { 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            var v = BigInt.FromByteArray(new byte[] { 0x03, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            var w = u.BitwiseOr(v);
            Console.ReadLine();
        }

        private static void 逆元テーブル変換の検証()
        {
            var _2の8乗を法とした逆元テーブル = Enumerable.Range(0, 256)
                .Select(n => n % 2 == 0 ? BigInteger.Zero : 逆元を求める((BigInteger)n, 256))
                .ToArray();

            var _2の16乗を法とした逆元テーブル = Enumerable.Range(0, 65536)
                .Select(n => n % 2 == 0 ? BigInteger.Zero : 逆元を求める((BigInteger)n, (BigInteger)65536))
                .ToArray();

            for (var y = 0; y < 16; ++y)
            {
                for (var x = 1; x < 16; x += 2)
                {
                    var index = y * 16 + x;
                    Console.Write("{0}, ", _2の8乗を法とした逆元テーブル[index]);
                }
                Console.WriteLine();
            }
            Console.WriteLine(逆元を求める(3, BigInteger.One << 32));
            Console.WriteLine(逆元を求める(3, BigInteger.One << 64));
            Console.ReadLine();

            for (var n = 1; n < 65536; n += 2)
            {
                var inverse8 = _2の8乗を法とした逆元テーブル[n & 0xff];
                var inverse16 = (2 * inverse8 - inverse8 * inverse8 * n).Mod(65536);
                if (inverse16 != _2の16乗を法とした逆元テーブル[n])
                    throw new ApplicationException();
            }
        }

        private static BigInteger 逆元を求める(BigInteger value, BigInteger m)
        {
            var r = ExtendedEuclideanAlgorithm(value, m);
            var r_value = r.Item2.Mod(m);
            if ((value * r_value).Mod(m) != 1)
                throw new ApplicationException();
            return (r_value);
        }

        private static UBigInt 完全除算_3(UBigInt u)
        {
            var inverse_3 = 2863311531;
            var q_digits = new UInt32[0];
            while (u >= 0x100000000)
            {
                // u の桁が 2 ワード以上残っている場合
                var u0 = u & 0xffffffffU;
                var q0 = ((UBigInt)u0 * inverse_3) & 0xffffffffU;
                u = u.USubtruct((UBigInt)q0 * 3U);
                q_digits = q_digits.Append(q0).ToArray();
                if ((u & 0xffffffff) != 0)
                    throw new ApplicationException();
                u >>= 32;
            }
            if (u % 3 != 0)
                throw new ApplicationException();
            q_digits = q_digits.Append((UInt32)u / 3).ToArray();
            var q = UBigInt.Zero;
            for (var index = q_digits.Length - 1; index >= 0; --index)
            {
                q = (q << 32) | q_digits[index];
            }

            return (q);
        }

        private static Tuple<BigInteger, BigInteger, BigInteger> ExtendedEuclideanAlgorithm(BigInteger a, BigInteger b)
        {
            if (a.IsZero)
                throw new ArgumentOutOfRangeException();
            if (b.IsZero)
                throw new ArgumentOutOfRangeException();
            var previous_x = BigInteger.One;
            var previous_y = BigInteger.Zero;
            var current_x = BigInteger.Zero;
            var current_y = BigInteger.One;
            while (!b.IsZero)
            {
                var next_b = a % b;
                var q = a / b;
                var next_x = previous_x - q * current_x;
                var next_y = previous_y - q * current_y;
                a = b;
                b = next_b;
                previous_x = current_x;
                current_x = next_x;
                previous_y = current_y;
                current_y = next_y;
            }
            return (new Tuple<BigInteger, BigInteger, BigInteger>(a, previous_x, previous_y));
        }
    }

    static class BigIntegerExtensions
    {
        public static BigInteger Mod(this BigInteger u, BigInteger v)
        {
            var r = u % v;
            return (r < 0 ? v + r : r);
        }
    }

}