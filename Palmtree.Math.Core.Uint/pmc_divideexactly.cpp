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
#include "pmc_inversetable.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static _BYTE_T inverse8_table[128] =
    {
        1, 171, 205, 183, 57, 163, 197, 239,
        241, 27, 61, 167, 41, 19, 53, 223,
        225, 139, 173, 151, 25, 131, 165, 207,
        209, 251, 29, 135, 9, 243, 21, 191,
        193, 107, 141, 119, 249, 99, 133, 175,
        177, 219, 253, 103, 233, 211, 245, 159,
        161, 75, 109, 87, 217, 67, 101, 143,
        145, 187, 221, 71, 201, 179, 213, 127,
        129, 43, 77, 55, 185, 35, 69, 111,
        113, 155, 189, 39, 169, 147, 181, 95,
        97, 11, 45, 23, 153, 3, 37, 79,
        81, 123, 157, 7, 137, 115, 149, 63,
        65, 235, 13, 247, 121, 227, 5, 47,
        49, 91, 125, 231, 105, 83, 117, 31,
        33, 203, 237, 215, 89, 195, 229, 15,
        17, 59, 93, 199, 73, 51, 85, 255,
    };

    static __UNIT_TYPE GetInverse(__UNIT_TYPE n)
    {
#ifdef _DEBUG
        if ((n & 1) == 0)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;GetInverse;1");
#endif
        _BYTE_T inverse8 = inverse8_table[(n >> 1) & 0x7f];
        _UINT16_T inverse16 = ((_UINT16_T)inverse8 << 1) - (_UINT16_T)inverse8 * inverse8 * (_UINT16_T)n;
#ifdef ENABLED_PERFORMANCE_COUNTER
        AddToDIV32Counter(2);
#endif
        _UINT32_T inverse32 = ((_UINT32_T)inverse16 << 1) - (_UINT32_T)inverse16 * inverse16 * (_UINT32_T)n;
#ifdef ENABLED_PERFORMANCE_COUNTER
        AddToDIV32Counter(2);
#endif
#ifdef _M_IX86
        return (inverse32);
#elif defined(_M_X64)
        _UINT64_T inverse64 = ((_UINT64_T)inverse32 << 1) - (_UINT64_T)inverse32 * inverse32 * (_UINT64_T)n;
#ifdef ENABLED_PERFORMANCE_COUNTER
        AddToDIV64Counter(2);
#endif
        return (inverse64);
#else
#error unknown platform
#endif
    }

    // 完全除算を行う。
    // u_buf の最上位ワードは必ず 0 でなければならない。
    static void DivideExactly_UNIT(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE* q_buf, __UNIT_TYPE q_buf_count)
    {
#ifdef _DEBUG
        if (u_buf[u_buf_count - 1] != 0)
        {
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;1");
        }
#endif
        while (u_buf_count >= 2 && u_buf[u_buf_count - 2] == 0)
            --u_buf_count;
        while (v_buf_count > 0 && v_buf[v_buf_count - 1] == 0)
            --v_buf_count;

        __UNIT_TYPE v0 = v_buf[0]; // 除数の最下位桁
        __UNIT_TYPE inverse_v0 = GetInverse(v0);; // 除数の最下位桁の逆元

        __UNIT_TYPE q_index = 0;
        while (u_buf_count > v_buf_count + q_index)
        {
            __UNIT_TYPE u0 = u_buf[q_index]; // 被除数の最下位桁
            __UNIT_TYPE temp;
            __UNIT_TYPE q0 = _MULTIPLY_UNIT(u0, inverse_v0, &temp); // 商の最下位桁 (乗算の桁あふれは無視する)
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(u0) == sizeof(_UINT64_T))
                IncrementMULTI64Counter();
            else
                IncrementMULTI32Counter();
#endif
            // 商と除数の積を被除数から引く
            if (MultiplySubtructArray_UNIT(u_buf, u_buf_count, v_buf, v_buf_count, q_index, q0))
            {
                // 桁借りが発生要因は u が v で割り切れないぐらい・・・のはず
                throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
            }

            // 商を q_buf に追加する
            q_buf[q_index] = q0;
            ++q_index;

        }

        // この時点で u_buf_count == v_buf_count + q_index であるが、u の最上位ワードが 0 かつ v の最上位ワードが 0 なので、これ以上は割れないため、除算は終了。

        // q_buf の余った領域を 0 クリアする
        _ZERO_MEMORY_UNIT(q_buf + q_index, q_buf_count - q_index);

        // u_buf の上位 v_buf_count 桁に 0 でないワードが存在すれば完全除算は失敗
        for (__UNIT_TYPE index = q_index; index < u_buf_count; ++index)
        {
            if (u_buf[index] != 0)
                throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
        }
    }

    static void DivideExactly_UNIT(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE u_tzcnt, __UNIT_TYPE* v_buf, __UNIT_TYPE v_buf_count, __UNIT_TYPE v_tzcnt, __UNIT_TYPE* work_u_buf, __UNIT_TYPE work_u_buf_count, __UNIT_TYPE* work_v_buf, __UNIT_TYPE work_v_buf_count, __UNIT_TYPE* q_buf, __UNIT_TYPE q_buf_count)
    {
        if (u_tzcnt < v_tzcnt)
        {
            // v は 2^v_tzcnt を因数として持つが、少なくとも u も 2^v_tzcnt で割り切れなければ完全除算の前提が崩れるので、u_tzcnt < v_tzcnt ならば例外とする
            throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
        }
#ifdef _DEBUG
        if (v_buf_count > u_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;1");
        if (work_u_buf_count < u_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;2");
        if (work_v_buf_count < v_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;2");
        if (q_buf_count < u_buf_count - v_buf_count + 2)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;3");
#endif
        if (v_tzcnt > 0)
        {
            // u と v が 2^v_tzcnt を共通因数として持つので、あらかじめ 2^v_tzcnt で u と v を割っておく
            RightShift_Imp(u_buf, u_buf_count, v_tzcnt, work_u_buf, true);
            RightShift_Imp(v_buf, v_buf_count, v_tzcnt, work_v_buf, true);
            _ZERO_MEMORY_UNIT(work_u_buf + u_buf_count, work_u_buf_count - u_buf_count);
            _ZERO_MEMORY_UNIT(work_v_buf + v_buf_count, work_v_buf_count - v_buf_count);
        }
        else
        {
            _COPY_MEMORY_UNIT(work_u_buf, u_buf, u_buf_count);
            _ZERO_MEMORY_UNIT(work_u_buf + u_buf_count, work_u_buf_count - u_buf_count);
            _COPY_MEMORY_UNIT(work_v_buf, v_buf, v_buf_count);
            _ZERO_MEMORY_UNIT(work_v_buf + v_buf_count, work_v_buf_count - v_buf_count);
        }
        DivideExactly_UNIT(work_u_buf, work_u_buf_count, work_v_buf, work_v_buf_count, q_buf, q_buf_count);
    }

    bool MultiplySubtructArray_3_UNIT(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_len, __UNIT_TYPE q_index, __UNIT_TYPE q_)
    {
        __UNIT_TYPE mul_hi = q_ >> (__UNIT_TYPE_BIT_COUNT - 1);
        __UNIT_TYPE mul_lo = q_ << 1;
        _ADD_UNIT(_ADD_UNIT(0, mul_lo, q_, &mul_lo), mul_hi, 0, &mul_hi);
        char c;
        c = _SUBTRUCT_UNIT(0, u_buf[q_index], mul_lo, &u_buf[q_index]);
        c = _SUBTRUCT_UNIT(c, u_buf[q_index + 1], mul_hi, &u_buf[q_index + 1]);

        return (DoBorrow_UNIT(c, u_buf + q_index + 2, u_buf_len - q_index - 2));
    }

    // 完全除算を行う。u が v で割り切れない場合の動作は未定義とする。(例外が起きるかもしれないし起きずに誤った値を返すかもしれない)
    static void DivideExactly_3_UNIT(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* q_buf, __UNIT_TYPE q_buf_count)
    {
        __UNIT_TYPE inverse_v0 = INVERSE_3_MOD_UNIT_TYPE; // 除数の最下位桁の逆元
        __UNIT_TYPE q_index = 0;
        while (u_buf_count > 1 + q_index)
        {
            // MultiplySubtructArray_3_UNITの過程にて、u_buf からの q_index + 2 桁の引き算が発生するので、 u_buf_count >= q_index + 2 である必要がある
            __UNIT_TYPE u0 = u_buf[q_index]; // 被除数の最下位桁
            __UNIT_TYPE temp;
            __UNIT_TYPE q0 = _MULTIPLY_UNIT(u0, inverse_v0, &temp); // 商の最下位桁
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(u0) == sizeof(_UINT64_T))
                IncrementMULTI64Counter();
            else
                IncrementMULTI32Counter();
#endif
            // 商と除数の積を被除数から引く
            if (MultiplySubtructArray_3_UNIT(u_buf, u_buf_count, q_index, q0))
            {
                // 桁借りが発生要因は u が v で割り切れないぐらい・・・のはず
                throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
            }
            q_buf[q_index] = q0;
            ++q_index;
        }
        // この時点で u_buf_count == 1 + q_index のはず
        {
            __UNIT_TYPE u0 = u_buf[q_index]; // 被除数の最下位桁
            __UNIT_TYPE r;
            __UNIT_TYPE q0 = _DIVREM_UNIT(0, u0, 3, &r); // 商の最下位桁
#ifdef ENABLED_PERFORMANCE_COUNTER
            if (sizeof(u0) == sizeof(_UINT64_T))
                IncrementDIV64Counter();
            else
                IncrementDIV32Counter();
#endif
            if (r != 0)
                throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");

            q_buf[q_index] = q0;
            ++q_index;
        }

        // q_buf の余りを 0 クリアする
        _ZERO_MEMORY_UNIT(q_buf + q_index, q_buf_count - q_index);
    }

    static void DivideExactly_UNIT_3(__UNIT_TYPE* u_buf, __UNIT_TYPE u_buf_count, __UNIT_TYPE* work_u_buf, __UNIT_TYPE work_u_buf_count, __UNIT_TYPE* q_buf, __UNIT_TYPE q_buf_count)
    {
#ifdef _DEBUG
        if (work_u_buf_count < u_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;2");
        if (q_buf_count < u_buf_count)
            throw InternalErrorException(L"内部エラーが発生しました。", L"pmc_divideexactly.cpp;DivideExactly;3");
#endif
        _COPY_MEMORY_UNIT(work_u_buf, u_buf, u_buf_count);
        _ZERO_MEMORY_UNIT(work_u_buf + u_buf_count, work_u_buf_count - u_buf_count);
        DivideExactly_3_UNIT(work_u_buf, work_u_buf_count, q_buf, q_buf_count);
    }

    static _UINT32_T PMC_DivideExactly_UI_UX_Imp(ThreadContext& tc, _UINT32_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // u が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u と v がともに 0 ではない場合

                // x と y の商・剰余を計算する
                __UNIT_TYPE u_bit_count = sizeof(u) * 8 - _LZCNT_ALT_32(u);
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                if (u_bit_count < v_bit_count)
                {
                    // 明らかに u < v である場合

                    // 割り切れないので例外を通知する
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else
                {
                    // u のビット数が v のビット数以上である場合

                    // u は 1 ワードで表現できるので、v も 1 ワードで表現できる。
                    __UNIT_TYPE temp_r;
                    __UNIT_TYPE temp_q = _DIVREM_UNIT(0, u, v->BLOCK[0], &temp_r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(u) == sizeof(_UINT64_T))
                        IncrementDIV64Counter();
                    else
                        IncrementDIV32Counter();
#endif
                    if (temp_r != 0)
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    return ((_UINT32_T)temp_q);
                }
            }
        }
    }

    _UINT32_T PMC_DivideExactly_UI_UX(ThreadContext& tc, _UINT32_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(u))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UI_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivideExactly_UI_UX_Imp(tc, u, nv));
    }

    static NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UI_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT32_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u と v がともに 0 ではない場合

                // x と y の商・剰余を計算する
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v);
                if (u_bit_count < v_bit_count)
                {
                    // 明らかに u < v である場合

                    // 割り切れないので例外を通知する
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else if (v == 3)
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT;
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);
                    __UNIT_TYPE q_bit_count = u->UNIT_BIT_COUNT;
                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                    DivideExactly_UNIT_3(u->BLOCK, u->UNIT_WORD_COUNT,
                                         work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                         q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);

                    __UNIT_TYPE v_buf[] = { v };
                    __UNIT_TYPE work_v_buf[countof(v_buf)];

                    __UNIT_TYPE q_bit_count = (u->UNIT_WORD_COUNT - countof(v_buf) + 2) * __UNIT_TYPE_BIT_COUNT;
                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                    DivideExactly_UNIT(u->BLOCK, u->UNIT_WORD_COUNT, u->TRAILING_ZERO_BITS_COUNT,
                                       v_buf, countof(v_buf), _TZCNT_ALT_UNIT(v),
                                       work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                       work_v_buf, countof(work_v_buf),
                                       q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UI(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT32_T v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) < sizeof(v))
        {
            // _UINT32_T が 1 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UX_I;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UI_Imp(tc, nu, v);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

#ifdef _M_IX86
    static _UINT64_T PMC_DivideExactly_UL_UX_Imp(ThreadContext& tc, _UINT64_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // x が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                _UINT32_T u_hi;
                _UINT32_T u_lo = _FROMDWORDTOWORD(u, &u_hi);
                if (u_hi == 0)
                {
                    // u の値が 32bit で表現可能な場合
                    __UNIT_TYPE u_bit_count = sizeof(u_lo) * 8 - _LZCNT_ALT_32(u_lo);
                    __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                    if (u_bit_count < v_bit_count)
                    {
                        // 明らかに u < v である場合

                        // 割り切れないので例外を通知する
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    }
                    else
                    {
                        // u のビット数が v のビット数以上である場合

                        // u は 32bit で表現できるので、v も 32bit で表現できる。
                        __UNIT_TYPE temp_r;
                        __UNIT_TYPE temp_q = _DIVREM_UNIT(0, u_lo, v->BLOCK[0], &temp_r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                        if (sizeof(u) == sizeof(_UINT64_T))
                            IncrementDIV64Counter();
                        else
                            IncrementDIV32Counter();
#endif
                        if (temp_r != 0)
                            throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                        return ((_UINT32_T)temp_q);
                    }
                }
                else
                {
                    // v の値が 32bit では表現できない場合
                    __UNIT_TYPE u_bit_count = sizeof(u) * 8 - _LZCNT_ALT_32(u_hi);
                    __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                    if (u_bit_count < v_bit_count)
                    {
                        // 明らかに u < v である場合

                        // 割り切れないので例外を通知する
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    }
                    else
                    {
                        // u のビット長が 33 以上 64 以下であり、かつ、u のビット長が v のビット長以上(v のビット長は多くとも64以下)である場合


                        ResourceHolderUINT root(tc);

                        __UNIT_TYPE u_buf[] = { u_lo, u_hi };
                        __UNIT_TYPE work_u_buf[countof(u_buf) + 1];
                        __UNIT_TYPE u_tzcnt = u_lo == 0 ? sizeof(u_lo) * 8 + _TZCNT_ALT_UNIT(u_hi) : _TZCNT_ALT_UNIT(u_lo);

                        __UNIT_TYPE work_v_bit_count = v_bit_count;
                        __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_v_bit_count);

                        __UNIT_TYPE q_bit_count = (countof(u_buf) - v->UNIT_WORD_COUNT + 2) * __UNIT_TYPE_BIT_COUNT;
                        __UNIT_TYPE* q_buf = root.AllocateBlock(q_bit_count);

                        DivideExactly_UNIT(u_buf, countof(u_buf), u_tzcnt,
                                           v->BLOCK, v->UNIT_WORD_COUNT, v->TRAILING_ZERO_BITS_COUNT,
                                           work_u_buf, countof(work_u_buf),
                                           work_v_buf, _DIVIDE_CEILING_UNIT(work_v_bit_count, __UNIT_TYPE_BIT_COUNT),
                                           q_buf, _DIVIDE_CEILING_UNIT(q_bit_count, __UNIT_TYPE_BIT_COUNT));
#ifdef _DEBUG
                        root.CheckBlock(work_v_buf);
                        root.CheckBlock(q_buf);
#endif
                        return (_FROMWORDTODWORD(q_buf[1], q_buf[0]));
                    }
                }
            }
        }
    }
#elif defined(_M_X64)
    static _UINT64_T PMC_DivideExactly_UL_UX_Imp(ThreadContext& tc, _UINT64_T u, NUMBER_OBJECT_UINT* v) noexcept(false)
    {
        if (v->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u == 0)
        {
            // x が 0 である場合

            // 0 を返す
            return (0);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (u);
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                __UNIT_TYPE u_bit_count = sizeof(u) * 8 - _LZCNT_ALT_UNIT(u);
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                if (u_bit_count < v_bit_count)
                {
                    // 明らかに u < v である場合

                    // 割り切れないので例外を通知する
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else
                {
                    // u のビット数が v のビット数以上である場合

                    // u は 1 ワードで表現できるので、v も 1 ワードで表現できる。
                    __UNIT_TYPE temp_r;
                    __UNIT_TYPE temp_q = _DIVREM_UNIT(0, u, v->BLOCK[0], &temp_r);
#ifdef ENABLED_PERFORMANCE_COUNTER
                    if (sizeof(u) == sizeof(_UINT64_T))
                        IncrementDIV64Counter();
                    else
                        IncrementDIV32Counter();
#endif
                    if (temp_r != 0)
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    return (temp_q);
                }
            }
        }
    }
#else
#error unknown platform
#endif

    _UINT64_T PMC_DivideExactly_UL_UX(ThreadContext& tc, _UINT64_T u, PMC_HANDLE_UINT v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(u))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UL_UX;1");
        }
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        return (PMC_DivideExactly_UL_UX_Imp(tc, u, nv));
    }

#ifdef _M_IX86
    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                _UINT32_T v_hi;
                _UINT32_T v_lo = _FROMDWORDTOWORD(v, &v_hi);
                if (v_hi == 0)
                {
                    // v の値が 32bit で表現可能な場合
                    __UNIT_TYPE v_bit_count = sizeof(v_lo) * 8 - _LZCNT_ALT_32(v_lo);
                    if (u_bit_count < v_bit_count)
                    {
                        // 明らかに u < v である場合

                        // 割り切れないので例外を通知する
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    }
                    else
                    {
                        ResourceHolderUINT root(tc);

                        __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                        __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);

                        __UNIT_TYPE v_buf[] = { v_lo };
                        __UNIT_TYPE work_v_buf[countof(v_buf)];

                        __UNIT_TYPE q_bit_count = (u->UNIT_WORD_COUNT - countof(v_buf) + 2) * __UNIT_TYPE_BIT_COUNT;
                        NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                        DivideExactly_UNIT(u->BLOCK, u->UNIT_WORD_COUNT, u->TRAILING_ZERO_BITS_COUNT,
                                           v_buf, countof(v_buf), _TZCNT_ALT_UNIT(v_lo),
                                           work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                           work_v_buf, countof(work_v_buf),
                                           q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                        root.CheckBlock(work_u_buf);
                        root.CheckNumber(q);
#endif
                        CommitNumber(tc, q);
                        if (q->IS_ZERO)
                        {
                            root.DeallocateNumber(q);
                            q = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(q);
                        return (q);
                    }
                }
                else
                {
                    // v の値が 32bit では表現できない場合
                    __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_32(v_hi);
                    if (u_bit_count < v_bit_count)
                    {
                        // 明らかに u < v である場合

                        // 割り切れないので例外を通知する
                        throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                    }
                    else
                    {
                        ResourceHolderUINT root(tc);

                        __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                        __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);

                        __UNIT_TYPE v_buf[] = { v_lo, v_hi };
                        __UNIT_TYPE work_v_buf[countof(v_buf)];
                        __UNIT_TYPE v_tzcnt = v_lo == 0 ? sizeof(v_lo) * 8 + _TZCNT_ALT_UNIT(v_hi) : _TZCNT_ALT_UNIT(v_lo);

                        __UNIT_TYPE q_bit_count = (u->UNIT_WORD_COUNT - countof(v_buf) + 2) * __UNIT_TYPE_BIT_COUNT;
                        NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                        DivideExactly_UNIT(u->BLOCK, u->UNIT_WORD_COUNT, u->TRAILING_ZERO_BITS_COUNT,
                                           v_buf, countof(v_buf), v_tzcnt,
                                           work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                           work_v_buf, countof(work_v_buf),
                                           q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                        root.CheckBlock(work_u_buf);
                        root.CheckNumber(q);
#endif
                        CommitNumber(tc, q);
                        if (q->IS_ZERO)
                        {
                            root.DeallocateNumber(q);
                            q = &number_object_uint_zero;
                        }
                        else
                            root.UnlinkNumber(q);
                        return (q);
                    }
                }
            }
        }
    }
#elif defined(_M_X64)
    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UL_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, _UINT64_T v)
    {
        if (v == 0)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        if (u->IS_ZERO)
        {
            // x が 0 である場合

            // q = 0, r = 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v == 1)
            {
                // v が 1 である場合

                // q = u, r = 0 を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // u と v の商・剰余を計算する
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = sizeof(v) * 8 - _LZCNT_ALT_UNIT((__UNIT_TYPE)v);
                if (u_bit_count < v_bit_count)
                {
                    // 明らかに u < v である場合

                    // 割り切れないので例外を通知する
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);

                    __UNIT_TYPE v_buf[] = { v };
                    __UNIT_TYPE work_v_buf[countof(v_buf)];

                    __UNIT_TYPE q_bit_count = (u->UNIT_WORD_COUNT - countof(v_buf) + 2) * __UNIT_TYPE_BIT_COUNT;
                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                    DivideExactly_UNIT(u->BLOCK, u->UNIT_WORD_COUNT, u->TRAILING_ZERO_BITS_COUNT,
                                       v_buf, countof(v_buf), _TZCNT_ALT_UNIT(v),
                                       work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                       work_v_buf, countof(work_v_buf),
                                       q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }
#else
#error unknown platform
#endif

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UL(ThreadContext& tc, PMC_HANDLE_UINT u, _UINT64_T v) noexcept(false)
    {
        if (sizeof(__UNIT_TYPE) * 2 < sizeof(v))
        {
            // _UINT64_T が 2 ワードで表現しきれない処理系には対応しない
            throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_divrem.cpp;PMC_DivideExactly_UX_L;1");
        }
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UL_Imp(tc, nu, v);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

    NUMBER_OBJECT_UINT* PMC_DivideExactly_UX_UX_Imp(ThreadContext& tc, NUMBER_OBJECT_UINT* u, NUMBER_OBJECT_UINT* v)
    {
        if (u->IS_ZERO)
        {
            // u が 0 である場合

            // 0 を返す
            return (&number_object_uint_zero);
        }
        else
        {
            // u が 0 ではない場合

            if (v->IS_ONE)
            {
                // v が 1 である場合

                // u を返す
                return (DuplicateNumber(tc, u));
            }
            else
            {
                // u > 0 かつ v > 1 である場合

                // x と y の商・剰余を計算する
                __UNIT_TYPE u_bit_count = u->UNIT_BIT_COUNT;
                __UNIT_TYPE v_bit_count = v->UNIT_BIT_COUNT;
                if (u_bit_count < v_bit_count)
                {
                    // 明らかに u < v である場合

                    // 割り切れないので例外を通知する
                    throw ArithmeticException(L"完全除算において被除数が除数で割り切れませんでした。");
                }
                else
                {
                    ResourceHolderUINT root(tc);

                    __UNIT_TYPE work_u_bit_count = u->UNIT_BIT_COUNT + __UNIT_TYPE_BIT_COUNT;
                    __UNIT_TYPE* work_u_buf = root.AllocateBlock(work_u_bit_count);

                    __UNIT_TYPE work_v_bit_count = v->UNIT_BIT_COUNT;
                    __UNIT_TYPE* work_v_buf = root.AllocateBlock(work_v_bit_count);

                    __UNIT_TYPE q_bit_count = (u->UNIT_WORD_COUNT - v->UNIT_WORD_COUNT + 2) * __UNIT_TYPE_BIT_COUNT;
                    NUMBER_OBJECT_UINT* q = root.AllocateNumber(q_bit_count);

                    DivideExactly_UNIT(u->BLOCK, u->UNIT_WORD_COUNT, u->TRAILING_ZERO_BITS_COUNT,
                                       v->BLOCK, v->UNIT_WORD_COUNT, v->TRAILING_ZERO_BITS_COUNT,
                                       work_u_buf, _DIVIDE_CEILING_UNIT(work_u_bit_count, __UNIT_TYPE_BIT_COUNT),
                                       work_v_buf, _DIVIDE_CEILING_UNIT(work_v_bit_count, __UNIT_TYPE_BIT_COUNT),
                                       q->BLOCK, q->BLOCK_COUNT);
#ifdef _DEBUG
                    root.CheckBlock(work_u_buf);
                    root.CheckBlock(work_v_buf);
                    root.CheckNumber(q);
#endif
                    CommitNumber(tc, q);
                    if (q->IS_ZERO)
                    {
                        root.DeallocateNumber(q);
                        q = &number_object_uint_zero;
                    }
                    else
                        root.UnlinkNumber(q);
                    return (q);
                }
            }
        }
    }

    PMC_HANDLE_UINT PMC_DivideExactly_UX_UX(ThreadContext& tc, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v) noexcept(false)
    {
        NUMBER_OBJECT_UINT* nu = GET_NUMBER_OBJECT(u, L"u");
        NUMBER_OBJECT_UINT* nv = GET_NUMBER_OBJECT(v, L"v");
        if (nv->IS_ZERO)
        {
            // v が 0 である場合

            // 0 による除算はエラーで返す
            throw DivisionByZeroException(L"0による除算が行われようとしました。");
        }
        ResourceHolderUINT root(tc);
        NUMBER_OBJECT_UINT* nq = PMC_DivideExactly_UX_UX_Imp(tc, nu, nv);
        root.HookNumber(nq);
        PMC_HANDLE_UINT q = GET_NUMBER_HANDLE(nq);
        root.UnlinkNumber(nq);
        return (q);
    }

}


/*
 * END OF FILE
 */
