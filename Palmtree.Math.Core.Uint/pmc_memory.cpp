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
#include "pmc_resourceholder_uint.h"
#include "pmc_exception.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"

//#define _LOG_MEMORY

#pragma region プラットフォーム固有の定義
#ifdef _M_IX86
#define	CHECK_CODE_INIT     (0x84848484)
#define	DEFAULT_MEMORY_DATA (0xcccccccc)
#elif defined(_M_X64)
#define CHECK_CODE_INIT     (0x8484848484848484)
#define	DEFAULT_MEMORY_DATA (0xcccccccccccccccc)
#else
#error unknown platform
#endif
#pragma endregion

namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
    HANDLE hLocalHeap;
    NUMBER_HEADER number_zero;
    NUMBER_HEADER number_one;
    CRITICAL_SECTION mcs;
#pragma endregion


#pragma region インライン関数の定義
    static __UNIT_TYPE CalculateHashCode(__UNIT_TYPE* p, __UNIT_TYPE words) noexcept(true)
    {
        __UNIT_TYPE code = CHECK_CODE_INIT;

        __UNIT_TYPE count = words >> 5;
        while (count != 0)
        {
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];
            code = _ROTATE_L_UNIT(code, 3) ^ p[1];
            code = _ROTATE_L_UNIT(code, 3) ^ p[2];
            code = _ROTATE_L_UNIT(code, 3) ^ p[3];
            code = _ROTATE_L_UNIT(code, 3) ^ p[4];
            code = _ROTATE_L_UNIT(code, 3) ^ p[5];
            code = _ROTATE_L_UNIT(code, 3) ^ p[6];
            code = _ROTATE_L_UNIT(code, 3) ^ p[7];
            code = _ROTATE_L_UNIT(code, 3) ^ p[8];
            code = _ROTATE_L_UNIT(code, 3) ^ p[9];
            code = _ROTATE_L_UNIT(code, 3) ^ p[10];
            code = _ROTATE_L_UNIT(code, 3) ^ p[11];
            code = _ROTATE_L_UNIT(code, 3) ^ p[12];
            code = _ROTATE_L_UNIT(code, 3) ^ p[13];
            code = _ROTATE_L_UNIT(code, 3) ^ p[14];
            code = _ROTATE_L_UNIT(code, 3) ^ p[15];
            code = _ROTATE_L_UNIT(code, 3) ^ p[16];
            code = _ROTATE_L_UNIT(code, 3) ^ p[17];
            code = _ROTATE_L_UNIT(code, 3) ^ p[18];
            code = _ROTATE_L_UNIT(code, 3) ^ p[19];
            code = _ROTATE_L_UNIT(code, 3) ^ p[20];
            code = _ROTATE_L_UNIT(code, 3) ^ p[21];
            code = _ROTATE_L_UNIT(code, 3) ^ p[22];
            code = _ROTATE_L_UNIT(code, 3) ^ p[23];
            code = _ROTATE_L_UNIT(code, 3) ^ p[24];
            code = _ROTATE_L_UNIT(code, 3) ^ p[25];
            code = _ROTATE_L_UNIT(code, 3) ^ p[26];
            code = _ROTATE_L_UNIT(code, 3) ^ p[27];
            code = _ROTATE_L_UNIT(code, 3) ^ p[28];
            code = _ROTATE_L_UNIT(code, 3) ^ p[29];
            code = _ROTATE_L_UNIT(code, 3) ^ p[30];
            code = _ROTATE_L_UNIT(code, 3) ^ p[31];
            p += 32;
            --count;
        }

        if (words & 0x10)
        {
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];
            code = _ROTATE_L_UNIT(code, 3) ^ p[1];
            code = _ROTATE_L_UNIT(code, 3) ^ p[2];
            code = _ROTATE_L_UNIT(code, 3) ^ p[3];
            code = _ROTATE_L_UNIT(code, 3) ^ p[4];
            code = _ROTATE_L_UNIT(code, 3) ^ p[5];
            code = _ROTATE_L_UNIT(code, 3) ^ p[6];
            code = _ROTATE_L_UNIT(code, 3) ^ p[7];
            code = _ROTATE_L_UNIT(code, 3) ^ p[8];
            code = _ROTATE_L_UNIT(code, 3) ^ p[9];
            code = _ROTATE_L_UNIT(code, 3) ^ p[10];
            code = _ROTATE_L_UNIT(code, 3) ^ p[11];
            code = _ROTATE_L_UNIT(code, 3) ^ p[12];
            code = _ROTATE_L_UNIT(code, 3) ^ p[13];
            code = _ROTATE_L_UNIT(code, 3) ^ p[14];
            code = _ROTATE_L_UNIT(code, 3) ^ p[15];
            p += 16;
        }

        if (words & 0x8)
        {
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];
            code = _ROTATE_L_UNIT(code, 3) ^ p[1];
            code = _ROTATE_L_UNIT(code, 3) ^ p[2];
            code = _ROTATE_L_UNIT(code, 3) ^ p[3];
            code = _ROTATE_L_UNIT(code, 3) ^ p[4];
            code = _ROTATE_L_UNIT(code, 3) ^ p[5];
            code = _ROTATE_L_UNIT(code, 3) ^ p[6];
            code = _ROTATE_L_UNIT(code, 3) ^ p[7];
            p += 8;
        }

        if (words & 0x4)
        {
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];
            code = _ROTATE_L_UNIT(code, 3) ^ p[1];
            code = _ROTATE_L_UNIT(code, 3) ^ p[2];
            code = _ROTATE_L_UNIT(code, 3) ^ p[3];
            p += 4;
        }

        if (words & 0x2)
        {
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];
            code = _ROTATE_L_UNIT(code, 3) ^ p[1];
            p += 2;
        }

        if (words & 0x1)
            code = _ROTATE_L_UNIT(code, 3) ^ p[0];

        return (code);
    }
#pragma endregion


#pragma region __UNIT_TYPEの配列としてメモリを獲得する関数
    // 多倍長整数をバイト列として格納するためのメモリ領域を獲得する。
    // 引数には格納可能な多倍長整数の合計ワード数が渡される。
    static __UNIT_TYPE* AllocateBlock(size_t bits, __UNIT_TYPE* allocated_block_words, __UNIT_TYPE* code)
    {
        // 実際に獲得されるメモリ領域は「引数で渡されたワード数+2」のワード数となる。
        // 最初のワードには獲得時に引数で渡されたワード数が格納される。
        // 最後のワードには格納されている内容の正当性確認のための値が格納される。
        // 2番目のワードへのポインタは呼び出し元に通知され利用される。
        __UNIT_TYPE words1 = _DIVIDE_CEILING_UNIT(bits, __UNIT_TYPE_BIT_COUNT);
        __UNIT_TYPE words2 = words1 + 2;
        __UNIT_TYPE bytes = words2 * __UNIT_TYPE_BYTE_COUNT;
        __UNIT_TYPE* buffer = (__UNIT_TYPE*)HeapAlloc(hLocalHeap, HEAP_ZERO_MEMORY, bytes);
        if (buffer == nullptr)
            throw NotEnoughMemoryException(L"ヒープメモリ領域が不足しています。");
#ifdef _LOG_MEMORY
        {
            wprintf(L"0x%08lx: new block 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)buffer);
        }
#endif
        buffer[0] = words1;
        *allocated_block_words = words1;
#ifdef _DEBUG
        // 乱数もどきを生成する。
#ifdef _M_IX86
        __UNIT_TYPE r = GetTickCount();
#elif defined(_M_X64)
#ifdef _MSC_VER
        __UNIT_TYPE r = GetTickCount64();
#elif defined(__GNUC__)
        _UINT32_T temp = GetTickCount();
        __UNIT_TYPE r = _FROMWORDTODWORD(temp, temp);
#else
#error unknown compiler
#endif
#else
#error unknown platform
#endif
        __UNIT_TYPE check_code = CHECK_CODE_INIT | r;
#else
        __UNIT_TYPE check_code = 0;
#endif
        buffer[words1 + 1] = check_code;
        *code = check_code;
        return (&buffer[1]);
    }


    // AllocateBlock によって獲得されたメモリ領域が解放される。
    static void DeallocateBlock(__UNIT_TYPE* buffer, __UNIT_TYPE buffer_words, __UNIT_TYPE check_code)
    {
        if (buffer == nullptr)
            return;
        __UNIT_TYPE* p = buffer - 1;
#ifdef _DEBUG
        if (*p != buffer_words)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;DeallocateBlock;1");
        if (p[buffer_words+1] != check_code)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;DeallocateBlock;2");
#endif
        // 使用済みのバッファを既定のデータで塗りつぶす。
        _FILL_MEMORY_UNIT(p, DEFAULT_MEMORY_DATA, buffer_words + 2);
        // バッファを解放する。
        HeapFree(hLocalHeap, 0, p);
#ifdef _LOG_MEMORY
        {
            wprintf(L"0x%08lx: delete block 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)p);
        }
#endif
    }

    // メモリ内容が正当かどうかが比較される。正当であれば復帰値として0が通知され、正当ではないのなら0以外が通知される。
    static void CheckBlock(__UNIT_TYPE* buffer, __UNIT_TYPE count, __UNIT_TYPE code)
    {
//#ifdef _DEBUG
        if (buffer == nullptr)
            return;
        --buffer;
        __UNIT_TYPE words = buffer[0];
        if (words != count)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckBlockLight;1");
        __UNIT_TYPE code_actual = buffer[words + 1];
        __UNIT_TYPE code_desired = code;
        if (code_desired != code_actual)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckBlockLight;2");
//#else
//        return;
//#endif
    }

    __inline static void ClearNumberHeader(NUMBER_HEADER* p)
    {
#ifdef _M_X64
        if (sizeof(*p) == sizeof(_UINT64_T) * 10)
        {
            _UINT64_T* __p = (_UINT64_T*)p;
            __p[0] = 0;
            __p[1] = 0;
            __p[2] = 0;
            __p[3] = 0;
            __p[4] = 0;
            __p[5] = 0;
            __p[6] = 0;
            __p[7] = 0;
            __p[8] = 0;
            __p[9] = 0;
        }
        else
        {
#endif
            if (sizeof(*p) == sizeof(_UINT32_T) * 11)
            {
                _UINT32_T* __p = (_UINT32_T*)p;
                __p[0] = 0;
                __p[1] = 0;
                __p[2] = 0;
                __p[3] = 0;
                __p[4] = 0;
                __p[5] = 0;
                __p[6] = 0;
                __p[7] = 0;
                __p[8] = 0;
                __p[9] = 0;
                __p[10] = 0;
            }
#ifdef _M_X64
            else if (sizeof(*p) % sizeof(_UINT64_T) == 0)
                _ZERO_MEMORY_64((_UINT64_T*)p, sizeof(*p) / sizeof(_UINT64_T));
#endif
            else if (sizeof(*p) % sizeof(_UINT32_T) == 0)
                _ZERO_MEMORY_32((_UINT32_T*)p, sizeof(*p) / sizeof(_UINT32_T));
            else if (sizeof(*p) % sizeof(_UINT16_T) == 0)
                _ZERO_MEMORY_16((_UINT16_T*)p, sizeof(*p) / sizeof(_UINT16_T));
            else
                _ZERO_MEMORY_BYTE(p, sizeof(*p));
#ifdef _M_X64
        }
#endif
    }

    __inline static void FillNumberHeader(NUMBER_HEADER* p)
    {
#ifdef _M_X64
        if (sizeof(*p) == sizeof(_UINT64_T) * 10)
        {
            _UINT64_T* __p = (_UINT64_T*)p;
            __p[0] = DEFAULT_MEMORY_DATA;
            __p[1] = DEFAULT_MEMORY_DATA;
            __p[2] = DEFAULT_MEMORY_DATA;
            __p[3] = DEFAULT_MEMORY_DATA;
            __p[4] = DEFAULT_MEMORY_DATA;
            __p[5] = DEFAULT_MEMORY_DATA;
            __p[6] = DEFAULT_MEMORY_DATA;
            __p[7] = DEFAULT_MEMORY_DATA;
            __p[8] = DEFAULT_MEMORY_DATA;
            __p[9] = DEFAULT_MEMORY_DATA;
        }
        else
        {
#endif
            if (sizeof(*p) == sizeof(_UINT32_T) * 11)
            {
                _UINT32_T* __p = (_UINT32_T*)p;
                __p[0] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[1] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[2] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[3] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[4] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[5] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[6] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[7] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[8] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[9] = (_UINT32_T)DEFAULT_MEMORY_DATA;
                __p[10] = (_UINT32_T)DEFAULT_MEMORY_DATA;
            }
#ifdef _M_X64
            else if (sizeof(*p) % sizeof(_UINT64_T) == 0)
                _FILL_MEMORY_64((_UINT64_T*)p, DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT64_T));
#endif
            else if (sizeof(*p) % sizeof(_UINT32_T) == 0)
                _FILL_MEMORY_32((_UINT32_T*)p, (_UINT32_T)DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT32_T));
            else if (sizeof(*p) % sizeof(_UINT16_T) == 0)
                _FILL_MEMORY_16((_UINT16_T*)p, (_UINT16_T)DEFAULT_MEMORY_DATA, sizeof(*p) / sizeof(_UINT16_T));
            else
                _FILL_MEMORY_BYTE(p, (unsigned char)DEFAULT_MEMORY_DATA, sizeof(*p));
#ifdef _M_X64
        }
#endif
    }

    static void InitializeNumber(NUMBER_HEADER* p, __UNIT_TYPE bit_count)
    {
        if (bit_count > 0)
        {
            __UNIT_TYPE word_count;
            __UNIT_TYPE check_code;
            __UNIT_TYPE* block = AllocateBlock(bit_count, &word_count, &check_code);
            ClearNumberHeader(p);
            p->SIGNATURE1 = PMC_SIGNATURE;
            p->SIGNATURE2 = PMC_UINT_SIGNATURE;
            p->UNIT_BIT_COUNT = bit_count;
            p->BLOCK_COUNT = word_count;
            p->BLOCK = block;
            p->BLOCK_CHECK_CODE = check_code;
            p->IS_COMMITTED = false;
#ifdef _LOG_MEMORY
            {
                wprintf(L"0x%08lx: link 0x%016llx->0x%016llx\n", GetCurrentThreadId(), (unsigned long long)p, (unsigned long long)(block - 1));
            }
#endif
        }
        else
        {
            // bit_count に 0 が与えられるのは、数値が 0 の場合。
            ClearNumberHeader(p);
            p->SIGNATURE1 = PMC_SIGNATURE;
            p->SIGNATURE2 = PMC_UINT_SIGNATURE;
            p->UNIT_BIT_COUNT = 0;
            p->BLOCK_COUNT = 0;
            p->BLOCK = nullptr;
            p->BLOCK_CHECK_CODE = 0;
            p->IS_COMMITTED = false;
        }
    }

    static void CleanUpNumber(NUMBER_HEADER* p)
    {
        if (p->BLOCK != nullptr)
        {
            __UNIT_TYPE* block = p->BLOCK;
            __UNIT_TYPE block_count = p->BLOCK_COUNT;
            __UNIT_TYPE block_check_code = p->BLOCK_CHECK_CODE;
            p->BLOCK = nullptr;
#ifdef _LOG_MEMORY
            {
                wprintf(L"0x%08lx: unlink 0x%016llx->0x%016llx\n", GetCurrentThreadId(), (unsigned long long)p, (unsigned long long)(block - 1));
            }
#endif
            DeallocateBlock(block, block_count, block_check_code);        }
    }

    static void AttatchNumber(NUMBER_HEADER* p, __UNIT_TYPE bit_count)
    {
        InitializeNumber(p, bit_count);
        p->IS_STATIC = true;
    }

    static NUMBER_HEADER* AllocateNumber(__UNIT_TYPE bit_count)
    {
        ResourceHolderUINT root;
        NUMBER_HEADER* p = (NUMBER_HEADER*)root.AllocateBytes(sizeof(NUMBER_HEADER));
        InitializeNumber(p, bit_count);
        p->IS_STATIC = false;
        root.UnlinkBytes((void*)p);
        return (p);
    }

    static void DetatchNumber(NUMBER_HEADER* p)
    {
        if (p != nullptr && p->IS_STATIC)
            CleanUpNumber(p);
    }

    static void DeallocateNumber(NUMBER_HEADER* p)
    {
        if (p != nullptr && !p->IS_STATIC)
        {
            CleanUpNumber(p);
            FillNumberHeader(p);
            HeapFree(hLocalHeap, 0, p);
#ifdef _LOG_MEMORY
            {
                wprintf(L"0x%08lx: delete header 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)p);
            }
#endif
        }
    }

    static __UNIT_TYPE GetEffectiveBitLength(__UNIT_TYPE* p, __UNIT_TYPE word_count, __UNIT_TYPE* effective_word_count)
    {
        if (p == nullptr)
        {
            *effective_word_count = 0;
            return (0);
        }
        p += word_count;
        while (word_count != 0)
        {
            --p;
            if (*p != 0)
            {
                *effective_word_count = word_count;
                return (word_count * __UNIT_TYPE_BIT_COUNT - _LZCNT_ALT_UNIT(*p));
            }
            --word_count;
        }
        *effective_word_count = 0;
        return (0);
    }

    static __UNIT_TYPE GetTrailingZeroBitCount(__UNIT_TYPE* p, __UNIT_TYPE word_count)
    {
        __UNIT_TYPE bit_count = 0;
        while (word_count > 0)
        {
            --word_count;
            if (*p != 0)
                return (bit_count + _TZCNT_ALT_UNIT(*p));
            bit_count += __UNIT_TYPE_BIT_COUNT;
            ++p;
        }
        // このルートには到達しないはず
        return (0);
    }

    void CommitNumber(NUMBER_HEADER* p) noexcept(true)
    {
        p->UNIT_BIT_COUNT = GetEffectiveBitLength(p->BLOCK, p->BLOCK_COUNT, &p->UNIT_WORD_COUNT);
        if (p->UNIT_BIT_COUNT <= 0)
        {
            p->HASH_CODE = 0;
            p->IS_ZERO = true;
            p->IS_ONE = false;
            p->IS_EVEN = true;
            p->TRAILING_ZERO_BITS_COUNT = 0;
            p->IS_POWER_OF_TWO = false;
            p->IS_COMMITTED = true;
        }
        else if (p->UNIT_BIT_COUNT == 1)
        {
            p->HASH_CODE = CalculateHashCode(p->BLOCK, p->UNIT_WORD_COUNT);
            p->IS_ZERO = false;
            p->IS_ONE = p->BLOCK[0] == 1; // 無条件でTRUEでも大丈夫だが念のため。
            p->IS_EVEN = !(p->BLOCK[0] & 1);
            p->TRAILING_ZERO_BITS_COUNT = 0;
            p->IS_POWER_OF_TWO = true;
            p->IS_COMMITTED = true;
        }
        else
        {
            p->HASH_CODE = CalculateHashCode(p->BLOCK, p->UNIT_WORD_COUNT);
            p->IS_ZERO = false;
            p->IS_ONE = false;
            p->IS_EVEN = !(p->BLOCK[0] & 1);
            p->TRAILING_ZERO_BITS_COUNT = GetTrailingZeroBitCount(p->BLOCK, p->UNIT_WORD_COUNT);
            p->IS_POWER_OF_TWO = p->TRAILING_ZERO_BITS_COUNT + 1 == p->UNIT_BIT_COUNT;
            p->IS_COMMITTED = true;
        }
    }

    void CheckNumber(NUMBER_HEADER* p) noexcept(false)
    {
        if (p->SIGNATURE1 != PMC_SIGNATURE || p->SIGNATURE2 != PMC_UINT_SIGNATURE)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;1");
        if (!p->IS_ZERO)
        {
            CheckBlock(p->BLOCK, p->BLOCK_COUNT, p->BLOCK_CHECK_CODE);
#ifdef _DEBUG
            if (p->IS_COMMITTED)
            {
                __UNIT_TYPE actual_hash_code = CalculateHashCode(p->BLOCK, p->UNIT_WORD_COUNT);
                __UNIT_TYPE desired_hash_code = p->HASH_CODE;
                if (actual_hash_code !=  desired_hash_code)
                    throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;2");
            }
#endif
        }
    }

    NUMBER_HEADER* DuplicateNumber(NUMBER_HEADER* x)
    {
        if (x->IS_STATIC)
            return (x);
        if (x->IS_ZERO)
            return (&number_zero);
        __UNIT_TYPE x_bit_count = x->UNIT_BIT_COUNT;
        NUMBER_HEADER* o = AllocateNumber(x_bit_count);
        _COPY_MEMORY_UNIT(o->BLOCK, x->BLOCK, o->BLOCK_COUNT);
        CommitNumber(o);
        return (o);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        switch (type)
        {
        case PMC_CONSTANT_ZERO:
            return ((PMC_HANDLE_UINT)&number_zero);
        case PMC_CONSTANT_ONE:
            return ((PMC_HANDLE_UINT)&number_one);
        default:
            throw ArgumentException(L"引数typeが未知の値です。");
        }
    }

    void __PMC_CALL PMC_Dispose(PMC_HANDLE_UINT p)
    {
        NUMBER_HEADER* np = (NUMBER_HEADER*)p;
        CheckNumber(np);
        DeallocateNumber(np);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Clone_X(PMC_HANDLE_UINT x) noexcept(false)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"x");
        NUMBER_HEADER* nx = (NUMBER_HEADER*)x;
        CheckNumber(nx);
        ResourceHolderUINT root;
        NUMBER_HEADER* no;
        if (nx->IS_ZERO)
            no = &number_zero;
        else
            no = DuplicateNumber(nx);
        root.HookNumber(no);
#ifdef _DEBUG
        CheckNumber(no);
#endif
        root.UnlinkNumber(no);
        return ((PMC_HANDLE_UINT)no);
    }

#pragma endregion

#pragma region チェーンされたメモリ管理
    Lock::Lock()
    {
        EnterCriticalSection(&mcs);
    }

    Lock::~Lock()
    {
        LeaveCriticalSection(&mcs);
    }

    ResourceHolderUINT::__GenericChainBufferTag::__GenericChainBufferTag(void * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderUINT::__GenericChainBufferTag::~__GenericChainBufferTag()
    {
    }

    BOOL ResourceHolderUINT::__GenericChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__GenericChainBufferTag::Destruct()
    {
        HeapFree(hLocalHeap, 0, _buffer);
#ifdef _LOG_MEMORY
        {
            wprintf(L"0x%08lx: delete header 0x%016llx\n", GetCurrentThreadId(), (unsigned long long)_buffer);
        }
#endif
    }

    ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::____UNIT_TYPE_Array_ChainBufferTag(__UNIT_TYPE * buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code)
    {
        _buffer = buffer;
        _word_count = word_count;
        _check_code = check_code;
    }

    ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::~____UNIT_TYPE_Array_ChainBufferTag()
    {
    }

    BOOL  ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::Clear()
    {
        _ZERO_MEMORY_UNIT(_buffer, _word_count);
    }

    void  ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::CheckBlock(_buffer, _word_count, _check_code);
    }

    void  ResourceHolderUINT::____UNIT_TYPE_Array_ChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::DeallocateBlock(_buffer, _word_count, _check_code);
    }

    ResourceHolderUINT::__StringChainBufferTag::__StringChainBufferTag(__UNIT_TYPE * buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code)
    {
        _buffer = buffer;
        _word_count = word_count;
        _check_code = check_code;
    }

    ResourceHolderUINT::__StringChainBufferTag::~__StringChainBufferTag()
    {
    }

    BOOL ResourceHolderUINT::__StringChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void ResourceHolderUINT::__StringChainBufferTag::Clear()
    {
        _ZERO_MEMORY_UNIT(_buffer, _word_count);
    }

    void ResourceHolderUINT::__StringChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::CheckBlock(_buffer, _word_count, _check_code);
    }

    void ResourceHolderUINT::__StringChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::DeallocateBlock(_buffer, _word_count, _check_code);
    }

    ResourceHolderUINT::__DynamicNumberChainBufferTag::__DynamicNumberChainBufferTag(NUMBER_HEADER * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderUINT::__DynamicNumberChainBufferTag::~__DynamicNumberChainBufferTag()
    {
    }

    BOOL  ResourceHolderUINT::__DynamicNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__DynamicNumberChainBufferTag::Check()
    {
        Palmtree::Math::Core::Internal::CheckNumber(_buffer);
    }

    void  ResourceHolderUINT::__DynamicNumberChainBufferTag::Destruct()
    {
        Palmtree::Math::Core::Internal::DeallocateNumber(_buffer);
    }

    ResourceHolderUINT::__NumberHandleHookingChainBufferTag::__NumberHandleHookingChainBufferTag(NUMBER_HEADER * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderUINT::__NumberHandleHookingChainBufferTag::~__NumberHandleHookingChainBufferTag()
    {
    }

    BOOL  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::Check()
    {
    }

    void  ResourceHolderUINT::__NumberHandleHookingChainBufferTag::Destruct()
    {
       Palmtree::Math::Core::Internal::DeallocateNumber(_buffer);
    }

    ResourceHolderUINT::__StaticNumberChainBufferTag::__StaticNumberChainBufferTag(NUMBER_HEADER * buffer)
    {
        _buffer = buffer;
    }

    ResourceHolderUINT::__StaticNumberChainBufferTag::~__StaticNumberChainBufferTag()
    {
    }

    BOOL  ResourceHolderUINT::__StaticNumberChainBufferTag::EqualsBufferAddress(void * buffer)
    {
        return ((void*)_buffer == buffer);
    }

    void  ResourceHolderUINT::__StaticNumberChainBufferTag::Check()
    {
    }

    void  ResourceHolderUINT::__StaticNumberChainBufferTag::Destruct()
    {
        DetatchNumber(_buffer);
    }

    ResourceHolderUINT::ResourceHolderUINT()
    {
    }

    ResourceHolderUINT::~ResourceHolderUINT()
    {
    }

    void* ResourceHolderUINT::AllocateBytes(size_t size)
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

    void ResourceHolderUINT::DeallocateBytes(void * buffer)
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

    void ResourceHolderUINT::UnlinkBytes(void *buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBytes;1");
        tag->Unlink();
    }

    __UNIT_TYPE * ResourceHolderUINT::AllocateBlock(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        __UNIT_TYPE word_count;
        __UNIT_TYPE check_code;
        __UNIT_TYPE* buffer = Palmtree::Math::Core::Internal::AllocateBlock(bit_count, &word_count, &check_code);
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
            tag->Unlink();
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
        tag->Unlink();
    }

    wchar_t * ResourceHolderUINT::AllocateString(__UNIT_TYPE count)
    {
        Lock lock_obj;
        __UNIT_TYPE word_count;
        __UNIT_TYPE check_code;
        __UNIT_TYPE* buffer = Palmtree::Math::Core::Internal::AllocateBlock(count * __UNIT_TYPE_BIT_COUNT, &word_count, &check_code);
        __ChainBufferTag* tag = new ____UNIT_TYPE_Array_ChainBufferTag(buffer, word_count, check_code);
        LinkTag(tag);
        return ((wchar_t*)buffer);
    }

    void ResourceHolderUINT::ClearString(wchar_t * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::ClearString;1");
        tag->Clear();
    }

    void ResourceHolderUINT::DeallocateString(wchar_t * buffer)
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

    void ResourceHolderUINT::CheckString(wchar_t * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckString;1");
        tag->Check();
#endif
    }

    void ResourceHolderUINT::UnlinkString(wchar_t * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkBlock;1");
        tag->Unlink();
    }

    NUMBER_HEADER * ResourceHolderUINT::AllocateNumber(__UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        NUMBER_HEADER* buffer = Palmtree::Math::Core::Internal::AllocateNumber(bit_count);
        __ChainBufferTag* tag = new __DynamicNumberChainBufferTag(buffer);
        LinkTag(tag);
        return (buffer);
    }

    void ResourceHolderUINT::HookNumber(NUMBER_HEADER * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = new __NumberHandleHookingChainBufferTag(buffer);
        LinkTag(tag);
    }

    void ResourceHolderUINT::DeallocateNumber(NUMBER_HEADER * buffer)
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

    void ResourceHolderUINT::CheckNumber(NUMBER_HEADER * buffer)
    {
#ifdef _DEBUG
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::CheckNumber;1");
        tag->Check();
#endif
    }

    void ResourceHolderUINT::UnlinkNumber(NUMBER_HEADER * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkNumber;1");
        tag->Unlink();
    }

    void ResourceHolderUINT::AttatchStaticNumber(NUMBER_HEADER* p, __UNIT_TYPE bit_count)
    {
        Lock lock_obj;
        Palmtree::Math::Core::Internal::AttatchNumber(p, bit_count);
        __ChainBufferTag* tag = new __StaticNumberChainBufferTag(p);
        LinkTag(tag);
    }

    void ResourceHolderUINT::DetatchStaticNumber(NUMBER_HEADER * buffer)
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

    void ResourceHolderUINT::UnlinkStatickNumber(NUMBER_HEADER * buffer)
    {
        Lock lock_obj;
        __ChainBufferTag* tag = FindTag(buffer);
        if (tag == nullptr)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;ResourceHolderUINT::UnlinkStatickNumber;1");
        tag->Unlink();
    }
#pragma endregion

#pragma region ヒープメモリ関連関数

    static BOOL GetAllocatedMemorySize_Imp(_UINT64_T* size)
    {
        *size = 0;
        DWORD LastError;
        PROCESS_HEAP_ENTRY Entry;
        Entry.lpData = NULL;
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

    _UINT64_T __PMC_CALL PMC_GetAllocatedMemorySize()
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

#pragma endregion

    PMC_STATUS_CODE Initialize_Memory(PROCESSOR_FEATURES* feature)
    {
        InitializeCriticalSection(&mcs);

        ResourceHolderUINT root;

        try
        {
            root.AttatchStaticNumber(&number_zero, 0);
            CommitNumber(&number_zero);

            root.AttatchStaticNumber(&number_one, 1);
            number_one.BLOCK[0] = 1;
            CommitNumber(&number_one);

            root.UnlinkStatickNumber(&number_zero);
            root.UnlinkStatickNumber(&number_one);
            return (PMC_STATUS_OK);
        }
        catch (const Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    BOOL AllocateHeapArea() noexcept(true)
    {
        hLocalHeap = HeapCreate(0, 0x1000, 0);
        if (hLocalHeap == nullptr)
            return (FALSE);
        return (TRUE);
    }

    void DeallocateHeapArea() noexcept(true)
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