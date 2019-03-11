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


#include <windows.h>
#include "pmc_uint.h"
#include "pmc_internal.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 型の定義
    typedef struct __tag_NUMBER_HEADER
    {
        __UNIT_TYPE HASH_CODE;              // データのハッシュコード。
        unsigned IS_ZERO : 1;               // データが 0 なら TRUE
        unsigned IS_ONE : 1;                // データが 1 なら TRUE
        unsigned IS_EVEN : 1;               // データが 偶数 なら TRUE
        unsigned IS_POWER_OF_TWO : 1;       // データが 2 のべき乗なら TRUE

        _UINT32_T SIGNATURE1;               // テーブルを識別するためのデータ1
        _UINT32_T SIGNATURE2;               // テーブルを識別するためのデータ2
        __UNIT_TYPE UNIT_WORD_COUNT;        // BLOCKが示す領域において有効なデータが格納されている要素の数
        __UNIT_TYPE UNIT_BIT_COUNT;         // データの有効部分の合計ビット数
        __UNIT_TYPE TRAILING_ZERO_BITS_COUNT;  // データの最下位の連続した 0 ビット数

        unsigned IS_STATIC : 1;             // 本構造体が静的に割り当てられていて開放不要ならばTRUE
        unsigned IS_COMMITTED : 1;          // データ部のコミットが完了していればTRUE

        size_t BLOCK_COUNT;             // BLOCKが示す領域に格納可能な最大の要素数
        // 多倍長整数の内部データが格納されている領域へのポインタ
        // このポインタが指す領域には少なくともUNIT_COUNT+1個の__UNIT_TYPEを格納するのに十分な大きさがなければならない。
        // UNIT_ARRAY[UNIT_COUNT]の要素はデータの正当性チェックのために使用される。
        __UNIT_TYPE* BLOCK;
        __UNIT_TYPE BLOCK_CHECK_CODE;       // BLOCK が指す領域の検査用の数値
    } NUMBER_HEADER;
#pragma endregion


#pragma region 共用関数/変数の宣言
    // ライブラリのコンフィグレーション情報
    extern PMC_CONFIGURATION_INFO configuration_info;

    // 整数 0 のインスタンス
    extern NUMBER_HEADER number_zero;

    // 整数 1 のインスタンス
    extern NUMBER_HEADER number_one;

    // パフォーマンスカウンタ
    extern PMC_STATISTICS_INFO statistics_info;

    // 内部ヒープメモリ領域を獲得する。
    extern BOOL AllocateHeapArea(void) noexcept(true);

    // 内部ヒープメモリ領域を解放する。
    extern void DeallocateHeapArea(void) noexcept(true);

    // p->BLOCK に格納された数値を確定します。
    extern void CommitNumber(NUMBER_HEADER* p) noexcept(true);

    // 与えられた NUMBER_HEADER 構造体へのポインタが正しい構造体を指しているかどうか検査します。(主としてメモリ破壊の観点で)
    extern void CheckNumber(NUMBER_HEADER* p) noexcept(false);

    // 与えられた NUMBER_HEADER 構造体を複製する。p が指す NUMBER_HEADER 構造体は 0 値であってはならない。
    extern NUMBER_HEADER* DuplicateNumber(NUMBER_HEADER* p);

    // 32bit 整数 x から NUMBER_HEADER 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_HEADER* From_I_Imp(_UINT32_T x) noexcept(false);

    // 64bit 整数 x から NUMBER_HEADER 構造体を構築し、そのポインタを o が指す領域に格納して返す。x は 0 であってはならない。
    extern NUMBER_HEADER* From_L_Imp(_UINT64_T x) noexcept(false);

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
    extern _INT32_T Compare_Imp(__UNIT_TYPE* u, __UNIT_TYPE* v, __UNIT_TYPE count);

    // 与えられた PMC_NUMBER_FORMAT_INFO 構造体を既定値に初期化する。
    extern void InitializeNumberFormatoInfo(PMC_NUMBER_FORMAT_INFO* info);

    // 多倍長整数の加算を行う。
    extern NUMBER_HEADER* PMC_Add_X_X_Imp(NUMBER_HEADER* u, NUMBER_HEADER* v);

    // 多倍長整数のべき乗を計算する。
    extern NUMBER_HEADER* PMC_Pow_X_I_Imp(NUMBER_HEADER* v, _UINT32_T e) noexcept(false);

    // 多倍長整数のべき乗を計算する。
    extern NUMBER_HEADER* PMC_Pow_X_L_Imp(NUMBER_HEADER* v, _UINT64_T e) noexcept(false);

    // 多倍長整数と整数の乗算を行う。
    extern NUMBER_HEADER* PMC_Multiply_X_I_Imp(NUMBER_HEADER* u, _UINT32_T v);

    // v * 10^e を計算する。
    extern NUMBER_HEADER* PMC_TimesOfExponentOf10_Imp(_UINT32_T v, __UNIT_TYPE e);

    // 常用対数の整数部を計算する
    extern _UINT32_T PMC_Floor_Log10_Imp(NUMBER_HEADER* v);

    // 多倍長整数の大小比較を行う。
    _INT32_T PMC_Compare_X_X_Imp(NUMBER_HEADER* u, NUMBER_HEADER* v);
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
    extern PMC_STATUS_CODE __PMC_CALL PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

    extern void __PMC_CALL PMC_GetStatisticsInfo(PMC_STATISTICS_INFO* p);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_From_I(_UINT32_T x) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_From_L(_UINT64_T x) noexcept(false);

    extern void __PMC_CALL PMC_Dispose(PMC_HANDLE_UINT p);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_FromByteArray(const unsigned char* buffer, size_t count) noexcept(false);
    extern size_t __PMC_CALL PMC_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_Clone_X(PMC_HANDLE_UINT x) noexcept(false);

    extern _UINT64_T __PMC_CALL PMC_GetAllocatedMemorySize();

    extern _UINT32_T __PMC_CALL PMC_To_X_I(PMC_HANDLE_UINT p) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_To_X_L(PMC_HANDLE_UINT p) noexcept(false);

    extern void __PMC_CALL PMC_InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info);
    extern size_t __PMC_CALL PMC_ToString(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE __PMC_CALL PMC_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o, _UINT32_T* result) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_Add_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Add_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Add_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Add_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Add_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T __PMC_CALL PMC_Subtruct_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_Subtruct_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Subtruct_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Subtruct_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Subtruct_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T __PMC_CALL PMC_DivRem_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_DivRem_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_DivRem_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_DivRem_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_DivRem_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_RightShift_X_I(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_LeftShift_X_I(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

    extern _UINT32_T __PMC_CALL PMC_BitwiseAnd_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_BitwiseAnd_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_BitwiseAnd_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT64_T __PMC_CALL PMC_BitwiseAnd_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseAnd_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_BitwiseOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_ExclusiveOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_ExclusiveOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_ExclusiveOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_ExclusiveOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_ExclusiveOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _INT32_T __PMC_CALL PMC_Compare_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _INT32_T __PMC_CALL PMC_Compare_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _INT32_T __PMC_CALL PMC_Compare_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _INT32_T __PMC_CALL PMC_Compare_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern _INT32_T __PMC_CALL PMC_Compare_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern _UINT32_T __PMC_CALL PMC_Equals_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_Equals_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_Equals_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_Equals_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern _UINT32_T __PMC_CALL PMC_Equals_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_GreatestCommonDivisor_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_GreatestCommonDivisor_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_GreatestCommonDivisor_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_GreatestCommonDivisor_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_GreatestCommonDivisor_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_Pow_X_I(PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false);
    extern PMC_HANDLE_UINT __PMC_CALL PMC_Pow_X_L(PMC_HANDLE_UINT x, _UINT64_T n) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_ModPow_X_X_X(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_TimesOfExponentOf10(_UINT32_T v, _UINT32_T e);

    extern _UINT32_T __PMC_CALL PMC_Floor_Log10(PMC_HANDLE_UINT v);

    extern PMC_HANDLE_UINT __PMC_CALL PMC_FromByteArrayForSINT(unsigned char* buffer, size_t count, char* o_sign) noexcept(false);
    extern size_t __PMC_CALL PMC_ToByteArrayForSINT(char p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
    extern PMC_STATUS_CODE __PMC_CALL PMC_TryParseForSINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, PMC_HANDLE_UINT* o_abs, _UINT32_T* result) noexcept(false);
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
#pragma endregion


}

#endif /* PMC_UINT_INTERNAL_H */


/*
 * END OF FILE
 */