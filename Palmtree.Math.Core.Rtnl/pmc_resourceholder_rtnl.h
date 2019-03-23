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

#ifndef PMC_RESOURCEHOLDER_RTNL_H
#define PMC_RESOURCEHOLDER_RTNL_H


#include "pmc_resourceholder.h"
#include "pmc_rtnl_internal.h"


namespace Palmtree::Math::Core::Internal
{

    class ResourceHolderRTNL
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

        class __SINTNumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            PMC_HANDLE_SINT _buffer;
        public:
            __SINTNumberHandleHookingChainBufferTag(PMC_HANDLE_SINT x);
            virtual ~__SINTNumberHandleHookingChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __DynamicNumberChainBufferTag(NUMBER_OBJECT_RTNL* buffer);
            virtual ~__DynamicNumberChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __NumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __NumberHandleHookingChainBufferTag(NUMBER_OBJECT_RTNL* buffer);
            virtual ~__NumberHandleHookingChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StaticNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __StaticNumberChainBufferTag(NUMBER_OBJECT_RTNL* buffer);
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
        ResourceHolderRTNL(const ResourceHolderRTNL& p); // åƒÇ—èoÇµã÷é~

    public:
        ResourceHolderRTNL();
        virtual ~ResourceHolderRTNL();

        void* AllocateBytes(size_t size);
        void DeallocateBytes(void* buffer);
        void UnlinkBytes(void* buffer);

        NUMBER_OBJECT_RTNL* AllocateNumber(PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator);
        void HookNumber(NUMBER_OBJECT_RTNL* buffer);
        void HookNumber(PMC_HANDLE_SINT x);
        void HookNumber(PMC_HANDLE_UINT x);
        void DeallocateNumber(NUMBER_OBJECT_RTNL* buffer);
        void DeallocateNumber(PMC_HANDLE_SINT x);
        void DeallocateNumber(PMC_HANDLE_UINT x);
        void CheckNumber(NUMBER_OBJECT_RTNL* buffer);
        void UnlinkNumber(NUMBER_OBJECT_RTNL* buffer);
        void UnlinkNumber(PMC_HANDLE_SINT x);
        void UnlinkNumber(PMC_HANDLE_UINT x);
        void AttatchStaticNumber(NUMBER_OBJECT_RTNL* p, PMC_HANDLE_SINT numerator, PMC_HANDLE_UINT denominator);
        void DetatchStaticNumber(NUMBER_OBJECT_RTNL* buffer);
        void UnlinkStatickNumber(NUMBER_OBJECT_RTNL* buffer);
    };

}

#endif


/*
 * END OF FILE
 */