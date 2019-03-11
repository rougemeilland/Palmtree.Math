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
#ifndef PMC_STRINGIO_H
#define PMC_STRINGIO_H


#include <windows.h>
#include "pmc_exception.h"


namespace Palmtree::Math::Core::Internal
{

    class StringReader
    {
    protected:
        const wchar_t* _p;

    protected:
        StringReader()
            : StringReader(nullptr)
        {
        }

    public:
        StringReader(const wchar_t* p)
        {
            _p = p;
        }

        wchar_t ReadChar()
        {
            wchar_t c = PeekChar();
            Progress();
            return (c);
        }

        wchar_t ReadChar(wchar_t default_char)
        {
            wchar_t c = PeekChar();
            if (c == L'\0')
                return (default_char);
            Progress();
            return (c);
        }

        virtual wchar_t PeekChar()
        {
            return (*_p);
        }

        virtual void Progress()
        {
            if (*_p == L'\0')
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;StringReader::Progress;1");
            ++_p;
        }

        virtual int StartsWith(const wchar_t* str)
        {
            return (StartsWith(_p, str));
        }

        void SkipSpace()
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

        virtual void SkipString(const wchar_t* str)
        {
            if (!StartsWith(_p, str))
            {
                // str で始まっていないにもかかわらず、strをスキップしようとした。
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;StringReader::SkipString;1");
            }
            _p += lstrlenW(str);
        }

    private:
        static int StartsWith(const wchar_t* a, const wchar_t* b)
        {
            while (*b != L'\0')
            {
                if (*a != *b)
                    return (0);
                ++a;
                ++b;
            }
            return (1);
        }

    };

    class ReverseStringReader
        : public StringReader
    {
    private:
        const wchar_t* _start;

    public:
        ReverseStringReader(const wchar_t* p)
            : StringReader(nullptr)
        {
            _start = p;
            _p = p + lstrlenW(p) - 1;
        }

        virtual wchar_t PeekChar()
        {
            if (_p < _start)
                return (L'\0');
            return (*_p);
        }

        virtual  void Progress()
        {
            if (_p < _start)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;ReverseStringReader::Progress;1");
            --_p;
        }

        virtual int StartsWith(const wchar_t* str)
        {
            return (StartsWith(_p, _start, str));
        }

        virtual void SkipString(const wchar_t* str)
        {
            if (!StartsWith(_p, _start, str))
            {
                // str で始まっていないにもかかわらず、strをスキップしようとした。
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_stringio.h;ReverseStringReader::SkipString;1");
            }
            _p -= lstrlenW(str);
        }

    private:
        static int StartsWith(const wchar_t* a, const wchar_t* eoa, const wchar_t* b)
        {
            while (*b != L'\0')
            {
                if (a < eoa || *a != *b)
                    return (0);
                --a;
                ++b;
            }
            return (1);
        }

    };

    class StringWriter
    {
    protected:
        wchar_t* _p;
        wchar_t* _sob;
        wchar_t* _eob;
        size_t _written;

        StringWriter(wchar_t* p, wchar_t* sob, wchar_t* eob)
        {
            _p = p;
            _sob = sob;
            _eob = eob;
            _written = 0;
        }

    public:
        StringWriter(wchar_t* buffer, size_t size)
            : StringWriter(buffer, buffer, buffer != nullptr ? buffer + size : nullptr)
        {
        }

        virtual void Write(wchar_t c)
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

        void Write(wchar_t c, size_t count)
        {
            while (count > 0)
            {
                Write(c);
                --count;
            }
        }

        virtual void Write(const wchar_t* str)
        {
            while (*str != L'\0')
            {
                Write(*str);
                ++str;
            }
        }

        virtual wchar_t* GetString()
        {
            return (_sob);
        }

        size_t GetLength()
        {
            return (_written);
        }

        bool IsBufferAssigned()
        {
            return (_p != nullptr);
        }
    };

    class ReverseStringWriter
        : public StringWriter
    {
    public:
        ReverseStringWriter(wchar_t* buffer, size_t size)
            : StringWriter(buffer != nullptr ? buffer + size : nullptr, buffer, buffer != nullptr ? buffer + size : nullptr)
        {
            Write(L'\0');
        }

        virtual void Write(wchar_t c) override
        {
            if (_p <= _sob)
                throw InsufficientBufferException(L"書き込み先バッファのサイズが不足しています。");
            --_p;
            *_p = c;
            ++_written;
        }

        virtual void Write(const wchar_t* str) override
        {
            const wchar_t* p = str + lstrlenW(str);
            while (p > str)
            {
                --p;
                Write(*p);
            }
        }

        virtual wchar_t* GetString() override
        {
            return (_p);
        }
    };

}

#endif


 /*
  * END OF FILE
  */
