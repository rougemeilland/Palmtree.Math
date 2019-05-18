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

#ifndef PMC_THOUSAND_SEPARATED_STRING_WRITER_H
#define PMC_THOUSAND_SEPARATED_STRING_WRITER_H

#include "pmc_stringio.h"

namespace Palmtree::Math::Core::Internal
{

    class __DLLEXPORT_UINT ThousandSeparatedStringWriter
        : public ReverseStringWriter
    {
    private:
        ReverseStringWriter& _native_writer;
        bool _is_supported_thousand;
        const wchar_t* _group_separator;
        const wchar_t* _current_group;
        int _current_group_size;
        int _current_group_index;

    public:
        ThousandSeparatedStringWriter(ReverseStringWriter& native_writer, wchar_t format_type, const PMC_NUMBER_FORMAT_INFO& format_option);
        using StringWriter::Write; // ←これを追加しないと、StringWriter::Writeが ThousandSeparatedStringWriter::Write により隠蔽されて不可視となってしまう。(不可視判定は名前のみで行われパラメタは反映されない)
        virtual void Write(wchar_t c) override;
        virtual void Write(const wchar_t* str) override;
        virtual wchar_t* GetString() override;
    };

}

#endif

/*
 * END OF FILE
 */