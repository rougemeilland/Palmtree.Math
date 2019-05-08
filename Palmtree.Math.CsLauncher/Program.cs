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
        /*
  <dataitem index="87">
    <param1 type="ubigint">01,09,00,00,00,00,00,00,00,00,01</param1>
    <param2 type="uint64">9999999999</param2>
    <result1 type="ubigint">01,04,67,7f,f3,6d</result1>
  </dataitem>
         */


        static void Main(string[] args)
        {
            var u = 12345678901234567890UL;
            var v = UBigInt.From(1);
            var r = u.Add(v);
            Console.ReadLine();
        }
    }

}