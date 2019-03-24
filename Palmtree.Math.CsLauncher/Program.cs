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
            UInt32 u = 4294967295;
            UBigInt v = UBigInt.Zero;
            var w = u.Subtruct(v);

            Console.ReadLine();
        }
    }

}