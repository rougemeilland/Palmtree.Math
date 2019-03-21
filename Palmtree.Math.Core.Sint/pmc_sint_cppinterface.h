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

#ifndef PMC_SINT_CPPINTERFACE_H
#define PMC_SINT_CPPINTERFACE_H

#include "pmc_sint.h"

namespace Palmtree::Math::Core::Internal
{

#ifdef PALMTREEMATHCORESINT_EXPORTS
#define __DLLEXPORT_SINT __declspec(dllexport)
#else
#define __DLLEXPORT_SINT __declspec(dllimport)
#endif

    class __DLLEXPORT_SINT PMC_SINT_CppInterface
    {
    public:
        PMC_SINT_CppInterface();
        ~PMC_SINT_CppInterface();

        bool Initialize();

        PMC_STATUS_CODE GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

        void  GetStatisticsInfo(PMC_STATISTICS_INFO* statistics_info) noexcept(false);// ó^Ç¶ÇÁÇÍÇΩóÃàÊÇ…åªç›Ç‹Ç≈çÃéÊÇ≥ÇÍÇƒÇ¢ÇÈìùåvèÓïÒÇï°é Ç∑ÇÈÅB

        PMC_HANDLE_SINT From(_UINT32_T x) noexcept(false);
        PMC_HANDLE_SINT From(_INT32_T x) noexcept(false);
        PMC_HANDLE_SINT From(_UINT64_T x) noexcept(false);
        PMC_HANDLE_SINT From(_INT64_T x) noexcept(false);
        PMC_HANDLE_SINT From(PMC_HANDLE_UINT x) noexcept(false);

        _INT32_T GetHashCode(PMC_HANDLE_SINT p) noexcept(false);

        void  CheckHandle(PMC_HANDLE_UINT p) noexcept(false);
        void  CheckHandle(PMC_HANDLE_SINT p) noexcept(false);

        void  Dispose(PMC_HANDLE_UINT p) noexcept(false);
        void  Dispose(PMC_HANDLE_SINT p) noexcept(false);

        PMC_HANDLE_SINT GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

        PMC_HANDLE_SINT FromByteArray(const unsigned char* buffer, size_t count) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_SINT Clone(PMC_HANDLE_SINT x) noexcept(false);

        _UINT64_T GetAllocatedMemorySize() noexcept(false);

        _UINT32_T ToUint32(PMC_HANDLE_SINT p) noexcept(false);
        _INT32_T ToInt32(PMC_HANDLE_SINT p) noexcept(false);
        _UINT64_T ToUInt64(PMC_HANDLE_SINT p) noexcept(false);
        _INT64_T ToInt64(PMC_HANDLE_SINT p) noexcept(false);
        PMC_HANDLE_UINT ToUBigInt(PMC_HANDLE_SINT p) noexcept(false);

        PMC_HANDLE_SINT Negate(PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_SINT Negate(PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_UINT Abs(PMC_HANDLE_SINT x) noexcept(false);

        size_t ToString(PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        void  InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

        PMC_STATUS_CODE TryParse(const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false);

        PMC_HANDLE_SINT Add(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Add(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT Subtruct(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT Increment(PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_SINT Decrement(PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_SINT Multiply(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        _UINT32_T DivRem(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _INT32_T DivRem(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _UINT64_T DivRem(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _INT64_T DivRem(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_UINT DivRem(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);

        PMC_HANDLE_SINT LeftShift(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_SINT RightShift(PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_SINT OneComplement(PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_SINT OneComplement(PMC_HANDLE_SINT x) noexcept(false);

        _UINT32_T BitwiseAnd(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        _UINT64_T BitwiseAnd(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        _UINT32_T BitwiseAnd(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        _UINT64_T BitwiseAnd(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT BitwiseOr(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT ExclusiveOr(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        SIGN_T Compare(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        bool Equals(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_UINT GreatestCommonDivisor(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);
    };

}

#endif


/*
 * END OF FILE
 */