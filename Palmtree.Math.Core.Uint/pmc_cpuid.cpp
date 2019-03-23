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


#include <intrin.h>
#include <immintrin.h>
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    __inline static void cpuid(_UINT32_T op, _UINT32_T* reg_eax, _UINT32_T* reg_ebx, _UINT32_T* reg_ecx, _UINT32_T* reg_edx)
    {
        _INT32_T regbuf[4];
        __cpuid(regbuf, op);
        *reg_eax = regbuf[0];
        *reg_ebx = regbuf[1];
        *reg_ecx = regbuf[2];
        *reg_edx = regbuf[3];
    }

    __inline static void cpuidex(_UINT32_T op, _UINT32_T subop, _UINT32_T* reg_eax, _UINT32_T* reg_ebx, _UINT32_T* reg_ecx, _UINT32_T* reg_edx)
    {
        _INT32_T regbuf[4];
        __cpuidex(regbuf, op, subop);
        *reg_eax = regbuf[0];
        *reg_ebx = regbuf[1];
        *reg_ecx = regbuf[2];
        *reg_edx = regbuf[3];
    }

    void GetCPUInfo(PROCESSOR_FEATURES* feature)
    {
        _UINT32_T reg_eax;
        _UINT32_T reg_ebx;
        _UINT32_T reg_ecx;
        _UINT32_T reg_edx;
        _UINT32_T max_function_no = 0;
        _UINT32_T max_subleaf_no = 0;
        _UINT32_T max_ex_function_no = 0;
        cpuid(0, &reg_eax, &reg_ebx, &reg_ecx, &reg_edx);
        max_function_no = reg_eax;
        _ZERO_MEMORY_BYTE(feature, sizeof(*feature));
        if (max_function_no >= 1)
        {
            cpuid(1, &reg_eax, &reg_ebx, &reg_ecx, &reg_edx);
            feature->PROCESSOR_FEATURE_POPCNT = (reg_ecx >> 23) & 1;
        }
        if (max_function_no >= 7)
        {
            cpuidex(7, 0, &reg_eax, &reg_ebx, &reg_ecx, &reg_edx);
            max_subleaf_no = reg_eax;
            feature->PROCESSOR_FEATURE_BMI1 = (reg_ebx >> 3) & 1;
            feature->PROCESSOR_FEATURE_ADX = (reg_ebx >> 8) & 1;
            feature->PROCESSOR_FEATURE_BMI2 = (reg_ebx >> 19) & 1;
        }
        cpuid(0x80000000, &reg_eax, &reg_ebx, &reg_ecx, &reg_edx);
        max_ex_function_no = reg_eax;
        if (max_ex_function_no >= 0x80000001)
        {
            cpuid(0x80000001, &reg_eax, &reg_ebx, &reg_ecx, &reg_edx);
            feature->PROCESSOR_FEATURE_ABM = (reg_ecx >> 5) & 1;
        }
    }

}


/*
 * END OF FILE
 */