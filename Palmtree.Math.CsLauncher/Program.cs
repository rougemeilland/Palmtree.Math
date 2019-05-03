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
            var x = UBigInt.From(1U);
            var s = x.ToString();
            var b = x.ToByteArray();
            Console.ReadLine();
        }
    }

}