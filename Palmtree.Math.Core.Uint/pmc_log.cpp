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
#include <math.h>
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{
    static double log10_2; // 0.3010299956639811952137388947244

    _INT32_T PMC_FloorLog10_R_Imp(NUMBER_OBJECT_UINT* v_numerator, NUMBER_OBJECT_UINT* v_denominator)
    {
        if (v_numerator->IS_ZERO)
            throw ArithmeticException(L"0 の対数は未定義です。");
        if (v_denominator->IS_ZERO)
            throw ArithmeticException(L"分数の分母が 0 です。");

        _INT32_T c = PMC_Compare_UX_UX_Imp(v_numerator, v_denominator);
        if (c == 0)
        {
            // v == 1 の場合
            return (0);
        }
        else if (c > 0)
        {
            // v > 1  の場合

            ResourceHolderUINT root;
            __UNIT_TYPE diff = v_numerator->UNIT_BIT_COUNT - v_denominator->UNIT_BIT_COUNT;
            if (diff > 0)
                --diff;
            if (diff > 0x7fffffffU)
                throw ArgumentOutOfRangeException(L"与えられた数値が計算可能な範囲を超えています。");
            _INT32_T result_value = (_INT32_T)floor(diff * log10_2);
            NUMBER_OBJECT_UINT* ten_n = PMC_Pow_UX_UI_Imp(&number_object_uint_ten, result_value);
            root.HookNumber(ten_n);
            NUMBER_OBJECT_UINT* v_denominator_times_ten_n = PMC_Multiply_UX_UX_Imp(v_denominator, ten_n);
            root.HookNumber(v_denominator_times_ten_n);
            while (true)
            {
                _INT32_T c = PMC_Compare_UX_UX_Imp(v_numerator, v_denominator_times_ten_n);
                if (c < 0)
                    return (result_value - 1);
                if (c == 0)
                    return (result_value);
                v_denominator_times_ten_n = PMC_Multiply_UX_UI_Imp(v_denominator_times_ten_n, 10);
                root.HookNumber(v_denominator_times_ten_n);
                ++result_value;
            }
        }
        else
        {
            // v < 1 の場合

            ResourceHolderUINT root;
            __UNIT_TYPE diff = v_denominator->UNIT_BIT_COUNT - v_numerator->UNIT_BIT_COUNT;
            if (diff > 0)
                --diff;
            if (diff > 0x7fffffffU)
                throw ArgumentOutOfRangeException(L"与えられた数値が計算可能な範囲を超えています。");
            _INT32_T result_value = -(_INT32_T)floor(diff * log10_2);
            NUMBER_OBJECT_UINT* ten_n = PMC_Pow_UX_UI_Imp(&number_object_uint_ten, -result_value);
            root.HookNumber(ten_n);
            NUMBER_OBJECT_UINT* v_numerator_times_ten_n = PMC_Multiply_UX_UX_Imp(v_numerator, ten_n);
            root.HookNumber(v_numerator_times_ten_n);
            while (true)
            {
                _INT32_T c = PMC_Compare_UX_UX_Imp(v_numerator_times_ten_n, v_denominator);
                if (c >= 0)
                    return (result_value);
                v_numerator_times_ten_n = PMC_Multiply_UX_UI_Imp(v_numerator_times_ten_n, 10);
                root.HookNumber(v_numerator_times_ten_n);
                --result_value;
            }
        }
    }

    _UINT32_T PMC_FloorLog10_UX_Imp(NUMBER_OBJECT_UINT* v)
    {
        return (PMC_FloorLog10_R_Imp(v, &number_object_uint_one));
    }

    _UINT32_T PMC_FloorLog10_UX(PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_FloorLog10_UX_Imp(nv));
    }

    _INT32_T PMC_FloorLog10_R(PMC_HANDLE_UINT v_numerator, PMC_HANDLE_UINT v_denominator)
    {
        NUMBER_OBJECT_UINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        NUMBER_OBJECT_UINT* nv_denominator = GET_NUMBER_OBJECT(v_denominator, L"v_denominator");
        return (PMC_FloorLog10_R_Imp(nv_numerator, nv_denominator));
    }

    PMC_STATUS_CODE Initialize_Log(PROCESSOR_FEATURES* feature)
    {
        log10_2 = log10(2);
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */