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


//#define DO_TRACE (1)
//#define _LOG_MEMORY

namespace Palmtree::Math::Core::Internal
{

    static int Compare_Easy(__UNIT_TYPE* u, __UNIT_TYPE u_count, __UNIT_TYPE* v, __UNIT_TYPE v_count)
    {
        if (u_count > v_count)
            return (1);
        else if (u_count < v_count)
            return (-1);
        else
            return (Compare_Imp(u, v, u_count));
    }

    __inline static void SwapPointer(__UNIT_TYPE** u, __UNIT_TYPE** v)
    {
        __UNIT_TYPE* t = *u;
        *u = *v;
        *v = t;
    }

    static NUMBER_HEADER* Remainder(NUMBER_HEADER* u, NUMBER_HEADER* v)
    {
        //Lock lock_obj;
        if (u->UNIT_BIT_COUNT < v->UNIT_BIT_COUNT)
            return (DuplicateNumber(u));
        else
        {
            ResourceHolderUINT root;
            __UNIT_TYPE* work_v_buf = root.AllocateBlock(v->UNIT_BIT_COUNT);
            NUMBER_HEADER* r = root.AllocateNumber(u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT);
            if (u->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
                _COPY_MEMORY_UNIT(r->BLOCK, u->BLOCK, u->UNIT_WORD_COUNT);
            else
            {
                DivRem_X_X(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, work_v_buf, nullptr, r->BLOCK);
                root.CheckBlock(work_v_buf);
                root.CheckNumber(r);
            }
            root.DeallocateBlock(work_v_buf);
            CommitNumber(r);
            root.UnlinkNumber(r);
            return (r);
        }
    }

    LONG exception_filter(DWORD code)
    {
        if (code == EXCEPTION_ACCESS_VIOLATION)
            return (EXCEPTION_EXECUTE_HANDLER);
        else
            return (EXCEPTION_CONTINUE_SEARCH);
    }

    static NUMBER_HEADER* ModulePower(NUMBER_HEADER* v, NUMBER_HEADER* e, NUMBER_HEADER* m)
    {
        //Lock lock_obj;
        ResourceHolderUINT root;

        __UNIT_TYPE* m_buf = m->BLOCK;
        __UNIT_TYPE m_count = m->UNIT_WORD_COUNT;

        // 作業域を獲得する

        __UNIT_TYPE v_2_bit_count = v->UNIT_WORD_COUNT * __UNIT_TYPE_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE* v_2_buf = root.AllocateBlock(v_2_bit_count);
        __UNIT_TYPE work_1_bit_count = m_count * 2 * __UNIT_TYPE_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE* work_1_buf = root.AllocateBlock(work_1_bit_count);
        __UNIT_TYPE work_2_bit_count = m_count * 2 * __UNIT_TYPE_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE* work_2_buf = root.AllocateBlock(work_2_bit_count);
        __UNIT_TYPE work_v_bit_count = m_count * __UNIT_TYPE_BIT_COUNT;
        __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_v_bit_count);
        __UNIT_TYPE r_bit_count = m->UNIT_BIT_COUNT;
        NUMBER_HEADER* r = root.AllocateNumber(r_bit_count);

        __UNIT_TYPE v_count;
        int cmp = Compare_Easy(v->BLOCK, v->UNIT_WORD_COUNT, m_buf, m_count);
        if (cmp == 0)
        {
            // v == m である場合

            // v を何乗してもその剰余は 0 であるため、0 を返す。
            return (&number_zero);
        }
        else if (cmp > 0)
        {
            // v > m である場合

            // v2 を v % m に設定する。

            DivRem_X_X(v->BLOCK, v->UNIT_WORD_COUNT, m_buf, m_count, work_v_buf, nullptr, v_2_buf);
            root.CheckBlock(work_v_buf);
            root.CheckBlock(v_2_buf);
            v_count = m_count;
            while (v_count > 0 && v_2_buf[v_count - 1] == 0)
                --v_count;

            if (v_count <= 0)
            {
                // v2 が 0 になってしまった場合はべき乗を繰り返しても 0 になることが確定なので 0 を返す
                return (&number_zero);
            }
        }
        else
        {
            // v2 を v に設定する。

            _COPY_MEMORY_UNIT(v_2_buf, v->BLOCK, v->UNIT_WORD_COUNT);
            v_count = v->UNIT_WORD_COUNT;
        }

        __UNIT_TYPE e_count = e->UNIT_WORD_COUNT;
        __UNIT_TYPE e_mask = ~((__UNIT_TYPE)-1 >> 1);
        e_mask = e_mask >> _LZCNT_ALT_UNIT(e->BLOCK[e_count - 1]);
        // e_mask は e の最上位 bit を示しているはず
        // かつ、e は 2以上であるので、同時に最下位 bit であることはあり得ない
        _COPY_MEMORY_UNIT(work_1_buf, v_2_buf, m_count);

#ifdef _DEBUG
        if ((e_mask & e->BLOCK[e_count - 1]) == 0)
            *((int*)0) = 0;
#endif

        __UNIT_TYPE* u_ptr = work_1_buf;
        __UNIT_TYPE* v_ptr = v_2_buf;
        __UNIT_TYPE* w_ptr = work_2_buf;
        __UNIT_TYPE u_count = v_count;

        while (e_count > 0)
        {
            //Lock lock_obj;

            // 次の桁の準備をする
            e_mask >>= 1;
            if (e_mask == 0)
            {
                e_mask = ~((__UNIT_TYPE)-1 >> 1);
                --e_count;
            }

            if (e_count <= 0)
                break;

            // w := u * u を計算する
            root.ClearBlock(w_ptr);
            {
                // ここの乗算をクリティカルセクションに含めることによりアクセス違反の頻度が大きく変わる模様
                //Lock lock_obj;
                Multiply_X_X_Imp(u_ptr, u_count, u_ptr, u_count, w_ptr);
            }
            root.CheckBlock(work_1_buf);
            root.CheckBlock(work_2_buf);
            SwapPointer(&u_ptr, &w_ptr);
            u_count *= 2;
            if (u_ptr[u_count - 1] == 0)
                --u_count;

            // w := u % m を計算する
            if (u_count >= m_count)
            {
                //Lock lock_obj;

                root.ClearBlock(work_v_buf);
                root.ClearBlock(w_ptr);
                DivRem_X_X(u_ptr, u_count, m_buf, m_count, work_v_buf, nullptr, w_ptr);
                root.CheckBlock(work_v_buf);
                root.CheckBlock(work_1_buf);
                root.CheckBlock(work_2_buf);
                SwapPointer(&u_ptr, &w_ptr);
                u_count = m_count;
                while (u_count > 0 && u_ptr[u_count - 1] == 0)
                    --u_count;

                if (u_count <= 0)
                {
                    // 剰余が 0 になった場合はこれ以上続行しても解が 0 以外にはならないので、処理を中断して 0 を返す
                    return (&number_zero);
                }
            }

            if (e_mask & e->BLOCK[e_count - 1])
            {
                // e の当該桁のビットが立っている場合

                //Lock lock_obj;

                // w := u * v を計算する
                root.ClearBlock(w_ptr);
                {
                    //Lock lock_obj;
                    Multiply_X_X_Imp(u_ptr, u_count, v_ptr, v_count, w_ptr);
                }
                root.CheckBlock(work_1_buf);
                root.CheckBlock(work_2_buf);
                SwapPointer(&u_ptr, &w_ptr);
                u_count += v_count;
                if (u_ptr[u_count - 1] == 0)
                    --u_count;

                // w := u % m を計算する
                if (u_count >= m_count)
                {
                    root.ClearBlock(work_v_buf);
                    {
                        // このClearBlockをクリティカルセクションに含めるかどうかでアクセス違反の頻度が大きく変わる
                        //Lock lock_obj;
                        root.ClearBlock(w_ptr);
                    }
                    {
                        // この除算をクリティカルセクションに含めるかどうかでアクセス違反の頻度が大きく変わる
                        //Lock lock_obj;
                        DivRem_X_X(u_ptr, u_count, m_buf, m_count, work_v_buf, nullptr, w_ptr);
                    }
                    root.CheckBlock(work_v_buf);
                    root.CheckBlock(work_1_buf);
                    root.CheckBlock(work_2_buf);
                    SwapPointer(&u_ptr, &w_ptr);
                    u_count = m_count;
                    while (u_count > 0 && u_ptr[u_count - 1] == 0)
                        --u_count;
                    if (u_count <= 0)
                    {
                        // 剰余が 0 になった場合はこれ以上続行しても解が 0 以外にはならないので、処理を中断して 0 を返す
                        return (&number_zero);
                    }
                }
            }
        }

        // 最下位桁まで達したので u_ptr と u_count を解として帰る
        _COPY_MEMORY_UNIT(r->BLOCK, u_ptr, u_count);
        root.CheckNumber(r);
        CommitNumber(r);
        root.UnlinkNumber(r);
        return (r);
    }

    static NUMBER_HEADER* PMC_ModPow_X_X_X_Imp(NUMBER_HEADER* v, NUMBER_HEADER* e, NUMBER_HEADER* m)
    {
        //Lock lock_obj;
        if (m->IS_ZERO)
        {
            // m が 0 の場合

            // 0 による除算は許されないのでエラーを通知する
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        else if (m->IS_ONE)
        {
            // m が 1 の場合
            if (v->IS_ZERO)
            {
                // v が 0 の場合
                if (e->IS_ZERO)
                {
                    // e が 0 の場合

                    // 0 の 0 乗となるので、エラーを返す
                    throw ArithmeticException(L"0の0乗の値は未定義です。");
                }
                else
                {
                    // e が 0 ではない場合

                    // v の e 乗がどんな値であっても 1 では必ず割り切れるので剰余は 0 となる。
                    return (&number_zero);
                }
            }
            else
            {
                // v が 0 ではない場合

                // v の e 乗がどんな値であっても 1 では必ず割り切れるので剰余は 0 となる。
                return (&number_zero);
            }
        }
        else
        {
            // m が 2 以上の場合
            if (v->IS_ZERO)
            {
                // v が 0 の場合
                if (e->IS_ZERO)
                {
                    // e が 0 の場合

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
                // v が 1 の場合

                // 1 を何乗しても 1 であり、1 を 2 以上の数で割ればその剰余は必ず 1 となる
                return (&number_one);
            }
            else
            {
                // v が 2 以上の場合
                if (e->IS_ZERO)
                {
                    // e が 0 の場合
                    return (&number_one);
                }
                else if (e->IS_ONE)
                {
                    // e が 1 の場合

                    // v % m を計算して返す
                    return (Remainder(v, m));
                }
                else
                {
                    // v、e、m がすべて 2 以上である場合
                    // v の e 乗 の m による剰余を計算して返す
                    return (ModulePower(v, e, m));
                }
            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_ModPow_X_X_X(PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false)
    {
        //Lock lock_obj;
        if (v == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"v");
        if (e == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"e");
        if (m == nullptr)
            throw ArgumentNullException(L"引数にnullptrが与えられています。", L"m");
        CheckNumber((NUMBER_HEADER*)v);
        CheckNumber((NUMBER_HEADER*)e);
        CheckNumber((NUMBER_HEADER*)m);
        ResourceHolderUINT root;
        NUMBER_HEADER* r = PMC_ModPow_X_X_X_Imp((NUMBER_HEADER*)v, (NUMBER_HEADER*)e, (NUMBER_HEADER*)m);
        root.HookNumber(r);
#ifdef _DEBUG
        CheckNumber(r);
#endif
        root.UnlinkNumber(r);
        return ((PMC_HANDLE_UINT)r);
    }

    PMC_STATUS_CODE Initialize_ModPow(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */