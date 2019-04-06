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


using System.Collections;
using System.Collections.Generic;


namespace Palmtree.Math
{
    internal class ConfigurationDictionary
        : IReadOnlyDictionary<string, string>
    {
        private IDictionary<string, string> _imp;

        public ConfigurationDictionary()
        {
            _imp = new Dictionary<string, string>();
        }

        internal void Add(string key, string value)
        {
            _imp.Add(key, value);
        }

        public string this[string key] => _imp[key];

        public IEnumerable<string> Keys => _imp.Keys;

        public IEnumerable<string> Values => _imp.Values;

        public int Count => _imp.Count;

        public bool ContainsKey(string key)
        {
            return (_imp.ContainsKey(key));
        }

        public IEnumerator<KeyValuePair<string, string>> GetEnumerator()
        {
            return (_imp.GetEnumerator());
        }

        public bool TryGetValue(string key, out string value)
        {
            return (_imp.TryGetValue(key, out value));
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return (GetEnumerator());
        }
    }
}


/*
 * END OF FILE
 */