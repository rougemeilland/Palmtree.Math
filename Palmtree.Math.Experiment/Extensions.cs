using System.Linq;
using System;
using System.Collections.Generic;
using System.Numerics;

namespace Palmtree.Math.Experiment
{
    static class Extensions
    {
        public static string Dump(this BigInteger x)
        {
            var array = x.ToByteArray();
            while (array.Length > 1 && array.Last() == 0)
                array = array.Take(array.Length - 1).ToArray();
            return (string.Join(", ", array.Select(n => string.Format("0x{0:x02}", n))));
        }

        public static UInt32[] To__UNIT_TYPEArray(this BigInteger x)
        {
            if (x < 0)
                throw new ApplicationException();
            var list = new List<UInt32>();
            while (x != 0)
            {
                var e = x & 0xffffffff;
                list.Add((UInt32)e);
                x >>= 32;
            }
            return (list.ToArray());
        }

        public static BigInteger ToBigInteger(this byte[] array)
        {
            return (array
                    .Zip(Enumerable.Range(0, array.Length), (x, index) => new BigInteger(x) << (8 * index))
                    .Aggregate((x, y) => x + y));
        }

        public static BigInteger ToBigInteger(this UInt32[] array)
        {
            return (array
                    .Zip(Enumerable.Range(0, array.Length), (x, index) => new BigInteger(x) << (32 * index))
                    .Aggregate((x, y) => x + y));
        }

        public static int LZCNT(this UInt32 x)
        {
            var lzcnt = 32;
            while (x != 0)
            {
                --lzcnt;
                x >>= 1;
            }
            return (lzcnt);
        }

        public static UInt32[] Padding(this UInt32[] array, int n)
        {
            return (array.Concat(Enumerable.Repeat(0U, n)).Take(n).ToArray());
        }
    }
}