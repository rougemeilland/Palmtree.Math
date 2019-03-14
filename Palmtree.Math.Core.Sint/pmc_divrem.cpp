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
#include "pmc_sint_internal.h"
#include "pmc_resourceholder_sint.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{
    // q.abs == u.abs / v.abs
    // q.sign == u.sign * v.sign
    // r.abs == u.abs % v.abs
    // r.sign == u.sign

    // ���b���ȒP�ɂ��邽�߂�64�r�b�g�����^�ɂ��Ă͍l�����Ȃ��B
    // 1) u �������Ȃ�32bit�����Av �����{�������̏ꍇ�ɁAq �� r �𕄍��Ȃ�(���邢�͕����t)32bit�����ŕ\���ł��邩�H
    //   u.sign >= 0 �Ȃ̂ŁAq.sign == v.sign, r.sign > 0�B
    //   �� u �͕����Ȃ��Aq �͕����t�łȂ���΂Ȃ�Ȃ��B
    //   r.abs <= u.abs ���� r.abs < v.abs �Ȃ̂ŁA r �͕����Ȃ�32bit�����ŕ\���ł���B
    //   ����Aq �͕������Œ�ł͂Ȃ����߂ɕ����Ȃ������ł͕\���ł��Ȃ��B���Aq.abs <= u.abs �ł��邪�������]�ɂ�萸�x��������\��������B
    //   �˂���āAq �͑��{�������ŕ\������K�v������B
    //
    // 2) u �������t��32bit�����Av �����{�������̏ꍇ�ɁAq �� r �𕄍��Ȃ�(���邢�͕����t)32bit�����ŕ\���ł��邩�H
    //   u �� q �̕����͂Ƃ��ɌŒ肳��Ȃ����߁A�����t�����ł���K�v������B
    //   r.abs <= u.abs ���� r.abs < v.abs �ł���Ar �͐�Βl�ɂ����Ă�u�ȉ��ŕ����ɂ����Ă�u�Ɠ����Ȃ̂ŁAr��32�r�b�g�����ŕ\���ł���B
    //   ����Aq�ɂ��Ă�1)�Ɠ��l�̗��R�ɂ��32�r�b�g�����ŕ\�����邱�Ƃ͂ł��Ȃ��B
    //
    // 3) u �����{�������Av �������Ȃ�32bit�����̏ꍇ�ɁAq �� r �𕄍��Ȃ�(���邢�͕����t)32bit�����ŕ\���ł��邩�H
    //   u �� q �̕����͂Ƃ��ɌŒ肳��Ȃ����߁A�����t�����ł���K�v������B
    //   r.abs < v.abs �ł͂��邪�Ar�̕����͕��ł����肤�邽�߁A�������]�ɂ�萸�x�������邱�Ƃ�����B
    //   �y��zu == -2147483648(0x80000000)�Av == 0x80000001�̏ꍇ�A�� r�̕����͕�����Βl��0x80000000�ł��邪�A����͕����t32bit�����ł͕\���ł��Ȃ��B���̔���ɂ��Ar�͕����t���{�������ł���K�v������B
    //   ����Aq �ɂ��ẮAq.abs == u.abs / v.abs �ł���A32�r�b�g�����ŕ\���\�Ƃ͌���Ȃ����Ƃ��e�Ղɂ킩��B
    //   �˂����̂��Ƃ���Aq �� r �͂Ƃ��ɕ����t���{�������łȂ���΂Ȃ�Ȃ��B
    //
    // 4) u �����{�������Av �������t��32bit�����̏ꍇ�ɁAq �� r �𕄍��Ȃ�(���邢�͕����t)32bit�����ŕ\���ł��邩�H
    //   u �� q �̕����͂Ƃ��ɌŒ肳��Ȃ����߁A�����t�����ł���K�v������B
    //   r.abs < v.abs �ł��� v.abs �̍ő�l�� 0x80000000 �ł��邽�߁Ar.abs �� 0x80000000 �ȏ�ƂȂ邱�Ƃ͂Ȃ��A�������]�ɂ���Đ��x�������邱�Ƃ͂Ȃ��B
    //   �� r �͕����t32�r�b�g�����ŕ\���ł���B
    //   ����Aq �ɂ��ẮA3)�Ɠ��l�ɕ����t���{�������łȂ���΂Ȃ�Ȃ��B
    //
    // �����_�F�ǂ̃I�[�o�[���[�h�̏ꍇ�ł�q�͕����t���{�������ł���K�v������B�܂��Ar �͈ȉ��̏����ŌŒ萸�x�����ɂȂ邱�Ƃ��ł���B
    // a) u �������Ȃ��Œ萸�x�����̏ꍇ �� r �� v�Ɠ����^�̐���
    // b) u ���������Œ萸�x�����̏ꍇ �� r �� v�Ɠ����^�̐���
    // c) v ���������Œ萸�x�����̏ꍇ �� r �� v�Ɠ����^�̐���
    //
    // �Ƃ͌������̂�
    //
    // ���ϓI�ȗ��������ɂ������������邽�߁Ar�̌^���ȉ��̂悤�ɂ���(����c���폜)
    // a') u �������Ȃ��Œ萸�x�����̏ꍇ �� r �� v�Ɠ����^�̐���
    // b') u ���������Œ萸�x�����̏ꍇ �� r �� v�Ɠ����^�̐���



    // �I�[�o�[���[�h���� q �� r �̌^����������

    _UINT32_T __PMC_CALL PMC_DivRem_UI_X(_UINT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        // ���̏ꍇ�� q �� r �̐��x�� _INT32_T �Ŗ��Ȃ����A�I�[�o�[�t���[���Ă��܂��P�[�X�����݂��邽�߁APMC_HANDLE_SINT �^�Ƃ���
        // ��: u == -2147483648, v == -1 �̏ꍇ�Aq = 2147483648, r = 0 �ƂȂ邪 2147483648 �� _INT32_T�ł͕\���ł��Ȃ��B
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (nv->SIGN == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (u == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u > 0 �̏ꍇ

            if (q != nullptr)
            {
                char q_sign = nv->SIGN;
                _UINT32_T q_abs;
                _UINT32_T r_abs = ep_uint.DivRem_I_X(u, nv->ABS, &q_abs);
                *q = (PMC_HANDLE_SINT)From_I_Imp(q_abs == 0 ? 0 : q_sign, q_abs);
                return (r_abs);
            }
            else
                return (ep_uint.DivRem_I_X(u, nv->ABS, nullptr));
        }
    }

    _INT32_T __PMC_CALL PMC_DivRem_I_X(_INT32_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        // ���̏ꍇ�� q �� r �̐��x�� _INT32_T �Ŗ��Ȃ����A�I�[�o�[�t���[���Ă��܂��P�[�X�����݂��邽�߁APMC_HANDLE_SINT �^�Ƃ���
        // ��: u == -2147483648, v == -1 �̏ꍇ�Aq = 2147483648, r = 0 �ƂȂ邪 2147483648 �� _INT32_T�ł͕\���ł��Ȃ��B
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (nv->SIGN == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (u_sign == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = u_sign > 0 ? nv->SIGN : -nv->SIGN;
                char r_sign = u_sign;
                _UINT32_T q_abs;
                _UINT32_T r_abs = ep_uint.DivRem_I_X(u_abs, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_I_Imp(q_abs == 0 ? 0 : q_sign, q_abs);
                root.HookNumber(nq);
                _INT32_T r = GET_INT_32(r_abs == 0 ? 0 : r_sign, r_abs);
                root.UnlinkNumber(nq);
                *q = (PMC_HANDLE_SINT)nq;
                return (r);
            }
            else
            {
                char r_sign = u_sign;
                _UINT32_T r_abs = ep_uint.DivRem_I_X(u_abs, nv->ABS, nullptr);
                return (GET_INT_32(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    _UINT64_T __PMC_CALL PMC_DivRem_UL_X(_UINT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        // ���̏ꍇ�� q �� r �̐��x�� _INT32_T �Ŗ��Ȃ����A�I�[�o�[�t���[���Ă��܂��P�[�X�����݂��邽�߁APMC_HANDLE_SINT �^�Ƃ���
        // ��: u == -9223372036854775808, v == -1 �̏ꍇ�Aq = 9223372036854775808, r = 0 �ƂȂ邪 9223372036854775808 �� _INT64_T�ł͕\���ł��Ȃ��B
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (nv->SIGN == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (u == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                char q_sign = nv->SIGN;
                _UINT64_T q_abs;
                _UINT64_T r_abs = ep_uint.DivRem_L_X(u, nv->ABS, &q_abs);
                *q = (PMC_HANDLE_SINT)From_L_Imp(q_abs == 0 ? 0 : q_sign, q_abs);
                return (r_abs);
            }
            else
                return (ep_uint.DivRem_L_X(u, nv->ABS, nullptr));
        }
    }

    _INT64_T __PMC_CALL PMC_DivRem_L_X(_INT64_T u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        // ���̏ꍇ�� q �� r �̐��x�� _INT32_T �Ŗ��Ȃ����A�I�[�o�[�t���[���Ă��܂��P�[�X�����݂��邽�߁APMC_HANDLE_SINT �^�Ƃ���
        // ��: u == -9223372036854775808, v == -1 �̏ꍇ�Aq = 9223372036854775808, r = 0 �ƂȂ邪 9223372036854775808 �� _INT64_T�ł͕\���ł��Ȃ��B
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (nv->SIGN == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (u_sign == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = u_sign > 0 ? nv->SIGN : -nv->SIGN;
                char r_sign = u_sign;
                _UINT64_T q_abs;
                _UINT64_T r_abs = ep_uint.DivRem_L_X(u_abs, nv->ABS, &q_abs);
                NUMBER_OBJECT_SINT* nq = From_L_Imp(q_abs == 0 ? 0 : q_sign, q_abs);
                root.HookNumber(nq);
                _INT64_T r = GET_INT_64(r_abs == 0 ? 0 : r_sign, r_abs);
                root.UnlinkNumber(nq);
                *q = (PMC_HANDLE_SINT)nq;
                return (r);
            }
            else
            {
                char r_sign = u_sign;
                _UINT64_T r_abs = ep_uint.DivRem_L_X(u_abs, nv->ABS, nullptr);
                return (GET_INT_64(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_UINT __PMC_CALL PMC_DivRem_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (nv->SIGN == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (number_handle_uint_zero);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nv->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r = ep_uint.DivRem_X_X(u, nv->ABS, &q_abs);
                root.HookNumber(r);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                root.UnlinkNumber(r);
                root.UnlinkNumber(nq);
                *q = (PMC_HANDLE_SINT)nq;
                return (r);
            }
            else
                return (ep_uint.DivRem_X_X(u, nv->ABS, nullptr));
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_UI(PMC_HANDLE_SINT u, _UINT32_T v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (v == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT32_T r_abs = ep_uint.DivRem_X_I(nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(r_abs == 0 ? 0 : r_sign, r_abs);
                root.HookNumber(nr);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                char r_sign = nu->SIGN;
                _UINT32_T r_abs = ep_uint.DivRem_X_I(nu->ABS, v, nullptr);
                return ((PMC_HANDLE_SINT)From_I_Imp(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_I(PMC_HANDLE_SINT u, _INT32_T v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN > 0 ? v_sign : -v_sign;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT32_T r_abs = ep_uint.DivRem_X_I(nu->ABS, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_I_Imp(r_abs == 0 ? 0 : r_sign, r_abs);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(nq);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                char r_sign = nu->SIGN;
                _UINT32_T r_abs = ep_uint.DivRem_X_I(nu->ABS, v_abs, nullptr);
                return ((PMC_HANDLE_SINT)From_I_Imp(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_UL(PMC_HANDLE_SINT u, _UINT64_T v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (v == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT64_T r_abs = ep_uint.DivRem_X_L(nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(r_abs == 0 ? 0 : r_sign, r_abs);
                root.HookNumber(nr);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                char r_sign = nu->SIGN;
                _UINT64_T r_abs = ep_uint.DivRem_X_L(nu->ABS, v, nullptr);
                return ((PMC_HANDLE_SINT)From_L_Imp(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_L(PMC_HANDLE_SINT u, _INT64_T v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (v_sign == 0)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return (0);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN > 0 ? v_sign : -v_sign;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                _UINT64_T r_abs = ep_uint.DivRem_X_L(nu->ABS, v_abs, &q_abs);
                root.HookNumber(q_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = From_L_Imp(r_abs == 0 ? 0 : r_sign, r_abs);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(nq);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                char r_sign = nu->SIGN;
                _UINT64_T r_abs = ep_uint.DivRem_X_L(nu->ABS, v_abs, nullptr);
                return ((PMC_HANDLE_SINT)From_L_Imp(r_abs == 0 ? 0 : r_sign, r_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (v->FLAGS.IS_ZERO)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q == nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem_X_X(nu->ABS, v, &q_abs);
                root.HookNumber(q_abs);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_abs->FLAGS.IS_ZERO ? 0 : r_sign, r_abs);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(r_abs);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                ResourceHolderSINT root;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem_X_X(nu->ABS, v, nullptr);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_abs->FLAGS.IS_ZERO ? 0 : r_sign, r_abs);
                root.UnlinkNumber(r_abs);
                root.UnlinkNumber(nr);
                return ((PMC_HANDLE_SINT)nr);
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_DivRem_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v, PMC_HANDLE_SINT* q)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"������null���^�����Ă��܂��B", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        if (nv->IS_ZERO)
        {
            // v == 0 �̏ꍇ

            // �G���[��Ԃ�
            throw DivisionByZeroException(L"0�ɂ�鏜�Z���s���悤�Ƃ��܂����B");
        }
        if (nu->SIGN == 0)
        {
            // u == 0 �̏ꍇ

            if (q != nullptr)
                *q = (PMC_HANDLE_SINT)&number_object_sint_zero;
            return ((PMC_HANDLE_SINT)&number_object_sint_zero);
        }
        else
        {
            // u != 0 �̏ꍇ

            if (q != nullptr)
            {
                ResourceHolderSINT root;
                char q_sign = nu->SIGN > 0 ? nv->SIGN : -nv->SIGN;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT q_abs;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem_X_X(nu->ABS, nv->ABS, &q_abs);
                root.HookNumber(q_abs);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nq = root.AllocateNumber(q_abs->FLAGS.IS_ZERO ? 0 : q_sign, q_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_abs->FLAGS.IS_ZERO ? 0 : r_sign, r_abs);
                root.UnlinkNumber(q_abs);
                root.UnlinkNumber(r_abs);
                root.UnlinkNumber(nq);
                root.UnlinkNumber(nr);
                *q = (PMC_HANDLE_SINT)nq;
                return ((PMC_HANDLE_SINT)nr);
            }
            else
            {
                ResourceHolderSINT root;
                char r_sign = nu->SIGN;
                PMC_HANDLE_UINT r_abs = ep_uint.DivRem_X_X(nu->ABS, nv->ABS, nullptr);
                root.HookNumber(r_abs);
                NUMBER_OBJECT_SINT* nr = root.AllocateNumber(r_abs->FLAGS.IS_ZERO ? 0 : r_sign, r_abs);
                root.UnlinkNumber(r_abs);
                root.UnlinkNumber(nr);
                return ((PMC_HANDLE_SINT)nr);
            }
        }
    }

}


/*
 * END OF FILE
 */