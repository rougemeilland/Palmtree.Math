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
            var u = Rational.FromByteArray(new byte[] { 0x10, 0x01, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            var v = Rational.FromByteArray(new byte[] { 0x10, 0x01, 0x01, 0x01, 0x01, 0x05, 0x00, 0x00, 0x00, 0x00, 0x01 });
            var w = u.Subtruct(v);
            Console.ReadLine();
        }
    }

}