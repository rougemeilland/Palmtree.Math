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
#include "pmc_threadcontext.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_UINT number_object_uint_decimal_max;

    _INT32_T PMC_ToInt32_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(_UINT32_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt32_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT32_T) * 8)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        if (np->BLOCK[0] > 0x7fffffffU)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        return ((_INT32_T)np->BLOCK[0]);
    }

    _INT64_T PMC_ToInt64_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(_UINT64_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT64_T) * 8)
            throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        else
        {
            if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT)
            {
                // 値が 1 ワードで表現できる場合
                if (np->BLOCK[0] > 0x7fffffffffffffffUL)
                    throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
                return (np->BLOCK[0]);
            }
            else if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT * 2)
            {
                // 値が 2 ワードで表現できる場合
                if (np->BLOCK[1] > 0x7fffffffUL)
                    throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
                return (_FROMWORDTODWORD((_UINT32_T)np->BLOCK[1], (_UINT32_T)np->BLOCK[0]));
            }
            else
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;2");
        }
    }

    _UINT32_T PMC_ToUInt32_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(_UINT32_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt32_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT32_T) * 8)
            throw OverflowException(L"符号なし32bit整数への型変換に失敗しました。");
        return (np->IS_ZERO ? 0 : (_UINT32_T)np->BLOCK[0]);
    }

    _UINT64_T PMC_ToUInt64_UX(PMC_HANDLE_UINT p) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(_UINT64_T))
        {
            // 32bit未満のCPUは未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;1");
        }
        NUMBER_OBJECT_UINT* np = GET_NUMBER_OBJECT(p, L"p");
        if (np->UNIT_BIT_COUNT > sizeof(_UINT64_T) * 8)
            throw OverflowException(L"符号なし64bit整数への型変換に失敗しました。");
        if (np->IS_ZERO)
            return (0);
        else
        {
            if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT)
            {
                // 値が 1 ワードで表現できる場合
                return (np->BLOCK[0]);
            }
            else if (np->UNIT_BIT_COUNT <= __UNIT_TYPE_BIT_COUNT * 2)
            {
                // 値が 2 ワードで表現できる場合
                return (_FROMWORDTODWORD((_UINT32_T)np->BLOCK[1], (_UINT32_T)np->BLOCK[0]));
            }
            else
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_to.cpp;PMC_ToUInt64_UX;2");
        }
    }

    DECIMAL PMC_ToDecimal_R(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np_numerator = GET_NUMBER_OBJECT(p_numerator, L"p_numerator");
        NUMBER_OBJECT_UINT* np_denominator = GET_NUMBER_OBJECT(p_denominator, L"p_denominator");

        if (np_numerator->IS_ZERO)
        {
            // p == 0 の場合

            DECIMAL r = { 0, 0, 0, 0, 0 };
            return (r);
        }
        else
        {
            // p > 0 の場合

            ResourceHolderUINT root(tc);

            // 最大値のチェック
            NUMBER_OBJECT_UINT* t = PMC_Multiply_UX_UX_Imp(tc, &number_object_uint_decimal_max, np_denominator);
            root.HookNumber(t);
            // decimal.max >= p * 10^scale を満たす最大の scale を求める
            _INT32_T max_scale = PMC_FloorLog10_R_Imp(tc, t, np_numerator);
            if (max_scale < 0)
                throw OverflowException(L"decimal への型変換に失敗しました。");
            if (max_scale >= 29)
                max_scale = 28;

            _INT32_T scale = 0;
            while (scale < max_scale && !np_denominator->IS_ONE)
            {
                // scale が最大値に達しておらず、かつ分母が 1 ではない場合

                // p に 10 を掛ける
                np_numerator = PMC_Multiply_UX_UI_Imp(tc, np_numerator, 10);
                root.HookNumber(np_numerator);

                // p を約分する
                NUMBER_OBJECT_UINT* gcd = PMC_GreatestCommonDivisor_UX_UX_Imp(tc, np_numerator, np_denominator);
                root.HookNumber(gcd);
                if (!gcd->IS_ONE)
                {
                    // GCD が 1 ではない (== 既約ではない) 場合

                    // 分子と分母を GCD で割る
                    np_numerator = PMC_DivideExactly_UX_UX_Imp(tc, np_numerator, gcd);
                    root.HookNumber(np_numerator);
                    np_denominator = PMC_DivideExactly_UX_UX_Imp(tc, np_denominator, gcd);
                    root.HookNumber(np_denominator);
                }
                ++scale;
            }

            // 数値を丸める
            NUMBER_OBJECT_UINT* p_int_part = PMC_RoundZero_R_Imp(tc, p_sign, np_numerator, np_denominator, PMC_GetDefaultRoundingMode());
            root.HookNumber(p_int_part);

            // 復帰値を組み立てる

            DECIMAL r;
            r.RESERVED = 0;
            r.SIGN = p_sign < 0 ? 0x80 : 0x00;
            r.SCALE = scale;
#ifdef _M_IX86
            switch (p_int_part->UNIT_WORD_COUNT)
            {
            case 0:
                r.LO_64 = 0;
                r.HI_32 = 0;
                break;
            case 1:
                r.LO_64 = p_int_part->BLOCK[0];
                r.HI_32 = 0;
                break;
            case 2:
                r.LO_64 = _FROMWORDTODWORD(p_int_part->BLOCK[1], p_int_part->BLOCK[0]);
                r.HI_32 = 0;
                break;
            default:
                r.LO_64 = _FROMWORDTODWORD(p_int_part->BLOCK[1], p_int_part->BLOCK[0]);
                r.HI_32 = p_int_part->BLOCK[2];
                break;
            }
#elif defined (_M_X64)
            switch (p_int_part->UNIT_WORD_COUNT)
            {
            case 0:
                r.LO_64 = 0;
                r.HI_32 = 0;
                break;
            case 1:
                r.LO_64 = p_int_part->BLOCK[0];
                r.HI_32 = 0;
                break;
            default:
                r.LO_64 = p_int_part->BLOCK[0];
                r.HI_32 = (_UINT32_T)p_int_part->BLOCK[1];
                break;
            }
#else
#error unknown platform
#endif

            return (r);
        }
    }

    double PMC_ToDouble_R(ThreadContext& tc, SIGN_T p_sign, PMC_HANDLE_UINT p_numerator, PMC_HANDLE_UINT p_denominator) noexcept(false)
    {
        NUMBER_OBJECT_UINT* np_numerator = GET_NUMBER_OBJECT(p_numerator, L"p_numerator");
        NUMBER_OBJECT_UINT* np_denominator = GET_NUMBER_OBJECT(p_denominator, L"p_denominator");

        if (np_numerator->IS_ZERO)
        {
            // p == 0 の場合
            return (0.0);
        }

        // p > 0 の場合

        ResourceHolderUINT root(tc);

        if (np_numerator->UNIT_BIT_COUNT > 0x7fffffff)
            throw OverflowException(L"double への型変換に失敗しました。");
        if (np_denominator->UNIT_BIT_COUNT > 0x7fffffff)
            throw OverflowException(L"double への型変換に失敗しました。");
        _INT32_T scale = (_INT32_T)(np_numerator->UNIT_BIT_COUNT - np_denominator->UNIT_BIT_COUNT);
        if (scale > 0)
        {
            np_denominator = PMC_LeftShift_UX_UI_Imp(tc, np_denominator, scale);
            root.HookNumber(np_denominator);
        }
        else if (scale < 0)
        {
            np_numerator = PMC_LeftShift_UX_UI_Imp(tc, np_numerator, -scale);
            root.HookNumber(np_numerator);
        }
        else
        {
            // nop
        }
        if (PMC_Compare_UX_UX_Imp(np_numerator, np_denominator) < 0)
        {
            np_numerator = PMC_LeftShift_UX_UI_Imp(tc, np_numerator, 1);
            root.HookNumber(np_numerator);
            --scale;
        }

        // この時点で、1 <= np < 2 が成立する。(仮数部は必ず 1bit)

        // 更に、np を 52bit だけ左シフトする。
        np_numerator = PMC_LeftShift_UX_UI_Imp(tc, np_numerator, 52);
        root.HookNumber(np_numerator);

        // 数値を丸める
        NUMBER_OBJECT_UINT* int_part = PMC_RoundZero_R_Imp(tc, p_sign, np_numerator, np_denominator, PMC_GetDefaultRoundingMode());
        root.HookNumber(int_part);

        // int_part が丸めにより 54 bit になっている場合は 1bit だけ右シフトする。
        if (int_part->UNIT_BIT_COUNT > 53)
        {
            int_part = PMC_RightShift_UX_UI_Imp(tc, int_part, 1);
            root.HookNumber(int_part);
            ++scale;
        }

        // この時点で int_part は 53bit (doubleの有効桁数) あるはず。
        if (int_part->UNIT_BIT_COUNT != 53)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_to.cpp;PMC_ToDouble_R;1");

        // 仮数部の取得
#ifdef _M_IX86
        _UINT64_T mantissa_ulong = _FROMWORDTODWORD(int_part->BLOCK[1], int_part->BLOCK[0]);
#elif defined (_M_X64)
        _UINT64_T mantissa_ulong = int_part->BLOCK[0];
#else
#error unknown platform
#endif

        // 復帰値の作成
        _UINT64_T result;
        if (scale > 1023)
        {
            // double で表現するには数値の絶対値が大きすぎる場合

            // 無限大を返す。
            result = 0x7ff0000000000000;
            if (p_sign < 0)
                result = result | 0x8000000000000000;
        }
        else if (scale < -1022)
        {
            // double で表現するには数値の絶対値が小さすぎる場合

            // 非正規化数を返す
            result = 0x0000000000000001;
            if (p_sign < 0)
                result = result | 0x8000000000000000;
        }
        else
        {
            // double で表現できる場合
            result = mantissa_ulong & 0x000fffffffffffff;
            result = result | (((_UINT64_T)scale + 1023) << 52);
            if (p_sign < 0)
                result = result | 0x8000000000000000;
        }

        return (*(double*)&result);
    }

    PMC_STATUS_CODE Initialize_To(PROCESSOR_FEATURES *feature)
    {
        ThreadContext tc;

        ResourceHolderUINT root(tc);

        try
        {
            root.AttatchStaticNumber(&number_object_uint_decimal_max, 96);
#ifdef _M_IX86
            number_object_uint_decimal_max.BLOCK[0] = 0xffffffff;
            number_object_uint_decimal_max.BLOCK[1] = 0xffffffff;
            number_object_uint_decimal_max.BLOCK[2] = 0xffffffff;
#elif defined (_M_X64)
            number_object_uint_decimal_max.BLOCK[0] = 0xffffffffffffffff;
            number_object_uint_decimal_max.BLOCK[1] = 0x00000000ffffffff;
#else
#error unknown platform
#endif
            CommitNumber(tc, &number_object_uint_decimal_max);

            root.UnlinkStatickNumber(&number_object_uint_decimal_max);

            return (PMC_STATUS_OK);
        }
        catch (const BadBufferException& ex)
        {
            return (ex.GetStatusCode());
        }
        catch (const Exception& ex)
        {
            if (!tc.VerifyAllocationCount(0, false))
                return (PMC_STATUS_BAD_BUFFER);
            return (ex.GetStatusCode());
        }
    }

}


/*
 * END OF FILE
 */