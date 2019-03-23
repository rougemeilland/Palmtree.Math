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

#ifndef PMC_RESOURCEHOLDER_SINT_H
#define PMC_RESOURCEHOLDER_SINT_H


#include "pmc_resourceholder.h"
#include "pmc_sint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    class ResourceHolderSINT
        : ResourceHolder
    {
    private:
        class __GenericChainBufferTag
            : public __ChainBufferTag
        {
        private:
            void* _buffer;
        public:
            __GenericChainBufferTag(void* buffer);
            virtual ~__GenericChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;
        };

        class __UINTNumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            PMC_HANDLE_UINT _buffer;
        public:
            __UINTNumberHandleHookingChainBufferTag(PMC_HANDLE_UINT x);
            virtual ~__UINTNumberHandleHookingChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __DynamicNumberChainBufferTag(NUMBER_OBJECT_SINT* buffer);
            virtual ~__DynamicNumberChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __NumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __NumberHandleHookingChainBufferTag(NUMBER_OBJECT_SINT* buffer);
            virtual ~__NumberHandleHookingChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StaticNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __StaticNumberChainBufferTag(NUMBER_OBJECT_SINT* buffer);
            virtual ~__StaticNumberChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __RootTag
            : public __ChainBufferTag
        {
        public:
            __RootTag();
            virtual ~__RootTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;

        };

    private:
        ResourceHolderSINT(const ResourceHolderSINT& p); // åƒÇ—èoÇµã÷é~

    public:
        ResourceHolderSINT();
        virtual ~ResourceHolderSINT();

        void* AllocateBytes(size_t size);
        void DeallocateBytes(void* buffer);
        void UnlinkBytes(void* buffer);

        NUMBER_OBJECT_SINT* AllocateNumber(SIGN_T sign, PMC_HANDLE_UINT abs);
        void HookNumber(NUMBER_OBJECT_SINT* buffer);
        void HookNumber(PMC_HANDLE_UINT x);
        void DeallocateNumber(NUMBER_OBJECT_SINT* buffer);
        void DeallocateNumber(PMC_HANDLE_UINT x);
        void CheckNumber(NUMBER_OBJECT_SINT* buffer);
        void UnlinkNumber(NUMBER_OBJECT_SINT* buffer);
        void UnlinkNumber(PMC_HANDLE_UINT x);
        void AttatchStaticNumber(NUMBER_OBJECT_SINT* p, SIGN_T sign, PMC_HANDLE_UINT abs);
        void DetatchStaticNumber(NUMBER_OBJECT_SINT* buffer);
        void UnlinkStatickNumber(NUMBER_OBJECT_SINT* buffer);
    };

}

#endif


/*
 * END OF FILE
 */