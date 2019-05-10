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


#pragma once

#ifndef PMC_UINT_CPPINTERFACE_H
#define PMC_UINT_CPPINTERFACE_H

#include "pmc_uint.h"

namespace Palmtree::Math::Core::Internal
{

    class ThreadContext;

    class __DLLEXPORT_UINT PMC_UINT_CppInterface
    {
    public:
        PMC_UINT_CppInterface();
        ~PMC_UINT_CppInterface();

        bool Initialize();

        PMC_STATUS_CODE GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

        PMC_HANDLE_UINT From(ThreadContext& tc, _INT32_T x);
        PMC_HANDLE_UINT From(ThreadContext& tc, _INT64_T x);
        PMC_HANDLE_UINT From(ThreadContext& tc, _UINT32_T x);
        PMC_HANDLE_UINT From(ThreadContext& tc, _UINT64_T x);
        PMC_HANDLE_UINT From(ThreadContext& tc, DECIMAL x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator);
        PMC_HANDLE_UINT From(ThreadContext& tc, double x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator);

        void CheckHandle(PMC_HANDLE_UINT p);

        void Dispose(ThreadContext& tc, PMC_HANDLE_UINT p);

        _INT32_T GetBufferCount(PMC_HANDLE_UINT p) noexcept(false);

        PMC_HANDLE_UINT GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

        PMC_HANDLE_UINT FromByteArray_UINT(ThreadContext& tc, const unsigned char* buffer, size_t count) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_UINT Clone(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

        _INT32_T ToInt32(PMC_HANDLE_UINT p) noexcept(false);
        _INT64_T ToInt64(PMC_HANDLE_UINT p) noexcept(false);
        _UINT32_T ToUInt32(PMC_HANDLE_UINT p) noexcept(false);
        _UINT64_T ToUInt64(PMC_HANDLE_UINT p) noexcept(false);
        DECIMAL ToDecimal(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);
        double ToDouble(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);

        void InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info);
        size_t ToString(ThreadContext& tc, PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        PMC_STATUS_CODE TryParse_UINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o) noexcept(false);
        PMC_HANDLE_UINT AToL(ThreadContext& tc, const wchar_t* source);
#ifdef _M_IX86
        _UINT32_T AToI(const wchar_t* source);
#elif defined(_M_X64)
        _UINT64_T AToI(const wchar_t* source);
#else
#error unknown platform
#endif

        PMC_HANDLE_UINT Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT64_T Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT Increment(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

        PMC_HANDLE_UINT Decrement(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);

        PMC_HANDLE_UINT Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Multiply(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T DivRem(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
        _UINT64_T DivRem(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
        _UINT32_T DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
        _UINT64_T DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
        PMC_HANDLE_UINT DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

        _UINT32_T DivideExactly(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT64_T DivideExactly(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T Modulo(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT32_T v);
        _UINT64_T Modulo(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, _UINT64_T v);
        PMC_HANDLE_UINT Modulo(ThreadContext& tc, SIGN_T u_sign, PMC_HANDLE_UINT u_abs, PMC_HANDLE_UINT v);
        PMC_HANDLE_UINT Modulo(ThreadContext& tc, SIGN_T u_sign, _UINT32_T u_abs, PMC_HANDLE_UINT v);
        PMC_HANDLE_UINT Modulo(ThreadContext& tc, SIGN_T u_sign, _UINT64_T u_abs, PMC_HANDLE_UINT v);

        PMC_HANDLE_UINT RightShift(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_UINT LeftShift(ThreadContext& tc, PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

        _UINT32_T BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT64_T BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        _UINT64_T BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        _UINT64_T OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT BitwiseOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT ExclusiveOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        SIGN_T Compare(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T Equals(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T Equals(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T Equals(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        _UINT32_T Equals(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        _UINT32_T Equals(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT Pow(ThreadContext& tc, _UINT32_T x, _UINT32_T n) noexcept(false);
        PMC_HANDLE_UINT Pow(ThreadContext& tc, _UINT64_T x, _UINT32_T n) noexcept(false);
        PMC_HANDLE_UINT Pow(ThreadContext& tc, PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false);

        PMC_HANDLE_UINT Pow10(ThreadContext& tc, _UINT32_T n);

        PMC_HANDLE_UINT ModPow(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false);

        _UINT32_T FloorLog10(ThreadContext& tc, PMC_HANDLE_UINT v);
        _INT32_T FloorLog10(ThreadContext& tc, PMC_HANDLE_UINT v_numerator, PMC_HANDLE_UINT v_denominator);

        PMC_HANDLE_UINT RoundZero(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);
        PMC_HANDLE_UINT RoundZero(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);
        PMC_HANDLE_UINT Round(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);
        PMC_HANDLE_UINT Round(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);

        PMC_MIDPOINT_ROUNDING_CODE GetDefaultRoundingMode();
        void SetDefaultRoundingMode(PMC_MIDPOINT_ROUNDING_CODE mode) noexcept(false);

        PMC_HANDLE_UINT FromByteArray_SINT(ThreadContext& tc, const unsigned char* buffer, size_t count, SIGN_T* o_sign) noexcept(false);
        PMC_HANDLE_UINT FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs) noexcept(false);
        size_t ToByteArray(SIGN_T p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
        size_t ToByteArray(SIGN_T p_numerator_sign, PMC_HANDLE_UINT p_numerator_abs, PMC_HANDLE_UINT p_denominator, unsigned char* buffer, size_t buffer_size) noexcept(false);
        PMC_STATUS_CODE TryParse_SINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, PMC_HANDLE_UINT* o_abs) noexcept(false);
        PMC_STATUS_CODE TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs, PMC_HANDLE_UINT* o_denominator) noexcept(false);
        size_t ToString(ThreadContext& tc, SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);
        size_t ToString(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);

        PMC_HANDLE_SFMT AllocateRandomStateObject(ThreadContext& tc, _UINT32_T seed);
        PMC_HANDLE_SFMT AllocateRandomStateObject(ThreadContext& tc, _UINT32_T* init_key, _INT32_T key_length);
        void CheckHandle(PMC_HANDLE_SFMT p);
        void Dispose(ThreadContext& tc, PMC_HANDLE_SFMT p);
        _UINT32_T GenerateUInt32RandomValue(PMC_HANDLE_SFMT handle);
        _UINT64_T GenerateUInt64RandomValue(PMC_HANDLE_SFMT handle);
        double GenerateDoubleRandomValue(PMC_HANDLE_SFMT handle);
        PMC_HANDLE_UINT GenerateUBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count);
        PMC_HANDLE_UINT GenerateUBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count);

        void InternalTest();

    };

}

#endif


/*
 * END OF FILE
 */