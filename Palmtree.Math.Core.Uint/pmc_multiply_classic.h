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

#pragma once

#ifndef PMC_MULTIPLY_CLASSIC_H
#define PMC_MULTIPLY_CLASSIC_H

#include "pmc_uint_internal.h"

namespace Palmtree::Math::Core::Internal::Multiply::Classic
{

    extern void Multiply_UX_1W(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE v, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count);
    extern void Multiply_UX_2W(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count);
    extern void Multiply_UX_UX(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* w_buf, __UNIT_TYPE w_buf_count);

}

#endif


/*
 * END OF FILE
 */
