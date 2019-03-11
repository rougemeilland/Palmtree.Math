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
#include "pmc_exception.h"
#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    void RightShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, BOOL padding_zero)
    {
        __UNIT_TYPE* pp = p;
        __UNIT_TYPE p_count = p_word_count;
        __UNIT_TYPE* op = o;
        // n_word_count ワード右に移動し、更に n_bit_count ビット右に移動する。
        __UNIT_TYPE n_word_count = n / __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE n_rshift_bit_count = n % __UNIT_TYPE_BIT_COUNT;
        if (n_rshift_bit_count == 0)
        {
            // シフト数がちょうどワード境界分であれば単にワード単位のデータ移動のみ行う。
            _COPY_MEMORY_UNIT(op, pp + n_word_count, p_count - n_word_count);
            if (padding_zero)
                _ZERO_MEMORY_UNIT(op + p_count - n_word_count, n_word_count);
        }
        else
        {
            pp += n_word_count;
            __UNIT_TYPE n_lshift_bit_count = __UNIT_TYPE_BIT_COUNT - n_rshift_bit_count;
            // p_count - n_word_count 回繰り返し

            __UNIT_TYPE temp = *pp++;
            __UNIT_TYPE work;
            __UNIT_TYPE t_count = p_count - n_word_count - 1;

            __UNIT_TYPE count = t_count >> 5;
            while (count > 0)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                work = temp >> n_rshift_bit_count; temp = pp[1]; work |= temp << n_lshift_bit_count; op[1] = work;
                work = temp >> n_rshift_bit_count; temp = pp[2]; work |= temp << n_lshift_bit_count; op[2] = work;
                work = temp >> n_rshift_bit_count; temp = pp[3]; work |= temp << n_lshift_bit_count; op[3] = work;
                work = temp >> n_rshift_bit_count; temp = pp[4]; work |= temp << n_lshift_bit_count; op[4] = work;
                work = temp >> n_rshift_bit_count; temp = pp[5]; work |= temp << n_lshift_bit_count; op[5] = work;
                work = temp >> n_rshift_bit_count; temp = pp[6]; work |= temp << n_lshift_bit_count; op[6] = work;
                work = temp >> n_rshift_bit_count; temp = pp[7]; work |= temp << n_lshift_bit_count; op[7] = work;
                work = temp >> n_rshift_bit_count; temp = pp[8]; work |= temp << n_lshift_bit_count; op[8] = work;
                work = temp >> n_rshift_bit_count; temp = pp[9]; work |= temp << n_lshift_bit_count; op[9] = work;
                work = temp >> n_rshift_bit_count; temp = pp[10]; work |= temp << n_lshift_bit_count; op[10] = work;
                work = temp >> n_rshift_bit_count; temp = pp[11]; work |= temp << n_lshift_bit_count; op[11] = work;
                work = temp >> n_rshift_bit_count; temp = pp[12]; work |= temp << n_lshift_bit_count; op[12] = work;
                work = temp >> n_rshift_bit_count; temp = pp[13]; work |= temp << n_lshift_bit_count; op[13] = work;
                work = temp >> n_rshift_bit_count; temp = pp[14]; work |= temp << n_lshift_bit_count; op[14] = work;
                work = temp >> n_rshift_bit_count; temp = pp[15]; work |= temp << n_lshift_bit_count; op[15] = work;
                work = temp >> n_rshift_bit_count; temp = pp[16]; work |= temp << n_lshift_bit_count; op[16] = work;
                work = temp >> n_rshift_bit_count; temp = pp[17]; work |= temp << n_lshift_bit_count; op[17] = work;
                work = temp >> n_rshift_bit_count; temp = pp[18]; work |= temp << n_lshift_bit_count; op[18] = work;
                work = temp >> n_rshift_bit_count; temp = pp[19]; work |= temp << n_lshift_bit_count; op[19] = work;
                work = temp >> n_rshift_bit_count; temp = pp[20]; work |= temp << n_lshift_bit_count; op[20] = work;
                work = temp >> n_rshift_bit_count; temp = pp[21]; work |= temp << n_lshift_bit_count; op[21] = work;
                work = temp >> n_rshift_bit_count; temp = pp[22]; work |= temp << n_lshift_bit_count; op[22] = work;
                work = temp >> n_rshift_bit_count; temp = pp[23]; work |= temp << n_lshift_bit_count; op[23] = work;
                work = temp >> n_rshift_bit_count; temp = pp[24]; work |= temp << n_lshift_bit_count; op[24] = work;
                work = temp >> n_rshift_bit_count; temp = pp[25]; work |= temp << n_lshift_bit_count; op[25] = work;
                work = temp >> n_rshift_bit_count; temp = pp[26]; work |= temp << n_lshift_bit_count; op[26] = work;
                work = temp >> n_rshift_bit_count; temp = pp[27]; work |= temp << n_lshift_bit_count; op[27] = work;
                work = temp >> n_rshift_bit_count; temp = pp[28]; work |= temp << n_lshift_bit_count; op[28] = work;
                work = temp >> n_rshift_bit_count; temp = pp[29]; work |= temp << n_lshift_bit_count; op[29] = work;
                work = temp >> n_rshift_bit_count; temp = pp[30]; work |= temp << n_lshift_bit_count; op[30] = work;
                work = temp >> n_rshift_bit_count; temp = pp[31]; work |= temp << n_lshift_bit_count; op[31] = work;
                --count;
                pp += 32;
                op += 32;
            }

            if (t_count & 0x10)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                work = temp >> n_rshift_bit_count; temp = pp[1]; work |= temp << n_lshift_bit_count; op[1] = work;
                work = temp >> n_rshift_bit_count; temp = pp[2]; work |= temp << n_lshift_bit_count; op[2] = work;
                work = temp >> n_rshift_bit_count; temp = pp[3]; work |= temp << n_lshift_bit_count; op[3] = work;
                work = temp >> n_rshift_bit_count; temp = pp[4]; work |= temp << n_lshift_bit_count; op[4] = work;
                work = temp >> n_rshift_bit_count; temp = pp[5]; work |= temp << n_lshift_bit_count; op[5] = work;
                work = temp >> n_rshift_bit_count; temp = pp[6]; work |= temp << n_lshift_bit_count; op[6] = work;
                work = temp >> n_rshift_bit_count; temp = pp[7]; work |= temp << n_lshift_bit_count; op[7] = work;
                work = temp >> n_rshift_bit_count; temp = pp[8]; work |= temp << n_lshift_bit_count; op[8] = work;
                work = temp >> n_rshift_bit_count; temp = pp[9]; work |= temp << n_lshift_bit_count; op[9] = work;
                work = temp >> n_rshift_bit_count; temp = pp[10]; work |= temp << n_lshift_bit_count; op[10] = work;
                work = temp >> n_rshift_bit_count; temp = pp[11]; work |= temp << n_lshift_bit_count; op[11] = work;
                work = temp >> n_rshift_bit_count; temp = pp[12]; work |= temp << n_lshift_bit_count; op[12] = work;
                work = temp >> n_rshift_bit_count; temp = pp[13]; work |= temp << n_lshift_bit_count; op[13] = work;
                work = temp >> n_rshift_bit_count; temp = pp[14]; work |= temp << n_lshift_bit_count; op[14] = work;
                work = temp >> n_rshift_bit_count; temp = pp[15]; work |= temp << n_lshift_bit_count; op[15] = work;
                pp += 16;
                op += 16;
            }

            if (t_count & 0x8)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                work = temp >> n_rshift_bit_count; temp = pp[1]; work |= temp << n_lshift_bit_count; op[1] = work;
                work = temp >> n_rshift_bit_count; temp = pp[2]; work |= temp << n_lshift_bit_count; op[2] = work;
                work = temp >> n_rshift_bit_count; temp = pp[3]; work |= temp << n_lshift_bit_count; op[3] = work;
                work = temp >> n_rshift_bit_count; temp = pp[4]; work |= temp << n_lshift_bit_count; op[4] = work;
                work = temp >> n_rshift_bit_count; temp = pp[5]; work |= temp << n_lshift_bit_count; op[5] = work;
                work = temp >> n_rshift_bit_count; temp = pp[6]; work |= temp << n_lshift_bit_count; op[6] = work;
                work = temp >> n_rshift_bit_count; temp = pp[7]; work |= temp << n_lshift_bit_count; op[7] = work;
                pp += 8;
                op += 8;
            }

            if (t_count & 0x4)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                work = temp >> n_rshift_bit_count; temp = pp[1]; work |= temp << n_lshift_bit_count; op[1] = work;
                work = temp >> n_rshift_bit_count; temp = pp[2]; work |= temp << n_lshift_bit_count; op[2] = work;
                work = temp >> n_rshift_bit_count; temp = pp[3]; work |= temp << n_lshift_bit_count; op[3] = work;
                pp += 4;
                op += 4;
            }

            if (t_count & 0x2)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                work = temp >> n_rshift_bit_count; temp = pp[1]; work |= temp << n_lshift_bit_count; op[1] = work;
                pp += 2;
                op += 2;
            }

            if (t_count & 0x1)
            {
                work = temp >> n_rshift_bit_count; temp = pp[0]; work |= temp << n_lshift_bit_count; op[0] = work;
                pp += 1;
                op += 1;
            }

            work = temp >> n_rshift_bit_count;
            if (work != 0 || padding_zero)
                *op = work;

            if (padding_zero)
                _ZERO_MEMORY_UNIT(o + p_word_count - n_word_count, n_word_count);
        }
    }

    void LeftShift_Imp(__UNIT_TYPE* p, __UNIT_TYPE p_word_count, __UNIT_TYPE n, __UNIT_TYPE* o, BOOL padding_zero)
    {
        __UNIT_TYPE* pp = p;
        __UNIT_TYPE p_count = p_word_count;
        __UNIT_TYPE* op = o;
        __UNIT_TYPE n_word_count = n / __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE n_lshift_bit_count = n % __UNIT_TYPE_BIT_COUNT;
        if (n_lshift_bit_count == 0)
        {
            // シフト数がちょうどワード境界分であれば単にワード単位のデータ移動のみ行う。
            _COPY_MEMORY_UNIT(op + n_word_count, pp, p_count);
            if (padding_zero)
                _ZERO_MEMORY_UNIT(op, n_word_count);
        }
        else
        {
            __UNIT_TYPE n_rshift_bit_count = __UNIT_TYPE_BIT_COUNT - n_lshift_bit_count;
            pp += p_count - 1;
            op += p_count + n_word_count;
            p_count -= 1;
            __UNIT_TYPE temp = *pp;
            __UNIT_TYPE work = temp >> n_rshift_bit_count;
            if (work != 0)
                *op = work;
            --pp;
            --op;

            __UNIT_TYPE count = p_count >> 5;
            while (count != 0)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                work = temp << n_lshift_bit_count; temp = pp[-1]; work |= temp >> n_rshift_bit_count; op[-1] = work;
                work = temp << n_lshift_bit_count; temp = pp[-2]; work |= temp >> n_rshift_bit_count; op[-2] = work;
                work = temp << n_lshift_bit_count; temp = pp[-3]; work |= temp >> n_rshift_bit_count; op[-3] = work;
                work = temp << n_lshift_bit_count; temp = pp[-4]; work |= temp >> n_rshift_bit_count; op[-4] = work;
                work = temp << n_lshift_bit_count; temp = pp[-5]; work |= temp >> n_rshift_bit_count; op[-5] = work;
                work = temp << n_lshift_bit_count; temp = pp[-6]; work |= temp >> n_rshift_bit_count; op[-6] = work;
                work = temp << n_lshift_bit_count; temp = pp[-7]; work |= temp >> n_rshift_bit_count; op[-7] = work;
                work = temp << n_lshift_bit_count; temp = pp[-8]; work |= temp >> n_rshift_bit_count; op[-8] = work;
                work = temp << n_lshift_bit_count; temp = pp[-9]; work |= temp >> n_rshift_bit_count; op[-9] = work;
                work = temp << n_lshift_bit_count; temp = pp[-10]; work |= temp >> n_rshift_bit_count; op[-10] = work;
                work = temp << n_lshift_bit_count; temp = pp[-11]; work |= temp >> n_rshift_bit_count; op[-11] = work;
                work = temp << n_lshift_bit_count; temp = pp[-12]; work |= temp >> n_rshift_bit_count; op[-12] = work;
                work = temp << n_lshift_bit_count; temp = pp[-13]; work |= temp >> n_rshift_bit_count; op[-13] = work;
                work = temp << n_lshift_bit_count; temp = pp[-14]; work |= temp >> n_rshift_bit_count; op[-14] = work;
                work = temp << n_lshift_bit_count; temp = pp[-15]; work |= temp >> n_rshift_bit_count; op[-15] = work;
                work = temp << n_lshift_bit_count; temp = pp[-16]; work |= temp >> n_rshift_bit_count; op[-16] = work;
                work = temp << n_lshift_bit_count; temp = pp[-17]; work |= temp >> n_rshift_bit_count; op[-17] = work;
                work = temp << n_lshift_bit_count; temp = pp[-18]; work |= temp >> n_rshift_bit_count; op[-18] = work;
                work = temp << n_lshift_bit_count; temp = pp[-19]; work |= temp >> n_rshift_bit_count; op[-19] = work;
                work = temp << n_lshift_bit_count; temp = pp[-20]; work |= temp >> n_rshift_bit_count; op[-20] = work;
                work = temp << n_lshift_bit_count; temp = pp[-21]; work |= temp >> n_rshift_bit_count; op[-21] = work;
                work = temp << n_lshift_bit_count; temp = pp[-22]; work |= temp >> n_rshift_bit_count; op[-22] = work;
                work = temp << n_lshift_bit_count; temp = pp[-23]; work |= temp >> n_rshift_bit_count; op[-23] = work;
                work = temp << n_lshift_bit_count; temp = pp[-24]; work |= temp >> n_rshift_bit_count; op[-24] = work;
                work = temp << n_lshift_bit_count; temp = pp[-25]; work |= temp >> n_rshift_bit_count; op[-25] = work;
                work = temp << n_lshift_bit_count; temp = pp[-26]; work |= temp >> n_rshift_bit_count; op[-26] = work;
                work = temp << n_lshift_bit_count; temp = pp[-27]; work |= temp >> n_rshift_bit_count; op[-27] = work;
                work = temp << n_lshift_bit_count; temp = pp[-28]; work |= temp >> n_rshift_bit_count; op[-28] = work;
                work = temp << n_lshift_bit_count; temp = pp[-29]; work |= temp >> n_rshift_bit_count; op[-29] = work;
                work = temp << n_lshift_bit_count; temp = pp[-30]; work |= temp >> n_rshift_bit_count; op[-30] = work;
                work = temp << n_lshift_bit_count; temp = pp[-31]; work |= temp >> n_rshift_bit_count; op[-31] = work;
                pp -= 32;
                op -= 32;
                --count;
            }

            if (p_count & 0x10)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                work = temp << n_lshift_bit_count; temp = pp[-1]; work |= temp >> n_rshift_bit_count; op[-1] = work;
                work = temp << n_lshift_bit_count; temp = pp[-2]; work |= temp >> n_rshift_bit_count; op[-2] = work;
                work = temp << n_lshift_bit_count; temp = pp[-3]; work |= temp >> n_rshift_bit_count; op[-3] = work;
                work = temp << n_lshift_bit_count; temp = pp[-4]; work |= temp >> n_rshift_bit_count; op[-4] = work;
                work = temp << n_lshift_bit_count; temp = pp[-5]; work |= temp >> n_rshift_bit_count; op[-5] = work;
                work = temp << n_lshift_bit_count; temp = pp[-6]; work |= temp >> n_rshift_bit_count; op[-6] = work;
                work = temp << n_lshift_bit_count; temp = pp[-7]; work |= temp >> n_rshift_bit_count; op[-7] = work;
                work = temp << n_lshift_bit_count; temp = pp[-8]; work |= temp >> n_rshift_bit_count; op[-8] = work;
                work = temp << n_lshift_bit_count; temp = pp[-9]; work |= temp >> n_rshift_bit_count; op[-9] = work;
                work = temp << n_lshift_bit_count; temp = pp[-10]; work |= temp >> n_rshift_bit_count; op[-10] = work;
                work = temp << n_lshift_bit_count; temp = pp[-11]; work |= temp >> n_rshift_bit_count; op[-11] = work;
                work = temp << n_lshift_bit_count; temp = pp[-12]; work |= temp >> n_rshift_bit_count; op[-12] = work;
                work = temp << n_lshift_bit_count; temp = pp[-13]; work |= temp >> n_rshift_bit_count; op[-13] = work;
                work = temp << n_lshift_bit_count; temp = pp[-14]; work |= temp >> n_rshift_bit_count; op[-14] = work;
                work = temp << n_lshift_bit_count; temp = pp[-15]; work |= temp >> n_rshift_bit_count; op[-15] = work;
                pp -= 16;
                op -= 16;
            }

            if (p_count & 0x8)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                work = temp << n_lshift_bit_count; temp = pp[-1]; work |= temp >> n_rshift_bit_count; op[-1] = work;
                work = temp << n_lshift_bit_count; temp = pp[-2]; work |= temp >> n_rshift_bit_count; op[-2] = work;
                work = temp << n_lshift_bit_count; temp = pp[-3]; work |= temp >> n_rshift_bit_count; op[-3] = work;
                work = temp << n_lshift_bit_count; temp = pp[-4]; work |= temp >> n_rshift_bit_count; op[-4] = work;
                work = temp << n_lshift_bit_count; temp = pp[-5]; work |= temp >> n_rshift_bit_count; op[-5] = work;
                work = temp << n_lshift_bit_count; temp = pp[-6]; work |= temp >> n_rshift_bit_count; op[-6] = work;
                work = temp << n_lshift_bit_count; temp = pp[-7]; work |= temp >> n_rshift_bit_count; op[-7] = work;
                pp -= 8;
                op -= 8;
            }

            if (p_count & 0x4)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                work = temp << n_lshift_bit_count; temp = pp[-1]; work |= temp >> n_rshift_bit_count; op[-1] = work;
                work = temp << n_lshift_bit_count; temp = pp[-2]; work |= temp >> n_rshift_bit_count; op[-2] = work;
                work = temp << n_lshift_bit_count; temp = pp[-3]; work |= temp >> n_rshift_bit_count; op[-3] = work;
                pp -= 4;
                op -= 4;
            }

            if (p_count & 0x2)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                work = temp << n_lshift_bit_count; temp = pp[-1]; work |= temp >> n_rshift_bit_count; op[-1] = work;
                pp -= 2;
                op -= 2;
            }

            if (p_count & 0x1)
            {
                work = temp << n_lshift_bit_count; temp = pp[-0]; work |= temp >> n_rshift_bit_count; op[-0] = work;
                pp -= 1;
                op -= 1;
            }
            work = temp << n_lshift_bit_count;
            *op = work;

            if (padding_zero)
                _ZERO_MEMORY_UNIT(o, n_word_count);
        }
    }

    static NUMBER_HEADER* PMC_RightShift_X_I_Imp(NUMBER_HEADER* u, _UINT32_T n)
    {
        if (u->IS_ZERO)
            return (&number_zero);
        else if (n == 0)
            return (DuplicateNumber(u));
        else
        {
            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            if (u_bit_count <= n)
                return (&number_zero);
            else
            {
                ResourceHolderUINT root;
                __UNIT_TYPE w_bit_count = u_bit_count - n;
                NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                RightShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, FALSE);
                root.CheckNumber(w);
                CommitNumber(w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    static NUMBER_HEADER* PMC_LeftShift_X_I_Imp(NUMBER_HEADER* u, _UINT32_T n)
    {
        if (u->IS_ZERO)
            return (&number_zero);
        else if (n == 0)
            return (DuplicateNumber(u));
        else
        {
            ResourceHolderUINT root;
            __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
            __UNIT_TYPE w_bit_count = u_bit_count + n;
            NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
            LeftShift_Imp(u->BLOCK, u->UNIT_WORD_COUNT, n, w->BLOCK, FALSE);
            root.CheckNumber(w);
            CommitNumber(w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_RightShift_X_I(PMC_HANDLE_UINT u, _INT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_shift.cpp;PMC_RightShift_X_I;1");
        }
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"u");
        NUMBER_HEADER* nu = (NUMBER_HEADER*)u;
        CheckNumber(nu);
        ResourceHolderUINT root;
        char n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        NUMBER_HEADER* w = n_sign >= 0 ? PMC_RightShift_X_I_Imp(nu, n_abs) : PMC_LeftShift_X_I_Imp(nu, n_abs);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_LeftShift_X_I(PMC_HANDLE_UINT u, _INT32_T n) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(n) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_LeftShift_X_I;1");
        }
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"u");
        NUMBER_HEADER* nu = (NUMBER_HEADER*)u;
        CheckNumber(nu);
        ResourceHolderUINT root;
        char n_sign;
        _UINT32_T n_abs = GET_ABS_32(n, &n_sign);
        NUMBER_HEADER* w = n_sign >= 0 ? PMC_LeftShift_X_I_Imp(nu, n_abs) : PMC_RightShift_X_I_Imp(nu, n_abs);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    PMC_STATUS_CODE Initialize_Shift(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */
