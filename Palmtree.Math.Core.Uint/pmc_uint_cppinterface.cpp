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

    void PMC_UINT_CppInterface::GetStatisticsInfo(PMC_STATISTICS_INFO * p)
    {
        return (PMC_GetStatisticsInfo(p));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_UINT32_T x) noexcept(false)
    {
        return (PMC_From_I(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::From(_UINT64_T x) noexcept(false)
    {
        return (PMC_From_L(x));
    }

    void PMC_UINT_CppInterface::CheckHandle(PMC_HANDLE_UINT p)
    {
        PMC_CheckHandle_X(p);
    }

    void PMC_UINT_CppInterface::Dispose(PMC_HANDLE_UINT p)
    {
        PMC_Dispose_X(p);
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false)
    {
        return (PMC_GetConstantValue_I(type));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArray(const unsigned char * buffer, size_t count) noexcept(false)
    {
        return (PMC_FromByteArray(buffer, count));
    }

    size_t PMC_UINT_CppInterface::ToByteArray(PMC_HANDLE_UINT p, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArray(p, buffer, buffer_size));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Clone(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Clone_X(x));
    }

    _UINT64_T PMC_UINT_CppInterface::GetAllocatedMemorySize()
    {
        return (PMC_GetAllocatedMemorySize());
    }

    _UINT32_T PMC_UINT_CppInterface::ToUInt32(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_To_X_I(p));
    }

    _UINT64_T PMC_UINT_CppInterface::ToUInt64(PMC_HANDLE_UINT p) noexcept(false)
    {
        return (PMC_To_X_L(p));
    }

    void PMC_UINT_CppInterface::InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO * info)
    {
        PMC_InitializeNumberFormatInfo(info);
    }

    size_t PMC_UINT_CppInterface::ToString(PMC_HANDLE_UINT x, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToString(x, format, format_option, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParse(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, PMC_HANDLE_UINT * o) noexcept(false)
    {
        return (PMC_TryParse(source, number_styles, format_option, o));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Add_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Add_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Add(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Add_X_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_I_X(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Subtruct_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Subtruct_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Increment(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Increment_X(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Decrement(PMC_HANDLE_UINT x) noexcept(false)
    {
        return (PMC_Decrement_X(x));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Multiply_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Multiply_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Multiply_X_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T * q) noexcept(false)
    {
        return (PMC_DivRem_I_X(u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T * q) noexcept(false)
    {
        return (PMC_DivRem_L_X(u, v, q));
    }

    _UINT32_T PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_X_I(u, v, q));
    }

    _UINT64_T PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_X_L(u, v, q));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::DivRem(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * q) noexcept(false)
    {
        return (PMC_DivRem_X_X(u, v, q));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::RightShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_RightShift_X_I(p, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::LeftShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false)
    {
        return (PMC_LeftShift_X_I(p, n));
    }

    _UINT32_T PMC_UINT_CppInterface::BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_I_X(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_L_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_I(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseAnd_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_L_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_X_I(u, v));
    }

    _UINT64_T PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_OneCompliment_And_BitwiseAnd_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::BitwiseOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_BitwiseOr_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ExclusiveOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_ExclusiveOr_X_X(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_I_X(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_L_X(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Compare_X_I(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Compare_X_L(u, v));
    }

    SIGN_T PMC_UINT_CppInterface::Compare(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Compare_X_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_I_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_L_X(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_Equals_X_I(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_Equals_X_L(u, v));
    }

    _UINT32_T PMC_UINT_CppInterface::Equals(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_Equals_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_I_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_L_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_I(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_L(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::GreatestCommonDivisor(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        return (PMC_GreatestCommonDivisor_X_X(u, v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false)
    {
        return (PMC_Pow_X_I(x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::Pow(PMC_HANDLE_UINT x, _UINT64_T n) noexcept(false)
    {
        return (PMC_Pow_X_L(x, n));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::ModPow(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false)
    {
        return (PMC_ModPow_X_X_X(v, e, m));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::TimesOfExponentOf10(_UINT32_T v, _UINT32_T e)
    {
        return (PMC_TimesOfExponentOf10(v, e));
    }

    _UINT32_T PMC_UINT_CppInterface::Floor_Log10(PMC_HANDLE_UINT v)
    {
        return (PMC_Floor_Log10(v));
    }

    PMC_HANDLE_UINT PMC_UINT_CppInterface::FromByteArrayForSINT(const unsigned char * buffer, size_t count, SIGN_T * o_sign) noexcept(false)
    {
        return (PMC_FromByteArrayForSINT(buffer, count, o_sign));
    }

    size_t PMC_UINT_CppInterface::ToByteArrayForSINT(SIGN_T p_sign, PMC_HANDLE_UINT p_abs, unsigned char * buffer, size_t buffer_size) noexcept(false)
    {
        return (PMC_ToByteArrayForSINT(p_sign, p_abs, buffer, buffer_size));
    }

    PMC_STATUS_CODE PMC_UINT_CppInterface::TryParseForSINT(const wchar_t * source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO * format_option, SIGN_T * o_sign, PMC_HANDLE_UINT * o_abs) noexcept(false)
    {
        return (PMC_TryParseForSINT(source, number_styles, format_option, o_sign, o_abs));
    }

    size_t PMC_UINT_CppInterface::ToStringForSINT(SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t * format, const PMC_NUMBER_FORMAT_INFO * format_option, wchar_t * buffer, size_t buffer_size)
    {
        return (PMC_ToStringForSINT(x_sign, x_abs, format, format_option, buffer, buffer_size));
    }

    void PMC_UINT_CppInterface::InternalTest()
    {
        PMC_InternalTest();
    }


}


/*
 * END OF FILE
 */