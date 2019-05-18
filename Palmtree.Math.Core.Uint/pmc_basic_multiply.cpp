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

#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_basic_multiply_classic.h"
#include "pmc_basic_multiply_karatsuba.h"
#include "pmc_basic_multiply_toomcook.h"
#include "pmc_basic_multiply_schonHagestrassen.h"

namespace Palmtree::Math::Core::Internal
{

    static ClassicMultiplicationEngine* _engine_classic;
    static KaratsubaMultiplicationEngine* _engine_karatsuba;
    static KaratsubaMultiplicationEngine* _fixed_engine_karatsuba;
    static ToomCookMultiplicationEngine* _engine_toomcook;
    static ToomCookMultiplicationEngine* _fixed_engine_toomcook;
    static SchonHageStrassenMultiplicationEngine* _engine_schonHagestrassen;
    static SchonHageStrassenMultiplicationEngine* _fixed_engine_schonHagestrassen;

    void BasicOperatorEngine::Multiply(_UBASIC_T u_buf, __UNIT_TYPE v, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;BasicOperatorEngine::Multiply;1");
#endif
        if (v == 0)
            w_buf.Clear(); 
        else if (u_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else
            _engine_classic->Multiply_UX_1W(u_buf, v, w_buf);
    }

    void BasicOperatorEngine::Multiply(_UBASIC_T u_buf, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;BasicOperatorEngine::Multiply;1");
#endif
        if (v_hi == 0)
            Multiply(u_buf, v_lo, w_buf);
        else if (u_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else
            _engine_classic->Multiply_UX_2W(u_buf, v_hi, v_lo, w_buf);
    }

    void BasicOperatorEngine::Multiply(ThreadContext & tc, PMC_MULTIPLICATION_METHOD_CODE method, _UBASIC_T u_buf, _UBASIC_T v_buf, _UBASIC_T w_buf)
    {
#ifdef _DEBUG
        if (u_buf.BLOCK_COUNT > 0 && u_buf.BLOCK[u_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;BasicOperatorEngine::Multiply;1");
        if (v_buf.BLOCK_COUNT > 0 && v_buf.BLOCK[v_buf.BLOCK_COUNT - 1] == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_basic_multiply.cpp;BasicOperatorEngine::Multiply;2");
#endif
        if (u_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else if (v_buf.BLOCK_COUNT == 0)
            w_buf.Clear();
        else
        {
            switch (method)
            {
            case PMC_MULTIPLICATION_METHOD_AUTO:
                return (_engine_schonHagestrassen->Multiply_UX_UX(tc, u_buf, v_buf, w_buf));
            case PMC_MULTIPLICATION_METHOD_CLASSIC:
                return (_engine_classic->Multiply_UX_UX(u_buf, v_buf, w_buf));
            case PMC_MULTIPLICATION_METHOD_KARATSUBA:
                return (_engine_karatsuba->Multiply_UX_UX(tc, u_buf, v_buf, w_buf));
            case PMC_MULTIPLICATION_METHOD_FIXED_KARATSUBA:
                return (_fixed_engine_karatsuba->Multiply_UX_UX(tc, u_buf, v_buf, w_buf));
            case PMC_MULTIPLICATION_METHOD_SCHONSTRASSEN:
                return (_engine_schonHagestrassen->Multiply_UX_UX(tc, u_buf, v_buf, w_buf));
            case PMC_MULTIPLICATION_METHOD_FIXED_SCHONSTRASSEN:
                return (_fixed_engine_schonHagestrassen->Multiply_UX_UX(tc, u_buf, v_buf, w_buf));
            default:
                throw ArgumentException(L"methodが不正です。");
            }
        }
    }

    PMC_STATUS_CODE Initialize_BasicMultiply(PROCESSOR_FEATURES* feature)
    {
        try
        {
            _engine_classic = new ClassicMultiplicationEngine();
            _engine_karatsuba = new KaratsubaMultiplicationEngine(false, *_engine_classic, basic_ep);
            _fixed_engine_karatsuba = new KaratsubaMultiplicationEngine(true, *_engine_classic, basic_ep);
            _engine_toomcook = new ToomCookMultiplicationEngine(false, *_engine_karatsuba, *_engine_classic);
            _fixed_engine_toomcook = new ToomCookMultiplicationEngine(true, *_engine_karatsuba, *_engine_classic);
            _engine_schonHagestrassen = new SchonHageStrassenMultiplicationEngine(false, *_engine_toomcook, *_engine_classic);
            _fixed_engine_schonHagestrassen = new SchonHageStrassenMultiplicationEngine(true, *_engine_toomcook, *_engine_classic);
            return (PMC_STATUS_OK);
        }
        catch (std::bad_alloc)
        {
            return (PMC_STATUS_NOT_ENOUGH_MEMORY);
        }
    }

}


/*
 * END OF FILE
 */