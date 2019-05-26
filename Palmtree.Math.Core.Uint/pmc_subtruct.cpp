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

#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_UINT* PMC_Decrement_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* x)
    {
        if (x->IS_ZERO)
        {
            // x が 0 である場合

            // 演算結果は負となってしまうのでエラーを返す。
            throw OverflowException(L"減算によりオーバーフローが発生しました。");
        }
        else
        {
            // x が 0 ではない場合

            // x - 1 を計算する

            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(x->UNIT_WORD_COUNT);

            if (Basic::Borrow(1, x->BLOCK, x->UNIT_WORD_COUNT, w->BLOCK, w->BLOCK_COUNT))
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
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

    PMC_HANDLE_UINT PMC_Decrement_UX(ThreadContext& tc, PMC_HANDLE_UINT x) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Decrement_UX_Imp(tc, nx);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    _UINT32_T PMC_Subtruct_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_subtruct.cpp;PMC_Subtruct_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
        {
            // u が 0 である場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (0);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // 演算結果となる u の値を返す。
                return (u);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // x と y の差を計算する

                __UNIT_TYPE w;
                Basic::USubtruct(u, nv->BLOCK, nv->UNIT_WORD_COUNT, w);
                return ((_UINT32_T)w);
            }
        }
    }

    static NUMBER_OBJECT_UINT* PMC_Subtruct_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 演算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の差を計算する

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT);

                Basic::USubtruct(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK, w->BLOCK_COUNT);
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

    PMC_HANDLE_UINT PMC_Subtruct_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_subtruct.cpp;PMC_Subtruct_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Subtruct_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

#ifdef _M_IX86
    _UINT64_T PMC_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_subtruct.cpp;PMC_Subtruct_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
        {
            // u が 0 である場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // x と y がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (0);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // 演算結果となる u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (u);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の差を計算する

                _UINT32_T u_hi;
                _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);

                __UNIT_TYPE w_hi;
                __UNIT_TYPE w_lo;

                Basic::USubtruct(u_hi, u_lo, nv->BLOCK, nv->UNIT_WORD_COUNT, w_hi, w_lo);

                return (_FROMWORDTODWORD((_UINT32_T)w_hi, (_UINT32_T)w_lo));
            }
        }
    }
#elif defined(_M_X64)
    _UINT64_T PMC_Subtruct_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_subtruct.cpp;PMC_Subtruct_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
        {
            // u が 0 である場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // x と y がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (0);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (nv->IS_ZERO)
            {
                // v が 0 である場合

                // 演算結果となる u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (u);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の差を計算する

                __UNIT_TYPE w;
                Basic::USubtruct(u, nv->BLOCK, nv->UNIT_WORD_COUNT, w);

                return (w);
            }
        }
    }
#else
#error unknown platform
#endif

#ifdef _M_IX86
    static NUMBER_OBJECT_UINT* PMC_Subtruct_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 演算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の差を計算する

                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT);

                Basic::USubtruct(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo, w->BLOCK, w->BLOCK_COUNT);
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
    static NUMBER_OBJECT_UINT* PMC_Subtruct_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 演算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の差を計算する

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT);

                Basic::USubtruct(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK, w->BLOCK_COUNT);
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

    PMC_HANDLE_UINT PMC_Subtruct_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_subtruct.cpp;PMC_Subtruct_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Subtruct_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_Subtruct_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            if (v->IS_ZERO)
            {
                // y が 0 である場合

                // x と y がともに 0 であるので、演算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 演算結果は負となってしまうのでエラーを返す。
                throw OverflowException(L"減算によりオーバーフローが発生しました。");
            }
        }
        else
        {
            // x が 0 ではない場合

            if (v->IS_ZERO)
            {
                // y が 0 である場合

                // 演算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // x と y がともに 0 ではない場合

                // x と y の差を計算する
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT);

                Basic::USubtruct(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK, w->BLOCK_COUNT);
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

    PMC_HANDLE_UINT PMC_Subtruct_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Subtruct_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_Subtruct(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */