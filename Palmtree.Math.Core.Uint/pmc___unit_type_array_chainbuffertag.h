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

#ifndef ____UNIT_TYPE_Array_ChainBufferTag_h
#define ____UNIT_TYPE_Array_ChainBufferTag_h


#include "pmc_resourceholder.h"
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    class ____UNIT_TYPE_Array_ChainBufferTag
        : public ResourceHolder::__ChainBufferTag
    {
    private:
        __UNIT_TYPE* _buffer;
        __UNIT_TYPE _word_count;
        __UNIT_TYPE _check_code;
    public:
        ____UNIT_TYPE_Array_ChainBufferTag(__UNIT_TYPE* buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code);
        virtual ~____UNIT_TYPE_Array_ChainBufferTag();
        virtual bool EqualsBufferAddress(void* buffer) override;
        void virtual Clear() override;
        void virtual Check() override;
        void virtual Destruct() override;
    };

}

#endif


/*
 * END OF FILE
 */