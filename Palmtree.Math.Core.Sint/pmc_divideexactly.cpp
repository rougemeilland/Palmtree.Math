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
#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"


namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_SINT PMC_DivideExactly_UI_X(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -2147483648, v == -1 の場合、q = 2147483648, r = 0 となるが 2147483648 は _INT32_Tでは表現できない。
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u > 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nv->SIGN;
            _UINT32_T q_abs = ep_uint.DivideExactly(tc, u, nv->ABS);
            NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_I_X(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -2147483648, v == -1 の場合、q = 2147483648, r = 0 となるが 2147483648 は _INT32_Tでは表現できない。
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u_sign == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = PRODUCT_SIGN(u_sign, nv->SIGN);
            _UINT32_T q_abs = ep_uint.DivideExactly(tc, u_abs, nv->ABS);
            NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -2147483648, v == -1 の場合、q = 2147483648, r = 0 となるが 2147483648 は _INT32_Tでは表現できない。
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        SIGN_T u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (v->FLAGS.IS_ZERO)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u_sign == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = u_sign;
            _UINT32_T q_abs = ep_uint.DivideExactly(tc, u_abs, v);
            NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_UL_X(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -9223372036854775808, v == -1 の場合、q = 9223372036854775808, r = 0 となるが 9223372036854775808 は _INT64_Tでは表現できない。
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nv->SIGN;
            _UINT64_T q_abs = ep_uint.DivideExactly(tc, u, nv->ABS);
            NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_L_X(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -9223372036854775808, v == -1 の場合、q = 9223372036854775808, r = 0 となるが 9223372036854775808 は _INT64_Tでは表現できない。
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u_sign == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = PRODUCT_SIGN(u_sign, nv->SIGN);
            _UINT64_T q_abs = ep_uint.DivideExactly(tc, u_abs, nv->ABS);
            NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        // 大抵の場合は q と r の精度は _INT32_T で問題ないが、オーバーフローしてしまうケースが存在するため、PMC_HANDLE_SINT 型とする
        // 例: u == -9223372036854775808, v == -1 の場合、q = 9223372036854775808, r = 0 となるが 9223372036854775808 は _INT64_Tでは表現できない。
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        SIGN_T u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (v->FLAGS.IS_ZERO)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u_sign == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = u_sign;
            _UINT64_T q_abs = ep_uint.DivideExactly(tc, u_abs, v);
            NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
            root.HookNumber(nq);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_UX_X(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->SIGN == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u > 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nv->SIGN;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, u, nv->ABS);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nu->SIGN;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, v);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_I(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, v_sign);
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, v_abs);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u > 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = v_sign;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, u, v_abs);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nu->SIGN;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, v);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_L(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, v_sign);
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, v_abs);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_UX_L(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u > 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = v_sign;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, u, v_abs);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, nv->SIGN);
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, nv->ABS);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        if (v->FLAGS.IS_ZERO)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            ResourceHolderSINT root(tc);
            SIGN_T q_sign = nu->SIGN;
            PMC_HANDLE_UINT q_abs = ep_uint.DivideExactly(tc, nu->ABS, v);
            root.HookNumber(q_abs);
            NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
            PMC_HANDLE_SINT q = GET_NUMBER_HANDLE(nq);
            root.UnlinkNumber(nq);
            return (q);
        }
    }

}


/*
 * END OF FILE
 */