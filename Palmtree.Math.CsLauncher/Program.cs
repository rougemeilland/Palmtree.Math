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
            var dd = ConstructDoubleValue(0x001fffffffffffffLU, 1).ToString("G19");

            using (var r = new Random(0))
            {
                var x1 = r.GenerateUint32();
                var x2 = r.GenerateUint64();
                var x3 = r.GenerateDouble();
                Console.WriteLine("---------");
                for (var count = 0; count < 100; count++)
                    Console.Write(r.GenerateUBigInt(4) + ", ");
                Console.WriteLine("\n---------");
                for (var count = 0; count < 100; count++)
                    Console.Write(r.GenerateRational(4) + ", ");
                Console.WriteLine("\n---------");
            }
            Console.ReadLine();
            using (var r = new Palmtree.Security.Cryptography.CryptoRandom())
            {
                var x1 = r.GenerateUint32();
                var x2 = r.GenerateUint64();
                var x3 = r.GenerateDouble();
                Console.WriteLine("---------");
                for (var count = 0; count < 100; count++)
                    Console.Write(r.GenerateDouble() + ", ");
                Console.WriteLine("\n---------");
                for (var count = 0; count < 100; count++)
                    Console.Write(r.GenerateUBigInt(4) + ", ");
                Console.WriteLine("\n---------");
                for (var count = 0; count < 100; count++)
                    Console.Write(r.GenerateRational(4) + ", ");
                Console.WriteLine("\n---------");
            }
            Console.ReadLine();
        }

        private static double ConstructDoubleValue(UInt64 mantissa, UInt32 exponent)
        {
            exponent += 52U;
            var result = (double)mantissa;
            while (exponent >= 32)
            {
                result /= 0x0000000100000000UL;
                exponent -= 32;
            }
            if ((exponent & 0x10) != 0)
                result /= 0x10000U;
            if ((exponent & 0x8) != 0)
                result /= 0x100U;
            if ((exponent & 0x4) != 0)
                result /= 0x10U;
            if ((exponent & 0x2) != 0)
                result /= 0x4U;
            if ((exponent & 0x1) != 0)
                result /= 0x2U;

            if (result < 0 || result >= 1.0)
                throw new InternalErrorException();
            return result;
        }

    }

}