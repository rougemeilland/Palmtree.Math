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


namespace Palmtree::Math::Core::Internal
{

    static SIGN_T CompareU_X_I_Imp(SIGN_T sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (sign > 0)
            return (ep_uint.Compare(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_I_Imp;1");
#endif
        else
            return (ep_uint.Compare(v, u));
    }

    static SIGN_T CompareU_X_L_Imp(SIGN_T sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (sign > 0)
            return (ep_uint.Compare(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_L_Imp;1");
#endif
        else
            return (ep_uint.Compare(v, u));
    }

    static SIGN_T CompareU_X_X_Imp(SIGN_T sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        if (sign > 0)
            return (ep_uint.Compare(u, v));
#ifdef _DEBUG
        else if (sign == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;CompareU_X_X_Imp;1");
#endif
        else
            return (ep_uint.Compare(v, u));
    }

    __inline static SIGN_T EPILOGUE(SIGN_T value)
    {
#ifdef _DEBUG
        if (value != 0 && value != 1 && value != -1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_compare.cpp;EPILOGUE;1");
#endif
        return (value);
    }

    SIGN_T PMC_Compare_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_NEGATIVE, nv->ABS, u)));
            }
        }
    }

    SIGN_T PMC_Compare_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_NEGATIVE, nv->ABS, u_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v >= 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_POSITIVE, nv->ABS, u_abs)));
            }
        }
    }

    SIGN_T PMC_Compare_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_NEGATIVE, nv->ABS, u)));
            }
        }
    }

    SIGN_T PMC_Compare_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        SIGN_T u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else if (u_sign > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v <= 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_NEGATIVE, nv->ABS, u_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v >= 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_POSITIVE, nv->ABS, u_abs)));
            }
        }
    }

    SIGN_T PMC_Compare_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_X_Imp(SIGN_POSITIVE, u, nv->ABS)));
            }
        }
    }

    SIGN_T PMC_Compare_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // v の符号の反対を返す
                return (EPILOGUE(SIGN_ZERO));
            }
            else
            {
                // v > 0 の場合

                // v の符号の反対を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }

        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_POSITIVE, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (EPILOGUE(SIGN_NEGATIVE));
        }
    }

    SIGN_T PMC_Compare_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(v_sign)));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_POSITIVE, nu->ABS, v_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_I_Imp(SIGN_NEGATIVE, nu->ABS, v_abs)));
            }
        }
    }

    SIGN_T PMC_Compare_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // v の符号の反対を返す
                return (EPILOGUE(SIGN_ZERO));
            }
            else
            {
                // v > 0 の場合

                // v の符号の反対を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }

        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v == 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_POSITIVE, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (EPILOGUE(SIGN_NEGATIVE));
        }
    }

    SIGN_T PMC_Compare_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        SIGN_T v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(v_sign)));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v_sign <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_POSITIVE, nu->ABS, v_abs)));
            }
        }
        else
        {
            // u < 0 の場合

            if (v_sign >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_L_Imp(SIGN_NEGATIVE, nu->ABS, v_abs)));
            }
        }
    }

    SIGN_T PMC_Compare_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullが与えられています。", L"v");
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 0 を返す
                return (EPILOGUE(SIGN_ZERO));
            }
            else
            {
                // v > 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_X_Imp(SIGN_POSITIVE, nu->ABS, v)));
            }
        }
        else
        {
            // u < 0 の場合

            // -1 を返す
            return (EPILOGUE(SIGN_NEGATIVE));
        }
    }

    SIGN_T PMC_Compare_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        NUMBER_OBJECT_SINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_SINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nu->SIGN == 0)
        {
            // u == 0 の場合

            // v の符号の反対を返す
            return (EPILOGUE(INVERT_SIGN(nv->SIGN)));
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 の場合

            if (nv->SIGN <= 0)
            {
                // v == 0 の場合

                // 1 を返す
                return (EPILOGUE(SIGN_POSITIVE));
            }
            else
            {
                // v > 0 の場合

                // abs(u) と abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_X_Imp(SIGN_POSITIVE, nu->ABS, nv->ABS)));
            }
        }
        else
        {
            // u < 0 の場合

            if (nv->SIGN >= 0)
            {
                // v == 0 の場合

                // -1 を返す
                return (EPILOGUE(SIGN_NEGATIVE));
            }
            else
            {
                // v < 0 の場合

                // -abs(u) と -abs(v) の比較結果を返す
                return (EPILOGUE(CompareU_X_X_Imp(SIGN_NEGATIVE, nu->ABS, nv->ABS)));
            }
        }
    }

}


/*
 * END OF FILE
 */