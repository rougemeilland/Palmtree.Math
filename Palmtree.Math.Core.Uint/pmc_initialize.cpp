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
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
    PMC_CONFIGURATION_INFO configuration_info;
    //static PMC_UINT_ENTRY_POINTS entry_points;
    static bool initialized = false;
#pragma endregion

    PMC_STATUS_CODE PMC_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
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
        else if (lstrcmpW(key, L"TABLESIZE") == 0)
        {
            wchar_t value[32];
            wsprintfW(value, L"%d", sizeof(NUMBER_OBJECT_UINT));
            int count_of_value = lstrlenW(value) + 1;
            if (value_buffer != nullptr)
            {
                if (value_buffer_size < count_of_value)
                    return (PMC_STATUS_INSUFFICIENT_BUFFER);
                lstrcpyW(value_buffer, value);
            }
            *count = count_of_value;
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
        NUMBER_OBJECT_UINT nh;
        PMC_HANDLE_UINT handle = (PMC_HANDLE_UINT)&nh;

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.HASH_CODE = 0x12345678;
        if (handle->HASH_CODE != 0x12345678)
            return (FALSE);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_STATIC = TRUE;
        if (!handle->FLAGS.IS_STATIC)
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

    bool PMC_UINT_Initialize()
    {
        if (!initialized)
        {
            if (!SelfCheck())
                return (false);

            PROCESSOR_FEATURES feature;
            GetCPUInfo(&feature);
            _ZERO_MEMORY_BYTE(&configuration_info, sizeof(configuration_info));
            configuration_info.MEMORY_VERIFICATION_ENABLED = true;
            if (Initialize_Memory(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_From(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_To(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Add(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Subtruct(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Multiply(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_DivRem(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Shift(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_BitwiseAnd(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_BitwiseOr(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_ExclusiveOr(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Compare(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Equals(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_ToString(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Parse(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_GreatestCommonDivisor(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Pow(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_ModPow(&feature) != PMC_STATUS_OK)
                return (false);
            if (Initialize_Log(&feature) != PMC_STATUS_OK)
                return (false);

            initialized = true;
        }

        return (true);
    }

}


/*
 * END OF FILE
 */