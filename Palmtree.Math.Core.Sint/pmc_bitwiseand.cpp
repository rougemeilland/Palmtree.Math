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


#include <windows.h>
#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"


namespace Palmtree::Math::Core::Internal
{
    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, PMC_HANDLE_UINT w_abs)
    {
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static PMC_HANDLE_UINT PMC_BitwiseAnd_UX_I_Imp(PMC_HANDLE_UINT u, _INT32_T v)
    {
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (number_handle_uint_zero);
        }
        else
        {
            // u > 0 の場合

            SIGN_T v_sign;
            _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (number_handle_uint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                _UINT32_T w_abs = ep_uint.BitwiseAnd(u, v_abs);
                return (ep_uint.From(w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == u & ~(abs(v) - 1) となる

                return (ep_uint.OneCompliment_And_BitwiseAnd(v_abs - 1, u));
            }
        }
    }

    static PMC_HANDLE_UINT PMC_BitwiseAnd_UX_L_Imp(PMC_HANDLE_UINT u, _INT64_T v)
    {
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (number_handle_uint_zero);
        }
        else
        {
            // u > 0 の場合

            SIGN_T v_sign;
            _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (number_handle_uint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                _UINT64_T w_abs = ep_uint.BitwiseAnd(u, v_abs);
                return (ep_uint.From(w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == u & ~(abs(v) - 1) となる

                return (ep_uint.OneCompliment_And_BitwiseAnd(v_abs - 1, u));
            }
        }
    }

    static _UINT32_T PMC_BitwiseAnd_X_UI_Imp(NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (0);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (0);
            }
            else
            {
                // v > 0 の場合

                return (ep_uint.BitwiseAnd(u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (0);
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT32_T w = ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v);
                return (w);
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseAnd_X_I_Imp(NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            SIGN_T v_sign;
            _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                _UINT32_T w_abs = ep_uint.BitwiseAnd(u->ABS, v_abs);
                return (From_I_Imp(SIGN_POSITIVE, w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == u & ~(abs(v) - 1) となる

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.OneCompliment_And_BitwiseAnd(v_abs - 1, u->ABS)));
            }
        }
        else
        {
            // u < 0 の場合

            SIGN_T v_sign;
            _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT32_T w_abs = ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v_abs);
                return (From_I_Imp(SIGN_POSITIVE, w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) & ~(abs(v) - 1) となり、OR式に直すと
                // abs(w) == ((abs(u) - 1) | (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.BitwiseOr(u_abs_minus_one, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    static _UINT64_T PMC_BitwiseAnd_X_UL_Imp(NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (0);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (0);
            }
            else
            {
                // v > 0 の場合

                return (ep_uint.BitwiseAnd(u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (0);
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT64_T w = ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v);
                return (w);
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseAnd_X_L_Imp(NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            SIGN_T v_sign;
            _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                _UINT64_T w_abs = ep_uint.BitwiseAnd(u->ABS, v_abs);
                return (From_L_Imp(SIGN_POSITIVE, w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == u & ~(abs(v) - 1) となる

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.OneCompliment_And_BitwiseAnd(v_abs - 1, u->ABS)));
            }
        }
        else
        {
            // u < 0 の場合

            SIGN_T v_sign;
            _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
            if (v_sign == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT64_T w_abs = ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v_abs);
                return (From_L_Imp(SIGN_POSITIVE, w_abs));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) & ~(abs(v) - 1) となり、OR式に直すと
                // abs(w) == ((abs(u) - 1) | (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.BitwiseOr(u_abs_minus_one, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    static PMC_HANDLE_UINT PMC_BitwiseAnd_X_UX_Imp(NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (number_handle_uint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (number_handle_uint_zero);
            }
            else
            {
                // v > 0 の場合

                return (ep_uint.BitwiseAnd(u->ABS, v));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (number_handle_uint_zero);
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w = ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v);
                return (w);
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseAnd_X_X_Imp(NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (&number_object_sint_zero);
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseAnd(u->ABS, v->ABS)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == u & ~(abs(v) - 1) となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(v->ABS);
                root.HookNumber(v_abs_minus_one);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.OneCompliment_And_BitwiseAnd(v_abs_minus_one, u->ABS)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (&number_object_sint_zero);
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // w == ~(abs(u) - 1) & v となる

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.OneCompliment_And_BitwiseAnd(u_abs_minus_one, v->ABS)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // AND式 w == u & v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) & ~(abs(v) - 1) となり、OR式に直すと
                // abs(w) == ((abs(u) - 1) | (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(v->ABS);
                root.HookNumber(v_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.BitwiseOr(u_abs_minus_one, v_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    __inline static _UINT32_T EPILOGUE(_UINT32_T w)
    {
        return (w);
    }

    __inline static _UINT64_T EPILOGUE(_UINT64_T w)
    {
        return (w);
    }

    __inline static PMC_HANDLE_UINT EPILOGUE(PMC_HANDLE_UINT w)
    {
        return (w);
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, NUMBER_OBJECT_SINT* nw)
    {
        root.HookNumber(nw);
        PMC_HANDLE_SINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    _UINT32_T PMC_BitwiseAnd_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        _UINT32_T w = PMC_BitwiseAnd_X_UI_Imp(nv, u);
        return (EPILOGUE(w));
    }

    PMC_HANDLE_SINT PMC_BitwiseAnd_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseAnd_X_I_Imp(nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        PMC_HANDLE_UINT nw = PMC_BitwiseAnd_UX_I_Imp(v, u);
        return (EPILOGUE(nw));
    }

    _UINT64_T PMC_BitwiseAnd_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        _UINT64_T w = PMC_BitwiseAnd_X_UL_Imp(nv, u);
        return (EPILOGUE(w));
    }

    PMC_HANDLE_SINT PMC_BitwiseAnd_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseAnd_X_L_Imp(nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        PMC_HANDLE_UINT nw = PMC_BitwiseAnd_UX_L_Imp(v, u);
        return (EPILOGUE(nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        PMC_HANDLE_UINT w = PMC_BitwiseAnd_X_UX_Imp(nv, u);
        return (EPILOGUE(w));
    }

    _UINT32_T PMC_BitwiseAnd_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        _UINT32_T w = PMC_BitwiseAnd_X_UI_Imp(nu, v);
        return (EPILOGUE(w));
    }

    PMC_HANDLE_SINT PMC_BitwiseAnd_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseAnd_X_I_Imp(nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        PMC_HANDLE_UINT nw = PMC_BitwiseAnd_UX_I_Imp(u, v);
        return (EPILOGUE(nw));
    }

    _UINT64_T PMC_BitwiseAnd_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        _UINT64_T w = PMC_BitwiseAnd_X_UL_Imp(nu, v);
        return (EPILOGUE(w));
    }

    PMC_HANDLE_SINT PMC_BitwiseAnd_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseAnd_X_L_Imp(nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        PMC_HANDLE_UINT nw = PMC_BitwiseAnd_UX_L_Imp(u, v);
        return (EPILOGUE(nw));
    }

    PMC_HANDLE_UINT PMC_BitwiseAnd_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        PMC_HANDLE_UINT w = PMC_BitwiseAnd_X_UX_Imp(nu, v);
        return (EPILOGUE(w));
    }

    PMC_HANDLE_SINT PMC_BitwiseAnd_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseAnd_X_X_Imp(nu, nv);
        return (EPILOGUE(root, nw));
    }

}

/*
 * END OF FILE
 */