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

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, _UINT32_T w_abs)
    {
        return (From_I_Imp(w_sign, w_abs));
    }

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, _UINT64_T w_abs)
    {
        return (From_L_Imp(w_sign, w_abs));
    }

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, PMC_HANDLE_UINT w_abs)
    {
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_UX_I_Imp(PMC_HANDLE_UINT u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (From_I_Imp(v_sign, v_abs));
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(SIGN_POSITIVE, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR 式 w == u | v と上式より
                // ~(abs(w) - 1) == u | ~(abs(v) - 1) となる。これを AND 式に変換して abs(w) について解くと
                // abs(w) == (~u & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.OneCompliment_And_BitwiseAnd(u, v_abs - 1) + 1));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_UX_L_Imp(PMC_HANDLE_UINT u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (From_L_Imp(v_sign, v_abs));
        }
        else
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (From_X_Imp(SIGN_POSITIVE, u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR 式 w == u | v と上式より
                // ~(abs(w) - 1) == u | ~(abs(v) - 1) となる。これを AND 式に変換して abs(w) について解くと
                // abs(w) == (~u & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.OneCompliment_And_BitwiseAnd(u, v_abs - 1) + 1));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_UI_Imp(NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_I_Imp(SIGN_POSITIVE, v));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_I_Imp(NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_I_Imp(v_sign, v_abs));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR 式 w == u | v と上式より
                // ~(abs(w) - 1) == u | ~(abs(v) - 1) となる。これを AND 式に変換して abs(w) について解くと
                // abs(w) == (~u & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.OneCompliment_And_BitwiseAnd(u->ABS, v_abs - 1) + 1));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v_abs, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | ~(abs(v) - 1) となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT32_T w_abs = ep_uint.BitwiseAnd(u_abs_minus_one, v_abs - 1) + 1;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, w_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_UL_Imp(NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_L_Imp(SIGN_POSITIVE, v));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_L_Imp(NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_L_Imp(v_sign, v_abs));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR 式 w == u | v と上式より
                // ~(abs(w) - 1) == u | ~(abs(v) - 1) となる。これを AND 式に変換して abs(w) について解くと
                // abs(w) == (~u & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.OneCompliment_And_BitwiseAnd(u->ABS, v_abs - 1) + 1));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v_sign > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v_abs, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | ~(abs(v) - 1) となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                _UINT64_T w_abs = ep_uint.BitwiseAnd(u_abs_minus_one, v_abs - 1) + 1;
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, w_abs));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_UX_Imp(NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_X_Imp(SIGN_POSITIVE, v));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_BitwiseOr_X_X_Imp(NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (DuplicateNumber_X(v));
        }
        else if (u->SIGN > 0)
        {
            // u > 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                ResourceHolderSINT root;
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.BitwiseOr(u->ABS, v->ABS)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR 式 w == u | v と上式より
                // ~(abs(w) - 1) == u | ~(abs(v) - 1) となる。これを AND 式に変換して abs(w) について解くと
                // abs(w) == (~u & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(v->ABS);
                root.HookNumber(v_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(u->ABS, v_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v->SIGN == 0)
            {
                // v == 0 の場合

                return (DuplicateNumber_X(u));
            }
            else if (v->SIGN > 0)
            {
                // v > 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | v となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & ~v) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.OneCompliment_And_BitwiseAnd(v->ABS, u_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // OR式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) | ~(abs(v) - 1) となり、これを AND 式に変換し、abs(w) について解くと
                // abs(w) == ((abs(u) - 1) & (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root;
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(v->ABS);
                root.HookNumber(v_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.BitwiseAnd(u_abs_minus_one, v_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(w_abs_2)));
            }
        }
    }

    __inline static PMC_HANDLE_SINT EPILOGUE(ResourceHolderSINT& root, NUMBER_OBJECT_SINT* nw)
    {
        root.HookNumber(nw);
        PMC_HANDLE_SINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UI_Imp(nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_X_I_Imp(nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_I_UX(_INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_UX_I_Imp(v, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UL_Imp(nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_X_L_Imp(nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_L_UX(_INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_UX_L_Imp(v, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UX_Imp(nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UI_Imp(nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_X_I_Imp(nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_UX_I(PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_UX_I_Imp(u, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UL_Imp(nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_X_L_Imp(nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_UX_L(PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_UX_L_Imp(u, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* w = PMC_BitwiseOr_X_UX_Imp(nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_BitwiseOr_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root;
        NUMBER_OBJECT_SINT* nw = PMC_BitwiseOr_X_X_Imp(nu, nv);
        return (EPILOGUE(root, nw));
    }

}

/*
 * END OF FILE
 */