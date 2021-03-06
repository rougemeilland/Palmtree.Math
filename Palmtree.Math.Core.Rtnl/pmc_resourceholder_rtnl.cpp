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

#include "pmc_resourceholder_rtnl.h"
#include "pmc_threadcontext.h"
#include "pmc_rtnl_internal.h"
#include "pmc_lock.h"

namespace Palmtree::Math::Core::Internal
{

    ResourceHolderRTNL::__RationalNumberObjectStructureChainBufferTag::__RationalNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    ResourceHolderRTNL::__RationalNumberObjectStructureChainBufferTag::~__RationalNumberObjectStructureChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    bool ResourceHolderRTNL::__RationalNumberObjectStructureChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__RationalNumberObjectStructureChainBufferTag::Destruct()
    {
#ifdef USE_WIN32_HEAP
        __DeallocateHeap(_buffer);
#else
        delete _buffer;
#endif
        _tc.DecrementTypeAAllocationCount();
    }

    ResourceHolderRTNL::__UBigIntNumberHandleChainBufferTag::__UBigIntNumberHandleChainBufferTag(ThreadContext& tc, PMC_HANDLE_UINT x)
        : _tc(tc)
    {
        _buffer = x;
        ++statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    ResourceHolderRTNL::__UBigIntNumberHandleChainBufferTag::~__UBigIntNumberHandleChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    bool ResourceHolderRTNL::__UBigIntNumberHandleChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__UBigIntNumberHandleChainBufferTag::Check()
    {
    }

    void ResourceHolderRTNL::__UBigIntNumberHandleChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_uint.Dispose(_tc, _buffer);
    }

    ResourceHolderRTNL::__BigIntNumberHandleChainBufferTag::__BigIntNumberHandleChainBufferTag(ThreadContext& tc, PMC_HANDLE_SINT x)
        : _tc(tc)
    {
        _buffer = x;
        ++statistics_info.COUNT_HOOK_NUMBER_X;
    }

    ResourceHolderRTNL::__BigIntNumberHandleChainBufferTag::~__BigIntNumberHandleChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_X;
    }

    bool ResourceHolderRTNL::__BigIntNumberHandleChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__BigIntNumberHandleChainBufferTag::Check()
    {
    }

    void ResourceHolderRTNL::__BigIntNumberHandleChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_sint.Dispose(_tc, _buffer);
    }

    ResourceHolderRTNL::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    ResourceHolderRTNL::__DynamicNumberChainBufferTag::~__DynamicNumberChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER;
    }

    bool  ResourceHolderRTNL::__DynamicNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderRTNL::__DynamicNumberChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::__CheckNumber(_buffer);
    }

    void  ResourceHolderRTNL::__DynamicNumberChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_tc, _buffer);
    }

    ResourceHolderRTNL::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL * buffer)
        : _tc(tc)
    {
        _buffer = buffer;
    }

    ResourceHolderRTNL::__StaticNumberChainBufferTag::~__StaticNumberChainBufferTag()
    {
    }

    bool  ResourceHolderRTNL::__StaticNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderRTNL::__StaticNumberChainBufferTag::Check()
    {
    }

    void  ResourceHolderRTNL::__StaticNumberChainBufferTag::Destruct()
    {
        __DetatchNumber(_tc, _buffer);
    }

    ResourceHolderRTNL::ResourceHolderRTNL(ThreadContext& tc)
        : ResourceHolder(tc)
    {
    }

    ResourceHolderRTNL::~ResourceHolderRTNL()
    {
    }

    NUMBER_OBJECT_RTNL * ResourceHolderRTNL::AllocateRationalNumberObjectStructure()
    {
        Lock lock_obj;
#ifdef USE_WIN32_HEAP
        NUMBER_OBJECT_RTNL* buffer = (NUMBER_OBJECT_RTNL*)__AllocateHeap(sizeof(NUMBER_OBJECT_RTNL));
#else
        NUMBER_OBJECT_RTNL* buffer = new NUMBER_OBJECT_RTNL();
#endif
        _tc.IncrementTypeAAllocationCount();
        __ChainBufferTag* tag = new __RationalNumberObjectStructureChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderRTNL::UnlinkRationalNumberObjectStructure(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkBytes;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    NUMBER_OBJECT_RTNL * ResourceHolderRTNL::AllocateNumber(PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        Lock lock_obj;
        NUMBER_OBJECT_RTNL* buffer = Palmtree::Math::Core::Internal::__AllocateNumber(_tc, numerator, denominator);
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(_tc, buffer);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
        UnlinkInternalNumber(buffer->NUMERATOR);
        UnlinkInternalNumber(buffer->DENOMINATOR);
        return (buffer);
    }

    void ResourceHolderRTNL::HookNumber(NUMBER_OBJECT_RTNL * buffer)
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

    void ResourceHolderRTNL::HookNumber(PMC_HANDLE_SINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(x);
#endif
        __ChainBufferTag* tag = new __BigIntNumberHandleChainBufferTag(_tc, x);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderRTNL::HookNumber(PMC_HANDLE_UINT x)
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

    void ResourceHolderRTNL::DeallocateNumber(NUMBER_OBJECT_RTNL * buffer)
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

    void ResourceHolderRTNL::DeallocateNumber(PMC_HANDLE_SINT x)
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

    void ResourceHolderRTNL::DeallocateNumber(PMC_HANDLE_UINT x)
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

    void ResourceHolderRTNL::CheckNumber(NUMBER_OBJECT_RTNL * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::CheckNumber;1");
        tag->Check();
#endif
    }

    void ResourceHolderRTNL::UnlinkNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        if (buffer->IS_SHARED)
            return;
        Lock lock_obj;
        UnlinkInternalNumber(buffer->NUMERATOR);
        UnlinkInternalNumber(buffer->DENOMINATOR);
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderRTNL::UnlinkNumber(PMC_HANDLE_SINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderRTNL::UnlinkNumber(PMC_HANDLE_UINT x)
    {
        if (x->FLAGS.IS_SHARED)
            return;
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderRTNL::AttatchStaticNumber(NUMBER_OBJECT_RTNL * p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(p);
#endif
        Palmtree::Math::Core::Internal::__AttatchNumber(_tc, p, numerator, denominator);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(_tc, p);
        _tc.IncrementTypeBAllocationCount();
        LinkTag(tag);
    }

    void ResourceHolderRTNL::DetatchStaticNumber(NUMBER_OBJECT_RTNL * buffer)
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

    void ResourceHolderRTNL::UnlinkStatickNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkStatickNumber;1");
        delete tag;
        _tc.DecrementTypeBAllocationCount();
    }

    void ResourceHolderRTNL::UnlinkInternalNumber(PMC_HANDLE_SINT x)
    {
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            delete tag;
            _tc.DecrementTypeBAllocationCount();
        }
    }

    void ResourceHolderRTNL::UnlinkInternalNumber(PMC_HANDLE_UINT x)
    {
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            delete tag;
            _tc.DecrementTypeBAllocationCount();
        }
    }

    PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, ResourceHolderRTNL& root, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        PMC_HANDLE_SINT q;
        PMC_HANDLE_SINT r = ep_sint.DivRem(tc, u, v, &q);
        root.HookNumber(q);
        root.HookNumber(r);
        if (!r->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;DivideExactly;1");
        root.UnlinkNumber(q);
        return (q);
    }

    PMC_HANDLE_UINT DivideExactly(ThreadContext& tc, ResourceHolderRTNL& root, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        PMC_HANDLE_UINT q;
        PMC_HANDLE_UINT r = ep_uint.DivRem(tc, u, v, &q);
        root.HookNumber(q);
        root.HookNumber(r);
        if (!r->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;DivideExactly;2");
        root.UnlinkNumber(q);
        return (q);
    }

}


/*
 * END OF FILE
 */