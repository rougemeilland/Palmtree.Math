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


#include "pmc_uint_internal.h"
#include "pmc_threadcontext.h"

namespace Palmtree::Math::Core::Internal
{

    extern "C" _UINT32_T __stdcall PMCCS_UINT_Initialize()
    {
        return (PMC_UINT_Initialize() ? 1 : 0);
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_EVEN(PMC_HANDLE_UINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = p->FLAGS.IS_EVEN;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ONE(PMC_HANDLE_UINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = p->FLAGS.IS_ONE;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_POWER_OF_TWO(PMC_HANDLE_UINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = p->FLAGS.IS_POWER_OF_TWO;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ZERO(PMC_HANDLE_UINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = p->FLAGS.IS_ZERO;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GET_HASH_CODE(PMC_HANDLE_UINT p, _INT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = (_INT32_T)p->HASH_CODE;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_I(_INT32_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_From_UI(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_L(_INT64_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_From_UL(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UI(_UINT32_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_From_UI(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UL(_UINT64_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_From_UL(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_CheckHandle_UX(PMC_HANDLE_UINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            PMC_CheckHandle_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Dispose_UX(PMC_HANDLE_UINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            _INT32_T count = PMC_GetBufferCount_UX(p);
            PMC_Dispose_UX(tc, p);
            tc.VerifyAllocationCount(-count, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_GetConstantValue_UI(type);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetDefaultRoundingMode(PMC_MIDPOINT_ROUNDING_CODE* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_GetDefaultRoundingMode();
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_SetDefaultRoundingMode(PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        try
        {
            PMC_SetDefaultRoundingMode(mode);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_FromByteArray(const unsigned char* buffer, _INT32_T count, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *value = PMC_FromByteArray_UINT(tc, buffer, count);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*value), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            size_t r = PMC_ToByteArray_UX(p, buffer, buffer_size);
            if (r > 0x7fffffff)
                return (PMC_STATUS_NOT_ENOUGH_MEMORY);
            *size = (_INT32_T)r;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Clone_UX(PMC_HANDLE_UINT x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_Clone_UX(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetAllocatedMemorySize(_UINT64_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *size = PMC_GetAllocatedMemorySize();
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt32_UX(PMC_HANDLE_UINT p, _INT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_ToInt32_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt64_UX(PMC_HANDLE_UINT p, _INT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_ToInt64_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt32_UX(PMC_HANDLE_UINT p, _UINT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_ToUInt32_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt64_UX(PMC_HANDLE_UINT p, _UINT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_ToUInt64_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToString_UX(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            size_t r = PMC_ToString_UX(tc, x, format, format_option, buffer, buffer_size);
            if (r > 0x7fffffff)
            {
                tc.VerifyAllocationCount(0, true);
                return (PMC_STATUS_NOT_ENOUGH_MEMORY);
            }
            *size = (_INT32_T)r;
            tc.VerifyAllocationCount(0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Parse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o)
    {
        const PMC_NUMBER_STYLE_CODE all_styles = 
            PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE |
            PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE |
            PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN |
            PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN |
            PMC_NUMBER_STYLE_ALLOW_PARENTHESES |
            PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT |
            PMC_NUMBER_STYLE_ALLOW_THOUSANDS |
            PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL |
            PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER;
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (number_styles & ~all_styles)
            return (PMC_STATUS_ARGUMENT_ERROR);
        ThreadContext tc;
        try
        {
            PMC_STATUS_CODE result = PMC_TryParse_UINT(tc, source, number_styles, format_option, o);
            if (result == PMC_STATUS_OK)
                tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            else
                tc.VerifyAllocationCount(0, true);
            return (result);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o)
    {
        const PMC_NUMBER_STYLE_CODE all_styles =
            PMC_NUMBER_STYLE_ALLOW_LEADING_WHITE |
            PMC_NUMBER_STYLE_ALLOW_TRAILING_WHITE |
            PMC_NUMBER_STYLE_ALLOW_LEADING_SIGN |
            PMC_NUMBER_STYLE_ALLOW_TRAILING_SIGN |
            PMC_NUMBER_STYLE_ALLOW_PARENTHESES |
            PMC_NUMBER_STYLE_ALLOW_DECIMAL_POINT |
            PMC_NUMBER_STYLE_ALLOW_THOUSANDS |
            PMC_NUMBER_STYLE_ALLOW_CURRENCY_SYMBOL |
            PMC_NUMBER_STYLE_ALLOW_HEX_SPECIFIER;
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (number_styles & ~all_styles)
            return (PMC_STATUS_ARGUMENT_ERROR);
        ThreadContext tc;
        try
        {
            PMC_STATUS_CODE err = PMC_TryParse_UINT(tc, source, number_styles, format_option, o);
            switch (err)
            {
            case PMC_STATUS_FORMAT_ERROR:
            case PMC_STATUS_OVERFLOW:
                *o = nullptr;
                tc.VerifyAllocationCount(0, true);
                return (PMC_STATUS_OK);
            default:
                tc.VerifyAllocationCount(0, true);
                return (err);
            case PMC_STATUS_OK:
                tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
                return (err);
            }
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Add_UI_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Add_UL_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Add_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Add_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Add_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_UI_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_UL_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Subtruct_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Subtruct_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Subtruct_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Multiply_UI_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Multiply_UL_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Multiply_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Multiply_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Multiply_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_UI_UX(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_UL_UX(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UI(tc, u, v, q);
            tc.VerifyAllocationCount(q != nullptr ? PMC_GetBufferCount_UX(*q) : 0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UL(tc, u, v, q);
            tc.VerifyAllocationCount(q != nullptr ? PMC_GetBufferCount_UX(*q) : 0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UX(tc, u, v, q);
            tc.VerifyAllocationCount((q != nullptr ? PMC_GetBufferCount_UX(*q) : 0) + PMC_GetBufferCount_UX(*r), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_UI_UX(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_UL_UX(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UI(tc, u, v, nullptr);
            tc.VerifyAllocationCount(0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UL(tc, u, v, nullptr);
            tc.VerifyAllocationCount(0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_DivRem_UX_UX(tc, u, v, nullptr);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*r), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_RightShift_UX_I(PMC_HANDLE_UINT p, _INT32_T n, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_RightShift_UX_I(tc, p, n);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_LeftShift_UX_I(PMC_HANDLE_UINT p, _INT32_T n, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *o = PMC_LeftShift_UX_I(tc, p, n);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*o), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_UI_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_UL_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_UX_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_UX_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseAnd_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseOr_UI_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseOr_UL_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseOr_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseOr_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_BitwiseOr_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_ExclusiveOr_UI_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_ExclusiveOr_UL_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_ExclusiveOr_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_ExclusiveOr_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_ExclusiveOr_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_UI_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_Compare_UL_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_UX_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_UX_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_UX_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_UI_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_UL_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_UX_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_UX_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_UX_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_GreatestCommonDivisor_UI_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_GreatestCommonDivisor_UL_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_GreatestCommonDivisor_UX_UI(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_GreatestCommonDivisor_UX_UL(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *w = PMC_GreatestCommonDivisor_UX_UX(tc, u, v);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*w), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UI_UI(_UINT32_T x, _UINT32_T n, PMC_HANDLE_UINT* v)
    {
        if (v == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *v = PMC_Pow_UI_UI(tc, x, n);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*v), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UL_UI(_UINT64_T x, _UINT32_T n, PMC_HANDLE_UINT* v)
    {
        if (v == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *v = PMC_Pow_UL_UI(tc, x, n);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*v), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UX_UI(PMC_HANDLE_UINT x, _UINT32_T n, PMC_HANDLE_UINT* v)
    {
        if (v == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *v = PMC_Pow_UX_UI(tc, x, n);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*v), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ModPow_UX_UX_UX(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_ModPow_UX_UX_UX(tc, v, e, m);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*r), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_FloorLog10_UX(PMC_HANDLE_UINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_FloorLog10_UX(tc, v);
            tc.VerifyAllocationCount(0, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Increment_UX(PMC_HANDLE_UINT x, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_Increment_UX(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*r), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Decrement_UX(PMC_HANDLE_UINT x, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *r = PMC_Decrement_UX(tc, x);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*r), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetPerformanceCounter(const wchar_t* key, _INT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_GetPerformanceCounter(key);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_AllocateRandomStateObjectFromUInt32(_UINT32_T seed, PMC_HANDLE_SFMT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *value = PMC_AllocateRandomStateObjectFromUInt32(tc, seed);
            tc.VerifyAllocationCount(PMC_GetBufferCount_SFMT(*value), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_AllocateRandomStateObjectFromUInt32Array(_UINT32_T* init_key, _INT32_T key_length, PMC_HANDLE_SFMT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *value = PMC_AllocateRandomStateObjectFromUInt32Array(tc, init_key, key_length);
            tc.VerifyAllocationCount(PMC_GetBufferCount_SFMT(*value), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_CheckHandle_SFMT(PMC_HANDLE_SFMT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_CheckHandle_SFMT(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Dispose_SFMT(PMC_HANDLE_SFMT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            _INT32_T count = PMC_GetBufferCount_SFMT(p);
            PMC_Dispose_SFMT(tc, p);
            tc.VerifyAllocationCount(-count, true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GenerateUInt32RandomValue(PMC_HANDLE_SFMT p, _UINT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_GenerateUInt32RandomValue(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GenerateUInt64RandomValue(PMC_HANDLE_SFMT p, _UINT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_GenerateUInt64RandomValue(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GenerateDoubleRandomValue(PMC_HANDLE_SFMT p, double* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_GenerateDoubleRandomValue(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GenerateUBigIntRandomValue(PMC_HANDLE_SFMT handle, _INT32_T bit_count, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *value = PMC_GenerateUBigIntRandomValue(tc, handle, bit_count);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*value), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GenerateUBigIntCryptoRandomValue(_BYTE_T* data, _INT32_T bit_count, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        ThreadContext tc;
        try
        {
            *value = PMC_GenerateUBigIntCryptoRandomValue(tc, data, bit_count);
            tc.VerifyAllocationCount(PMC_GetBufferCount_UX(*value), true);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

}


/*
 * END OF FILE
 */