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
            using (var r = new Random(0))
            {
                for (var count = 0; count < 10000; ++count)
                {
                    var x1 = r.GenerateUint64();
                    var x2 = r.GenerateUint32();
                    Console.WriteLine(string.Format("{0}, {1}", x1, x2));
                }
            }
            Console.ReadLine();
        }
    }

}