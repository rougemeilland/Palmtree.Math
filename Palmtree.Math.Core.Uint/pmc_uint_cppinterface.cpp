#include "pmc_uint_cppinterface.h"
#include "pmc_uint_cppinterface.h"
#include "pmc_uint_cppinterface.h"
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

#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_string.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_UINT_CppInterface::PMC_UINT_CppInterface()
    {
    }

    PMC_UINT_CppInterface::~PMC_UINT_CppInterface()
    {
    }

    bool PMC_UINT_CppInterface::Initialize()
    {
        return (PMC_UINT_Initialize());
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::GetConfigurationSettings(const wchar_t * key, wchar_t * value_buffer, _INT32_T value_buffer_size, _INT32_T * count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, _INT32_T x)
    {
        return (PMC_From_UI(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, _INT64_T x)
    {
        return (PMC_From_UL(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, _UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, _UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, DECIMAL x, SIGN_T * o_sign, PMC_HANDLE_UINT * o_denominator)
    {
        return (PMC_From_DECIMAL(tc, x, o_sign, o_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(ThreadContext& tc, double x, SIGN_T * o_sign, PMC_HANDLE_UINT * o_denominator)
    {
        return (PMC_From_DOUBLE(tc, x, o_sign, o_denominator));
    }

    void PMC_UINT_CppInterface::CheckHandle(PMC_HANDLE_UINT p)
    {
        PMC_CheckHandle_UX(p);
    }

    void PMC_UINT_CppInterface::Dispose(ThreadContext& tc, PMC_HANDLE_UINT p)
    {
        PMC_Dispose_UX(tc, p);
    }

    _INT32_T PMC_UINT_CppInterface::GetBufferCount(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_GetBufferCount_UX(p));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_UI(type));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_UINT(ThreadContext& tc, const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray_UINT(tc, buffer, count));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(PMC_HANDLE_UINT p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_UX(p, buffer, buffer_size));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Clone(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Clone_UX(tc, x));
    }

    _INT32_T PMC_UINT_CppInterface::ToInt32(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_ToInt32_UX(p));
    }

    _INT64_T PMC_UINT_CppInterface::ToInt64(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_ToInt64_UX(p));
    }

    _UINT32_T PMC_UINT_CppInterface::ToUInt32(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_ToUInt32_UX(p));
    }

    _UINT64_T PMC_UINT_CppInterface::ToUInt64(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_ToUInt64_UX(p));
    }

    DECIMAL PMC_UINT_CppInterface::ToDecimal(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        return (PMC_ToDecimal_R(tc, p_sign, p_numerator, p_denominator));
    }

    double PMC_UINT_CppInterface::ToDouble(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        return (PMC_ToDouble_R(tc, p_sign, p_numerator, p_denominator));
    }

    void PMC_UINT_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    size_t PMC_UINT_CppInterface::ToString(ThreadContext& tc, PMC_HANDLE_UINT x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_UX(tc, x, format, format_option, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_UINT(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_UINT * o) noexcept(false)
    {
        return (PMC_TryParse_UINT(tc, source, number_styles, format_option, o));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::AToL(ThreadContext& tc, const wchar_t * source)
    {
        return (PMC_AToL(tc, source));
    }

#ifdef _M_IX86
    _UINT32_T PMC_UINT_CppInterface::AToI(const wchar_t * source)
    {
        return (PMC_AToI(source));
    }
#elif defined(_M_X64)
    _UINT64_T PMC_UINT_CppInterface::AToI(const wchar_t * source)
    {
        return (PMC_AToI(source));
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UX_UX(tc, u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_UX(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Increment(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Increment_UX(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Decrement(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Decrement_UX(tc, x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UX_UX(tc, PMC_MULTIPLICATION_METHOD_AUTO, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(ThreadContext & tc, PMC_MULTIPLICATION_METHOD_CODE method, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UX_UX(tc, method, u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T * q) noexcept(false)
    {
        return (PMC_DivRem_UI_UX(u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T * q) noexcept(false)
    {
        return (PMC_DivRem_UL_UX(u, v, q));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UI(tc, u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UL(tc, u, v, q));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UX(tc, u, v, q));
    }

    _UINT32_T PMC_UINT_CppInterface::DivideExactly(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_DivideExactly_UI_UX(tc, u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::DivideExactly(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_DivideExactly_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivideExactly(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_DivideExactly_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivideExactly(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_DivideExactly_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_DivideExactly_UX_UX(tc, u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Modulo(ThreadContext & tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT32_T v)
    {
        return (PMC_Modulo_X_UI(tc, u_sign, u_abs, v));
    }

    _UINT64_T PMC_UINT_CppInterface::Modulo(ThreadContext & tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT64_T v)
    {
        return (PMC_Modulo_X_UL(tc, u_sign, u_abs, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Modulo(ThreadContext & tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, PMC_HANDLE_UINT v)
    {
        return (PMC_Modulo_X_UX(tc, u_sign, u_abs, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Modulo(ThreadContext & tc, SIGN_T u_sign, _UINT32_T u_abs, PMC_HANDLE_UINT v)
    {
        return (PMC_Modulo_I_UX(tc, u_sign, u_abs, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Modulo(ThreadContext & tc, SIGN_T u_sign, _UINT64_T u_abs, PMC_HANDLE_UINT v)
    {
        return (PMC_Modulo_L_UX(tc, u_sign, u_abs, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RightShift(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_RightShift_UX_I(tc, p, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::LeftShift(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_LeftShift_UX_I(tc, p, n));
    }

    _UINT32_T PMC_UINT_CppInterface::BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UI_UX(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UL_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_UI(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UL_UX(tc, u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UX(tc, u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_UI_UX(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_UL_UX(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Compare_UX_UI(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Compare_UX_UL(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_UX_UX(u, v));
    }
     
    _UINT32_T PMC_UINT_CppInterface::Equals(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_UI_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_UL_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Equals_UX_UI(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Equals_UX_UL(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UI_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UL_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UI(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UL(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UX(tc, u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(ThreadContext& tc, _UINT32_T x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UI_UI(tc, x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(ThreadContext& tc, _UINT64_T x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UL_UI(tc, x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(ThreadContext& tc, PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UX_UI(tc, x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow10(ThreadContext& tc, _UINT32_T n)
    {
        return (PMC_Pow10_UI(tc, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ModPow(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false)
    {
        return (PMC_ModPow_UX_UX_UX(tc, v, e, m));
    }

    _UINT32_T PMC_UINT_CppInterface::FloorLog10(ThreadContext& tc, PMC_HANDLE_UINT v)
    {
        return (PMC_FloorLog10_UX(tc, v));
    }

    _INT32_T PMC_UINT_CppInterface::FloorLog10(ThreadContext& tc, PMC_HANDLE_UINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        return (PMC_FloorLog10_R(tc, v_numerator, v_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RoundZero(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_RoundZero_R(tc, x_numerator_abs, x_denominator, mode));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RoundZero(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_RoundZero_R(tc, x_numerator_sign, x_numerator_abs, x_denominator, mode));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Round(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT * r_denominator)
    {
        return (PMC_Round_R(tc, x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Round(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT * r_denominator)
    {
        return (PMC_Round_R(tc, x_numerator_sign, x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    PMC_MIDPOINT_ROUNDING_CODE PMC_UINT_CppInterface::GetDefaultRoundingMode()
    {
        return (PMC_GetDefaultRoundingMode());
    }

    void PMC_UINT_CppInterface::SetDefaultRoundingMode(PMC_MIDPOINT_ROUNDING_CODE mode) noexcept(false)
    {
        PMC_SetDefaultRoundingMode(mode);
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_SINT(ThreadContext& tc, const unsigned char * buffer, size_t count, SIGN_T * o_sign) noexcept(false)
    {
        return (PMC_FromByteArray_SINT(tc, buffer, count, o_sign));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_RTNL(ThreadContext& tc, const unsigned char * buffer, size_t count, SIGN_T * o_numerator_sign, PMC_HANDLE_UINT * o_numerator_abs) noexcept(false)
    {
        return (PMC_FromByteArray_RTNL(tc, buffer, count, o_numerator_sign, o_numerator_abs));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(SIGN_T p_sign, PMC_HANDLE_UINT p_abs, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_X(p_sign, p_abs, buffer, buffer_size));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(SIGN_T p_numerator_sign, PMC_HANDLE_UINT p_numerator_abs, PMC_HANDLE_UINT p_denominator, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_R(p_numerator_sign, p_numerator_abs, p_denominator, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_SINT(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * o_sign, PMC_HANDLE_UINT * o_abs) noexcept(false)
    {
        return (PMC_TryParse_SINT(tc, source, number_styles, format_option, o_sign, o_abs));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_RTNL(ThreadContext& tc, const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * o_numerator_sign, PMC_HANDLE_UINT * o_numerator_abs, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        return (PMC_TryParse_RTNL(tc, source, number_styles, format_option, o_numerator_sign, o_numerator_abs, o_denominator));
    }

    size_t PMC_UINT_CppInterface::ToString(ThreadContext& tc, SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size)
    {
        return (PMC_ToString_X(tc, x_sign, x_abs, format, format_option, buffer, buffer_size));
    }

    size_t PMC_UINT_CppInterface::ToString(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size)
    {
        return (PMC_ToString_R(tc, x_numerator_sign, x_numerator_abs, x_denominator, format, format_option, buffer, buffer_size));
    }

    PMC_HANDLE_SFMT PMC_UINT_CppInterface::AllocateRandomStateObject(ThreadContext & tc, _UINT32_T seed)
    {
        return (PMC_AllocateRandomStateObjectFromUInt32(tc, seed));
    }

    PMC_HANDLE_SFMT PMC_UINT_CppInterface::AllocateRandomStateObject(ThreadContext & tc, _UINT32_T * init_key, _INT32_T key_length)
    {
        return (PMC_AllocateRandomStateObjectFromUInt32Array(tc, init_key, key_length));
    }

    void PMC_UINT_CppInterface::CheckHandle(PMC_HANDLE_SFMT p)
    {
        PMC_CheckHandle_SFMT(p);
    }

    void PMC_UINT_CppInterface::Dispose(ThreadContext & tc, PMC_HANDLE_SFMT p)
    {
        PMC_Dispose_SFMT(tc, p);
    }

    _UINT32_T PMC_UINT_CppInterface::GenerateUInt32RandomValue(PMC_HANDLE_SFMT handle)
    {
        return (PMC_GenerateUInt32RandomValue(handle));
    }

    _UINT64_T PMC_UINT_CppInterface::GenerateUInt64RandomValue(PMC_HANDLE_SFMT handle)
    {
        return (PMC_GenerateUInt64RandomValue(handle));
    }

    double PMC_UINT_CppInterface::GenerateDoubleRandomValue(PMC_HANDLE_SFMT handle)
    {
        return (PMC_GenerateDoubleRandomValue(handle));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GenerateUBigIntRandomValue(ThreadContext & tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count)
    {
        return (PMC_GenerateUBigIntRandomValue(tc, handle, bit_count));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GenerateUBigIntCryptoRandomValue(ThreadContext & tc, _BYTE_T * data, _INT32_T bit_count)
    {
        return (PMC_GenerateUBigIntCryptoRandomValue(tc, data, bit_count));
    }

    void PMC_UINT_CppInterface::InternalTest()
    {
        PMC_InternalTest();
    }


}


/*
 * END OF FILE
 */