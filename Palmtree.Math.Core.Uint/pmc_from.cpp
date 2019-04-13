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


#include <windows.h>
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    NUMBER_OBJECT_UINT* From_UI_Imp(_UINT32_T x) noexcept(false)
    {
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* o = root.AllocateNumber(sizeof(x) * 8 - _LZCNT_ALT_32(x));
        o->BLOCK[0] = x;
        CommitNumber(o);
        root.UnlinkNumber(o);
        return (o);
    }

    NUMBER_OBJECT_UINT* From_UL_Imp(_UINT64_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(x))
        {
            // _UINT64_T を表現するのに 2 ワードでは不足する処理系には対応しない。
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;From_UL_Imp;1");
        }
        else if (sizeof(__UNIT_TYPE) < sizeof(x))
        {
            // _UINT64_T を表現するのに 1 ワードでは不足する(ちょうど 2 ワード必要とする)処理系の場合

            _UINT32_T x_hi;
            _UINT32_T x_lo = _FROMDWORDTOWORD(x, &x_hi);
            if (x_hi == 0)
            {
                ResourceHolderUINT root;
                __UNIT_TYPE x_bit_length = sizeof(x_lo) * 8 - _LZCNT_ALT_32(x_lo);
                NUMBER_OBJECT_UINT* o = root.AllocateNumber(x_bit_length);
                o->BLOCK[0] = x_lo;
                CommitNumber(o);
                root.UnlinkNumber(o);
                return (o);
            }
            else
            {
                ResourceHolderUINT root;
                __UNIT_TYPE x_bit_length = sizeof(x) * 8 - _LZCNT_ALT_32(x_hi);
                NUMBER_OBJECT_UINT* o = root.AllocateNumber(x_bit_length);
                o->BLOCK[0] = x_lo;
                o->BLOCK[1] = x_hi;
                CommitNumber(o);
                root.UnlinkNumber(o);
                return (o);
            }
        }
        else
        {
            // _UINT64_T を表現するのに 1 ワードで十分である処理系の場合
            ResourceHolderUINT root;
            __UNIT_TYPE x_bit_length = sizeof(x) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)x);
            NUMBER_OBJECT_UINT* o = root.AllocateNumber(x_bit_length);
            o->BLOCK[0] = (__UNIT_TYPE)x;
            CommitNumber(o);
            root.UnlinkNumber(o);
            return (o);
        }
    }

    PMC_HANDLE_UINT PMC_From_UI(_INT32_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(x))
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_I;1");
        ResourceHolderUINT root;
        SIGN_T x_sign;
        _UINT32_T x_abs = GET_ABS_32(x, &x_sign);
        NUMBER_OBJECT_UINT* no;
        if (x_sign < 0)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        else if (x_sign == 0)
            no = &number_object_uint_zero;
        else
            no = From_UL_Imp(x_abs);
        root.HookNumber(no);
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    PMC_HANDLE_UINT PMC_From_UL(_INT64_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(x))
        {
            // 32bit未満のCPUには未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_L;1");
        }
        ResourceHolderUINT root;
        SIGN_T x_sign;
        _UINT64_T x_abs = GET_ABS_64(x, &x_sign);
        NUMBER_OBJECT_UINT* no;
        if (x_sign < 0)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        else if (x_sign == 0)
            no = &number_object_uint_zero;
        else
            no = From_UL_Imp(x_abs);
        root.HookNumber(no);
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    PMC_HANDLE_UINT PMC_From_UI(_UINT32_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(x))
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_UI;1");
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* no;
        if (x == 0)
            no = &number_object_uint_zero;
        else
            no = From_UI_Imp(x);
        root.HookNumber(no);
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    PMC_HANDLE_UINT PMC_From_UL(_UINT64_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(x))
        {
            // 32bit未満のCPUには未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_UL;1");
        }
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* no;
        if (x == 0)
            no = &number_object_uint_zero;
        else
            no = From_UL_Imp(x);
        root.HookNumber(no);
        PMC_HANDLE_UINT o = GET_NUMBER_HANDLE(no);
        root.UnlinkNumber(no);
        return (o);
    }

    static NUMBER_OBJECT_UINT* PMC_From_DECIMAL_Imp(DECIMAL x, SIGN_T* o_sign, NUMBER_OBJECT_UINT** o_denominator) noexcept(false)
    {
        if (x.HI_32 == 0 && x.LO_64 == 0)
        {
            *o_sign = SIGN_ZERO;
            *o_denominator = &number_object_uint_one;
            return (&number_object_uint_zero);
        }

        ResourceHolderUINT root;

        *o_sign = x.SIGN != 0 ? SIGN_NEGATIVE : SIGN_POSITIVE;
        __UNIT_TYPE x_bit_length = (sizeof(x.HI_32) + sizeof(x.LO_64)) * 8;
        NUMBER_OBJECT_UINT* o_numerator = root.AllocateNumber(x_bit_length);
#ifdef _M_IX86
        _UINT32_T x_lo_hi;
        _UINT32_T x_lo_lo = _FROMDWORDTOWORD(x.LO_64, &x_lo_hi);
        o_numerator->BLOCK[0] = x_lo_lo;
        o_numerator->BLOCK[1] = x_lo_hi;
        o_numerator->BLOCK[2] = x.HI_32;
#elif defined(_M_X64)
        o_numerator->BLOCK[0] = x.LO_64;
        o_numerator->BLOCK[1] = x.HI_32;
#else
#error unknown platform
#endif
        CommitNumber(o_numerator);
        *o_denominator = PMC_Pow10_UI_Imp(x.SCALE);
        root.HookNumber(*o_denominator);
        NUMBER_OBJECT_UINT* gcd = PMC_GreatestCommonDivisor_UX_UX_Imp(o_numerator, *o_denominator);
        root.HookNumber(gcd);
        if (!gcd->IS_ONE)
        {
            o_numerator = PMC_DivideExactly_UX_UX_Imp(o_numerator, gcd);
            root.HookNumber(o_numerator);
            *o_denominator = PMC_DivideExactly_UX_UX_Imp(*o_denominator, gcd);
            root.HookNumber(*o_denominator);
        }
        root.UnlinkNumber(o_numerator);
        root.UnlinkNumber(*o_denominator);
        return (o_numerator);
    }

    PMC_HANDLE_UINT PMC_From_DECIMAL(DECIMAL x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* no_denominator;
        NUMBER_OBJECT_UINT* no_numerator = PMC_From_DECIMAL_Imp(x, o_sign, &no_denominator);
        root.HookNumber(no_numerator);
        root.HookNumber(no_denominator);
        PMC_HANDLE_UINT o_numerator = GET_NUMBER_HANDLE(no_numerator);
        *o_denominator = GET_NUMBER_HANDLE(no_denominator);
        root.UnlinkNumber(no_numerator);
        root.UnlinkNumber(no_denominator);
        return (o_numerator);
    }

    static NUMBER_OBJECT_UINT* PMC_From_DOUBLE_Imp(double x, SIGN_T* o_sign, NUMBER_OBJECT_UINT** o_denominator) noexcept(false)
    {
        _UINT64_T x_raw_bits = *(_UINT64_T*)&x;
        _UINT64_T x_mantissa_part = x_raw_bits & 0x000fffffffffffff;
        _UINT16_T x_exponent_part = ((_UINT16_T)(x_raw_bits >> 52) & (_UINT16_T)0x7ff);
        _BYTE_T x_sign_part = (_BYTE_T)(x_raw_bits >> 63) & (_BYTE_T)0x01;

        if (x_exponent_part == 0)
        {
            if (x_mantissa_part == 0)
            {
                // x が 0 である場合

                *o_sign = SIGN_ZERO;
                *o_denominator = &number_object_uint_one;
                return (&number_object_uint_zero);
            }
            else
            {
                // x が非正規化数 (非常に 0 に近い数) である場合

                *o_sign = SIGN_ZERO;
                *o_denominator = &number_object_uint_one;
                return (&number_object_uint_zero);
            }
        }
        else if (x_exponent_part == 0x7ff)
        {
            if (x_mantissa_part == 0)
            {
                // x が無限大である場合

                throw OverflowException(L"与えられた数値が無限大または NAN のため変換できません。");
            }
            else
            {
                // x が NAN である場合

                throw OverflowException(L"与えられた数値が無限大または NAN のため変換できません。");
            }
        }
        else
        {
            ResourceHolderUINT root;

            // 符号の作成
            *o_sign = x_sign_part != 0 ? SIGN_NEGATIVE : SIGN_POSITIVE;

            // 分子の作成
            __UNIT_TYPE x_bit_length = 53;
            NUMBER_OBJECT_UINT* o_numerator = root.AllocateNumber(x_bit_length);
            _UINT64_T mantissa_value = x_mantissa_part | 0x0010000000000000;
            _INT16_T exponent_value = (_INT16_T)x_exponent_part - 1023 - 52;
#ifdef _M_IX86
            _UINT32_T mantissa_value_hi;
            _UINT32_T mantissa_value_lo = _FROMDWORDTOWORD(mantissa_value, &mantissa_value_hi);

            // mantissa_value の最下位 bit が 0 の場合は、連続する 0 のビット数分だけ mantissa_value を右シフトし、更に exponent_value に加える
            if (mantissa_value_lo == 0)
            {
                // 仮数部の下位 32bit が 0 である場合

                mantissa_value_lo = mantissa_value_hi;
                mantissa_value_hi = 0;
                exponent_value += 32;

                int zero_count = _TZCNT_ALT_UNIT(mantissa_value_lo);
                if (zero_count > 0)
                {
                    mantissa_value_lo >>= zero_count;
                    exponent_value += zero_count;
                }

            }
            else
            {
                // 仮数部の下位 32bit が 0 ではない場合

                int zero_count = _TZCNT_ALT_UNIT(mantissa_value_lo);
                if (zero_count > 0)
                {
                    mantissa_value_lo = (mantissa_value_lo >> zero_count) | (mantissa_value_hi << (32 - zero_count));
                    mantissa_value_hi = (mantissa_value_hi >> zero_count);
                    exponent_value += zero_count;
                }
            }
            o_numerator->BLOCK[0] = mantissa_value_lo;
            o_numerator->BLOCK[1] = mantissa_value_hi;

#elif defined(_M_X64)
            // mantissa_value の最下位 bit が 0 の場合は、連続する 0 のビット数分だけ mantissa_value を右シフトし、更に exponent_value に加える
            int zero_count = _TZCNT_ALT_UNIT(mantissa_value);
            if (zero_count > 0)
            {
                mantissa_value >>= zero_count;
                exponent_value += zero_count;
            }
            o_numerator->BLOCK[0] = mantissa_value;
#else
#error unknown platform
#endif
            CommitNumber(o_numerator);
            // この時点で分子は奇数になっている

            // 分母の作成
            *o_denominator = &number_object_uint_one;
            root.HookNumber(*o_denominator);

            // 指数を分子/分母に反映させる
            if (exponent_value > 0)
            {
                o_numerator = PMC_LeftShift_UX_UI_Imp(o_numerator, exponent_value);
                root.HookNumber(o_numerator);
            }
            else if (exponent_value < 0)
            {
                *o_denominator = PMC_LeftShift_UX_UI_Imp(*o_denominator, -exponent_value);
                root.HookNumber(*o_denominator);
            }
            else
            {
                // nop
            }

            // 分子は奇数で、分母は2の累乗であり、分子と分母は既約であるため、約分は不要である

            root.UnlinkNumber(o_numerator);
            root.UnlinkNumber(*o_denominator);
            return (o_numerator);
        }
    }

    PMC_HANDLE_UINT PMC_From_DOUBLE(double x, SIGN_T* o_sign, PMC_HANDLE_UINT* o_denominator) noexcept(false)
    {
        ResourceHolderUINT root;
        NUMBER_OBJECT_UINT* no_denominator;
        NUMBER_OBJECT_UINT* no_numerator = PMC_From_DOUBLE_Imp(x, o_sign, &no_denominator);
        root.HookNumber(no_numerator);
        root.HookNumber(no_denominator);
        PMC_HANDLE_UINT o_numerator = GET_NUMBER_HANDLE(no_numerator);
        *o_denominator = GET_NUMBER_HANDLE(no_denominator);
        root.UnlinkNumber(no_numerator);
        root.UnlinkNumber(no_denominator);
        return (o_numerator);
    }

    PMC_STATUS_CODE Initialize_From(PROCESSOR_FEATURES *feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */