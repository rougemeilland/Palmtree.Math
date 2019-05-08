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
#include "pmc_multiply_classic.h"
#include "pmc_multiply_karatsuba.h"
#include "pmc_multiply_schonHagestrassen.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static ClassicMultiplicationEngine* _engine_classic;
    static KaratsubaMultiplicationEngine* _engine_karatsuba;
    static KaratsubaMultiplicationEngine* _fixed_engine_karatsuba;
    static SchonHageStrassenMultiplicationEngine* _engine_schonHagestrassen;
    static SchonHageStrassenMultiplicationEngine* _fixed_engine_schonHagestrassen;

    static bool AutoKaratsubaCondition(__UNIT_TYPE u_count, __UNIT_TYPE v_count)
    {
#ifdef _M_IX86
        return (u_count >= 65536 / __UNIT_TYPE_BIT_COUNT && v_count >= 53974 / __UNIT_TYPE_BIT_COUNT);
#elif defined(_M_X64)
        return (u_count >= 131072 / __UNIT_TYPE_BIT_COUNT && v_count >= 120016 / __UNIT_TYPE_BIT_COUNT);
#else
#error unknown platform
#endif
    }

    static bool AutoSchonStrassenCondition(__UNIT_TYPE u_count, __UNIT_TYPE v_count)
    {
        return (false);
    }

    void Multiply_UX_UX_Imp(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, __UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count, __UNIT_TYPE* w)
    {
        switch (method)
        {
        case PMC_MULTIPLICATION_METHOD_AUTO:
            if (u_count > v_count ? AutoSchonStrassenCondition(u_count, v_count) : AutoSchonStrassenCondition(v_count, u_count))
                return (_engine_schonHagestrassen->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
            else if (AutoKaratsubaCondition(u_count, v_count))
                return (_engine_karatsuba->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
            else
                return (_engine_classic->Multiply_UX_UX(u, u_count, v, v_count, w));
        case PMC_MULTIPLICATION_METHOD_CLASSIC:
            return (_engine_classic->Multiply_UX_UX(u, u_count, v, v_count, w));
        case PMC_MULTIPLICATION_METHOD_KARATSUBA:
            return (_engine_karatsuba->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
        case PMC_MULTIPLICATION_METHOD_FIXED_KARATSUBA:
            return (_fixed_engine_karatsuba->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
        case PMC_MULTIPLICATION_METHOD_SCHONSTRASSEN:
            return (_engine_schonHagestrassen->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
        case PMC_MULTIPLICATION_METHOD_FIXED_SCHONSTRASSEN:
            return (_fixed_engine_schonHagestrassen->Multiply_UX_UX(tc, u, u_count, v, v_count, w));
        default:
            throw ArgumentException(L"methodが不正です。");
        }
    }

    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UI_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                ResourceHolderUINT root(tc);
                // 乗算 engine での処理の簡素化のために、w のビット長は u と v のワード長から計算する。
                __UNIT_TYPE w_bit_count = (u->UNIT_WORD_COUNT + 1) * __UNIT_TYPE_BIT_COUNT;
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                _engine_classic->Multiply_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Multiply_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v == 0)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v == 1)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
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
                        ResourceHolderUINT root(tc);
                        // 乗算 engine での処理の簡素化のために、w のビット長は u と v のワード長から計算する。
                        __UNIT_TYPE w_bit_count = (u->UNIT_WORD_COUNT + 1) * __UNIT_TYPE_BIT_COUNT;
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                        _engine_classic->Multiply_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v_lo, w->BLOCK);
#ifdef _DEBUG
                        root.CheckNumber(w);
#endif
                        CommitNumber(tc, w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                    else
                    {
                        // v の値が 32bit では表現できない場合
                        ResourceHolderUINT root(tc);
                        // 乗算 engine での処理の簡素化のために、w のビット長は u と v のワード長から計算する。
                        __UNIT_TYPE w_bit_count = (u->UNIT_WORD_COUNT + 2) * __UNIT_TYPE_BIT_COUNT;
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                        _engine_classic->Multiply_UX_2W(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo, w->BLOCK);
#ifdef _DEBUG
                        root.CheckNumber(w);
#endif
                        CommitNumber(tc, w);
                        root.UnlinkNumber(w);
                        return (w);
                    }
                }
                else
                {
                    // _UINT64_T が 1 ワードで表現できる場合
                    ResourceHolderUINT root(tc);
                    // 乗算 engine での処理の簡素化のために、w のビット長は u と v のワード長から計算する。
                    __UNIT_TYPE w_bit_count = (u->UNIT_WORD_COUNT + 1) * __UNIT_TYPE_BIT_COUNT;
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                    _engine_classic->Multiply_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, (__UNIT_TYPE)v, w->BLOCK);
#ifdef _DEBUG
                    root.CheckNumber(w);
#endif
                    CommitNumber(tc, w);
                    root.UnlinkNumber(w);
                    return (w);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_Multiply_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_multiply.cpp;PMC_Multiply_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    NUMBER_OBJECT_UINT* PMC_Multiply_UX_UX_Imp(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // v の値にかかわらず 0 を返す。
            return (&number_object_uint_zero);
        }
        else if (u->IS_ONE)
        {
            // u が 1 である場合
            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 乗算結果は v に等しいため、v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, v));
            }
        }
        else
        {
            // u が 0 と 1 のどちらでもない場合

            if (v->IS_ZERO)
            {
                // v が 0 である場合

                //  0  を返す。
                return (&number_object_uint_zero);
            }
            else if (v->IS_ONE)
            {
                // v が 1 である場合

                // 乗算結果は u に等しいため、u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 、1 のどちらでもない場合

                // u と v の積を計算する
                ResourceHolderUINT root(tc);
                // 乗算 engine での処理の簡素化のために、w のビット長は u と v のワード長から計算する。
                __UNIT_TYPE w_bit_count = (u->UNIT_WORD_COUNT + v->UNIT_WORD_COUNT) * __UNIT_TYPE_BIT_COUNT;
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                Multiply_UX_UX_Imp(tc, method, u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);

            }
        }
    }

    PMC_HANDLE_UINT PMC_Multiply_UX_UX(ThreadContext& tc, PMC_MULTIPLICATION_METHOD_CODE method, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Multiply_UX_UX_Imp(tc, method, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_Multiply(PROCESSOR_FEATURES* feature)
    {
        try
        {
            _engine_classic = new ClassicMultiplicationEngine();
            _engine_karatsuba = new KaratsubaMultiplicationEngine(false, *_engine_classic);
            _fixed_engine_karatsuba = new KaratsubaMultiplicationEngine(true, *_engine_classic);
            _engine_schonHagestrassen = new SchonHageStrassenMultiplicationEngine(false, *_engine_karatsuba);
            _fixed_engine_schonHagestrassen = new SchonHageStrassenMultiplicationEngine(true, *_engine_karatsuba);
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