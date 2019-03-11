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
#include "pmc_exception.h"
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


    static NUMBER_HEADER* PMC_FromByteArrayForSINT_Imp(unsigned char* buffer, size_t count, char* o_sign)
    {
        if (count < 1)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        unsigned char header = buffer[0];
        unsigned char sign = header & 0x03;
        unsigned char header_reserved = header & 0xfc;
        if (header_reserved != 0)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        if (sign == 0)
        {
            if (count != 1)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            *o_sign = 0;
            return (&number_zero);
        }
        else if (sign == 2)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        else
        {
            __UNIT_TYPE bit_count = CountActualBitsFromBuffer(buffer + 1, count - 1);
            if (bit_count == 0)
            {
                *o_sign = 0;
                return (&number_zero);
            }
            else
            {
                ResourceHolderUINT root;
                NUMBER_HEADER* o_abs = root.AllocateNumber(bit_count);
                _COPY_MEMORY_BYTE(o_abs->BLOCK, buffer + 1, _DIVIDE_CEILING_SIZE(bit_count, 8));
                CommitNumber(o_abs);
                *o_sign = sign == 1 ? 1 : -1;
                root.UnlinkNumber(o_abs);
                return (o_abs);
            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_FromByteArrayForSINT(unsigned char* buffer, size_t count, char* o_sign) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"buffer");
        if (o_sign == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"o_sign");
        ResourceHolderUINT root;
        NUMBER_HEADER* o_abs = PMC_FromByteArrayForSINT_Imp(buffer, count, o_sign);
        root.HookNumber(o_abs);
#ifdef _DEBUG
        CheckNumber(o_abs);
#endif
        root.UnlinkNumber(o_abs);
        return ((PMC_HANDLE_UINT)o_abs);
    }

    static NUMBER_HEADER* PMC_FromByteArray_Imp(const unsigned char* buffer, size_t count)
    {
        if (count < 1)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        unsigned char header = buffer[0];
        unsigned char sign = header & 0x03;
        unsigned char header_reserved = header & 0xfc;
        if (header_reserved != 0)
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
        if (sign == 0)
        {
            if (count != 1)
                throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
            return (&number_zero);
        }
        else if (sign == 1)
        {
            __UNIT_TYPE bit_count = CountActualBitsFromBuffer(buffer + 1, count - 1);
            if (bit_count == 0)
                return (&number_zero);
            else
            {
                ResourceHolderUINT root;
                NUMBER_HEADER* o = root.AllocateNumber(bit_count);
                _COPY_MEMORY_BYTE(o->BLOCK, buffer + 1, _DIVIDE_CEILING_SIZE(bit_count, 8));
                CommitNumber(o);
                root.UnlinkNumber(o);
                return (o);
            }
        }
        else
            throw FormatException(L"与えられたバイト列が多倍長整数として認識できません。");
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_FromByteArray(const unsigned char* buffer, size_t count) noexcept(false)
    {
        if (buffer == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"buffer");
        ResourceHolderUINT root;
        NUMBER_HEADER* o = PMC_FromByteArray_Imp(buffer, count);
        root.HookNumber(o);
#ifdef _DEBUG
        CheckNumber(o);
#endif
        root.UnlinkNumber(o);
        return ((PMC_HANDLE_UINT)o);
    }

    size_t __PMC_CALL PMC_ToByteArrayForSINT(char p_sign, PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size) noexcept(false)
    {
        if (p == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"p");
        NUMBER_HEADER* np = (NUMBER_HEADER*)p;
        CheckNumber(np);
        size_t expected_abs_buffer_size = np->IS_ZERO ? 0 : _DIVIDE_CEILING_SIZE(np->UNIT_BIT_COUNT, 8);
        if (buffer != nullptr)
        {
            if (8 + np->UNIT_BIT_COUNT > sizeof(*buffer) * 8 * buffer_size)
                throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
            if (p_sign == 0)
            {
                if (!np->IS_ZERO)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bytes.cpp;PMC_ToByteArrayForSINT;1");
                buffer[0] = 0x00;
            }
            else if (p_sign > 0)
            {
                if (np->IS_ZERO)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bytes.cpp;PMC_ToByteArrayForSINT;2");
                buffer[0] = 0x01;
                _COPY_MEMORY_BYTE(buffer + 1, np->BLOCK, expected_abs_buffer_size);
            }
            else
            {
                if (np->IS_ZERO)
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bytes.cpp;PMC_ToByteArrayForSINT;3");
                buffer[0] = 0x03;
                _COPY_MEMORY_BYTE(buffer + 1, np->BLOCK, expected_abs_buffer_size);
            }
        }
        return (expected_abs_buffer_size + 1);
    }

    size_t __PMC_CALL PMC_ToByteArray(PMC_HANDLE_UINT p, unsigned char* buffer, size_t buffer_size)
    {
        if (p == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"p");
        NUMBER_HEADER* np = (NUMBER_HEADER*)p;
        CheckNumber(np);
        size_t expected_abs_buffer_size = np->IS_ZERO ? 0 : _DIVIDE_CEILING_SIZE(np->UNIT_BIT_COUNT, 8);
        if (buffer != nullptr)
        {
            if (8 + np->UNIT_BIT_COUNT > sizeof(*buffer) * 8 * buffer_size)
                throw InsufficientBufferException(L"出力先バッファのサイズが不足しています。");
            if (np->IS_ZERO)
                buffer[0] = 0x00;
            else
            {
                buffer[0] = 0x01;
                _COPY_MEMORY_BYTE(buffer + 1, np->BLOCK, expected_abs_buffer_size);
            }
        }
        return (expected_abs_buffer_size + 1);
    }

}


/*
 * END OF FILE
 */