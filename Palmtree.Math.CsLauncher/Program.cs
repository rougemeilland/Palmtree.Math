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
            Int64 u = -4294967297;
            UBigInt v = UBigInt.One;
            var w = v.BitwiseOr(u);
            Console.ReadLine();
        }
    }

}