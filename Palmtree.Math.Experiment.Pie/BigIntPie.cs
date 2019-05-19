namespace Palmtree.Math.Experiment.Pie
{
    class BigIntPie
    {
        BigInt expansion(UBigInt p, UBigInt q, uint n)
        {
            var x = (p * q) / n;
            var s = (BigInt)x;
            var nn = (UBigInt)(n * n);
            var c = BigInt.One;
            var k = BigInt.One;
            while (x > 0)
            {
                x = x / nn;
                k = k + 2;
                c = -c;
                s = s + c * (x / k);
            }
            return s;
        }

        public void CalculatePie(uint prsn, out UBigInt u, out UBigInt v)
        {
            var p = UBigInt.Pow(10, prsn);
            var q = UBigInt.Pow(10, 10);

            var y = ((12 * expansion(p, q, 18) + ( expansion(p, q, 57)<<3) - 5 * expansion(p, q, 239)) << 2).ToUBigInt() / q;
            u = y.DivRem(p, out v);
        }
    }
}
