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


#include <windows.h>
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static __UNIT_TYPE CountActualBitsFromBuffer(const unsigned char* p, size_t count)
    {
        p += count;
        while (count > 0)
        {
            --p;
            if (*p != 0)
                return (count * 8 - _LZCNT_ALT_8(*p));
            --count;
        }
        return (0);
    }


    static const unsigned char* PMC_FromByteArray_Imp(const unsigned char* buffer, size_t count, SIGN_T* o_sign, NUMBER_OBJECT_UINT** o_abs)
    {
        if (count < 1)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        unsigned char header = buffer[0];
        unsigned char sign_bit = header & 0x03;
        unsigned char length_bit = header & 0x0c;
        unsigned char header_reserved = header & 0xf0;
        if (header_reserved != 0)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        size_t data_length;
        const unsigned char* data_ptr;
        switch (length_bit)
        {
        case 0x00:
            if (count < 1 + 1)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            if (sizeof(size_t) * 8 < 8)
                throw OverflowException(L"与えられたバイト列を多倍長整数として読み込もうとしてオーバーフローが発生しました。");
            data_length = buffer[1];
            data_ptr= &buffer[1 + 1];
            if (count < 1 + 1+ data_length)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            break;
        case 0x04:
            if (count < 1 + 2)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            if (sizeof(size_t) * 8 < 16)
                throw OverflowException(L"与えられたバイト列を多倍長整数として読み込もうとしてオーバーフローが発生しました。");
            data_length = buffer[1] | ((size_t)buffer[2] << 8);
            data_ptr = &buffer[1 + 2];
            if (count < 1 + 2 + data_length)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            break;
        case 0x08:
            if (count < 1 + 4)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            if (sizeof(size_t) * 8 < 32)
                throw OverflowException(L"与えられたバイト列を多倍長整数として読み込もうとしてオーバーフローが発生しました。");
            data_length = buffer[1] | ((size_t)buffer[2] << 8) | ((size_t)buffer[3] << 16) | ((size_t)buffer[4] << 24);
            data_ptr = &buffer[1 + 4];
            if (count < 1 + 4 + data_length)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            break;
        case 0x0c:
            if (count < 1 + 8)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            if (sizeof(size_t) * 8 < 64)
                throw OverflowException(L"与えられたバイト列を多倍長整数として読み込もうとしてオーバーフローが発生しました。");
#ifdef _M_IX86
            throw OverflowException(L"与えられたバイト列を多倍長整数として読み込もうとしてオーバーフローが発生しました。");
#elif defined(_M_X64)
            data_length = buffer[1] | ((size_t)buffer[2] << 8) | ((size_t)buffer[3] << 16) | ((size_t)buffer[4] << 24) | ((size_t)buffer[5] << 32) | ((size_t)buffer[6] << 40) | ((size_t)buffer[7] << 48) | ((size_t)buffer[8] << 56);
            data_ptr = &buffer[1 + 8];
            if (count < 1 + 8 + data_length)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
#else
#error unknown platform
#endif
            break;
        default:
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        }
        if (sign_bit == 0)
        {
            if (data_length != 0)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            *o_sign = SIGN_ZERO;
            *o_abs = &number_object_uint_zero;
            return (data_ptr + data_length);
        }
        else if (sign_bit == 2)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        else
        {
            __UNIT_TYPE bit_count = CountActualBitsFromBuffer(data_ptr, data_length);
            if (bit_count == 0)
            {
                *o_sign = SIGN_ZERO;
                *o_abs = &number_object_uint_zero;
                return (data_ptr + data_length);
            }
            else
            {
                ResourceHolderUINT root;
                NUMBER_OBJECT_UINT* no_abs = root.AllocateNumber(bit_count);
                _COPY_MEMORY_BYTE(no_abs->BLOCK, data_ptr, _DIVIDE_CEILING_SIZE(bit_count, 8));
                CommitNumber(no_abs);
                *o_sign = sign_bit == 1 ? SIGN_POSITIVE : SIGN_NEGATIVE;
                root.UnlinkNumber(no_abs);
                *o_abs = no_abs;
                return (data_ptr + data_length);
            }
        }
    }

    PMC_HANDLE_UINT PMC_FromByteArrayForRTNL(const unsigned char* buffer, size_t count, SIGN_T* o_numerator_sign, PMC_HANDLE_UINT* o_numerator_abs) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        if (o_numerator_sign == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o_numerator_sign");
        if (o_numerator_abs == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o_numerator_abs");
        ResourceHolderUINT root;
        if (count < 1)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        if (buffer[0] != 0x10)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");

        const unsigned char* next_ptr = &buffer[1];

        SIGN_T no_numerator_sign;
        NUMBER_OBJECT_UINT* no_numerator_abs;
        next_ptr = PMC_FromByteArray_Imp(next_ptr, buffer + count - next_ptr, &no_numerator_sign, &no_numerator_abs);
        root.HookNumber(no_numerator_abs);
        
        SIGN_T no_denominator_sign;
        NUMBER_OBJECT_UINT* no_denominator_abs;
        next_ptr = PMC_FromByteArray_Imp(next_ptr, buffer + count - next_ptr, &no_denominator_sign, &no_denominator_abs);
        root.HookNumber(no_denominator_abs);

        if (next_ptr != buffer + count)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");

        if (no_denominator_sign <= 0)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");

        *o_numerator_abs = GET_NUMBER_HANDLE(no_numerator_abs);
        *o_numerator_sign = no_numerator_sign;
        PMC_HANDLE_UINT o_denominator_abs = GET_NUMBER_HANDLE(no_denominator_abs);
        root.UnlinkNumber(no_numerator_abs);
        root.UnlinkNumber(no_denominator_abs);
        return (o_denominator_abs);
    }

    PMC_HANDLE_UINT PMC_FromByteArrayForSINT(const unsigned char* buffer, size_t count, SIGN_T* o_sign) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        if (o_sign == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"o_sign");
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* no_abs;
        const unsigned char* next_ptr = PMC_FromByteArray_Imp(buffer, count, o_sign, &no_abs);
        if (next_ptr != buffer + count)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        root.HookNumber(no_abs);
        PMC_HANDLE_UINT o_abs = GET_NUMBER_HANDLE(no_abs);
        root.UnlinkNumber(no_abs);
        return (o_abs);
    }

    PMC_HANDLE_UINT PMC_FromByteArray(const unsigned char* buffer, size_t count) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"buffer");
        ResourceHolderUINT root;
        SIGN_T o_sign;
        NUMBER_OBJECT_UINT* no_abs;
        const unsigned char* next_ptr = PMC_FromByteArray_Imp(buffer, count, &o_sign, &no_abs);
        root.HookNumber(no_abs);
        if (next_ptr != buffer + count)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        if (o_sign < 0)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no_abs);
        root.UnlinkNumber(no_abs);
        return (o);
    }

    static size_t SetSizeField(size_t count, unsigned char* buffer, size_t buffer_length, unsigned char* header)
    {
        if (count <= 0xff)
        {
            if (buffer != nullptr)
            {
                if (buffer_length < 1)
                    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
                buffer[0] = (unsigned char)count;
            }
            if (header != nullptr)
                *header |= 0x00;
            return (1);
        }
        else if (count <= 0xffff)
        {
            if (buffer != nullptr)
            {
                if (buffer_length < 2)
                    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
                buffer[0] = (unsigned char)count;
                buffer[1] = (unsigned char)(count >> 8);
            }
            if (header != nullptr)
                *header |= 0x04;
            return (2);
        }
        else if (count <= 0xffffffff)
        {
            if (buffer != nullptr)
            {
                if (buffer_length < 4)
                    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
                buffer[0] = (unsigned char)count;
                buffer[1] = (unsigned char)(count >> 8);
                buffer[2] = (unsigned char)(count >> 16);
                buffer[3] = (unsigned char)(count >> 24);
            }
            if (header != nullptr)
                *header |= 0x08;
            return (4);
        }
        else
        {
#ifdef _M_IX86
            // 32bit 版ではこの直前の条件判断が常に成功するためこのルートには到達しないはずではあるが、念のため例外を発生させておく。
            // 到達条件があり得ないため、例外のメッセージの内容もよくわからないものになってしまっている。＾＾；
            throw OverflowException(L"与えられた多倍長整数をとバイト列へ書き込もうとしてオーバーフローが発生しました。");
#elif defined(_M_X64)
            if (buffer != nullptr)
            {
                if (buffer_length < 8)
                    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
                buffer[0] = (unsigned char)count;
                buffer[1] = (unsigned char)(count >> 8);
                buffer[2] = (unsigned char)(count >> 16);
                buffer[3] = (unsigned char)(count >> 24);
                buffer[4] = (unsigned char)(count >> 32);
                buffer[5] = (unsigned char)(count >> 40);
                buffer[6] = (unsigned char)(count >> 48);
                buffer[7] = (unsigned char)(count >> 56);
            }
            if (header != nullptr)
                *header |= 0x0c;
            return (8);
#else
#endif
        }
    }

    size_t PMC_ToByteArray_Imp(SIGN_T p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        size_t expected_abs_buffer_size = np->IS_ZERO ? 0 : _DIVIDE_CEILING_SIZE(np->UNIT_BIT_COUNT, 8);
        size_t size_field_length = SetSizeField(expected_abs_buffer_size, nullptr, 0, nullptr);
        size_t expected_total_size = 1 + size_field_length + expected_abs_buffer_size;
        if (buffer == nullptr)
            return (expected_total_size);
        if (np->IS_ZERO)
        {
            unsigned char* next_ptr = buffer;
            if (buffer_size < 2)
                throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
            *next_ptr++ = 0x00;
            *next_ptr++ = 0x00;
            return (next_ptr - buffer);
        }
        else
        {
            if (p_sign == 0)
                throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bytes.cpp;PMC_ToByteArrayForSINT;3");
            if (buffer_size < 1)
                throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
            unsigned char header = p_sign > 0 ? 0x01 : 0x03;
            unsigned char* next_ptr = buffer + 1;
            next_ptr += SetSizeField(expected_abs_buffer_size, next_ptr, buffer + buffer_size - next_ptr, &header);
            buffer[0] = header;
            if (buffer + buffer_size < next_ptr + expected_abs_buffer_size)
                throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
            _COPY_MEMORY_BYTE(next_ptr, np->BLOCK, expected_abs_buffer_size);
            next_ptr += expected_abs_buffer_size;
            return (next_ptr - buffer);
        }
    }

    size_t PMC_ToByteArrayForRTNL(SIGN_T p_numerator_sign, PMC_HANDLE_UINT p_numerator_abs, PMC_HANDLE_UINT p_denominator, unsigned char* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np_numerator_abs = GET_NUMBER_OBJECT(p_numerator_abs, L"p_numerator_abs");
        NUMBER_OBJECT_UINT* np_denominator = GET_NUMBER_OBJECT(p_denominator, L"p_denominator");
        size_t expected_total_size = 1 + PMC_ToByteArray_Imp(p_numerator_sign, p_numerator_abs, nullptr, 0) + PMC_ToByteArray_Imp(SIGN_POSITIVE, p_denominator, nullptr, 0);
        if (buffer == nullptr)
            return (expected_total_size);
        if (buffer_size < 1)
            throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
        unsigned char* next_ptr = buffer;
        *next_ptr++ = 0x10;
        if (buffer + buffer_size < next_ptr)
            throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
        next_ptr += PMC_ToByteArray_Imp(p_numerator_sign, p_numerator_abs, next_ptr, buffer + buffer_size - next_ptr);
        if (buffer + buffer_size < next_ptr)
            throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
        next_ptr += PMC_ToByteArray_Imp(SIGN_POSITIVE, p_denominator, next_ptr, buffer + buffer_size - next_ptr);
        return (next_ptr - buffer);
    }

    size_t PMC_ToByteArrayForSINT(SIGN_T p_sign, PMC_HANDLE_UINT p_abs, unsigned char* buffer, size_t buffer_size) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np_numerator_abs = GET_NUMBER_OBJECT(p_abs, L"p_abs");
        size_t expected_total_size = PMC_ToByteArray_Imp(p_sign, p_abs, nullptr, 0);
        if (buffer == nullptr)
            return (expected_total_size);
        unsigned char* next_ptr = buffer;
        //意味がないチェックのため削除
        //if (buffer + buffer_size < next_ptr)
        //    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
        next_ptr += PMC_ToByteArray_Imp(p_sign, p_abs, next_ptr, buffer + buffer_size - next_ptr);
        return (next_ptr - buffer);
    }

    size_t PMC_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size)
    {
        NUMBER_OBJECT_UINT* np_numerator_abs = GET_NUMBER_OBJECT(p, L"p");
        size_t expected_total_size = PMC_ToByteArray_Imp(SIGN_POSITIVE, p, nullptr, 0);
        if (buffer == nullptr)
            return (expected_total_size);
        unsigned char* next_ptr = buffer;
        //意味がないチェックのため削除
        //if (buffer + buffer_size < next_ptr)
        //    throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
        next_ptr += PMC_ToByteArray_Imp(SIGN_POSITIVE, p, next_ptr, buffer + buffer_size - next_ptr);
        return (next_ptr - buffer);
    }

}


/*
 * END OF FILE
 */