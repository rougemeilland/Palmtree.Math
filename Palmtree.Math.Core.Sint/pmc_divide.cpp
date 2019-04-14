#include "pmc_uint_cppinterface.h"
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


#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"

namespace Palmtree::Math::Core::Internal
{

    PMC_HANDLE_SINT PMC_Divide_UI_R(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nv_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, u, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_UL_R(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nv_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, u, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_UX_R(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nv_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, u, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_I_R(ThreadContext& tc, _INT32_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            SIGN_T u_sign;
            _UINT32_T u_abs = GET_ABS_32(u, &u_sign);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(u_sign, nv_numerator->SIGN);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, u_abs, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_L_R(ThreadContext& tc, _INT64_T u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            SIGN_T u_sign;
            _UINT64_T u_abs = GET_ABS_64(u, &u_sign);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(u_sign, nv_numerator->SIGN);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, u_abs, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_X_R(ThreadContext& tc, PMC_HANDLE_SINT u, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(nu->SIGN, nv_numerator->SIGN);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, nu->ABS, v_denominator);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = nv_numerator->ABS;

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // denominator を複製する
                denominator = ep_uint.Clone(tc, denominator);
                root.HookNumber(denominator);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_UI(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        if (v == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nu_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, v);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_UL(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _UINT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        if (v == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nu_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, v);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_UX(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_UINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        if (v->FLAGS.IS_ZERO)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = nu_numerator->SIGN;

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, v);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_I(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT32_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        if (v == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            SIGN_T v_sign;
            _UINT32_T v_abs = GET_ABS_32(v, &v_sign);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(nu_numerator->SIGN, v_sign);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, v_abs);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_L(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, _INT64_T v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        if (v == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            SIGN_T v_sign;
            _UINT64_T v_abs = GET_ABS_64(v, &v_sign);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(nu_numerator->SIGN, v_sign);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, v_abs);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_X(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(nu_numerator->SIGN, nv->SIGN);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = nu_numerator->ABS;
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, nv->ABS);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (gcd->FLAGS.IS_ONE)
            {
                // GCD == 1 の場合 (分子と分母が互いに素であった場合)

                // numerator_abs を複製する
                numerator_abs = ep_uint.Clone(tc, numerator_abs);
                root.HookNumber(numerator_abs);
            }
            else
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

    PMC_HANDLE_SINT PMC_Divide_R_R(ThreadContext& tc, PMC_HANDLE_SINT u_numerator, PMC_HANDLE_UINT u_denominator, PMC_HANDLE_SINT v_numerator, PMC_HANDLE_UINT v_denominator, PMC_HANDLE_UINT * w_denominator) noexcept(false)
    {
        NUMBER_OBJECT_SINT* nu_numerator = GET_NUMBER_OBJECT(u_numerator, L"u_numerator");
        if (u_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u_denominator");
        NUMBER_OBJECT_SINT* nv_numerator = GET_NUMBER_OBJECT(v_numerator, L"v_numerator");
        if (v_denominator == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v_denominator");
        if (nv_numerator->SIGN == 0)
            throw DivisionByZeroException(L"0 による除算が行われようとしました。");
        else
        {
            ResourceHolderSINT root(tc);

            // 分子の符号を求める
            SIGN_T numerator_sign = PRODUCT_SIGN(nu_numerator->SIGN, nv_numerator->SIGN);

            // 分子と分母を求める
            PMC_HANDLE_UINT numerator_abs = ep_uint.Multiply(tc, v_denominator, nu_numerator->ABS);
            root.HookNumber(numerator_abs);
            PMC_HANDLE_UINT denominator = ep_uint.Multiply(tc, u_denominator, nv_numerator->ABS);
            root.HookNumber(denominator);

            // 分子と分母を約分する
            PMC_HANDLE_UINT gcd = ep_uint.GreatestCommonDivisor(tc, numerator_abs, denominator);
            root.HookNumber(gcd);
            if (!gcd->FLAGS.IS_ONE)
            {
                // GCD != 1 の場合 (分子と分母が互いに素でなかった場合)

                // 分子と分母をそれぞれ GCD で割る
                numerator_abs = ep_uint.DivideExactly(tc, numerator_abs, gcd);
                root.HookNumber(numerator_abs);
                denominator = ep_uint.DivideExactly(tc, denominator, gcd);
                root.HookNumber(denominator);
            }
            NUMBER_OBJECT_SINT* numerator = root.AllocateNumber(numerator_sign, numerator_abs);
            PMC_HANDLE_SINT w_numerator = GET_NUMBER_HANDLE(numerator);
            *w_denominator = denominator;
            root.UnlinkNumber(numerator);
            root.UnlinkNumber(denominator);
            return (w_numerator);
        }
    }

}


/*
 * END OF FILE
 */