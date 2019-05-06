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

#include <stdlib.h>
#include <string.h>
#include "pmc_sfmt.h"
#include "SFMT.h"

namespace Palmtree::Math::Core::Internal
{

    extern "C" __DLLEXPORT_SFMT void* PMCSFMT_AllocateRandomStateFromUInt32(unsigned int seed)
    {
        void* state = malloc(sizeof(sfmt_t));
        if (state != NULL)
        {
            memset(state, 0, sizeof(sfmt_t));
            sfmt_init_gen_rand((sfmt_t*)state, seed);
        }
        return (state);
    }

    extern "C" __DLLEXPORT_SFMT void* PMCSFMT_AllocateRandomStateFromUInt32Array(unsigned int* init_key, unsigned int key_length)
    {
        void* state = malloc(sizeof(sfmt_t));
        if (state != NULL)
        {
            memset(state, 0, sizeof(sfmt_t));
            sfmt_init_by_array((sfmt_t*)state, init_key, key_length);
        }
        return (state);
    }

    extern "C" __DLLEXPORT_SFMT void PMCSFMT_DeallocateRandomState(void* state)
    {
        memset(state, 0xcc, sizeof(sfmt_t));
        free(state);
    }

    extern "C" __DLLEXPORT_SFMT unsigned int PMCSFMT_GenerateUInt32RandomValue(void* state)
    {
        // どうやら、同じ sfmt_t 構造体を使用して sfmt_genrand_uint32 と sfmt_genrand_uint64 を混在して呼び出すと Assert で落ちるらしいので、
        // 32bit 版では sfmt_genrand_uint32 のみ、64bit版では sfmt_genrand_uint64 のみを呼び出すようにする。
#ifdef _M_IX86
        return (sfmt_genrand_uint32((sfmt_t*)state));
#elif defined(_M_X64)
        return ((unsigned int)sfmt_genrand_uint64((sfmt_t*)state));
#endif
    }

    extern "C" __DLLEXPORT_SFMT unsigned long long PMCSFMT_GenerateUInt64RandomValue(void* state)
    {
#ifdef _M_IX86
        unsigned int v_lo = sfmt_genrand_uint32((sfmt_t*)state);
        unsigned int v_hi = sfmt_genrand_uint32((sfmt_t*)state);
        return (((unsigned long long)v_hi << 32) | v_lo);
#elif defined(_M_X64)
        return (sfmt_genrand_uint64((sfmt_t*)state));
#endif
    }

    extern "C" __DLLEXPORT_SFMT double PMCSFMT_GenerateDoubleRandomValue(void* state)
    {
#ifdef _M_IX86
        unsigned int v1 = sfmt_genrand_uint32((sfmt_t*)state);
        unsigned int v2 = sfmt_genrand_uint32((sfmt_t*)state);
        return (sfmt_to_res53_mix(v1, v2));
#elif defined(_M_X64)
        unsigned long long v = sfmt_genrand_uint64((sfmt_t*)state);
        return (sfmt_to_res53(v));
#else
#error unknown platform
#endif
    }

}


/*
 * END OF FILE
 */