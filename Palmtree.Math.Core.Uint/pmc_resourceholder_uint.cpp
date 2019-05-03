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
#include "pmc_threadcontext.h"
#include "pmc_lock.h"
#include "pmc_uint_internal.h"
#include "pmc___unit_type_array_chainbuffertag.h"
#include "pmc_sfmt.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    ResourceHolderUINT::__UBigIntNumberObjectStructureChainBufferTag::__UBigIntNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    ResourceHolderUINT::__UBigIntNumberObjectStructureChainBufferTag::~__UBigIntNumberObjectStructureChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    bool ResourceHolderUINT::__UBigIntNumberObjectStructureChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__UBigIntNumberObjectStructureChainBufferTag::Destruct()
    {
#ifdef USE_WIN32_HEAP
        __DeallocateHeap(_buffer);
#else
        delete _buffer;
#endif
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderUINT::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT * buffer)
        : _tc(tc)
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
        Palmtree::Math::Core::Internal::__DeallocateNumber(_tc, _buffer);
    }

    ResourceHolderUINT::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT * buffer)
        : _tc(tc)
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
        __DetatchNumber(_tc, _buffer);
    }

    ResourceHolderUINT::__RandomStateObjectStructureChainBufferTag::__RandomStateObjectStructureChainBufferTag(ThreadContext& tc, RANDOM_STATE_OBJECT * buffer)
        : _tc(tc), _buffer(buffer)
    {
    }

    ResourceHolderUINT::__RandomStateObjectStructureChainBufferTag::~__RandomStateObjectStructureChainBufferTag()
    {
    }

    bool ResourceHolderUINT::__RandomStateObjectStructureChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__RandomStateObjectStructureChainBufferTag::Destruct()
    {
        delete _buffer;
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderUINT::__RandomStateObjectChainBufferTag::__RandomStateObjectChainBufferTag(ThreadContext & tc, RANDOM_STATE_OBJECT * buffer)
        : _tc(tc), _buffer(buffer)
    {
    }

    ResourceHolderUINT::__RandomStateObjectChainBufferTag::~__RandomStateObjectChainBufferTag()
    {
    }

    bool ResourceHolderUINT::__RandomStateObjectChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__RandomStateObjectChainBufferTag::Check()
    {
    }

    void ResourceHolderUINT::__RandomStateObjectChainBufferTag::Destruct()
    {
        __DeallocateRandomStateObject(_tc, _buffer);
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderUINT::__InternalRandomStateObjectChainBufferTag::__InternalRandomStateObjectChainBufferTag(ThreadContext & tc, void * buffer)
        : _tc(tc), _buffer(buffer)
    {
    }

    ResourceHolderUINT::__InternalRandomStateObjectChainBufferTag::~__InternalRandomStateObjectChainBufferTag()
    {
    }

    bool ResourceHolderUINT::__InternalRandomStateObjectChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__InternalRandomStateObjectChainBufferTag::Check()
    {
    }

    void ResourceHolderUINT::__InternalRandomStateObjectChainBufferTag::Destruct()
    {
        PMCSFMT_DeallocateRandomState(_buffer);
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderUINT::ResourceHolderUINT(ThreadContext& tc)
        : ResourceHolder(tc)
    {
    }

    ResourceHolderUINT::~ResourceHolderUINT()
    {
    }

    NUMBER_OBJECT_UINT* ResourceHolderUINT::AllocateUBigIntNumberObjectStructure()
    {
        Lock lock_obj;
#ifdef USE_WIN32_HEAP
        NUMBER_OBJECT_UINT* buffer = (NUMBER_OBJECT_UINT*)__AllocateHeap(sizeof(NUMBER_OBJECT_UINT));
#else
        NUMBER_OBJECT_UINT* buffer = new NUMBER_OBJECT_UINT();
#endif
        _tc.IncrementTypeAAllocationCount();
        __ChainBufferTag* tag = new __UBigIntNumberObjectStructureChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::DeallocateUBigIntNumberObjectStructure(NUMBER_OBJECT_UINT * buffer)
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

    void ResourceHolderUINT::UnlinkUBigIntNumberObjectStructure(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBytes;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    __UNIT_TYPE * ResourceHolderUINT::AllocateBlock(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        __UNIT_TYPE word_count;
        __UNIT_TYPE check_code;
        __UNIT_TYPE* buffer = Palmtree::Math::Core::Internal::__AllocateBlock(_tc, bit_count, &word_count, &check_code);
        __ChainBufferTag* tag = new ____UNIT_TYPE_Array_ChainBufferTag(_tc, buffer, word_count, check_code);
        _tc.IncrementTypeBAllocationCount();
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
            _tc.DecrementTypeBAllocationCount();
        }
    }

#ifdef _DEBUG
    void ResourceHolderUINT::CheckBlock(__UNIT_TYPE * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckBlock;1");
        tag->Check();
    }
#endif

    void ResourceHolderUINT::UnlinkBlock(__UNIT_TYPE * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBlock;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }


    NUMBER_OBJECT_UINT * ResourceHolderUINT::AllocateNumber(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        NUMBER_OBJECT_UINT* buffer = Palmtree::Math::Core::Internal::__AllocateNumber(_tc, bit_count);
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::HookNumber(NUMBER_OBJECT_UINT * buffer)
    {
        if (buffer->IS_SHARED)
            return;
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderUINT::DeallocateNumber(NUMBER_OBJECT_UINT * buffer)
    {
        if (buffer->IS_SHARED)
            return;
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
    void ResourceHolderUINT::CheckNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckNumber;1");
        tag->Check();
    }
#endif

    void ResourceHolderUINT::UnlinkNumber(NUMBER_OBJECT_UINT * buffer)
    {
        if (buffer->IS_SHARED)
            return;
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderUINT::AttatchStaticNumber(NUMBER_OBJECT_UINT* p, __UNIT_TYPE bit_count)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(p);
#endif
        Palmtree::Math::Core::Internal::__AttatchNumber(_tc, p, bit_count);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(_tc, p);
        _tc.IncrementTypeBAllocationCount();
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
            _tc.DecrementTypeBAllocationCount();
        }
    }

    void ResourceHolderUINT::UnlinkStatickNumber(NUMBER_OBJECT_UINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkStatickNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    RANDOM_STATE_OBJECT * ResourceHolderUINT::AllocateRandomStateObjectStructure()
    {
        Lock lock_obj;
        RANDOM_STATE_OBJECT* buffer = new RANDOM_STATE_OBJECT();
        _tc.IncrementTypeAAllocationCount();
        memset(buffer, 0, sizeof(buffer));
        __ChainBufferTag* tag = new __RandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    RANDOM_STATE_OBJECT * ResourceHolderUINT::AllocateRandomStateObject(_UINT32_T seed)
    {
        Lock lock_obj;
        RANDOM_STATE_OBJECT* buffer = __AllocateRandomStateObjectFromUInt32(_tc, seed);
        __ChainBufferTag* tag = new __RandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    RANDOM_STATE_OBJECT * ResourceHolderUINT::AllocateRandomStateObject(_UINT32_T * init_key, _INT32_T key_length)
    {
        Lock lock_obj;
        RANDOM_STATE_OBJECT* buffer = __AllocateRandomStateObjectFromUInt32Array(_tc, init_key, key_length);
        __ChainBufferTag* tag = new __RandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::DeallocateRandomStateObject(RANDOM_STATE_OBJECT * buffer)
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

    void ResourceHolderUINT::HookRandomStateObject(RANDOM_STATE_OBJECT * buffer)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __RandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderUINT::UnlinkRandomStateObject(RANDOM_STATE_OBJECT * buffer)
    {
        Lock lock_obj;
        UnlinkInternalRandomStateObjectInternally(buffer->STATE);
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::Unlink;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void * ResourceHolderUINT::AllocateInternalRandomStateObject(_UINT32_T seed)
    {
        Lock lock_obj;
        void* buffer = PMCSFMT_AllocateRandomStateFromUInt32(seed);
        if (buffer == nullptr)
            throw NotEnoughMemoryException(L"乱数の状態を記憶するためのメモリ領域が不足しています。");
        _tc.IncrementTypeAAllocationCount();
        __ChainBufferTag * tag = new __InternalRandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void * ResourceHolderUINT::AllocateInternalRandomStateObject(_UINT32_T * init_key, _INT32_T key_length)
    {
        Lock lock_obj;
        void* buffer = PMCSFMT_AllocateRandomStateFromUInt32Array(init_key, key_length);
        if (buffer == nullptr)
            throw NotEnoughMemoryException(L"乱数の状態を記憶するためのメモリ領域が不足しています。");
        _tc.IncrementTypeAAllocationCount();
        __ChainBufferTag * tag = new __InternalRandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::DeallocateInternalRandomStateObject(void * buffer)
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

    void ResourceHolderUINT::HookInternalRandomStateObject(void * buffer)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __InternalRandomStateObjectChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderUINT::UnlinkInternalRandomStateObject(void * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::Unlink;2");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderUINT::UnlinkInternalRandomStateObjectInternally(void * buffer)
    {
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            delete tag;
            _tc.DecrementTypeBAllocationCount();
        }
    }

}


/*
 * END OF FILE
 */