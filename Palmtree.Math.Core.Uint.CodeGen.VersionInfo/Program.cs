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
using System.Reflection;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Palmtree.Math.Core.Uint.CodeGen.VersionInfo
{
    class Program
    {
        static void Main(string[] args)
        {

            var source_file = new FileInfo(Assembly.GetExecutingAssembly().Location).Directory.Parent.Parent.Parent.GetChildDirectory("Palmtree.Math.Core.Uint").GetChildFile("Palmtree.Math.Core.Uint.rc");
            if (!source_file.Exists)
                return;
            var target_file = new FileInfo(Assembly.GetExecutingAssembly().Location).Directory.Parent.Parent.Parent.GetChildDirectory("Palmtree.Math.Core.Uint").GetChildFile("version.rc");
            if (!target_file.Exists)
                return;
            using (var reader = new StreamReader(source_file.FullName, Encoding.Unicode))
            using (var writer = new StreamWriter(target_file.FullName, false, Encoding.UTF8))
            {
                writer.WriteLine("#include <winver.h>");
                writer.WriteLine();
                string text0 = null;
                string text1 = null;
                string text2 = null;
                while (true)
                {
                    text2 = reader.ReadLine();
                    if (text2 == null)
                        throw new ApplicationException();

                    if (text0 == "/////////////////////////////////////////////////////////////////////////////" &&
                        text1 == "//" &&
                        text2 == "// Version")
                        break;
                    text0  = text1;
                    text1 = text2;
                    text2 = null;
                }
                writer.WriteLine(text0);
                writer.WriteLine(text1);
                writer.WriteLine(text2);
                while (true)
                {
                    var text = reader.ReadLine();
                    if (text == null)
                        throw new ApplicationException();
                    writer.WriteLine(text);
                    if (text == "END")
                        break;
                }
            }
        }
    }
}
