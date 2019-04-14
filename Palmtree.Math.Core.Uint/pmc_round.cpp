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


namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_UINT* Round_R_Imp(ThreadContext& tc, ResourceHolderUINT& root, PMC_MIDPOINT_ROUNDING_CODE mode, SIGN_T r_numerator_sign, NUMBER_OBJECT_UINT* r_numerator_abs, NUMBER_OBJECT_UINT* frac_part_numerator, NUMBER_OBJECT_UINT* frac_part_denominator)
    {
        if (frac_part_numerator->IS_ZERO)
            return (r_numerator_abs);
        switch (mode)
        {
        case PMC_MIDPOINT_ROUNDING_DOWN:
            // 0 に近づくように丸める。
            return (r_numerator_abs);
        case PMC_MIDPOINT_ROUNDING_UP:
            // 0から離れるように丸める。
            r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
            root.HookNumber(r_numerator_abs);
            return (r_numerator_abs);
        case PMC_MIDPOINT_ROUNDING_CEILING:
            // 正の無限大に近づくように丸める。
            if (r_numerator_sign >= 0)
            {
                r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
                root.HookNumber(r_numerator_abs);
            }
            return (r_numerator_abs);
        case PMC_MIDPOINT_ROUNDING_FLOOR:
            // 負の無限大に近づくように丸める。
            if (r_numerator_sign < 0)
            {
                r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
                root.HookNumber(r_numerator_abs);
            }
            return (r_numerator_abs);
        default:
            break;
        }
        // 端数 (fraction_part) と 1/2 を比較する 
        NUMBER_OBJECT_UINT* frac_part_numerator2 = PMC_LeftShift_UX_UI_Imp(tc, frac_part_numerator, 1);
        root.HookNumber(frac_part_numerator2);
        _INT32_T c = PMC_Compare_UX_UX_Imp(frac_part_numerator2, frac_part_denominator);
        if (c < 0)
        {
            // frac_part は 1/2 に満たないため、r_abs に対しては何もしない
            return (r_numerator_abs);
        }
        else if (c > 0)
        {
            // frac_part は 1/2 を超えているため、r_abs をインクリメントする
            r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
            root.HookNumber(r_numerator_abs);
            return (r_numerator_abs);
        }
        else
        {
            // frac_part は 1/2 ちょうどであるため、mode に従って r_abs をインクリメントする
            switch (mode)
            {
            case PMC_MIDPOINT_ROUNDING_HALF_UP:
                r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
                root.HookNumber(r_numerator_abs);
                return (r_numerator_abs);
            case PMC_MIDPOINT_ROUNDING_HALF_DOWN:
                return (r_numerator_abs);
            case PMC_MIDPOINT_ROUNDING_HALF_EVEN:
                if (!r_numerator_abs->IS_EVEN)
                {
                    r_numerator_abs = PMC_Increment_UX_Imp(tc, r_numerator_abs);
                    root.HookNumber(r_numerator_abs);
                }
                return (r_numerator_abs);
            default:
                throw ArgumentException(L"引数 mode の値に誤りがあります。");
            }
        }
    }

    NUMBER_OBJECT_UINT* PMC_Round_R_Imp(ThreadContext& tc, SIGN_T x_numerator_sign, NUMBER_OBJECT_UINT* nx_numerator_abs, NUMBER_OBJECT_UINT* nx_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, NUMBER_OBJECT_UINT** r_denominator)
    {
        if (decimals >= 0)
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* nr_denominator = PMC_Pow10_UI_Imp(tc, decimals);
            root.HookNumber(nr_denominator);
            nx_numerator_abs = PMC_Multiply_UX_UX_Imp(tc, nx_numerator_abs, nr_denominator);
            root.HookNumber(nx_numerator_abs);
            NUMBER_OBJECT_UINT* nr_numerator_abs;
            NUMBER_OBJECT_UINT* frac_part_numerator = PMC_DivRem_UX_UX_Imp(tc, nx_numerator_abs, nx_denominator, &nr_numerator_abs);
            root.HookNumber(nr_numerator_abs);
            root.HookNumber(frac_part_numerator);
            nr_numerator_abs = Round_R_Imp(tc, root, mode, x_numerator_sign, nr_numerator_abs, frac_part_numerator, nx_denominator);
            NUMBER_OBJECT_UINT* gcd = PMC_GreatestCommonDivisor_UX_UX_Imp(tc, nr_numerator_abs, nr_denominator);
            root.HookNumber(gcd);
            if (!gcd->IS_ONE)
            {
                nr_numerator_abs = PMC_DivideExactly_UX_UX_Imp(tc, nr_numerator_abs, gcd);
                root.HookNumber(nr_numerator_abs);
                nr_denominator = PMC_DivideExactly_UX_UX_Imp(tc, nr_denominator, gcd);
                root.HookNumber(nr_denominator);
            }
            PMC_HANDLE_UINT r_numerator_abs = GET_NUMBER_HANDLE(nr_numerator_abs);
            *r_denominator = nr_denominator;
            root.UnlinkNumber(nr_numerator_abs);
            root.UnlinkNumber(nr_denominator);
            return (nr_numerator_abs);
        }
        else
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* factor = PMC_Pow10_UI_Imp(tc, -decimals);
            root.HookNumber(factor);
            NUMBER_OBJECT_UINT* frac_part_denominator = PMC_Multiply_UX_UX_Imp(tc, nx_denominator, factor);
            root.HookNumber(frac_part_denominator);
            NUMBER_OBJECT_UINT* nr_numerator_abs;
            NUMBER_OBJECT_UINT* frac_part_numerator = PMC_DivRem_UX_UX_Imp(tc, nx_numerator_abs, frac_part_denominator, &nr_numerator_abs);
            root.HookNumber(nr_numerator_abs);
            root.HookNumber(frac_part_numerator);
            nr_numerator_abs = Round_R_Imp(tc, root, mode, x_numerator_sign, nr_numerator_abs, frac_part_numerator, frac_part_denominator);
            nr_numerator_abs = PMC_Multiply_UX_UX_Imp(tc, nr_numerator_abs, factor);
            root.HookNumber(nr_numerator_abs);
            PMC_HANDLE_UINT r_numerator_abs = GET_NUMBER_HANDLE(nr_numerator_abs);
            *r_denominator = &number_object_uint_one;
            root.UnlinkNumber(nr_numerator_abs);
            return (nr_numerator_abs);
        }
    }

    NUMBER_OBJECT_UINT* PMC_Round_R_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* x_numerator_abs, NUMBER_OBJECT_UINT* x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, NUMBER_OBJECT_UINT** r_denominator)
    {
        // x の符号が不明なので、PMC_MIDPOINT_ROUNDING_CEILING と PMC_MIDPOINT_ROUNDING_FLOOR は使用不可能
        if (mode == PMC_MIDPOINT_ROUNDING_CEILING || mode == PMC_MIDPOINT_ROUNDING_FLOOR)
            throw ArgumentException(L"mode に PMC_MIDPOINT_ROUNDING_CEILING または PMC_MIDPOINT_ROUNDING_FLOOR を指定できません。");

        return (PMC_Round_R_Imp(tc, SIGN_POSITIVE, x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    // mode で指定された方法により、符号が省略された有理数 x を小数以下を 0 桁に丸める。
    PMC_HANDLE_UINT PMC_RoundZero_R(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        // x の符号が不明なので、PMC_MIDPOINT_ROUNDING_CEILING と PMC_MIDPOINT_ROUNDING_FLOOR は使用不可能
        if (mode == PMC_MIDPOINT_ROUNDING_CEILING || mode == PMC_MIDPOINT_ROUNDING_FLOOR)
            throw ArgumentException(L"mode に PMC_MIDPOINT_ROUNDING_CEILING または PMC_MIDPOINT_ROUNDING_FLOOR を指定できません。");

        return (PMC_RoundZero_R(tc, SIGN_POSITIVE, x_numerator_abs, x_denominator, mode));
    }

    // mode で指定された方法により、有理数 x を小数以下を 0 桁に丸める。
    PMC_HANDLE_UINT PMC_RoundZero_R(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, PMC_MIDPOINT_ROUNDING_CODE mode)
    {
        NUMBER_OBJECT_UINT* nx_numerator_abs = GET_NUMBER_OBJECT(x_numerator_abs, L"x_numerator_abs");
        NUMBER_OBJECT_UINT* nx_denominator = GET_NUMBER_OBJECT(x_denominator, L"x_denominator");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nr_abs;
        NUMBER_OBJECT_UINT* frac_part_numerator = PMC_DivRem_UX_UX_Imp(tc, nx_numerator_abs, nx_denominator, &nr_abs);
        root.HookNumber(nr_abs);
        root.HookNumber(frac_part_numerator);
        nr_abs = Round_R_Imp(tc, root, mode, x_numerator_sign, nr_abs, frac_part_numerator, nx_denominator);
        PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr_abs);
        root.UnlinkNumber(nr_abs);
        return (r);
    }

    // mode で指定された方法により、符号が省略された有理数 x の小数以下を decimals 桁に丸める。
    PMC_HANDLE_UINT PMC_Round_R(ThreadContext& tc, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator)
    {
        // x の符号が不明なので、PMC_MIDPOINT_ROUNDING_CEILING と PMC_MIDPOINT_ROUNDING_FLOOR は使用不可能
        if (mode == PMC_MIDPOINT_ROUNDING_CEILING || mode == PMC_MIDPOINT_ROUNDING_FLOOR)
            throw ArgumentException(L"mode に PMC_MIDPOINT_ROUNDING_CEILING または PMC_MIDPOINT_ROUNDING_FLOOR を指定できません。");

        return (PMC_Round_R(tc, SIGN_POSITIVE, x_numerator_abs, x_denominator, decimals, mode, r_denominator));
    }

    // mode で指定された方法により、有理数 x の小数以下を decimals 桁に丸める。
    PMC_HANDLE_UINT PMC_Round_R(ThreadContext& tc, SIGN_T x_numerator_sign, PMC_HANDLE_UINT x_numerator_abs, PMC_HANDLE_UINT x_denominator, _INT32_T decimals, PMC_MIDPOINT_ROUNDING_CODE mode, PMC_HANDLE_UINT* r_denominator)
    {
        NUMBER_OBJECT_UINT* nx_numerator_abs = GET_NUMBER_OBJECT(x_numerator_abs, L"x_numerator_abs");
        NUMBER_OBJECT_UINT* nx_denominator = GET_NUMBER_OBJECT(x_denominator, L"x_denominator");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nr_denominator;
        NUMBER_OBJECT_UINT* nr_numerator_abs = PMC_Round_R_Imp(tc, x_numerator_sign, nx_numerator_abs, nx_denominator, decimals, mode, &nr_denominator);
        root.HookNumber(nr_denominator);
        root.HookNumber(nr_numerator_abs);
        PMC_HANDLE_UINT r_numerator_abs = GET_NUMBER_HANDLE(nr_numerator_abs);
        *r_denominator = GET_NUMBER_HANDLE(nr_denominator);
        root.UnlinkNumber(nr_numerator_abs);
        root.UnlinkNumber(nr_denominator);
        return (r_numerator_abs);
    }

}


/*
 * END OF FILE
 */