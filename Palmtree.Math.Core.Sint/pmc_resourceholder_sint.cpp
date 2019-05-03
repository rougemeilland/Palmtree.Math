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


#include "pmc_resourceholder_sint.h"
#include "pmc_threadcontext.h"
#include "pmc_lock.h"


namespace Palmtree::Math::Core::Internal
{

    ResourceHolderSINT::__BigIntNumberObjectStructureChainBufferTag::__BigIntNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    ResourceHolderSINT::__BigIntNumberObjectStructureChainBufferTag::~__BigIntNumberObjectStructureChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    bool ResourceHolderSINT::__BigIntNumberObjectStructureChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderSINT::__BigIntNumberObjectStructureChainBufferTag::Destruct()
    {
#ifdef USE_WIN32_HEAP
        __DeallocateHeap(_buffer);
#else
        delete _buffer;
#endif
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderSINT::__UBigIntNumberHandleChainBufferTag::__UBigIntNumberHandleChainBufferTag(ThreadContext& tc, PMC_HANDLE_UINT x)
        : _tc(tc)
    {
        _buffer = x;
        ++statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    ResourceHolderSINT::__UBigIntNumberHandleChainBufferTag::~__UBigIntNumberHandleChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    bool ResourceHolderSINT::__UBigIntNumberHandleChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderSINT::__UBigIntNumberHandleChainBufferTag::Check()
    {
    }

    void ResourceHolderSINT::__UBigIntNumberHandleChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_uint.Dispose(_tc, _buffer);
    }

    ResourceHolderSINT::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    ResourceHolderSINT::__DynamicNumberChainBufferTag::~__DynamicNumberChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    bool  ResourceHolderSINT::__DynamicNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__DynamicNumberChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::__CheckNumber(_buffer);
    }

    void  ResourceHolderSINT::__DynamicNumberChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_tc, _buffer);
    }

    ResourceHolderSINT::__SINTNumberHandleChainBufferTag::__SINTNumberHandleChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_HOOK_NUMBER_X;
    }

    ResourceHolderSINT::__SINTNumberHandleChainBufferTag::~__SINTNumberHandleChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_X;
    }

    bool ResourceHolderSINT::__SINTNumberHandleChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__SINTNumberHandleChainBufferTag::Check()
    {
    }

    void  ResourceHolderSINT::__SINTNumberHandleChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_tc, _buffer);
    }

    ResourceHolderSINT::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
    }

    ResourceHolderSINT::__StaticNumberChainBufferTag::~__StaticNumberChainBufferTag()
    {
    }

    bool ResourceHolderSINT::__StaticNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__StaticNumberChainBufferTag::Check()
    {
    }

    void  ResourceHolderSINT::__StaticNumberChainBufferTag::Destruct()
    {
        __DetatchNumber(_tc, _buffer);
    }

    ResourceHolderSINT::ResourceHolderSINT(ThreadContext& tc)
        : ResourceHolder(tc)
    {
    }

    ResourceHolderSINT::~ResourceHolderSINT()
    {
    }

    NUMBER_OBJECT_SINT * ResourceHolderSINT::AllocateBigIntNumberObjectStructure()
    {
        Lock lock_obj;
#ifdef USE_WIN32_HEAP
        NUMBER_OBJECT_SINT* buffer = (NUMBER_OBJECT_SINT*)__AllocateHeap(sizeof(NUMBER_OBJECT_SINT));
#else
        NUMBER_OBJECT_SINT* buffer = new NUMBER_OBJECT_SINT();
#endif
        _tc.IncrementTypeAAllocationCount();
        __ChainBufferTag* tag = new __BigIntNumberObjectStructureChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderSINT::DeallocateBigIntNumberObjectStructure(NUMBER_OBJECT_SINT* buffer)
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

    void ResourceHolderSINT::UnlinkBigIntNumberObjectStructure(NUMBER_OBJECT_SINT* buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkBigIntNumberObjectStructure;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    NUMBER_OBJECT_SINT * ResourceHolderSINT::AllocateNumber(SIGN_T sign, PMC_HANDLE_UINT abs)
    {
#ifdef _DEBUG
        if (sign == SIGN_ZERO && !abs->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;ResourceHolderSINT::AllocateNumber;1");
#endif
        Lock lock_obj;
        NUMBER_OBJECT_SINT* buffer = Palmtree::Math::Core::Internal::__AllocateNumber(_tc, sign, abs);
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        UnlinkInternalNumber(abs);
        return (buffer);
    }

    void ResourceHolderSINT::HookNumber(NUMBER_OBJECT_SINT * buffer)
    {
        if (buffer->IS_SHARED)
            return;
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __SINTNumberHandleChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderSINT::HookNumber(PMC_HANDLE_UINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(x);
#endif
        __ChainBufferTag* tag = new __UBigIntNumberHandleChainBufferTag(_tc, x);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderSINT::DeallocateNumber(NUMBER_OBJECT_SINT * buffer)
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

    void ResourceHolderSINT::DeallocateNumber(PMC_HANDLE_UINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            tag->Destruct();
            delete tag;
            _tc.DecrementTypeBAllocationCount();
        }
    }

    void ResourceHolderSINT::CheckNumber(NUMBER_OBJECT_SINT * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::CheckNumber;1");
        tag->Check();
#endif
    }

    void ResourceHolderSINT::UnlinkNumber(NUMBER_OBJECT_SINT * buffer)
    {
        if (buffer->IS_SHARED)
            return;
        Lock lock_obj;
        UnlinkInternalNumber(buffer->ABS);
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderSINT::UnlinkNumber(PMC_HANDLE_UINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderSINT::AttatchStaticNumber(NUMBER_OBJECT_SINT * p, SIGN_T sign, PMC_HANDLE_UINT abs)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(p);
#endif
        Palmtree::Math::Core::Internal::__AttatchNumber(p, sign, abs);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(_tc, p);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderSINT::DetatchStaticNumber(NUMBER_OBJECT_SINT * buffer)
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

    void ResourceHolderSINT::UnlinkStatickNumber(NUMBER_OBJECT_SINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkStatickNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderSINT::UnlinkInternalNumber(PMC_HANDLE_UINT x)
    {
        __ChainBufferTag* tag = FindTag(x);
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