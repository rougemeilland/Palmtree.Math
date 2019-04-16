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


#include "pmc_uint.h"


namespace Palmtree::Math::Core::Internal
{

    class __DLLEXPORT_UINT StringReader
    {
    protected:
        const wchar_t* _p;
        const wchar_t* _limit;

    protected:
        StringReader(const wchar_t* p, const wchar_t* limit);

    private:
        StringReader(const StringReader& p);

    public:
        StringReader(const wchar_t* p);
        StringReader(const wchar_t* p, size_t length);
        wchar_t ReadChar();
        wchar_t ReadChar(wchar_t default_char);
        virtual wchar_t PeekChar();
        virtual void Progress();
        virtual int StartsWith(const wchar_t* str);
        void SkipSpace();
        virtual void SkipString(const wchar_t* str);

    private:
        static int StartsWith(const wchar_t* a, const wchar_t* a_limit, const wchar_t* b);

    };

    class __DLLEXPORT_UINT ReverseStringReader
        : public StringReader
    {
    public:
        ReverseStringReader(const wchar_t* p);
        ReverseStringReader(const wchar_t* p, size_t length);

    private:
        ReverseStringReader(const ReverseStringReader& p);

    public:
        virtual wchar_t PeekChar();
        virtual  void Progress();
        virtual int StartsWith(const wchar_t* str);
        virtual void SkipString(const wchar_t* str);

    private:
        static int StartsWith(const wchar_t* a, const wchar_t* a_limit, const wchar_t* b);

    };

    class __DLLEXPORT_UINT StringWriter
    {
    protected:
        wchar_t* _p;
        wchar_t* _sob;
        wchar_t* _eob;
        size_t _written;

        StringWriter(wchar_t* p, wchar_t* sob, wchar_t* eob);

    public:
        StringWriter(wchar_t* buffer, size_t size);

    private:
        StringWriter(const StringWriter& p);

    public:
        virtual void Write(wchar_t c);
        void Write(wchar_t c, size_t count);
        virtual void Write(const wchar_t* str);
        virtual void Write(const wchar_t* ptr, size_t count);
        void Write(StringReader& reader);
        virtual wchar_t* GetString();
        size_t GetLength();
        bool IsBufferAssigned();
    };

    class __DLLEXPORT_UINT ReverseStringWriter
        : public StringWriter
    {
    protected:
        ReverseStringWriter(wchar_t* p, wchar_t* sob, wchar_t* eob);

    public:
        ReverseStringWriter(wchar_t* buffer, size_t size);

    private:
        ReverseStringWriter(const ReverseStringWriter& p);

    public:
        using StringWriter::Write; // ←これを追加しないと、StringWriter::Writeが ReverseStringWriter::Write により隠蔽されて不可視となってしまう。(不可視判定は名前のみで行われパラメタは反映されない)
        virtual void Write(wchar_t c) override;
        virtual void Write(const wchar_t* str) override;
        virtual void Write(const wchar_t* ptr, size_t count) override;
        virtual wchar_t* GetString() override;
    };

}

#endif


 /*
  * END OF FILE
  */
