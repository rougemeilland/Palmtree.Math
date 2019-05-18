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

#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "pmc_sint.h"


namespace Palmtree::Math::Core::Internal
{
    extern "C" int main(int argc, char** argv)
    {
        setlocale(LC_ALL, "Japanese");

        printf("***start\n");

        char module_path[MAX_PATH + 1];
        GetModuleFileNameA(NULL, module_path, MAX_PATH + 1);
        *strrchr(module_path, '\\') = '\0';

        char dll_file_path[MAX_PATH + 1];
        if (0)
        {
            strcpy_s(dll_file_path, MAX_PATH, module_path);
            strcat_s(dll_file_path, MAX_PATH, "\\");
            strcat_s(dll_file_path, MAX_PATH, "Palmtree.Math.Core.Sint.dll");
        }
        else
        {
            lstrcpyA(dll_file_path, "Z:\\Sources\\Lunor\\Repos\\rougemeilland\\Palmtree.Math\\dist\\Debug\\x86");
            strcat_s(dll_file_path, MAX_PATH, "\\");
            strcat_s(dll_file_path, MAX_PATH, "Palmtree.Math.Core.Sint.dll");
        }

        printf("***dll file path: %s\n", dll_file_path);

        HMODULE hLib = LoadLibraryA(dll_file_path);
        if (hLib == NULL)
        {
            DWORD err = GetLastError();
            fprintf(stderr, "***error: %d in LoadLibrary(\"%s\")\n", (int)err, dll_file_path);
            getchar();
            return (1);
        }

        bool (__stdcall *fp_PMC_SINT_Initialize)(const PMC_CONFIGURATION_INFO*);

        const char* actual_symbol = "";
        fp_PMC_SINT_Initialize = (bool (__stdcall *)(const PMC_CONFIGURATION_INFO*))GetProcAddress(hLib, "");
        if (fp_PMC_SINT_Initialize == NULL)
        {
            char* actual_symbol = NULL;
            fprintf(stderr, "***error: GetProcAddress(\"%s\")\n", "");
            getchar();
            return (1);
        }
        printf("***symbol resolved: %s\n", actual_symbol);
        PMC_CONFIGURATION_INFO conf;
        conf.MEMORY_VERIFICATION_ENABLED = 1;
        bool ep = (*fp_PMC_SINT_Initialize)(&conf);
        if (ep == false)
        {
            fprintf(stderr, "***error: PMC_UINT_Initialize()");
            getchar();
            return (1);
        }

        printf("***ok\n");
#ifdef _MSC_VER
        //getchar();
#endif
        return (0);
    }
}