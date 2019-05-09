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

#include <intrin.h>
#include "pmc_uint.h"
#include "pmc_internal.h"
#include "pmc_exception.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 型の定義
    class ThreadContext;

    typedef struct __tag_NUMBER_OBJECT_UINT
    {
        __UNIT_TYPE HASH_CODE;              // 数値のハッシュコード。
        unsigned IS_SHARED : 1;             // 本構造体が静的に割り当てられていて開放不要ならばTRUE
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

    typedef struct __tag_PMC_STATISTICS_INFO_UINT
    {
        long COUNT_MULTI64; // 32bit * 32bit => 64bitの乗算の回数
        long COUNT_MULTI32; // 16bit * 16bit => 32bitの乗算の回数
        long COUNT_DIV64;   // 64bit / 32bit => 32bitの除算の回数
        long COUNT_DIV32;   // 32bit / 16bit => 16bitの除算の回数
        _INT64_T COUNT_ALLOCATE_BLOCK;
        _INT64_T COUNT_ALLOCATE_NUMBER_OBJECT;
        _INT64_T COUNT_ALLOCATE_NUMBER;
        _INT64_T COUNT_HOOK_NUMBER;
    } PMC_STATISTICS_INFO_UINT;

    typedef struct __tag_RANDOM_STATE_OBJECT
    {
        _UINT32_T       SIGNATURE1; // テーブルを識別するためのデータ1
        _UINT32_T       SIGNATURE2; // テーブルを識別するためのデータ2

        void*           STATE;     // 乱数の状態を示すオブジェクト
    } RANDOM_STATE_OBJECT;

#pragma endregion


#pragma region 共用関数/変数の宣言

#pragma region 変数の宣言

    // ライブラリのコンフィグレーション情報
    extern PMC_CONFIGURATION_INFO configuration_info;

    // 整数 0 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_zero;

    // 整数 1 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_one;

    // 整数 10 のインスタンス
    extern NUMBER_OBJECT_UINT number_object_uint_ten;

    // パフォーマンスカウンタ
    extern PMC_STATISTICS_INFO_UINT statistics_info;

#pragma endregion

#pragma region メモリ管理関連関数の宣言

    // クリティカルセクションを使用して排他を獲得する。
    extern void __GlobalLock(void) noexcept (true);

    // クリティカルセクションを使用して排他を解放する。
    extern void __GlobalUnlock(void) noexcept (true);

#ifdef USE_WIN32_HEAP
    // 内部ヒープメモリ領域を獲得する。
    extern bool __AllocateUINTHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域を解放する。
    extern void __DeallocateUINTHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域から指定サイズのメモリを獲得する。
    extern void* __AllocateHeap(size_t size) noexcept(false);

    // 指定されたアドレスのメモリを解放する。
    extern void __DeallocateHeap(void* buffer) noexcept(true);
#endif

    // 与えられたビット数のメモリを獲得するのに十分な __UNIT_TYPE 配列を獲得する。
    extern __UNIT_TYPE* __AllocateBlock(ThreadContext& tc, size_t bits, __UNIT_TYPE* allocated_block_words, __UNIT_TYPE* code);

    // AllocateBlock によって獲得されたメモリ領域を解放する。
    extern void __DeallocateBlock(ThreadContext& tc, __UNIT_TYPE* buffer, __UNIT_TYPE buffer_words, __UNIT_TYPE check_code);

    // 与えられた __UNIT_TYPE の配列がオーバーランを引き起こしていないかどうか検査する。
    extern void __CheckBlock(__UNIT_TYPE* buffer, __UNIT_TYPE count, __UNIT_TYPE code);

    extern void __AttatchNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p, __UNIT_TYPE bit_count);

    extern NUMBER_OBJECT_UINT* __AllocateNumber(ThreadContext& tc, __UNIT_TYPE bit_count);

    extern void __DetatchNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p);

    extern void __DeallocateNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p);

    // 与えられた NUMBER_OBJECT_UINT 構造体へのポインタが正しい構造体を指しているかどうか検査する。(主としてメモリ破壊の観点で)
    extern void __CheckNumber(NUMBER_OBJECT_UINT* p) noexcept(false);

    extern RANDOM_STATE_OBJECT* __AllocateRandomStateObjectFromUInt32(ThreadContext& tc, _UINT32_T seed);

    extern RANDOM_STATE_OBJECT* __AllocateRandomStateObjectFromUInt32Array(ThreadContext& tc, _UINT32_T* init_key, _INT32_T key_length);

    extern void __DeallocateRandomStateObject(ThreadContext& tc, RANDOM_STATE_OBJECT* p);

    extern void __CheckNumber(RANDOM_STATE_OBJECT* p) noexcept(false);

    // p->BLOCK に格納された数値を確定します。
    extern void CommitNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p) noexcept(false);

    // 与えられた NUMBER_OBJECT_UINT 構造体を複製する。p が指す NUMBER_OBJECT_UINT 構造体は 0 値であってはならない。
    extern NUMBER_OBJECT_UINT* DuplicateNumber(ThreadContext& tc, NUMBER_OBJECT_UINT* p);

#pragma endregion

#pragma region __UNIT_TYPE* ベースの関数の宣言

    // 多倍長整数の減算を行う。u と v はどちらも 0 であってはならない。また、x のワード長は y のワード長以上でなければならない。
    extern void Subtruct_Imp(__UNIT_TYPE* up, __UNIT_TYPE u_count, __UNIT_TYPE* vp, __UNIT_TYPE v_count, __UNIT_TYPE* wp, __UNIT_TYPE w_count);

    // 多倍長整数の乗算を行う。u と v はどちらも 0 であってはならない。
    extern void Multiply_UX_UX_Imp(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, __UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w);

    // 多倍長同士の除算を行う。work_v_buf が指す領域は v_count ワード以上の大きさが必要である。q_buf が指す領域は <uのビット数> - <vのビット数> + 1 + <1ワード分のビット数> 以上の大きさが必要である。r_buf が指す領域は u_count + 1 ワード以上の大きさが必要である。q_buf に nullptr が与えられた場合は商を出力しない。
    extern void DivRem_UX_UX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* work_v_buf, __UNIT_TYPE* q_buf, __UNIT_TYPE q_buf_count, __UNIT_TYPE* r_buf, __UNIT_TYPE r_buf_count);

    // 多倍長整数の大小比較を行う。
    extern SIGN_T Compare_Imp(__UNIT_TYPE* u, __UNIT_TYPE* v, __UNIT_TYPE count);

    // 指定されたワード列を右にシフトして指定された領域に格納する。シフト数は 0 であってはならない。
    extern void RightShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, bool padding_zero);

    // 指定されたワード列を左にシフトして指定された領域に格納する。シフト数は 0 であってはならない。
    extern void LeftShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, bool padding_zero);

#pragma endregion

#pragma region NUMBER_OBJECT_UINT* ベースの関数

    // 符号なし 32bit 整数 x から NUMBER_OBJECT_UINT 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_OBJECT_UINT* From_UI_Imp(ThreadContext& tc, _UINT32_T x) noexcept(false);

    // 符号なし 64bit 整数 x から NUMBER_OBJECT_UINT 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_OBJECT_UINT* From_UL_Imp(ThreadContext& tc, _UINT64_T x) noexcept(false);

    // 多倍長整数の加算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Add_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);

    // 多倍長整数をインクリメントする。
    extern NUMBER_OBJECT_UINT* PMC_Increment_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* x);

    // 多倍長整数と整数の乗算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Multiply_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v);

    // 多倍長整数と整数の乗算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Multiply_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v);

    // 多倍長整数と多倍長整数の乗算を行う。
    extern NUMBER_OBJECT_UINT* PMC_Multiply_UX_UX_Imp(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);

    // 多倍長整数と整数の除算を行う。
    extern _UINT32_T PMC_DivRem_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v, NUMBER_OBJECT_UINT** q);

    // 多倍長整数と整数の除算を行う。
    extern _UINT64_T PMC_DivRem_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v, NUMBER_OBJECT_UINT** q);

    // 多倍長整数と多倍長整数の除算を行う。
    extern NUMBER_OBJECT_UINT* PMC_DivRem_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v, NUMBER_OBJECT_UINT** q);

    // 多倍長整数と多倍長整数の除算を行う。
    extern NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v) noexcept(false);

    // 多倍長整数の大小比較を行う。
    SIGN_T PMC_Compare_UX_UX_Imp(NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);

    // 多倍長整数を左シフトする。
    NUMBER_OBJECT_UINT* PMC_LeftShift_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T n);

    // 多倍長整数を右シフトする。
    NUMBER_OBJECT_UINT* PMC_RightShift_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T n);

    // 多倍長整数と多倍長整数の最大公約数を計算する。
    extern NUMBER_OBJECT_UINT* PMC_GreatestCommonDivisor_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v);

    // 多倍長整数のべき乗を計算する。
    extern NUMBER_OBJECT_UINT* PMC_Pow_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* v, _UINT32_T e) noexcept(false);

    // 10 のべき乗を計算する。
    extern NUMBER_OBJECT_UINT* PMC_Pow10_UI_Imp(ThreadContext& tc, _UINT32_T n);

    // mode で指定された方法により、有理数 x を小数以下を 0 桁に丸める。
    NUMBER_OBJECT_UINT* PMC_RoundZero_R_Imp(ThreadContext& tc, SIGN_T x_numerator_sign, NUMBER_OBJECT_UINT* x_numerator_abs, NUMBER_OBJECT_UINT* x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);

    // mode で指定された方法により、符号が省略された有理数 x の小数以下を decimals 桁に丸める。
    extern NUMBER_OBJECT_UINT* PMC_Round_R_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* x_numerator_abs, NUMBER_OBJECT_UINT* x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, NUMBER_OBJECT_UINT** r_denominator);
    
    // mode で指定された方法により、有理数 x の小数以下を decimals 桁に丸める。
    extern NUMBER_OBJECT_UINT* PMC_Round_R_Imp(ThreadContext& tc, SIGN_T x_numerator_sign, NUMBER_OBJECT_UINT* x_numerator_abs, NUMBER_OBJECT_UINT* x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, NUMBER_OBJECT_UINT** r_denominator);

    // 常用対数の整数部を計算する
    extern _UINT32_T PMC_FloorLog10_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* v);

    // 常用対数の整数部を計算する
    extern _INT32_T PMC_FloorLog10_R_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* v_numerator, NUMBER_OBJECT_UINT* v_denominator);
#pragma endregion


    // 与えられた PMC_NUMBER_FORMAT_INFO 構造体を既定値に初期化する。
    extern void InitializeNumberFormatoInfo(PMC_NUMBER_FORMAT_INFO* info);

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

    // 低レベル文字列解析の実装の初期化処理を行う。
    extern PMC_STATUS_CODE Initialize_AToI(PROCESSOR_FEATURES* feature);

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

    extern _UINT64_T PMC_GetPerformanceCounter(const wchar_t* key);

    extern PMC_HANDLE_UINT PMC_From_UI(ThreadContext& tc, _INT32_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_UL(ThreadContext& tc, _INT64_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_UI(ThreadContext& tc, _UINT32_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_UL(ThreadContext& tc, _UINT64_T x) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_DECIMAL(ThreadContext& tc, DECIMAL x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator) noexcept(false);
    extern PMC_HANDLE_UINT PMC_From_DOUBLE(ThreadContext& tc, double x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator) noexcept(false);

    extern void PMC_CheckHandle_UX(PMC_HANDLE_UINT p);

    extern void PMC_Dispose_UX(ThreadContext& tc, PMC_HANDLE_UINT p);

    extern _INT32_T PMC_GetBufferCount_UX(PMC_HANDLE_UINT p) noexcept(false);

    extern PMC_HANDLE_UINT PMC_GetConstantValue_UI(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

    extern PMC_HANDLE_UINT PMC_FromByteArray_UINT(ThreadContext& tc, const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t PMC_ToByteArray_UX(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Clone_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

    extern _INT32_T PMC_ToInt32_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern _INT64_T PMC_ToInt64_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern _UINT32_T PMC_ToUInt32_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern _UINT64_T PMC_ToUInt64_UX(PMC_HANDLE_UINT p) noexcept(false);
    extern DECIMAL PMC_ToDecimal_R(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);
    extern double PMC_ToDouble_R(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);

    extern void PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info);
    extern size_t PMC_ToString_UX(ThreadContext& tc, PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse_UINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Add_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Add_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T PMC_Subtruct_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T PMC_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Subtruct_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Increment_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Decrement_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Multiply_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Multiply_UX_UX(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T PMC_DivRem_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
    extern _UINT32_T PMC_DivRem_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern _UINT64_T PMC_DivRem_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern PMC_HANDLE_UINT PMC_DivRem_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

    extern PMC_HANDLE_UINT PMC_DivideExactly_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T PMC_Modulo_X_UI(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT32_T v);
    extern _UINT64_T PMC_Modulo_X_UL(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT64_T v);
    extern PMC_HANDLE_UINT PMC_Modulo_X_UX(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, PMC_HANDLE_UINT v);
    extern PMC_HANDLE_UINT PMC_Modulo_I_UX(ThreadContext& tc, SIGN_T u_sign, _UINT32_T u_abs, PMC_HANDLE_UINT v);
    extern PMC_HANDLE_UINT PMC_Modulo_L_UX(ThreadContext& tc, SIGN_T u_sign, _UINT64_T u_abs, PMC_HANDLE_UINT v);

    extern PMC_HANDLE_UINT PMC_RightShift_UX_I(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern PMC_HANDLE_UINT PMC_LeftShift_UX_I(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern _UINT32_T PMC_BitwiseAnd_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T PMC_BitwiseAnd_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT64_T PMC_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseAnd_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T PMC_OneCompliment_And_BitwiseAnd_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT64_T PMC_OneCompliment_And_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_BitwiseOr_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_BitwiseOr_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_ExclusiveOr_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern SIGN_T PMC_Compare_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern SIGN_T PMC_Compare_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern bool PMC_Equals_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern bool PMC_Equals_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern bool PMC_Equals_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern bool PMC_Equals_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT PMC_GreatestCommonDivisor_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Pow_UI_UI(ThreadContext& tc, _UINT32_T x, _UINT32_T n) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Pow_UL_UI(ThreadContext& tc, _UINT64_T x, _UINT32_T n) noexcept(false);
    extern PMC_HANDLE_UINT PMC_Pow_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false);

    extern PMC_HANDLE_UINT PMC_Pow10_UI(ThreadContext& tc, _UINT32_T n);
        
    extern PMC_HANDLE_UINT PMC_ModPow_UX_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false);

    extern _UINT32_T PMC_FloorLog10_UX(ThreadContext& tc, PMC_HANDLE_UINT v);
    extern _INT32_T PMC_FloorLog10_R(ThreadContext& tc, PMC_HANDLE_UINT v_numerator, PMC_HANDLE_UINT v_denominator);

    extern PMC_HANDLE_UINT PMC_RoundZero_R(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);
    extern PMC_HANDLE_UINT PMC_RoundZero_R(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);

    extern PMC_HANDLE_UINT PMC_Round_R(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);
    extern PMC_HANDLE_UINT PMC_Round_R(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);

    extern PMC_MIDPOINT_ROUNDING_CODE PMC_GetDefaultRoundingMode();
    extern void PMC_SetDefaultRoundingMode(PMC_MIDPOINT_ROUNDING_CODE mode) noexcept(false);

    extern PMC_HANDLE_UINT PMC_FromByteArray_SINT(ThreadContext& tc, const unsigned char* buffer, size_t count, SIGN_T* o_sign) noexcept(false);
    extern PMC_HANDLE_UINT PMC_FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs) noexcept(false);
    extern size_t PMC_ToByteArray_X(SIGN_T p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
    extern size_t PMC_ToByteArray_R(SIGN_T p_numerator_sign, PMC_HANDLE_UINT p_numerator_abs, PMC_HANDLE_UINT p_denominator, unsigned char* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse_SINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, PMC_HANDLE_UINT* o_abs) noexcept(false);
    extern PMC_STATUS_CODE PMC_TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs, PMC_HANDLE_UINT* o_denominator) noexcept(false);
    extern size_t PMC_ToString_X(ThreadContext& tc, SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);
    extern size_t PMC_ToString_R(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);

    extern PMC_HANDLE_SFMT PMC_AllocateRandomStateObjectFromUInt32(ThreadContext& tc, _UINT32_T seed);
    extern PMC_HANDLE_SFMT PMC_AllocateRandomStateObjectFromUInt32Array(ThreadContext& tc, _UINT32_T* init_key, _INT32_T key_length);
    extern void PMC_CheckHandle_SFMT(PMC_HANDLE_SFMT p);
    extern void PMC_Dispose_SFMT(ThreadContext& tc, PMC_HANDLE_SFMT p);
    extern _INT32_T PMC_GetBufferCount_SFMT(PMC_HANDLE_SFMT p) noexcept(false);
    extern _UINT32_T PMC_GenerateUInt32RandomValue(PMC_HANDLE_SFMT handle);
    extern _UINT64_T PMC_GenerateUInt64RandomValue(PMC_HANDLE_SFMT handle);
    extern double PMC_GenerateDoubleRandomValue(PMC_HANDLE_SFMT handle);
    extern PMC_HANDLE_UINT PMC_GenerateUBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count);
    extern PMC_HANDLE_UINT PMC_GenerateUBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count);

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

    __inline static RANDOM_STATE_OBJECT* GET_STATE_OBJECT(PMC_HANDLE_SFMT x, const wchar_t* param_name)
    {
        if (x == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", param_name);
        RANDOM_STATE_OBJECT* nx = (RANDOM_STATE_OBJECT*)x;
        __CheckNumber(nx);
        return (nx);
    }

    __inline static PMC_HANDLE_SFMT GET_STATE_HANDLE(RANDOM_STATE_OBJECT* r)
    {
#ifdef _DEBUG
        __CheckNumber(r);
#endif
        return ((PMC_HANDLE_SFMT)r);
    }
#pragma endregion


}

#endif


/*
 * END OF FILE
 */