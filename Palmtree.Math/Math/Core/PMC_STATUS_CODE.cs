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


namespace Palmtree.Math.Core
{
    internal enum PMC_STATUS_CODE
    {
        PMC_STATUS_OK = 0,
        PMC_STATUS_ARGUMENT_ERROR = -1,
        PMC_STATUS_ARGUMENT_NULL_ERROR = -2,
        PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR = -3,
        PMC_STATUS_OVERFLOW = -4,
        PMC_STATUS_DIVISION_BY_ZERO = -5,
        PMC_STATUS_ARITHMETIC_ERROR = -6,
        PMC_STATUS_FORMAT_ERROR = -7,
        PMC_STATUS_INSUFFICIENT_BUFFER = -8,
        PMC_STATUS_NOT_ENOUGH_MEMORY = -9,
        PMC_STATUS_NOT_SUPPORTED = -10,
        PMC_STATUS_KEY_NOT_FOUND = -11,
        PMC_STATUS_INVALID_OPERATION = -12,
        PMC_STATUS_INTERNAL_ERROR = -256,
        PMC_STATUS_BAD_BUFFER = -257,
        PMC_STATUS_SEH = -258,
    }
}


/*
 * END OF FILE
 */
