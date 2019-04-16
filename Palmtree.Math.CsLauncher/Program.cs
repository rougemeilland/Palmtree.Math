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
            var x = Rational.FromByteArray(new byte[] { 0x10, 0x01, 0x02, 0xa5, 0x09, 0x01, 0x01, 0x14 });
            Console.WriteLine(x.ToString(@"g"));
            Console.ReadLine();
        }
    }

}