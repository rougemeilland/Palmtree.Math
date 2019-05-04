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


#pragma once
#ifndef PMC_MULTIPLY_KARATSUBA_H
#define PMC_MULTIPLY_KARATSUBA_H

#include <chrono>
#include "pmc_uint_internal.h"

namespace Palmtree::Math::Core::Internal
{

    class KaratsubaMultiplicationEngine
    {
    private:
        class MemoryManager;
        class WordArray;

        static int _life_time_seconds;
        static int _interval_time_seconds;

        class SmartPointer
        {
        private:
            MemoryManager& _mm;
            WordArray* _raw_ptr;
            bool _owner;
        public:
            SmartPointer(MemoryManager& mm, WordArray* raw_ptr);
            SmartPointer(SmartPointer& p);
            ~SmartPointer();
            __UNIT_TYPE* Array() const;
#ifdef _DEBUG
            void Check();
#endif
        };

        class LinkElement
            : public BidirectionalListHeader<LinkElement>
        {
        public:
            LinkElement();
            virtual ~LinkElement();
            virtual WordArray* ToWordArray();
        };

        class WordArray
            : public LinkElement
        {
        private:
            int _log2_n;
            __UNIT_TYPE *_payload;
            __UNIT_TYPE _payload_count;
            std::chrono::steady_clock::time_point _destructed;

        public:
            WordArray(int log2_n);
            virtual ~WordArray();
            virtual WordArray* ToWordArray() override;
            int n() const;
            void Clear();
            __UNIT_TYPE* Array() const;
            std::chrono::steady_clock::time_point Destructed() const;
            void UpdateDestructed();
#ifdef _DEBUG
            void Check();
#endif
        };

        class LinkRoot
            : public LinkElement
        {
        private:
            std::chrono::steady_clock::time_point _next_cleaned;
        public:
            LinkRoot();
            virtual ~LinkRoot();
            void Add(LinkElement* p);
            WordArray* GetNewElement(int log2_n);
            void RemoveOldElements(std::chrono::steady_clock::time_point boundary);
            void RemoveAllElements();
        };

        class MemoryManager
        {
        private:
            LinkRoot _root[__UNIT_TYPE_BIT_COUNT];

        public:
            MemoryManager();

        private:
            MemoryManager(const MemoryManager& p); // 使用禁止

        public:
            ~MemoryManager();
            SmartPointer Allocate(int log2_n);
            void Deallocate(WordArray* buffer);
        };

    private:
        MemoryManager _mm;

    public:
        KaratsubaMultiplicationEngine();
        ~KaratsubaMultiplicationEngine();
        void Multiply_UX_UX(ThreadContext& tc, __UNIT_TYPE* u_buf, __UNIT_TYPE u_count, __UNIT_TYPE* v_buf, __UNIT_TYPE v_count, __UNIT_TYPE* w_buf);
        void Multiply_UX_UX_Karatsuba(ThreadContext& tc, int log2_n, __UNIT_TYPE * u_buf, __UNIT_TYPE * v_buf, __UNIT_TYPE * w_buf);

    };

}

#endif


/*
 * END OF FILE
 */
