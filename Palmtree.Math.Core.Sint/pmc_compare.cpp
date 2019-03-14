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
#include "pmc_exception.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static _INT32_T CompareU_X_I_Imp(char sign, PMC_HANDLE_UINT u, _INT32_T v)
    {
        if (sign > 0)
            return (ep_uint.Compare_X_I(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_I_Imp;1");
#endif
        else
            return (ep_uint.Compare_I_X(v, u));
    }

    static _INT32_T CompareU_X_L_Imp(char sign, PMC_HANDLE_UINT u, _INT64_T v)
    {
        if (sign > 0)
            return (ep_uint.Compare_X_L(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_L_Imp;1");
#endif
        else
            return (ep_uint.Compare_L_X(v, u));
    }

    static _INT32_T CompareU_X_X_Imp(char sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        if (sign > 0)
            return (ep_uint.Compare_X_X(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_X_Imp;1");
#endif
        else
            return (ep_uint.Compare_X_X(v, u));
    }

    __inline static _INT32_T CHECK_RETURN_VALUE(_INT32_T value)
    {
#ifdef _DEBUG
        if (value != 0 && value != 1 && value != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CHECK_RETURN_VALUE;1");
#endif
        return (value);
    }

    _INT32_T __PMC_CALL PMC_Compare_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(-1, nv->ABS, u)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(-1, nv->ABS, u_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v >= 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(1, nv->ABS, u_abs)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(-1, nv->ABS, u)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(-1, nv->ABS, u_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v >= 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(1, nv->ABS, u_abs)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_X_Imp(1, u, nv->ABS)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // v の符号の反対を返す
                return (CHECK_RETURN_VALUE(0));
            }
            else
            {
                // v > 0 の場合

                // v の符号の反対を返す
                return (CHECK_RETURN_VALUE(-1));
            }

        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(1, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (CHECK_RETURN_VALUE(-1));
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-v_sign));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(1, nu->ABS, v_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_I_Imp(-1, nu->ABS, v_abs)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // v の符号の反対を返す
                return (CHECK_RETURN_VALUE(0));
            }
            else
            {
                // v > 0 の場合

                // v の符号の反対を返す
                return (CHECK_RETURN_VALUE(-1));
            }

        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(1, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (CHECK_RETURN_VALUE(-1));
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-v_sign));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(1, nu->ABS, v_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_L_Imp(-1, nu->ABS, v_abs)));
            }
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 0 を返す
                return (CHECK_RETURN_VALUE(0));
            }
            else
            {
                // v > 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_X_Imp(1, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (CHECK_RETURN_VALUE(-1));
        }
    }

    _INT32_T __PMC_CALL PMC_Compare_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (CHECK_RETURN_VALUE(-nv->SIGN));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (CHECK_RETURN_VALUE(1));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_X_Imp(1, nu->ABS, nv->ABS)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (CHECK_RETURN_VALUE(-1));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (CHECK_RETURN_VALUE(CompareU_X_X_Imp(-1, nu->ABS, nv->ABS)));
            }
        }
    }

}


/*
 * END OF FILE
 */