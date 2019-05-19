using System;
using System.Diagnostics;
using System.Numerics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Palmtree.Math.Experiment.Pie
{
    class BigIntegerPie
    {
        BigInteger expansion(BigInteger p, BigInteger q, int n)
        {
            var x = BigInteger.Zero;
            var nn = BigInteger.Zero;
            var c = BigInteger.Zero;
            var s = BigInteger.Zero;
            var k = BigInteger.Zero;
            x = (p * q) / n;
            nn = n * n;
            c = 1;
            s = x;
            k = 1;
            while (x > 0)
            {
                x = x / nn;
                k = k + 2;
                c = -c;
                s = s + c * (x / k);
            }
            return s;
        }

        public void CalculatePie(int prsn, out BigInteger u, out BigInteger v)
        {
            var p = BigInteger.Pow(10, prsn);
            var q = BigInteger.Pow(10, 10);

            var y = ( (12 * expansion(p, q, 18) + (expansion(p, q, 57) << 3) - 5 * expansion(p, q, 239)) << 2) / q;
            u = BigInteger.DivRem(y, p, out v);
        }
    }
}
