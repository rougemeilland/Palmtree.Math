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


namespace Palmtree::Math::Core::Internal
{

#pragma region セルフテスト

    void PMC_InternalTest()
    {
#if defined(_DEBUG)
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 1234567890U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 1234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 4294967295U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 4294967295UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 9999999999UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678901234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551615
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551615
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551615
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744073709551615UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 0
            unsigned char u_array[] = { 0x00 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 0U;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 0UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 1234567890U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 1234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967294
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967294
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967294
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 4294967294U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 4294967294UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 9999999998UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678901234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551614
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551614
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551614
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744073709551614UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1
            unsigned char u_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1U;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998
            unsigned char desired_w_array[] = { 0x01,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 3060399405
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 3060399405
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 3060399405
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 3060399405U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 3060399405UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8926126381
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x09,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8926126381
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x09,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8926126381
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x09,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 8926126381UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678900008388608
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x09,0xa2,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678900008388608
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x09,0xa2,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678900008388608
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x09,0xa2,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678900008388608UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744072474983725
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744072474983725
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744072474983725
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744072474983725UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998909087021
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x09,0x22,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998909087021
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x09,0x22,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998909087021
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x09,0x22,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678900025165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x29,0x86,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890
            unsigned char u_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 1234567890U;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 1234567890UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xfd,0x69,0xb6,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8589934592
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8589934592
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8589934592
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 8589934592UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678897289887744
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678897289887744
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678897289887744
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678897289887744UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744069414584320
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744069414584320
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744069414584320
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744069414584320UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998338007040
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998338007040
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998338007040
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678897774329856
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967295
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT32_T u = 4294967295U;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UI_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967295UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995705032704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 1234567890U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 1234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 4294967295U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 4294967295UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 9999999999UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678901234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744069414584319
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744069414584319
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744069414584319UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2c,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2c,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 4294967296
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 4294967296UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999995705032703
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 160694272
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x94,0x09 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 160694272
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x94,0x09 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 160694272U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 160694272UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 2884901888
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 2884901888
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 2884901888U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 2884901888UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678900160104448
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x14,0xab,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678900160104448
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x14,0xab,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678900160104448UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744063709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744063709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744063709551616UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998925478912
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0x04,0x23,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999998925478912
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0x04,0x23,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678891503060992
            unsigned char desired_w_array[] = { 0x01,0x00,0x08,0x34,0x8a,0x94,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999
            unsigned char u_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 9999999999UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999990000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x1c,0xf4,0xab,0xfd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8388608
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x80 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8388608
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x80 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 8388608U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 8388608UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 350287149
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 350287149
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 350287149U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 350287149UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8925536557
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x00,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8925536557
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x00,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 8925536557UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 6101065172474983725
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 6101065172474983725
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 6101065172474983725UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 96882374308658214189
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0x00,0x00,0x21,0x56,0x83,0x40,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 96882374308658214189
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0x00,0x00,0x21,0x56,0x83,0x40,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789000234363137397096448
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x56,0xa8,0x04,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789000234363137397096448
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x56,0xa8,0x04,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999987798586919934293293
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x40,0xa1,0x10,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999987798586919934293293
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x40,0xa1,0x10,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789000220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x50,0x8b,0x04,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456789000220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x50,0x8b,0x04,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999987654321098765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999987654321098765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789000220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x50,0x8b,0x04,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789000220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x20,0x04,0x12,0x50,0x8b,0x04,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999987654321098765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 12345678901234567890UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999987654321098765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xe0,0x14,0x73,0x56,0xab,0x54,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 92233720368547758080
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 92233720368547758080
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456788999898750329779388416
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456788999898750329779388416
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999986600277081061326848
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999986600277081061326848
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456788999893241776524230656
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456788999893241776524230656
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999981553255926290448384
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999981553255926290448384
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456788999893241776524230656
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456788999893241776524230656
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551615
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999981553255926290448384
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            _UINT64_T u = 18446744073709551615UL;
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999981553255926290448384
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UL_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 1234567890U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 1234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967295
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 4294967295U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 4294967295UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999
            unsigned char desired_w_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 9999999999UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 12345678901234567890UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551615
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 18446744073709551615UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 81553255926290448383
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x04 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999981553255926290448383
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xaa,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456788993898934827525016274
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4a,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999981553255926290448383
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456788993898934827525016274
            unsigned char desired_w_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4a,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 18446744073709551616
            unsigned char u_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999981553255926290448383
            unsigned char desired_w_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 143654912
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x90,0x08 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 143654912U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 143654912UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 2632974336
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0xf0,0x9c };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 2632974336U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 2632974336UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8925478912
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x14,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 8925478912UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9228053209892782080
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x10,0x88,0x80,0xa1,0x10,0x80 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 9228053209892782080UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 10680464442257309696
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0xf0,0x9c,0xd2,0xa1,0x38,0x94 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 10680464442257309696UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789009426117070410481664
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x30,0x8c,0x92,0x01,0x38,0x84,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999978543373436643704832
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0xf0,0x9c,0xd2,0x20,0x30,0x90,0xaa,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678901234567890123456788990960529566424104960
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x30,0x8c,0x92,0xa1,0x08,0x84,0x4a,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999999999999999999999900000000000000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0xf0,0x9c,0xd2,0xa1,0x38,0x94,0xfa,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456788990960529566424104960
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x30,0x8c,0x92,0xa1,0x08,0x84,0x4a,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999900000000000000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0xf0,0x9c,0xd2,0xa1,0x38,0x94,0xfa,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 25165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x80,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 25165824U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 25165824UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 834729261
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 834729261U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 834729261UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 268493101
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x00,0x10 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 268493101UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 234363137397096448
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x21,0x08,0xa0,0x40,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 234363137397096448UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 5999815502254372141
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0xa0,0x43,0x53 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 5999815502254372141UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 18446744073709551616
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 97080438169175913773
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0x00,0x21,0x29,0x00,0x43,0x43,0x05 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9617134952335316903326124674986824234285
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x20,0x41,0x11,0x03,0x0c,0x24,0x1c,0x82,0xd1,0x20,0x43,0x1c };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678900851375731203254639905385882617013862400
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0xa0,0x43,0x00,0x43,0x00,0x20,0x0b,0x08,0x81,0x22,0x4d,0x14,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999999276234699275535352339222292556415038765
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0xa0,0x43,0x53,0x47,0x0c,0x00,0x0e,0x00,0x07,0x22,0x43,0xc8,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678900511421122000071704434764206064361537536
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0xa0,0x43,0x00,0x43,0x00,0x20,0x2f,0x00,0x11,0x34,0x04,0x5c,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999998765432109876543210987654321098765432109
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0xa0,0x43,0x53,0x47,0x0c,0x24,0x3f,0x8a,0xdf,0x36,0x5f,0xfc,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 144265821168861184
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x89,0x00,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 144265821168861184UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 5047021154770878464
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x9f,0x0a,0x46 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 5047021154770878464UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 78543373436643704832
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x1e,0x02,0x42,0x04 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 851702842458773692338470353888058802176
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x1f,0x08,0x04,0x10,0x40,0x5b,0x80,0x34,0x00,0xc0,0x80,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 12345678901234567890123456789012345678893959492111748774030664158426643350683648
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x91,0x0a,0x04,0x40,0x40,0x09,0x83,0x1c,0x00,0x42,0x0c,0x00,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 99999999999999999999999999999999999999997145980665136516676582247584066506326016
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x9f,0x0a,0x46,0x54,0x40,0x40,0x82,0x24,0x06,0x82,0x00,0xc2,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678891663913086326508368219993165185339621376
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x91,0x0a,0x04,0x40,0x40,0x5b,0xa3,0x20,0x00,0x14,0x04,0x42,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999990000000000000000000000000000000000000000
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x9f,0x0a,0x46,0x54,0x40,0x5b,0xa3,0x3c,0x0e,0xd6,0x9c,0xe2,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 25165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x80,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 25165824U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 25165824UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 834729261
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 834729261U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 834729261UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 268493101
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x00,0x10 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 268493101UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x21,0x08,0x08,0x10,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 220685212747563008UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 5994306948999214381
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 5994306948999214381UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 78614850665189537069
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0x00,0x21,0x29,0x0e,0x00,0x43,0x04 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 851375731203254639905385882617013862400
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x0e,0x30,0x00,0xb0,0x02,0xd2,0x00,0x60,0x00,0x81,0x80,0x02 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 2724924221625317241651812747742116115757
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x00,0x30,0x11,0xa0,0x0e,0x84,0x14,0xc2,0x50,0x01,0x02,0x08 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 91360580531746826076388076778227997737003818794549711954239454831086075652404525
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53,0xb4,0x0e,0xc0,0x04,0x60,0x06,0x80,0x02,0xca,0x00,0xa4,0x4b,0x05,0x69,0x50,0xcc,0x70,0xcd,0xc3,0x49,0x03,0x1c,0x60,0x01,0x15,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789003765972017873351534051508074014796275554901609367261071698229415766983289339904
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0x24,0x60,0x10,0x15,0x00,0x4a,0x80,0xa0,0x08,0x05,0x40,0x00,0xca,0x10,0x0c,0x83,0x48,0xc0,0x1d,0x40,0x40,0x85,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999988584503370307464962764695383997880180967445018015881823806878017820873424172333
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53,0xb4,0x0e,0xd6,0x34,0xe2,0x5e,0x95,0x92,0xea,0x80,0xf6,0x4b,0x80,0x2d,0x42,0xca,0x70,0xd0,0x02,0x40,0x40,0x08,0x01,0x21,0x91,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 510802589398992141351567971457649606656
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1b,0x00,0x11,0x00,0x49,0x80,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 7145980665136516676582247584066506326016
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x24,0x10,0x83,0xd0,0x09,0x00,0x15 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 3706259432981393966511533567240343415905053362439835411028467176764976886972416
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x29,0x01,0x19,0x80,0x48,0x0c,0x15,0x67,0x09,0x10,0x48,0x80,0x2c,0x30,0x8f,0x00,0x20,0x94,0x20,0x80,0x04,0x02,0x20 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1234567890123456789012345678901234567890123456789012345678901234567890123456789003186905367621935969121245637979083606952207351340252839973504543047406858534912
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3b,0x21,0x01,0x10,0x1d,0x04,0x14,0x83,0x09,0x00,0x40,0x00,0x20,0x12,0x8c,0x00,0x00,0x94,0xc0,0x01,0x04,0x40,0x80,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 9999999999999999999999999999999999999999999999999999999999999999999999999999999931036294344379144485724890719139742277806106228671497553833287919229830053232640
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3f,0x31,0x9b,0xd8,0x5d,0x9c,0x35,0xe7,0x5b,0x10,0x80,0x04,0x02,0x32,0x84,0x10,0x20,0x10,0x40,0x00,0x05,0x22,0xa0,0xf0,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 1
            unsigned char desired_w_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 1U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 1UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 25165824
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x80,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 25165824U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 25165824UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 834729261
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 834729261U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 834729261UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 4294967296
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 4294967296UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 268493101
            unsigned char desired_w_array[] = { 0x01,0x2d,0xe1,0x00,0x10 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 268493101UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 220685212747563008
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x21,0x08,0x08,0x10,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 220685212747563008UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 5994306948999214381
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 5994306948999214381UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 78614850665189537069
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0x00,0x21,0x29,0x0e,0x00,0x43,0x04 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 511421122000071704434764206064361537536
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x0e,0x30,0x00,0xb0,0x02,0x80,0x00,0x14,0x20,0xc0,0x80,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 429345196203051579207647486284105053485
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x00,0x30,0x11,0xa0,0x0e,0x84,0x10,0x82,0xe0,0x00,0x43,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 3765972017873351534051508074014796275554901609367261071698229415766983289339904
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1c,0xa0,0x42,0x49,0x01,0x6c,0x00,0x34,0x28,0x90,0x8c,0x20,0x03,0x22,0x24,0x20,0x38,0xa0,0x08,0x86,0x20 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 90841226466387368078997788848966737928050972783450129383184492197368505623967021
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53,0xb4,0x0e,0x80,0x00,0x04,0x26,0x82,0x43,0x80,0x08,0x04,0x67,0x20,0x39,0xd0,0x04,0x60,0xe3,0x44,0x21,0x1b,0x20,0x28,0x85,0x10,0x03 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char u_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 8787799947326938872537227442366673855258847692382483474978655577178500840398700308824340064329820084632877438198150222294842267552777122987862791528900406080813
            unsigned char desired_w_array[] = { 0x01,0x2d,0xf5,0xc0,0x31,0x69,0x0e,0x30,0x53,0xb4,0x0e,0x84,0x10,0x9e,0xee,0xc2,0xdb,0xa1,0x6c,0x56,0x77,0x80,0x2d,0xc2,0x20,0x60,0xd0,0x20,0x00,0x10,0x20,0x09,0xa7,0x30,0x02,0x01,0x06,0x13,0x00,0x02,0x18,0x59,0x4d,0x31,0x14,0x18,0x08,0x18,0xf0,0x18,0x18,0x82,0x00,0x50,0x10,0xb3,0x82,0x90,0x34,0xa4,0x72,0x61,0xcc,0x16,0x10,0x40,0x00,0x0a };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 0
            unsigned char v_array[] = { 0x00 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 0U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 0UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1
            unsigned char v_array[] = { 0x01,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890
            unsigned char v_array[] = { 0x01,0xd2,0x02,0x96,0x49 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 1234567890U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 1234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967295
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT32_T v = 4294967295U;
            _UINT32_T desired_w = 0U;
            _UINT32_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UI(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967295UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 4294967296
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 4294967296UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999
            unsigned char v_array[] = { 0x01,0xff,0xe3,0x0b,0x54,0x02 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 9999999999UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x1f,0xeb,0x8c,0xa9,0x54,0xab };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 12345678901234567890UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551615
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            _UINT64_T v = 18446744073709551615UL;
            _UINT64_T desired_w = 0UL;
            _UINT64_T actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UL(u, v);
            if (actual_w != desired_w)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 18446744073709551616
            unsigned char v_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0x0f,0x63,0x2d,0x5e,0xc7,0x6b,0x05 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0x5f,0xbc,0xac,0xb8,0xf3,0xdb,0xc0,0x75,0x20,0xc9,0xa0,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0x60,0xf5,0xb9,0xab,0xbf,0xa4,0x5c,0xc3,0xf1,0x29,0x63,0x1d };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 12345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x29,0xcb,0x1d,0xa1,0x6a,0x6d,0x15,0x7f,0x09,0xb4,0x68,0x92,0xad,0x31,0x8f,0x22,0x3c,0xb6,0x3c,0xa2,0x8e,0x9e,0x6a };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 930182271542032852888152173010225859868679585906005280595890363499774658740224
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x92,0x2c,0x00,0x0b,0x22,0x1c,0xa4,0x2c,0x82,0x80,0x08,0x08 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 99999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xc0,0xce,0x64,0x27,0xa2,0x63,0xca,0x18,0xa4,0xef,0x25,0x7b,0xd1,0xcd,0x70,0xef,0xdf,0x6b,0x1f,0x3e,0xea,0x9d,0x5f,0x03 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 31036294344379144485724890719139742277806106228671497553833287919229830053232640
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x52,0x10,0x04,0x00,0x2f,0xdd,0x29,0x0f,0x16,0xe0,0x08,0x0c,0x01 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890
            unsigned char v_array[] = { 0x01,0xd2,0x0a,0x3f,0xce,0x96,0xf1,0xcf,0xac,0x4b,0xf1,0x7b,0xef,0x61,0x11,0x3d,0x24,0x5e,0x93,0xa9,0x88,0x45,0x42,0x21,0xdb,0x9c,0x0c,0x9b,0xde,0xc4,0x1f,0xc6,0x58,0xcf,0xf4,0x5a,0xd1,0xcc,0xd6,0xfc,0xc7,0xa6,0x32,0x88,0xea,0x83,0x91,0xc5,0x0a,0xa6,0x20,0x1d,0x29,0xa6,0xc5,0x44,0x75,0x6f,0xc3,0x13,0x88,0x06,0x32,0xa1,0x47,0xae,0x67,0x01 };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 22367837450395661549573121267908423148971149171495820657556811746390963855489321170018965564387974756334227210495901196076835442900579776875137207801640648704
            unsigned char desired_w_array[] = { 0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x45,0x42,0x20,0x00,0x08,0x0c,0x99,0x8c,0x84,0x17,0xc0,0x48,0x0c,0x04,0x48,0x80,0xcc,0xc2,0xbc,0x03,0x82,0x22,0x80,0x28,0x02,0x80,0x84,0x02,0xa2,0x00,0x0d,0x29,0x20,0xc1,0x44,0x71,0x46,0x80,0x12,0x80,0x06,0x00,0x00,0x45,0x84,0x06 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
        {
            ResourceHolderUINT root;
            // u = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char u_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT u = PMC_FromByteArray(u_array, countof(u_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)u);
            // v = 9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999
            unsigned char v_array[] = { 0x01,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x80,0x2d,0xc3,0xfb,0xf4,0xd0,0x22,0x52,0x50,0x28,0x0f,0xb7,0xf3,0xf2,0x13,0x57,0x13,0x14,0x42,0xdc,0x7d,0x5d,0x39,0xd6,0x99,0x19,0x59,0xf8,0x1c,0x38,0x92,0x00,0xd6,0x14,0xb3,0x86,0xb9,0x77,0xa5,0x7a,0x61,0xfe,0xb7,0x12,0x6a,0x61,0x0b };
            PMC_HANDLE_UINT v = PMC_FromByteArray(v_array, countof(v_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)v);
            // desired_w = 0
            unsigned char desired_w_array[] = { 0x00 };
            PMC_HANDLE_UINT desired_w = PMC_FromByteArray(desired_w_array, countof(desired_w_array));
            root.HookNumber((NUMBER_OBJECT_UINT*)desired_w);
            PMC_HANDLE_UINT actual_w = PMC_OneCompliment_And_BitwiseAnd_UX_UX(u, v);
            root.HookNumber((NUMBER_OBJECT_UINT*)actual_w);
            if (PMC_Equals_UX_UX(actual_w, desired_w) == 0)
                throw InternalErrorException(L"", L"");
        }
#endif
    }

#pragma endregion

}


/*
 * END OF FILE
 */