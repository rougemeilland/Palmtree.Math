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

    PMC_STATUS_CODE PMC_RTNL_CppInterface::GetConfigurationSettings(const wchar_t * key, wchar_t * value_buffer, _INT32_T value_buffer_size, _INT32_T * count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, _UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, _INT32_T x) noexcept(false)
    {
        return (PMC_From_I(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, _UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, _INT64_T x) noexcept(false)
    {
        return (PMC_From_L(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_From_UX(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::From(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_From_X(tc, x));
    }

    _INT32_T PMC_RTNL_CppInterface::GetHashCode(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_GetHashCode(p));
    }

    void PMC_RTNL_CppInterface::CheckHandle(PMC_HANDLE_RTNL p) noexcept(false)
    {
        PMC_CheckHandle_R(p);
    }

    void PMC_RTNL_CppInterface::Dispose(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        PMC_Dispose_R(tc, p);
    }

    _INT32_T PMC_RTNL_CppInterface::GetBufferCount(PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_GetBufferCount_R(p));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_I(type));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::FromByteArray_RTNL(ThreadContext& tc, const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray_RTNL(tc, buffer, count));
    }

    size_t PMC_RTNL_CppInterface::ToByteArray(PMC_HANDLE_RTNL p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_R(p, buffer, buffer_size));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Clone(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Clone_R(tc, x));
    }

    _UINT32_T PMC_RTNL_CppInterface::ToUInt32(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUInt32_R(tc, p));
    }

    _INT32_T PMC_RTNL_CppInterface::ToInt32(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToInt32_R(tc, p));
    }

    _UINT64_T PMC_RTNL_CppInterface::ToUInt64(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUInt64_R(tc, p));
    }

    _INT64_T PMC_RTNL_CppInterface::ToInt64(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToInt64_R(tc, p));
    }

    PMC_HANDLE_UINT PMC_RTNL_CppInterface::ToUBigInt(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToUBigInt_R(tc, p));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::ToBigInt(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false)
    {
        return (PMC_ToBigInt_R(tc, p));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Negate(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Negate_R(tc, x));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Abs(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false)
    {
        return (PMC_Abs_R(tc, x));
    }

    size_t PMC_RTNL_CppInterface::ToString(ThreadContext& tc, PMC_HANDLE_RTNL x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_R(tc, x, format, format_option, buffer, buffer_size));
    }

    void PMC_RTNL_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    PMC_STATUS_CODE PMC_RTNL_CppInterface::TryParse_RTNL(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_RTNL * o) noexcept(false)
    {
        return (PMC_TryParse_RTNL(tc, source, number_styles, format_option, o));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UI_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_I_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UL_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_L_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_X_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_UX_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_R_UI(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_R_I(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_R_UL(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_R_L(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_R_X(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_R_UX(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Add_R_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UI_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_I_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UL_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_L_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_X_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_UX_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_UI(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_I(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_UL(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_R_L(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_R_X(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_R_UX(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Subtruct_R_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UI_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_I_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UL_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_L_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_X_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_UX_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_R_UI(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_R_I(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_R_UL(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_R_L(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_R_X(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_R_UX(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Multiply_R_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UI_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_I_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UL_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_L_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_X_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_UX_R(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Divide_R_UI(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Divide_R_I(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Divide_R_UL(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Divide_R_L(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Divide_R_X(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Divide_R_UX(tc, u, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Divide_R_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UI_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_I_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UL_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_L_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_X_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_UX_R(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Compare_R_UI(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false)
    {
        return (PMC_Compare_R_I(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Compare_R_UL(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false)
    {
        return (PMC_Compare_R_L(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_R_X(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_R_UX(tc, u, v));
    }

    SIGN_T PMC_RTNL_CppInterface::Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Compare_R_R(tc, u, v));
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

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, _INT32_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_I_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, _INT64_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_L_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_X_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, _UINT32_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UI_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, _UINT64_T v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UL_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_UX_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_RTNL v, _INT32_T e) noexcept(false)
    {
        return (PMC_Pow_R_I(tc, v, e));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, _INT32_T v) noexcept(false)
    {
        return (PMC_Invert_I(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, _INT64_T v) noexcept(false)
    {
        return (PMC_Invert_L(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Invert_X(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, _UINT32_T v) noexcept(false)
    {
        return (PMC_Invert_UI(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, _UINT64_T v) noexcept(false)
    {
        return (PMC_Invert_UL(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Invert_UX(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_RTNL v) noexcept(false)
    {
        return (PMC_Invert_R(tc, v));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Round(ThreadContext& tc, PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_Round_R(tc, x, mode));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::Round(ThreadContext& tc, PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_Round_R_I(tc, x, decimals, mode));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Floor(ThreadContext& tc, PMC_HANDLE_RTNL x)
    {
        return (PMC_Floor_R(tc, x));
    }

    PMC_HANDLE_SINT PMC_RTNL_CppInterface::Ceiling(ThreadContext& tc, PMC_HANDLE_RTNL x)
    {
        return (PMC_Ceiling_R(tc, x));
    }

    _INT32_T PMC_RTNL_CppInterface::FloorLog10(ThreadContext& tc, PMC_HANDLE_RTNL v)
    {
        return (PMC_FloorLog10_R(tc, v));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::GenerateRationalRandomValue(ThreadContext & tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        return (PMC_GenerateRationalRandomValue(tc, handle, bit_count));
    }

    PMC_HANDLE_RTNL PMC_RTNL_CppInterface::GenerateRationalCryptoRandomValue(ThreadContext & tc, _BYTE_T * data, _INT32_T bit_count)
    {
        return (PMC_GenerateRationalCryptoRandomValue(tc, data, bit_count));
    }

}


/*
 * END OF FILE
 */