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


namespace Palmtree.Math
{
    public enum RoundingMode
    {
        HalfEven = 0,       // 数値が 2 つの数値の中間に位置する場合、最も近い偶数方向に丸められる。
        ToEven = 0,         // 数値が 2 つの数値の中間に位置する場合、最も近い偶数方向に丸められる。
        HalfUp = 1,         // 数値が 2 つの数値の中間に位置する場合、0 から遠い方の近似値に丸められる。
        AwayFromZero = 1,   // 数値が 2 つの数値の中間に位置する場合、0 から遠い方の近似値に丸められる。
        Ceiling = 1001,     // 正の無限大に近づくように丸められる。
        Down = 1002,        // 0 に近づくように丸められる。
        Truncate = 1002,    // 0 に近づくように丸められる。
        Floor = 1003,       // 負の無限大に近づくように丸められる。
        HalfDown = 1004,    // 数値が 2 つの数値の中間に位置する場合、0 から近い方の近似値に丸められる。
        Up = 1005,          // 0 から離れるように丸められる。
    }
}


/*
 * END OF FILE
 */
