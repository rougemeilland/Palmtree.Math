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
#include "pmc_exception.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    NUMBER_HEADER* From_I_Imp(_UINT32_T x) noexcept(false)
    {
        ResourceHolderUINT root;
        NUMBER_HEADER* o = root.AllocateNumber(sizeof(x) * 8 - _LZCNT_ALT_32(x));
        o->BLOCK[0] = x;
        CommitNumber(o);
        root.UnlinkNumber(o);
        return (o);
    }

    NUMBER_HEADER* From_L_Imp(_UINT64_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(x))
        {
            // _UINT64_T を表現するのに 2 ワードでは不足する処理系には対応しない。
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;From_L_Imp;1");
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
                NUMBER_HEADER* o = root.AllocateNumber(x_bit_length);
                o->BLOCK[0] = x_lo;
                CommitNumber(o);
                root.UnlinkNumber(o);
                return (o);
            }
            else
            {
                ResourceHolderUINT root;
                __UNIT_TYPE x_bit_length = sizeof(x) * 8 - _LZCNT_ALT_32(x_hi);
                NUMBER_HEADER* o = root.AllocateNumber(x_bit_length);
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
            NUMBER_HEADER* o = root.AllocateNumber(x_bit_length);
            o->BLOCK[0] = (__UNIT_TYPE)x;
            CommitNumber(o);
            root.UnlinkNumber(o);
            return (o);
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_From_I(_UINT32_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(x))
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_I;1");
        ResourceHolderUINT root;
        NUMBER_HEADER* o;
        if (x == 0)
            o = &number_zero;
        else
            o = From_I_Imp(x);
        root.HookNumber(o);
#ifdef _DEBUG
        CheckNumber(o);
#endif
        root.UnlinkNumber(o);
        return ((PMC_HANDLE_UINT)o);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_From_L(_UINT64_T x) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(x))
        {
            // 32bit未満のCPUには未対応
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_from.cpp;PMC_From_L;1");
        }
        ResourceHolderUINT root;
        NUMBER_HEADER* o;
        if (x == 0)
            o = &number_zero;
        else
            o = From_L_Imp(x);
        root.HookNumber(o);
#ifdef _DEBUG
        CheckNumber(o);
#endif
        root.UnlinkNumber(o);
        return ((PMC_HANDLE_UINT)o);
    }

    PMC_STATUS_CODE Initialize_From(PROCESSOR_FEATURES *feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */