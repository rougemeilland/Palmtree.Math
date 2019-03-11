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

namespace Palmtree.Math.Core.Uint.CodeGen.TestData
{
    abstract class TestDataRendererPluginBase
        : ITestDataRendererPlugin
    {
        string _data_file_path;

        protected TestDataRendererPluginBase(string data_file_name)
        {
            var assembly = typeof(ITestDataRendererPlugin).Assembly;
            var assembly_directory = Path.GetDirectoryName(assembly.Location);
            var solution_directory = Path.GetDirectoryName(Path.GetDirectoryName(Path.GetDirectoryName(assembly_directory)));
            _data_file_path = Path.Combine(solution_directory, "Palmtree.Math.Core.Uint.Test", "Data", data_file_name);
            DataFileName = data_file_name;
        }

        protected virtual IEnumerable<BigInteger> AdditionalUBigIntDataSource
        {
            get
            {
                return (new BigInteger[0]);
            }
        }

        protected IEnumerable<BigInteger> UBigIntDataSource
        {
            get
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
                    (BigInteger.One << 64) - 1,
                }
                .Concat(AdditionalUBigIntDataSource)
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
                return (numbers
                        .Distinct(new BigIntegerComparer())
                        .OrderBy(x => x, new BigIntegerComparer())
                        .ToArray());
            }
        }

        protected IEnumerable<Int32> BitCountDataSource
        {
            get
            {
                return (new[] { -1, 0, 1, 31, 32, 33, 63, 64, 65 });
            }
        }

        protected IEnumerable<UInt32> ExponentDataSource
        {
            get
            {
                return (new[] { 0U, 1U, 31U, 32U, 33U, 63U, 64U, 65U });
            }
        }

        protected abstract IEnumerable<XmlElement> GetDataItemRows(XmlDocument document);

        public string DataFileName { get; }

        public void Render()
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