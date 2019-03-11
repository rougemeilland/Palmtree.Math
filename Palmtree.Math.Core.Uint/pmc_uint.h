/*
 * The MIT License
 *
 * Copyright 2018 Palmtree Software.
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

#ifndef PMC_UINT_H
#define PMC_UINT_H

#include "pmc.h"

#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
    extern "C"
    {
#endif

#pragma region 型の定義
        struct __tag_PMC_HANDLE_UINT
        {
#ifdef _M_IX86
            const _UINT32_T HASH_CODE;  // ハッシュコード
#elif defined(_M_X64)
            const _UINT64_T HASH_CODE;  // ハッシュコード
#else
#error unknown platform
#endif
            const struct __tag_UINT_FLAGS
            {
                unsigned    IS_ZERO : 1;            // 数値が 0 なら TRUE
                unsigned    IS_ONE : 1;             // 数値が 1 なら TRUE
                unsigned    IS_EVEN : 1;            // 数値が偶数なら TRUE
                unsigned    IS_POWER_OF_TWO : 1;    // 数値が 2 のべき乗なら TRUE
            } FLAGS;
#ifdef _M_IX86
            _UINT32_T __dummy;
#elif defined(_M_X64)
            _UINT64_T __dummy;
#else
#error unknown platform
#endif
        };
        typedef struct __tag_PMC_HANDLE_UINT* PMC_HANDLE_UINT;

        typedef struct __tag_PMC_UINT_ENTRY_POINTS
        {
            // 実行中のプロセッサの実装命令に関する情報
            unsigned PROCESSOR_FEATURE_POPCNT : 1;  // 実行中のプロセッサの実装命令を示すフラグ。POPCNTをサポートしているなら1、そうではないのなら0。
            unsigned PROCESSOR_FEATURE_ADX : 1;     // 実行中のプロセッサの実装命令を示すフラグ。ADXをサポートしているなら1、そうではないのなら0。
            unsigned PROCESSOR_FEATURE_BMI1 : 1;    // 実行中のプロセッサの実装命令を示すフラグ。BMI1をサポートしているなら1、そうではないのなら0。
            unsigned PROCESSOR_FEATURE_BMI2 : 1;    // 実行中のプロセッサの実装命令を示すフラグ。BMI2をサポートしているなら1、そうではないのなら0。
            unsigned PROCESSOR_FEATURE_ABM : 1;     // 実行中のプロセッサの実装命令を示すフラグ。ABMをサポートしているなら1、そうではないのなら0。

            // コンフィグレーション情報の取得
            PMC_STATUS_CODE (__PMC_CALL *GetConfigurationSettings)(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);
                                                    
            // 統計情報関連
            void (__PMC_CALL * GetStatisticsInfo)(PMC_STATISTICS_INFO* statistics_info);// 与えられた領域に現在まで採取されている統計情報を複写する。

            // コンストラクタ(32bit整数により初期化)
            PMC_HANDLE_UINT(__PMC_CALL * From_I)(_UINT32_T x);

            // コンストラクタ(64bit整数により初期化)
            PMC_HANDLE_UINT(__PMC_CALL * From_L)(_UINT64_T x);

            // デストラクタ
            void (__PMC_CALL * Dispose)(PMC_HANDLE_UINT p);

            // 定数値を取得
            PMC_HANDLE_UINT(__PMC_CALL * GetConstantValue_I)(PMC_CONSTANT_VALUE_CODE type);

            // バイト操作
            PMC_HANDLE_UINT(__PMC_CALL * FromByteArray)(const unsigned char* buffer, size_t count);
            size_t(__PMC_CALL * ToByteArray)(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

            // オブジェクトの複製
            PMC_HANDLE_UINT(__PMC_CALL * Clone_X)(PMC_HANDLE_UINT x);

            // 獲得済みメモリの合計サイズの取得
            _UINT64_T(__PMC_CALL * GetAllocatedMemorySize)();

            // To 関数
            _UINT32_T(__PMC_CALL * To_X_I)(PMC_HANDLE_UINT p);
            _UINT64_T(__PMC_CALL * To_X_L)(PMC_HANDLE_UINT p);

            // 文字列化/文字列の解析
            void (__PMC_CALL * InitializeNumberFormatInfo)(PMC_NUMBER_FORMAT_INFO* info);
            size_t (__PMC_CALL * ToString)(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);
            PMC_STATUS_CODE(__PMC_CALL * TryParse)(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o, _UINT32_T* result);

            // Add 関数
            PMC_HANDLE_UINT(__PMC_CALL * Add_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * Add_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * Add_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Add_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Add_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // Subtruct 関数
            _UINT32_T(__PMC_CALL * Subtruct_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            _UINT64_T(__PMC_CALL * Subtruct_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * Subtruct_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Subtruct_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Subtruct_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // Multiply 関数
            PMC_HANDLE_UINT(__PMC_CALL * Multiply_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * Multiply_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * Multiply_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Multiply_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * Multiply_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // DivRem 関数
            _UINT32_T(__PMC_CALL * DivRem_I_X)(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
            _UINT64_T(__PMC_CALL * DivRem_L_X)(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
            _UINT32_T(__PMC_CALL * DivRem_X_I)(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
            _UINT64_T(__PMC_CALL * DivRem_X_L)(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
            PMC_HANDLE_UINT(__PMC_CALL * DivRem_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

            // LeftShift 関数
            PMC_HANDLE_UINT(__PMC_CALL * LeftShift_X_I)(PMC_HANDLE_UINT p, _INT32_T n);

            // RightShift 関数
            PMC_HANDLE_UINT(__PMC_CALL * RightShift_X_I)(PMC_HANDLE_UINT p, _INT32_T n);

            // BitwiseAnd 関数
            _UINT32_T(__PMC_CALL * BitwiseAnd_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            _UINT64_T(__PMC_CALL * BitwiseAnd_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            _UINT32_T(__PMC_CALL * BitwiseAnd_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            _UINT64_T(__PMC_CALL * BitwiseAnd_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseAnd_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // BitwiseOr 関数
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseOr_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseOr_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseOr_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseOr_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseOr_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // ExclusiveOr 関数
            PMC_HANDLE_UINT(__PMC_CALL * ExclusiveOr_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * ExclusiveOr_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * ExclusiveOr_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * ExclusiveOr_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * ExclusiveOr_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // 比較関数
            _INT32_T(__PMC_CALL * Compare_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            _INT32_T(__PMC_CALL * Compare_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            _INT32_T(__PMC_CALL * Compare_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            _INT32_T(__PMC_CALL * Compare_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            _INT32_T(__PMC_CALL * Compare_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // 等値関数
            _UINT32_T(__PMC_CALL * Equals_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            _UINT32_T(__PMC_CALL * Equals_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            _UINT32_T(__PMC_CALL * Equals_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            _UINT32_T(__PMC_CALL * Equals_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            _UINT32_T(__PMC_CALL * Equals_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // 最大公約数の計算
            PMC_HANDLE_UINT(__PMC_CALL * GreatestCommonDivisor_I_X)(_UINT32_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * GreatestCommonDivisor_L_X)(_UINT64_T u, PMC_HANDLE_UINT v);
            PMC_HANDLE_UINT(__PMC_CALL * GreatestCommonDivisor_X_I)(PMC_HANDLE_UINT u, _UINT32_T v);
            PMC_HANDLE_UINT(__PMC_CALL * GreatestCommonDivisor_X_L)(PMC_HANDLE_UINT u, _UINT64_T v);
            PMC_HANDLE_UINT(__PMC_CALL * GreatestCommonDivisor_X_X)(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);

            // べき乗の計算
            PMC_HANDLE_UINT(__PMC_CALL * Pow_X_I)(PMC_HANDLE_UINT x, _UINT32_T n);
            PMC_HANDLE_UINT(__PMC_CALL * Pow_X_L)(PMC_HANDLE_UINT x, _UINT64_T n);

            // べき剰余の計算
            PMC_HANDLE_UINT(__PMC_CALL * ModPow_X_X_X)(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m);

            // v * 10^e の計算
            PMC_HANDLE_UINT(__PMC_CALL * TimesOfExponentOf10)(_UINT32_T v, _UINT32_T e);

            // 常用対数の整数部の計算
            _UINT32_T(__PMC_CALL * Floor_Log10)(PMC_HANDLE_UINT v);

            // 非公開関数
            PMC_HANDLE_UINT(__PMC_CALL * FromByteArrayForSINT)(unsigned char* buffer, size_t count, char* o_sign);
            size_t(__PMC_CALL * ToByteArrayForSINT)(char p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
            PMC_STATUS_CODE(__PMC_CALL * TryParseForSINT)(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, char* o_sign, PMC_HANDLE_UINT* o_abs, _UINT32_T* result) noexcept(false);
        } PMC_UINT_ENTRY_POINTS;
#pragma endregion


#pragma region 宣言
        PMC_EXPORT PMC_UINT_ENTRY_POINTS* __PMC_CALL PMC_UINT_Initialize(const PMC_CONFIGURATION_INFO*);
#pragma endregion


#ifdef __cplusplus
    }
}
#endif

#endif /* PMC_UINT_H */


/*
 * END OF FILE
 */