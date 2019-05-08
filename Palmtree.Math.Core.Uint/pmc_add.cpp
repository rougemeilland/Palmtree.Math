﻿/*
 * The MIT License
 *
 * Copyright 2018 Palmtree Software.
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
#include "autogenerated_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static void DoCarry(char c, __UNIT_TYPE* u_ptr, __UNIT_TYPE u_count, __UNIT_TYPE* w_ptr, __UNIT_TYPE w_count)
    {
        // 繰り上がりを続く限り行う
        for (;;)
        {
            if (u_count <= 0)
            {
                // u の最上位まで達してしまった場合

                if (c)
                {
                    // かつそれでも繰り上がりを行う必要がある場合
                    if (w_count <= 0)
                    {
                        // しかし w がもう終端に達してしまった場合

                        // w のバッファはこの余裕を見込んでいるのでこのルートには到達しないはず。
                        throw InternalErrorException(L"内部エラーが発生しました。", L"pcm_add.cpp;DoCarry;1");
                    }
                    *w_ptr++ = 1;
                    --w_count;
                }

                // u の最上位に達してしまった場合はいずれにしろループを中断して正常復帰する。
                break;
            }
            else if (c)
            {
                // u の最上位に達しておらず、かつキャリーが立っている場合

                // 繰り上がりを継続する
                c = _ADD_UNIT(c, *u_ptr++, 0, w_ptr++);
                --u_count;
                --w_count;
            }
            else
            {
                // u の最上位に達しておらず、かつキャリーが立っていない場合

                // 繰り上がりを中断し、u の残りのデータを z にそのまま複写し、正常復帰する。
                _COPY_MEMORY_UNIT(w_ptr, u_ptr, u_count);
                w_ptr += u_count;
                u_ptr += u_count;
                w_count -= u_count;
                u_count = 0;
                break;
            }
        }
        _ZERO_MEMORY_UNIT(w_ptr, w_count);
    }


    static void Add_UX_1W(__UNIT_TYPE* u_ptr, __UNIT_TYPE u_count, __UNIT_TYPE v, __UNIT_TYPE* w_ptr, __UNIT_TYPE w_count)
    {
#ifdef _DEBUG
        if (u_count < 1)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;1");
        if (w_count < u_count)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;2");
        if (w_count < 1)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;3");
#endif
        char c;

        // 最下桁の加算を行う
        c = _ADD_UNIT(0, *u_ptr++, v, w_ptr++);
        --u_count;
        --w_count;

        // 残りの桁の繰上りを行い復帰する。
        DoCarry(c, u_ptr, u_count, w_ptr, w_count);
    }

    static void Add_UX_2W(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE v_hi, __UNIT_TYPE v_lo, __UNIT_TYPE* w_buf, __UNIT_TYPE w_count)
    {
#ifdef _DEBUG
        if (u_count < 1)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;1");
        if (w_count < u_count)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;2");
        if (w_count < 2)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;3");
#endif
        __UNIT_TYPE* up = u_buf;
        __UNIT_TYPE* wp = w_buf;
        char c;

        if (u_count < 2)
        {
            // u が 1 ワードしかなかった場合

            // 最下位ワードの加算を行う
            c = _ADD_UNIT(0, up[0], v_lo, &wp[0]);

            // 最下位から 2 番目のワードの加算を行う
            c = _ADD_UNIT(c, 0, v_hi, &wp[1]);

            // 桁上りが発生したら 3 番目のワードに 1 を設定する。
            if (c && w_count >= 3)
            {
                wp[2] = 1;
                _ZERO_MEMORY_UNIT(w_buf + 3, w_count - 3);
            }
            else
            {
                _ZERO_MEMORY_UNIT(w_buf + 2, w_count - 2);
            }
        }
        else
        {
            // u が 2 ワード以上あった場合

            // 最下位のワードの加算をする
            c = _ADD_UNIT(0, *up++, v_lo, wp++);

            // 最下位から 2 番目のワードの加算をする。
            c = _ADD_UNIT(c, *up++, v_hi, wp++);
            u_count -= 2;
            w_count -= 2;

            // 残りの桁の繰り上がりを計算し、復帰する。
            DoCarry(c, up, u_count, wp, w_count);
        }
    }

    // 加算の実装。u のワード数は v のワード数より小さくてはならない。
    static void Add_Imp(__UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* w_buf, __UNIT_TYPE w_count)
    {
        // u のワード長が v のワード長以上であるようにする
        if (u_count < v_count)
        {
            __UNIT_TYPE* t_buf = u_buf;
            u_buf = v_buf;
            v_buf = t_buf;
            __UNIT_TYPE t_count = u_count;
            u_count = v_count;
            v_count = t_count;
        }

#ifdef _DEBUG
        if (u_count < v_count)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;1");
        if (w_count < u_count)
            throw InternalErrorException(L"予期しないルートに到達しました。", L"pmc_add.cpp;Add_Imp;2");
#endif

        __UNIT_TYPE* up = u_buf;
        __UNIT_TYPE* vp = v_buf;
        __UNIT_TYPE* wp = w_buf;
        char c = 0;

        // まず 32 ワードずつ加算をする。
        __UNIT_TYPE count = v_count >> 5;
        while (count != 0)
        {
            c = _ADD_32WORDS_ADC(c, up, vp, wp);
            up += 32;
            vp += 32;
            wp += 32;
            --count;
        }
        // この時点で未処理の桁は 32 ワード未満のはず

        // 未処理の桁が 16 ワード以上あるなら 16 ワード加算を行う。
        if (v_count & 0x10)
        {
            c = _ADD_16WORDS_ADC(c, up, vp, wp);
            up += 16;
            vp += 16;
            wp += 16;
        }
        // この時点で未処理の桁は 16 ワード未満のはず

        // 未処理の桁が 8 ワード以上あるなら 8 ワード加算を行う。
        if (v_count & 0x8)
        {
            c = _ADD_8WORDS_ADC(c, up, vp, wp);
            up += 8;
            vp += 8;
            wp += 8;
        }
        // この時点で未処理の桁は 8 ワード未満のはず

        // 未処理の桁が 4 ワード以上あるなら 4 ワード加算を行う。
        if (v_count & 0x4)
        {
            c = _ADD_4WORDS_ADC(c, up, vp, wp);
            up += 4;
            vp += 4;
            wp += 4;
        }
        // この時点で未処理の桁は 4 ワード未満のはず

        // 未処理の桁が 2 ワード以上あるなら 2 ワード加算を行う。
        if (v_count & 0x2)
        {
            c = _ADD_2WORDS_ADC(c, up, vp, wp);
            up += 2;
            vp += 2;
            wp += 2;
        }
        // この時点で未処理の桁は 2 ワード未満のはず

        // 未処理の桁が 1 ワード以上あるなら 1 ワード加算を行う。
        if (v_count & 0x1)
            c = _ADD_UNIT(c, *up++, *vp++, wp++);

        // 残りの桁の繰り上がりを計算し、復帰する。
        DoCarry(c, up, u_count - v_count, wp, w_count - v_count);
    }

    NUMBER_OBJECT_UINT* PMC_Increment_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* x)
    {
        if (x->IS_ZERO)
        {
            // x が 0 である場合

            // 1 を返す
            return (&number_object_uint_one);
        }
        else
        {
            // x が 0 ではない場合

            // x + 1 を計算する

            ResourceHolderUINT root(tc);
            __UNIT_TYPE x_bit_count = x->UNIT_BIT_COUNT;
            __UNIT_TYPE w_bit_count = x_bit_count + 1;
            NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
            DoCarry(1, x->BLOCK, x->UNIT_WORD_COUNT, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
            root.CheckNumber(w);
#endif
            CommitNumber(tc, w);
            root.UnlinkNumber(w);
            return (w);
        }
    }

    PMC_HANDLE_UINT PMC_Increment_UX(ThreadContext& tc, PMC_HANDLE_UINT x)
    {
        NUMBER_OBJECT_UINT* nx = GET_NUMBER_OBJECT(x, L"x");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Increment_UX_Imp(tc, nx);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_Add_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            if (v == 0)
            {
                // y が 0 である場合

                // x と y がともに 0 であるので、加算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // y が 0 ではない場合

                // 加算結果となる y の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UI_Imp(tc, v));
            }
        }
        else
        {
            // x が 0 ではない場合

            if (v == 0)
            {
                // y が 0 である場合

                // 加算結果となる x の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // x と y がともに 0 ではない場合

                // x と y の和を計算する
                ResourceHolderUINT root(tc);
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
                __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count) + 1;
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                Add_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Add_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(u) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw =  PMC_Add_UX_UI_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Add_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT < sizeof(v) * 8)
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    static NUMBER_OBJECT_UINT* PMC_Add_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            if (v == 0)
            {
                // v が 0 である場合

                // u と v がともに 0 であるので、加算結果の 0 を呼び出し元に返す。
                return (&number_object_uint_zero);
            }
            else
            {
                // v が 0 ではない場合

                // 加算結果となる v の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (From_UL_Imp(tc, v));
            }
        }
        else
        {
            // u が 0 ではない場合

            if (v == 0)
            {
                // v が 0 である場合

                // 加算結果となる u の値を持つ NUMBER_OBJECT_UINT 構造体を獲得し、呼び出し元へ返す。
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // u と v の和を計算する
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
                        __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                        __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count) + 1;
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                        Add_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, v_lo, w->BLOCK, w->BLOCK_COUNT);
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
                        __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                        __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count) + 1;
                        NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                        Add_UX_2W(u->BLOCK, u->UNIT_WORD_COUNT, v_hi, v_lo, w->BLOCK, w->BLOCK_COUNT);
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
                    __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                    __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count) + 1;
                    NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                    Add_UX_1W(u->BLOCK, u->UNIT_WORD_COUNT, (__UNIT_TYPE)v, w->BLOCK, w->BLOCK_COUNT);
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

    PMC_HANDLE_UINT PMC_Add_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(u) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UL_Imp(tc, nv, u);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_HANDLE_UINT PMC_Add_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v)
    {
        if (__UNIT_TYPE_BIT_COUNT * 2 < sizeof(v) * 8)
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_add.cpp;PMC_Add_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    NUMBER_OBJECT_UINT* PMC_Add_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            if (v->IS_ZERO)
                return (&number_object_uint_zero);
            else
                return (DuplicateNumber(tc, v));
        }
        else
        {
            if (v->IS_ZERO)
                return (DuplicateNumber(tc, u));
            else
            {
                ResourceHolderUINT root(tc);
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                __UNIT_TYPE w_bit_count = _MAXIMUM_UNIT(u_bit_count, v_bit_count) + 1;
                NUMBER_OBJECT_UINT* w = root.AllocateNumber(w_bit_count);
                Add_Imp(u->BLOCK, u->UNIT_WORD_COUNT, v->BLOCK, v->UNIT_WORD_COUNT, w->BLOCK, w->BLOCK_COUNT);
#ifdef _DEBUG
                root.CheckNumber(w);
#endif
                CommitNumber(tc, w);
                root.UnlinkNumber(w);
                return (w);
            }
        }
    }

    PMC_HANDLE_UINT PMC_Add_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nw = PMC_Add_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nw);
        PMC_HANDLE_UINT w = GET_NUMBER_HANDLE(nw);
        root.UnlinkNumber(nw);
        return (w);
    }

    PMC_STATUS_CODE Initialize_Add(PROCESSOR_FEATURES* feature)
    {
        return (PMC_STATUS_OK);
    }

}


/*
 * END OF FILE
 */