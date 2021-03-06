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

#include "pmc_resourceholder.h"
#include "pmc_exception.h"
#include "pmc_threadcontext.h"
#include "pmc_lock.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"
#include "pmc___unit_type_array_chainbuffertag.h"

namespace Palmtree::Math::Core::Internal
{
     ResourceHolder::__ChainBufferTag::__ChainBufferTag()
         : BidirectionalListHeader< ResourceHolder::__ChainBufferTag>(this)
     {
     }

     ResourceHolder::__ChainBufferTag::~__ChainBufferTag()
     {
         Remove();
     }

     void ResourceHolder::__ChainBufferTag::Link(__ChainBufferTag * tag)
     {
         AddAffter(tag);
     }

     void ResourceHolder::__ChainBufferTag::Clear()
     {
     }

     void ResourceHolder::__ChainBufferTag::Check()
     {
     }

     ResourceHolder::__RootTag::__RootTag()
     {
     }

     ResourceHolder::__RootTag::~__RootTag()
     {
     }

     bool ResourceHolder::__RootTag::EqualsBufferAddress(void * buffer)
     {
         throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_resourceholder.h;ResourceHolder::__RootTag::EqualsBufferAddress;1");
     }

     void ResourceHolder::__RootTag::Destruct()
     {
     }

     ResourceHolder::ResourceHolder(ThreadContext& tc)
         : _tc(tc)
     {
     }

     ResourceHolder::~ResourceHolder()
     {
         Lock lock_obj;
         while (_root_tag.Next() != &_root_tag)
         {
             __ChainBufferTag* tag = _root_tag.Next();
             tag->Destruct();
             delete tag;
             _tc.DecrementTypeBAllocationCount();
         }
     }

     wchar_t * ResourceHolder::AllocateString(size_t count)
     {
         Lock lock_obj;
         __UNIT_TYPE word_count = _DIVIDE_CEILING_UNIT(count * sizeof(wchar_t), __UNIT_TYPE_BYTE_COUNT);
         __UNIT_TYPE check_code;
         __UNIT_TYPE* buffer = Palmtree::Math::Core::Internal::__AllocateBlock(_tc, word_count, &check_code);
         __ChainBufferTag* tag = new ____UNIT_TYPE_Array_ChainBufferTag(_tc, buffer, word_count, check_code);
         _tc.IncrementTypeBAllocationCount();
         LinkTag(tag);
         return ((wchar_t*)buffer);
     }

     void ResourceHolder::ClearString(wchar_t * buffer)
     {
         Lock lock_obj;
         __ChainBufferTag* tag = FindTag(buffer);
         if (tag == nullptr)
             throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::ClearString;1");
         tag->Clear();
     }

     void ResourceHolder::DeallocateString(wchar_t * buffer)
     {
         Lock lock_obj;
         __ChainBufferTag* tag = FindTag(buffer);
         if (tag != nullptr)
         {
             tag->Destruct();
             delete tag;
             _tc.DecrementTypeBAllocationCount();
         }
     }

#ifdef _DEBUG
     void ResourceHolder::CheckString(wchar_t * buffer)
     {
         Lock lock_obj;
         __ChainBufferTag* tag = FindTag(buffer);
         if (tag == nullptr)
             throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckString;1");
         tag->Check();
     }
#endif

     void ResourceHolder::UnlinkString(wchar_t * buffer)
     {
         Lock lock_obj;
         __ChainBufferTag* tag = FindTag(buffer);
         if (tag == nullptr)
             throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBlock;1");
         delete tag;
         _tc.DecrementTypeBAllocationCount();
     }

     void ResourceHolder::LinkTag(__ChainBufferTag * tag)
     {
         _root_tag.Link(tag);
     }

     ResourceHolder::__ChainBufferTag * ResourceHolder::FindTag(void * buffer)
     {
         for (__ChainBufferTag* tag = _root_tag.Next(); tag != &_root_tag; tag = tag->Next())
         {
             if (tag->EqualsBufferAddress(buffer))
                 return (tag);
         }
         return (nullptr);
     }

     void ResourceHolder::NotExists(void * buffer)
     {
         void* found_tag = FindTag(buffer);
         if (found_tag != nullptr)
             throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_resourceholder.h;ResourceHolder::CheckBuffer;1");
     }

}


/*
 * END OF FILE
 */