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

    void PMC_UINT_CppInterface::UseObject(PMC_HANDLE_UINT x) noexcept(false)
    {
        PMC_UseObject_UX(x);
    }

    void PMC_UINT_CppInterface::UnuseObject(PMC_HANDLE_UINT x) noexcept(false)
    {
        PMC_UnuseObject_UX(x);
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::GetConfigurationSettings(const wchar_t * key, wchar_t * value_buffer, _INT32_T value_buffer_size, _INT32_T * count)
    {
        return (PMC_GetConfigurationSettings(key, value_buffer, value_buffer_size, count));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_INT32_T x)
    {
        return (PMC_From_UI(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_INT64_T x)
    {
        return (PMC_From_UL(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_UINT32_T x) noexcept(false)
    {
        return (PMC_From_UI(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_UINT64_T x) noexcept(false)
    {
        return (PMC_From_UL(x));
    }

    void PMC_UINT_CppInterface::CheckHandle(PMC_HANDLE_UINT p)
    {
        PMC_CheckHandle_UX(p);
    }

    void PMC_UINT_CppInterface::Dispose(PMC_HANDLE_UINT p)
    {
        PMC_Dispose_UX(p);
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_UI(type));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_UINT(const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray_UINT(buffer, count));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(PMC_HANDLE_UINT p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_UX(p, buffer, buffer_size));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Clone(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Clone_UX(x));
    }

    _UINT64_T PMC_UINT_CppInterface::GetAllocatedMemorySize()
    {
        return (PMC_GetAllocatedMemorySize());
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

    void PMC_UINT_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    size_t PMC_UINT_CppInterface::ToString(PMC_HANDLE_UINT x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString_UX(x, format, format_option, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_UINT(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_UINT * o) noexcept(false)
    {
        return (PMC_TryParse_UINT(source, number_styles, format_option, o));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::AToL(const wchar_t * source)
    {
        return (PMC_AToL(source));
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

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_UX_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UI_UX(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Increment(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Increment_UX(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Decrement(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Decrement_UX(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_UX_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T * q) noexcept(false)
    {
        return (PMC_DivRem_UI_UX(u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T * q) noexcept(false)
    {
        return (PMC_DivRem_UL_UX(u, v, q));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UI(u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UL(u, v, q));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_UX_UX(u, v, q));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RightShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_RightShift_UX_I(p, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::LeftShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_LeftShift_UX_I(p, n));
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

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_UX_UX(u, v));
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

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UI_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UL_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UI(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UL(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_UX_UX(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(_UINT32_T x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UI_UI(x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(_UINT64_T x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UL_UI(x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_UX_UI(x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow10(_UINT32_T n)
    {
        return (PMC_Pow10_UI(n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ModPow(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false)
    {
        return (PMC_ModPow_UX_UX_UX(v, e, m));
    }

    _UINT32_T PMC_UINT_CppInterface::FloorLog10(PMC_HANDLE_UINT v)
    {
        return (PMC_FloorLog10_UX(v));
    }

    _INT32_T PMC_UINT_CppInterface::FloorLog10(PMC_HANDLE_UINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        return (PMC_FloorLog10_R(v_numerator, v_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RoundZero(PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_RoundZero_R(x_numerator_abs, x_denominator, mode));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RoundZero(SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        return (PMC_RoundZero_R(x_numerator_sign, x_numerator_abs, x_denominator, mode));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Round(PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT * r_denominator)
    {
        return (PMC_Round_R(x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Round(SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT * r_denominator)
    {
        return (PMC_Round_R(x_numerator_sign, x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_SINT(const unsigned char * buffer, size_t count, SIGN_T * o_sign) noexcept(false)
    {
        return (PMC_FromByteArray_SINT(buffer, count, o_sign));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray_RTNL(const unsigned char * buffer, size_t count, SIGN_T * o_numerator_sign, PMC_HANDLE_UINT * o_numerator_abs) noexcept(false)
    {
        return (PMC_FromByteArray_RTNL(buffer, count, o_numerator_sign, o_numerator_abs));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(SIGN_T p_sign, PMC_HANDLE_UINT p_abs, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_X(p_sign, p_abs, buffer, buffer_size));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(SIGN_T p_numerator_sign, PMC_HANDLE_UINT p_numerator_abs, PMC_HANDLE_UINT p_denominator, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray_R(p_numerator_sign, p_numerator_abs, p_denominator, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_SINT(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * o_sign, PMC_HANDLE_UINT * o_abs) noexcept(false)
    {
        return (PMC_TryParse_SINT(source, number_styles, format_option, o_sign, o_abs));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse_RTNL(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * o_numerator_sign, PMC_HANDLE_UINT * o_numerator_abs, PMC_HANDLE_UINT * o_denominator) noexcept(false)
    {
        return (PMC_TryParse_RTNL(source, number_styles, format_option, o_numerator_sign, o_numerator_abs, o_denominator));
    }

    size_t PMC_UINT_CppInterface::ToString(SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size)
    {
        return (PMC_ToString_X(x_sign, x_abs, format, format_option, buffer, buffer_size));
    }

    size_t PMC_UINT_CppInterface::ToString(SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size)
    {
        return (PMC_ToString_R(x_numerator_sign, x_numerator_abs, x_denominator, format, format_option, buffer, buffer_size));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivideExactly(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        return (PMC_DivideExactly_UX_UX(u, v));
    }

    void PMC_UINT_CppInterface::InternalTest()
    {
        PMC_InternalTest();
    }


}


/*
 * END OF FILE
 */