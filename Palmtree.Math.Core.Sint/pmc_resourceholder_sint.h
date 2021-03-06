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
        : public ResourceHolder
    {
    private:
        class __BigIntNumberObjectStructureChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __BigIntNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT* buffer);
            virtual ~__BigIntNumberObjectStructureChainBufferTag();
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

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT* buffer);
            virtual ~__DynamicNumberChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __SINTNumberHandleChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __SINTNumberHandleChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT* buffer);
            virtual ~__SINTNumberHandleChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StaticNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_SINT* _buffer;
        public:
            __StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_SINT* buffer);
            virtual ~__StaticNumberChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

    private:
        ResourceHolderSINT(const ResourceHolderSINT& p); // �Ăяo���֎~

    public:
        ResourceHolderSINT(ThreadContext& tc);
        virtual ~ResourceHolderSINT();

        NUMBER_OBJECT_SINT* AllocateBigIntNumberObjectStructure();
        void DeallocateBigIntNumberObjectStructure(NUMBER_OBJECT_SINT* buffer);
        void UnlinkBigIntNumberObjectStructure(NUMBER_OBJECT_SINT* buffer);

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

    private:
        void UnlinkInternalNumber(PMC_HANDLE_UINT x);
    };

}

#endif


/*
 * END OF FILE
 */