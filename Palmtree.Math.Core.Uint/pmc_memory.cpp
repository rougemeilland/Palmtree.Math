﻿/*
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
#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_lock.h"
#include "pmc_threadcontext.h"
#include "pmc_sfmt.h"
#include "pmc_inline_func.h"

#pragma region プラットフォーム固有の定義
#define CHECK_CODE_INIT     ((__UNIT_TYPE)0x8484848484848484)
#define	DEFAULT_MEMORY_DATA ((__UNIT_TYPE)0xcccccccccccccccc)
#pragma endregion
namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
#ifdef USE_WIN32_HEAP
    HANDLE hLocalHeap;
#endif
    NUMBER_OBJECT_UINT number_object_uint_zero;
    NUMBER_OBJECT_UINT number_object_uint_one;
    NUMBER_OBJECT_UINT number_object_uint_ten;
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
    __UNIT_TYPE* __AllocateBlock(ThreadContext& tc, size_t word_count, __UNIT_TYPE* code)
    {
        if (
            // 実際に獲得されるメモリのバイト数が MAX_USER_MEMORY_SIZE を超えないためのチェック
            word_count > MAX_USER_MEMORY_SIZE / __UNIT_TYPE_BYTE_COUNT ||
            // word_count が大きすぎて 'UNIT_BIT_COUNT' がオーバーフローしないためのチェック
            word_count > (__UNIT_TYPE)-1 / __UNIT_TYPE_BIT_COUNT
            )
            throw NotEnoughMemoryException(L"数値が大きすぎるために数値を格納するメモリが獲得できませんでした。");
#ifdef _DEBUG
        // 実際に獲得されるメモリ領域は「引数で渡されたワード数+2」のワード数となる。
        // 最初のワードには獲得時に引数で渡されたワード数が格納される。
        // 最後のワードには格納されている内容の正当性確認のための値が格納される。
        // 2番目のワードへのポインタは呼び出し元に通知され利用される。
        __UNIT_TYPE words2 = word_count + 2;
#ifdef USE_WIN32_HEAP
        __UNIT_TYPE* buffer = (__UNIT_TYPE*)__AllocateHeap(words2 * __UNIT_TYPE_BYTE_COUNT);
#else
        __UNIT_TYPE* buffer = new __UNIT_TYPE[words2];
        _FILL_MEMORY_UNIT(buffer, DEFAULT_MEMORY_DATA, words2);
#endif
        tc.IncrementTypeAAllocationCount();
        buffer[0] = word_count;

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
        buffer[word_count + 1] = check_code;
        *code = check_code;

        return (&buffer[1]);
#else
#ifdef USE_WIN32_HEAP
        __UNIT_TYPE* buffer = (__UNIT_TYPE*)__AllocateHeap(word_count * __UNIT_TYPE_BYTE_COUNT);
#else
        __UNIT_TYPE* buffer = new __UNIT_TYPE[word_count];
#endif
        tc.IncrementTypeAAllocationCount();
        *code = 0;
        return (&buffer[0]);
#endif
    }


    // AllocateBlock によって獲得されたメモリ領域が解放される。
    void __DeallocateBlock(ThreadContext& tc, __UNIT_TYPE* buffer, __UNIT_TYPE buffer_words, __UNIT_TYPE check_code)
    {
        if (buffer == nullptr)
            return;
#ifdef _DEBUG
        __UNIT_TYPE* p = buffer - 1;
        if (*p != buffer_words)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;DeallocateBlock;1");
        if (p[buffer_words+1] != check_code)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;DeallocateBlock;2");
        // 使用済みのバッファを既定のデータで塗りつぶす。
        _FILL_MEMORY_UNIT(p, DEFAULT_MEMORY_DATA, buffer_words + 2);
#else
        __UNIT_TYPE* p = buffer;
#endif
        // バッファを解放する。
#ifdef USE_WIN32_HEAP
        __DeallocateHeap(p);
#else
        delete[] p;
#endif
        tc.DecrementTypeAAllocationCount();
    }

    void __CheckBlock(__UNIT_TYPE* buffer, __UNIT_TYPE count, __UNIT_TYPE code)
    {
        if (buffer == nullptr)
            return;
#ifdef _DEBUG
        --buffer;
        __UNIT_TYPE words = buffer[0];
        if (words != count)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckBlockLight;1");
        __UNIT_TYPE code_actual = buffer[words + 1];
        __UNIT_TYPE code_desired = code;
        if (code_desired != code_actual)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckBlockLight;2");
#endif
    }

    __inline static void ClearNumberHeader(NUMBER_OBJECT_UINT* p)
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

    __inline static void FillNumberHeader(NUMBER_OBJECT_UINT* p)
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

    static void InitializeNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p, __UNIT_TYPE word_count)
    {
        if (word_count > 0)
        {
            __UNIT_TYPE check_code;
            __UNIT_TYPE* block = __AllocateBlock(tc, word_count, &check_code);
            ClearNumberHeader(p);
            p->SIGNATURE1 = PMC_SIGNATURE;
            p->SIGNATURE2 = PMC_UINT_SIGNATURE;
            p->UNIT_BIT_COUNT = word_count * __UNIT_TYPE_BIT_COUNT;
            p->UNIT_WORD_COUNT = 0;
            p->BLOCK_COUNT = word_count;
            p->BLOCK = block;
            p->BLOCK_CHECK_CODE = check_code;
            p->IS_COMMITTED = false;
        }
        else
        {
            // word_count に 0 が与えられるのは、数値が 0 の場合。
            ClearNumberHeader(p);
            p->SIGNATURE1 = PMC_SIGNATURE;
            p->SIGNATURE2 = PMC_UINT_SIGNATURE;
            p->UNIT_BIT_COUNT = 0;
            p->UNIT_WORD_COUNT = 0;
            p->BLOCK_COUNT = 0;
            p->BLOCK = nullptr;
            p->BLOCK_CHECK_CODE = 0;
            p->IS_COMMITTED = false;
        }
    }

    static void CleanUpNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p)
    {
        if (p->BLOCK != nullptr)
        {
            __UNIT_TYPE* block = p->BLOCK;
            __UNIT_TYPE block_count = p->BLOCK_COUNT;
            __UNIT_TYPE block_check_code = p->BLOCK_CHECK_CODE;
            p->BLOCK = nullptr;
            __DeallocateBlock(tc, block, block_count, block_check_code);        }
    }

    void __AttatchNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p, __UNIT_TYPE word_count)
    {
        InitializeNumber(tc, p, word_count);
        p->IS_SHARED = true;
    }

    NUMBER_OBJECT_UINT* __AllocateNumber(ThreadContext& tc, __UNIT_TYPE word_count)
    {
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* p = (NUMBER_OBJECT_UINT*)root.AllocateUBigIntNumberObjectStructure();
        InitializeNumber(tc, p, word_count);
        p->IS_SHARED = false;
        root.UnlinkUBigIntNumberObjectStructure(p);
        return (p);
    }

    void __DetatchNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p)
    {
        if (p != nullptr && p->IS_SHARED)
            CleanUpNumber(tc, p);
    }

    void __DeallocateNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p)
    {
        Lock lock_obj;
        if (p == nullptr || p->IS_SHARED)
            return;
        CleanUpNumber(tc, p);
        FillNumberHeader(p);
#ifdef USE_WIN32_HEAP
        __DeallocateHeap(p);
#else
        delete p;
#endif
        tc.DecrementTypeAAllocationCount();
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

    RANDOM_STATE_OBJECT* __AllocateRandomStateObjectFromUInt32(ThreadContext& tc, _UINT32_T seed)
    {
        ResourceHolderUINT root(tc);
        RANDOM_STATE_OBJECT* p = (RANDOM_STATE_OBJECT*)root.AllocateRandomStateObjectStructure();
        p->SIGNATURE1 = PMC_SIGNATURE;
        p->SIGNATURE2 = PMC_SFMT_SIGNATURE;
        p->STATE = root.AllocateInternalRandomStateObject(seed);
        root.UnlinkRandomStateObject(p);
        return (p);
    }

    RANDOM_STATE_OBJECT* __AllocateRandomStateObjectFromUInt32Array(ThreadContext& tc, _UINT32_T* init_key, _INT32_T key_length)
    {
        ResourceHolderUINT root(tc);
        RANDOM_STATE_OBJECT* p = (RANDOM_STATE_OBJECT*)root.AllocateRandomStateObjectStructure();
        p->SIGNATURE1 = PMC_SIGNATURE;
        p->SIGNATURE2 = PMC_SFMT_SIGNATURE;
        p->STATE = root.AllocateInternalRandomStateObject(init_key, key_length);
        root.UnlinkRandomStateObject(p);
        return (p);
    }

    void __DeallocateRandomStateObject(ThreadContext& tc, RANDOM_STATE_OBJECT* p)
    {
        if (p->STATE != nullptr)
        {
            PMCSFMT_DeallocateRandomState(p->STATE);
            tc.DecrementTypeAAllocationCount();
        }
        delete p;
        tc.DecrementTypeAAllocationCount();
    }

    void CommitNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p) noexcept(false)
    {
        if (p->IS_COMMITTED)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;CommitNumber;1");
        p->UNIT_BIT_COUNT = GetEffectiveBitLength(p->BLOCK, p->BLOCK_COUNT, &p->UNIT_WORD_COUNT);
        if (p->UNIT_BIT_COUNT <= 0)
        {
            if (p->BLOCK != nullptr)
            {
                __DeallocateBlock(tc, p->BLOCK, p->BLOCK_COUNT, p->BLOCK_CHECK_CODE);
                p->BLOCK = nullptr;
                p->BLOCK_COUNT = 0;
                p->BLOCK_CHECK_CODE = 0;
            }
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

    void __CheckNumber(NUMBER_OBJECT_UINT* p) noexcept(false)
    {
        if (p->SIGNATURE1 != PMC_SIGNATURE || p->SIGNATURE2 != PMC_UINT_SIGNATURE)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;1");
        if (p->BLOCK != nullptr)
            __CheckBlock(p->BLOCK, p->BLOCK_COUNT, p->BLOCK_CHECK_CODE);
        if (p->IS_COMMITTED)
        {
            if (p->IS_ZERO && !p->IS_SHARED)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_memory.cpp;CheckNumber;1");
            if (!p->IS_ZERO)
            {
#ifdef _DEBUG
                __UNIT_TYPE actual_hash_code = CalculateHashCode(p->BLOCK, p->UNIT_WORD_COUNT);
                __UNIT_TYPE desired_hash_code = p->HASH_CODE;
                if (actual_hash_code != desired_hash_code)
                    throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;2");
#endif
            }
        }
    }

    void __CheckNumber(RANDOM_STATE_OBJECT* p) noexcept(false)
    {
        if (p->SIGNATURE1 != PMC_SIGNATURE || p->SIGNATURE2 != PMC_SFMT_SIGNATURE)
            throw BadBufferException(L"メモリ領域の不整合を検出しました。", L"pmc_memory.cpp;CheckNumber;1");
    }

    NUMBER_OBJECT_UINT* DuplicateNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* x)
    {
        if (x->IS_SHARED)
            return (x);
        if (x->IS_ZERO)
            return (&number_object_uint_zero);
        __UNIT_TYPE x_word_count = x->UNIT_WORD_COUNT;
        NUMBER_OBJECT_UINT* o = __AllocateNumber(tc, x_word_count);
        _COPY_MEMORY_UNIT(o->BLOCK, x->BLOCK, o->BLOCK_COUNT);
        CommitNumber(tc, o);
        return (o);
    }

    PMC_HANDLE_UINT PMC_GetConstantValue_UI(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        switch (type)
        {
        case PMC_CONSTANT_ZERO:
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        case PMC_CONSTANT_ONE:
            return (GET_NUMBER_HANDLE(&number_object_uint_one));
        case PMC_CONSTANT_TEN:
            return (GET_NUMBER_HANDLE(&number_object_uint_ten));
        default:
            throw ArgumentException(L"引数typeが未知の値です。");
        }
    }

    PMC_HANDLE_SFMT PMC_AllocateRandomStateObjectFromUInt32(ThreadContext & tc, _UINT32_T seed)
    {
        ResourceHolderUINT root(tc);

        RANDOM_STATE_OBJECT* nstate = root.AllocateRandomStateObject(seed);
        PMC_HANDLE_SFMT state = GET_STATE_HANDLE(nstate);
        root.UnlinkRandomStateObject(nstate);
        return (state);
    }

    PMC_HANDLE_SFMT PMC_AllocateRandomStateObjectFromUInt32Array(ThreadContext& tc, _UINT32_T* init_key, _INT32_T key_length)
    {
        ResourceHolderUINT root(tc);

        RANDOM_STATE_OBJECT* nstate = root.AllocateRandomStateObject(init_key, key_length);
        PMC_HANDLE_SFMT state = GET_STATE_HANDLE(nstate);
        root.UnlinkRandomStateObject(nstate);
        return (state);
    }

    void PMC_CheckHandle_UX(PMC_HANDLE_UINT p)
    {
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        __CheckNumber(np);
    }

    void PMC_CheckHandle_SFMT(PMC_HANDLE_SFMT p)
    {
        RANDOM_STATE_OBJECT* np = GET_STATE_OBJECT(p, L"p");
        __CheckNumber(np);
    }

    void PMC_Dispose_UX(ThreadContext& tc, PMC_HANDLE_UINT p)
    {
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        __DeallocateNumber(tc, np);
    }

    void PMC_Dispose_SFMT(ThreadContext& tc, PMC_HANDLE_SFMT p)
    {
        RANDOM_STATE_OBJECT* np = GET_STATE_OBJECT(p, L"p");
        __DeallocateRandomStateObject(tc, np);
    }

    PMC_HANDLE_UINT PMC_Clone_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* no;
        if (nx->IS_ZERO)
            no = &number_object_uint_zero;
        else
            no = DuplicateNumber(tc, nx);
        root.HookNumber(no);
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    _INT32_T PMC_GetBufferCount_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->IS_SHARED)
            return (0);
        return (1 + (np->BLOCK != nullptr ? 1 : 0));
    }

    _INT32_T PMC_GetBufferCount_SFMT(PMC_HANDLE_SFMT p) noexcept(false)
    {
        RANDOM_STATE_OBJECT* np = GET_STATE_OBJECT(p, L"p");
        return (1 + (np->STATE != nullptr ? 1 : 0));
    }
#pragma endregion

    PMC_STATUS_CODE Initialize_Memory(PROCESSOR_FEATURES* feature)
    {
        ThreadContext tc;

        InitializeCriticalSection(&mcs);

        ResourceHolderUINT root(tc);

        try
        {
            root.AttatchStaticNumber(&number_object_uint_zero, 0);
            CommitNumber(tc, &number_object_uint_zero);

            root.AttatchStaticNumber(&number_object_uint_one, 1);
            number_object_uint_one.BLOCK[0] = 1;
            CommitNumber(tc, &number_object_uint_one);

            root.AttatchStaticNumber(&number_object_uint_ten, 1);
            number_object_uint_ten.BLOCK[0] = 10;
            CommitNumber(tc, &number_object_uint_ten);

            root.UnlinkStatickNumber(&number_object_uint_zero);
            root.UnlinkStatickNumber(&number_object_uint_one);
            root.UnlinkStatickNumber(&number_object_uint_ten);

            return (PMC_STATUS_OK);
        }
        catch (const BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    void __GlobalLock(void) noexcept (true)
    {
        EnterCriticalSection(&mcs);
    }

    void __GlobalUnlock(void) noexcept (true)
    {
        LeaveCriticalSection(&mcs);
    }

#ifdef USE_WIN32_HEAP
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

    bool __AllocateUINTHeapArea() noexcept(true)
    {
        hLocalHeap = HeapCreate(0, 0x1000, 0);
        if (hLocalHeap == nullptr)
            return (FALSE);
        return (TRUE);
    }

    void __DeallocateUINTHeapArea() noexcept(true)
    {
        if (hLocalHeap != nullptr)
        {
            HeapDestroy(hLocalHeap);
            hLocalHeap = nullptr;
        }
    }
#endif

}

/*
 * END OF FILE
 */