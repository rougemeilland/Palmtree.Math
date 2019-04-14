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
#ifndef PMC_STRING_H
#define PMC_STRING_H


#include "pmc_uint_internal.h"
#include "pmc_thousandseparatedstringwriter.h"


namespace Palmtree::Math::Core::Internal
{

    //
    // 関数の宣言
    //

    // 整数値を文字列化する
    extern void PMC_LToA_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* int_part, ReverseStringWriter& writer);

    // 数字のみから構成された文字列を整数化する
    extern NUMBER_OBJECT_UINT* PMC_AToL_Imp(ThreadContext& tc, const wchar_t* source);

    // 数字のみから構成された文字列を整数化する
    extern PMC_HANDLE_UINT PMC_AToL(ThreadContext& tc, const wchar_t* source);

#ifdef _M_IX86
    // 短い整数値を文字列化する
    extern void PMC_ItoA(_UINT32_T x, ReverseStringWriter& writer);

    // 数字のみから構成された短い文字列を整数化する
    extern _UINT32_T PMC_AToI(const wchar_t* source);
#elif defined(_M_X64)
    // 短い整数値を文字列化する
    extern void PMC_ItoA(_UINT64_T x, ReverseStringWriter& writer);

    // 数字のみから構成された短い文字列を整数化する
    extern _UINT64_T PMC_AToI(const wchar_t* source);
#else
#error unknown platform
#endif

    // 小数値を文字列化する
    extern void PMC_FToA_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator, size_t max_fraction_part_length, StringWriter& simple_number_sequence_writer);

}

#endif


/*
 * END OF FILE
 */
