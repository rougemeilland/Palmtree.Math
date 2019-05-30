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

    NUMBER_OBJECT_UINT* PMC_RightShift_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            if (n >= u->UNIT_WORD_COUNT *  __UNIT_TYPE_BIT_COUNT)
                return (&number_object_uint_zero);
            else
            {
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT - n / __UNIT_TYPE_BIT_COUNT);

                Basic::RightShift(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                if (w->IS_ZERO)
                {
                    root.DeallocateNumber(w);
                    w = &number_object_uint_zero;
                }
                else
                    root.UnlinkNumber(w);
                return (w);
            }
        }
    }

#ifdef _M_IX86
    NUMBER_OBJECT_UINT* PMC_RightShift_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            _UINT32_T n_hi;
            _UINT32_T n_lo = _FROMDWORDTOWORD(n, &n_hi);

            if (n_hi > 0 || n_lo >= u->UNIT_BIT_COUNT)
                return (&number_object_uint_zero);
            else
            {
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT - n_lo / __UNIT_TYPE_BIT_COUNT);

                Basic::RightShift(u->BLOCK, u->UNIT_WORD_COUNT, n_lo, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                if (w->IS_ZERO)
                {
                    root.DeallocateNumber(w);
                    w = &number_object_uint_zero;
                }
                else
                    root.UnlinkNumber(w);
                return (w);
            }
        }
}
#elif defined(_M_X64)
    NUMBER_OBJECT_UINT* PMC_RightShift_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            if (n >= u->UNIT_WORD_COUNT *  __UNIT_TYPE_BIT_COUNT)
                return (&number_object_uint_zero);
            else
            {
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT - n / __UNIT_TYPE_BIT_COUNT);

                Basic::RightShift(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                if (w->IS_ZERO)
                {
                    root.DeallocateNumber(w);
                    w = &number_object_uint_zero;
                }
                else
                    root.UnlinkNumber(w);
                return (w);
            }
        }
}
#else
#error unknown platform
#endif

    NUMBER_OBJECT_UINT* PMC_LeftShift_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            ResourceHolderUINT root(tc);

            __UNIT_TYPE w_length;
            if (_ADD_UNIT(0, u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(n, __UNIT_TYPE_BIT_COUNT), &w_length))
                throw NotEnoughMemoryException(L"左シフト演算の結果を格納するためのメモリが不足しています。");

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_length);

            Basic::LeftShift(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

#ifdef _M_IX86
    NUMBER_OBJECT_UINT* PMC_LeftShift_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            _UINT32_T n_hi;
            _UINT32_T n_lo = _FROMDWORDTOWORD(n, &n_hi);

            ResourceHolderUINT root(tc);

            __UNIT_TYPE w_length;
            if (n_hi > 0 ||  _ADD_UNIT(0, u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(n_lo, __UNIT_TYPE_BIT_COUNT), &w_length))
                throw NotEnoughMemoryException(L"左シフト演算の結果を格納するためのメモリが不足しています。");

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_length);

            Basic::LeftShift(u->BLOCK, u->UNIT_WORD_COUNT, n_lo, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }
#elif defined(_M_X64)
    NUMBER_OBJECT_UINT* PMC_LeftShift_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T n)
    {
        if (u->IS_ZERO)
            return (&number_object_uint_zero);
        else if (n == 0)
            return (DuplicateNumber(tc, u));
        else
        {
            ResourceHolderUINT root(tc);

            __UNIT_TYPE w_length;
            if (_ADD_UNIT(0, u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(n, __UNIT_TYPE_BIT_COUNT), &w_length))
                throw NotEnoughMemoryException(L"左シフト演算の結果を格納するためのメモリが不足しています。");

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_length);

            Basic::LeftShift(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_RightShift_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_shift.cpp;PMC_RightShift_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        SIGN_T n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        NUMBER_OBJECT_UINT* nw = n_sign >= 0 ? PMC_RightShift_UX_UI_Imp(tc, nu, n_abs) : PMC_LeftShift_UX_UI_Imp(tc, nu, n_abs);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_RightShift_UX_UI(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_shift.cpp;PMC_RightShift_UX_UI;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_RightShift_UX_UI_Imp(tc, nu, n);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_RightShift_UX_L(ThreadContext & tc, PMC_HANDLE_UINT u, _INT64_T n) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        SIGN_T n_sign;
        _UINT64_T n_abs = GET_ABS_64(n, &n_sign);
        NUMBER_OBJECT_UINT* nw = n_sign >= 0 ? PMC_RightShift_UX_UL_Imp(tc, nu, n_abs) : PMC_LeftShift_UX_UL_Imp(tc, nu, n_abs);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_RightShift_UX_UL(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT64_T n) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_RightShift_UX_UL_Imp(tc, nu, n);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_LeftShift_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_LeftShift_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        SIGN_T n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        NUMBER_OBJECT_UINT* nw = n_sign >= 0 ? PMC_LeftShift_UX_UI_Imp(tc, nu, n_abs) : PMC_RightShift_UX_UI_Imp(tc, nu, n_abs);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_LeftShift_UX_UI(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_LeftShift_UX_UI;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_LeftShift_UX_UI_Imp(tc, nu, n);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_LeftShift_UX_L(ThreadContext & tc, PMC_HANDLE_UINT u, _INT64_T n) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        SIGN_T n_sign;
        _UINT64_T n_abs = GET_ABS_64(n, &n_sign);
        NUMBER_OBJECT_UINT* nw = n_sign >= 0 ? PMC_LeftShift_UX_UL_Imp(tc, nu, n_abs) : PMC_RightShift_UX_UL_Imp(tc, nu, n_abs);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_LeftShift_UX_UL(ThreadContext & tc, PMC_HANDLE_UINT u, _UINT64_T n) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_LeftShift_UX_UL_Imp(tc, nu, n);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_Shift(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */
