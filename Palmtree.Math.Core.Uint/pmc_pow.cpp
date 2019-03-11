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

    static void Pow_X_I_Imp(__UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, _UINT32_T e, __UNIT_TYPE* work1_buf, __UNIT_TYPE* work2_buf, __UNIT_TYPE* r_buf)
    {
        _UINT32_T e_mask = _rotr(1, _LZCNT_ALT_32(e) + 1);

        // この時点で e & e_mask は 0ではないはず

        __UNIT_TYPE* u_ptr = work1_buf;
        __UNIT_TYPE* v_ptr = v_buf;
        __UNIT_TYPE* w_ptr = work2_buf;
        __UNIT_TYPE u_count = v_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        _COPY_MEMORY_UNIT(work1_buf, v_buf, v_buf_count);
        e_mask >>= 1;
        while (e_mask != 0)
        {
            // u を自乗して w に格納する
            _ZERO_MEMORY_UNIT(w_ptr, u_count * 2);
            Multiply_X_X_Imp(u_ptr, u_count, u_ptr, u_count, w_ptr);
            u_count *= 2;
            if (w_ptr[u_count - 1] == 0)
                --u_count;

            // e の該当桁の bit を調べる
            if (e & e_mask)
            {
                // bit が立っていたら u = w * v とする
                _ZERO_MEMORY_UNIT(u_ptr, u_count + v_count);
                Multiply_X_X_Imp(w_ptr, u_count, v_ptr, v_count, u_ptr);
                u_count += v_count;
                if (u_ptr[u_count - 1] == 0)
                    --u_count;
            }
            else
            {
                // u と w を交換する
                __UNIT_TYPE* t_ptr = u_ptr;
                u_ptr = w_ptr;
                w_ptr = t_ptr;
            }

            e_mask >>= 1;
        }
        _COPY_MEMORY_UNIT(r_buf, u_ptr, u_count);
    }

    NUMBER_HEADER* PMC_Pow_X_I_Imp(NUMBER_HEADER* v, _UINT32_T e) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            if (e == 0)
            {
                // e が 0 である場合

                // 0 の 0 乗となるので、エラーを返す
                throw ArithmeticException(L"0の0乗の値は未定義です。");
            }
            else
            {
                // e が 0 ではない場合

                return (&number_zero);
            }
        }
        else if (v->IS_ONE)
        {
            // v が 1 である場合

            // e が何であってもべき乗は 1 となる。
            return (&number_one);
        }
        else
        {
            // v が 2 以上である場合

            if (e == 0)
            {
                // e が 0 である場合

                // 計算結果の 1 を返す
                return (&number_one);
            }
            else if (e == 1)
            {
                // e が 1 である場合

                // 計算結果の v を返す
                return (DuplicateNumber(v));
            }
            else
            {
                // v と e がともに 2 以上である場合

                // v の e 乗を計算する
                ResourceHolderUINT root;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;

                // べき乗の計算結果のビット長が論理的な限界を超えると思われる場合、エラーを返す
                if (v_bit_count > ((__UNIT_TYPE)-1 - __UNIT_TYPE_BIT_COUNT) / e)
                    throw OverflowException(L"オーバーフローにより計算を続行できません。");

                __UNIT_TYPE work_bit_count = v_bit_count * e + __UNIT_TYPE_BIT_COUNT;

                __UNIT_TYPE* work1_buf = root.AllocateBlock(work_bit_count);
                __UNIT_TYPE* work2_buf = root.AllocateBlock(work_bit_count);
                NUMBER_HEADER* r = root.AllocateNumber(work_bit_count);
                Pow_X_I_Imp(v->BLOCK, v->UNIT_WORD_COUNT, e, work1_buf, work2_buf, r->BLOCK);
                root.CheckBlock(work1_buf);
                root.CheckBlock(work2_buf);
                root.CheckNumber(r);
                CommitNumber(r);
                root.UnlinkNumber(r);
                return (r);
            }
        }
    }

#ifdef _M_X64
    static void Pow_X_L_Imp(__UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, _UINT64_T e, __UNIT_TYPE* work1_buf, __UNIT_TYPE* work2_buf, __UNIT_TYPE* r_buf)
    {
        _UINT64_T e_mask = _rotr64(1, _LZCNT_ALT_64(e) + 1);

        // この時点で e & e_mask は 0ではないはず

        __UNIT_TYPE* u_ptr = work1_buf;
        __UNIT_TYPE* v_ptr = v_buf;
        __UNIT_TYPE* w_ptr = work2_buf;
        __UNIT_TYPE u_count = v_buf_count;
        __UNIT_TYPE v_count = v_buf_count;
        _COPY_MEMORY_UNIT(work1_buf, v_buf, v_buf_count);
        e_mask >>= 1;
        while (e_mask != 0)
        {
            // u を自乗して w に格納する
            _ZERO_MEMORY_UNIT(w_ptr, u_count * 2);
            Multiply_X_X_Imp(u_ptr, u_count, u_ptr, u_count, w_ptr);
            u_count *= 2;
            if (w_ptr[u_count - 1] == 0)
                --u_count;

            // e の該当桁の bit を調べる
            if (e & e_mask)
            {
                // bit が立っていたら u = w * v とする
                _ZERO_MEMORY_UNIT(u_ptr, u_count + v_count);
                Multiply_X_X_Imp(w_ptr, u_count, v_ptr, v_count, u_ptr);
                u_count += v_count;
                if (u_ptr[u_count - 1] == 0)
                    --u_count;
            }
            else
            {
                // u と w を交換する
                __UNIT_TYPE* t_ptr = u_ptr;
                u_ptr = w_ptr;
                w_ptr = t_ptr;
            }

            e_mask >>= 1;
        }
        _COPY_MEMORY_UNIT(r_buf, u_ptr, u_count);
    }

    NUMBER_HEADER* PMC_Pow_X_L_Imp(NUMBER_HEADER* v, _UINT64_T e) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            if (e == 0)
            {
                // e が 0 である場合

                // 0 の 0 乗となるので、エラーを返す
                throw ArithmeticException(L"0の0乗の値は未定義です。");
            }
            else
            {
                // e が 0 ではない場合

                return (&number_zero);
            }
        }
        else if (v->IS_ONE)
        {
            // v が 1 である場合

            // e が何であってもべき乗は 1 となる。
            return (&number_one);
        }
        else
        {
            // v が 2 以上である場合

            if (e == 0)
            {
                // e が 0 である場合

                // 計算結果の 1 を返す
                return (&number_one);
            }
            else if (e == 1)
            {
                // e が 1 である場合

                // 計算結果の v を返す
                return (DuplicateNumber(v));
            }
            else
            {
                // v と e がともに 2 以上である場合

                // v の e 乗を計算する
                ResourceHolderUINT root;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;

                // べき乗の計算結果のビット長が論理的な限界を超えると思われる場合、エラーを返す
                if (v_bit_count > ((__UNIT_TYPE)-1 - __UNIT_TYPE_BIT_COUNT) / e)
                    throw OverflowException(L"オーバーフローにより計算を続行できません。");

                __UNIT_TYPE work_bit_count = v_bit_count * e + __UNIT_TYPE_BIT_COUNT;

                __UNIT_TYPE* work1_buf = root.AllocateBlock(work_bit_count);
                __UNIT_TYPE* work2_buf = root.AllocateBlock(work_bit_count);
                NUMBER_HEADER* r = root.AllocateNumber(work_bit_count);
                Pow_X_L_Imp(v->BLOCK, v->UNIT_WORD_COUNT, e, work1_buf, work2_buf, r->BLOCK);
                root.CheckBlock(work1_buf);
                root.CheckBlock(work2_buf);
                root.CheckNumber(r);
                CommitNumber(r);
                root.UnlinkNumber(r);
                return (r);
            }
        }
    }
#endif

    PMC_HANDLE_UINT __PMC_CALL PMC_Pow_X_I(PMC_HANDLE_UINT v, _UINT32_T e) noexcept(false)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(e) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_pow.cpp;PMC_Pow_X_I;1");
        }
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        CheckNumber((NUMBER_HEADER*)v);
        ResourceHolderUINT root;
        NUMBER_HEADER* r = PMC_Pow_X_I_Imp((NUMBER_HEADER*)v, e);
        root.HookNumber(r);
#ifdef _DEBUG
        CheckNumber(r);
#endif
        root.UnlinkNumber(r);
        return ((PMC_HANDLE_UINT)r);
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_Pow_X_L(PMC_HANDLE_UINT v, _UINT64_T e) noexcept(false)
    {
#ifdef _M_X64
        if (__UNIT_TYPE_BIT_COUNT < sizeof(e) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_pow.cpp;PMC_Pow_X_I;1");
        }
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        CheckNumber((NUMBER_HEADER*)v);
        ResourceHolderUINT root;
        NUMBER_HEADER* r = PMC_Pow_X_L_Imp((NUMBER_HEADER*)v, e);
        root.HookNumber(r);
#ifdef _DEBUG
        CheckNumber(r);
#endif
        root.UnlinkNumber(r);
        return ((PMC_HANDLE_UINT)r);
#else
        throw NotSupportedException(L"現在のプラットフォームではサポートされない機能を実行しようとしました。");
#endif
    }

    NUMBER_HEADER* PMC_TimesOfExponentOf10_Imp(_UINT32_T v, __UNIT_TYPE e)
    {
        if (v == 0)
            return (&number_zero);
        if (e == 0)
            return (From_I_Imp(v));
        ResourceHolderUINT root;
        NUMBER_HEADER* _10 = From_I_Imp(10);
        root.HookNumber(_10);
#if _M_IX86
        NUMBER_HEADER* exponent_of_10 = PMC_Pow_X_I_Imp(_10, e);
#elif defined(_M_X64)
        NUMBER_HEADER* exponent_of_10 = PMC_Pow_X_L_Imp(_10, e);
#else
#error unknown platform
#endif
        if (v == 1)
            return (exponent_of_10);
        else
        {
            root.HookNumber(exponent_of_10);
            NUMBER_HEADER* x_times_of_exponent_of_10 = PMC_Multiply_X_I_Imp(exponent_of_10, v);
            return (x_times_of_exponent_of_10);
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_TimesOfExponentOf10(_UINT32_T v, _UINT32_T e)
    {
        return ((PMC_HANDLE_UINT)PMC_TimesOfExponentOf10_Imp(v, e));
    }

    PMC_STATUS_CODE Initialize_Pow(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */