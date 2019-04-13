// Palmtree.Math.ExperimentCpp.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <intrin.h>
//#include "pmc.h"
//#include "pmc_stringio.h"

namespace Palmtree::Math::Core::Internal
{

    extern "C" int main()
    {

        wchar_t exp_format[22];
        wsprintfW(exp_format, L"%%c%%s%%0%dd", 10);
        wchar_t exp_buf[1 + 1 + 21 + 1];
        int exponent = 123456;
        wsprintfW(exp_buf, exp_format, L'e', L"+", exponent);


        return 0;
    }
}
