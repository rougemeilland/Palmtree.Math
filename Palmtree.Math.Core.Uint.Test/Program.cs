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
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Threading;
using System.Threading.Tasks;

namespace Palmtree.Math.Core.Uint.Test
{
    class Program
    {
        static void Main(string[] args)
        {
            var current_assembly = typeof(Program).Assembly;
            var interface_name = typeof(IComponentTestPlugin).FullName;
            var plugins = current_assembly.GetTypes()
                          .Where(t => t.IsClass /*&& t.IsPublic */&& !t.IsAbstract && t.GetInterface(interface_name) != null)
                          .Select(t => (IComponentTestPlugin)current_assembly.CreateInstance(t.FullName))
                          .ToArray();
            var 重複確認用コレクション = plugins
                .GroupBy(plugin => plugin.PluginName)
                .Select(g => new { key = g.Key, count = g.Count() })
                .Where(item => item.count != 1);
            foreach (var item in 重複確認用コレクション)
            {
                Console.WriteLine(string.Format("***プラグインが重複しています。: {0}", item.key));
                Console.ReadLine();
                return;
            }
            int 合計項目数 = 0;
            int NG項目数 = 0;
            Console.WriteLine(string.Format("***settings: {0}", string.Join(", ", UBigInt.ConfigurationSettings.Select(item => string.Format("{0}={1}", item.Key, item.Value)))));
            Console.WriteLine("***test start");
            bool parallel = false;
            var lock_obj = new object();
            if (parallel)
            {
                var options = new ParallelOptions();
                options.MaxDegreeOfParallelism = 8;
                Parallel.ForEach(plugins.SelectMany(plugin => plugin.TestItems), options, test_item =>
                {
                    TaskAction(test_item, ref 合計項目数, ref NG項目数, lock_obj);
                });
            }
            else
            {
                foreach (var test_item in plugins.SelectMany(plugin => plugin.TestItems))
                {
                    TaskAction(test_item, ref 合計項目数, ref NG項目数, lock_obj);
                };
            }
            Console.WriteLine(string.Format("***test end: 合計項目数:{0}, OK項目数:{1}, NG項目数:{2}, NG率:{3:p2}",
                                             合計項目数,
                                             合計項目数 - NG項目数,
                                             NG項目数,
                                             (double)NG項目数 / 合計項目数));
            //Console.ReadLine();
        }

        [HandleProcessCorruptedStateExceptions]
        private static void TaskAction(IComponentTestItem test_item, ref int 合計項目数, ref int NG項目数, object lock_obj)
        {
            string summary;
            try
            {
                var 結果 = test_item.DoTest(out summary);
                if (!結果)
                {
                    lock (lock_obj)
                    {
                        ++NG項目数;
                        Console.WriteLine(string.Format("NG: {0}-{1} {2}", test_item.PluginName, test_item.Index, summary));
                    }
                }
            }
            catch (AccessViolationException)
            {
                throw;
            }
            Interlocked.Increment(ref 合計項目数);
        }
    }
}


/*
 * END OF FILE
 */