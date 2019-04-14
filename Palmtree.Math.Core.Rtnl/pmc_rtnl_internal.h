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


#ifndef PMC_RTNL_INTERNAL_H
#define PMC_RTNL_INTERNAL_H

#if defined(__GNUC__) && defined(_M_IX86)
#include <stdio.h>
#endif

#include <windows.h>
#include "pmc_rtnl.h"
#include "pmc_internal.h"
#include "pmc_exception.h"
#include "pmc_uint_cppinterface.h"
#include "pmc_sint_cppinterface.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 型の定義
    typedef struct __tag_NUMBER_OBJECT_RTNL
    {
        unsigned        IS_STATIC : 1;          // 本ハンドルが静的に割り当てられていて開放不要ならばTRUE
        unsigned        IS_INT : 1;             // 数値が整数なら TRUE
        unsigned        IS_ZERO : 1;            // 数値が 0 なら TRUE
        unsigned        IS_ONE : 1;             // 数値が 1 なら TRUE
        unsigned        IS_MINUS_ONE : 1;       // 数値が -1 なら TRUE

        _UINT32_T       SIGNATURE1;             // テーブルを識別するためのデータ1
        _UINT32_T       SIGNATURE2;             // テーブルを識別するためのデータ2
        __UNIT_TYPE     WORKING_COUNT;          // この数値オブジェクトを参照して演算中のスレッドの数

        PMC_HANDLE_SINT NUMERATOR;              // 数値を分数で表現した場合の分子を表すハンドル
        PMC_HANDLE_UINT DENOMINATOR;            // 数値を分数で表現した場合の分母を表すハンドル
    } NUMBER_OBJECT_RTNL;

    typedef struct __tag_PMC_STATISTICS_INFO_RTNL
    {
        _INT64_T COUNT_ALLOCATE_NUMBER_OBJECT;
        _INT64_T COUNT_ALLOCATE_NUMBER;
        _INT64_T COUNT_HOOK_NUMBER_R;
        _INT64_T COUNT_HOOK_NUMBER_X;
        _INT64_T COUNT_HOOK_NUMBER_UX;
    } PMC_STATISTICS_INFO_RTNL;
#pragma endregion


#pragma region 共用関数/変数の宣言
    // 符号なし多倍長整数演算ライブラリのエントリポイント(C++)
    extern PMC_UINT_CppInterface ep_uint;

    // 符号つき多倍長整数演算ライブラリのエントリポイント(C++)
    extern PMC_SINT_CppInterface ep_sint;

    // 整数 0 のインスタンス
    extern NUMBER_OBJECT_RTNL number_object_rtnl_zero;

    // 整数 1 のインスタンス
    extern NUMBER_OBJECT_RTNL number_object_rtnl_one;

    // 整数 -1 のインスタンス
    extern NUMBER_OBJECT_RTNL number_object_rtnl_minus_one;

    // 符号なし整数 0 のインスタンス
    extern PMC_HANDLE_UINT number_handle_uint_zero;

    // 符号なし整数 1 のインスタンス
    extern PMC_HANDLE_UINT number_handle_uint_one;

    // 符号つき整数 0 のインスタンス
    extern PMC_HANDLE_SINT number_handle_sint_zero;

    // 符号つき整数 1 のインスタンス
    extern PMC_HANDLE_SINT number_handle_sint_one;

    // 符号つき整数 -1 のインスタンス
    extern PMC_HANDLE_SINT number_handle_sint_minus_one;

    // パフォーマンスカウンタ
    extern PMC_STATISTICS_INFO_RTNL statistics_info;

    // 内部ヒープメモリ領域を獲得する。
    extern bool __AllocateRTNLHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域を解放する。
    extern void __DeallocateRTNLHeapArea(void) noexcept(true);

    //// 内部ヒープメモリ領域から指定サイズのメモリを獲得する。
    extern void* __AllocateHeap(size_t size) noexcept(false);

    //// 指定されたアドレスのメモリを解放する。
    extern void __DeallocateHeap(void* buffer) noexcept(true);

    extern void __AttatchNumber(ThreadContext& tc, NUMBER_OBJECT_RTNL* p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator);

    extern NUMBER_OBJECT_RTNL* __AllocateNumber(ThreadContext& tc, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator);

    extern  void __DetatchNumber(ThreadContext& tc, NUMBER_OBJECT_RTNL* p);

    extern  void __DeallocateNumber(ThreadContext& tc, NUMBER_OBJECT_RTNL* p);

    extern void __CheckNumber(NUMBER_OBJECT_RTNL* p) noexcept(false);

#pragma endregion

#pragma region 初期化関数の宣言
    extern PMC_STATUS_CODE Initialize_Memory(void);
#pragma endregion

#pragma region エントリポイントに登録される関数の宣言
    extern bool PMC_RTNL_Initialize();

    extern void PMC_UseObject_R(PMC_HANDLE_RTNL x) noexcept(false);
    extern void PMC_UnuseObject_R(PMC_HANDLE_RTNL x) noexcept(false);

    extern PMC_STATUS_CODE PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

    extern _UINT64_T PMC_GetPerformanceCounter(const wchar_t* key);

    extern PMC_HANDLE_RTNL PMC_From_I(ThreadContext& tc, _INT32_T x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_L(ThreadContext& tc, _INT64_T x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_UI(ThreadContext& tc, _UINT32_T x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_UL(ThreadContext& tc, _UINT64_T x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_X(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_DECIMAL(ThreadContext& tc, DECIMAL x) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_From_DOUBLE(ThreadContext& tc, double x) noexcept(false);

    extern _INT32_T PMC_GetHashCode(PMC_HANDLE_RTNL p) noexcept(false);

    extern void  PMC_CheckHandle_R(PMC_HANDLE_RTNL p) noexcept(false);

    extern void  PMC_Dispose_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);

    extern _INT32_T PMC_GetBufferCount_R(PMC_HANDLE_RTNL p) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t PMC_ToByteArray_R(PMC_HANDLE_RTNL p, unsigned char* buffer, size_t buffer_size) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Clone_R(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

    extern _UINT64_T PMC_GetAllocatedMemorySize() noexcept(false);

    extern _UINT32_T PMC_ToUInt32_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern _INT32_T PMC_ToInt32_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern _UINT64_T PMC_ToUInt64_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern _INT64_T PMC_ToInt64_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ToUBigInt_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ToBigInt_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern DECIMAL PMC_ToDecimal_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
    extern double PMC_ToDouble_R(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Negate_R(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Abs_R(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

    extern size_t PMC_ToString_R(ThreadContext& tc, PMC_HANDLE_RTNL x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern void  PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

    extern PMC_STATUS_CODE PMC_TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_RTNL* o) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Add_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Add_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Subtruct_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Subtruct_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Multiply_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Multiply_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Divide_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Divide_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern SIGN_T PMC_Compare_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern SIGN_T PMC_Compare_R_I(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_R_L(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_R_X(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_R_UI(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_R_UL(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_R_UX(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_R_R(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern bool PMC_Equals_I_R(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_L_R(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
    extern bool PMC_Equals_R_I(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
    extern bool PMC_Equals_R_L(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
    extern bool PMC_Equals_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
    extern bool PMC_Equals_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
    extern bool PMC_Equals_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Pow_I_I(ThreadContext& tc, _INT32_T v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_L_I(ThreadContext& tc, _INT64_T v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_X_I(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_UI_I(ThreadContext& tc, _UINT32_T v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_UL_I(ThreadContext& tc, _UINT64_T v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_UX_I(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Pow_R_I(ThreadContext& tc, PMC_HANDLE_RTNL v, _INT32_T e) noexcept(false);

    extern PMC_HANDLE_RTNL PMC_Invert_I(ThreadContext& tc, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_L(ThreadContext& tc, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_X(ThreadContext& tc, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_UI(ThreadContext& tc, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_UL(ThreadContext& tc, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_UX(ThreadContext& tc, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_RTNL PMC_Invert_R(ThreadContext& tc, PMC_HANDLE_RTNL v) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Round_R(ThreadContext& tc, PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode);
    extern PMC_HANDLE_RTNL PMC_Round_R_I(ThreadContext& tc, PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode);
    extern PMC_HANDLE_SINT PMC_Floor_R(ThreadContext& tc, PMC_HANDLE_RTNL x);
    extern PMC_HANDLE_SINT PMC_Ceiling_R(ThreadContext& tc, PMC_HANDLE_RTNL x);

    extern _INT32_T PMC_FloorLog10_R(ThreadContext& tc, PMC_HANDLE_RTNL v);

#pragma endregion

#pragma region インライン関数の定義

    __inline static NUMBER_OBJECT_RTNL* GET_NUMBER_OBJECT(PMC_HANDLE_RTNL x, const wchar_t* param_name)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", param_name);
        NUMBER_OBJECT_RTNL* nx = (NUMBER_OBJECT_RTNL*)x;
        __CheckNumber(nx);
        return (nx);
    }

    __inline static PMC_HANDLE_RTNL GET_NUMBER_HANDLE(NUMBER_OBJECT_RTNL* r)
    {
#ifdef _DEBUG
        __CheckNumber(r);
#endif
        return ((PMC_HANDLE_RTNL)r);
    }

#pragma endregion

}

#endif /* PMC_UINT_INTERNAL_H */

/*
 * END OF FILE
 */