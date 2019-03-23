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


#include <windows.h>
#include "pmc_sint_internal.h"
#include "pmc_inline_func.h"
#include "pmc_resourceholder_sint.h"


#pragma region プラットフォーム固有の定義
#ifdef _M_IX86
#define	DEFAULT_MEMORY_DATA (0xcccccccc)
#elif defined(_M_X64)
#define	DEFAULT_MEMORY_DATA (0xcccccccccccccccc)
#else
#error unknown platform
#endif
#pragma endregion


namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
    static HANDLE hLocalHeap;
    static CRITICAL_SECTION mcs;
    NUMBER_OBJECT_SINT number_object_sint_zero;
    NUMBER_OBJECT_SINT number_object_sint_one;
    NUMBER_OBJECT_SINT number_object_sint_minus_one;
    PMC_HANDLE_UINT number_handle_uint_zero;
    PMC_HANDLE_UINT number_handle_uint_one;
#pragma endregion


    __inline static void ClearNumberHeader(NUMBER_OBJECT_SINT* p)
    {
#ifdef _M_IX64
        if (sizeof(*p) == sizeof(_UINT64_T) * 4)
        {
            _UINT64_T* __p = (_UINT64_T*)p;
            __p[0] = 0;
            __p[1] = 0;
            __p[2] = 0;
            __p[3] = 0;
        }
        else
        {
#endif
            if (sizeof(*p) == sizeof(_UINT32_T) * 6)
            {
                _UINT32_T* __p = (_UINT32_T*)p;
                __p[0] = 0;
                __p[1] = 0;
                __p[2] = 0;
                __p[3] = 0;
                __p[4] = 0;
            }
#ifdef _M_IX64
            else if (sizeof(*p) % sizeof(_UINT64_T) == 0)
                _ZERO_MEMORY_64((_UINT64_T*)p, sizeof(*p) / sizeof(_UINT64_T));
#endif
            else if (sizeof(*p) % sizeof(_UINT32_T) == 0)
                _ZERO_MEMORY_32((_UINT32_T*)p, sizeof(*p) / sizeof(_UINT32_T));
            else if (sizeof(*p) % sizeof(_UINT16_T) == 0)
                _ZERO_MEMORY_16((_UINT16_T*)p, sizeof(*p) / sizeof(_UINT16_T));
            else
                _ZERO_MEMORY_BYTE(p, sizeof(*p));
#ifdef _M_IX64
        }
#endif
    }

    __inline static void FillNumberHeader(NUMBER_OBJECT_SINT* p)
    {
#ifdef _M_IX64
        if (sizeof(*p) == sizeof(_UINT64_T) * 4)
        {
            _UINT64_T* __p = (_UINT64_T*)p;
            __p[0] = DEFAULT_MEMORY_DATA;
            __p[1] = DEFAULT_MEMORY_DATA;
            __p[2] = DEFAULT_MEMORY_DATA;
            __p[3] = DEFAULT_MEMORY_DATA;
        }
        else
        {
#endif
            if (sizeof(*p) == sizeof(_UINT32_T) * 6)
            {
                _UINT32_T* __p = (_UINT32_T*)p;
                __p[0] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[1] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[2] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[3] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[4] = (_UINT32_T)DEFAULT_MEMORY_DATA;
            }
#ifdef _M_IX64
            else if (sizeof(*p) % sizeof(_UINT64_T) == 0)
                _FILL_MEMORY_64((_UINT64_T*)p, DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT64_T));
#endif
            else if (sizeof(*p) % sizeof(_UINT32_T) == 0)
                _FILL_MEMORY_32((_UINT32_T*)p, (_UINT32_T)DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT32_T));
            else if (sizeof(*p) % sizeof(_UINT16_T) == 0)
                _FILL_MEMORY_16((_UINT16_T*)p, (_UINT16_T)DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT16_T));
            else
                _FILL_MEMORY_BYTE(p, (unsigned char)DEFAULT_MEMORY_DATA, sizeof(*p));
#ifdef _M_IX64
        }
#endif
    }

    static void InitializeNumber(NUMBER_OBJECT_SINT* p, SIGN_T sign, PMC_HANDLE_UINT abs)
    {
        if (abs->FLAGS.IS_ZERO)
            sign = SIGN_ZERO;
        ClearNumberHeader(p);
        p->SIGNATURE1 = PMC_SIGNATURE;
        p->SIGNATURE2 = PMC_SINT_SIGNATURE;
        p->SIGN = sign;
        p->ABS = abs;
        p->IS_EVEN = abs->FLAGS.IS_EVEN;
        if (abs->FLAGS.IS_ZERO)
        {
            p->IS_MINUS_ONE = false;
            p->IS_ONE = false;
            p->IS_POWER_OF_TWO = false;
            p->IS_ZERO = true;
        }
        else if (sign >= 0)
        {
            p->IS_MINUS_ONE = false;
            p->IS_ONE = abs->FLAGS.IS_ONE;
            p->IS_POWER_OF_TWO = abs->FLAGS.IS_POWER_OF_TWO;
            p->IS_ZERO = false;
        }
        else
        {
            p->IS_MINUS_ONE = abs->FLAGS.IS_ONE;
            p->IS_ONE = false;
            p->IS_POWER_OF_TWO = false;
            p->IS_ZERO = false;
        }

#ifdef _DEBUG
        if (sign != SIGN_NEGATIVE && sign != SIGN_ZERO && sign != SIGN_POSITIVE)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;1");

        if (sign != SIGN_ZERO && p->IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;2");

        if (sign == SIGN_ZERO && !p->IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;3");
#endif
    }

    static void CleanUpNumber(NUMBER_OBJECT_SINT* p)
    {
        ep_uint.Dispose(p->ABS);
    }

    static void AttatchNumber(NUMBER_OBJECT_SINT* p, SIGN_T sign, PMC_HANDLE_UINT abs)
    {
        InitializeNumber(p, sign, abs);
        p->IS_STATIC = TRUE;
    }

    static NUMBER_OBJECT_SINT* AllocateNumber(SIGN_T sign, PMC_HANDLE_UINT abs)
    {
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* p = (NUMBER_OBJECT_SINT*)root.AllocateBytes(sizeof(NUMBER_OBJECT_SINT));
        InitializeNumber(p, sign, abs);
        p->IS_STATIC = FALSE;
        root.UnlinkBytes(p);
        return (p);
    }

    static void DetatchNumber(NUMBER_OBJECT_SINT* p)
    {
        if (p == nullptr || !p->IS_STATIC)
            return;
        CleanUpNumber(p);
    }

    static void DeallocateNumber(NUMBER_OBJECT_SINT* p)
    {
        if (p == nullptr || p->IS_STATIC)
            return;
        CleanUpNumber(p);
        FillNumberHeader(p);
        HeapFree(hLocalHeap, 0, p);
    }

    void __CheckNumber(NUMBER_OBJECT_SINT* p) noexcept(false)
    {
        if (p->SIGNATURE1 != PMC_SIGNATURE || p->SIGNATURE2 != PMC_SINT_SIGNATURE)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;1");
        ep_uint.CheckHandle(p->ABS);
    }

    NUMBER_OBJECT_SINT* From_I_Imp(SIGN_T x_sign, _UINT32_T x_abs)
    {
        if (x_abs == 0)
            return (&number_object_sint_zero);
        else
        {
            ResourceHolderSINT root;
            PMC_HANDLE_UINT o_abs = ep_uint.From(x_abs);
            root.HookNumber(o_abs);
            NUMBER_OBJECT_SINT* o = root.AllocateNumber(x_sign, o_abs);
            root.UnlinkNumber(o_abs);
            root.UnlinkNumber(o);
            return (o);
        }
        return (PMC_STATUS_OK);
    }

    NUMBER_OBJECT_SINT* From_L_Imp(SIGN_T x_sign, _UINT64_T x_abs)
    {
        if (x_abs == 0)
            return (&number_object_sint_zero);
        else
        {
            ResourceHolderSINT root;
            PMC_HANDLE_UINT o_abs = ep_uint.From(x_abs);
            root.HookNumber(o_abs);
            NUMBER_OBJECT_SINT* o = root.AllocateNumber(x_sign, o_abs);
            root.UnlinkNumber(o_abs);
            root.UnlinkNumber(o);
            return (o);
        }
    }

    NUMBER_OBJECT_SINT* From_X_Imp(SIGN_T sign, PMC_HANDLE_UINT x)
    {
        if (x->FLAGS.IS_ZERO)
            return (&number_object_sint_zero);
        else
        {
            ResourceHolderSINT root;
            PMC_HANDLE_UINT new_x = ep_uint.Clone(x);
            root.HookNumber(new_x);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, new_x);
            root.UnlinkNumber(new_x);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    NUMBER_OBJECT_SINT* DuplicateNumber_X(NUMBER_OBJECT_SINT* x)
    {
        if (x->IS_STATIC)
            return (x);
        return (From_X_Imp(x->SIGN, x->ABS));
    }

    NUMBER_OBJECT_SINT* NegateNumber_X(NUMBER_OBJECT_SINT* x)
    {
        return (From_X_Imp(INVERT_SIGN(x->SIGN), x->ABS));
    }

    PMC_HANDLE_SINT PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type)
    {
        switch (type)
        {
        case PMC_CONSTANT_ZERO:
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        case PMC_CONSTANT_ONE:
            return (GET_NUMBER_HANDLE(&number_object_sint_one));
        case PMC_CONSTANT_MINUS_ONE:
            return (GET_NUMBER_HANDLE(&number_object_sint_minus_one));
        default:
            throw ArgumentException(L"引数typeが未知の値です。");
        }
    }

    PMC_HANDLE_SINT PMC_Negate_X(PMC_HANDLE_SINT x)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nr = NegateNumber_X(nx);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_Negate_UX(PMC_HANDLE_UINT x)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"x");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nr = From_X_Imp(SIGN_NEGATIVE, x);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_UINT PMC_Abs_X(PMC_HANDLE_SINT x)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        return (ep_uint.Clone(nx->ABS));
    }

    PMC_HANDLE_SINT PMC_Clone_X(PMC_HANDLE_SINT x)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nr = nx->IS_ZERO ? &number_object_sint_zero : DuplicateNumber_X(nx);
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    void PMC_CheckHandle_UX(PMC_HANDLE_UINT p)
    {
        ep_uint.CheckHandle(p);
    }

    void PMC_CheckHandle_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        __CheckNumber(np);
    }

    void PMC_Dispose_UX(PMC_HANDLE_UINT p)
    {
        ep_uint.Dispose(p);
    }

    void PMC_Dispose_X(PMC_HANDLE_SINT p)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        DeallocateNumber(np);
    }

#pragma region チェーンされたメモリ管理
    Lock::Lock()
    {
        EnterCriticalSection(&mcs);
    }

    Lock::~Lock()
    {
        LeaveCriticalSection(&mcs);
    }

    ResourceHolderSINT::__GenericChainBufferTag::__GenericChainBufferTag(void * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderSINT::__GenericChainBufferTag::~__GenericChainBufferTag()
    {
    }

    BOOL ResourceHolderSINT::__GenericChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderSINT::__GenericChainBufferTag::Destruct()
    {
        HeapFree(hLocalHeap, 0, _buffer);
#ifdef _LOG_MEMORY
        {
            wprintf(L"0x%08lx: delete header 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)_buffer);
        }
#endif
    }

    ResourceHolderSINT::__UINTNumberHandleHookingChainBufferTag::__UINTNumberHandleHookingChainBufferTag(PMC_HANDLE_UINT x)
    {
        _buffer = x;
    }

    ResourceHolderSINT::__UINTNumberHandleHookingChainBufferTag::~__UINTNumberHandleHookingChainBufferTag()
    {
    }

    BOOL ResourceHolderSINT::__UINTNumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderSINT::__UINTNumberHandleHookingChainBufferTag::Check()
    {
    }

    void ResourceHolderSINT::__UINTNumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::ep_uint.Dispose(_buffer);
    }

    ResourceHolderSINT::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(NUMBER_OBJECT_SINT * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderSINT::__DynamicNumberChainBufferTag::~__DynamicNumberChainBufferTag()
    {
    }

    BOOL  ResourceHolderSINT::__DynamicNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__DynamicNumberChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::__CheckNumber(_buffer);
    }

    void  ResourceHolderSINT::__DynamicNumberChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::DeallocateNumber(_buffer);
    }

    ResourceHolderSINT::__NumberHandleHookingChainBufferTag::__NumberHandleHookingChainBufferTag(NUMBER_OBJECT_SINT * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderSINT::__NumberHandleHookingChainBufferTag::~__NumberHandleHookingChainBufferTag()
    {
    }

    BOOL  ResourceHolderSINT::__NumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__NumberHandleHookingChainBufferTag::Check()
    {
    }

    void  ResourceHolderSINT::__NumberHandleHookingChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::DeallocateNumber(_buffer);
    }

    ResourceHolderSINT::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(NUMBER_OBJECT_SINT * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderSINT::__StaticNumberChainBufferTag::~__StaticNumberChainBufferTag()
    {
    }

    BOOL  ResourceHolderSINT::__StaticNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderSINT::__StaticNumberChainBufferTag::Check()
    {
    }

    void  ResourceHolderSINT::__StaticNumberChainBufferTag::Destruct()
    {
        DetatchNumber(_buffer);
    }

    ResourceHolderSINT::ResourceHolderSINT()
    {
    }

    ResourceHolderSINT::~ResourceHolderSINT()
    {
    }

    void* ResourceHolderSINT::AllocateBytes(size_t size)
    {
        Lock lock_obj;
        void* buffer = HeapAlloc(hLocalHeap, HEAP_ZERO_MEMORY, size);
        if (buffer == nullptr)
            throw NotEnoughMemoryException(L"ヒープメモリ領域が不足しています。");
#ifdef _LOG_MEMORY
        {
            wprintf(L"0x%08lx: new header 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)buffer);
        }
#endif
        __ChainBufferTag* tag = new __GenericChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderSINT::DeallocateBytes(void * buffer)
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

    void ResourceHolderSINT::UnlinkBytes(void *buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkBytes;1");
        tag->Unlink();
    }

    NUMBER_OBJECT_SINT * ResourceHolderSINT::AllocateNumber(SIGN_T sign, PMC_HANDLE_UINT abs)
    {
#ifdef _DEBUG
        if (sign == SIGN_ZERO && !abs->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;ResourceHolderSINT::AllocateNumber;1");
#endif
        Lock lock_obj;
        NUMBER_OBJECT_SINT* buffer = Palmtree::Math::Core::Internal::AllocateNumber(sign, abs);
#ifdef _DEBUG
        CheckBuffer(buffer);
#endif
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderSINT::HookNumber(NUMBER_OBJECT_SINT * buffer)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!buffer->IS_STATIC)
            CheckBuffer(buffer);
#endif
        __ChainBufferTag* tag = new __NumberHandleHookingChainBufferTag(buffer);
        LinkTag(tag);
    }

    void ResourceHolderSINT::HookNumber(PMC_HANDLE_UINT x)
    {
        Lock lock_obj;
#ifdef _DEBUG
        if (!x->FLAGS.IS_STATIC)
             CheckBuffer(x);
#endif
        __ChainBufferTag* tag = new __UINTNumberHandleHookingChainBufferTag(x);
        LinkTag(tag);
    }

    void ResourceHolderSINT::DeallocateNumber(NUMBER_OBJECT_SINT * buffer)
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

    void ResourceHolderSINT::DeallocateNumber(PMC_HANDLE_UINT x)
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
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkNumber;1");
        tag->Unlink();
    }

    void ResourceHolderSINT::UnlinkNumber(PMC_HANDLE_UINT x)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(x);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkNumber;1");
        tag->Unlink();
    }

    void ResourceHolderSINT::AttatchStaticNumber(NUMBER_OBJECT_SINT * p, SIGN_T sign, PMC_HANDLE_UINT abs)
    {
        Lock lock_obj;
#ifdef _DEBUG
        CheckBuffer(p);
#endif
        Palmtree::Math::Core::Internal::AttatchNumber(p, sign, abs);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(p);
        LinkTag(tag);
    }

    void ResourceHolderSINT::DetatchStaticNumber(NUMBER_OBJECT_SINT * buffer)
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

    void ResourceHolderSINT::UnlinkStatickNumber(NUMBER_OBJECT_SINT * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderSINT::UnlinkStatickNumber;1");
        tag->Unlink();
    }
#pragma endregion

#pragma region ヒープメモリ関連関数

    static BOOL GetAllocatedMemorySize_Imp(_UINT64_T* size)
    {
        *size = 0;
        DWORD LastError;
        PROCESS_HEAP_ENTRY Entry;
        Entry.lpData = nullptr;
        while (HeapWalk(hLocalHeap, &Entry))
        {
            BOOL is_allocated = FALSE;
            if ((Entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) != 0)
            {
                //_tprintf(TEXT("Allocated block"));
                is_allocated = TRUE;

                if ((Entry.wFlags & PROCESS_HEAP_ENTRY_MOVEABLE) != 0)
                {
                    //_tprintf(TEXT(", movable with HANDLE %#p"), Entry.Block.hMem);
                }

                if ((Entry.wFlags & PROCESS_HEAP_ENTRY_DDESHARE) != 0)
                {
                    //_tprintf(TEXT(", DDESHARE"));
                }
            }
            else if ((Entry.wFlags & PROCESS_HEAP_REGION) != 0)
            {
                //_tprintf(TEXT("Region\n  %d bytes committed\n") \
                //    TEXT("  %d bytes uncommitted\n  First block address: %#p\n") \
                //    TEXT("  Last block address: %#p\n"),
                //    Entry.Region.dwCommittedSize,
                //    Entry.Region.dwUnCommittedSize,
                //    Entry.Region.lpFirstBlock,
                //    Entry.Region.lpLastBlock);
            }
            else if ((Entry.wFlags & PROCESS_HEAP_UNCOMMITTED_RANGE) != 0)
            {
                //_tprintf(TEXT("Uncommitted range\n"));
            }
            else
            {
                //_tprintf(TEXT("Block\n"));
            }

            //_tprintf(TEXT("  Data portion begins at: %#p\n  Size: %d bytes\n") \
            //    TEXT("  Overhead: %d bytes\n  Region index: %d\n\n"),
            //    Entry.lpData,
            //    Entry.cbData,
            //    Entry.cbOverhead,
            //    Entry.iRegionIndex);
            if (is_allocated)
                *size += Entry.cbData;
        }
        LastError = GetLastError();
        if (LastError != ERROR_NO_MORE_ITEMS)
        {
            //_tprintf(TEXT("HeapWalk failed with LastError %d.\n"), LastError);
            return (FALSE);
        }
        return (TRUE);
    }

    _UINT64_T PMC_GetAllocatedMemorySize() noexcept(false)
    {
        if (!HeapLock(hLocalHeap))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;GetAllocatedMemorySize;1");
        _UINT64_T size;
        BOOL result = GetAllocatedMemorySize_Imp(&size);
        if (!HeapUnlock(hLocalHeap))
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;GetAllocatedMemorySize;2");
        if (!result)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;GetAllocatedMemorySize;3");
        return (size);
    }

    _INT32_T PMC_GetHashCode(PMC_HANDLE_SINT p) noexcept(false)
    {
        NUMBER_OBJECT_SINT* np = GET_NUMBER_OBJECT(p, L"p");
        return ((_INT32_T)np->SIGN ^ (_INT32_T)np->ABS->HASH_CODE);
    }


#pragma endregion

    PMC_STATUS_CODE Initialize_Memory(void)
    {
        InitializeCriticalSection(&mcs);

        ResourceHolderSINT root;

        try
        {
            PMC_HANDLE_UINT uint_zero = ep_uint.GetConstantValue(PMC_CONSTANT_ZERO);
            root.HookNumber(uint_zero);
            PMC_HANDLE_UINT uint_one = ep_uint.GetConstantValue(PMC_CONSTANT_ONE);
            root.HookNumber(uint_one);
            root.AttatchStaticNumber(&number_object_sint_zero, SIGN_ZERO, uint_zero);
            root.AttatchStaticNumber(&number_object_sint_one, SIGN_POSITIVE, uint_one);
            root.AttatchStaticNumber(&number_object_sint_minus_one, SIGN_NEGATIVE, uint_one);

            number_handle_uint_one = uint_one;
            number_handle_uint_zero = uint_zero;

            root.UnlinkNumber(uint_zero);
            root.UnlinkNumber(uint_one);
            root.UnlinkStatickNumber(&number_object_sint_zero);
            root.UnlinkStatickNumber(&number_object_sint_one);
            root.UnlinkStatickNumber(&number_object_sint_minus_one);

            return (PMC_STATUS_OK);
        }
        catch (const Exception& ex)
        {
            return (ex.GetStatusCode());
        }



    }

    BOOL AllocateSINTHeapArea()
    {
        hLocalHeap = HeapCreate(0, 0x1000, 0);
        if (hLocalHeap == nullptr)
            return (FALSE);
        return (TRUE);
    }

    void DeallocateSINTHeapArea()
    {
        if (hLocalHeap != nullptr)
        {
            HeapDestroy(hLocalHeap);
            hLocalHeap = nullptr;
        }
    }

}


/*
 * END OF FILE
 */