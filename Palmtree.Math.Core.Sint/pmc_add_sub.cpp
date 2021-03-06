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

#include <windows.h>
#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"

namespace Palmtree::Math::Core::Internal
{
    // リソースリーク対策された AllocateNumber
    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, PMC_HANDLE_UINT w_abs)
    {
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* AddU_X_I_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_I_Imp;2");
#endif
        ResourceHolderSINT root(tc);
        PMC_HANDLE_UINT w_abs = ep_uint.Add(tc, u, v);
        return (ALLOCATE_NUMBER(root, sign, w_abs));
    }

    static NUMBER_OBJECT_SINT* AddU_X_L_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_L_Imp;2");
#endif
        ResourceHolderSINT root(tc);
        PMC_HANDLE_UINT w_abs = ep_uint.Add(tc, u, v);
        return (ALLOCATE_NUMBER(root, sign, w_abs));
    }

    static NUMBER_OBJECT_SINT* AddU_X_X_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;AddU_X_X_Imp;2");
#endif
        ResourceHolderSINT root(tc);
        PMC_HANDLE_UINT w_abs = ep_uint.Add(tc, u, v);
        return (ALLOCATE_NUMBER(root, sign, w_abs));
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_I_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_I_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) の場合

            // abs(u) - abs(v) を返す
            ResourceHolderSINT root(tc);
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct(tc, u, v);
            return (ALLOCATE_NUMBER(root, sign, w_abs));
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) の場合

            // - (abs(v) - abs(u)) を返す
            ResourceHolderSINT root(tc);
            _UINT32_T t = ep_uint.Subtruct(v, u);
            PMC_HANDLE_UINT w_abs = ep_uint.From(tc, t);
            return (ALLOCATE_NUMBER(root, INVERT_SIGN(sign), w_abs));
        }
        return (PMC_STATUS_OK);
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_L_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_L_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) の場合

            // abs(u) - abs(v) を返す
            ResourceHolderSINT root(tc);
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct(tc, u, v);
            return (ALLOCATE_NUMBER(root, sign, w_abs));
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) の場合

            // - (abs(v) - abs(u)) を返す
            ResourceHolderSINT root(tc);
            _UINT64_T t = ep_uint.Subtruct(v, u);
            PMC_HANDLE_UINT w_abs = ep_uint.From(tc, t);
            return (ALLOCATE_NUMBER(root, INVERT_SIGN(sign), w_abs));
        }
        return (PMC_STATUS_OK);
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_X_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_add_sub.cpp;SubtructU_X_X_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) の場合

            // abs(u) - abs(v) を返す
            ResourceHolderSINT root(tc);
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct(tc, u, v);
            return (ALLOCATE_NUMBER(root, sign, w_abs));
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) の場合

            // 0 を返す
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) の場合

            // - (abs(v) - abs(u)) を返す
            ResourceHolderSINT root(tc);
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct(tc, v, u);
            return (ALLOCATE_NUMBER(root, INVERT_SIGN(sign), w_abs));
        }
        return (PMC_STATUS_OK);
    }

    static NUMBER_OBJECT_SINT* Add_UX_I_Imp(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_I_Imp(tc, v_sign, v_abs));
            }
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, SIGN_POSITIVE, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_I_Imp(tc, SIGN_POSITIVE, u, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_I_Imp(tc, SIGN_POSITIVE, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_UX_L_Imp(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_L_Imp(tc, v_sign, v_abs));
            }
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, SIGN_POSITIVE, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_L_Imp(tc, SIGN_POSITIVE, u, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_L_Imp(tc, SIGN_POSITIVE, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_I_Imp(tc, SIGN_POSITIVE, v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_I_Imp(tc, SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_I_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_I_Imp(tc, v_sign, v_abs));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_I_Imp(tc, SIGN_POSITIVE, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_I_Imp(tc, SIGN_POSITIVE, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, SIGN_NEGATIVE, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_I_Imp(tc, SIGN_NEGATIVE, u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_L_Imp(tc, SIGN_POSITIVE, v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_L_Imp(tc, SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_L_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_L_Imp(tc, v_sign, v_abs));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_L_Imp(tc, SIGN_POSITIVE, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_L_Imp(tc, SIGN_POSITIVE, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, SIGN_NEGATIVE, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_L_Imp(tc, SIGN_NEGATIVE, u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_X_Imp(tc, SIGN_POSITIVE, v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_X_Imp(tc, SIGN_POSITIVE, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_X_Imp(tc, SIGN_NEGATIVE, u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Add_X_X_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (DuplicateNumber_X(tc, v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                return (AddU_X_X_Imp(tc, SIGN_POSITIVE, u->ABS, v->ABS));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_X_Imp(tc, SIGN_POSITIVE, u->ABS, v->ABS));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(tc, u));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_X_Imp(tc, SIGN_NEGATIVE, u->ABS, v->ABS));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_X_Imp(tc, SIGN_NEGATIVE, u->ABS, v->ABS));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_UX_I_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_I_Imp(tc, INVERT_SIGN(PRODUCT_SIGN(sign, v_sign)), v_abs));
            }
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, sign, u, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_I_Imp(tc, sign, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_UX_L_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_L_Imp(tc, INVERT_SIGN(PRODUCT_SIGN(sign, v_sign)), v_abs));
            }
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, sign, u, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_L_Imp(tc, sign, u, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_UX_UI_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_I_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, sign, u, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_UX_UL_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_L_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, sign, u, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_UX_UX_Imp(ThreadContext& tc, SIGN_T sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_X_Imp(tc, sign, u, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_UI_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_I_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, sign, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_I_Imp(tc, INVERT_SIGN(sign), u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_I_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_I_Imp(tc, INVERT_SIGN(PRODUCT_SIGN(sign, v_sign)), v_abs));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_I_Imp(tc, sign, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_I_Imp(tc, sign, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_I_Imp(tc, INVERT_SIGN(sign), u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_I_Imp(tc, INVERT_SIGN(sign), u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_UL_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_L_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, sign, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_L_Imp(tc, INVERT_SIGN(sign), u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_L_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_L_Imp(tc, INVERT_SIGN(PRODUCT_SIGN(sign, v_sign)), v_abs));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_L_Imp(tc, sign, u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_L_Imp(tc, sign, u->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                return (AddU_X_L_Imp(tc, INVERT_SIGN(sign), u->ABS, v_abs));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_L_Imp(tc, INVERT_SIGN(sign), u->ABS, v_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_UX_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v > 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), v));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (SubtructU_X_X_Imp(tc, sign, u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else
            {
                // v > 0 の場合

                return (AddU_X_X_Imp(tc, INVERT_SIGN(sign), u->ABS, v));
            }
        }
    }

    static NUMBER_OBJECT_SINT* Subtruct_X_X_Imp(ThreadContext& tc, SIGN_T sign, NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else
            {
                // v != 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(PRODUCT_SIGN(sign, v->SIGN)), v->ABS));
            }
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, sign, u->ABS));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                return (SubtructU_X_X_Imp(tc, sign, u->ABS, v->ABS));
            }
            else
            {
                // v < 0 の場合

                return (AddU_X_X_Imp(tc, sign, u->ABS, v->ABS));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(tc, INVERT_SIGN(sign), u->ABS));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                return (AddU_X_X_Imp(tc, INVERT_SIGN(sign), u->ABS, v->ABS));
            }
            else
            {
                // v < 0 の場合

                return (SubtructU_X_X_Imp(tc, INVERT_SIGN(sign), u->ABS, v->ABS));
            }
        }
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, NUMBER_OBJECT_SINT* nr)
    {
        root.HookNumber(nr);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, SIGN_T r_sign, PMC_HANDLE_UINT r_abs)
    {
        root.HookNumber(r_abs);
        NUMBER_OBJECT_SINT* nr= root.AllocateNumber(r_sign, r_abs);
        PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_HANDLE_SINT PMC_Add_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_UX_I_Imp(tc, v, u)));
    }

    PMC_HANDLE_SINT PMC_Add_I_X(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_I_Imp(tc, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Add_L_X(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_L_Imp(tc, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Add_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_UX_L_Imp(tc, v, u)));
    }

    PMC_HANDLE_SINT PMC_Add_UI_X(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UI_Imp(tc, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Add_UL_X(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UL_Imp(tc, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Add_UX_X(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UX_Imp(tc, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Add_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_UX_I_Imp(tc, u, v)));
    }

    PMC_HANDLE_SINT PMC_Add_UX_L(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_UX_L_Imp(tc, u, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UI_Imp(tc, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_I(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_I_Imp(tc, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UL_Imp(tc, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_L(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_L_Imp(tc, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_UX_Imp(tc, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Add_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Add_X_X_Imp(tc, nu, nv)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_I_Imp(tc, SIGN_NEGATIVE, v, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_I_X(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_I_Imp(tc, SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_L_Imp(tc, SIGN_NEGATIVE, v, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_L_X(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_L_Imp(tc, SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_UI_Imp(tc, SIGN_NEGATIVE, v, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UI_X(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UI_Imp(tc, SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_UL_Imp(tc, SIGN_NEGATIVE, v, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UL_X(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UL_Imp(tc, SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_UI_Imp(tc, SIGN_POSITIVE, u, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_UL_Imp(tc, SIGN_POSITIVE, u, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_UX_Imp(tc, SIGN_POSITIVE, u, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_X(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UX_Imp(tc, SIGN_NEGATIVE, nv, u)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UI_Imp(tc, SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_I(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_I_Imp(tc, SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_I_Imp(tc, SIGN_POSITIVE, u, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UL_Imp(tc, SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_L(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_L_Imp(tc, SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_UX_L(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_UX_L_Imp(tc, SIGN_POSITIVE, u, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_UX_Imp(tc, SIGN_POSITIVE, nu, v)));
    }

    PMC_HANDLE_SINT PMC_Subtruct_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        return (EPILOGUE(root, Subtruct_X_X_Imp(tc, SIGN_POSITIVE, nu, nv)));
    }

    PMC_HANDLE_SINT PMC_Increment_X(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        if (nx->SIGN == 0)
        {
            // u == 0 の場合

            // 1 を返す
            return (GET_NUMBER_HANDLE(&number_object_sint_one));
        }
        else if (nx->SIGN > 0)
        {
            // u > 0 の場合

            // abs(u) + 1 を返す
            ResourceHolderSINT root(tc);
            return (EPILOGUE(root, SIGN_POSITIVE, ep_uint.Increment(tc, nx->ABS)));
        }
        else
        {
            // u < 0 の場合

            // - abs(u) + 1 を返す
            ResourceHolderSINT root(tc);
            return (EPILOGUE(root, SIGN_NEGATIVE, ep_uint.Decrement(tc, nx->ABS)));
        }
    }

    PMC_HANDLE_SINT PMC_Decrement_X(ThreadContext& tc, PMC_HANDLE_SINT x) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nx = GET_NUMBER_OBJECT(x, L"x");
        if (nx->SIGN == 0)
        {
            // u == 0 の場合

            // -1 を返す
            return (GET_NUMBER_HANDLE(&number_object_sint_minus_one));
        }
        else if (nx->SIGN > 0)
        {
            // u > 0 の場合

            // abs(u) - 1 を返す
            ResourceHolderSINT root(tc);
            return (EPILOGUE(root, SIGN_POSITIVE, ep_uint.Decrement(tc, nx->ABS)));
        }
        else
        {
            // u < 0 の場合

            // - abs(u) - 1 を返す
            ResourceHolderSINT root(tc);
            return (EPILOGUE(root, SIGN_NEGATIVE, ep_uint.Increment(tc, nx->ABS)));
        }
    }

}

/*
 * END OF FILE
 */