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


#ifndef PMC_SINT_INTERNAL_H
#define PMC_SINT_INTERNAL_H

#if defined(__GNUC__) && defined(_M_IX86)
#include <stdio.h>
#endif

#include <windows.h>
#include "pmc_sint.h"
#include "pmc_internal.h"
#include "pmc_exception.h"
#include "pmc_uint_cppinterface.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 型の定義
    typedef struct __tag_NUMBER_OBJECT_SINT
    {
        unsigned        IS_STATIC : 1;          // 本構造体が静的に割り当てられていて解放不要ならばTRUE
        unsigned        IS_ZERO : 1;            // データが 0 なら TRUE
        unsigned        IS_ONE : 1;             // データが 1 なら TRUE
        unsigned        IS_MINUS_ONE : 1;       // データが -1 なら TRUE
        unsigned        IS_EVEN : 1;            // データが 偶数 なら TRUE
        unsigned        IS_POWER_OF_TWO : 1;    // データが 2 のべき乗なら TRUE

        _UINT32_T       SIGNATURE1;             // テーブルを識別するためのデータ1
        _UINT32_T       SIGNATURE2;             // テーブルを識別するためのデータ2
        __UNIT_TYPE     WORKING_COUNT;          // この数値オブジェクトを参照して演算中のスレッドの数

        PMC_HANDLE_UINT ABS;                    // 数値の絶対値を表すハンドル
        SIGN_T          SIGN;                   // 数値の符号
    } NUMBER_OBJECT_SINT;

    typedef struct __tag_PMC_STATISTICS_INFO_SINT
    {
        _INT64_T COUNT_ALLOCATE_NUMBER_OBJECT;
        _INT64_T COUNT_ALLOCATE_NUMBER;
        _INT64_T COUNT_HOOK_NUMBER_X;
        _INT64_T COUNT_HOOK_NUMBER_UX;
    } PMC_STATISTICS_INFO_SINT;
#pragma endregion


#pragma region 共用関数/変数の宣言
    // 符号なし多倍長整数演算ライブラリのエントリポイント(C++)
    extern PMC_UINT_CppInterface ep_uint;

    // 整数 0 のインスタンス
    extern NUMBER_OBJECT_SINT number_object_sint_zero;

    // 整数 1 のインスタンス
    extern NUMBER_OBJECT_SINT number_object_sint_one;

    // 整数 -1 のインスタンス
    extern NUMBER_OBJECT_SINT number_object_sint_minus_one;

    // 符号なし整数 0 のインスタンス
    extern PMC_HANDLE_UINT number_handle_uint_zero;

    // 符号なし整数 1 のインスタンス
    extern PMC_HANDLE_UINT number_handle_uint_one;

    // 符号なし整数 10 のインスタンス
    extern PMC_HANDLE_UINT number_handle_uint_ten;

    // パフォーマンスカウンタ
    extern PMC_STATISTICS_INFO_SINT statistics_info;

    // 内部ヒープメモリ領域を獲得する。
    extern bool __AllocateSINTHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域を解放する。
    extern void __DeallocateSINTHeapArea(void) noexcept(true);

    //// 内部ヒープメモリ領域から指定サイズのメモリを獲得する。
    extern void* __AllocateHeap(size_t size) noexcept(false);

    //// 指定されたアドレスのメモリを解放する。
    extern void __DeallocateHeap(void* buffer) noexcept(true);

    extern void __AttatchNumber(NUMBER_OBJECT_SINT* p, SIGN_T sign, PMC_HANDLE_UINT abs);

    extern NUMBER_OBJECT_SINT* __AllocateNumber(SIGN_T sign, PMC_HANDLE_UINT abs);

    extern  void __DetatchNumber(NUMBER_OBJECT_SINT* p);

    extern  void __DeallocateNumber(NUMBER_OBJECT_SINT* p);

    extern void __CheckNumber(NUMBER_OBJECT_SINT* p) noexcept(false);

    extern NUMBER_OBJECT_SINT* DuplicateNumber_X(NUMBER_OBJECT_SINT* x);
    extern NUMBER_OBJECT_SINT* NegateNumber_X(NUMBER_OBJECT_SINT* x);
    extern NUMBER_OBJECT_SINT* From_I_Imp(SIGN_T x_sign, _UINT32_T x_abs);
    extern NUMBER_OBJECT_SINT* From_L_Imp(SIGN_T x_sign, _UINT64_T x_abs);
    extern NUMBER_OBJECT_SINT* From_X_Imp(SIGN_T sign, PMC_HANDLE_UINT x);
#pragma endregion


#pragma region 初期化関数の宣言
    extern PMC_STATUS_CODE Initialize_Memory(void);
#pragma endregion


#pragma region エントリポイントに登録される関数の宣言
    extern bool PMC_SINT_Initialize();
    extern void PMC_UseObject_X(PMC_HANDLE_SINT x) noexcept(false);
    extern void PMC_UnuseObject_X(PMC_HANDLE_SINT x) noexcept(false);
    extern PMC_STATUS_CODE PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);
    extern _UINT64_T PMC_GetPerformanceCounter(const wchar_t* key);
    extern PMC_HANDLE_SINT PMC_From_UI(_UINT32_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_I(_INT32_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_UL(_UINT64_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_L(_INT64_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_UX(PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_DECIMAL(DECIMAL x, PMC_HANDLE_UINT* o_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_DOUBLE(double x, PMC_HANDLE_UINT* o_denominator) noexcept(false);
    extern _INT32_T PMC_GetHashCode(PMC_HANDLE_SINT p) noexcept(false);
    extern void  PMC_CheckHandle_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern void  PMC_CheckHandle_X(PMC_HANDLE_SINT p) noexcept(false);
    extern void  PMC_Dispose_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern void  PMC_Dispose_X(PMC_HANDLE_SINT p) noexcept(false);
    extern PMC_HANDLE_SINT PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false);
    extern PMC_HANDLE_SINT PMC_FromByteArray_SINT(const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t PMC_ToByteArray_X(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Clone_X(PMC_HANDLE_SINT x) noexcept(false);
    extern _UINT64_T PMC_GetAllocatedMemorySize() noexcept(false);
    extern _UINT32_T PMC_ToUInt32_X(PMC_HANDLE_SINT p) noexcept(false);
    extern _INT32_T PMC_ToInt32_X(PMC_HANDLE_SINT p) noexcept(false);
    extern _UINT64_T PMC_ToUInt64_X(PMC_HANDLE_SINT p) noexcept(false);
    extern _INT64_T PMC_ToInt64_X(PMC_HANDLE_SINT p) noexcept(false);
    extern DECIMAL PMC_ToDecimal_R(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);
    extern double PMC_ToDouble_R(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ToUBigInt_X(PMC_HANDLE_SINT p) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Negate_UX(PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Negate_X(PMC_HANDLE_SINT x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Abs_X(PMC_HANDLE_SINT x) noexcept(false);
    extern size_t PMC_ToString_X(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern size_t PMC_ToString_R(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);
    extern void  PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse_SINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse_RTNL(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o_numerator, PMC_HANDLE_UINT* o_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Increment_X(PMC_HANDLE_SINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Decrement_X(PMC_HANDLE_SINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern _UINT32_T PMC_DivRem_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT32_T PMC_DivRem_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT32_T PMC_DivRem_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT64_T PMC_DivRem_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT64_T PMC_DivRem_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_UINT PMC_DivRem_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _UINT32_T PMC_DivRem_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivideExactly_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_LeftShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);
    extern PMC_HANDLE_SINT PMC_RightShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);
    extern PMC_HANDLE_SINT PMC_OneComplement_UX(PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_OneComplement_X(PMC_HANDLE_SINT x) noexcept(false);
    extern _UINT32_T PMC_BitwiseAnd_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern _UINT32_T PMC_BitwiseAnd_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern bool PMC_Equals_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern bool PMC_Equals_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern bool PMC_Equals_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern bool PMC_Equals_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern bool PMC_Equals_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern bool PMC_Equals_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_FromByteArray_RTNL(const unsigned char * buffer, size_t count, PMC_HANDLE_SINT * o_numerator) noexcept(false);
    extern size_t PMC_ToByteArray_R(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator, unsigned char * buffer, size_t buffer_size) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Round_R(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);
    extern PMC_HANDLE_SINT PMC_Round_R_I(PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);
    extern PMC_HANDLE_SINT PMC_Pow_I_UI(_INT32_T v, _UINT32_T e) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_L_UI(_INT64_T v, _UINT32_T e) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_X_UI(PMC_HANDLE_SINT v, _UINT32_T e) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_I_I(_INT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_L_I(_INT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_X_I(PMC_HANDLE_SINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_UI_I(_UINT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_UL_I(_UINT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_UX_I(PMC_HANDLE_UINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Pow_R_I(PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern _INT32_T PMC_FloorLog10_R(PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator);
    extern PMC_HANDLE_SINT PMC_Divide_UI_R(_UINT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_UL_R(_UINT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_I_R(_INT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_L_R(_INT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_UI(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_UL(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_UX(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_I(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_L(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_X(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Divide_R_R(PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_I(_INT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_L(_INT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_X(PMC_HANDLE_SINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_UI(_UINT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_UL(_UINT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_UX(PMC_HANDLE_UINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Invert_R(PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* r_denominator) noexcept(false);

#pragma endregion

#pragma region インライン関数の定義

    __inline static _INT32_T GET_INT_32(SIGN_T sign, _UINT32_T abs) noexcept(false)
    {
        if (sign > 0)
        {
            if (abs >= ((_INT64_T)1 << 31))
                throw OverflowException(L"符号つき32bit整数への型変換に失敗しました。");
            return ((_UINT32_T)abs);
        }
        else if (sign == 0)
        {
            if (abs != 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_inline_func.h;GET_INT_32;1");
            return (0);
        }
        else
        {
            if (abs > ((_INT64_T)1 << 31))
                throw OverflowException(L"符号つき32bit整数への型変換に失敗しました。");
            else if (abs == ((_INT64_T)1 << 31))
                return ((_INT32_T)abs);
            else
                return (-(_INT32_T)abs);
        }
    }

    __inline static _INT64_T GET_INT_64(SIGN_T sign, _UINT64_T abs) noexcept(false)
    {
        if (sign > 0)
        {
            if (abs >= ((_INT64_T)1 << 63))
                throw OverflowException(L"符号つき64bit整数への型変換に失敗しました。");
            return ((_INT64_T)abs);
        }
        else if (sign == 0)
        {
            if (abs != 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_inline_func.h;GET_INT_64;1");
            return (0);
        }
        else
        {
            if (abs > ((_INT64_T)1 << 63))
                throw OverflowException(L"符号つき64bit整数への型変換に失敗しました。");
            else if (abs == ((_INT64_T)1 << 63))
                return ((_INT64_T)abs);
            else
                return (-(_INT64_T)abs);
        }
    }

    __inline static NUMBER_OBJECT_SINT* GET_NUMBER_OBJECT(PMC_HANDLE_SINT x, const wchar_t* param_name)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", param_name);
        NUMBER_OBJECT_SINT* nx = (NUMBER_OBJECT_SINT*)x;
        __CheckNumber(nx);
        return (nx);
    }

    __inline static PMC_HANDLE_SINT GET_NUMBER_HANDLE(NUMBER_OBJECT_SINT* r)
    {
#ifdef _DEBUG
        __CheckNumber(r);
#endif
        return ((PMC_HANDLE_SINT)r);
    }

#pragma endregion

}

#endif /* PMC_UINT_INTERNAL_H */

/*
 * END OF FILE
 */