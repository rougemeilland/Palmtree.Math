﻿/*
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

#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    static SIGN_T PMC_Compare_UX_UI_Imp(NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (SIGN_ZERO);
            }
            else
            {
                // v が 0 でない場合
                return (SIGN_NEGATIVE);
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (SIGN_POSITIVE);
        }
        else
        {
            // x と y がともに 0 ではない場合

            return (Basic::Compare(u->BLOCK, u->UNIT_WORD_COUNT, v));
        }
    }

    SIGN_T PMC_Compare_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_compare.cpp;PMC_Compare_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T w = INVERT_SIGN(PMC_Compare_UX_UI_Imp(nv, u));
#ifdef _DEBUG
        if (w != 0 && w != 1 && w != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;PMC_Compare_UI_UX;2");
#endif
        return (w);
    }

    SIGN_T PMC_Compare_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_compare.cpp;PMC_Compare_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T w = PMC_Compare_UX_UI_Imp(nu, v);
#ifdef _DEBUG
        if (w != 0 && w != 1 && w != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;PMC_Compare_UX_I;2");
#endif
        return (w);
    }

#ifdef _M_IX86
    static SIGN_T PMC_Compare_UX_UL_Imp(NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (SIGN_ZERO);
            }
            else
            {
                // v が 0 でない場合
                return (SIGN_NEGATIVE);
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (SIGN_POSITIVE);
        }
        else
        {
            // u と v がともに 0 ではない場合

            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            _UINT32_T v_hi;
            _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
            return (Basic::Compare(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo));
        }
    }
#elif defined(_M_X64)
    static SIGN_T PMC_Compare_UX_UL_Imp(NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (SIGN_ZERO);
            }
            else
            {
                // v が 0 でない場合
                return (SIGN_NEGATIVE);
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (SIGN_POSITIVE);
        }
        else
        {
            // u と v がともに 0 ではない場合

            return (Basic::Compare(u->BLOCK, u->UNIT_WORD_COUNT, v));
        }
    }
#else
#error unknown platform
#endif

    SIGN_T PMC_Compare_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_compare.cpp;PMC_Compare_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T w = INVERT_SIGN(PMC_Compare_UX_UL_Imp(nv, u));
#ifdef _DEBUG
        if (w != 0 && w != 1 && w != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;PMC_Compare_UL_UX;2");
#endif
        return (w);
    }

    SIGN_T PMC_Compare_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_compare.cpp;PMC_Compare_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T w = PMC_Compare_UX_UL_Imp(nu, v);
#ifdef _DEBUG
        if (w != 0 && w != 1 && w != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;PMC_Compare_UX_L;2");
#endif
        return (w);
    }

    SIGN_T PMC_Compare_UX_UX_Imp(NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
            return (v->IS_ZERO ? SIGN_ZERO : SIGN_NEGATIVE);
        else if (v->IS_ZERO)
            return (SIGN_POSITIVE);
        else
        {
            return (Basic::Compare(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT));
        }
    }

    SIGN_T PMC_Compare_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T w = PMC_Compare_UX_UX_Imp(nu, nv);
#ifdef _DEBUG
        if (w != 0 && w != 1 && w != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;PMC_Compare_UX_UX;1");
#endif
        return (w);
    }

    PMC_STATUS_CODE Initialize_Compare(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */