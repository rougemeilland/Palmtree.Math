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
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static void OneCompliment_And_BitwiseAnd_1W(__UNIT_TYPE u, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf)
    {
#ifdef _DEBUG
        if (v_buf_count < 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_1W;1");
#endif
        w_buf[0] = ~u & v_buf[0];
        if (v_buf_count > 1)
            _COPY_MEMORY_UNIT(&w_buf[1], &v_buf[1], v_buf_count - 1);
    }

    static void OneCompliment_And_BitwiseAnd_2W(__UNIT_TYPE u_hi, __UNIT_TYPE u_lo, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf)
    {
#ifdef _DEBUG
        if (v_buf_count < 1)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_1W;1");
#endif
        w_buf[0] = ~u_lo & v_buf[0];
        if (v_buf_count > 1)
            w_buf[1] = ~u_hi & v_buf[1];
        if (v_buf_count > 2)
            _COPY_MEMORY_UNIT(&w_buf[2], &v_buf[2], v_buf_count - 2);
    }

    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_I_X;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        // ~u & v を計算する

        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        }
        else if (u == 0)
        {
            // u が 0 である場合
            ResourceHolderUINT root;
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // u と v がともに 0 ではない場合

            ResourceHolderUINT root;
            __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
            __UNIT_TYPE w_bit_count = v_bit_count;
            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(w_bit_count);
            OneCompliment_And_BitwiseAnd_1W(u, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK);
            root.CheckNumber(nw);
            CommitNumber(nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }

    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_L_X;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");

        // ~u & v を計算する

        if (nv->IS_ZERO)
        {
            // v が 0 である場合
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        }
        else if (u == 0)
        {
            // u が 0 である場合
            ResourceHolderUINT root;
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else
        {
            // u と v がともに 0 ではない場合

            if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
            {
                // _UINT64_T が 1 ワードで表現しきれない場合

                _UINT32_T u_hi;
                _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);
                if (u_hi == 0)
                {
                    // u の値が 32bit で表現可能な場合

                    ResourceHolderUINT root;
                    __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
                    __UNIT_TYPE w_bit_count = v_bit_count;
                    NUMBER_OBJECT_UINT* nw = root.AllocateNumber(w_bit_count);
                    OneCompliment_And_BitwiseAnd_1W(u_lo, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK);
                    root.CheckNumber(nw);
                    CommitNumber(nw);
                    if (nw->IS_ZERO)
                    {
                        root.DeallocateNumber(nw);
                        return (GET_NUMBER_HANDLE(&number_object_uint_zero));
                    }
                    PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
                    root.UnlinkNumber(nw);
                    return (w);
                }
                else
                {
                    // u の値が 32bit では表現できない場合

                    ResourceHolderUINT root;
                    __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
                    __UNIT_TYPE w_bit_count = v_bit_count;
                    NUMBER_OBJECT_UINT* nw = root.AllocateNumber(w_bit_count);
                    OneCompliment_And_BitwiseAnd_2W(u_hi, u_lo, nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK);
                    root.CheckNumber(nw);
                    CommitNumber(nw);
                    if (nw->IS_ZERO)
                    {
                        root.DeallocateNumber(nw);
                        return (GET_NUMBER_HANDLE(&number_object_uint_zero));
                    }
                    PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
                    root.UnlinkNumber(nw);
                    return (w);
                }
            }
            else
            {
                // _UINT64_T が 1 ワードで表現できる場合
                ResourceHolderUINT root;
                //__UNIT_TYPE u_bit_count = sizeof(u) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)u);
                __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
                __UNIT_TYPE w_bit_count = v_bit_count;
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                OneCompliment_And_BitwiseAnd_1W((__UNIT_TYPE)u, nv->BLOCK, nv->UNIT_WORD_COUNT, w->BLOCK);
                root.CheckNumber(w);
                CommitNumber(w);
                if (w->IS_ZERO)
                {
                    root.DeallocateNumber(w);
                    return (GET_NUMBER_HANDLE(&number_object_uint_zero));
                }
                root.UnlinkNumber(w);
                return ((PMC_HANDLE_UINT)w);
            }
        }
    }

    _UINT32_T PMC_OneCompliment_And_BitwiseAnd_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_OneCompliment_And_BitwiseAnd_X_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");

        // ~u & v を計算する

        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (v);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            _UINT32_T w = ~nu->BLOCK[0] & v;
            return (w);
        }
    }

    _UINT64_T PMC_OneCompliment_And_BitwiseAnd_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_bitwiseand.cpp;PMC_BitwiseAnd_L_X;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");

        // ~u & v を計算する

        if (nu->IS_ZERO)
        {
            // u が 0 である場合
            return (v);
        }
        else if (v == 0)
        {
            // v が 0 である場合
            return (0);
        }
        else
        {
            // u と v がともに 0 ではない場合

            if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
            {
                // _UINT64_T が 1 ワードで表現しきれない場合

                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit で表現可能な場合

                    _UINT32_T w = ~nu->BLOCK[0] & v_lo;
                    return (w);
                }
                else
                {
                    // v の値が 32bit では表現できない場合

                    if (nu->UNIT_WORD_COUNT <= 1)
                    {
                        // u が 1 ワードで表現できる場合

                        _UINT32_T w_lo = ~nu->BLOCK[0] & v_lo;
                        _UINT32_T w_hi = v_hi;
                        return (_FROMWORDTODWORD(w_hi, w_lo));
                    }
                    else
                    {
                        // u が 1 ワードで表現できない場合

                        _UINT32_T w_lo = ~nu->BLOCK[0] & v_lo;
                        _UINT32_T w_hi = ~nu->BLOCK[1] & v_hi;
                        return (_FROMWORDTODWORD(w_hi, w_lo));
                    }
                }
            }
            else
            {
                // _UINT64_T が 1 ワードで表現できる場合

                _UINT64_T w = (_UINT64_T)(~nu->BLOCK[0] & v);
                return (w);
            }
        }
    }

    static void OneCompliment_And_BitwiseAnd_X_X(const __UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, const __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf)
    {
        const __UNIT_TYPE* u_ptr = u_buf;
        const __UNIT_TYPE* v_ptr = v_buf;
        __UNIT_TYPE* w_ptr = w_buf;

        __UNIT_TYPE count = u_buf_count >> 5;
        while (count > 0)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            w_ptr[8] = ~u_ptr[8] & v_ptr[8];
            w_ptr[9] = ~u_ptr[9] & v_ptr[9];
            w_ptr[10] = ~u_ptr[10] & v_ptr[10];
            w_ptr[11] = ~u_ptr[11] & v_ptr[11];
            w_ptr[12] = ~u_ptr[12] & v_ptr[12];
            w_ptr[13] = ~u_ptr[13] & v_ptr[13];
            w_ptr[14] = ~u_ptr[14] & v_ptr[14];
            w_ptr[15] = ~u_ptr[15] & v_ptr[15];
            w_ptr[16] = ~u_ptr[16] & v_ptr[16];
            w_ptr[17] = ~u_ptr[17] & v_ptr[17];
            w_ptr[18] = ~u_ptr[18] & v_ptr[18];
            w_ptr[19] = ~u_ptr[19] & v_ptr[19];
            w_ptr[20] = ~u_ptr[20] & v_ptr[20];
            w_ptr[21] = ~u_ptr[21] & v_ptr[21];
            w_ptr[22] = ~u_ptr[22] & v_ptr[22];
            w_ptr[23] = ~u_ptr[23] & v_ptr[23];
            w_ptr[24] = ~u_ptr[24] & v_ptr[24];
            w_ptr[25] = ~u_ptr[25] & v_ptr[25];
            w_ptr[26] = ~u_ptr[26] & v_ptr[26];
            w_ptr[27] = ~u_ptr[27] & v_ptr[27];
            w_ptr[28] = ~u_ptr[28] & v_ptr[28];
            w_ptr[29] = ~u_ptr[29] & v_ptr[29];
            w_ptr[30] = ~u_ptr[30] & v_ptr[30];
            w_ptr[31] = ~u_ptr[31] & v_ptr[31];
            u_ptr += 32;
            v_ptr += 32;
            w_ptr += 32;
            --count;
        }

        if (u_buf_count & 0x10)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            w_ptr[8] = ~u_ptr[8] & v_ptr[8];
            w_ptr[9] = ~u_ptr[9] & v_ptr[9];
            w_ptr[10] = ~u_ptr[10] & v_ptr[10];
            w_ptr[11] = ~u_ptr[11] & v_ptr[11];
            w_ptr[12] = ~u_ptr[12] & v_ptr[12];
            w_ptr[13] = ~u_ptr[13] & v_ptr[13];
            w_ptr[14] = ~u_ptr[14] & v_ptr[14];
            w_ptr[15] = ~u_ptr[15] & v_ptr[15];
            u_ptr += 16;
            v_ptr += 16;
            w_ptr += 16;
        }

        if (u_buf_count & 0x8)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            w_ptr[4] = ~u_ptr[4] & v_ptr[4];
            w_ptr[5] = ~u_ptr[5] & v_ptr[5];
            w_ptr[6] = ~u_ptr[6] & v_ptr[6];
            w_ptr[7] = ~u_ptr[7] & v_ptr[7];
            u_ptr += 8;
            v_ptr += 8;
            w_ptr += 8;
        }

        if (u_buf_count & 0x4)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            w_ptr[2] = ~u_ptr[2] & v_ptr[2];
            w_ptr[3] = ~u_ptr[3] & v_ptr[3];
            u_ptr += 4;
            v_ptr += 4;
            w_ptr += 4;
        }

        if (u_buf_count & 0x2)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            w_ptr[1] = ~u_ptr[1] & v_ptr[1];
            u_ptr += 2;
            v_ptr += 2;
            w_ptr += 2;
        }

        if (u_buf_count & 0x1)
        {
            w_ptr[0] = ~u_ptr[0] & v_ptr[0];
            u_ptr += 1;
            v_ptr += 1;
            w_ptr += 1;
        }

        if (v_buf_count > u_buf_count)
            _COPY_MEMORY_UNIT(w_ptr, v_ptr, v_buf_count - u_buf_count);

    }

    PMC_HANDLE_UINT PMC_OneCompliment_And_BitwiseAnd_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root;
        if (nu->IS_ZERO)
        {
            ResourceHolderUINT root;
            NUMBER_OBJECT_UINT* nr = DuplicateNumber(nv);
            root.HookNumber(nr);
            PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
            root.UnlinkNumber(nr);
            return (r);
        }
        else if (nv->IS_ZERO)
            return (GET_NUMBER_HANDLE(&number_object_uint_zero));
        else
        {
            ResourceHolderUINT root;
            __UNIT_TYPE v_bit_count = nv->UNIT_BIT_COUNT;
            __UNIT_TYPE w_bit_count = v_bit_count;
            NUMBER_OBJECT_UINT* nw = root.AllocateNumber(w_bit_count);
            OneCompliment_And_BitwiseAnd_X_X(nu->BLOCK, _MINIMUM_UNIT(nu->UNIT_WORD_COUNT, nv->UNIT_WORD_COUNT), nv->BLOCK, nv->UNIT_WORD_COUNT, nw->BLOCK);
            root.CheckNumber(nw);
            CommitNumber(nw);
            if (nw->IS_ZERO)
            {
                root.DeallocateNumber(nw);
                return (GET_NUMBER_HANDLE(&number_object_uint_zero));
            }
            PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
            root.UnlinkNumber(nw);
            return (w);
        }
    }

}


/*
 * END OF FILE
 */