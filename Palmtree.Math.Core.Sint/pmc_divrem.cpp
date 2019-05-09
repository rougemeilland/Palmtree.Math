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
    // q.abs == u.abs / v.abs
    // q.sign == u.sign * v.sign
    // r.abs == u.abs % v.abs
    // r.sign == u.sign

    // ※話を簡単にするために64ビット整数型については考慮しない。
    // 1) u が符号なし32bit整数、v が多倍長整数の場合に、q と r を符号なし(あるいは符号付)32bit整数で表現できるか？
    //   u.sign >= 0 なので、q.sign == v.sign, r.sign > 0。
    //   ⇒ u は符号なし、q は符号付でなければならない。
    //   r.abs <= u.abs かつ r.abs < v.abs なので、 r は符号なし32bit整数で表現できる。
    //   一方、q は符号が固定ではないために符号なし整数では表現できない。かつ、q.abs <= u.abs であるが符号反転により精度が失われる可能性がある。
    //   ⇒よって、q は多倍長整数で表現する必要がある。
    //
    // 2) u が符号付き32bit整数、v が多倍長整数の場合に、q と r を符号なし(あるいは符号付)32bit整数で表現できるか？
    //   u と q の符号はともに固定されないため、符号付整数である必要がある。
    //   r.abs <= u.abs かつ r.abs < v.abs であり、r は絶対値においてはu以下で符号においてはuと同じなので、rは32ビット整数で表現できる。
    //   一方、qについては1)と同様の理由により32ビット整数で表現することはできない。
    //
    // 3) u が多倍長整数、v が符号なし32bit整数の場合に、q と r を符号なし(あるいは符号付)32bit整数で表現できるか？
    //   u と q の符号はともに固定されないため、符号付整数である必要がある。
    //   r.abs < v.abs ではあるが、rの符号は負でもありうるため、符号反転により精度が失われることがある。
    //   【例】u == -2147483648(0x80000000)、v == 0x80000001の場合、⇒ rの符号は負かつ絶対値は0x80000000であるが、これは符号付32bit整数では表現できない。この反例により、rは符号付多倍長整数である必要がある。
    //   一方、q については、q.abs == u.abs / v.abs であり、32ビット整数で表現可能とは限らないことが容易にわかる。
    //   ⇒これらのことから、q と r はともに符号付多倍長整数でなければならない。
    //
    // 4) u が多倍長整数、v が符号付き32bit整数の場合に、q と r を符号なし(あるいは符号付)32bit整数で表現できるか？
    //   u と q の符号はともに固定されないため、符号付整数である必要がある。
    //   r.abs < v.abs であり v.abs の最大値は 0x80000000 であるため、r.abs は 0x80000000 以上となることはなく、符号反転によって精度が失われることはない。
    //   ⇒ r は符号付32ビット整数で表現できる。
    //   一方、q については、3)と同様に符号付多倍長整数でなければならない。
    //
    // ※結論：どのオーバーロードの場合でもqは符号付多倍長整数である必要がある。また、r は以下の条件で固定精度整数になることができる。
    // a) u が符号なし固定精度整数の場合 ⇒ r は vと同じ型の整数
    // b) u が符号つき固定精度整数の場合 ⇒ r は vと同じ型の整数
    // c) v が符号つき固定精度整数の場合 ⇒ r は vと同じ型の整数
    //
    // とは言うものの
    //
    // 直観的な理解がしにくい部分もあるため、rの型を以下のようにする(項目cを削除)
    // a') u が符号なし固定精度整数の場合 ⇒ r は vと同じ型の整数
    // b') u が符号つき固定精度整数の場合 ⇒ r は vと同じ型の整数

    _UINT32_T PMC_DivRem_UI_X(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u > 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nv->SIGN;
                _UINT32_T q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(u, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r_abs);
            }
            else
                return (ep_uint.DivRem(u, nv->ABS, nullptr));
        }
    }

    _INT32_T PMC_DivRem_I_X(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = PRODUCT_SIGN(u_sign, nv->SIGN);
                SIGN_T r_sign = u_sign;
                _UINT32_T q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(u_abs, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                _INT32_T r = GET_INT_32(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r);
            }
            else
            {
                SIGN_T r_sign = u_sign;
                _UINT32_T r_abs = ep_uint.DivRem(u_abs, nv->ABS, nullptr);
                return (GET_INT_32(r_sign, r_abs));
            }
        }
    }

    _INT32_T PMC_DivRem_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = u_sign;
                SIGN_T r_sign = u_sign;
                _UINT32_T q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(u_abs, v, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_I_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                _INT32_T r = GET_INT_32(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r);
            }
            else
            {
                SIGN_T r_sign = u_sign;
                _UINT32_T r_abs = ep_uint.DivRem(u_abs, v, nullptr);
                return (GET_INT_32(r_sign, r_abs));
            }
        }
    }

    _UINT64_T PMC_DivRem_UL_X(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nv->SIGN;
                _UINT64_T q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(u, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r_abs);
            }
            else
                return (ep_uint.DivRem(u, nv->ABS, nullptr));
        }
    }

    _INT64_T PMC_DivRem_L_X(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = PRODUCT_SIGN(u_sign, nv->SIGN);
                SIGN_T r_sign = u_sign;
                _UINT64_T q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(u_abs, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                _INT64_T r = GET_INT_64(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r);
            }
            else
            {
                SIGN_T r_sign = u_sign;
                _UINT64_T r_abs = ep_uint.DivRem(u_abs, nv->ABS, nullptr);
                return (GET_INT_64(r_sign, r_abs));
            }
        }
    }

    _INT64_T PMC_DivRem_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT * q) noexcept(false)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = u_sign;
                SIGN_T r_sign = u_sign;
                _UINT64_T q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(u_abs, v, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_L_Imp(tc, q_sign, q_abs);
                root.HookNumber(nq);
                _INT64_T r = GET_INT_64(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r);
            }
            else
            {
                SIGN_T r_sign = u_sign;
                _UINT64_T r_abs = ep_uint.DivRem(u_abs, v, nullptr);
                return (GET_INT_64(r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivRem_UX_X(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (number_handle_uint_zero);
        }
        else
        {
            // u > 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nv->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem(tc, u, nv->ABS, &q_abs);
                root.HookNumber(r_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(r_abs);
                return (r_abs);
            }
            else
            {
                return (ep_uint.DivRem(tc, u, nv->ABS, nullptr));
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nu->SIGN;
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(tc, nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                _UINT32_T r_abs = ep_uint.DivRem(tc, nu->ABS, v, nullptr);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_I(ThreadContext& tc, PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, v_sign);
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(tc, nu->ABS, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                _UINT32_T r_abs = ep_uint.DivRem(tc, nu->ABS, v_abs, nullptr);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    _UINT32_T PMC_DivRem_UX_I(ThreadContext& tc, PMC_HANDLE_UINT u, _INT32_T v, PMC_HANDLE_SINT * q) noexcept(false)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u > 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = v_sign;
                PMC_HANDLE_UINT q_abs;
                _UINT32_T r_abs = ep_uint.DivRem(tc, u, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r_abs);
            }
            else
            {
                return (ep_uint.DivRem(tc, u, v_abs, nullptr));
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nu->SIGN;
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(tc, nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                _UINT64_T r_abs = ep_uint.DivRem(tc, nu->ABS, v, nullptr);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_L(ThreadContext& tc, PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, v_sign);
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(tc, nu->ABS, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                _UINT64_T r_abs = ep_uint.DivRem(tc, nu->ABS, v_abs, nullptr);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(tc, r_sign, r_abs);
                root.HookNumber(nr);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    _UINT64_T PMC_DivRem_UX_L(ThreadContext& tc, PMC_HANDLE_UINT u, _INT64_T v, PMC_HANDLE_SINT * q) noexcept(false)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (0);
        }
        else
        {
            // u > 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = v_sign;
                PMC_HANDLE_UINT q_abs;
                _UINT64_T r_abs = ep_uint.DivRem(tc, u, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                *q = GET_NUMBER_HANDLE(nq);
                root.UnlinkNumber(nq);
                return (r_abs);
            }
            else
            {
                return (ep_uint.DivRem(tc, u, v_abs, nullptr));
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = nu->SIGN;
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem(tc, nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem(tc, nu->ABS, v, nullptr);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivRem_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
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

            if (q != nullptr)
                *q = GET_NUMBER_HANDLE(&number_object_sint_zero);
            return (GET_NUMBER_HANDLE(&number_object_sint_zero));
        }
        else
        {
            // u != 0 の場合

            if (q != nullptr)
            {
                ResourceHolderSINT root(tc);
                SIGN_T q_sign = PRODUCT_SIGN(nu->SIGN, nv->SIGN);
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem(tc, nu->ABS, nv->ABS, &q_abs);
                root.HookNumber(q_abs);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                *q = GET_NUMBER_HANDLE(nq);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                return (r);
            }
            else
            {
                ResourceHolderSINT root(tc);
                SIGN_T r_sign = nu->SIGN;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem(tc, nu->ABS, nv->ABS, nullptr);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_sign, r_abs);
                PMC_HANDLE_SINT r = GET_NUMBER_HANDLE(nr);
                root.UnlinkNumber(nr);
                return (r);
            }
        }
    }

    PMC_HANDLE_SINT PMC_DivideExactly_X_X(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v) noexcept(false)
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

    _UINT32_T PMC_Modulo_X_UI(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        else
        {
            // v != 0 の場合

            _UINT32_T r = ep_uint.Modulo(tc, nu->SIGN, nu->ABS, v);
            return (r);
        }
    }

    _UINT64_T PMC_Modulo_X_UL(ThreadContext& tc, PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == 0)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        else
        {
            // v != 0 の場合

            _UINT64_T r = ep_uint.Modulo(tc, nu->SIGN, nu->ABS, v);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_Modulo_X_UX(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
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
        else
        {
            // v != 0 の場合

            PMC_HANDLE_UINT r = ep_uint.Modulo(tc, nu->SIGN, nu->ABS, v);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_Modulo_I_UX(ThreadContext& tc, _INT32_T u, PMC_HANDLE_UINT v)
    {
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
        else
        {
            // v != 0 の場合

            PMC_HANDLE_UINT r = ep_uint.Modulo(tc, u_sign, u_abs, v);
            return (r);
        }
    }

    PMC_HANDLE_UINT PMC_Modulo_L_UX(ThreadContext& tc, _INT64_T u, PMC_HANDLE_UINT v)
    {
        SIGN_T u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (v->FLAGS.IS_ZERO)
        {
            // v == 0 の場合

            // エラーを返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        else
        {
            // v != 0 の場合

            PMC_HANDLE_UINT r = ep_uint.Modulo(tc, u_sign, u_abs, v);
            return (r);
        }
    }

}


/*
 * END OF FILE
 */