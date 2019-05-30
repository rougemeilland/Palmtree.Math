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
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Xml;

namespace Palmtree.Math.CodeGen.TestData
{
    abstract class TestDataRendererPluginBase
        : ITestDataRendererPlugin
    {
        private string _category;
        private string _data_file_path;

        protected TestDataRendererPluginBase(string category, string data_file_name)
        {
            var assembly = typeof(ITestDataRendererPlugin).Assembly;
            var assembly_directory = Path.GetDirectoryName(assembly.Location);
            var solution_directory = Path.GetDirectoryName(Path.GetDirectoryName(Path.GetDirectoryName(assembly_directory)));
            _category = category;
            _data_file_path = Path.Combine(solution_directory, "Palmtree.Math.Test", "Data", category, data_file_name);
            DataFileKey = string.Format("{0}.{1}", category, data_file_name);
        }

        protected virtual IEnumerable<BigInteger> AdditionalUBigIntDataSource
        {
            get
            {
                return (new BigInteger[0]);
            }
        }

        protected IEnumerable<Int32> Int32DataSource
        {
            get
            {
                return (BigIntDataSource
                        .Where(x => x >= Int32.MinValue && x <= Int32.MaxValue)
                        .Select(x => (Int32)x));
            }
        }

        protected IEnumerable<Int64> Int64DataSource
        {
            get
            {
                return (BigIntDataSource
                        .Where(x => x >= Int64.MinValue && x <= Int64.MaxValue)
                        .Select(x => (Int64)x));
            }
        }

        protected IEnumerable<UInt32> UInt32DataSource
        {
            get
            {
                return (BigIntDataSource
                        .Where(x => x >= UInt32.MinValue && x <= UInt32.MaxValue)
                        .Select(x => (UInt32)x));
            }
        }

        protected IEnumerable<UInt64> UInt64DataSource
        {
            get
            {
                return (BigIntDataSource
                        .Where(x => x >= UInt64.MinValue && x <= UInt64.MaxValue)
                        .Select(x => (UInt64)x));
            }
        }

        protected IEnumerable<BigInteger> UBigIntDataSource
        {
            get
            {
                return (BigIntDataSource.Where(x => x >= 0));
            }
        }

        protected IEnumerable<BigInteger> BigIntDataSource
        {
            get
            {
                IEnumerable<BigInteger> source;
                switch (_category)
                {
                    case "uint":
                        {
                            var numbers = new[]
                            {
                                // 0と1
                                BigInteger.Zero,
                                BigInteger.One,

                                // ワード境界値
                                BigInteger.One << 32,
                                (BigInteger.One << 32) - 1,
                                BigInteger.One << 64,
                                (BigInteger.One << 64) - 1
                            }
                            .ToList();

                            // 長いデータ(最長で512bit程度)
                            // 最大で512bitのデータを作る 10進数10桁で2進数33桁≒32桁＝4バイト。
                            var data_str_1 = "9999999999";
                            var data_str_2 = "1234567890";
                            var limit = new BigInteger(1) << 512;
                            for (; ; )
                            {
                                BigInteger data_1;
                                BigInteger data_2;
                                if (!BigInteger.TryParse(data_str_1, out data_1))
                                    throw new ApplicationException();
                                if (!BigInteger.TryParse(data_str_2, out data_2))
                                    throw new ApplicationException();
                                numbers.Add(data_1);
                                numbers.Add(data_2);
                                if (data_1 >= limit || data_2 >= limit)
                                    break;
                                data_str_1 += data_str_1;
                                data_str_2 += data_str_2;
                            }
                            source = numbers;
                        }
                        break;
                    case "sint":
                    case "rtnl":
                        {
                            source = new[]
                            {
                                BigInteger.Zero,
                                BigInteger.One,

                                // ワード境界値
                                BigInteger.One << 32,
                                (BigInteger.One << 32) - 1,
                                (BigInteger.One << 32) + 1,
                                BigInteger.One << 64,
                                (BigInteger.One << 64) - 1,
                                (BigInteger.One << 64) + 1
                            };
                        }
                        break;
                    default:
                        throw new ApplicationException();
                }
                return (source
                        .Concat(AdditionalUBigIntDataSource)
                        .SelectMany(item => new[] { item, -item })
                        .Distinct(new BigIntegerComparer())
                        .OrderBy(x => x, new BigIntegerComparer()));
            }
        }

        protected virtual IEnumerable<MiniRational> AdditionalRationalDataSource
        {
            get
            {
                return (new MiniRational[0]);
            }
        }

        protected IEnumerable<MiniRational> RationalDataSource
        {
            get
            {
                var source = new BigInteger[]
                {
                    BigInteger.Zero,
                    BigInteger.One,
                    (BigInteger.One << 32) - 1,
                    BigInteger.One << 32,
                    (BigInteger.One << 64) - 1,
                    BigInteger.One << 64,
                    BigInteger.Parse("999999999"),
                    BigInteger.Parse("1000000000"),
                    BigInteger.Parse("9999999999999999999"),
                    BigInteger.Parse("10000000000000000000"),
                };
                return (source.SelectMany(n => new[] { n, -n })
                        .SelectMany(n => source.Where(d => d != 0), (n, d) => new MiniRational(n, d))
                        .Concat(AdditionalRationalDataSource)
                        .Distinct(new MiniRationalComparer())
                        .OrderBy(x => x, new MiniRationalComparer()));
            }
        }

        protected IEnumerable<Int32> BitCountDataSource
        {
            get
            {
                return (new[] { -1, 0, 1, 31, 32, 33, 63, 64, 65 });
            }
        }

        protected IEnumerable<UInt32> UBitCountDataSource
        {
            get
            {
                return (new[] { 0U, 1U, 31U, 32U, 33U, 63U, 64U, 65U });
            }
        }

        protected IEnumerable<UInt32> UExponentDataSource
        {
            get
            {
                return (new[] { 0U, 1U, 31U, 32U, 33U, 63U, 64U, 65U });
            }
        }

        protected IEnumerable<Int32> ExponentDataSource
        {
            get
            {
                return (new[] { -5, -2, -1, 0, 1, 2, 5 });
            }
        }

        protected abstract IEnumerable<XmlElement> GetDataItemRows(XmlDocument document);

        public string DataFileKey { get; }

        public void Render()
        {
            try
            {
                var document = new XmlDocument();

                var declaration = document.CreateXmlDeclaration("1.0", "UTF-8", null);
                var root = document.CreateElement("dataitems");
                document.AppendChild(declaration);
                document.AppendChild(root);
                foreach (var row in GetDataItemRows(document))
                    root.AppendChild(row);
                document.Save(_data_file_path);
            }
            catch (IOException ex)
            {
                Console.WriteLine(string.Format("ファイルの読み書きで例外が発生しました。: path='{0}'", _data_file_path));
                throw ex;
            }
        }

        protected static void AppendElement(XmlElement parent_element, XmlElement child_element)
        {
            if (child_element != null)
                parent_element.AppendChild(child_element);
        }
    }
}


/*
 * END OF FILE
 */