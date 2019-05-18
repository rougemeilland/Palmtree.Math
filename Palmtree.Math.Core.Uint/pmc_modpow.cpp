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

#include "pmc_resourceholder_uint.h"
#include "pmc_uint_internal.h"
#include "pmc_basic.h"
#include "pmc_inline_func.h"

namespace Palmtree::Math::Core::Internal
{

    __inline static void SwapPointer(_UBASIC_T** u, _UBASIC_T** v)
    {
        _UBASIC_T* t = *u;
        *u = *v;
        *v = t;
    }

    static NUMBER_OBJECT_UINT* Remainder(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->UNIT_WORD_COUNT < v->UNIT_WORD_COUNT)
            return (DuplicateNumber(tc, u));
        else
        {
            ResourceHolderUINT root(tc);
            _UBASIC_T work_v_buf = root.AllocateBlock(v->UNIT_WORD_COUNT);
            NUMBER_OBJECT_UINT* r = root.AllocateNumber(u->UNIT_WORD_COUNT + 1);

            basic_ep.Remainder(_UBASIC_T(u), _UBASIC_T(v), work_v_buf, _UBASIC_T(r));
#ifdef _DEBUG
            root.CheckBlock(work_v_buf);
            root.CheckNumber(r);
#endif
            CommitNumber(tc, r);
            if (r->IS_ZERO)
            {
                root.DeallocateNumber(r);
                r = &number_object_uint_zero;
            }
            else
                root.UnlinkNumber(r);
            return (r);
        }
    }

    static NUMBER_OBJECT_UINT* ModulePower(ThreadContext& tc, NUMBER_OBJECT_UINT* v, NUMBER_OBJECT_UINT* e, NUMBER_OBJECT_UINT* m)
    {
        ResourceHolderUINT root(tc);

        _UBASIC_T m_buf(m);

        // 作業域を獲得する
        _UBASIC_T _v_2_buf = root.AllocateBlock(v->UNIT_WORD_COUNT + 1);
        _UBASIC_T work_1_buf = root.AllocateBlock(m_buf.BLOCK_COUNT * 2 + 1);
        _UBASIC_T work_2_buf = root.AllocateBlock(m_buf.BLOCK_COUNT * 2 + 1);
        _UBASIC_T work_v_buf = root.AllocateBlock(m_buf.BLOCK_COUNT);
        NUMBER_OBJECT_UINT* r = root.AllocateNumber(m_buf.BLOCK_COUNT);

        int cmp = basic_ep.Compare(_UBASIC_T(v), _UBASIC_T(m));
        if (cmp == 0)
        {
            // v == m である場合

            // v を何乗してもその剰余は 0 であるため、0 を返す。
            return (&number_object_uint_zero);
        }
        else if (cmp > 0)
        {
            // v > m である場合

            // v2 を v % m に設定する。

            basic_ep.Remainder(_UBASIC_T(v), m_buf, work_v_buf, _v_2_buf);
#ifdef _DEBUG
            root.CheckBlock(work_v_buf);
            root.CheckBlock(_v_2_buf);
#endif
        }
        else
        {
            // v2 を v に設定する。

            _v_2_buf.CopyFrom(_UBASIC_T(v));
        }

        _UBASIC_T v_2_buf = _v_2_buf.Shrink();

        if (v_2_buf.BLOCK_COUNT == 0)
        {
            // v2 が 0 になってしまった場合はべき乗を繰り返しても 0 になることが確定なので 0 を返す
            return (&number_object_uint_zero);
        }

        __UNIT_TYPE e_count = e->UNIT_WORD_COUNT;
        __UNIT_TYPE e_mask = ~((__UNIT_TYPE)-1 >> 1);
        e_mask = e_mask >> _LZCNT_ALT_UNIT(e->BLOCK[e_count - 1]);
        
        // e_mask は e の最上位 bit を示しているはず
        // かつ、e は 2以上であるので、同時に最下位 bit であることはあり得ない

        work_1_buf.CopyFrom(v_2_buf);
        _UBASIC_T* u_ptr = &work_1_buf;
        _UBASIC_T* w_ptr = &work_2_buf;
        __UNIT_TYPE u_count = v_2_buf.BLOCK_COUNT;

        while (e_count > 0)
        {
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
            basic_ep.Multiply(tc, PMC_MULTIPLICATION_METHOD_AUTO, u_ptr->Region(0, u_count), u_ptr->Region(0, u_count), *w_ptr);
#ifdef _DEBUG
            root.CheckBlock(*w_ptr);
#endif
            SwapPointer(&u_ptr, &w_ptr);
            u_count *= 2;
            while (u_ptr->BLOCK[u_count - 1] == 0)
                --u_count;

            // w := u % m を計算する
            if (u_count >= m_buf.BLOCK_COUNT)
            {
                basic_ep.Remainder(u_ptr->Region(0, u_count), m_buf, work_v_buf, *w_ptr);
#ifdef _DEBUG
                root.CheckBlock(work_v_buf);
                root.CheckBlock(*w_ptr);
#endif
                SwapPointer(&u_ptr, &w_ptr);
                u_count = m_buf.BLOCK_COUNT;
                while (u_ptr->BLOCK[u_count - 1] == 0)
                    --u_count;

                if (u_count <= 0)
                {
                    // 剰余が 0 になった場合はこれ以上続行しても解が 0 以外にはならないので、処理を中断して 0 を返す
                    return (&number_object_uint_zero);
                }
            }

            if (e_mask & e->BLOCK[e_count - 1])
            {
                // e の当該桁のビットが立っている場合

                // w := u * v を計算する
                basic_ep.Multiply(tc, PMC_MULTIPLICATION_METHOD_AUTO, u_ptr->Region(0, u_count), v_2_buf, *w_ptr);
#ifdef _DEBUG
                root.CheckBlock(*w_ptr);
#endif
                SwapPointer(&u_ptr, &w_ptr);
                u_count += v_2_buf.BLOCK_COUNT;
                while (u_ptr->BLOCK[u_count - 1] == 0)
                    --u_count;

                // w := u % m を計算する
                if (u_count >= m_buf.BLOCK_COUNT)
                {
                    basic_ep.Remainder(u_ptr->Region(0, u_count), m_buf, work_v_buf, *w_ptr);
#ifdef _DEBUG
                    root.CheckBlock(work_v_buf);
                    root.CheckBlock(*w_ptr);
#endif
                    SwapPointer(&u_ptr, &w_ptr);
                    u_count = m_buf.BLOCK_COUNT;
                    while (u_ptr->BLOCK[u_count - 1] == 0)
                        --u_count;

                    if (u_count <= 0)
                    {
                        // 剰余が 0 になった場合はこれ以上続行しても解が 0 以外にはならないので、処理を中断して 0 を返す
                        return (&number_object_uint_zero);
                    }
                }
            }
        }

        // 最下位桁まで達したので u_ptr と u_count を解として帰る
        _UBASIC_T(r).CopyFrom(u_ptr->Region(0, u_count));
#ifdef _DEBUG
        root.CheckNumber(r);
#endif
        CommitNumber(tc, r);
        if (r->IS_ZERO)
        {
            root.DeallocateNumber(r);
            r = &number_object_uint_zero;
        }
        else
            root.UnlinkNumber(r);
        return (r);
    }

    static NUMBER_OBJECT_UINT* PMC_ModPow_UX_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* v, NUMBER_OBJECT_UINT* e, NUMBER_OBJECT_UINT* m)
    {
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
                    return (&number_object_uint_zero);
                }
            }
            else
            {
                // v が 0 ではない場合

                // v の e 乗がどんな値であっても 1 では必ず割り切れるので剰余は 0 となる。
                return (&number_object_uint_zero);
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

                    return (&number_object_uint_zero);
                }
            }
            else if (v->IS_ONE)
            {
                // v が 1 の場合

                // 1 を何乗しても 1 であり、1 を 2 以上の数で割ればその剰余は必ず 1 となる
                return (&number_object_uint_one);
            }
            else
            {
                // v が 2 以上の場合
                if (e->IS_ZERO)
                {
                    // e が 0 の場合
                    return (&number_object_uint_one);
                }
                else if (e->IS_ONE)
                {
                    // e が 1 の場合

                    // v % m を計算して返す
                    return (Remainder(tc, v, m));
                }
                else
                {
                    // v、e、m がすべて 2 以上である場合
                    // v の e 乗 の m による剰余を計算して返す
                    return (ModulePower(tc, v, e, m));
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_ModPow_UX_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT v, PMC_HANDLE_UINT e, PMC_HANDLE_UINT m) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        NUMBER_OBJECT_UINT* ne = GET_NUMBER_OBJECT(e, L"e");
        NUMBER_OBJECT_UINT* nm = GET_NUMBER_OBJECT(m, L"m");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nr = PMC_ModPow_UX_UX_UX_Imp(tc, nv, ne, nm);
        root.HookNumber(nr);
        PMC_HANDLE_UINT r = GET_NUMBER_HANDLE(nr);
        root.UnlinkNumber(nr);
        return (r);
    }

    PMC_STATUS_CODE Initialize_ModPow(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */