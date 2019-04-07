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
            var u = BigInt.FromByteArray(new byte[] { 0x03, 0x04, 0xef, 0xcd, 0xab, 0x89 });
            var s1 = u.ToString("x");
            Console.ReadLine();
        }
    }

}