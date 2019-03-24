#include "pmc_uint_cppinterface.h"
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


#include "pmc_sint_internal.h"
#include "pmc_sint_cppinterface.h"

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

    void PMC_SINT_CppInterface::GetStatisticsInfo(PMC_STATISTICS_INFO * p)
    {
        return (PMC_GetStatisticsInfo(p));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(_UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(_INT32_T x) noexcept(false)
    {
        return (PMC_From_I(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(_UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(_INT64_T x) noexcept(false)
    {
        return (PMC_From_L(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::From(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_From_UX(x));
    }

    _INT32_T PMC_SINT_CppInterface::GetHashCode(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_GetHashCode(p));
    }

    void PMC_SINT_CppInterface::CheckHandle(PMC_HANDLE_UINT p)
    {
        PMC_CheckHandle_UX(p);
    }

    void PMC_SINT_CppInterface::CheckHandle(PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_CheckHandle_X(p);
    }

    void PMC_SINT_CppInterface::Dispose(PMC_HANDLE_UINT p)
    {
        PMC_Dispose_UX(p);
    }

    void PMC_SINT_CppInterface::Dispose(PMC_HANDLE_SINT p) noexcept(false)
    {
        PMC_Dispose_X(p);
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_I(type));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::FromByteArray(const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray(buffer, count));
    }

    size_t PMC_SINT_CppInterface::ToByteArray(PMC_HANDLE_SINT p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray(p, buffer, buffer_size));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Clone(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Clone_X(x));
    }

    _UINT64_T PMC_SINT_CppInterface::GetAllocatedMemorySize()
    {
        return (PMC_GetAllocatedMemorySize());
    }

    _UINT32_T PMC_SINT_CppInterface::ToUint32(PMC_HANDLE_SINT p) noexcept(false)
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

    PMC_HANDLE_UINT PMC_SINT_CppInterface::ToUBigInt(PMC_HANDLE_SINT p) noexcept(false)
    {
        return (PMC_ToUBigInt_X(p));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Negate(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Negate_UX(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Negate(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Negate_X(x));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::Abs(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Abs_X(x));
    }

    size_t PMC_SINT_CppInterface::ToString(PMC_HANDLE_SINT x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString(x, format, format_option, buffer, buffer_size));
    }

    void PMC_SINT_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    PMC_STATUS_CODE PMC_SINT_CppInterface::TryParse(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_SINT * o) noexcept(false)
    {
        return (PMC_TryParse(source, number_styles, format_option, o));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UI_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_I_UX(u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_I_X(u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UL_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_L_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_UX_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_UX_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_UX_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Add_X_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Add_X_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Add(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Add_X_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_I_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_I_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_L_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Subtruct(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Subtruct_X_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Increment(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Increment_X(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Decrement(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_Decrement_X(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UI_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_I_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_I_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UL_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_L_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_UX_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_Multiply_X_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_Multiply_X_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::Multiply(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_Multiply_X_X(u, v));
    }

    _UINT32_T PMC_SINT_CppInterface::DivRem(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UI_X(u, v, q));
    }

    _INT32_T PMC_SINT_CppInterface::DivRem(_INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_I_UX(u, v, q));
    }

    _INT32_T PMC_SINT_CppInterface::DivRem(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_I_X(u, v, q));
    }

    _INT64_T PMC_SINT_CppInterface::DivRem(_INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_L_UX(u, v, q));
    }

    _UINT64_T PMC_SINT_CppInterface::DivRem(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UL_X(u, v, q));
    }

    _UINT32_T PMC_SINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_I(u, v, q));
    }

    _UINT64_T PMC_SINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_L(u, v, q));
    }

    _INT64_T PMC_SINT_CppInterface::DivRem(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_L_X(u, v, q));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_UX_X(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UI(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_I(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UL(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_L(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_UX(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::DivRem(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false)
    {
        return (PMC_DivRem_X_X(u, v, q));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::LeftShift(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_LeftShift_X_I(p, n));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::RightShift(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_RightShift_X_I(p, n));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::OneComplement(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_OneComplement_UX(x));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::OneComplement(PMC_HANDLE_SINT x) noexcept(false)
    {
        return (PMC_OneComplement_X(x));
    }

    _UINT32_T PMC_SINT_CppInterface::BitwiseAnd(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UI_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_I_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_I_X(u, v));
    }

    _UINT64_T PMC_SINT_CppInterface::BitwiseAnd(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UL_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_I(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_L(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_X(u, v));
    }

    _UINT32_T PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_I(u, v));
    }

    _UINT64_T PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseAnd(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UI_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_I_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_I_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UL_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_L_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::BitwiseOr(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UI_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_I_UX(u, v));
    }

    inline PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_I_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UL_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_L_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_L_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_X(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UI(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_I(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UL(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_L(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_UX(u, v));
    }

    PMC_HANDLE_SINT PMC_SINT_CppInterface::ExclusiveOr(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_X(u, v));
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

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UI_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_I_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_L_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UL_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_I(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_L(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_X(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_SINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_X(u, v));
    }

}


/*
 * END OF FILE
 */