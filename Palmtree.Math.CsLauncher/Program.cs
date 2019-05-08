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
            var m = UBigInt.One << 32;
            var _3 = UBigInt.From(3);
            var r = _3.ExtendedEuclideanAlgorithm(m);
            var _2の32乗を法とした3の逆元 = r.Item2;
            if ((_2の32乗を法とした3の逆元 * _3) % m != UBigInt.One)
                throw new ApplicationException();
        }

    }
}