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

    //
    // 排他的論理和の公式
    // 1) u ^ v == (u & ~v) | (~u & v)
    // 2) u ^ v == (u | v) & (~u | ~v)
    // 3) u ^ v == (u | v) & ~(u & v)
    //
    // 4) ~u ^ v == ~(u ^ v)
    //     ~u ^ v == (^u & ^v) | (u & v)
    //            == ~(~(^u & ^v) & ~(u & v))
    //            == ~((u | v) & (~u | ~v))
    //            == ~(u ^ v)
    //


    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ThreadContext& tc, ResourceHolderSINT& root, SIGN_T w_sign, _UINT32_T w_abs)
    {
        return (From_I_Imp(tc, w_sign, w_abs));
    }

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ThreadContext& tc, ResourceHolderSINT& root, SIGN_T w_sign, _UINT64_T w_abs)
    {
        return (From_L_Imp(tc, w_sign, w_abs));
    }

    __inline static NUMBER_OBJECT_SINT* ALLOCATE_NUMBER(ResourceHolderSINT& root, SIGN_T w_sign, PMC_HANDLE_UINT w_abs)
    {
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(w_sign, w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_UX_I_Imp(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (From_I_Imp(tc, v_sign, v_abs));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) ==  u ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == u ^ (abs(v) - 1) となる。これを abs(w) について解くと
                // abs(w) == (u ^ (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_UX_L_Imp(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (From_L_Imp(tc, v_sign, v_abs));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) ==  u ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == u ^ (abs(v) - 1) となる。これを abs(w) について解くと
                // abs(w) == (u ^ (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _UINT32_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_I_Imp(tc, SIGN_POSITIVE, v));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_I_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _INT32_T v)
    {
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_I_Imp(tc, v_sign, v_abs));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) ==  u ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == u ^ (abs(v) - 1) となる。これを abs(w) について解くと
                // abs(w) == (u ^ (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u->ABS, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v_abs);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // w == (abs(u) - 1) ^ (abs(v) - 1) となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u_abs_minus_one, v_abs - 1)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _UINT64_T v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_L_Imp(tc, SIGN_POSITIVE, v));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_L_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, _INT64_T v)
    {
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_L_Imp(tc, v_sign, v_abs));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v_abs)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) ==  u ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == u ^ (abs(v) - 1) となる。これを abs(w) について解くと
                // abs(w) == (u ^ (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u->ABS, v_abs - 1);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v_abs);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // w == (abs(u) - 1) ^ (abs(v) - 1) となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u_abs_minus_one, v_abs - 1)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, PMC_HANDLE_UINT v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (From_X_Imp(tc, SIGN_POSITIVE, v));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
        }
    }

    static NUMBER_OBJECT_SINT* PMC_ExclusiveOr_X_X_Imp(ThreadContext& tc, NUMBER_OBJECT_SINT* u, NUMBER_OBJECT_SINT* v)
    {
        if (u->SIGN == 0)
        {
            // u == 0 の場合

            return (DuplicateNumber_X(tc, v));
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

                ResourceHolderSINT root(tc);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u->ABS, v->ABS)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) ==  u ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == u ^ (abs(v) - 1) となる。これを abs(w) について解くと
                // abs(w) == (u ^ (abs(v) - 1)) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(tc, v->ABS);
                root.HookNumber(v_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u->ABS, v_abs_minus_one);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
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

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ v となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // abs(w) - 1 == (abs(u) - 1) ^ v となる。これを abs(w) について解くと
                // abs(w) == ((abs(u) - 1) ^ v) + 1 となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT w_abs_2 = ep_uint.ExclusiveOr(tc, u_abs_minus_one, v->ABS);
                root.HookNumber(w_abs_2);
                return (ALLOCATE_NUMBER(root, SIGN_NEGATIVE, ep_uint.Increment(tc, w_abs_2)));
            }
            else
            {
                // v < 0 の場合

                // 恒等式 -x == ~x + 1 において、x < 0 の場合 abs(x) - 1 == x~ が成り立つ。
                // XOR 式 w == u | v と上式より
                // ~(abs(w) - 1) == ~(abs(u) - 1) ^ ~(abs(v) - 1) となり、更に恒等式 ~x ^ y == ~(x ^ y) により
                // w == (abs(u) - 1) ^ (abs(v) - 1) となる。

                ResourceHolderSINT root(tc);
                PMC_HANDLE_UINT u_abs_minus_one = ep_uint.Decrement(tc, u->ABS);
                root.HookNumber(u_abs_minus_one);
                PMC_HANDLE_UINT v_abs_minus_one = ep_uint.Decrement(tc, v->ABS);
                root.HookNumber(v_abs_minus_one);
                return (ALLOCATE_NUMBER(root, SIGN_POSITIVE, ep_uint.ExclusiveOr(tc, u_abs_minus_one, v_abs_minus_one)));
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

    PMC_HANDLE_SINT PMC_ExclusiveOr_UI_X(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UI_Imp(tc, nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_I_X(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_X_I_Imp(tc, nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_UX_I_Imp(tc, v, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_UL_X(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UL_Imp(tc, nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_L_X(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_X_L_Imp(tc, nv, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_UX_L_Imp(tc, v, u);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_UX_X(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UX_Imp(tc, nv, u);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UI_Imp(tc, nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_I(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_X_I_Imp(tc, nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_UX_I_Imp(tc, u, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UL_Imp(tc, nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_L(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_X_L_Imp(tc, nu, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_UX_L(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_UX_L_Imp(tc, u, v);
        return (EPILOGUE(root, nw));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* w = PMC_ExclusiveOr_X_UX_Imp(tc, nu, v);
        return (EPILOGUE(root, w));
    }

    PMC_HANDLE_SINT PMC_ExclusiveOr_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderSINT root(tc);
        NUMBER_OBJECT_SINT* nw = PMC_ExclusiveOr_X_X_Imp(tc, nu, nv);
        return (EPILOGUE(root, nw));
    }

}

/*
 * END OF FILE
 */