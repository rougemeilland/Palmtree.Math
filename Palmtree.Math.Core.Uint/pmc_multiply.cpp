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
#include "pmc_exception.h"
#include "pmc_uint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static void(*fp_Multiply_X_1W)(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* w);
    static void(*fp_Multiply_X_2W)(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w);
    static void(*fp_Multiply_X_X)(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w);

    void Multiply_X_X_Imp(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w)
    {
        (*fp_Multiply_X_X)(u, u_count, v, v_count, w);
    }

    __inline static __UNIT_TYPE _MULTIPLY_DIGIT_UNIT(__UNIT_TYPE k, __UNIT_TYPE* up, __UNIT_TYPE v, __UNIT_TYPE* wp)
    {
        __UNIT_TYPE t_hi;
        __UNIT_TYPE t_lo;
        t_lo = _MULTIPLY_UNIT(*up, v, &t_hi);
        _ADD_UNIT(_ADD_UNIT(0, t_lo, *wp, &t_lo), t_hi, 0, &t_hi);
        _ADD_UNIT(_ADD_UNIT(0, t_lo, k, &t_lo), t_hi, 0, &t_hi);
        *wp = t_lo;
        k = t_hi;
        return (k);
    }

    __inline static __UNIT_TYPE _MULTIPLYX_DIGIT_UNIT(__UNIT_TYPE k, __UNIT_TYPE* up, __UNIT_TYPE v, __UNIT_TYPE* wp)
    {
        __UNIT_TYPE t_hi;
        __UNIT_TYPE t_lo;
        t_lo = _MULTIPLYX_UNIT(*up, v, &t_hi);
        _ADDX_UNIT(_ADDX_UNIT(0, t_lo, *wp, &t_lo), t_hi, 0, &t_hi);
        _ADDX_UNIT(_ADDX_UNIT(0, t_lo, k, &t_lo), t_hi, 0, &t_hi);
        *wp = t_lo;
        k = t_hi;
        return (k);
    }

    __inline static void Multiply_WORD_using_MUL_ADC(__UNIT_TYPE* up, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* wp)
    {
        __UNIT_TYPE k = 0;
        __UNIT_TYPE count = u_count >> 5;

        while (count != 0)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[8], v, &wp[8]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[9], v, &wp[9]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[10], v, &wp[10]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[11], v, &wp[11]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[12], v, &wp[12]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[13], v, &wp[13]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[14], v, &wp[14]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[15], v, &wp[15]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[16], v, &wp[16]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[17], v, &wp[17]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[18], v, &wp[18]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[19], v, &wp[19]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[20], v, &wp[20]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[21], v, &wp[21]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[22], v, &wp[22]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[23], v, &wp[23]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[24], v, &wp[24]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[25], v, &wp[25]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[26], v, &wp[26]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[27], v, &wp[27]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[28], v, &wp[28]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[29], v, &wp[29]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[30], v, &wp[30]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[31], v, &wp[31]);
            up += 32;
            wp += 32;
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(32);
            else
                AddToMULTI64Counter(32);
#endif
        }

        if (u_count & 0x10)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[8], v, &wp[8]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[9], v, &wp[9]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[10], v, &wp[10]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[11], v, &wp[11]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[12], v, &wp[12]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[13], v, &wp[13]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[14], v, &wp[14]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[15], v, &wp[15]);
            up += 16;
            wp += 16;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(16);
            else
                AddToMULTI64Counter(16);
#endif
        }

        if (u_count & 0x8)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            up += 8;
            wp += 8;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(8);
            else
                AddToMULTI64Counter(8);
#endif
        }

        if (u_count & 0x4)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            up += 4;
            wp += 4;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(4);
            else
                AddToMULTI64Counter(4);
#endif
        }

        if (u_count & 0x2)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLY_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            up += 2;
            wp += 2;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }

        if (u_count & 0x1)
        {
            k = _MULTIPLY_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            up += 1;
            wp += 1;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }

        if (k != 0)
            *wp = k;
    }

    __inline static void Multiply_WORD_using_MULX_ADCX(__UNIT_TYPE* up, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* wp)
    {
        __UNIT_TYPE k = 0;
        __UNIT_TYPE count = u_count >> 5;

        while (count != 0)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[8], v, &wp[8]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[9], v, &wp[9]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[10], v, &wp[10]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[11], v, &wp[11]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[12], v, &wp[12]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[13], v, &wp[13]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[14], v, &wp[14]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[15], v, &wp[15]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[16], v, &wp[16]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[17], v, &wp[17]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[18], v, &wp[18]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[19], v, &wp[19]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[20], v, &wp[20]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[21], v, &wp[21]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[22], v, &wp[22]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[23], v, &wp[23]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[24], v, &wp[24]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[25], v, &wp[25]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[26], v, &wp[26]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[27], v, &wp[27]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[28], v, &wp[28]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[29], v, &wp[29]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[30], v, &wp[30]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[31], v, &wp[31]);
            up += 32;
            wp += 32;
            --count;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(32);
            else
                AddToMULTI64Counter(32);
#endif
        }

        if (u_count & 0x10)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[8], v, &wp[8]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[9], v, &wp[9]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[10], v, &wp[10]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[11], v, &wp[11]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[12], v, &wp[12]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[13], v, &wp[13]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[14], v, &wp[14]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[15], v, &wp[15]);
            up += 16;
            wp += 16;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(16);
            else
                AddToMULTI64Counter(16);
#endif
        }

        if (u_count & 0x8)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[4], v, &wp[4]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[5], v, &wp[5]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[6], v, &wp[6]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[7], v, &wp[7]);
            up += 8;
            wp += 8;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(8);
            else
                AddToMULTI64Counter(8);
#endif
        }

        if (u_count & 0x4)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[2], v, &wp[2]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[3], v, &wp[3]);
            up += 4;
            wp += 4;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(4);
            else
                AddToMULTI64Counter(4);
#endif
        }

        if (u_count & 0x2)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[1], v, &wp[1]);
            up += 2;
            wp += 2;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                AddToMULTI32Counter(2);
            else
                AddToMULTI64Counter(2);
#endif
        }

        if (u_count & 0x1)
        {
            k = _MULTIPLYX_DIGIT_UNIT(k, &up[0], v, &wp[0]);
            up += 1;
            wp += 1;
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(k) == sizeof(_UINT32_T))
                IncrementMULTI32Counter();
            else
                IncrementMULTI64Counter();
#endif
        }

        if (k != 0)
            *wp = k;
    }


    __inline static void Multiply_X_1W_using_MUL_ADC(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* w_buf)
    {
        Multiply_WORD_using_MUL_ADC(u_buf, u_count, v, w_buf);
    }

    __inline static void Multiply_X_1W_using_MULX_ADCX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* w_buf)
    {
        Multiply_WORD_using_MULX_ADCX(u_buf, u_count, v, w_buf);
    }

    __inline static void Multiply_X_2W_using_MUL_ADC(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w_buf)
    {
        Multiply_WORD_using_MUL_ADC(u_buf, u_count, v_lo, &w_buf[0]);
        Multiply_WORD_using_MUL_ADC(u_buf, u_count, v_hi, &w_buf[1]);
    }

    __inline static void Multiply_X_2W_using_MULX_ADCX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w_buf)
    {
        Multiply_WORD_using_MULX_ADCX(u_buf, u_count, v_lo, &w_buf[0]);
        Multiply_WORD_using_MULX_ADCX(u_buf, u_count, v_hi, &w_buf[1]);
    }

    __inline static void Multiply_X_X_using_MUL_ADC(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* w_buf)
    {
        // x のワード長が y のワード長以上であるようにする
        if (u_count < v_count)
        {
            __UNIT_TYPE* t_buf = u_buf;
            u_buf = v_buf;
            v_buf = t_buf;
            __UNIT_TYPE t_count = u_count;
            u_count = v_count;
            v_count = t_count;
        }
        __UNIT_TYPE* up = u_buf;
        __UNIT_TYPE* vp = v_buf;
        __UNIT_TYPE* wp = w_buf;

        do
        {
            Multiply_WORD_using_MUL_ADC(up, u_count, *vp, wp);
            ++vp;
            ++wp;
            --v_count;
        } while (v_count != 0);
    }

    __inline static void Multiply_X_X_using_MULX_ADCX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* w_buf)
    {
        // x のワード長が y のワード長以上であるようにする
        if (u_count < v_count)
        {
            __UNIT_TYPE* t_buf = u_buf;
            u_buf = v_buf;
            v_buf = t_buf;
            __UNIT_TYPE t_count = u_count;
            u_count = v_count;
            v_count = t_count;
        }
        __UNIT_TYPE* up = u_buf;
        __UNIT_TYPE* vp = v_buf;
        __UNIT_TYPE* wp = w_buf;

        do
        {
            Multiply_WORD_using_MULX_ADCX(up, u_count, *vp, wp);
            ++vp;
            ++wp;
            --v_count;
        } while (v_count != 0);
    }

    NUMBER_HEADER* PMC_Multiply_X_I_Imp(NUMBER_HEADER* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (From_I_Imp(v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                ResourceHolderUINT root;
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
                __UNIT_TYPE w_bit_count = u_bit_count + v_bit_count;
                NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                (*fp_Multiply_X_1W)(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK);
                root.CheckNumber(w);
                CommitNumber(w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_I_X(_UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_I_X;1");
        }
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        CheckNumber((NUMBER_HEADER*)v);
        ResourceHolderUINT root;
        NUMBER_HEADER* w = PMC_Multiply_X_I_Imp((NUMBER_HEADER*)v, u);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_I(PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_I_X;1");
        }
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"u");
        CheckNumber((NUMBER_HEADER*)u);
        ResourceHolderUINT root;
        NUMBER_HEADER* w = PMC_Multiply_X_I_Imp((NUMBER_HEADER*)u, v);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    static NUMBER_HEADER* PMC_Multiply_X_L_Imp(NUMBER_HEADER* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (From_L_Imp(v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
                {
                    // _UINT64_T が 1 ワードで表現しきれない場合

                    __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                    _UINT32_T v_hi;
                    _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                    if (v_hi == 0)
                    {
                        // v の値が 32bit で表現可能な場合
                        ResourceHolderUINT root;
                        __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                        __UNIT_TYPE w_bit_count = u_bit_count + v_bit_count;
                        NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                        (*fp_Multiply_X_1W)(u->BLOCK, u->UNIT_WORD_COUNT, v_lo, w->BLOCK);
                        root.CheckNumber(w);
                        CommitNumber(w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                    else
                    {
                        // v の値が 32bit では表現できない場合
                        ResourceHolderUINT root;
                        __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                        __UNIT_TYPE w_bit_count = u_bit_count + v_bit_count;
                        NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                        (*fp_Multiply_X_2W)(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo, w->BLOCK);
                        root.CheckNumber(w);
                        CommitNumber(w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                }
                else
                {
                    // _UINT64_T が 1 ワードで表現できる場合
                    ResourceHolderUINT root;
                    __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                    __UNIT_TYPE w_bit_count = u_bit_count + v_bit_count;
                    NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                    (*fp_Multiply_X_1W)(u->BLOCK, u->UNIT_WORD_COUNT, (__UNIT_TYPE)v, w->BLOCK);
                    root.CheckNumber(w);
                    CommitNumber(w);
                    root.UnlinkNumber(w);
                    return (w);
                }
            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_L_X(_UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_L_X;1");
        }
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        CheckNumber((NUMBER_HEADER*)v);
        ResourceHolderUINT root;
        NUMBER_HEADER* w = PMC_Multiply_X_L_Imp((NUMBER_HEADER*)v, u);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_L(PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_X_L;1");
        }
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"u");
        CheckNumber((NUMBER_HEADER*)u);
        ResourceHolderUINT root;
        NUMBER_HEADER* w = PMC_Multiply_X_L_Imp((NUMBER_HEADER*)u, v);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    static NUMBER_HEADER* PMC_Multiply_X_X_Imp(NUMBER_HEADER* u, NUMBER_HEADER* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_zero);
            }
            else if (v->IS_ONE)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_HEADER 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                ResourceHolderUINT root;
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                __UNIT_TYPE w_bit_count = u_bit_count + v_bit_count;
                NUMBER_HEADER* w = root.AllocateNumber(w_bit_count);
                (*fp_Multiply_X_X)(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK);
                root.CheckNumber(w);
                CommitNumber(w);
                root.UnlinkNumber(w);
                return (w);

            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Multiply_X_X(PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        NUMBER_HEADER* nu = (NUMBER_HEADER*)u;
        NUMBER_HEADER* nv = (NUMBER_HEADER*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        ResourceHolderUINT root;
        NUMBER_HEADER* w = PMC_Multiply_X_X_Imp(nu, nv);
        root.HookNumber(w);
#ifdef _DEBUG
        CheckNumber(w);
#endif
        root.UnlinkNumber(w);
        return ((PMC_HANDLE_UINT)w);
    }

    PMC_STATUS_CODE Initialize_Multiply(PROCESSOR_FEATURES* feature)
    {
        if (feature->PROCESSOR_FEATURE_ADX && feature->PROCESSOR_FEATURE_BMI2)
        {
            fp_Multiply_X_1W = Multiply_X_1W_using_MULX_ADCX;
            fp_Multiply_X_2W = Multiply_X_2W_using_MULX_ADCX;
            fp_Multiply_X_X = Multiply_X_X_using_MULX_ADCX;
        }
        else
        {
            fp_Multiply_X_1W = Multiply_X_1W_using_MUL_ADC;
            fp_Multiply_X_2W = Multiply_X_2W_using_MUL_ADC;
            fp_Multiply_X_X = Multiply_X_X_using_MUL_ADC;
        }
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */