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
using System.IO;
using System.Linq;
using System.Runtime.ExceptionServices;
using System.Threading;
using System.Threading.Tasks;


namespace Palmtree.Math.Test
{
    class Program
    {
        private static bool _verbose = false;
        private static bool _parallel = true;

        [HandleProcessCorruptedStateExceptions]
        static void Main(string[] args)
        {
            定数のテスト();
            TestLoop();
            // Console.ReadLine();
        }

        private static void 定数のテスト()
        {
            BigInt default_value_ubigint;
            バイト配列が等しいことの確認(default_value_ubigint.ToByteArray(), new byte[] { 0x00, 0x00 });
            バイト配列が等しいことの確認(UBigInt.Zero.ToByteArray(), new byte[] { 0x00, 0x00 });
            バイト配列が等しいことの確認(UBigInt.One.ToByteArray(), new byte[] { 0x01, 0x01, 0x01 });

            UBigInt default_value_bigint;
            バイト配列が等しいことの確認(default_value_bigint.ToByteArray(), new byte[] { 0x00, 0x00 });
            バイト配列が等しいことの確認(BigInt.Zero.ToByteArray(), new byte[] { 0x00, 0x00 });
            バイト配列が等しいことの確認(BigInt.One.ToByteArray(), new byte[] { 0x01, 0x01, 0x01 });
            バイト配列が等しいことの確認(BigInt.MinusOne.ToByteArray(), new byte[] { 0x03, 0x01, 0x01 });

            Rational default_value_rational;
            バイト配列が等しいことの確認(default_value_rational.ToByteArray(), new byte[] { 0x10, 0x00, 0x00, 0x01, 0x01, 0x01 });
            バイト配列が等しいことの確認(Rational.Zero.ToByteArray(), new byte[] { 0x10, 0x00, 0x00, 0x01, 0x01, 0x01 });
            バイト配列が等しいことの確認(Rational.One.ToByteArray(), new byte[] { 0x10, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 });
            バイト配列が等しいことの確認(Rational.MinusOne.ToByteArray(), new byte[] { 0x10, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01 });
        }

        private static void バイト配列が等しいことの確認(byte[] u, byte[] v)
        {
            if (u.Length != v.Length)
                throw new ApplicationException();
            for (var index = 0; index < u.Length; ++index)
            {
                if (u[index] != v[index])
                    throw new ApplicationException();
            }
        }

        private static void TestLoop()
        {
            var current_assembly = typeof(Program).Assembly;
            var interface_name = typeof(IComponentTestPlugin).FullName;
            var plugins = current_assembly.GetTypes()
                          .Where(t => t.IsClass /*&& t.IsPublic */&& !t.IsAbstract && t.GetInterface(interface_name) != null)
                          .Select(t => (IComponentTestPlugin)current_assembly.CreateInstance(t.FullName))
                          .OrderBy(p => p.DataFileSize)
                          .ToArray();

            // プラグインの重複の確認
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

            // テスト漏れのデータファイルがないか確認
            var base_dir = Path.Combine(Path.GetDirectoryName(typeof(Program).Assembly.Location));
            var data_files = Directory.EnumerateFiles(base_dir, "*.xml", SearchOption.AllDirectories)
                        .Select(full_path => new { dir = Path.GetDirectoryName(full_path), data_file_name = Path.GetFileName(full_path) })
                        .Select(item => new { category = Path.GetFileName(item.dir), item.data_file_name })
                        .Select(item => (item.category + "." + item.data_file_name).ToLower())
                        .ToDictionary(id => id, id => id);
            foreach (var plugin in plugins)
                data_files.Remove(plugin.DataFileID);

            if (data_files.Any())
            {
                Console.WriteLine(string.Format("***参照されていないデータファイルがあります: {0}", string.Join(", ", data_files.Keys)));
                Console.ReadLine();
                return;
            }

            int 合計項目数 = 0;
            int NG項目数 = 0;
            Console.WriteLine(string.Format("***UBigInt settings: {0}", string.Join(", ", UBigInt.ConfigurationSettings.Select(item => string.Format("{0}={1}", item.Key, item.Value)))));
            Console.WriteLine(string.Format("***BigInt settings: {0}", string.Join(", ", BigInt.ConfigurationSettings.Select(item => string.Format("{0}={1}", item.Key, item.Value)))));
            Console.WriteLine(string.Format("***Rational settings: {0}", string.Join(", ", Rational.ConfigurationSettings.Select(item => string.Format("{0}={1}", item.Key, item.Value)))));
            Console.WriteLine("***test start");
            var lock_obj = new object();
            if (_parallel)
            {
                var options = new ParallelOptions();
                options.MaxDegreeOfParallelism = 8;
                Parallel.ForEach(plugins.Where(plugin => PluginFilter(plugin)).SelectMany(plugin => plugin.TestItems).Where(test_item => TestItemFilter(test_item)), options, test_item =>
                {
                    TaskAction(test_item, ref 合計項目数, ref NG項目数, lock_obj);
                });
            }
            else
            {
                foreach (var test_item in plugins.Where(plugin => PluginFilter(plugin)).SelectMany(plugin => plugin.TestItems).Where(test_item => TestItemFilter(test_item)))
                {
                    TaskAction(test_item, ref 合計項目数, ref NG項目数, lock_obj);
                };
            }
            Console.WriteLine(string.Format("***test end: 合計項目数:{0}, OK項目数:{1}, NG項目数:{2}, NG率:{3:p2}",
                                             合計項目数,
                                             合計項目数 - NG項目数,
                                             NG項目数,
                                             (double)NG項目数 / 合計項目数));
        }

        private static bool PluginFilter(IComponentTestPlugin plugin)
        {
            //return (plugin.PluginName.StartsWith("rtnl."));
            return (true);
        }

        private static bool TestItemFilter(IComponentTestItem test_item)
        {
            //return (test_item.Index == 2);
            return (true);
        }

        [HandleProcessCorruptedStateExceptions]
        private static void TaskAction(IComponentTestItem test_item, ref int 合計項目数, ref int NG項目数, object lock_obj)
        {
            string summary;
            try
            {
                if (_verbose)
                {
                    lock (lock_obj)
                    {
                        Console.WriteLine(string.Format("***{0}-{1},{2}***", test_item.PluginName, test_item.Index, string.Join(",", new[]
                        {
                        UBigInt.PerformanceCounters["bigint/allocatenumber"],
                        UBigInt.PerformanceCounters["bigint/allocatenumberobject"],
                        UBigInt.PerformanceCounters["bigint/hooknumberux"],
                        UBigInt.PerformanceCounters["bigint/hooknumberx"],
                        UBigInt.PerformanceCounters["rational/allocatenumber"],
                        UBigInt.PerformanceCounters["rational/allocatenumberobject"],
                        UBigInt.PerformanceCounters["rational/hooknumberr"],
                        UBigInt.PerformanceCounters["rational/hooknumberux"],
                        UBigInt.PerformanceCounters["rational/hooknumberx"],
                        UBigInt.PerformanceCounters["ubigint/allocateblock"],
                        UBigInt.PerformanceCounters["ubigint/allocatenumber"],
                        UBigInt.PerformanceCounters["ubigint/allocatenumberobject"],
                        UBigInt.PerformanceCounters["ubigint/hooknumberux"],
                    })));
                    }
                }
                var 結果 = test_item.DoTest(out summary);
                if (!結果)
                {
                    lock (lock_obj)
                    {
                        ++NG項目数;
                        Console.WriteLine(string.Format("NG: {0}-{1} {2}", test_item.PluginName, test_item.Index, summary));
                        if (_verbose)
                            Console.ReadLine();
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