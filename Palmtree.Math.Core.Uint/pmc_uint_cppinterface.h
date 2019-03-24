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

#ifdef PALMTREEMATHCOREUINT_EXPORTS
#define __DLLEXPORT_UINT __declspec(dllexport)
#else
#define __DLLEXPORT_UINT __declspec(dllimport)
#endif

    class __DLLEXPORT_UINT PMC_UINT_CppInterface
    {
    public:
        PMC_UINT_CppInterface();
        ~PMC_UINT_CppInterface();

        bool Initialize();

        PMC_STATUS_CODE GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

        void GetStatisticsInfo(PMC_STATISTICS_INFO* p);

        PMC_HANDLE_UINT From(_INT32_T x);// noexcept(false);
        PMC_HANDLE_UINT From(_INT64_T x);// noexcept(false);
        PMC_HANDLE_UINT From(_UINT32_T x);// noexcept(false);
        PMC_HANDLE_UINT From(_UINT64_T x);// noexcept(false);

        void CheckHandle(PMC_HANDLE_UINT p);
        void Dispose(PMC_HANDLE_UINT p);

        PMC_HANDLE_UINT GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

        PMC_HANDLE_UINT FromByteArray(const unsigned char* buffer, size_t count) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_UINT Clone(PMC_HANDLE_UINT x) noexcept(false);

        _UINT64_T GetAllocatedMemorySize();

        _INT32_T ToInt32(PMC_HANDLE_UINT p) noexcept(false);
        _INT64_T ToInt64(PMC_HANDLE_UINT p) noexcept(false);
        _UINT32_T ToUInt32(PMC_HANDLE_UINT p) noexcept(false);
        _UINT64_T ToUInt64(PMC_HANDLE_UINT p) noexcept(false);

        void InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info);
        size_t ToString(PMC_HANDLE_UINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        PMC_STATUS_CODE TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_UINT* o) noexcept(false);

        PMC_HANDLE_UINT Add(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Add(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Add(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Add(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Add(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T Subtruct(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT64_T Subtruct(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT Increment(PMC_HANDLE_UINT x) noexcept(false);

        PMC_HANDLE_UINT Decrement(PMC_HANDLE_UINT x) noexcept(false);

        PMC_HANDLE_UINT Multiply(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Multiply(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT Multiply(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT Multiply(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        _UINT32_T DivRem(_UINT32_T u, PMC_HANDLE_UINT v, _UINT32_T* q) noexcept(false);
        _UINT64_T DivRem(_UINT64_T u, PMC_HANDLE_UINT v, _UINT64_T* q) noexcept(false);
        _UINT32_T DivRem(PMC_HANDLE_UINT u, _UINT32_T v, PMC_HANDLE_UINT* q) noexcept(false);
        _UINT64_T DivRem(PMC_HANDLE_UINT u, _UINT64_T v, PMC_HANDLE_UINT* q) noexcept(false);
        PMC_HANDLE_UINT DivRem(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* q) noexcept(false);

        PMC_HANDLE_UINT RightShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_UINT LeftShift(PMC_HANDLE_UINT p, _INT32_T n) noexcept(false);

        _UINT32_T BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT64_T BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        _UINT64_T BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        _UINT32_T OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        _UINT64_T OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT OneCompliment_And_BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT BitwiseOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT ExclusiveOr(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT ExclusiveOr(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

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

        PMC_HANDLE_UINT GreatestCommonDivisor(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);

        PMC_HANDLE_UINT Pow(PMC_HANDLE_UINT x, _UINT32_T n) noexcept(false);
        PMC_HANDLE_UINT Pow(PMC_HANDLE_UINT x, _UINT64_T n) noexcept(false);

        PMC_HANDLE_UINT ModPow(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false);

        PMC_HANDLE_UINT TimesOfExponentOf10(_UINT32_T v, _UINT32_T e);

        _UINT32_T Floor_Log10(PMC_HANDLE_UINT v);

        PMC_HANDLE_UINT FromByteArrayForSINT(const unsigned char* buffer, size_t count, SIGN_T* o_sign) noexcept(false);
        size_t ToByteArrayForSINT(SIGN_T p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);
        PMC_STATUS_CODE TryParseForSINT(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, SIGN_T* o_sign, PMC_HANDLE_UINT* o_abs) noexcept(false);
        size_t ToStringForSINT(SIGN_T x_sign, PMC_HANDLE_UINT x_abs, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size);

        void InternalTest();
    };

}

#endif


/*
 * END OF FILE
 */