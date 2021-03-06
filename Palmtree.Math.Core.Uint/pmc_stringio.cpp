﻿/*
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

#include <windows.h>
#include "pmc_stringio.h"
#include "pmc_exception.h"

namespace Palmtree::Math::Core::Internal
{
    StringReader::StringReader(const wchar_t * p, const wchar_t* limit)
    {
        if (p == nullptr)
            throw ArgumentNullException(L"引数に null が与えられました。", L"p");
        if (limit == nullptr)
            throw ArgumentNullException(L"引数に null が与えられました。", L"limit");
        _p = p;
        _limit = limit;
    }

    StringReader::StringReader(const StringReader & p)
    {
        _p = p._p;
        _limit = p._limit;
    }

    StringReader::StringReader(const wchar_t * p)
        : StringReader(p, p + lstrlenW(p))
    {
    }

    StringReader::StringReader(const wchar_t * p, size_t length)
        : StringReader(p, p + length)
    {
    }

    wchar_t StringReader::ReadChar()
    {
        wchar_t c = PeekChar();
        Progress();
        return (c);
    }

    wchar_t StringReader::ReadChar(wchar_t default_char)
    {
        wchar_t c = PeekChar();
        if (c == L'\0')
            return (default_char);
        Progress();
        return (c);
    }

    wchar_t StringReader::PeekChar()
    {
        if (_p >= _limit)
            return (L'\0');
        return (*_p);
    }

    void StringReader::Progress()
    {
        if (_p >= _limit  || *_p == L'\0')
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;StringReader::Progress;1");
        ++_p;
    }

    int StringReader::StartsWith(const wchar_t * str)
    {
        return (StartsWith(_p, _limit, str));
    }

    void StringReader::SkipSpace()
    {
        for (;;)
        {
            switch (PeekChar())
            {
            case L' ':
            case L'\t':
            case L'\n':
            case L'\r':
            case L'\f':
            case L'\v':
                break;
            default:
                return;
            }
            Progress();
        }
    }

    void StringReader::SkipString(const wchar_t * str)
    {
        if (!StartsWith(_p, _limit, str))
        {
            // str で始まっていないにもかかわらず、strをスキップしようとした。
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;StringReader::SkipString;1");
        }
        _p += lstrlenW(str);
    }

    int StringReader::StartsWith(const wchar_t * a, const wchar_t* a_limit, const wchar_t * b)
    {
        while (*b != L'\0')
        {
            if (a >= a_limit || *a != *b)
                return (0);
            ++a;
            ++b;
        }
        return (1);
    }

    ReverseStringReader::ReverseStringReader(const wchar_t * p)
        : StringReader(p + lstrlenW(p) - 1, p)
    {
    }

    ReverseStringReader::ReverseStringReader(const wchar_t * p, size_t length)
        : StringReader(p + length - 1, p)
    {
    }

    wchar_t ReverseStringReader::PeekChar()
    {
        if (_p < _limit)
            return (L'\0');
        return (*_p);
    }

    void ReverseStringReader::Progress()
    {
        if (_p < _limit)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;ReverseStringReader::Progress;1");
        --_p;
    }

    int ReverseStringReader::StartsWith(const wchar_t * str)
    {
        return (StartsWith(_p, _limit, str));
    }

    void ReverseStringReader::SkipString(const wchar_t * str)
    {
        if (!StartsWith(_p, _limit, str))
        {
            // str で始まっていないにもかかわらず、strをスキップしようとした。
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;ReverseStringReader::SkipString;1");
        }
        _p -= lstrlenW(str);
    }

    int ReverseStringReader::StartsWith(const wchar_t * a, const wchar_t * a_limit, const wchar_t * b)
    {
        while (*b != L'\0')
        {
            if (a < a_limit || *a != *b)
                return (0);
            --a;
            ++b;
        }
        return (1);
    }

    StringWriter::StringWriter(wchar_t * p, wchar_t * sob, wchar_t * eob)
    {
        if (p != nullptr)
        {
            if (sob == nullptr)
                throw ArgumentNullException(L"引数に null が与えられました。", L"sob");
            if (eob == nullptr)
                throw ArgumentNullException(L"引数に null が与えられました。", L"eob");
        }
        _p = p;
        _sob = sob;
        _eob = eob;
        _written = 0;
    }

    StringWriter::StringWriter(wchar_t * buffer, size_t size)
        : StringWriter(buffer, buffer, buffer != nullptr ? buffer + size : nullptr)
    {
        if (_p != nullptr)
        {
            if (_p >= _eob)
                throw InsufficientBufferException(L"書き込み先バッファのサイズが不足しています。");
            *_p = L'\0';
        }
    }

    StringWriter::StringWriter(const StringWriter & p)
    {
        _p = p._p;
        _sob = p._sob;
        _eob = p._eob;
        _written = p._written;
    }

    void StringWriter::Write(wchar_t c)
    {
        if (_p != nullptr)
        {
            if (_p + 1 >= _eob)
                throw InsufficientBufferException(L"書き込み先バッファのサイズが不足しています。");
            *_p++ = c;
            *_p = L'\0';
        }
        ++_written;
    }

    void StringWriter::Write(wchar_t c, size_t count)
    {
        while (count > 0)
        {
            Write(c);
            --count;
        }
    }

    void StringWriter::Write(const wchar_t * str)
    {
        while (*str != L'\0')
        {
            Write(*str);
            ++str;
        }
    }

    void StringWriter::Write(const wchar_t * ptr, size_t count)
    {
        while (count > 0)
        {
            Write(*ptr);
            ++ptr;
            --count;
        }
    }

    void StringWriter::Write(StringReader & reader)
    {
        while (reader.PeekChar() != L'\0')
            Write(reader.ReadChar());
    }

    wchar_t * StringWriter::GetString()
    {
        return (_sob);
    }

    size_t StringWriter::GetLength()
    {
        return (_written);
    }

    bool StringWriter::IsBufferAssigned()
    {
        return (_p != nullptr);
    }

    ReverseStringWriter::ReverseStringWriter(wchar_t * p, wchar_t * sob, wchar_t * eob)
        : StringWriter(p, sob, eob)
    {
    }

    ReverseStringWriter::ReverseStringWriter(wchar_t * buffer, size_t size)
        : StringWriter(buffer != nullptr ? buffer + size : nullptr, buffer, buffer != nullptr ? buffer + size : nullptr)
    {
        Write(L'\0');
    }

    void ReverseStringWriter::Write(wchar_t c)
    {
        if (_p <= _sob)
            throw InsufficientBufferException(L"書き込み先バッファのサイズが不足しています。");
        --_p;
        *_p = c;
        ++_written;
    }

    void ReverseStringWriter::Write(const wchar_t * str)
    {
        const wchar_t* p = str + lstrlenW(str);
        while (p > str)
        {
            --p;
            Write(*p);
        }
    }

    void ReverseStringWriter::Write(const wchar_t * ptr, size_t count)
    {
        const wchar_t* p = ptr + count;
        while (p > ptr)
        {
            --p;
            Write(*p);
        }
    }

    wchar_t * ReverseStringWriter::GetString()
    {
        return (_p);
    }

}


/*
 * END OF FILE
 */