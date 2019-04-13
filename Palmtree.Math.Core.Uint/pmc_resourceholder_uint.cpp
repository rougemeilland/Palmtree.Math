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


#include "pmc_resourceholder_uint.h"
#include "pmc_lock.h"
#include "pmc_uint_internal.h"
#include "pmc___unit_type_array_chainbuffertag.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    ResourceHolderUINT::__NumberObjectUintChainBufferTag::__NumberObjectUintChainBufferTag(NUMBER_OBJECT_UINT * buffer)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    ResourceHolderUINT::__NumberObjectUintChainBufferTag::~__NumberObjectUintChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    bool ResourceHolderUINT::__NumberObjectUintChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__NumberObjectUintChainBufferTag::Destruct()
    {
        __DeallocateHeap(_buffer);
    }

    ResourceHolderUINT::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(NUMBER_OBJECT_UINT * buffer)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    ResourceHolderUINT::__DynamicNumberChainBufferTag::~__DynamicNumberChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    bool  ResourceHolderUINT::__DynamicNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__DynamicNumberChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::__CheckNumber(_buffer);
    }

    void  ResourceHolderUINT::__DynamicNumberChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_buffer);
    }

    ResourceHolderUINT::__NumberHandleHookingChainBufferTag::__NumberHandleHookingChainBufferTag(NUMBER_OBJECT_UINT * buffer)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_HOOK_NUMBER;
    }

    ResourceHolderUINT::__NumberHandleHookingChainBufferTag::~__NumberHandleHookingChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER;
    }

    bool  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::Check()
    {
    }

    void  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_buffer);
    }

    ResourceHolderUINT::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(NUMBER_OBJECT_UINT * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderUINT::__StaticNumberChainBufferTag::~__StaticNumberChainBufferTag()
    {
    }

    bool  ResourceHolderUINT::__StaticNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__StaticNumberChainBufferTag::Check()
    {
    }

    void  ResourceHolderUINT::__StaticNumberChainBufferTag::Destruct()
    {
        __DetatchNumber(_buffer);
    }

    ResourceHolderUINT::ResourceHolderUINT()
    {
    }

    ResourceHolderUINT::~ResourceHolderUINT()
    {
    }

    NUMBER_OBJECT_UINT* ResourceHolderUINT::AllocateNumberObjectUint()
    {
        Lock lock_obj;
        NUMBER_OBJECT_UINT* buffer = (NUMBER_OBJECT_UINT*)__AllocateHeap(sizeof(NUMBER_OBJECT_UINT));
        __ChainBufferTag* tag = new __NumberObjectUintChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::DeallocateNumberObjectUint(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderUINT::UnlinkNumberObjectUint(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBytes;1");
        delete tag;
    }

    __UNIT_TYPE * ResourceHolderUINT::AllocateBlock(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        __UNIT_TYPE word_count;
        __UNIT_TYPE check_code;
        __UNIT_TYPE* buffer = Palmtree::Math::Core::Internal::__AllocateBlock(bit_count, &word_count, &check_code);
        __ChainBufferTag* tag = new ____UNIT_TYPE_Array_ChainBufferTag(buffer, word_count, check_code);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::ClearBlock(__UNIT_TYPE * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::ClearBlock;1");
        tag->Clear();
    }

    void ResourceHolderUINT::DeallocateBlock(__UNIT_TYPE * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderUINT::CheckBlock(__UNIT_TYPE * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckBlock;1");
        tag->Check();
#endif
    }

    void ResourceHolderUINT::UnlinkBlock(__UNIT_TYPE * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBlock;1");
        delete tag;
    }


    NUMBER_OBJECT_UINT * ResourceHolderUINT::AllocateNumber(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        NUMBER_OBJECT_UINT* buffer = Palmtree::Math::Core::Internal::__AllocateNumber(bit_count);
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::HookNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!buffer->IS_STATIC)
            NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __NumberHandleHookingChainBufferTag(buffer);
        LinkTag(tag);
    }

    void ResourceHolderUINT::DeallocateNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderUINT::CheckNumber(NUMBER_OBJECT_UINT * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckNumber;1");
        tag->Check();
#endif
    }

    void ResourceHolderUINT::UnlinkNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkNumber;1");
        delete tag;
    }

    void ResourceHolderUINT::AttatchStaticNumber(NUMBER_OBJECT_UINT* p, __UNIT_TYPE bit_count)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(p);
#endif
        Palmtree::Math::Core::Internal::__AttatchNumber(p, bit_count);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(p);
        LinkTag(tag);
    }

    void ResourceHolderUINT::DetatchStaticNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderUINT::UnlinkStatickNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkStatickNumber;1");
        delete tag;
    }

}


/*
 * END OF FILE
 */