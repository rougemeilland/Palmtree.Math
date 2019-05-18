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

#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    NUMBER_OBJECT_UINT* PMC_Increment_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u)
    {
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            // 1 を返す
            return (&number_object_uint_one);
        }
        else
        {
            // x が 0 ではない場合

            // x + 1 を計算する

            ResourceHolderUINT root(tc);

            NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT + 1);

            basic_ep.Carry(1, _UBASIC_T(u), _UBASIC_T(w));
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    PMC_HANDLE_UINT PMC_Increment_UX(ThreadContext& tc, PMC_HANDLE_UINT x)
    {
        NUMBER_OBJECT_UINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Increment_UX_Imp(tc, nx);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_Add_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            if (v == 0)
            {
                // y が 0 である場合

                // x と y がともに 0 であるので、加算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 加算結果となる y の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UI_Imp(tc, v));
            }
        }
        else
        {
            // x が 0 ではない場合

            if (v == 0)
            {
                // y が 0 である場合

                // 加算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // x と y がともに 0 ではない場合

                // x と y の和を計算する
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                if (basic_ep.Add(_UBASIC_T(u), v, _UBASIC_T(w)))
                {
                    // w のサイズが十分にあれば通知されないはずのキャリーが通知された場合
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;PMC_Add_UX_UI_Imp;1");
                }
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Add_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw =  PMC_Add_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Add_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

#ifdef _M_IX86
    static NUMBER_OBJECT_UINT* PMC_Add_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、加算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 加算結果となる v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 加算結果となる u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の和を計算する

                ResourceHolderUINT root(tc);

                __UNIT_TYPE v_hi;
                __UNIT_TYPE v_lo = _FROMDWORDTOWORD(v, &v_hi);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                if (basic_ep.Add(_UBASIC_T(u), v_hi, v_lo, _UBASIC_T(w)))
                {
                    // w のサイズが十分にあれば通知されないはずのキャリーが通知された場合
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;PMC_Add_UX_UL_Imp;1");
                }
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }
#elif defined(_M_X64)
    static NUMBER_OBJECT_UINT* PMC_Add_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、加算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 加算結果となる v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 加算結果となる u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の和を計算する

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, _DIVIDE_CEILING_UNIT(sizeof(v), __UNIT_TYPE_BYTE_COUNT)) + 1);

                if (basic_ep.Add(_UBASIC_T(u), v, _UBASIC_T(w)))
                {
                    // w のサイズが十分にあれば通知されないはずのキャリーが通知された場合
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;PMC_Add_UX_UL_Imp;1");
                }
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_Add_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Add_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    NUMBER_OBJECT_UINT* PMC_Add_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            if (v->IS_ZERO)
                return (&number_object_uint_zero);
            else
                return (DuplicateNumber(tc, v));
        }
        else
        {
            if (v->IS_ZERO)
                return (DuplicateNumber(tc, u));
            else
            {
                ResourceHolderUINT root(tc);
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(_MAXIMUM_UNIT(u->UNIT_WORD_COUNT, v->UNIT_WORD_COUNT) + 1);
                if (basic_ep.Add(_UBASIC_T(u), _UBASIC_T(v), _UBASIC_T(w)))
                {
                    // w のサイズが十分にあれば通知されないはずのキャリーが通知された場合
                    throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add.cpp;PMC_Add_UX_UX_Imp;1");
                }
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Add_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_Add(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */