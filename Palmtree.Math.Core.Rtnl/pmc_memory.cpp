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
#include "pmc_rtnl_internal.h"
#include "pmc_resourceholder_rtnl.h"
#include "pmc_lock.h"
#include "pmc_inline_func.h"


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
    NUMBER_OBJECT_RTNL number_object_rtnl_zero;
    NUMBER_OBJECT_RTNL number_object_rtnl_one;
    NUMBER_OBJECT_RTNL number_object_rtnl_minus_one;
    PMC_HANDLE_SINT number_handle_sint_zero;
    PMC_HANDLE_SINT number_handle_sint_one;
    PMC_HANDLE_SINT number_handle_sint_minus_one;
    PMC_HANDLE_UINT number_handle_uint_zero;
    PMC_HANDLE_UINT number_handle_uint_one;
#pragma endregion


    __inline static void ClearNumberHeader(NUMBER_OBJECT_RTNL* p)
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

    __inline static void FillNumberHeader(NUMBER_OBJECT_RTNL* p)
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

    static void InitializeNumber(NUMBER_OBJECT_RTNL* p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        if (denominator->FLAGS.IS_ZERO)
        {
            // 分母が 0 の場合
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;1");
        }
#ifdef _DEBUG
        if (numerator->FLAGS.IS_ZERO)
        {
            if (!denominator->FLAGS.IS_ONE)
            {
                // 分子が 0 でかつ分母が 1 ではない場合 ⇒ 0 の場合は 分母は 1 でなければならない。
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;2");
            }
        }
        else
        {
            ResourceHolderRTNL root;
            PMC_HANDLE_UINT gcd = ep_sint.GreatestCommonDivisor(numerator, denominator);
            root.HookNumber(gcd);
            if (!gcd->FLAGS.IS_ONE)
            {
                // 分子と分母は既約でなければならない。
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;InitializeNumber;3");
            }
        }
#endif
            ClearNumberHeader(p);
        p->SIGNATURE1 = PMC_SIGNATURE;
        p->SIGNATURE2 = PMC_RTNL_SIGNATURE;
        p->NUMERATOR = numerator;
        p->DENOMINATOR = denominator;
        if (p->DENOMINATOR->FLAGS.IS_ONE)
        {
            // 分母が 1 である場合
            p->IS_INT = true;
            p->IS_MINUS_ONE = p->NUMERATOR->FLAGS.IS_MINUS_ONE;
            p->IS_ONE = p->NUMERATOR->FLAGS.IS_ONE;
            p->IS_ZERO = p->NUMERATOR->FLAGS.IS_ZERO;
        }
        else
        {
            // 分母が 1 ではない場合
            p->IS_INT = false;
            p->IS_MINUS_ONE = false;
            p->IS_ONE = false;
            p->IS_ZERO = false;
        }
    }

    static void CleanUpNumber(NUMBER_OBJECT_RTNL* p)
    {
        ep_sint.Dispose(p->NUMERATOR);
        ep_uint.Dispose(p->DENOMINATOR);
    }

    void __AttatchNumber(NUMBER_OBJECT_RTNL* p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        InitializeNumber(p, numerator, denominator);
        p->IS_STATIC = true;
    }

    NUMBER_OBJECT_RTNL* __AllocateNumber(PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator)
    {
        ResourceHolderRTNL root;
        NUMBER_OBJECT_RTNL* p = root.AllocateNumberObject();
        InitializeNumber(p, numerator, denominator);
        p->IS_STATIC = false;
        root.UnlinkNumberObject(p);
        return (p);
    }

    void __DetatchNumber(NUMBER_OBJECT_RTNL* p)
    {
        if (p == nullptr || !p->IS_STATIC)
            return;
        CleanUpNumber(p);
    }

    void __DeallocateNumber(NUMBER_OBJECT_RTNL* p)
    {
        Lock lock_obj;
        if (p == nullptr || p->IS_STATIC)
            return;
        if (p->WORKING_COUNT > 0)
            throw InvalidOperationException(L"演算に使用中の数値オブジェクトを解放しようとしました。");
        CleanUpNumber(p);
        FillNumberHeader(p);
        HeapFree(hLocalHeap, 0, p);
    }

    void __CheckNumber(NUMBER_OBJECT_RTNL* p) noexcept(false)
    {
        if (p->SIGNATURE1 != PMC_SIGNATURE || p->SIGNATURE2 != PMC_RTNL_SIGNATURE)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;1");
        ep_sint.CheckHandle(p->NUMERATOR);
        ep_uint.CheckHandle(p->DENOMINATOR);
    }

    NUMBER_OBJECT_RTNL* DuplicateNumber_R(NUMBER_OBJECT_RTNL* x)
    {
        if (x->IS_STATIC)
            return (x);
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT new_numerator = ep_sint.Clone(x->NUMERATOR);
        root.HookNumber(new_numerator);
        PMC_HANDLE_UINT new_denominator = ep_uint.Clone(x->DENOMINATOR);
        root.HookNumber(new_denominator);
        NUMBER_OBJECT_RTNL* w = root.AllocateNumber(new_numerator, new_denominator);
        root.UnlinkNumber(w);
        return (w);
    }

    PMC_HANDLE_RTNL PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type)
    {
        switch (type)
        {
        case PMC_CONSTANT_ZERO:
            return (GET_NUMBER_HANDLE(&number_object_rtnl_zero));
        case PMC_CONSTANT_ONE:
            return (GET_NUMBER_HANDLE(&number_object_rtnl_one));
        case PMC_CONSTANT_MINUS_ONE:
            return (GET_NUMBER_HANDLE(&number_object_rtnl_minus_one));
        default:
            throw ArgumentException(L"引数typeが未知の値です。");
        }
    }

    PMC_HANDLE_RTNL PMC_Clone_R(PMC_HANDLE_RTNL x)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderRTNL root;
        NUMBER_OBJECT_RTNL* nr = DuplicateNumber_R(nx);
        root.HookNumber(nr);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Negate_R(PMC_HANDLE_RTNL x) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderRTNL root;
        PMC_HANDLE_SINT nr_numerator = ep_sint.Negate(nx->NUMERATOR);
        root.HookNumber(nr_numerator);
        PMC_HANDLE_UINT nr_denominator = ep_uint.Clone(nx->DENOMINATOR);
        root.HookNumber(nr_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(nr_numerator, nr_denominator);
        root.HookNumber(nr);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_RTNL PMC_Abs_R(PMC_HANDLE_RTNL x) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderRTNL root;
        PMC_HANDLE_UINT nr_numerator_abs = ep_sint.Abs(nx->NUMERATOR);
        root.HookNumber(nr_numerator_abs);
        PMC_HANDLE_SINT nr_numerator = ep_sint.From(nr_numerator_abs);
        root.HookNumber(nr_numerator);
        PMC_HANDLE_UINT nr_denominator = ep_uint.Clone(nx->DENOMINATOR);
        root.HookNumber(nr_denominator);
        NUMBER_OBJECT_RTNL* nr = root.AllocateNumber(nr_numerator, nr_denominator);
        PMC_HANDLE_RTNL r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    void PMC_CheckHandle_UX(PMC_HANDLE_UINT p)
    {
        ep_uint.CheckHandle(p);
    }

    void PMC_CheckHandle_X(PMC_HANDLE_SINT p)
    {
        ep_sint.CheckHandle(p);
    }

    void PMC_CheckHandle_R(PMC_HANDLE_RTNL p)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        __CheckNumber(np);
    }

    void PMC_Dispose_UX(PMC_HANDLE_UINT p)
    {
        ep_uint.Dispose(p);
    }

    void PMC_Dispose_X(PMC_HANDLE_SINT p)
    {
        ep_sint.Dispose(p);
    }

    void PMC_Dispose_R(PMC_HANDLE_RTNL p)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
       __DeallocateNumber(np);
    }

    void PMC_UseObject_R(PMC_HANDLE_RTNL x) noexcept(false)
    {
        if (x == nullptr)
            return;
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        ++nx->WORKING_COUNT;
    }

    void PMC_UnuseObject_R(PMC_HANDLE_RTNL x) noexcept(false)
    {
        if (x == nullptr)
            return;
        NUMBER_OBJECT_RTNL* nx = GET_NUMBER_OBJECT(x, L"x");
        --nx->WORKING_COUNT;
    }
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

    _INT32_T PMC_GetHashCode(PMC_HANDLE_RTNL p) noexcept(false)
    {
        NUMBER_OBJECT_RTNL* np = GET_NUMBER_OBJECT(p, L"p");
        return ((_INT32_T)ep_sint.GetHashCode(np->NUMERATOR) ^ (_INT32_T)np->DENOMINATOR->HASH_CODE);
    }


#pragma endregion

    PMC_STATUS_CODE Initialize_Memory(void)
    {
        ResourceHolderRTNL root;

        try
        {
            PMC_HANDLE_UINT uint_zero = ep_uint.GetConstantValue(PMC_CONSTANT_ZERO);
            root.HookNumber(uint_zero);
            PMC_HANDLE_UINT uint_one = ep_uint.GetConstantValue(PMC_CONSTANT_ONE);
            root.HookNumber(uint_one);

            PMC_HANDLE_SINT sint_zero = ep_sint.GetConstantValue(PMC_CONSTANT_ZERO);
            root.HookNumber(sint_zero);
            PMC_HANDLE_SINT sint_one = ep_sint.GetConstantValue(PMC_CONSTANT_ONE);
            root.HookNumber(sint_one);
            PMC_HANDLE_SINT sint_minus_one = ep_sint.GetConstantValue(PMC_CONSTANT_MINUS_ONE);
            root.HookNumber(sint_minus_one);

            root.AttatchStaticNumber(&number_object_rtnl_zero, sint_zero, uint_one);
            root.AttatchStaticNumber(&number_object_rtnl_one, sint_one, uint_one);
            root.AttatchStaticNumber(&number_object_rtnl_minus_one, sint_minus_one, uint_one);

            number_handle_sint_one = sint_one;
            number_handle_sint_minus_one = sint_minus_one;
            number_handle_sint_zero = sint_zero;

            number_handle_uint_one = uint_one;
            number_handle_uint_zero = uint_zero;

            root.UnlinkNumber(uint_zero);
            root.UnlinkNumber(uint_one);
            root.UnlinkNumber(sint_zero);
            root.UnlinkNumber(sint_one);
            root.UnlinkNumber(sint_minus_one);
            root.UnlinkStatickNumber(&number_object_rtnl_zero);
            root.UnlinkStatickNumber(&number_object_rtnl_one);
            root.UnlinkStatickNumber(&number_object_rtnl_minus_one);

            return (PMC_STATUS_OK);
        }
        catch (const Exception& ex)
        {
            return (ex.GetStatusCode());
        }

    }

    void* __AllocateHeap(size_t size) noexcept(false)
    {
        void* buffer = HeapAlloc(hLocalHeap, HEAP_ZERO_MEMORY, size);
        if (buffer == nullptr)
            throw NotEnoughMemoryException(L"ヒープメモリ領域が不足しています。");
        return (buffer);
    }

    void __DeallocateHeap(void* buffer) noexcept(true)
    {
        HeapFree(hLocalHeap, 0, buffer);
    }

    bool __AllocateRTNLHeapArea() noexcept(true)
    {
        hLocalHeap = HeapCreate(0, 0x1000, 0);
        if (hLocalHeap == nullptr)
            return (FALSE);
        return (TRUE);
    }

    void __DeallocateRTNLHeapArea() noexcept(true)
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