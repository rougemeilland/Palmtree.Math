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
        class __RationalNumberObjectStructureChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __RationalNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL* buffer);
            virtual ~__RationalNumberObjectStructureChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;
        };

        class __UBigIntNumberHandleChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            PMC_HANDLE_UINT _buffer;
        public:
            __UBigIntNumberHandleChainBufferTag(ThreadContext& tc, PMC_HANDLE_UINT x);
            virtual ~__UBigIntNumberHandleChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __BigIntNumberHandleChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            PMC_HANDLE_SINT _buffer;
        public:
            __BigIntNumberHandleChainBufferTag(ThreadContext& tc, PMC_HANDLE_SINT x);
            virtual ~__BigIntNumberHandleChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL* buffer);
            virtual ~__DynamicNumberChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StaticNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_RTNL* _buffer;
        public:
            __StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_RTNL* buffer);
            virtual ~__StaticNumberChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

    private:
        ResourceHolderRTNL(const ResourceHolderRTNL& p); // åƒÇ—èoÇµã÷é~

    public:
        ResourceHolderRTNL(ThreadContext& tc);
        virtual ~ResourceHolderRTNL();

        NUMBER_OBJECT_RTNL* AllocateRationalNumberObjectStructure();
        void UnlinkRationalNumberObjectStructure(NUMBER_OBJECT_RTNL* buffer);

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

    private:
        void UnlinkInternalNumber(PMC_HANDLE_SINT x);
        void UnlinkInternalNumber(PMC_HANDLE_UINT x);
    };

    extern PMC_HANDLE_SINT DivideExactly(ThreadContext&tc, ResourceHolderRTNL& root, PMC_HANDLE_SINT u, PMC_HANDLE_UINT v);
    extern PMC_HANDLE_UINT DivideExactly(ThreadContext&tc, ResourceHolderRTNL& root, PMC_HANDLE_UINT u, PMC_HANDLE_UINT v);
}

#endif


/*
 * END OF FILE
 */