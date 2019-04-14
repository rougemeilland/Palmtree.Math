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
#pragma warning(disable:4067)

#ifndef PMC_RESOURCEHOLDER_H
#define PMC_RESOURCEHOLDER_H


#include "pmc_uint.h"
#include "pmc_bidirectionallistheader.h"


namespace Palmtree::Math::Core::Internal
{

    class ThreadContext;

    class __DLLEXPORT_UINT ResourceHolder
    {
    public:
        class __DLLEXPORT_UINT __ChainBufferTag
            : public BidirectionalListHeader< __ChainBufferTag>
        {
        public:
            __ChainBufferTag();
            virtual ~__ChainBufferTag();
            void Link(__ChainBufferTag* tag);
            virtual bool EqualsBufferAddress(void* buffer) = 0;
            void virtual Clear();
            void virtual Check();
            virtual void Destruct() = 0;
        };

        class __DLLEXPORT_UINT __RootTag
            : public __ChainBufferTag
        {
        public:
            __RootTag();
            virtual ~__RootTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;
        };

#ifdef PALMTREEMATHCOREUINT_EXPORTS
#endif

    private:
        __RootTag _root_tag;

    protected:
        ThreadContext& _tc;

        ResourceHolder(ThreadContext& tc);

    public:
        virtual ~ResourceHolder();

        wchar_t* AllocateString(size_t count); // 終端ヌル文字を含めた文字数
        void ClearString(wchar_t* buffer);
        void DeallocateString(wchar_t* buffer);
        void CheckString(wchar_t* buffer);
        void UnlinkString(wchar_t* buffer);

    protected:
        void LinkTag(__ChainBufferTag* tag);

        __ChainBufferTag* FindTag(void* buffer);

        void NotExists(void* buffer);

    };

}

#endif
 
 
 /*
  * END OF FILE
  */