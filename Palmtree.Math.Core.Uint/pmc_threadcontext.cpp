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


#include <windows.h>
#include "pmc_threadcontext.h"
#include "pmc_exception.h"

namespace Palmtree::Math::Core::Internal
{

     ThreadContext::ThreadContext()
        : _type_a_count(0), _type_b_count(0)
     {
     }

     ThreadContext::~ThreadContext()
     {
     }

     void ThreadContext::IncrementTypeAAllocationCount()
     {
         _InterlockedIncrement(&_type_a_count);
     }

     void ThreadContext::DecrementTypeAAllocationCount()
     {
         _InterlockedDecrement(&_type_a_count);
     }

     void ThreadContext::IncrementTypeBAllocationCount()
     {
         _InterlockedIncrement(&_type_b_count);
     }

     void ThreadContext::DecrementTypeBAllocationCount()
     {
         _InterlockedDecrement(&_type_b_count);
     }

     bool ThreadContext::VerifyAllocationCount(_INT32_T count, bool cause_exception)
     {
         if (cause_exception)
         {
             if ((_INT32_T)_type_a_count != count)
                 throw BadBufferException(L"メモリの解放漏れを検出しました。", L"pmc_threadcontext.cpp;ThreadContext::VerifyAllocationCount;1");
             if (_type_b_count != 0)
                 throw BadBufferException(L"メモリの解放漏れを検出しました。", L"pmc_threadcontext.cpp;ThreadContext::VerifyAllocationCount;2");
         }
         else
         {
             if ((_INT32_T)_type_a_count != count)
                 return (false);
             if (_type_b_count != 0)
                 return (false);
         }
         return (true);
     }

     void ThreadContext::PrintCounter(const wchar_t* tag)
     {
         wchar_t buf[256];
         wsprintfW(buf, L"%ls: %d, %d\n", tag, _type_a_count, _type_b_count);
         ::OutputDebugStringW(buf);
     }

}


/*
 * END OF FILE
 */