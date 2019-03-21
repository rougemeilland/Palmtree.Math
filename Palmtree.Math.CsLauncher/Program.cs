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
            var x_int_1 = int.Parse(".00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign);
            var x_int_2 = int.Parse("-.00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign);
            var x_uint_1 = uint.Parse(".00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign);
            //var x_uint_2 = uint.Parse("-.00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign); // 例外
            var x_biginteger_1 = BigInteger.Parse(".00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign);
            var x_biginteger_2 = BigInteger.Parse("-.00", NumberStyles.AllowDecimalPoint | NumberStyles.AllowLeadingSign);

            BigInt value;
            BigInt.TryParse("(.00)", NumberStyles.AllowParentheses | NumberStyles.AllowDecimalPoint, null, out value);
            Console.ReadLine();
        }
    }

}