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

#define DLL_FUNC_SYMBOL   "PMCCS_UINT_Initialize"

#ifdef _MSC_VER
#define __CDECL _cdecl
#elif defined(__GNUC__)
#define __CDECL
#else
#error unknown compiler
#endif


struct __tag_PMC_DEBUG_ENVIRONMENT
{
    int(__CDECL * log)(const wchar_t*, ...);
    void(__CDECL * pause)(void);
};

typedef struct __tag_PMC_DEBUG_ENVIRONMENT  PMC_DEBUG_ENVIRONMENT;

static void pause_console(void)
{
    getchar();
}

/*
 *
 */
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Japanese");

    printf("***start\n");

    char module_path[MAX_PATH + 1];
    GetModuleFileNameA(NULL, module_path, MAX_PATH + 1);
    *strrchr(module_path, '\\') = '\0';

    char dll_file_path[MAX_PATH + 1];
    /*
    strcpy_s(dll_file_path, MAX_PATH, module_path);
    strcat_s(dll_file_path, MAX_PATH, "\\");
    strcat_s(dll_file_path, MAX_PATH, "Palmtree.Math.Core.Uint.dll");
    */

    strcpy_s(dll_file_path, MAX_PATH, "Z:\\Sources\\Lunor\\Repos\\rougemeilland\\Palmtree.Math.Core.Uint\\dist\\Release\\x86\\Palmtree.Math.Core.Uint.dll");
//    strcpy_s(dll_file_path, MAX_PATH, "Z:\\Sources\\Lunor\\Repos\\rougemeilland\\Palmtree.Math.Core.Uint\\vs_dist\\Release\\x86\\Palmtree.Math.Core.Uint.dll");

    printf("***dll file path: %s\n", dll_file_path);

    HANDLE hLib = LoadLibraryA(dll_file_path);
    if (hLib == NULL)
    {
        DWORD err = GetLastError();
        fprintf(stderr, "***error: %d in LoadLibrary(\"%s\")\n", (int)err, dll_file_path);
        getchar();
        return (1);
    }
    void(__stdcall *proc)(PMC_DEBUG_ENVIRONMENT *);
    char* actual_symbol = DLL_FUNC_SYMBOL;
    proc = (void(__stdcall *)(PMC_DEBUG_ENVIRONMENT *))GetProcAddress(hLib, DLL_FUNC_SYMBOL);
    if (proc == NULL)
    {
        char* actual_symbol = NULL;
        fprintf(stderr, "***error: GetProcAddress(\"%s\")\n", DLL_FUNC_SYMBOL);
        getchar();
        return (1);
    }
    printf("***symbol resolved: %s\n", actual_symbol);
    PMC_DEBUG_ENVIRONMENT debug_env;
    debug_env.log = wprintf;
    debug_env.pause = pause_console;
    (*proc)(&debug_env);
    printf("***ok\n");
#ifdef _MSC_VER
    //getchar();
#endif
    return (0);
}
