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

#ifndef PMC_THREAD_CONTEXT_H
#define PMC_THREAD_CONTEXT_H

#include "pmc_uint.h"

namespace Palmtree::Math::Core::Internal
{

    class __DLLEXPORT_UINT ThreadContext
    {
    private:
        _UINT32_T _type_a_count;
        _UINT32_T _type_b_count;

    public:
        ThreadContext();
        virtual ~ThreadContext();

    private:
        ThreadContext(const ThreadContext& p); // コピーは禁止

    public:
        // 数値オブジェクトの獲得カウンタをインクリメントする
        void IncrementTypeAAllocationCount();

        // 数値オブジェクトの獲得カウンタをデクリメントする
        void DecrementTypeAAllocationCount();

        // ResourceHolder の要素の獲得カウンタをインクリメントする
        void IncrementTypeBAllocationCount();

        // ResourceHolder の要素の獲得カウンタをデクリメントする
        void DecrementTypeBAllocationCount();

        // 獲得カウンタを検証する
        bool VerifyAllocationCount(_INT32_T count, bool cause_exception);

        void PrintCounter(const wchar_t* tag);
    };

}


#endif


/*
 * END OF FILE
 */