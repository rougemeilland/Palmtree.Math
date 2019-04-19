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


#include <windows.h>
#include <intrin.h>
#include <immintrin.h>
#include "pmc_sint_internal.h"
#include "pmc_uint_cppinterface.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

#pragma region 静的変数の定義
    PMC_UINT_CppInterface ep_uint;
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
        else if (lstrcmpW(key, L"CONFIG") == 0)
        {
#ifdef _DEBUG
            const wchar_t value[] = L"DEBUG";
#else
            const wchar_t value[] = L"RELEASE";
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
            wsprintfW(value, L"%d:%d", sizeof(NUMBER_OBJECT_SINT), sizeof(SIGN_T));
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

    static bool SelfCheck()
    {
        NUMBER_OBJECT_SINT nh;
        PMC_HANDLE_SINT handle = (PMC_HANDLE_SINT)&nh;

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_SHARED = TRUE;
        if (!handle->FLAGS.IS_SHARED)
            return (false);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_EVEN = TRUE;
        if (!handle->FLAGS.IS_EVEN)
            return (false);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_MINUS_ONE = TRUE;
        if (!handle->FLAGS.IS_MINUS_ONE)
            return (false);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_ONE = TRUE;
        if (!handle->FLAGS.IS_ONE)
            return (false);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_POWER_OF_TWO = TRUE;
        if (!handle->FLAGS.IS_POWER_OF_TWO)
            return (false);

        _ZERO_MEMORY_BYTE(&nh, sizeof(nh));
        nh.IS_ZERO = TRUE;
        if (!handle->FLAGS.IS_ZERO)
            return (false);

        return(true);
    }

    bool PMC_SINT_Initialize()
    {
        if (!initialized)
        {
            if (!SelfCheck())
                return (false);

            if (!ep_uint.Initialize())
                return (false);

            if (Initialize_Memory() != PMC_STATUS_OK)
                return (false);

            initialized = true;
        }

        return (true);
    }

}


/*
 * END OF FILE
 */