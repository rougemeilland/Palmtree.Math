using System;
using Palmtree.Math;
using System.Numerics;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Palmtree.Math.Experiment.Pie
{
    class Program
    {
        static void Main(string[] args)
        {
            性能測定_BigInt((u, v) => u + v, "加算", 1000000);
            性能測定_BigInteger((u, v) => u + v, "加算", 1000000);
            Console.WriteLine();

            性能測定_BigInt((u, v) => u + v, "加算", 1000000);
            性能測定_BigInteger((u, v) => u + v, "加算", 1000000);
            性能測定_BigInt((u, v) => u * v, "乗算", 1000000);
            性能測定_BigInteger((u, v) => u * v, "乗算", 1000000);
            性能測定_BigInt((u, v) => u / v, "除算", 1000000);
            性能測定_BigInteger((u, v) => u / v, "除算", 1000000);
        }

        private static void 性能測定_BigInteger(Func<BigInteger, BigInteger, BigInteger> op, string name, int loop_count)
        {
            using (var random = new Random(0))
            {
                var u = BigInteger.Parse(random.GenerateUBigInt(2048).ToString("D"));
                var v = BigInteger.Parse(random.GenerateUBigInt(1024).ToString("D"));
                var sw = new Stopwatch();
                sw.Start();
                for (var count = 0; count < loop_count; ++count)
                {
                    var w = op( u , v);
                }
                sw.Stop();
                Console.WriteLine("計算時間(BigInteger {0})={1:F6}[msec]", name, (double)sw.ElapsedMilliseconds / loop_count);
            }
        }

        private static void 性能測定_BigInt(Func<UBigInt, UBigInt, UBigInt> op, string name, int loop_count)
        {
            using (var random = new Random(0))
            {
                var u = random.GenerateUBigInt(2048);
                var v = random.GenerateUBigInt(1024);
                var sw = new Stopwatch();
                sw.Start();
                for (var count = 0; count < loop_count; ++count)
                {
                    var w = op(u, v);
                }
                sw.Stop();
                Console.WriteLine("計算時間(UBigInt {0})={1:F6}[msec]", name, (double)sw.ElapsedMilliseconds / loop_count);
            }
        }

        private static void Pie_BigInt測定()
        {
            var pie1 = new BigIntPie();
            var prsn = 1000U;

            Stopwatch sw = new Stopwatch();
            sw.Start();
            UBigInt u, v;
            pie1.CalculatePie(prsn, out u, out v);
            sw.Stop();

            Console.WriteLine("{0}.{1}", u, v);
            Console.WriteLine("計算時間(BigInt)={0}", sw.ElapsedMilliseconds / 1000.0);
        }

        private static void Pie_BigInteger測定()
        {
            var pie1 = new BigIntegerPie();
            var prsn = 1000;

            Stopwatch sw = new Stopwatch();
            sw.Start();
            BigInteger u, v;
            pie1.CalculatePie(prsn, out u, out v);
            sw.Stop();

            Console.WriteLine("{0}.{1}", u, v);
            Console.WriteLine("計算時間(BigInteger)={0}", sw.ElapsedMilliseconds / 1000.0);
        }
    }
}