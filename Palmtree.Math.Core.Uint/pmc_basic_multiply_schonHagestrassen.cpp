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

#include "pmc_basic_multiply_schonHagestrassen.h"
#include "pmc_basic_multiply_toomcook.h"
#include "pmc_basic.h"
#include "pmc_exception.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal::Multiply::SchonHageStrassen
{

    SchonHageStrassenMultiplicationEngine::SchonHageStrassenMultiplicationEngine(bool fixed, Multiply::ToomCook::ToomCookMultiplicationEngine & toomcook_engine, Multiply::Classic::ClassicMultiplicationEngine & classic_engine)
        : _fixed(fixed), _toomcook_engine(toomcook_engine), _classic_engine(classic_engine)
    {
    }

    SchonHageStrassenMultiplicationEngine::~SchonHageStrassenMultiplicationEngine()
    {
    }

    void SchonHageStrassenMultiplicationEngine::Multiply_UX_UX(ThreadContext & tc, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T & w_buf)
    {
        _toomcook_engine.Multiply_UX_UX(tc, u_buf, v_buf, w_buf);
    }

}


/*
 * END OF FILE
 */