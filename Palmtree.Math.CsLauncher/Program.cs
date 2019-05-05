using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Numerics;
using System.Globalization;
using Palmtree.Math;

namespace Palmtree.Math.CsLauncher
{
    class Program
    {
        static void Main(string[] args)
        {
            var u = UBigInt.FromByteArray(new byte[] { 0x01, 0x04, 0xd2, 0x02, 0x96, 0x49 });
            var v = UBigInt.FromByteArray(new byte[] { 0x01, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 });
            var w = u.Multiply(MultiplicationMethod.FixedKaratsuba, v);
            Console.ReadLine();
        }
    }

}