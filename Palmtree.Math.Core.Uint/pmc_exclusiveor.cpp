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

    static NUMBER_OBJECT_UINT* PMC_ExclusiveOr_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 でない場合
                return (From_UI_Imp(tc, v));
            }
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (DuplicateNumber(tc, u));
        }
        else
        {
            // x と y がともに 0 ではない場合
            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)));

            basic_ep.ExclusiveOr(_UBASIC_T(u), v, _UBASIC_T(w));
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

    PMC_HANDLE_UINT PMC_ExclusiveOr_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_exclusiveor.cpp;PMC_ExclusiveOr_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_ExclusiveOr_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_exclusiveor.cpp;PMC_ExclusiveOr_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_ExclusiveOr_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

#ifdef _M_IX86
    static NUMBER_OBJECT_UINT* PMC_ExclusiveOr_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v) noexcept(false)
    {
        if (u->IS_ZERO)
        {
            // x が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 でない場合
                return (From_UL_Imp(tc, v));
            }
        }
        else if (v == 0)
        {
            // y が 0 である場合
            return (DuplicateNumber(tc, u));
        }
        else
        {
            // u と v がともに 0 ではない場合

            ResourceHolderUINT root(tc);

            _UINT32_T v_hi;
            _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)));

            basic_ep.ExclusiveOr(_UBASIC_T(u), v_hi, v_lo, _UBASIC_T(w));
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
#elif defined(_M_X64)
    static NUMBER_OBJECT_UINT* PMC_ExclusiveOr_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v) noexcept(false)
    {
        if (u->IS_ZERO)
        {
            // x が 0 である場合
            if (v == 0)
            {
                // v が 0 である場合
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 でない場合
                return (From_UL_Imp(tc, v));
            }
        }
        else if (v == 0)
        {
            // y が 0 である場合
            return (DuplicateNumber(tc, u));
        }
        else
        {
            // u と v がともに 0 ではない場合
            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)));

            basic_ep.ExclusiveOr(_UBASIC_T(u), v, _UBASIC_T(w));
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
#else
#error unknown platform
#endif


    PMC_HANDLE_UINT PMC_ExclusiveOr_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_exclusiveor.cpp;PMC_ExclusiveOr_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_ExclusiveOr_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_exclusiveor.cpp;PMC_ExclusiveOr_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_ExclusiveOr_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_ExclusiveOr_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
            return (DuplicateNumber(tc, v));
        else if (v->IS_ZERO)
            return (DuplicateNumber(tc, u));
        else
        {
            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, v->UNIT_WORD_COUNT));

            basic_ep.ExclusiveOr(_UBASIC_T(u), _UBASIC_T(v), _UBASIC_T(w));
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

    PMC_HANDLE_UINT PMC_ExclusiveOr_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_ExclusiveOr_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_ExclusiveOr(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */