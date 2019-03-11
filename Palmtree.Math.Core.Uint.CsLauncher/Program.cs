using System;
using System.Numerics;
using System.Globalization;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Palmtree.Math;

namespace Palmtree.Math.Core.Uint.CsLauncher
{
    class Program
    {
        static void Main(string[] args)
        {
            var u1_array = new byte[] { 0x01, 0xe8, 0x03 };
            var u1 = UBigInt.FromByteArray(u1_array);
            var r1 = u1.FloorLog10(); // 3が正解

            var u2_array = new byte[] { 0x01, 0xff, 0xe3, 0x0b, 0x54, 0x02 };
            var u2 = UBigInt.FromByteArray(u2_array);
            var r2 = u2.FloorLog10(); // 9が正解
            Console.ReadLine();
        }
    }
}