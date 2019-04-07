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


#pragma once

#ifndef PMC_PARSER_H
#define PMC_PARSER_H


namespace Palmtree::Math::Core::Internal
{

    __inline static int ParseDecimalDigit(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (c - L'0');
        return (-1);
    }

    __inline static int ParseHexDigit(wchar_t c)
    {
        if (c >= L'0' && c <= L'9')
            return (c - L'0');

        if (c >= L'a' && c <= L'f')
            return (c - L'a' + 10);

        if (c >= L'A' && c <= L'F')
            return (c - L'A' + 10);
        return (-1);
    }

}

#endif


/*
 * END OF FILE
 */