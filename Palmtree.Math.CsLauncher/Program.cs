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
            using (var r = new CryptoRandom())
            {
                for (var count = 0; count < 10000; ++count)
                    r.GenerateDouble();
            }
            Console.ReadLine();
        }
    }

}