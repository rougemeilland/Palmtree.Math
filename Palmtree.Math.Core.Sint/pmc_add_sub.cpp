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
#include "pmc_resourceholder_sint.h"
#include "pmc_sint_internal.h"
#include "pmc_inline_func.h"


namespace Palmtree::Math::Core::Internal
{

    static NUMBER_OBJECT_SINT* AddU_X_I_Imp(char sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_I_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Add_X_I(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* AddU_X_L_Imp(char sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_L_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Add_X_L(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* AddU_X_X_Imp(char sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;AddU_X_X_Imp;2");
#endif
        ResourceHolderSINT root;
        PMC_HANDLE_UINT w_abs = ep_uint.Add_X_X(u, v);
        root.HookNumber(w_abs);
        NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
        root.UnlinkNumber(w_abs);
        root.UnlinkNumber(w);
        return (w);
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_I_Imp(char sign, PMC_HANDLE_UINT u, _UINT32_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_I_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_I_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare_X_I(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) ÇÃèÍçá

            // abs(u) - abs(v) Çï‘Ç∑
            ResourceHolderSINT root;
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct_X_I(u, v);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) ÇÃèÍçá

            // 0 Çï‘Ç∑
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) ÇÃèÍçá

            // - (abs(v) - abs(u)) Çï‘Ç∑
            ResourceHolderSINT root;
            _UINT32_T t = ep_uint.Subtruct_I_X(v, u);
            PMC_HANDLE_UINT w_abs = ep_uint.From_I(t);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(-sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        return (PMC_STATUS_OK);
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_L_Imp(char sign, PMC_HANDLE_UINT u, _UINT64_T v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_L_Imp;1");
        if (v == 0)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_L_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare_X_L(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) ÇÃèÍçá

            // abs(u) - abs(v) Çï‘Ç∑
            ResourceHolderSINT root;
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct_X_L(u, v);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) ÇÃèÍçá

            // 0 Çï‘Ç∑
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) ÇÃèÍçá

            // - (abs(v) - abs(u)) Çï‘Ç∑
            ResourceHolderSINT root;
            _UINT64_T t = ep_uint.Subtruct_L_X(v, u);
            PMC_HANDLE_UINT w_abs = ep_uint.From_L(t);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(-sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        return (PMC_STATUS_OK);
    }

    static NUMBER_OBJECT_SINT* SubtructU_X_X_Imp(char sign, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v)
    {
#ifdef _DEBUG
        if (u->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_X_Imp;1");
        if (v->FLAGS.IS_ZERO)
            throw InternalErrorException(L"ì‡ïîÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩÅB", L"pmc_add_sub.cpp;SubtructU_X_X_Imp;2");
#endif
        _INT32_T c = ep_uint.Compare_X_X(u, v);
        if (c > 0)
        {
            // abs(u) > abs(v) ÇÃèÍçá

            // abs(u) - abs(v) Çï‘Ç∑
            ResourceHolderSINT root;
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct_X_X(u, v);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        else if (c == 0)
        {
            // abs(u) == abs(v) ÇÃèÍçá

            // 0 Çï‘Ç∑
            return (&number_object_sint_zero);
        }
        else
        {
            // abs(u) < abs(v) ÇÃèÍçá

            // - (abs(v) - abs(u)) Çï‘Ç∑
            ResourceHolderSINT root;
            PMC_HANDLE_UINT w_abs = ep_uint.Subtruct_X_X(v, u);
            root.HookNumber(w_abs);
            NUMBER_OBJECT_SINT* w = root.AllocateNumber(-sign, w_abs);
            root.UnlinkNumber(w_abs);
            root.UnlinkNumber(w);
            return (w);
        }
        return (PMC_STATUS_OK);
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_UI_X(_UINT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(1, u));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nv->ABS, u));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_I_X(_INT32_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else if (u_sign > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(-1, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_UL_X(_UINT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(1, u));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nv->ABS, u));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_L_X(_INT64_T u, PMC_HANDLE_SINT v) noexcept(false)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else if (u_sign > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(-1, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_UX(u));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // u + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(1, u, nv->ABS));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // u - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(1, u, nv->ABS));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(1, v));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(v_sign, v_abs));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(1, nu->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(-1, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(1, v));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(v_sign, v_abs));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(1, nu->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(-1, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_UX(v));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(-1, nu->ABS, v));
            }

        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Add_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nv));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(1, nu->ABS, nv->ABS));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(1, nu->ABS, nv->ABS));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(-1, nu->ABS, nv->ABS));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(-1, nu->ABS, nv->ABS));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_UI_X(_UINT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(1, u));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nv->ABS, u));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_I_X(_INT32_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT32_T u_abs = GET_ABS_32(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else if (u_sign > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(-1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(1, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_UL_X(_UINT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(1, u));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nv->ABS, u));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nv->ABS, u));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_L_X(_INT64_T u, PMC_HANDLE_SINT v)
    {
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        char u_sign;
        _UINT64_T u_abs = GET_ABS_64(u, &u_sign);
        if (u_sign == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else if (u_sign > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nv->ABS, u_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(u_sign, u_abs));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(-1, nv->ABS, u_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(1, nv->ABS, u_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_UX_X(PMC_HANDLE_UINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nv);
        if (u->FLAGS.IS_ZERO)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_UX(u));
            }
            else if (nv->SIGN > 0)
            {
                // u > 0 ÇÃèÍçá

                // u - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(1, u, nv->ABS));
            }
            else
            {
                // u < 0 ÇÃèÍçá

                // u + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(1, u, nv->ABS));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_UI(PMC_HANDLE_SINT u, _UINT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(-1, v));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_I(PMC_HANDLE_SINT u, _INT32_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT32_T v_abs = GET_ABS_32(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_I_Imp(-v_sign, v_abs));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(1, nu->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_I_Imp(-1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_I_Imp(-1, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_UL(PMC_HANDLE_SINT u, _UINT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(-1, v));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_L(PMC_HANDLE_SINT u, _INT64_T v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        char v_sign;
        _UINT64_T v_abs = GET_ABS_64(v, &v_sign);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)From_L_Imp(-v_sign, v_abs));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(1, nu->ABS, v_abs));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v_sign == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (v_sign > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_L_Imp(-1, nu->ABS, v_abs));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_L_Imp(-1, nu->ABS, v_abs));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_UX(PMC_HANDLE_SINT u, PMC_HANDLE_UINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        CheckNumber(nu);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nu));
            }

        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(1, nu->ABS, v));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (v->FLAGS.IS_ZERO)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - v ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(-1, nu->ABS, v));
            }
        }
    }

    PMC_HANDLE_SINT __PMC_CALL PMC_Subtruct_X_X(PMC_HANDLE_SINT u, PMC_HANDLE_SINT v)
    {
        if (u == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"u");
        if (v == nullptr)
            throw ArgumentNullException(L"à¯êîÇ…nullÇ™ó^Ç¶ÇÁÇÍÇƒÇ¢Ç‹Ç∑ÅB", L"v");
        NUMBER_OBJECT_SINT* nu = (NUMBER_OBJECT_SINT*)u;
        NUMBER_OBJECT_SINT* nv = (NUMBER_OBJECT_SINT*)v;
        CheckNumber(nu);
        CheckNumber(nv);
        if (nu->SIGN == 0)
        {
            // u == 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // 0 Çï‘Ç∑
                return ((PMC_HANDLE_SINT)&number_object_sint_zero);
            }
            else
            {
                // v != 0 ÇÃèÍçá

                // -v Çï‘Ç∑
                return ((PMC_HANDLE_SINT)NegateNumber_X(nv));
            }
        }
        else if (nu->SIGN > 0)
        {
            // u > 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // abs(u) - abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(1, nu->ABS, nv->ABS));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // abs(u) + abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(1, nu->ABS, nv->ABS));
            }
        }
        else
        {
            // u < 0 ÇÃèÍçá

            if (nv->SIGN == 0)
            {
                // v == 0 ÇÃèÍçá

                // u Çï‘Ç∑
                return ((PMC_HANDLE_SINT)DuplicateNumber_X(nu));
            }
            else if (nv->SIGN > 0)
            {
                // v > 0 ÇÃèÍçá

                // - abs(u) - abs(v) ÇåvéZÇ∑ÇÈ
                return ((PMC_HANDLE_SINT)AddU_X_X_Imp(-1, nu->ABS, nv->ABS));
            }
            else
            {
                // v < 0 ÇÃèÍçá

                // - abs(u) + abs(v) Çï‘Ç∑
                return ((PMC_HANDLE_SINT)SubtructU_X_X_Imp(-1, nu->ABS, nv->ABS));
            }
        }
    }

}

/*
 * END OF FILE
 */