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
using System.Reflection;
using System.Text;

namespace Palmtree.Math.CodeGen.VersionInfo
{
    class Program
    {
        static void Main(string[] args)
        {
            var root_dir = new FileInfo(Assembly.GetExecutingAssembly().Location).Directory.Parent.Parent.Parent;

            var query = root_dir.EnumerateDirectories("*", SearchOption.TopDirectoryOnly)
                .SelectMany(dir => dir.EnumerateFiles("*.rc", SearchOption.TopDirectoryOnly), (dir, rcfile) => new { dir, rcfile })
                .Select(item => new { item.dir, item.rcfile, newrcfile = new FileInfo(Path.Combine(item.dir.FullName, "version.rc")), dir_name = item.dir.Name, file_name = Path.GetFileNameWithoutExtension(item.rcfile.Name) })
                .Where(item => item.dir_name == item.file_name);
            foreach (var item in query)
            {
                Console.WriteLine(string.Format("{0}, {1}", item.rcfile.FullName, item.newrcfile.FullName));
                CopyVersionResource(item.rcfile, item.newrcfile);
            }
        }

        private static void CopyVersionResource(FileInfo source_file, FileInfo target_file)
        {
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
                    text0 = text1;
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
