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

#pragma once

#ifndef PMC_SFMT_H
#define PMC_SFMT_H
namespace Palmtree::Math::Core::Internal
{

#ifdef PALMTREEMATHCORESFMT_EXPORTS
#define __DLLEXPORT_SFMT __declspec(dllexport)
#else
#define __DLLEXPORT_SFMT __declspec(dllimport)
#endif

    extern "C" __DLLEXPORT_SFMT void* PMCSFMT_AllocateRandomStateFromUInt32(unsigned int seed);
    extern "C" __DLLEXPORT_SFMT void* PMCSFMT_AllocateRandomStateFromUInt32Array(unsigned int* init_key, unsigned int key_length);
    extern "C" __DLLEXPORT_SFMT void PMCSFMT_DeallocateRandomState(void* state);
    extern "C" __DLLEXPORT_SFMT unsigned int PMCSFMT_GenerateUInt32RandomValue(void* state);
    extern "C" __DLLEXPORT_SFMT unsigned long long PMCSFMT_GenerateUInt64RandomValue(void* state);
    extern "C" __DLLEXPORT_SFMT double PMCSFMT_GenerateDoubleRandomValue(void* state);
}

#endif


/*
 * END OF FILE
 */