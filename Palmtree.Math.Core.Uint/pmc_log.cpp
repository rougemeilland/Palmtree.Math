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
#include "pmc_exception.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{
    static double log10_2; // 0.3010299956639811952137388947244

    _UINT32_T PMC_Floor_Log10_Imp(NUMBER_HEADER* v)
    {
        if (v->IS_ZERO)
            throw ArithmeticException(L"0の対数は未定義です。");

        ResourceHolderUINT root;
        _UINT32_T result = (_UINT32_T)floor((v->UNIT_BIT_COUNT - 1)* log10_2);
        NUMBER_HEADER* exp1 = PMC_TimesOfExponentOf10_Imp(1, result);
        root.HookNumber(exp1);
        while (true)
        {
            NUMBER_HEADER* exp2 = PMC_Multiply_X_I_Imp(exp1, 10);
            root.HookNumber(exp2);
            root.DeallocateNumber(exp1);
            exp1 = exp2;
            _INT32_T c = PMC_Compare_X_X_Imp(exp1, v);
            if (c > 0)
                return (result);
            if (c == 0)
                return (result + 1);
            ++result;
        }
    }

    _UINT32_T __PMC_CALL PMC_Floor_Log10(PMC_HANDLE_UINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        NUMBER_HEADER* nv = (NUMBER_HEADER*)v;
        CheckNumber(nv);
        return (PMC_Floor_Log10_Imp(nv));
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