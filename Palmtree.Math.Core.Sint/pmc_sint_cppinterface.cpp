#include "pmc_uint_cppinterface.h"
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
#include "pmc_sint_cppinterface.h"
#include "pmc_resourceholder_sint.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_SINT_CppInterface::PMC_SINT_CppInterface()
    {
    }

    PMC_SINT_CppInterface::~PMC_SINT_CppInterface()
    {
    }

    bool PMC_SINT_CppInterface::Initialize()
    {
        return (PMC_SINT_Initialize());
    }

    PMC_STATUS_CODE PMC_SINT_CppInterface::GetConfigurationSettings(const wchar_t * key, wchar_t * value_buffer, _INT32_T value_buffer_size, _INT32_T * count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, _UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, _INT32_T x) noexcept(false)
    {
        return (PMC_From_I(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, _UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, _INT64_T x) noexcept(false)
    {
        return (PMC_From_L(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_From_UX(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, DECIMAL x, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        return (PMC_From_DECIMAL(tc, x, o_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(ThreadContext& tc, double x, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        return (PMC_From_DOUBLE(tc, x, o_denominator));
    }

    _INT32_T PMC_SINT_CppInterface::GetHashCode(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_GetHashCode(p));
    }

    void PMC_SINT_CppInterface::CheckHandle(PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_CheckHandle_X(p);
    }

    void PMC_SINT_CppInterface::Dispose(ThreadContext& tc, PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_Dispose_X(tc, p);
    }

    _INT32_T PMC_SINT_CppInterface::GetBufferCount(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_GetBufferCount_X(p));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_I(type));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::FromByteArray_SINT(ThreadContext& tc, const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray_SINT(tc, buffer, count));
    }

    size_t PMC_SINT_CppInterface::ToByteArray(PMC_HANDLE_SINT p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_X(p, buffer, buffer_size));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Clone(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Clone_X(tc, x));
    }

    _UINT64_T PMC_SINT_CppInterface::GetAllocatedMemorySize()
    {
        return (PMC_GetAllocatedMemorySize());
    }

    _UINT32_T PMC_SINT_CppInterface::ToUInt32(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToUInt32_X(p));
    }

    _INT32_T PMC_SINT_CppInterface::ToInt32(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToInt32_X(p));
    }

    _UINT64_T PMC_SINT_CppInterface::ToUInt64(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToUInt64_X(p));
    }

    _INT64_T PMC_SINT_CppInterface::ToInt64(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToInt64_X(p));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::ToUBigInt(ThreadContext& tc, PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToUBigInt_X(tc, p));
    }

    DECIMAL PMC_SINT_CppInterface::ToDecimal(ThreadContext& tc, PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        return (PMC_ToDecimal_R(tc, p_numerator, p_denominator));
    }

    double PMC_SINT_CppInterface::ToDouble(ThreadContext& tc, PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        return (PMC_ToDouble_R(tc, p_numerator, p_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Negate(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Negate_UX(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Negate(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Negate_X(tc, x));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::Abs(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Abs_X(tc, x));
    }

    size_t PMC_SINT_CppInterface::ToString(ThreadContext& tc, PMC_HANDLE_SINT x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_X(tc, x, format, format_option, buffer, buffer_size));
    }

    size_t PMC_SINT_CppInterface::ToString(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_R(tc, x_numerator, x_denominator, format, format_option, buffer, buffer_size));
    }

    void PMC_SINT_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    PMC_STATUS_CODE PMC_SINT_CppInterface::TryParse_SINT(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_SINT * o) noexcept(false)
    {
        return (PMC_TryParse_SINT(tc, source, number_styles, format_option, o));
    }

    PMC_STATUS_CODE PMC_SINT_CppInterface::TryParse_RTNL(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_SINT * o_numerator, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        return (PMC_TryParse_RTNL(tc, source, number_styles, format_option, o_numerator, o_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UI_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_I_UX(tc, u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_I_X(tc, u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UL_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_L_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_UX_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_UX_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UX_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_X_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_X_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_X_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_I_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_I_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_L_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_X_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Increment(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Increment_X(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Decrement(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Decrement_X(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UI_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_I_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_I_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UL_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_L_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UX_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_X_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_X_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_X_X(tc, u, v));
    }

    _UINT32_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UI_X(tc, u, v, q));
    }

    _INT32_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_I_UX(tc, u, v, q));
    }

    _INT32_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_I_X(tc, u, v, q));
    }

    _INT64_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_L_UX(tc, u, v, q));
    }

    _UINT64_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UL_X(tc, u, v, q));
    }

    _UINT32_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_I(tc, u, v, q));
    }

    _UINT64_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_L(tc, u, v, q));
    }

    _INT64_T PMC_SINT_CppInterface::DivRem(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_L_X(tc, u, v, q));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UX_X(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UI(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_I(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UL(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_L(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UX(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_X(tc, u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::LeftShift(ThreadContext& tc, PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_LeftShift_X_I(tc, p, n));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::RightShift(ThreadContext& tc, PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_RightShift_X_I(tc, p, n));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::OneComplement(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_OneComplement_UX(tc, x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::OneComplement(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_OneComplement_X(tc, x));
    }

    _UINT32_T PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UI_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_I_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_I_X(tc, u, v));
    }

    _UINT64_T PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UL_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_L_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_I(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_L(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_X(tc, u, v));
    }

    _UINT32_T PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_I(tc, u, v));
    }

    _UINT64_T PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_L(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UI_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_I_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_I_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UL_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_L_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UI_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_I_UX(tc, u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_I_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UL_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_L_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_L_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UI(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_I(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UL(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_L(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UX(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_X(tc, u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_I_UX(u, v));
    }

    inline SIGN_T PMC_SINT_CppInterface::Compare(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_I_X(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_L_UX(u, v));
    }

    inline SIGN_T PMC_SINT_CppInterface::Compare(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_L_X(u, v));
    }

    inline SIGN_T PMC_SINT_CppInterface::Compare(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_UI_X(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_UL_X(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Compare_UX_I(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Compare_UX_L(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_UX_X(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Compare_X_UI(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Compare_X_I(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Compare_X_UL(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Compare_X_L(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_X_UX(u, v));
    }

    SIGN_T PMC_SINT_CppInterface::Compare(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Compare_X_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_UI_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_I_UX(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_I_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_L_UX(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_UL_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Equals_UX_I(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Equals_UX_L(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_L_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_UX_X(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Equals_X_UI(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Equals_X_I(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Equals_X_UL(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Equals_X_L(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_X_UX(u, v));
    }

    bool PMC_SINT_CppInterface::Equals(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Equals_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UI_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_I_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_I_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_L_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UL_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_I(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_L(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_L_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_I(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_L(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_X(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::FromByteArray_RTNL(ThreadContext& tc, const unsigned char * buffer, size_t count, PMC_HANDLE_SINT * o_numerator) noexcept(false)
    {
        return (PMC_FromByteArray_RTNL(tc, buffer, count, o_numerator));
    }

    size_t PMC_SINT_CppInterface::ToByteArray(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_R(p_numerator, p_denominator, buffer, buffer_size));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        return (PMC_DivideExactly_X_X(tc, u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_UI_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_UL_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_UX_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_I_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_L_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_X_R(tc, u, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_UI(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_UL(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_UX(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_I(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_L(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_X(tc, u_numerator, u_denominator, v, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        return (PMC_Divide_R_R(tc, u_numerator, u_denominator, v_numerator, v_denominator, w_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Round(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_Round_R(tc, x_numerator, x_denominator, mode));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Round(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT * r_denominator)
    {
        return (PMC_Round_R_I(tc, x_numerator, x_denominator, decimals, mode, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _INT32_T v, _UINT32_T e) noexcept(false)
    {
        return (PMC_Pow_I_UI(tc, v, e));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _INT64_T v, _UINT32_T e) noexcept(false)
    {
        return (PMC_Pow_L_UI(tc, v, e));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _UINT32_T e) noexcept(false)
    {
        return (PMC_Pow_X_UI(tc, v, e));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _INT32_T v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_I_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _INT64_T v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_L_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_X_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _UINT32_T v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_UI_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, _UINT64_T v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_UL_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_UX_I(tc, v, e, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, _INT32_T e, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Pow_R_I(tc, v_numerator, v_denominator, e, r_denominator));
    }

    _INT32_T PMC_SINT_CppInterface::FloorLog10(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        return (PMC_FloorLog10_R(tc, v_numerator, v_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, _INT32_T v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_I(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, _INT64_T v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_L(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_SINT v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_X(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, _UINT32_T v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_UI(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, _UINT64_T v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_UL(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_UX(tc, v, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Invert(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * r_denominator) noexcept(false)
    {
        return (PMC_Invert_R(tc, v_numerator, v_denominator, r_denominator));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::GenerateBigIntRandomValue(ThreadContext & tc, PMC_HANDLE_SFMT handle, _UINT32_T bit_count)
    {
        return (PMC_GenerateBigIntRandomValue(tc, handle, bit_count));
    }

}


/*
 * END OF FILE
 */