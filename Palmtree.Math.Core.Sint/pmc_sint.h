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


#ifndef PMC_SINT_H
#define PMC_SINT_H

#include "pmc_uint.h"

#ifdef __cplusplus
namespace Palmtree::Math::Core::Internal
{
    extern "C"
    {
#endif

#pragma region 型の定義
        union __tag_PMC_HANDLE_SINT
        {
            const struct __tag_SINT_FLAGS
            {
                unsigned    IS_ZERO : 1;            // 数値が 0 なら TRUE
                unsigned    IS_ONE : 1;             // 数値が 1 なら TRUE
                unsigned    IS_MINUS_ONE : 1;       // 数値が -1 なら TRUE
                unsigned    IS_EVEN : 1;            // 数値が偶数なら TRUE
                unsigned    IS_POWER_OF_TWO : 1;    // 数値が 2 のべき乗なら TRUE
            } FLAGS;
#ifdef _M_IX86
            _UINT32_T __dummy;
#elif defined(_M_IX64)
            _UINT64_T __dummy;
#else
#error unknown platform
#endif
        };
        typedef union __tag_PMC_HANDLE_SINT* PMC_HANDLE_SINT;

        typedef struct __tag_PMC_SINT_ENTRY_POINTS
        {
            // 符号なし整数演算のエントリポイント
            PMC_UINT_ENTRY_POINTS UINT_ENTRY_POINTS;

            // アセンブリ情報関連
            PMC_STATUS_CODE (__PMC_CALL * GetConfigurationSettings)(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

            // 統計情報関連
            void (__PMC_CALL * GetStatisticsInfo)(PMC_STATISTICS_INFO* statistics_info) noexcept(false);// 与えられた領域に現在まで採取されている統計情報を複写する。

            // From 関数
            PMC_HANDLE_SINT (__PMC_CALL * From_UI)(_UINT32_T x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * From_I)(_INT32_T x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * From_UL)(_UINT64_T x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * From_L)(_INT64_T x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * From_UX)(PMC_HANDLE_UINT x) noexcept(false);

            // ハッシュコードの取得
            _INT32_T (__PMC_CALL * GetHashCode)(PMC_HANDLE_SINT p) noexcept(false);

            // デストラクタ
            void  (__PMC_CALL * Dispose)(PMC_HANDLE_SINT p) noexcept(false);

            // 定数値を取得
            PMC_HANDLE_SINT (__PMC_CALL * GetConstantValue_I)(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

            // バイト操作
            PMC_HANDLE_SINT (__PMC_CALL * FromByteArray)(const unsigned char* buffer, size_t count) noexcept(false);
            size_t (__PMC_CALL * ToByteArray)(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

            // オブジェクトの複製
            PMC_HANDLE_SINT (__PMC_CALL * Clone_X)(PMC_HANDLE_SINT x) noexcept(false);

            // 獲得済みメモリの合計サイズの取得
            _UINT64_T(__PMC_CALL * GetAllocatedMemorySize)();

            // To 関数
            _INT32_T (__PMC_CALL * To_X_I)(PMC_HANDLE_SINT p) noexcept(false);
            _UINT32_T (__PMC_CALL * To_X_UI)(PMC_HANDLE_SINT p) noexcept(false);
            _INT64_T (__PMC_CALL * To_X_L)(PMC_HANDLE_SINT p) noexcept(false);
            _UINT64_T (__PMC_CALL * To_X_UL)(PMC_HANDLE_SINT p) noexcept(false);
            PMC_HANDLE_UINT (__PMC_CALL * To_X_UX)(PMC_HANDLE_SINT p) noexcept(false);

            // 符号反転
            PMC_HANDLE_SINT (__PMC_CALL * Negate_UX)(PMC_HANDLE_UINT x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * Negate_X)(PMC_HANDLE_SINT x) noexcept(false);

            // 絶対値
            PMC_HANDLE_UINT (__PMC_CALL * Abs_X)(PMC_HANDLE_SINT x) noexcept(false);

            // 文字列化
            size_t (__PMC_CALL * ToString)(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
            void (__PMC_CALL * InitializeNumberFormatInfo)(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

            // 文字列の解析
            PMC_STATUS_CODE(__PMC_CALL * TryParse)(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o, _UINT32_T* result) noexcept(false);

            // Add 関数
            PMC_HANDLE_SINT(__PMC_CALL * Add_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Add_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // Subtruct 関数
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Subtruct_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // Increment 関数
            PMC_HANDLE_SINT(__PMC_CALL * Increment_X)(PMC_HANDLE_SINT x) noexcept(false);

            // Decrement 関数
            PMC_HANDLE_SINT(__PMC_CALL * Decrement_X)(PMC_HANDLE_SINT x) noexcept(false);

            // Multiply 関数
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * Multiply_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // DivRem 関数
            _UINT32_T(__PMC_CALL * DivRem_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
            _INT32_T(__PMC_CALL * DivRem_I_X)(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
            _UINT64_T(__PMC_CALL * DivRem_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
            _INT64_T(__PMC_CALL * DivRem_L_X)(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_UINT(__PMC_CALL * DivRem_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_I)(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_L)(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * DivRem_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);

            // LeftShift 関数
            PMC_HANDLE_SINT (__PMC_CALL * LeftShift_X_I)(PMC_HANDLE_SINT p, _UINT32_T n) noexcept(false);

            // RightShift 関数
            PMC_HANDLE_SINT (__PMC_CALL * RightShift_X_I)(PMC_HANDLE_SINT p, _UINT32_T n) noexcept(false);

            PMC_HANDLE_SINT (__PMC_CALL * OneComplement_UX)(PMC_HANDLE_UINT x) noexcept(false);
            PMC_HANDLE_SINT (__PMC_CALL * OneComplement_X)(PMC_HANDLE_SINT x) noexcept(false);

            // BitwiseAnd 関数
            _UINT32_T(__PMC_CALL * BitwiseAnd_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseAnd_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT64_T(__PMC_CALL * BitwiseAnd_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseAnd_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseAnd_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * BitwiseAnd_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseAnd_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            _UINT64_T(__PMC_CALL * BitwiseAnd_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseAnd_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_UINT(__PMC_CALL * BitwiseAnd_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseAnd_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // BitwiseOr 関数
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * BitwiseOr_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // ExclusiveOr 関数
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * ExclusiveOr_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // 比較関数
            _INT32_T(__PMC_CALL * Compare_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            _INT32_T(__PMC_CALL * Compare_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // 等値関数
            _UINT32_T(__PMC_CALL * Equals_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            _UINT32_T(__PMC_CALL * Equals_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

            // 最大公約数の計算
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_UI_X)(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_I_X)(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_UL_X)(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_L_X)(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_UX_X)(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_UI)(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_I)(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_UL)(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_L)(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_UX)(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
            PMC_HANDLE_SINT(__PMC_CALL * GreatestCommonDivisor_X_X)(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
        } PMC_SINT_ENTRY_POINTS;
#pragma endregion


#pragma region 宣言
        PMC_EXPORT PMC_SINT_ENTRY_POINTS* __PMC_CALL PMC_SINT_Initialize(const PMC_CONFIGURATION_INFO*);
#pragma endregion


#ifdef __cplusplus
    }
}
#endif

#endif /* PMC_SINT_H */
