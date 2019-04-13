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
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;


// 演算子のオーバーロードに関するガイドライン：
// https://docs.microsoft.com/ja-jp/dotnet/standard/design-guidelines/operator-overloads

namespace Palmtree.Math
{
    public partial struct BigInt
        : IComparable, IComparable<BigInt>, IEquatable<BigInt>, IFormattable
    {
        #region プライベートフィールド

        private static object _lock_obj;
        //private static Regex _tostring_standard_format_pattern;
        private Core.BigIntHandle _handle;

        #endregion

        #region コンストラクタ

        static BigInt()
        {
            _lock_obj = new object();
            EngineObject = new Core.BigIntEngine();
            var settings = new ConfigurationDictionary();
            foreach (var key in new[] { "COMPILER", "CONFIG", "PLATFORM", "TABLESIZE" })
                settings.Add(key, EngineObject.GetConfigurationSettings(key));
            ConfigurationSettings = settings;
            PerformanceCounters = new PerformanceCounterCollection();
            MinusOne = new BigInt(EngineObject.MinusOne);
            One = new BigInt(EngineObject.One);
            Zero = new BigInt(EngineObject.Zero);
            //_tostring_standard_format_pattern = new Regex("^|[cdefgnprx]|[cdefgnprx][0-9]|[cdefgnprx][0-9][0-9]$", RegexOptions.Compiled | RegexOptions.IgnoreCase);
        }

        internal BigInt(Core.BigIntHandle handle)
        {
            _handle = handle;
        }

        #endregion

        #region パブリックプロパティ

        public static IReadOnlyDictionary<string, string> ConfigurationSettings { get; }

        public static IPerformanceCounterCollection PerformanceCounters { get; }

        public static BigInt MinusOne { get; }

        public static BigInt One { get; }

        public static BigInt Zero { get; }

        public bool IsEven => EngineObject.IsEven(Handle);

        public bool IsMinusOne => EngineObject.IsMinusOne(Handle);

        public bool IsOne => EngineObject.IsOne(Handle);

        public bool IsPowerOfTwo => EngineObject.IsPowerOfTwo(Handle);

        public bool IsZero => EngineObject.IsZero(Handle);

        #endregion

        #region インターナルプロパティ

        internal static Core.BigIntEngine EngineObject { get; private set; }

        internal Core.BigIntHandle Handle
        {
            get
            {
                lock (_lock_obj)
                {
                    if (_handle == null)
                        _handle = new Core.BigIntHandle();
                    return (_handle);
                }
            }
        }

        #endregion

    }
}


/*
 * END OF FILE
 */