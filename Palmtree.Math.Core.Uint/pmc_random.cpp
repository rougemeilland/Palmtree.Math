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

#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_sfmt.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    _UINT32_T PMC_GenerateUInt32RandomValue(PMC_HANDLE_SFMT handle)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        return (PMCSFMT_GenerateUInt32RandomValue(state->STATE));
    }

    _UINT64_T PMC_GenerateUInt64RandomValue(PMC_HANDLE_SFMT handle)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        return (PMCSFMT_GenerateUInt64RandomValue(state->STATE));
    }

    double PMC_GenerateDoubleRandomValue(PMC_HANDLE_SFMT handle)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        return (PMCSFMT_GenerateDoubleRandomValue(state->STATE));
    }

    PMC_HANDLE_UINT PMC_GenerateUBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        RANDOM_STATE_OBJECT* state = GET_STATE_OBJECT(handle, L"handle");
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderUINT root(tc);

        NUMBER_OBJECT_UINT* nr = root.AllocateNumber(bit_count);
        for (__UNIT_TYPE index = 0; index < nr->BLOCK_COUNT; ++index)
        {
#ifdef _M_IX86
            nr->BLOCK[index] = PMCSFMT_GenerateUInt32RandomValue(state->STATE);
#elif defined(_M_X64)
            nr->BLOCK[index] = PMCSFMT_GenerateUInt64RandomValue(state->STATE);
#else
#error unknown platform
#endif
        }
        if (nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT > (__UNIT_TYPE)bit_count)
        {
            int shift_count = (int)(__UNIT_TYPE_BIT_COUNT - nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT + bit_count);
            __UNIT_TYPE mask = (1UL << shift_count) - 1;
            nr->BLOCK[nr->BLOCK_COUNT - 1] &= mask;
        }
#ifdef _DEBUG
        root.CheckNumber(nr);
#endif
        CommitNumber(tc, nr);
        if (nr->IS_ZERO)
        {
            root.DeallocateNumber(nr);
            nr = &number_object_uint_zero;
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            return (r);
        }
        else
        {
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_GenerateUBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count)
    {
        if (bit_count <= 0)
            throw ArgumentOutOfRangeException(L"bit_count は正の整数である必要があります。");

        ResourceHolderUINT root(tc);

        NUMBER_OBJECT_UINT* nr = root.AllocateNumber(bit_count);
        size_t byte_count = (bit_count + 7) / 8;
        _COPY_MEMORY_BYTE(nr->BLOCK, data, byte_count);
        if (nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT > (__UNIT_TYPE)bit_count)
        {
            int shift_count = (int)(__UNIT_TYPE_BIT_COUNT - nr->BLOCK_COUNT*__UNIT_TYPE_BIT_COUNT + bit_count);
            __UNIT_TYPE mask = (1UL << shift_count) - 1;
            nr->BLOCK[nr->BLOCK_COUNT - 1] &= mask;
        }
#ifdef _DEBUG
        root.CheckNumber(nr);
#endif
        CommitNumber(tc, nr);
        if (nr->IS_ZERO)
        {
            root.DeallocateNumber(nr);
            nr = &number_object_uint_zero;
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            return (r);
        }
        else
        {
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
    }

}


/*
 * END OF FILE
 */