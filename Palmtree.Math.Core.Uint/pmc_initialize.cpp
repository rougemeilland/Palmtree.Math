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


#include <windows.h>
#include <intrin.h>
#include <immintrin.h>
#include "pmc_uint_internal.h"
#include "pmc_cpuid.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
    PMC_CONFIGURATION_INFO configuration_info;
    static PMC_UINT_ENTRY_POINTS entry_points;
    static char initialized = 0;
#pragma endregion

    PMC_STATUS_CODE __PMC_CALL PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
    {
        if (lstrcmpW(key, L"COMPILER") == 0)
        {
#ifdef _MSC_VER
            const wchar_t value[] = L"MSC";
#elif defined(__GNUC__)
            const wchar_t value[] = L"GNUC";
#else
#error unknwon compiler
#endif
            if (value_buffer != nullptr)
            {
                if (value_buffer_size < countof(value))
                    return (PMC_STATUS_INSUFFICIENT_BUFFER);
                lstrcpyW(value_buffer, value);
            }
            *count = countof(value);
            return (PMC_STATUS_OK);
        }
        else if (lstrcmpW(key, L"PLATFORM") == 0)
        {
#ifdef _M_IX86
            const wchar_t value[] = L"x86";
#elif defined(_M_X64)
            const wchar_t value[] = L"x64";
#else
#error unknwon compiler
#endif
            if (value_buffer != nullptr)
            {
                if (value_buffer_size < countof(value))
                    return (PMC_STATUS_INSUFFICIENT_BUFFER);
                lstrcpyW(value_buffer, value);
            }
            *count = countof(value);
            return (PMC_STATUS_OK);
        }
        else
        {
            *count = -1;
            return (PMC_STATUS_ARGUMENT_ERROR);
        }
    }


    static BOOL SelfCheck()
    {
        NUMBER_HEADER nh;
        PMC_HANDLE_UINT handle = (PMC_HANDLE_UINT)&nh;

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.HASH_CODE = 0x12345678;
        if (handle->HASH_CODE != 0x12345678)
            return (FALSE);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_EVEN = TRUE;
        if (!handle->FLAGS.IS_EVEN)
            return (FALSE);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_ONE = TRUE;
        if (!handle->FLAGS.IS_ONE)
            return (FALSE);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_POWER_OF_TWO = TRUE;
        if (!handle->FLAGS.IS_POWER_OF_TWO)
            return (FALSE);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_ZERO = TRUE;
        if (!handle->FLAGS.IS_ZERO)
            return (FALSE);

        return(TRUE);
    }

    PMC_EXPORT PMC_UINT_ENTRY_POINTS* __PMC_CALL PMC_UINT_Initialize(const PMC_CONFIGURATION_INFO* config)
    {
        if (!initialized)
        {
            if (!SelfCheck())
                return (nullptr);

            PROCESSOR_FEATURES feature;
            GetCPUInfo(&feature);
            configuration_info = *config;
            if (Initialize_Memory(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_From(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_To(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Add(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Subtruct(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Multiply(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_DivRem(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Shift(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_BitwiseAnd(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_BitwiseOr(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_ExclusiveOr(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Compare(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Equals(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_ToString(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Parse(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_GreatestCommonDivisor(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Pow(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_ModPow(&feature) != PMC_STATUS_OK)
                return (nullptr);
            if (Initialize_Log(&feature) != PMC_STATUS_OK)
                return (nullptr);

            entry_points.PROCESSOR_FEATURE_POPCNT = feature.PROCESSOR_FEATURE_POPCNT;
            entry_points.PROCESSOR_FEATURE_ADX = feature.PROCESSOR_FEATURE_ADX;
            entry_points.PROCESSOR_FEATURE_BMI1 = feature.PROCESSOR_FEATURE_BMI1;
            entry_points.PROCESSOR_FEATURE_BMI2 = feature.PROCESSOR_FEATURE_BMI2;
            entry_points.PROCESSOR_FEATURE_ABM = feature.PROCESSOR_FEATURE_ABM;
            entry_points.GetConfigurationSettings = PMC_GetConfigurationSettings;
            entry_points.GetStatisticsInfo = PMC_GetStatisticsInfo;
            entry_points.From_I = PMC_From_I;
            entry_points.From_L = PMC_From_L;
            entry_points.Dispose = PMC_Dispose;
            entry_points.To_X_I = PMC_To_X_I;
            entry_points.To_X_L = PMC_To_X_L;
            entry_points.FromByteArray = PMC_FromByteArray;
            entry_points.ToByteArray = PMC_ToByteArray;
            entry_points.InitializeNumberFormatInfo = PMC_InitializeNumberFormatInfo;
            entry_points.ToString = PMC_ToString;
            entry_points.TryParse = PMC_TryParse;
            entry_points.Add_I_X = PMC_Add_I_X;
            entry_points.Add_L_X = PMC_Add_L_X;
            entry_points.Add_X_I = PMC_Add_X_I;
            entry_points.Add_X_L = PMC_Add_X_L;
            entry_points.Add_X_X = PMC_Add_X_X;
            entry_points.Subtruct_I_X = PMC_Subtruct_I_X;
            entry_points.Subtruct_L_X = PMC_Subtruct_L_X;
            entry_points.Subtruct_X_I = PMC_Subtruct_X_I;
            entry_points.Subtruct_X_L = PMC_Subtruct_X_L;
            entry_points.Subtruct_X_X = PMC_Subtruct_X_X;
            entry_points.Multiply_I_X = PMC_Multiply_I_X;
            entry_points.Multiply_L_X = PMC_Multiply_L_X;
            entry_points.Multiply_X_I = PMC_Multiply_X_I;
            entry_points.Multiply_X_L = PMC_Multiply_X_L;
            entry_points.Multiply_X_X = PMC_Multiply_X_X;
            entry_points.DivRem_I_X = PMC_DivRem_I_X;
            entry_points.DivRem_L_X = PMC_DivRem_L_X;
            entry_points.DivRem_X_I = PMC_DivRem_X_I;
            entry_points.DivRem_X_L = PMC_DivRem_X_L;
            entry_points.DivRem_X_X = PMC_DivRem_X_X;
            entry_points.RightShift_X_I = PMC_RightShift_X_I;
            entry_points.LeftShift_X_I = PMC_LeftShift_X_I;
            entry_points.BitwiseAnd_I_X = PMC_BitwiseAnd_I_X;
            entry_points.BitwiseAnd_L_X = PMC_BitwiseAnd_L_X;
            entry_points.BitwiseAnd_X_I = PMC_BitwiseAnd_X_I;
            entry_points.BitwiseAnd_X_L = PMC_BitwiseAnd_X_L;
            entry_points.BitwiseAnd_X_X = PMC_BitwiseAnd_X_X;
            entry_points.BitwiseOr_I_X = PMC_BitwiseOr_I_X;
            entry_points.BitwiseOr_L_X = PMC_BitwiseOr_L_X;
            entry_points.BitwiseOr_X_I = PMC_BitwiseOr_X_I;
            entry_points.BitwiseOr_X_L = PMC_BitwiseOr_X_L;
            entry_points.BitwiseOr_X_X = PMC_BitwiseOr_X_X;
            entry_points.ExclusiveOr_I_X = PMC_ExclusiveOr_I_X;
            entry_points.ExclusiveOr_L_X = PMC_ExclusiveOr_L_X;
            entry_points.ExclusiveOr_X_I = PMC_ExclusiveOr_X_I;
            entry_points.ExclusiveOr_X_L = PMC_ExclusiveOr_X_L;
            entry_points.ExclusiveOr_X_X = PMC_ExclusiveOr_X_X;
            entry_points.Compare_I_X = PMC_Compare_I_X;
            entry_points.Compare_L_X = PMC_Compare_L_X;
            entry_points.Compare_X_I = PMC_Compare_X_I;
            entry_points.Compare_X_L = PMC_Compare_X_L;
            entry_points.Compare_X_X = PMC_Compare_X_X;
            entry_points.Equals_I_X = PMC_Equals_I_X;
            entry_points.Equals_L_X = PMC_Equals_L_X;
            entry_points.Equals_X_I = PMC_Equals_X_I;
            entry_points.Equals_X_L = PMC_Equals_X_L;
            entry_points.Equals_X_X = PMC_Equals_X_X;
            entry_points.GreatestCommonDivisor_I_X = PMC_GreatestCommonDivisor_I_X;
            entry_points.GreatestCommonDivisor_L_X = PMC_GreatestCommonDivisor_L_X;
            entry_points.GreatestCommonDivisor_X_I = PMC_GreatestCommonDivisor_X_I;
            entry_points.GreatestCommonDivisor_X_L = PMC_GreatestCommonDivisor_X_L;
            entry_points.GreatestCommonDivisor_X_X = PMC_GreatestCommonDivisor_X_X;
            entry_points.Pow_X_I = PMC_Pow_X_I;
            entry_points.Pow_X_L = PMC_Pow_X_L;
            entry_points.ModPow_X_X_X = PMC_ModPow_X_X_X;
            entry_points.TimesOfExponentOf10 = PMC_TimesOfExponentOf10;
            entry_points.Floor_Log10 = PMC_Floor_Log10;
            entry_points.GetConstantValue_I = PMC_GetConstantValue_I;
            entry_points.Clone_X = PMC_Clone_X;
            entry_points.GetAllocatedMemorySize = PMC_GetAllocatedMemorySize;

            entry_points.FromByteArrayForSINT = PMC_FromByteArrayForSINT;
            entry_points.ToByteArrayForSINT = PMC_ToByteArrayForSINT;
            entry_points.TryParseForSINT = PMC_TryParseForSINT;

            initialized = 1;
        }

        return (&entry_points);
    }

}


/*
 * END OF FILE
 */