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

#include "pmc_uint_internal.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    _UINT32_T PMC_BitwiseAnd_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (0);
        }
        else if (u == 0)
        {
            // u が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // u と v の bit AND を計算する
            __UNIT_TYPE w;
            Basic::BitwiseAnd(nv->BLOCK, nv->UNIT_WORD_COUNT, u, w);
            return ((_UINT32_T)w);
        }
    }

    _UINT32_T PMC_BitwiseAnd_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (0);
        }
        else  if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // u と v の bit AND を計算する
            __UNIT_TYPE w;
            Basic::BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v, w);
            return ((_UINT32_T)w);
        }
    }

#ifdef _M_IX86
    _UINT64_T PMC_BitwiseAnd_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (0);
        }
        else if (u == 0)
        {
            // u が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // x と y の bit AND を計算する
            _UINT32_T u_hi;
            _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);
            _UINT32_T w_hi = nv->UNIT_WORD_COUNT > 1 ? nv->BLOCK[1] & u_hi : 0;
            _UINT32_T w_lo = nv->BLOCK[0] & u_lo;
            Basic::BitwiseAnd(nv->BLOCK, nv->UNIT_WORD_COUNT, u_hi, u_lo, w_hi, w_lo);
            return (_FROMWORDTODWORD(w_hi, w_lo));
        }
    }
#elif defined(_M_X64)
    _UINT64_T PMC_BitwiseAnd_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (0);
        }
        else if (u == 0)
        {
            // u が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // x と y の bit AND を計算する
            __UNIT_TYPE w;
            Basic::BitwiseAnd(nv->BLOCK, nv->UNIT_WORD_COUNT, u, w);
            return (w);
        }
    }
#else
#error unknown platform
#endif

#ifdef _M_IX86
    _UINT64_T PMC_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (0);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // x と y の bit AND を計算する
            _UINT32_T v_hi;
            _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
            _UINT32_T w_hi;
            _UINT32_T w_lo;
            Basic::BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v_hi, v_lo, w_hi, w_lo);
            return (_FROMWORDTODWORD(w_hi, w_lo));
        }
    }
#elif defined(_M_X64)
    _UINT64_T PMC_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (0);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            // x と y の bit AND を計算する
            __UNIT_TYPE w;
            Basic::BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v, w);
            return (w);
        }
    }
#else
#error unknown platform
#endif

    static NUMBER_OBJECT_UINT* PMC_BitwiseAnd_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (v->IS_ZERO)
            return (&number_object_uint_zero);
        else
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MINIMUM_UNIT(u->UNIT_WORD_COUNT, v->UNIT_WORD_COUNT));
            Basic::BitwiseAnd(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            if (w->IS_ZERO)
            {
                root.DeallocateNumber(w);
                return (&number_object_uint_zero);
            }
            root.UnlinkNumber(w);
            return (w);
        }
    }
    
    PMC_HANDLE_UINT PMC_BitwiseAnd_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_BitwiseAnd_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_BitwiseAnd(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */