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

#ifndef PMC_RTNL_CPPINTERFACE_H
#define PMC_RTNL_CPPINTERFACE_H

#include "pmc_rtnl.h"

namespace Palmtree::Math::Core::Internal
{

    class __DLLEXPORT_RTNL PMC_RTNL_CppInterface
    {
    public:
        PMC_RTNL_CppInterface();
        ~PMC_RTNL_CppInterface();

        bool Initialize();

        PMC_STATUS_CODE GetConfigurationSettings(const wchar_t* key, wchar_t* value_buffer, _INT32_T value_buffer_size, _INT32_T* count);

        PMC_HANDLE_RTNL From(ThreadContext& tc, _INT32_T x) noexcept(false);
        PMC_HANDLE_RTNL From(ThreadContext& tc, _INT64_T x) noexcept(false);
        PMC_HANDLE_RTNL From(ThreadContext& tc, _UINT32_T x) noexcept(false);
        PMC_HANDLE_RTNL From(ThreadContext& tc, _UINT64_T x) noexcept(false);
        PMC_HANDLE_RTNL From(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false);
        PMC_HANDLE_RTNL From(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false);

        _INT32_T GetHashCode(PMC_HANDLE_RTNL p) noexcept(false);

        void CheckHandle(PMC_HANDLE_RTNL p) noexcept(false);

        void Dispose(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);

        _INT32_T GetBufferCount(PMC_HANDLE_RTNL p) noexcept(false);

        PMC_HANDLE_RTNL GetConstantValue(PMC_CONSTANT_VALUE_CODE type) noexcept(false);

        PMC_HANDLE_RTNL FromByteArray_RTNL(ThreadContext& tc, const unsigned char* buffer, size_t count) noexcept(false);
        size_t ToByteArray(PMC_HANDLE_RTNL p, unsigned char* buffer, size_t buffer_size) noexcept(false);

        PMC_HANDLE_RTNL Clone(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

        _UINT32_T ToUInt32(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
        _INT32_T ToInt32(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
        _UINT64_T ToUInt64(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
        _INT64_T ToInt64(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
        PMC_HANDLE_UINT ToUBigInt(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);
        PMC_HANDLE_SINT ToBigInt(ThreadContext& tc, PMC_HANDLE_RTNL p) noexcept(false);

        PMC_HANDLE_RTNL Negate(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

        PMC_HANDLE_RTNL Abs(ThreadContext& tc, PMC_HANDLE_RTNL x) noexcept(false);

        size_t ToString(ThreadContext& tc, PMC_HANDLE_RTNL x, const wchar_t* format, const PMC_NUMBER_FORMAT_INFO* format_option, wchar_t* buffer, size_t buffer_size) noexcept(false);
        void  InitializeNumberFormatInfo(PMC_NUMBER_FORMAT_INFO* info) noexcept(false);

        PMC_STATUS_CODE TryParse_RTNL(ThreadContext& tc, const wchar_t* source, PMC_NUMBER_STYLE_CODE number_styles, const PMC_NUMBER_FORMAT_INFO* format_option, PMC_HANDLE_RTNL* o) noexcept(false);

        PMC_HANDLE_RTNL Add(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_RTNL Add(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_RTNL Subtruct(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_RTNL Multiply(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        PMC_HANDLE_RTNL Divide(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_RTNL Divide(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        SIGN_T Compare(ThreadContext& tc, _INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, _INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        SIGN_T Compare(ThreadContext& tc, PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        bool Equals(_INT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(_INT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(PMC_HANDLE_SINT u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(_UINT32_T u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(_UINT64_T u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(PMC_HANDLE_UINT u, PMC_HANDLE_RTNL v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, _INT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, _INT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_SINT v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, _UINT32_T v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, _UINT64_T v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_UINT v) noexcept(false);
        bool Equals(PMC_HANDLE_RTNL u, PMC_HANDLE_RTNL v) noexcept(false);

        PMC_HANDLE_RTNL Pow(ThreadContext& tc, _INT32_T v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, _INT64_T v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, PMC_HANDLE_SINT v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, _UINT32_T v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, _UINT64_T v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, PMC_HANDLE_UINT v, _INT32_T e) noexcept(false);
        PMC_HANDLE_RTNL Pow(ThreadContext& tc, PMC_HANDLE_RTNL v, _INT32_T e) noexcept(false);

        PMC_HANDLE_RTNL Invert(ThreadContext& tc, _INT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, _INT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, PMC_HANDLE_SINT v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, _UINT32_T v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, _UINT64_T v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, PMC_HANDLE_UINT v) noexcept(false);
        PMC_HANDLE_RTNL Invert(ThreadContext& tc, PMC_HANDLE_RTNL v) noexcept(false);

        PMC_HANDLE_SINT Round(ThreadContext& tc, PMC_HANDLE_RTNL x, PMC_MIDPOINT_ROUNDING_CODE mode);
        PMC_HANDLE_RTNL Round(ThreadContext& tc, PMC_HANDLE_RTNL x, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode);
        PMC_HANDLE_SINT Floor(ThreadContext& tc, PMC_HANDLE_RTNL x);
        PMC_HANDLE_SINT Ceiling(ThreadContext& tc, PMC_HANDLE_RTNL x);

        _INT32_T FloorLog10(ThreadContext& tc, PMC_HANDLE_RTNL v);

        PMC_HANDLE_RTNL GenerateRationalRandomValue(ThreadContext& tc, PMC_HANDLE_SFMT handle, _INT32_T bit_count);
        PMC_HANDLE_RTNL GenerateRationalCryptoRandomValue(ThreadContext& tc, _BYTE_T* data, _INT32_T bit_count);
    };

}

#endif


/*
 * END OF FILE
 */