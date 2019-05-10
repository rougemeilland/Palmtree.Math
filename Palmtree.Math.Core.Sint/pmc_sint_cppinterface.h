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

        PMC_HANDLE_SINT From(ThreadContext& tc, _INT32_T x) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, _INT64_T x) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, _UINT32_T x) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, _UINT64_T x) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, DECIMAL x, PMC_HANDLE_UINT* o_denominator) noexcept(false);
        PMC_HANDLE_SINT From(ThreadContext& tc, double x, PMC_HANDLE_UINT* o_denominator) noexcept(false);

        _INT32_T GetHashCode(PMC_HANDLE_SINT p) noexcept(false);

        void  CheckHandle(PMC_HANDLE_SINT p) noexcept(false);

        void  Dispose(ThreadContext& tc, PMC_HANDLE_SINT p) noexcept(false);

        _INT32_T GetBufferCount(PMC_HANDLE_SINT p) noexcept(false);

        PMC_HANDLE_SINT GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

        PMC_HANDLE_SINT FromByteArray_SINT(ThreadContext& tc, const unsigned char* buffer, size_t count) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_SINT p, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_SINT Clone(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        _INT32_T ToInt32(PMC_HANDLE_SINT p) noexcept(false);
        _INT64_T ToInt64(PMC_HANDLE_SINT p) noexcept(false);
        _UINT32_T ToUInt32(PMC_HANDLE_SINT p) noexcept(false);
        _UINT64_T ToUInt64(PMC_HANDLE_SINT p) noexcept(false);
        PMC_HANDLE_UINT ToUBigInt(ThreadContext& tc, PMC_HANDLE_SINT p) noexcept(false);
        DECIMAL ToDecimal(ThreadContext& tc, PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);
        double ToDouble(ThreadContext& tc, PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false);

        PMC_HANDLE_SINT Negate(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_SINT Negate(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_UINT Abs(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        size_t ToString(ThreadContext& tc, PMC_HANDLE_SINT x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        size_t ToString(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        void  InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

        PMC_STATUS_CODE TryParse_SINT(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o) noexcept(false);
        PMC_STATUS_CODE TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_SINT* o_numerator, PMC_HANDLE_UINT* o_denominator) noexcept(false);

        PMC_HANDLE_SINT Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT Increment(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_SINT Decrement(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        _INT32_T DivRem(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _INT32_T DivRem(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _INT64_T DivRem(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _INT64_T DivRem(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _UINT32_T DivRem(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _UINT64_T DivRem(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        _UINT32_T DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
        _UINT64_T DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_UINT DivRem(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q) noexcept(false);
        PMC_HANDLE_SINT DivRem(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q) noexcept(false);

        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT DivideExactly(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT LeftShift(ThreadContext& tc, PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_SINT RightShift(ThreadContext& tc, PMC_HANDLE_SINT p, _INT32_T n) noexcept(false);

        PMC_HANDLE_SINT OneComplement(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_SINT OneComplement(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        _UINT32_T BitwiseAnd(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        _UINT64_T BitwiseAnd(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        _UINT32_T BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        _UINT64_T BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseAnd(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT BitwiseOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_SINT ExclusiveOr(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        SIGN_T Compare(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        bool Equals(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        bool Equals(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        bool Equals(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_UINT GreatestCommonDivisor(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v) noexcept(false);

        PMC_HANDLE_UINT FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count, PMC_HANDLE_SINT* o_numerator) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_SINT p_numerator, PMC_HANDLE_UINT p_denominator, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT64_T v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT32_T v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT64_T v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* w_denominator) noexcept(false);
        PMC_HANDLE_SINT DivideRational(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* w_denominator) noexcept(false);

        PMC_HANDLE_SINT Round(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode);
        PMC_HANDLE_SINT Round(ThreadContext& tc, PMC_HANDLE_SINT x_numerator, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator);

        PMC_HANDLE_SINT Pow(ThreadContext& tc, _INT32_T v, _UINT32_T e) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, _INT64_T v, _UINT32_T e) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _UINT32_T e) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, _INT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, _INT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, _UINT32_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, _UINT64_T v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Pow(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, _INT32_T e, PMC_HANDLE_UINT* r_denominator) noexcept(false);

        _INT32_T FloorLog10(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator);

        PMC_HANDLE_SINT Invert(ThreadContext& tc, _INT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, _INT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, PMC_HANDLE_SINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, _UINT32_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, _UINT64_T v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT* r_denominator) noexcept(false);
        PMC_HANDLE_SINT Invert(ThreadContext& tc, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT* r_denominator) noexcept(false);

        PMC_HANDLE_SINT GenerateBigIntRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count);
        PMC_HANDLE_SINT GenerateBigIntCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count);
    };

}

#endif


/*
 * END OF FILE
 */