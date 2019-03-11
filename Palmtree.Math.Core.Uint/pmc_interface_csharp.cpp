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


#include "pmc_exception.h"
#include "pmc_uint_internal.h"

#define __DLLEXPORT /*__declspec(dllexport)*/

namespace Palmtree::Math::Core::Internal
{

    extern "C" _UINT32_T __DLLEXPORT __PMC_CALL PMCCS_UINT_Initialize(const PMC_CONFIGURATION_INFO* conf)
    {
        _UINT32_T success = PMC_UINT_Initialize(conf) != nullptr ? 1 : 0;
        return (success);
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_IS_EVEN(PMC_HANDLE_UINT p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_IS_ONE(PMC_HANDLE_UINT p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_IS_POWER_OF_TWO(PMC_HANDLE_UINT p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_IS_ZERO(PMC_HANDLE_UINT p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GET_HASH_CODE(PMC_HANDLE_UINT p, _INT32_T* r)
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

    extern "C" void __DLLEXPORT __PMC_CALL PMCCS_GetStatisticsInfo(PMC_STATISTICS_INFO* p)
    {
        PMC_GetStatisticsInfo(p);
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_From_I(_UINT32_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_From_I(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_From_L(_UINT64_T x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_From_L(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Dispose(PMC_HANDLE_UINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_Dispose(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_GetConstantValue_I(type);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_FromByteArray(const unsigned char* buffer, _INT32_T count, PMC_HANDLE_UINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_FromByteArray(buffer, count);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            size_t r = PMC_ToByteArray(p, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Clone_X(PMC_HANDLE_UINT x, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_Clone_X(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GetAllocatedMemorySize(_UINT64_T* size)
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_To_X_I(PMC_HANDLE_UINT p, _UINT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_To_X_I(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_To_X_L(PMC_HANDLE_UINT p, _UINT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_To_X_L(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ToString(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            size_t r = PMC_ToString(x, format, format_option, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Parse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o)
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
        try
        {
            _UINT32_T result;
            PMC_STATUS_CODE err = PMC_TryParse(source, number_styles | PMC_NUMBER_STYLE_ALLOW_EXCEPTION_THROWING, format_option, o, &result);
            if (err != PMC_STATUS_OK)
                return (err);
            if (!result)
            {
                // Ç±ÇÃÉãÅ[ÉgÇ…ìûíBÇ∑ÇÈÇ±Ç∆ÇÕÇ»Ç¢ÇÕÇ∏
                return (PMC_STATUS_INTERNAL_ERROR);
            }
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o, _UINT32_T* result)
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
        try
        {
            PMC_STATUS_CODE err = PMC_TryParse(source, number_styles, format_option, o, result);
            if (err != PMC_STATUS_OK)
                return (err);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Add_I_X(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Add_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Add_L_X(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Add_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Add_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Add_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Add_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Add_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Add_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Add_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Subtruct_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Subtruct_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Subtruct_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Subtruct_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Subtruct_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Subtruct_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Multiply_I_X(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Multiply_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Multiply_L_X(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Multiply_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Multiply_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Multiply_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Multiply_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Multiply_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Multiply_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Multiply_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_DivRem_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_I_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_DivRem_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_L_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_DivRem_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_I(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_DivRem_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_L(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_DivRem_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Remainder_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_I_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Remainder_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_L_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Remainder_X_I(PMC_HANDLE_UINT u, _UINT32_T v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_I(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Remainder_X_L(PMC_HANDLE_UINT u, _UINT64_T v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_L(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Remainder_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_DivRem_X_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_RightShift_X_I(PMC_HANDLE_UINT p, _INT32_T n, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_RightShift_X_I(p, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_LeftShift_X_I(PMC_HANDLE_UINT p, _INT32_T n, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_LeftShift_X_I(p, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseAnd_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseAnd_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseAnd_X_I(PMC_HANDLE_UINT u, _UINT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseAnd_X_L(PMC_HANDLE_UINT u, _UINT64_T v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseAnd_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseAnd_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseOr_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseOr_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseOr_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseOr_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_BitwiseOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_BitwiseOr_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ExclusiveOr_I_X(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_ExclusiveOr_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ExclusiveOr_L_X(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_ExclusiveOr_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ExclusiveOr_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_ExclusiveOr_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ExclusiveOr_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_ExclusiveOr_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ExclusiveOr_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_ExclusiveOr_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Compare_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Compare_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Compare_X_I(PMC_HANDLE_UINT u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Compare_X_L(PMC_HANDLE_UINT u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Compare_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Compare_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Equals_I_X(_UINT32_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Equals_L_X(_UINT64_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Equals_X_I(PMC_HANDLE_UINT u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Equals_X_L(PMC_HANDLE_UINT u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Equals_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_Equals_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GreatestCommonDivisor_I_X(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_GreatestCommonDivisor_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GreatestCommonDivisor_L_X(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_GreatestCommonDivisor_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GreatestCommonDivisor_X_I(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_GreatestCommonDivisor_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GreatestCommonDivisor_X_L(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_GreatestCommonDivisor_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_GreatestCommonDivisor_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *w = PMC_GreatestCommonDivisor_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Pow_X_I(PMC_HANDLE_UINT x, _UINT32_T n, PMC_HANDLE_UINT* v)
    {
        if (v == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *v = PMC_Pow_X_I(x, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Pow_X_L(PMC_HANDLE_UINT x, _UINT64_T n, PMC_HANDLE_UINT* v)
    {
        if (v == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *v = PMC_Pow_X_L(x, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_ModPow_X_X_X(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_ModPow_X_X_X(v, e, m);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_TimesOfExponentOf10(_UINT32_T v, _UINT32_T e, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_TimesOfExponentOf10(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __DLLEXPORT __PMC_CALL PMCCS_Floor_Log10(PMC_HANDLE_UINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Floor_Log10(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

}


/*
 * END OF FILE
 */