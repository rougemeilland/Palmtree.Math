/*
 * The MIT License
 *
 * Copyright 2018 Palmtree Software.
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

#include "pmc___unit_type_array_chainbuffertag.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    ____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag(ThreadContext& tc, __UNIT_TYPE * buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code)
        : _tc(tc)
    {
        _buffer = buffer;
        _word_count = word_count;
        _check_code = check_code;
        ++statistics_info.COUNT_ALLOCATE_BLOCK;
    }

    ____UNIT_TYPE_Array_ChainBufferTag::~____UNIT_TYPE_Array_ChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_BLOCK;
    }

    bool  ____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag::Clear()
    {
        _ZERO_MEMORY_UNIT(_buffer, _word_count);
    }

    void  ____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::__CheckBlock(_buffer, _word_count, _check_code);
    }

    void  ____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateBlock(_tc, _buffer, _word_count, _check_code);
    }

}


/*
 * END OF FILE
 */