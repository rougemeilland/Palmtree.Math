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

            var u = BigInt.FromByteArray(new byte[] { 03, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff });
            var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 });
            u.Mod(v);




            var m = UBigInt.One << 32;
            var _3 = UBigInt.From(3);
            var r = _3.ExtendedEuclideanAlgorithm(m);
            var _2の32乗を法とした3の逆元 = r.Item2.Mod(m);
            if ((_2の32乗を法とした3の逆元 * _3).Mod(m) != UBigInt.One)
                throw new ApplicationException();
        }

    }
}