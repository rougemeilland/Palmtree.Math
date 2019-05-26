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

#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        // ~u & v を計算する

        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        }
        else if (u == 0)
        {
            // u が 0 である場合
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(tc, nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // u と v がともに 0 ではない場合

            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(nv->UNIT_WORD_COUNT);

            Basic::OneCompliment_And_BitwiseAnd(u, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK, nw->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(nw);
#endif
            CommitNumber(tc, nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }

#ifdef _M_IX86
    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        // ~u & v を計算する

        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        }
        else if (u == 0)
        {
            // u が 0 である場合
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(tc, nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // u と v がともに 0 ではない場合

            _UINT32_T u_hi;
            _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);

            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(nv->UNIT_WORD_COUNT);

            Basic::OneCompliment_And_BitwiseAnd(u_hi, u_lo, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK, nw->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(nw);
#endif
            CommitNumber(tc, nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }
#elif defined(_M_X64)
    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        // ~u & v を計算する

        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        }
        else if (u == 0)
        {
            // u が 0 である場合
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(tc, nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // u と v がともに 0 ではない場合

            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(nv->UNIT_WORD_COUNT);

            Basic::OneCompliment_And_BitwiseAnd(u, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK, nw->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(nw);
#endif
            CommitNumber(tc, nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }
#else
#error unknown platform
#endif

    _UINT32_T PMC_OneCompliment_And_BitwiseAnd_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");

        // ~u & v を計算する

        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (v);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            __UNIT_TYPE w;
            Basic::OneCompliment_And_BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v, w);
            return ((_UINT32_T)w);
        }
    }

#ifdef _M_IX86
    _UINT64_T PMC_OneCompliment_And_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");

        // ~u & v を計算する

        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (v);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            _UINT32_T v_hi;
            _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
            __UNIT_TYPE w_lo;
            __UNIT_TYPE w_hi;

            Basic::OneCompliment_And_BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v_hi, v_lo, w_hi, w_lo);

            return (_FROMWORDTODWORD(w_hi, w_lo));
        }
    }
#elif defined(_M_X64)
    _UINT64_T PMC_OneCompliment_And_BitwiseAnd_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");

        // ~u & v を計算する

        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (v);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            __UNIT_TYPE w;
            Basic::OneCompliment_And_BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, v, w);
            return (w);
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        if (nu->IS_ZERO)
        {
            ResourceHolderUINT root(tc);
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(tc, nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else if (nv->IS_ZERO)
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        else
        {
            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(nv->UNIT_WORD_COUNT);

            Basic::OneCompliment_And_BitwiseAnd(nu->BLOCK, nu->UNIT_WORD_COUNT, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK, nw->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(nw);
#endif
            CommitNumber(tc, nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }

}


/*
 * END OF FILE
 */