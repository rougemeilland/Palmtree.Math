/*
 * The MIT License
 *
 * Copyright 2019 Palmtree Software.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


using System;
using System.Globalization;
using System.Numerics;
using System.Threading;
using System.Threading.Tasks;
using System.Linq;

namespace Palmtree.Math.CodeGen.TestData
{
    class Program
    {
        static void Main(string[] args)
        {

#if true
            // 10,03,04,00,ca,9a,3b,01,08,ff,ff,e7,89,04,23,c7,8a

            var m = new MiniRational(0x3b9aca00, 0x8ac7230489e7ffff);
            var d = m.ToDecimal();
#endif

            var lock_obj = new object();
            var current_assembly = typeof(Program).Assembly;
            var interface_name = typeof(ITestDataRendererPlugin).FullName;
            var plugins = current_assembly.GetTypes()
                          .Where(t => t.IsClass /*&& t.IsPublic */&& !t.IsAbstract && t.GetInterface(interface_name) != null)
                          .Select(t => (ITestDataRendererPlugin)current_assembly.CreateInstance(t.FullName));


            var 重複確認用コレクション = plugins
                .GroupBy(item => item.DataFileKey)
                .Select(g => new { key = g.Key, count = g.Count() })
                .Where(item => item.count != 1);
            foreach (var item in 重複確認用コレクション)
            {
                Console.WriteLine(string.Format("***プラグインが重複しています。: {0}", item.key));
                Console.ReadLine();
                return;
            }
            var is_parallel = false;
            if (is_parallel)
            {
                var options = new ParallelOptions();
                options.MaxDegreeOfParallelism = 8;
                Parallel.ForEach(plugins/*.Where(plugin => plugin.DataFileName.StartsWith("test_data_tostring"))*/, options, plugin =>
                {
                    lock (lock_obj)
                    {
                        Console.WriteLine(string.Format("{0}...", plugin.DataFileKey));
                    }
                    plugin.Render();
                });
            }
            else
            {
                foreach (var plugin in plugins/*.Where(plugin => plugin.DataFileKey.Contains("to") || plugin.DataFileKey.Contains("from"))*/)
                {
                    lock (lock_obj)
                    {
                        Console.WriteLine(string.Format("{0}...", plugin.DataFileKey));
                    }
                    plugin.Render();
                }
            }
        }
    }
}


/*
 * END OF FILE
 */