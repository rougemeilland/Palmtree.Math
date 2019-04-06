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
using System.Runtime.InteropServices;


namespace Palmtree.Math.Core
{
    internal abstract class EngineBase
    {
        #region WIN32 API の宣言

        [DllImport("kernel32.dll", SetLastError = true)]
        private static extern bool SetDllDirectory(string lpPathName);

        #endregion

        #region プロテクテッドメソッド

        protected static void SetDllDir()
        {
            var this_assembly = typeof(EngineBase).Assembly;
            var this_assembly_path = this_assembly.Location;
            var base_directory_path = Path.GetDirectoryName(this_assembly_path);
            string sub_dir;
            if (IntPtr.Size == 8)
                sub_dir = "x64";
            else if (IntPtr.Size == 4)
                sub_dir = "x86";
            else
                throw new PlatformNotSupportedException();
            var dll_dir_path = Path.Combine(base_directory_path, sub_dir);
            if (!SetDllDirectory(dll_dir_path))
            {
                int error = Marshal.GetLastWin32Error();
                throw new InternalErrorException(string.Format("SetDllDirectory がエラーを通知しました。: errno={0}", error));
            }
        }

        protected static void HandleResultCode(PMC_STATUS_CODE result_code)
        {
            switch (result_code)
            {
                case PMC_STATUS_CODE.PMC_STATUS_OK:
                    return;
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_ERROR:
                    throw new ArgumentException();
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_NULL_ERROR:
                    throw new ArgumentNullException();
                case PMC_STATUS_CODE.PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR:
                    throw new ArgumentOutOfRangeException();
                case PMC_STATUS_CODE.PMC_STATUS_OVERFLOW:
                    throw new OverflowException();
                case PMC_STATUS_CODE.PMC_STATUS_DIVISION_BY_ZERO:
                    throw new DivideByZeroException();
                case PMC_STATUS_CODE.PMC_STATUS_ARITHMETIC_ERROR:
                    throw new ArithmeticException();
                case PMC_STATUS_CODE.PMC_STATUS_FORMAT_ERROR:
                    throw new FormatException();
                case PMC_STATUS_CODE.PMC_STATUS_INSUFFICIENT_BUFFER:
                    throw new InsufficientBufferException();
                case PMC_STATUS_CODE.PMC_STATUS_NOT_ENOUGH_MEMORY:
                    throw new InsufficientMemoryException();
                case PMC_STATUS_CODE.PMC_STATUS_NOT_SUPPORTED:
                    throw new NotSupportedException();
                case PMC_STATUS_CODE.PMC_STATUS_KEY_NOT_FOUND:
                    throw new KeyNotFoundException();
                case PMC_STATUS_CODE.PMC_STATUS_INVALID_OPERATION:
                    throw new InvalidOperationException();
                case PMC_STATUS_CODE.PMC_STATUS_INTERNAL_ERROR:
                    throw new InternalErrorException();
                case PMC_STATUS_CODE.PMC_STATUS_BAD_BUFFER:
                    throw new BadBufferException();
                case PMC_STATUS_CODE.PMC_STATUS_SEH:
                    throw new SEHException();
                default:
                    throw new InternalErrorException(string.Format("未知の例外が発生しました。: code={0}", result_code));
            }
        }

        #endregion
    }
}


/*
 * END OF FILE
 */