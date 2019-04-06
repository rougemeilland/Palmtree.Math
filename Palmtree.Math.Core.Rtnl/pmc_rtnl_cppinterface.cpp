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


#include "pmc_rtnl_internal.h"
#include "pmc_rtnl_cppinterface.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_RTNL_CppInterface::PMC_RTNL_CppInterface()
    {
    }

    PMC_RTNL_CppInterface::~PMC_RTNL_CppInterface()
    {
    }

    bool PMC_RTNL_CppInterface::Initialize()
    {
        return (PMC_RTNL_Initialize());
    }

    void PMC_RTNL_CppInterface::UseObject(PMC_HANDLE_RTNL x) noexcept(false)
    {
        PMC_UseObject_R(x);
    }

    void PMC_RTNL_CppInterface::UnuseObject(PMC_HANDLE_RTNL x) noexcept(false)
    {
        PMC_UnuseObject_R(x);
    }

    PMC_STATUS_CODE PMC_RTNL_CppInterface::GetConfigurationSettings(const wchar_t * key, wchar_t * value_buffer, _INT32_T value_buffer_size, _INT32_T * count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(_UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(_INT32_T x) noexcept(false)
    {
        return (PMC_From_I(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(_UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(_INT64_T x) noexcept(false)
    {
        return (PMC_From_L(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_From_UX(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_From_X(x));
    }

    _INT32_T PMC_RTNL_CppInterface::GetHashCode(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_GetHashCode(p));
    }

    void PMC_RTNL_CppInterface::CheckHandle(PMC_HANDLE_UINT p)
    {
        PMC_CheckHandle_UX(p);
    }

    void PMC_RTNL_CppInterface::CheckHandle(PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_CheckHandle_X(p);
    }

    void PMC_RTNL_CppInterface::CheckHandle(PMC_HANDLE_RTNL p) noexcept(false)
    {
        PMC_CheckHandle_R(p);
    }

    void PMC_RTNL_CppInterface::Dispose(PMC_HANDLE_UINT p)
    {
        PMC_Dispose_UX(p);
    }

    void PMC_RTNL_CppInterface::Dispose(PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_Dispose_X(p);
    }

    void PMC_RTNL_CppInterface::Dispose(PMC_HANDLE_RTNL p) noexcept(false)
    {
        PMC_Dispose_R(p);
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_I(type));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::FromByteArray(const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray(buffer, count));
    }

    size_t PMC_RTNL_CppInterface::ToByteArray(PMC_HANDLE_RTNL p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray(p, buffer, buffer_size));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Clone(PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Clone_R(x));
    }

    _UINT64_T PMC_RTNL_CppInterface::GetAllocatedMemorySize()
    {
        return (PMC_GetAllocatedMemorySize());
    }

    _UINT32_T PMC_RTNL_CppInterface::ToUInt32(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUInt32_R(p));
    }

    _INT32_T PMC_RTNL_CppInterface::ToInt32(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToInt32_R(p));
    }

    _UINT64_T PMC_RTNL_CppInterface::ToUInt64(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUInt64_R(p));
    }

    _INT64_T PMC_RTNL_CppInterface::ToInt64(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToInt64_R(p));
    }

    PMC_HANDLE_UINT PMC_RTNL_CppInterface::ToUBigInt(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUBigInt_R(p));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::ToBigInt(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToBigInt_R(p));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Negate(PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Negate_R(x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Abs(PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Abs_R(x));
    }

    size_t PMC_RTNL_CppInterface::ToString(PMC_HANDLE_RTNL x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_R(x, format, format_option, buffer, buffer_size));
    }

    void PMC_RTNL_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    PMC_STATUS_CODE PMC_RTNL_CppInterface::TryParse(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_RTNL * o) noexcept(false)
    {
        return (PMC_TryParse(source, number_styles, format_option, o));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UI_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_I_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UL_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_L_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_X_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UX_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_R_UI(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_R_I(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_R_UL(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_R_L(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_R_X(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_R_UX(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_R_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UI_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_I_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UL_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_L_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_X_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UX_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_UI(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_I(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_UL(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_L(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_R_X(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_R_UX(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_R_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UI_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_I_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UL_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_L_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_X_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UX_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_R_UI(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_R_I(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_R_UL(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_R_L(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_R_X(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_R_UX(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_R_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UI_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_I_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UL_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_L_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_X_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UX_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Divide_R_UI(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Divide_R_I(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Divide_R_UL(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Divide_R_L(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Divide_R_X(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Divide_R_UX(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_R_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UI_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_I_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UL_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_L_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_X_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UX_R(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Compare_R_UI(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Compare_R_I(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Compare_R_UL(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Compare_R_L(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_R_X(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_R_UX(u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_R_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_UI_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_I_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_UL_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_L_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_X_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_UX_R(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Equals_R_UI(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Equals_R_I(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Equals_R_UL(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Equals_R_L(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_R_X(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_R_UX(u, v));
    }

    bool PMC_RTNL_CppInterface::Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Equals_R_R(u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(_INT32_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_I_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(_INT64_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_L_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(PMC_HANDLE_SINT v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_X_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(_UINT32_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UI_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(_UINT64_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UL_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(PMC_HANDLE_UINT v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UX_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(PMC_HANDLE_RTNL v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_R_I(v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(_INT32_T v) noexcept(false)
    {
        return (PMC_Invert_I(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(_INT64_T v) noexcept(false)
    {
        return (PMC_Invert_L(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Invert_X(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(_UINT32_T v) noexcept(false)
    {
        return (PMC_Invert_UI(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(_UINT64_T v) noexcept(false)
    {
        return (PMC_Invert_UL(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Invert_UX(v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Invert_R(v));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Round(PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_Round_R(x, mode));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Round(PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_Round_R_I(x, decimals, mode));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Floor(PMC_HANDLE_RTNL x)
    {
        return (PMC_Floor_R(x));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Ceiling(PMC_HANDLE_RTNL x)
    {
        return (PMC_Ceiling_R(x));
    }

    _INT32_T PMC_RTNL_CppInterface::FloorLog10(PMC_HANDLE_RTNL v)
    {
        return (PMC_FloorLog10_R(v));
    }

}


/*
 * END OF FILE
 */