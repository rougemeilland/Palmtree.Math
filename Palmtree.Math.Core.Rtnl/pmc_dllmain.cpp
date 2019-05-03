﻿/*
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
#include "pmc_rtnl_internal.h"


namespace Palmtree::Math::Core::Internal
{

    extern "C" BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpvReserved)
    {
        BOOL result = TRUE;
        switch (dwReason)
        {
        case DLL_PROCESS_ATTACH: // DLLがプロセスのアドレス空間にマッピングされた。
#ifdef USE_WIN32_HEAP
            if (!__AllocateRTNLHeapArea())
#endif
                result = FALSE;
            break;

        case DLL_THREAD_ATTACH: // スレッドが作成されようとしている。
            break;

        case DLL_THREAD_DETACH: // スレッドが破棄されようとしている。
            break;

        case DLL_PROCESS_DETACH: // DLLのマッピングが解除されようとしている。
#ifdef USE_WIN32_HEAP
            __DeallocateRTNLHeapArea();
#endif
            break;
        default:
            result = FALSE;
            break;
        }
        return (result);
    }

}


/*
 * END OF FILE
 */