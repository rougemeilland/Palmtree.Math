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


#include "pmc_sint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    template<typename HANDLE_T>
    class UsingObject
    {
        HANDLE_T _handle;

    public:
        UsingObject(HANDLE_T handle)
        {
            _handle = handle;
        }

        ~UsingObject()
        {
        }
    };

    template<>
    class UsingObject<PMC_HANDLE_UINT>
    {
        PMC_HANDLE_UINT _handle;

    public:
        UsingObject(PMC_HANDLE_UINT handle)
        {
            _handle = handle;
            ep_uint.UseObject(_handle);
        }

        ~UsingObject()
        {
            ep_uint.UnuseObject(_handle);
        }
    };

    template<>
    class UsingObject<PMC_HANDLE_SINT>
    {
        PMC_HANDLE_SINT _handle;

    public:
        UsingObject(PMC_HANDLE_SINT handle)
        {
            _handle = handle;
            PMC_UseObject_X(_handle);
        }

        ~UsingObject()
        {
            PMC_UnuseObject_X(_handle);
        }
    };

    extern "C" _UINT32_T __stdcall PMCCS_SINT_Initialize()
    {
        return (PMC_SINT_Initialize() ? 1 : 0);
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_EVEN(PMC_HANDLE_SINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_EVEN;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_MINUS_ONE(PMC_HANDLE_SINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_MINUS_ONE;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ONE(PMC_HANDLE_SINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_ONE;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_POWER_OF_TWO(PMC_HANDLE_SINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_POWER_OF_TWO;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ZERO(PMC_HANDLE_SINT p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_ZERO;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetHashCode_X(PMC_HANDLE_SINT p, _INT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = PMC_GetHashCode(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UI(_UINT32_T x, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_From_UI(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_I(_INT32_T x, PMC_HANDLE_SINT* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UL(_UINT64_T x, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_From_UL(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_L(_INT64_T x, PMC_HANDLE_SINT* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UX(PMC_HANDLE_UINT x, PMC_HANDLE_SINT* o)
    {
        if (x == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *o = PMC_From_UX(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_CheckHandle_UX(PMC_HANDLE_UINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_CheckHandle_X(PMC_HANDLE_SINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_CheckHandle_X(p);
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
        try
        {
            PMC_Dispose_UX(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Dispose_X(PMC_HANDLE_SINT p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_Dispose_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type, PMC_HANDLE_SINT* value)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_FromByteArray(const unsigned char* buffer, _INT32_T count, PMC_HANDLE_SINT* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_FromByteArray_SINT(buffer, count);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToByteArray(PMC_HANDLE_SINT p, unsigned char* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            size_t r = PMC_ToByteArray_X(p, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Clone_X(PMC_HANDLE_SINT x, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *o = PMC_Clone_X(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt32_X(PMC_HANDLE_SINT p, _UINT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUInt32_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt32_X(PMC_HANDLE_SINT p, _INT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToInt32_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt64_X(PMC_HANDLE_SINT p, _UINT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUInt64_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt64_X(PMC_HANDLE_SINT p, _INT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToInt64_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUBigInt_X(PMC_HANDLE_SINT p, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUBigInt_X(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToString_X(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            size_t r = PMC_ToString_X(x, format, format_option, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Parse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o)
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
            return (PMC_TryParse_SINT(source, number_styles, format_option, o));
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o)
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
            PMC_STATUS_CODE err = PMC_TryParse_SINT(source, number_styles, format_option, o);
            switch (err)
            {
            case PMC_STATUS_FORMAT_ERROR:
            case PMC_STATUS_OVERFLOW:
                *o = nullptr;
                return (PMC_STATUS_OK);
            default:
                return (err);
            }
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UI_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UL_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_UX_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_UX_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_UX_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_UI_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, _INT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_I_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_UL_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, _INT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_L_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_UX_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_UI(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_I(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_UL(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_L(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_X_UX(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_X_X(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q, _INT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_I_UX(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q, _INT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_L_UX(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* q, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_UX_I(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_DivRem_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* q, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_UX_L(u, v, q);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_UI_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_I_X(_INT32_T u, PMC_HANDLE_SINT v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_I_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_UL_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_L_X(_INT64_T u, PMC_HANDLE_SINT v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_L_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_UX_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_UI(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_I(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_UL(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_X_L(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_X_UX(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *r = PMC_DivRem_X_X(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_I_UX(_INT32_T u, PMC_HANDLE_UINT v, _INT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_I_UX(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_L_UX(_INT64_T u, PMC_HANDLE_UINT v, _INT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_DivRem_L_UX(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_I(PMC_HANDLE_UINT u, _INT32_T v, _UINT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_UX_I(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Remainder_UX_L(PMC_HANDLE_UINT u, _INT64_T v, _UINT64_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *r = PMC_DivRem_UX_L(u, v, nullptr);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_RightShift_X_I(PMC_HANDLE_SINT p, _INT32_T n, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_RightShift_X_I(p, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_LeftShift_X_I(PMC_HANDLE_SINT p, _INT32_T n, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_LeftShift_X_I(p, n);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, _UINT64_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseAnd_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseAnd_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseAnd_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_BitwiseOr_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_BitwiseOr_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_BitwiseOr_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_ExclusiveOr_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ExclusiveOr_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_ExclusiveOr_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_I_X(_INT32_T u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_L_X(_INT64_T u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_I(PMC_HANDLE_SINT u, _INT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_L(PMC_HANDLE_SINT u, _INT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_I_UX(_INT32_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_L_UX(_INT64_T u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_I(PMC_HANDLE_UINT u, _INT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_L(PMC_HANDLE_UINT u, _INT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_I_X(_INT32_T u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_L_X(_INT64_T u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_I(PMC_HANDLE_SINT u, _INT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_L(PMC_HANDLE_SINT u, _INT64_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_I_UX(_INT32_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_L_UX(_INT64_T u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_I(PMC_HANDLE_UINT u, _INT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_L(PMC_HANDLE_UINT u, _INT64_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_UI_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_I_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_UL_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_L_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_UX_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_X_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_X_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_X_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_X_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_X_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_X_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_I_UX(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_I_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_L_UX(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_GreatestCommonDivisor_L_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_I(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_UX_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GreatestCommonDivisor_UX_L(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_GreatestCommonDivisor_UX_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Abs_X(PMC_HANDLE_SINT u, PMC_HANDLE_UINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Abs_X(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Negate_UX(PMC_HANDLE_UINT u, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Negate_UX(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Negate_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Negate_X(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_OneComplement_UX(PMC_HANDLE_UINT u, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_OneComplement_UX(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_OneComplement_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_OneComplement_X(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Increment_X(PMC_HANDLE_SINT x, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Increment_X(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Decrement_X(PMC_HANDLE_SINT x, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Decrement_X(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }


    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_I_UI(_INT32_T v, _UINT32_T e, PMC_HANDLE_SINT* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_I_UI(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_L_UI(_INT64_T v, _UINT32_T e, PMC_HANDLE_SINT* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_L_UI(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_X_UI(PMC_HANDLE_SINT v, _UINT32_T e, PMC_HANDLE_SINT* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Pow_X_UI(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
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

}


/*
 * END OF FILE
 */