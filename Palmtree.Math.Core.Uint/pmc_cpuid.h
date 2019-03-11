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

#ifndef PMC_CPUID_H
#define PMC_CPUID_H


namespace Palmtree::Math::Core::Internal
{

    // CPUIDによる機能の使用可否を識別する構造体。
    // 参照: https://www.wdic.org/w/SCI/cpuid%20(x86), https://en.wikipedia.org/wiki/Bit_Manipulation_Instruction_Sets
    typedef struct _tag_PROCESSOR_FEATURES
    {
        // このフラグで使用可能な命令: POPCNT
        unsigned PROCESSOR_FEATURE_POPCNT : 1;

        // このフラグで使用可能な命令: ADX
        unsigned PROCESSOR_FEATURE_ADX : 1;

        // このフラグで使用可能な命令: TZCNT
        unsigned PROCESSOR_FEATURE_BMI1 : 1;

        // このフラグで使用可能な命令: MULX
        unsigned PROCESSOR_FEATURE_BMI2 : 1;

        // このフラグで使用可能な命令: LZCNT
        unsigned PROCESSOR_FEATURE_ABM : 1;
    } PROCESSOR_FEATURES;

    extern void GetCPUInfo(PROCESSOR_FEATURES* feature);

}


#endif /* PMC_CPUID_H */

/*
 * END OF FILE
 */