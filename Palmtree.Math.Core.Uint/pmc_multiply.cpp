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

    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UI_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT + 1);
                basic_ep.Multiply(_UBASIC_T(u), v, _UBASIC_T(w));
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Multiply_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

#ifdef _M_IX86
    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する

                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT + 2);

                basic_ep.Multiply(_UBASIC_T(u), v_hi, v_lo, _UBASIC_T(w));
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
    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT + 1);

                basic_ep.Multiply(_UBASIC_T(u), v, _UBASIC_T(w));
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

    PMC_HANDLE_UINT PMC_Multiply_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UX_Imp(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v->IS_ONE)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する

                ResourceHolderUINT root(tc);

                NUMBER_OBJECT_UINT* w = root.AllocateNumber(u->UNIT_WORD_COUNT + v->UNIT_WORD_COUNT);
                basic_ep.Multiply(tc, method, _UBASIC_T(u), _UBASIC_T(v), _UBASIC_T(w));
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);

            }
        }
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UX(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UX_Imp(tc, method, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

}


/*
 * END OF FILE
 */