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
        unsigned        IS_EVEN : 1;            // 数値が偶数なら TRUE
        unsigned        IS_POWER_OF_TWO : 1;    // 数値が 2 のべき乗なら TRUE

        _UINT32_T       SIGNATURE1;             // テーブルを識別するためのデータ1
        _UINT32_T       SIGNATURE2;             // テーブルを識別するためのデータ2

        PMC_HANDLE_SINT NUMERATOR;              // 数値を分数で表現した場合の分子を表すハンドル
        PMC_HANDLE_UINT DENOMINATOR;            // 数値を分数で表現した場合の分母を表すハンドル
    } NUMBER_OBJECT_RTNL;
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

    extern BOOL AllocateRTNLHeapArea();
    extern void DeallocateRTNLHeapArea();
#if false
    extern void __CheckNumber(NUMBER_OBJECT_SINT* p) noexcept(false);
    extern NUMBER_OBJECT_SINT* DuplicateNumber_X(NUMBER_OBJECT_SINT* x);
    extern NUMBER_OBJECT_SINT* NegateNumber_X(NUMBER_OBJECT_SINT* x);
    extern NUMBER_OBJECT_SINT* From_I_Imp(SIGN_T x_sign, _UINT32_T x_abs);
    extern NUMBER_OBJECT_SINT* From_L_Imp(SIGN_T x_sign, _UINT64_T x_abs);
    extern NUMBER_OBJECT_SINT* From_X_Imp(SIGN_T sign, PMC_HANDLE_UINT x);
#endif
#pragma endregion


#pragma region 初期化関数の宣言
    extern PMC_STATUS_CODE Initialize_Memory(void);
#pragma endregion


#pragma region エントリポイントに登録される関数の宣言
    extern bool PMC_RTNL_Initialize();

#if false
    extern PMC_STATUS_CODE PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

    extern void  PMC_GetStatisticsInfo(PMC_STATISTICS_INFO* statistics_info) noexcept(false);// 与えられた領域に現在まで採取されている統計情報を複写する。

    extern PMC_HANDLE_SINT PMC_From_UI(_UINT32_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_I(_INT32_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_UL(_UINT64_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_L(_INT64_T x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_From_UX(PMC_HANDLE_UINT x) noexcept(false);

    extern _INT32_T PMC_GetHashCode(PMC_HANDLE_SINT p) noexcept(false);

    extern void  PMC_CheckHandle_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern void  PMC_CheckHandle_X(PMC_HANDLE_SINT p) noexcept(false);

    extern void  PMC_Dispose_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern void  PMC_Dispose_X(PMC_HANDLE_SINT p) noexcept(false);

    extern PMC_HANDLE_SINT PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

    extern PMC_HANDLE_SINT PMC_FromByteArray(const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t PMC_ToByteArray(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Clone_X(PMC_HANDLE_SINT x) noexcept(false);

    extern _UINT64_T PMC_GetAllocatedMemorySize() noexcept(false);

    extern _UINT32_T PMC_To_X_UI(PMC_HANDLE_SINT p) noexcept(false);
    extern _INT32_T PMC_To_X_I(PMC_HANDLE_SINT p) noexcept(false);
    extern _UINT64_T PMC_To_X_UL(PMC_HANDLE_SINT p) noexcept(false);
    extern _INT64_T PMC_To_X_L(PMC_HANDLE_SINT p) noexcept(false);
    extern PMC_HANDLE_UINT PMC_To_X_UX(PMC_HANDLE_SINT p) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Negate_UX(PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Negate_X(PMC_HANDLE_SINT x) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Abs_X(PMC_HANDLE_SINT x) noexcept(false);

    extern size_t PMC_ToString(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern void  PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

    extern PMC_STATUS_CODE PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Add_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Add_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Subtruct_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Subtruct_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Increment_X(PMC_HANDLE_SINT x) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Decrement_X(PMC_HANDLE_SINT x) noexcept(false);

    extern PMC_HANDLE_SINT PMC_Multiply_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_Multiply_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern _UINT32_T PMC_DivRem_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT32_T PMC_DivRem_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern _INT64_T PMC_DivRem_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_UINT PMC_DivRem_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
    extern PMC_HANDLE_SINT PMC_DivRem_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);

    extern PMC_HANDLE_SINT PMC_LeftShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

    extern PMC_HANDLE_SINT PMC_RightShift_X_I(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

    extern PMC_HANDLE_SINT PMC_OneComplement_UX(PMC_HANDLE_UINT x) noexcept(false);
    extern PMC_HANDLE_SINT PMC_OneComplement_X(PMC_HANDLE_SINT x) noexcept(false);

    extern _UINT32_T PMC_BitwiseAnd_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern _UINT32_T PMC_BitwiseAnd_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseAnd_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern PMC_HANDLE_SINT PMC_BitwiseOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_BitwiseOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_SINT PMC_ExclusiveOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern SIGN_T PMC_Compare_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern bool PMC_Equals_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern bool PMC_Equals_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern bool PMC_Equals_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern bool PMC_Equals_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern bool PMC_Equals_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern bool PMC_Equals_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UI(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_I(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UL(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_L(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
#endif
#pragma endregion

#pragma region インライン関数の定義

    __inline static NUMBER_OBJECT_RTNL* GET_NUMBER_OBJECT(PMC_HANDLE_RTNL x, const wchar_t* param_name)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", param_name);
        NUMBER_OBJECT_RTNL* nx = (NUMBER_OBJECT_RTNL*)x;
        //__CheckNumber(nx);
        return (nx);
    }

    __inline static PMC_HANDLE_RTNL GET_NUMBER_HANDLE(NUMBER_OBJECT_RTNL* r)
    {
#ifdef _DEBUG
        //__CheckNumber(r);
#endif
        return ((PMC_HANDLE_RTNL)r);
    }

#pragma endregion

}

#endif /* PMC_UINT_INTERNAL_H */

/*
 * END OF FILE
 */