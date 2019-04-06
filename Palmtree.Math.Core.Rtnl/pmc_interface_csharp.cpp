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


//#define SEH_TRACE

#include "pmc_rtnl_internal.h"
#ifdef SEH_TRACE
#include <iostream>
#endif


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
            ep_sint.UseObject(_handle);
        }

        ~UsingObject()
        {
            ep_sint.UnuseObject(_handle);
        }
    };

    template<>
    class UsingObject<PMC_HANDLE_RTNL>
    {
        PMC_HANDLE_RTNL _handle;

    public:
        UsingObject(PMC_HANDLE_RTNL handle)
        {
            _handle = handle;
            PMC_UseObject_R(_handle);
        }

        ~UsingObject()
        {
            PMC_UnuseObject_R(_handle);
        }
};

#ifdef SEH_TRACE
    static void __OUTPUT_DEBUG_STRING(const char* str)
    {
        //::OutputDebugStringW(str);
        std::cout << str << std::endl;
    }
#endif

    static LONG DumpSEHInfo(_EXCEPTION_POINTERS *ep)
    {
#ifdef SEH_TRACE
        PEXCEPTION_RECORD rec = ep->ExceptionRecord;

        char buf[1024];
        if (rec->ExceptionCode == EXCEPTION_ACCESS_VIOLATION && rec->NumberParameters >= 2)
        {
            wsprintfA(buf, "%pへの%s中にアクセス違反を検出しました。: 実行時アドレス=%p\n", rec->ExceptionInformation[1], rec->ExceptionInformation[0] ? "書き込み" : "読み込み", rec->ExceptionAddress);
            __OUTPUT_DEBUG_STRING(buf);
            for (DWORD index = 2; index < rec->NumberParameters; index++)
            {
                wsprintfA(buf, "  param[%d]=%x\n", index, rec->ExceptionInformation[index]);
                __OUTPUT_DEBUG_STRING(buf);
            }
        }
        else if (rec->ExceptionCode == 0xe06d7363)
        {
            // nop
        }
        else
        {
            wsprintfA(buf, "例外を検出しました。: code=%x flag=%x addr=%p params=%d\n", rec->ExceptionCode, rec->ExceptionFlags, rec->ExceptionAddress, rec->NumberParameters);
            __OUTPUT_DEBUG_STRING(buf);
            for (DWORD index = 0; index < rec->NumberParameters; index++)
            {
                wsprintfA(buf, "  param[%d]=%x\n", index, rec->ExceptionInformation[index]);
                __OUTPUT_DEBUG_STRING(buf);
            }
        }
#endif

        return (EXCEPTION_CONTINUE_SEARCH);
    }

    extern "C" _UINT32_T __stdcall PMCCS_RTNL_Initialize()
    {
        return (PMC_RTNL_Initialize() ? 1 : 0);
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_INT(PMC_HANDLE_RTNL p, _UINT32_T* r)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *r = p->FLAGS.IS_INT;
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_MINUS_ONE(PMC_HANDLE_RTNL p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ONE(PMC_HANDLE_RTNL p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_IS_ZERO(PMC_HANDLE_RTNL p, _UINT32_T* r)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetHashCode_R(PMC_HANDLE_RTNL p, _INT32_T* r)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_I(_INT32_T x, PMC_HANDLE_RTNL* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_L(_INT64_T x, PMC_HANDLE_RTNL* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_X(PMC_HANDLE_SINT x, PMC_HANDLE_RTNL* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *o = PMC_From_X(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UI(_UINT32_T x, PMC_HANDLE_RTNL* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UL(_UINT64_T x, PMC_HANDLE_RTNL* o)
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_From_UX(PMC_HANDLE_UINT x, PMC_HANDLE_RTNL* o)
    {
        if (x == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(x);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_CheckHandle_R(PMC_HANDLE_RTNL p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_CheckHandle_R(p);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Dispose_R(PMC_HANDLE_RTNL p)
    {
        if (p == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            PMC_Dispose_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_GetConstantValue_I(PMC_CONSTANT_VALUE_CODE type, PMC_HANDLE_RTNL* value)
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

    static PMC_HANDLE_RTNL PMC_FromByteArray_SEH(const unsigned char* buffer, _INT32_T count)
    {
#ifdef _MSC_VER
        __try
        {
            return (PMC_FromByteArray(buffer, count));
        }
        __except (DumpSEHInfo(GetExceptionInformation()))
        {
            throw SEHException(L"ハードウェア例外を検出しました。");
        }
#else
        return (PMC_FromByteArray(buffer, count));
#endif
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_FromByteArray(const unsigned char* buffer, _INT32_T count, PMC_HANDLE_RTNL* value)
    {
        if (value == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *value = PMC_FromByteArray_SEH(buffer, count);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    static size_t PMC_ToByteArray_SEH(PMC_HANDLE_RTNL p, unsigned char* buffer, _INT32_T buffer_size)
    {
#ifdef _MSC_VER
        __try
        {
            return (PMC_ToByteArray(p, buffer, buffer_size));
        }
        __except (DumpSEHInfo(GetExceptionInformation()))
        {
            throw SEHException(L"ハードウェア例外を検出しました。");
        }
#else
        return (PMC_ToByteArray(p, buffer, buffer_size));
#endif
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToByteArray(PMC_HANDLE_RTNL p, unsigned char* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            size_t r = PMC_ToByteArray_SEH(p, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Clone_R(PMC_HANDLE_RTNL x, PMC_HANDLE_RTNL* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *o = PMC_Clone_R(x);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt32_R(PMC_HANDLE_RTNL p, _INT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToInt32_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToInt64_R(PMC_HANDLE_RTNL p, _INT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToInt64_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToBigInt_R(PMC_HANDLE_RTNL p, PMC_HANDLE_SINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToBigInt_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt32_R(PMC_HANDLE_RTNL p, _UINT32_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUInt32_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUInt64_R(PMC_HANDLE_RTNL p, _UINT64_T* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUInt64_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToUBigInt_R(PMC_HANDLE_RTNL p, PMC_HANDLE_UINT* o)
    {
        if (o == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_p(p);
            *o = PMC_ToUBigInt_R(p);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_ToString_R(PMC_HANDLE_RTNL x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, _INT32_T buffer_size, _INT32_T* size)
    {
        if (size == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            size_t r = PMC_ToString_R(x, format, format_option, buffer, buffer_size);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Parse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_RTNL* o)
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
            return (PMC_TryParse(source, number_styles, format_option, o));
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_RTNL* o)
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
            PMC_STATUS_CODE err = PMC_TryParse(source, number_styles, format_option, o);
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

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_I_R(_INT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_L_R(_INT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Add_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_I(PMC_HANDLE_RTNL u, _INT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_L(PMC_HANDLE_RTNL u, _INT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Add_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Add_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Add_R_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_I_R(_INT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_L_R(_INT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Subtruct_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_I(PMC_HANDLE_RTNL u, _INT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_L(PMC_HANDLE_RTNL u, _INT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Subtruct_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Subtruct_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Subtruct_R_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_I_R(_INT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_L_R(_INT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Multiply_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_I(PMC_HANDLE_RTNL u, _INT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_L(PMC_HANDLE_RTNL u, _INT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Multiply_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    static PMC_HANDLE_RTNL PMC_Multiply_R_R_SEH(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v)
    {
#ifdef _MSC_VER
        __try
        {
            return (PMC_Multiply_R_R(u, v));
        }
        __except (DumpSEHInfo(GetExceptionInformation()))
        {
            throw SEHException(L"ハードウェア例外を検出しました。");
        }
#else
        return (PMC_Multiply_R_R(u, v));
#endif
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Multiply_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Multiply_R_R_SEH(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_I_R(_INT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Divide_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_L_R(_INT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Divide_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Divide_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Divide_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Divide_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Divide_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_I(PMC_HANDLE_RTNL u, _INT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Divide_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_L(PMC_HANDLE_RTNL u, _INT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Divide_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Divide_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Divide_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Divide_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Divide_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Divide_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Divide_R_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_I_R(_INT32_T u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_L_R(_INT64_T u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Compare_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_I(PMC_HANDLE_RTNL u, _INT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_L(PMC_HANDLE_RTNL u, _INT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Compare_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    static _INT32_T PMC_Compare_R_R_SEH(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v)
    {
#ifdef _MSC_VER
        __try
        {
            return (PMC_Compare_R_R(u, v));
        }
        __except (DumpSEHInfo(GetExceptionInformation()))
        {
            throw SEHException(L"ハードウェア例外を検出しました。");
        }
#else
        return (PMC_Compare_R_R(u, v));
#endif
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Compare_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, _INT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Compare_R_R_SEH(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_I_R(_INT32_T u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_I_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_L_R(_INT64_T u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_L_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_X_R(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_X_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UI_R(_UINT32_T u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_UI_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UL_R(_UINT64_T u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *w = PMC_Equals_UL_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_UX_R(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_UX_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_I(PMC_HANDLE_RTNL u, _INT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_R_I(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_L(PMC_HANDLE_RTNL u, _INT64_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_R_L(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_X(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_R_X(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_UI(PMC_HANDLE_RTNL u, _UINT32_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_R_UI(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_UL(PMC_HANDLE_RTNL u, _UINT64_T v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Equals_R_UL(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_UX(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_R_UX(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Equals_R_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v, _UINT32_T* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            UsingObject using_v(v);
            *w = PMC_Equals_R_R(u, v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Abs_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Abs_R(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Negate_R(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL* w)
    {
        if (w == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_u(u);
            *w = PMC_Negate_R(u);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_I_I(_INT32_T v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_I_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }
    
    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_L_I(_INT64_T v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_L_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_X_I(PMC_HANDLE_SINT v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Pow_X_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UI_I(_UINT32_T v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_UI_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UL_I(_UINT64_T v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Pow_UL_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_UX_I(PMC_HANDLE_UINT v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Pow_UX_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Pow_R_I(PMC_HANDLE_RTNL v, _INT32_T e, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Pow_R_I(v, e);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_I(_INT32_T v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Invert_I(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_L(_INT64_T v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Invert_L(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_X(PMC_HANDLE_SINT v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Invert_X(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_UI(_UINT32_T v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Invert_UI(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_UL(_UINT64_T v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            *r = PMC_Invert_UL(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_UX(PMC_HANDLE_UINT v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Invert_UX(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Invert_R(PMC_HANDLE_RTNL v, PMC_HANDLE_RTNL* r) noexcept(false)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_Invert_R(v);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Round_R(PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Round_R(x, mode);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Round_R_I(PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_RTNL* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Round_R_I(x, decimals, mode);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Floor_R(PMC_HANDLE_RTNL x, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Floor_R(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_Ceiling_R(PMC_HANDLE_RTNL x, PMC_HANDLE_SINT* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_x(x);
            *r = PMC_Ceiling_R(x);
            return (PMC_STATUS_OK);
        }
        catch (const Palmtree::Math::Core::Internal::Exception& ex)
        {
            return (ex.GetStatusCode());
        }
    }

    extern "C" PMC_STATUS_CODE __stdcall PMCCS_FloorLog10_R(PMC_HANDLE_RTNL v, _INT32_T* r)
    {
        if (r == nullptr)
            return (PMC_STATUS_ARGUMENT_NULL_ERROR);
        try
        {
            UsingObject using_v(v);
            *r = PMC_FloorLog10_R(v);
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