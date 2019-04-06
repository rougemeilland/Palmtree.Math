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
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static bool Equals_UX_UI_Imp(NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            return (v == 0);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (false);
        }
        else
        {
            // x と y がともに 0 ではない場合
            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
            if (u_bit_count != v_bit_count)
            {
                // 明らかに u != v である場合
                return (false);
            }
            else
            {
                // u > 0 && v > 0 かつ u のビット長と v のビット長が等しい場合
                // ⇒ u と v はともに 1 ワードで表現できる
                return (u->BLOCK[0] == v);
            }
        }
    }

    static bool Equals_UX_UL_Imp(NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合
            return (v == 0);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (false);
        }
        else
        {
            // u と v がともに 0 ではない場合
            if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
            {
                // _UINT64_T が 1 ワードで表現しきれない場合
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit では表現できる場合
                    __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                    if (u_bit_count != v_bit_count)
                    {
                        // 明らかに u > v である場合
                        return (false);
                    }
                    else
                    {
                        // u > 0 && v > 0 かつ u のビット長と v のビット長が等しく、かつ v が 1 ワードで表現できる場合
                        // ⇒ u と v はともに 1 ワードで表現できる
                        return (u->BLOCK[0] == v_lo);
                    }
                }
                else
                {
                    // v の値が 32bit では表現できない場合
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                    if (u_bit_count != v_bit_count)
                    {
                        // 明らかに u > v である場合
                        return (false);
                    }
                    else
                    {
                        // u > 0 && v > 0 かつ u のビット長と v のビット長が等しく、かつ v が 2 ワードで表現できる場合
                        // ⇒ u と v はともに 2 ワードで表現できる
                        return (u->BLOCK[1] == v_hi && u->BLOCK[0] == v_lo);
                    }
                }
            }
            else
            {
                // _UINT64_T が 1 ワードで表現できる場合

                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                if (u_bit_count != v_bit_count)
                {
                    // 明らかに u != v である場合
                    return (false);
                }
                else
                {
                    // u > 0 && v > 0 かつ u のビット長と v のビット長が等しく、かつ v が 1 ワードで表現できる場合
                    // ⇒ u と v はともに 1 ワードで表現できる
                    return (u->BLOCK[0] == v);
                }
            }
        }
    }

    static bool Equals_UX_UX_Imp(__UNIT_TYPE* u, __UNIT_TYPE* v, __UNIT_TYPE count)
    {
        while (count > 0)
        {
            if (*u != *v)
                return (false);
            ++u;
            ++v;
            --count;
        }
        return (true);
    }

    static bool EPILOGUE(bool r)
    {
        return (r);
    }

    bool PMC_Equals_UI_UX(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_equals.cpp;PMC_Equals_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (EPILOGUE(Equals_UX_UI_Imp(nv, u)));
    }

    bool PMC_Equals_UX_UI(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_equals.cpp;PMC_Equals_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        return (EPILOGUE(Equals_UX_UI_Imp(nu, v)));
    }

    bool PMC_Equals_UL_UX(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_equals.cpp;PMC_Equals_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (EPILOGUE(Equals_UX_UL_Imp(nv, u)));
    }

    bool PMC_Equals_UX_UL(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_equals.cpp;PMC_Equals_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        return (EPILOGUE(Equals_UX_UL_Imp(nu, v)));
    }

    bool PMC_Equals_UX_UX(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nu->IS_ZERO)
            return (EPILOGUE(nv->IS_ZERO ? 1 : 0));
        else if (nv->IS_ZERO)
            return (EPILOGUE(0));
        else
        {
            __UNIT_TYPE u_bit_count = nu->UNIT_BIT_COUNT;
            __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
            if (u_bit_count != v_bit_count)
            {
                // 明らかに u != v である場合
                return (EPILOGUE(0));
            }
            else
            {
                // u > 0 && v > 0 かつ u のビット長と v のビット長が等しい場合
                return (EPILOGUE(Equals_UX_UX_Imp(nu->BLOCK, nv->BLOCK, nu->UNIT_WORD_COUNT)));
            }
        }
    }

    PMC_STATUS_CODE Initialize_Equals(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */