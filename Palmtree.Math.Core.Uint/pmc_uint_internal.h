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

#ifndef PMC_UINT_INTERNAL_H
#define PMC_UINT_INTERNAL_H

#if defined(__GNUC__) && defined(_M_IX86)
#include <stdio.h>
#endif

#include <windows.h>
#include "pmc_uint.h"
#include "pmc_internal.h"
#include "pmc_exception.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 型の定義
    typedef struct __tag_NUMBER_OBJECT_UINT
    {
        __UNIT_TYPE HASH_CODE;              // データのハッシュコード。
        unsigned IS_STATIC : 1;             // 本構造体が静的に割り当てられていて開放不要ならばTRUE
        unsigned IS_ZERO : 1;               // データが 0 なら TRUE
        unsigned IS_ONE : 1;                // データが 1 なら TRUE
        unsigned IS_EVEN : 1;               // データが 偶数 なら TRUE
        unsigned IS_POWER_OF_TWO : 1;       // データが 2 のべき乗なら TRUE

        _UINT32_T SIGNATURE1;               // テーブルを識別するためのデータ1
        _UINT32_T SIGNATURE2;               // テーブルを識別するためのデータ2
        __UNIT_TYPE UNIT_WORD_COUNT;        // BLOCKが示す領域において有効なデータが格納されている要素の数
        __UNIT_TYPE UNIT_BIT_COUNT;         // データの有効部分の合計ビット数
        __UNIT_TYPE TRAILING_ZERO_BITS_COUNT;  // データの最下位の連続した 0 ビット数

        unsigned IS_COMMITTED : 1;          // データ部のコミットが完了していればTRUE

        size_t BLOCK_COUNT;             // BLOCKが示す領域に格納可能な最大の要素数
        // 多倍長整数の内部データが格納されている領域へのポインタ
        // このポインタが指す領域には少なくともUNIT_COUNT+1個の__UNIT_TYPEを格納するのに十分な大きさがなければならない。
        // UNIT_ARRAY[UNIT_COUNT]の要素はデータの正当性チェックのために使用される。
        __UNIT_TYPE* BLOCK;
        __UNIT_TYPE BLOCK_CHECK_CODE;       // BLOCK が指す領域の検査用の数値
    } NUMBER_OBJECT_UINT;
#pragma endregion


#pragma region 共用関数/変数の宣言
    // ライブラリのコンフィグレーション情報
    extern PMC_CONFIGURATION_INFO configuration_info;

    // 整数 0 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_zero;

    // 整数 1 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_one;

    // 整数 10 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_ten;

    // パフォーマンスカウンタ
    extern PMC_STATISTICS_INFO statistics_info;

    // 内部ヒープメモリ領域を獲得する。
    extern BOOL AllocateUINTHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域を解放する。
    extern void DeallocateUINTHeapArea(void) noexcept(true);

    // p->BLOCK に格納された数値を確定します。
    extern void CommitNumber(NUMBER_OBJECT_UINT* p) noexcept(false);

    // 与えられた NUMBER_OBJECT_UINT 構造体へのポインタが正しい構造体を指しているかどうか検査します。(主としてメモリ破壊の観点で)
    extern void __CheckNumber(NUMBER_OBJECT_UINT* p) noexcept(false);

    // 与えられた NUMBER_OBJECT_UINT 構造体を複製する。p が指す NUMBER_OBJECT_UINT 構造体は 0 値であってはならない。
    extern NUMBER_OBJECT_UINT* DuplicateNumber(NUMBER_OBJECT_UINT* p);

    // 符号なし 32bit 整数 x から NUMBER_OBJECT_UINT 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_OBJECT_UINT* From_UI_Imp(_UINT32_T x) noexcept(false);

    // 符号なし 64bit 整数 x から NUMBER_OBJECT_UINT 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_OBJECT_UINT* From_UL_Imp(_UINT64_T x) noexcept(false);

    // 指定されたワード列を右にシフトして指定された領域に格納する。シフト数は 0 であってはならない。
    extern void RightShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, BOOL padding_zero);

    // 指定されたワード列を左にシフトして指定された領域に格納する。シフト数は 0 であってはならない。
    extern void LeftShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, BOOL padding_zero);

    // 多倍長整数の減算を行う。u と v はどちらも 0 であってはならない。また、x のワード長は y のワード長以上でなければならない。
    extern void Subtruct_Imp(__UNIT_TYPE* up, __UNIT_TYPE u_count, __UNIT_TYPE* vp, __UNIT_TYPE v_count, __UNIT_TYPE* wp, __UNIT_TYPE w_count);

    // 多倍長整数の乗算を行う。u と v はどちらも 0 であってはならない。
    extern void Multiply_X_X_Imp(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w);

    // 多倍長整数を 1 ワードで除算を行う。
    extern void DivRem_X_1W(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_len, __UNIT_TYPE v, __UNIT_TYPE* q_buf, __UNIT_TYPE* r_buf);

    // 多倍長整数の 1 ワードによる剰余を計算する。
    extern __UNIT_TYPE Rem_X_1W(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_len, __UNIT_TYPE v);

    // 多倍長同士の除算を行う。work_v_buf が指す領域は v_count ワード以上の大きさが必要である。q_buf が指す領域は <uのビット数> - <vのビット数> + 1 + <1ワード分のビット数> 以上の大きさが必要である。r_buf が指す領域は u_count + 1 ワード以上の大きさが必要である。q_buf に nullptr が与えられた場合は商を出力しない。
    extern void DivRem_X_X(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* work_v_buf, __UNIT_TYPE* q_buf, __UNIT_TYPE* r_buf);

    // 多倍長整数の大小比較を行う。
    extern SIGN_T Compare_Imp(__UNIT_TYPE* u, __UNIT_TYPE* v, __UNIT_TYPE count);

    // 与えられた PMC_NUMBER_FORMAT_INFO 構造体を既定値に初期化する。
    extern void InitializeNumberFormatoInfo(PMC_NUMBER_FORMAT_INFO* info);

    // 多倍長整数の加算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Add_X_X_Imp(NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);

    // 多倍長整数のべき乗を計算する。
    extern NUMBER_OBJECT_UINT* PMC_Pow_X_I_Imp(NUMBER_OBJECT_UINT* v, _UINT32_T e) noexcept(false);

    // 多倍長整数のべき乗を計算する。
    extern NUMBER_OBJECT_UINT* PMC_Pow_X_L_Imp(NUMBER_OBJECT_UINT* v, _UINT64_T e) noexcept(false);

    // 多倍長整数と整数の乗算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Multiply_X_I_Imp(NUMBER_OBJECT_UINT* u, _UINT32_T v);

    // v * 10^e を計算する。
    extern NUMBER_OBJECT_UINT* PMC_TimesOfExponentOf10_Imp(_UINT32_T v, __UNIT_TYPE e);

    // 常用対数の整数部を計算する
    extern _UINT32_T PMC_Floor_Log10_Imp(NUMBER_OBJECT_UINT* v);

    // 多倍長整数の大小比較を行う。
    SIGN_T PMC_Compare_X_X_Imp(NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);
#pragma endregion


#pragma region モジュール初期化関数の宣言
    // メモリ管理の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Memory(PROCESSOR_FEATURES* feature);

    // コンストラクタの実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_From(PROCESSOR_FEATURES *feature);

    // Toの実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_To(PROCESSOR_FEATURES *feature);

    // 加算演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Add(PROCESSOR_FEATURES* feature);

    // 減算演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Subtruct(PROCESSOR_FEATURES* feature);

    // 乗算演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Multiply(PROCESSOR_FEATURES* feature);

    // 除算演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_DivRem(PROCESSOR_FEATURES* feature);

    // ビットシフト演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Shift(PROCESSOR_FEATURES* feature);

    // ビットAND演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_BitwiseAnd(PROCESSOR_FEATURES* feature);

    // ビットOR演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_BitwiseOr(PROCESSOR_FEATURES* feature);

    // XOR演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_ExclusiveOr(PROCESSOR_FEATURES* feature);

    // 比較演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Compare(PROCESSOR_FEATURES* feature);

    // 等値演算子の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Equals(PROCESSOR_FEATURES* feature);

    // 文字列化の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_ToString(PROCESSOR_FEATURES* feature);

    // 文字列解析の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Parse(PROCESSOR_FEATURES* feature);

    // 最大公約数の計算の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_GreatestCommonDivisor(PROCESSOR_FEATURES* feature);

    // べき乗計算の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Pow(PROCESSOR_FEATURES* feature);

    // べき剰余計算の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_ModPow(PROCESSOR_FEATURES* feature);

    // 対数計算の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_Log(PROCESSOR_FEATURES* feature);
#pragma endregion


#pragma region エントリポイントに登録される関数の宣言
    extern bool PMC_UINT_Initialize();

    extern PMC_STATUS_CODE PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

    extern void PMC_GetStatisticsInfo(PMC_STATISTICS_INFO* p);

    extern PMC_HANDLE_UINT PMC_From_I(_INT32_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_L(_INT64_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_UI(_UINT32_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_UL(_UINT64_T x) noexcept(false);

    extern void PMC_CheckHandle_X(PMC_HANDLE_UINT p);
    extern void PMC_Dispose_X(PMC_HANDLE_UINT p);

    extern PMC_HANDLE_UINT PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

    extern PMC_HANDLE_UINT PMC_FromByteArray(const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t PMC_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Clone_X(PMC_HANDLE_UINT x) noexcept(false);

    extern _UINT64_T PMC_GetAllocatedMemorySize();

    extern _INT32_T PMC_ToInt32_X(PMC_HANDLE_UINT p) noexcept(false);
    extern _INT64_T PMC_ToInt64_X(PMC_HANDLE_UINT p) noexcept(false);
    extern _UINT32_T PMC_ToUInt32_X(PMC_HANDLE_UINT p) noexcept(false);
    extern _UINT64_T PMC_ToUInt64_X(PMC_HANDLE_UINT p) noexcept(false);

    extern void PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info);
    extern size_t PMC_ToString(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Add_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T PMC_Subtruct_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T PMC_Subtruct_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Increment_X(PMC_HANDLE_UINT x) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Decrement_X(PMC_HANDLE_UINT x) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Multiply_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T PMC_DivRem_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
    extern _UINT32_T PMC_DivRem_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern PMC_HANDLE_UINT PMC_DivRem_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

    extern PMC_HANDLE_UINT PMC_RightShift_X_I(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern PMC_HANDLE_UINT PMC_LeftShift_X_I(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern _UINT32_T PMC_BitwiseAnd_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T PMC_BitwiseAnd_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T PMC_OneCompliment_And_BitwiseAnd_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT64_T PMC_OneCompliment_And_BitwiseAnd_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_BitwiseOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_ExclusiveOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern SIGN_T PMC_Compare_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern bool PMC_Equals_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern bool PMC_Equals_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern bool PMC_Equals_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Pow_X_I(PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Pow_X_L(PMC_HANDLE_UINT x, _UINT64_T n) noexcept(false);

    extern PMC_HANDLE_UINT PMC_ModPow_X_X_X(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false);

    extern PMC_HANDLE_UINT PMC_TimesOfExponentOf10(_UINT32_T v, _UINT32_T e);

    extern _UINT32_T PMC_Floor_Log10(PMC_HANDLE_UINT v);

    extern PMC_HANDLE_UINT PMC_FromByteArrayForSINT(const unsigned char* buffer, size_t count, SIGN_T* o_sign) noexcept(false);
    extern size_t PMC_ToByteArrayForSINT(SIGN_T p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParseForSINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, PMC_HANDLE_UINT* o_abs) noexcept(false);
    extern size_t PMC_ToStringForSINT(SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);

    extern void PMC_InternalTest();
#pragma endregion


#pragma region インライン関数の定義
    __inline static void IncrementDIV32Counter(void)
    {
        _InterlockedIncrement(&statistics_info.COUNT_DIV32);
    }


    __inline static void IncrementDIV64Counter(void)
    {
        _InterlockedIncrement(&statistics_info.COUNT_DIV64);
    }


    __inline static void IncrementMULTI32Counter(void)
    {
        _InterlockedIncrement(&statistics_info.COUNT_MULTI32);
    }


    __inline static void IncrementMULTI64Counter(void)
    {
        _InterlockedIncrement(&statistics_info.COUNT_MULTI64);
    }

    __inline static void AddToDIV32Counter(_INT32_T value)
    {
        _InterlockedExchangeAdd(&statistics_info.COUNT_DIV32, value);
    }


    __inline static void AddToDIV64Counter(_INT32_T value)
    {
        _InterlockedExchangeAdd(&statistics_info.COUNT_DIV64, value);
    }


    __inline static void AddToMULTI32Counter(_INT32_T value)
    {
        _InterlockedExchangeAdd(&statistics_info.COUNT_MULTI32, value);
    }


    __inline static void AddToMULTI64Counter(_INT32_T value)
    {
        _InterlockedExchangeAdd(&statistics_info.COUNT_MULTI64, value);
    }

    __inline static NUMBER_OBJECT_UINT* GET_NUMBER_OBJECT(PMC_HANDLE_UINT x, const wchar_t* param_name)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", param_name);
        NUMBER_OBJECT_UINT* nx = (NUMBER_OBJECT_UINT*)x;
        __CheckNumber(nx);
        return (nx);
    }

    __inline static PMC_HANDLE_UINT GET_NUMBER_HANDLE(NUMBER_OBJECT_UINT* r)
    {
#ifdef _DEBUG
        __CheckNumber(r);
#endif
        return ((PMC_HANDLE_UINT)r);
    }

#pragma endregion


}

#endif /* PMC_UINT_INTERNAL_H */


/*
 * END OF FILE
 */