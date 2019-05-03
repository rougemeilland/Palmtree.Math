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


#include "pmc_multiply_classic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

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

    __inline static void Multiply_WORD(__UNIT_TYPE* up, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* wp)
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

    ClassicMultiplicationEngine::ClassicMultiplicationEngine()
    {
    }

    ClassicMultiplicationEngine::~ClassicMultiplicationEngine()
    {
    }

    void ClassicMultiplicationEngine::Multiply_UX_1W(__UNIT_TYPE * u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE * w_buf)
    {
        Multiply_WORD(u_buf, u_count, v, w_buf);
    }

    void ClassicMultiplicationEngine::Multiply_UX_2W(__UNIT_TYPE * u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE * w_buf)
    {
        Multiply_WORD(u_buf, u_count, v_lo, &w_buf[0]);
        Multiply_WORD(u_buf, u_count, v_hi, &w_buf[1]);
    }

    void ClassicMultiplicationEngine::Multiply_UX_UX(ThreadContext& tc, __UNIT_TYPE * u_buf, __UNIT_TYPE u_count, __UNIT_TYPE * v_buf, __UNIT_TYPE v_count, __UNIT_TYPE * w_buf)
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
            Multiply_WORD(up, u_count, *vp, wp);
            ++vp;
            ++wp;
            --v_count;
        } while (v_count != 0);
    }

}


/*
 * END OF FILE
 */