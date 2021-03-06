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

#include <iostream>
#include <stdio.h>
#include <locale.h>
#include <chrono>
#include <string.h>
#include <windows.h>
#include "pmc_uint_cppinterface.h"
#include "pmc_threadcontext.h"

namespace Palmtree::Math::Core::Internal
{

    extern "C" void sokutei(PMC_UINT_CppInterface& ep, ThreadContext& tc, int loop_count, PMC_HANDLE_SFMT random, int bit_count)
    {
        std::chrono::microseconds classic_total_time(0);
        std::chrono::microseconds karatsuba_total_time(0);
        std::chrono::microseconds toomcook_total_time(0);
        PMC_HANDLE_UINT u = ep.GenerateUBigIntRandomValue(tc, random, bit_count);
        PMC_HANDLE_UINT v = ep.GenerateUBigIntRandomValue(tc, random, bit_count);
        for (int count = loop_count; count > 0; --count)
        {
            PMC_HANDLE_UINT w1;
            PMC_HANDLE_UINT w2;
            PMC_HANDLE_UINT w3;
            std::chrono::steady_clock::time_point begin;
            std::chrono::steady_clock::time_point end;
            std::chrono::microseconds elapsed_time;

            begin = std::chrono::steady_clock::now();
            w1 = ep.Multiply(tc, PMC_MULTIPLICATION_METHOD_CLASSIC, u, v);
            end = std::chrono::steady_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
            classic_total_time += elapsed_time;

            begin = std::chrono::steady_clock::now();
            w2 = ep.Multiply(tc, PMC_MULTIPLICATION_METHOD_KARATSUBA, u, v);
            end = std::chrono::steady_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
            karatsuba_total_time += elapsed_time;

            begin = std::chrono::steady_clock::now();
            w3 = ep.Multiply(tc, PMC_MULTIPLICATION_METHOD_TOOMCOOK, u, v);
            end = std::chrono::steady_clock::now();
            elapsed_time = std::chrono::duration_cast<std::chrono::microseconds> (end - begin);
            toomcook_total_time += elapsed_time;

            if (!ep.Equals(w1, w2))
            {
                std::cout << "bad result" << std::endl;
                break;
            }
            if (!ep.Equals(w1, w3))
            {
                std::cout << "bad result" << std::endl;
                break;
            }

            ep.Dispose(tc, w1);
            ep.Dispose(tc, w2);
            ep.Dispose(tc, w3);
        }
        ep.Dispose(tc, u);
        ep.Dispose(tc, v);
        std::cout << "bit_count: " << bit_count << ", ";
        std::cout << "classic: " << std::fixed << classic_total_time.count() * 0.000001 / loop_count << "[sec], ";
        std::cout << "karatsuba: " << std::fixed << karatsuba_total_time.count() * 0.000001 / loop_count << "[sec],";
        std::cout << "toom&cook: " << std::fixed << toomcook_total_time.count() * 0.000001 / loop_count << "[sec]";
        std::cout << std::endl;
    }

    extern "C" int main(int argc, char** argv)
    {
        setlocale(LC_ALL, "Japanese");

        PMC_UINT_CppInterface ep;
        ep.Initialize();
        ThreadContext tc;
        PMC_HANDLE_SFMT random = ep.AllocateRandomStateObject(tc, 0);
        int loop_count = 1;

        int bit_count = 1 << 8;

        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        sokutei(ep, tc, loop_count, random, bit_count); bit_count *= 2;
        ep.Dispose(tc, random);
#ifdef _MSC_VER
        getchar();
#endif
        return (0);
    }
}