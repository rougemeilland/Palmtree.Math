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


#include "pmc_resourceholder_rtnl.h"
#include "pmc_rtnl_internal.h"
#include "pmc_lock.h"


namespace Palmtree::Math::Core::Internal
{

    ResourceHolderRTNL::__NumberObjectRtnlChainBufferTag::__NumberObjectRtnlChainBufferTag(NUMBER_OBJECT_RTNL * buffer)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    ResourceHolderRTNL::__NumberObjectRtnlChainBufferTag::~__NumberObjectRtnlChainBufferTag()
    {
        --statistics_info.COUNT_ALLOCATE_NUMBER_OBJECT;
    }

    bool ResourceHolderRTNL::__NumberObjectRtnlChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__NumberObjectRtnlChainBufferTag::Destruct()
    {
        __DeallocateHeap(_buffer);
    }

    ResourceHolderRTNL::__UINTNumberHandleHookingChainBufferTag::__UINTNumberHandleHookingChainBufferTag(PMC_HANDLE_UINT x)
    {
        _buffer = x;
        ++statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    ResourceHolderRTNL::__UINTNumberHandleHookingChainBufferTag::~__UINTNumberHandleHookingChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_UX;
    }

    bool ResourceHolderRTNL::__UINTNumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__UINTNumberHandleHookingChainBufferTag::Check()
    {
    }

    void ResourceHolderRTNL::__UINTNumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_uint.Dispose(_buffer);
    }

    ResourceHolderRTNL::__SINTNumberHandleHookingChainBufferTag::__SINTNumberHandleHookingChainBufferTag(PMC_HANDLE_SINT x)
    {
        _buffer = x;
        ++statistics_info.COUNT_HOOK_NUMBER_X;
    }

    ResourceHolderRTNL::__SINTNumberHandleHookingChainBufferTag::~__SINTNumberHandleHookingChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_X;
    }

    bool ResourceHolderRTNL::__SINTNumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderRTNL::__SINTNumberHandleHookingChainBufferTag::Check()
    {
    }

    void ResourceHolderRTNL::__SINTNumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_sint.Dispose(_buffer);
    }

    ResourceHolderRTNL::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(NUMBER_OBJECT_RTNL * buffer)
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
        Palmtree::Math::Core::Internal::__DeallocateNumber(_buffer);
    }

    ResourceHolderRTNL::__NumberHandleHookingChainBufferTag::__NumberHandleHookingChainBufferTag(NUMBER_OBJECT_RTNL * buffer)
    {
        _buffer = buffer;
        ++statistics_info.COUNT_HOOK_NUMBER_R;
    }

    ResourceHolderRTNL::__NumberHandleHookingChainBufferTag::~__NumberHandleHookingChainBufferTag()
    {
        --statistics_info.COUNT_HOOK_NUMBER_R;
    }

    bool  ResourceHolderRTNL::__NumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderRTNL::__NumberHandleHookingChainBufferTag::Check()
    {
    }

    void  ResourceHolderRTNL::__NumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::__DeallocateNumber(_buffer);
    }

    ResourceHolderRTNL::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(NUMBER_OBJECT_RTNL * buffer)
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
        __DetatchNumber(_buffer);
    }

    ResourceHolderRTNL::ResourceHolderRTNL()
    {
    }

    ResourceHolderRTNL::~ResourceHolderRTNL()
    {
    }

    NUMBER_OBJECT_RTNL* ResourceHolderRTNL::AllocateNumberObject()
    {
        Lock lock_obj;
        NUMBER_OBJECT_RTNL* buffer = (NUMBER_OBJECT_RTNL*)__AllocateHeap(sizeof(NUMBER_OBJECT_RTNL));
        __ChainBufferTag* tag = new __NumberObjectRtnlChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderRTNL::UnlinkNumberObject(NUMBER_OBJECT_RTNL *buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkBytes;1");
        tag->Unlink();
        delete tag;
    }

    NUMBER_OBJECT_RTNL * ResourceHolderRTNL::AllocateNumber(PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        Lock lock_obj;
        NUMBER_OBJECT_RTNL* buffer = Palmtree::Math::Core::Internal::__AllocateNumber(numerator, denominator);
#ifdef _DEBUG
        NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderRTNL::HookNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!buffer->IS_STATIC)
            NotExists(buffer);
#endif
        __ChainBufferTag* tag = new __NumberHandleHookingChainBufferTag(buffer);
        LinkTag(tag);
    }

    void ResourceHolderRTNL::HookNumber(PMC_HANDLE_SINT x)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!x->FLAGS.IS_STATIC)
            NotExists(x);
#endif
        __ChainBufferTag* tag = new __SINTNumberHandleHookingChainBufferTag(x);
        LinkTag(tag);
    }

    void ResourceHolderRTNL::HookNumber(PMC_HANDLE_UINT x)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!x->FLAGS.IS_STATIC)
            NotExists(x);
#endif
        __ChainBufferTag* tag = new __UINTNumberHandleHookingChainBufferTag(x);
        LinkTag(tag);
    }

    void ResourceHolderRTNL::DeallocateNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Unlink();
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderRTNL::DeallocateNumber(PMC_HANDLE_SINT x)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            tag->Unlink();
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderRTNL::DeallocateNumber(PMC_HANDLE_UINT x)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            tag->Unlink();
            tag->Destruct();
            delete tag;
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
        Lock lock_obj;
        UnlinkInternalNumber(buffer->NUMERATOR);
        UnlinkInternalNumber(buffer->DENOMINATOR);
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        tag->Unlink();
        delete tag;
    }

    void ResourceHolderRTNL::UnlinkNumber(PMC_HANDLE_SINT x)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        tag->Unlink();
        delete tag;
    }

    void ResourceHolderRTNL::UnlinkNumber(PMC_HANDLE_UINT x)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkNumber;1");
        tag->Unlink();
        delete tag;
    }

    void ResourceHolderRTNL::AttatchStaticNumber(NUMBER_OBJECT_RTNL * p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        Lock lock_obj;
#ifdef _DEBUG
        NotExists(p);
#endif
        Palmtree::Math::Core::Internal::__AttatchNumber(p, numerator, denominator);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(p);
        LinkTag(tag);
    }

    void ResourceHolderRTNL::DetatchStaticNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag != nullptr)
        {
            tag->Unlink();
            tag->Destruct();
            delete tag;
        }
    }

    void ResourceHolderRTNL::UnlinkStatickNumber(NUMBER_OBJECT_RTNL * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderRTNL::UnlinkStatickNumber;1");
        tag->Unlink();
        delete tag;
    }

    void ResourceHolderRTNL::UnlinkInternalNumber(PMC_HANDLE_SINT x)
    {
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            tag->Unlink();
            delete tag;
        }
    }

    void ResourceHolderRTNL::UnlinkInternalNumber(PMC_HANDLE_UINT x)
    {
        __ChainBufferTag* tag = FindTag(x);
        if (tag != nullptr)
        {
            tag->Unlink();
            delete tag;
        }
    }

    PMC_HANDLE_SINT DivideExactly(ResourceHolderRTNL& root, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        PMC_HANDLE_SINT q;
        PMC_HANDLE_SINT r = ep_sint.DivRem(u, v, &q);
        root.HookNumber(q);
        root.HookNumber(r);
        if (!r->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;DivideExactly;1");
        root.UnlinkNumber(q);
        return (q);
    }

    PMC_HANDLE_UINT DivideExactly(ResourceHolderRTNL& root, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        PMC_HANDLE_UINT q;
        PMC_HANDLE_UINT r = ep_uint.DivRem(u, v, &q);
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