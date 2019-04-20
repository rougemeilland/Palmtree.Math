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

#ifndef PMC_RESOURCEHOLDER_UINT_H
#define PMC_RESOURCEHOLDER_UINT_H


#include "pmc_resourceholder.h"
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    class ResourceHolderUINT
        : public ResourceHolder
    {
    private:
        class __UBigIntNumberObjectStructureChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_UINT* _buffer;
        public:
            __UBigIntNumberObjectStructureChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT* buffer);
            virtual ~__UBigIntNumberObjectStructureChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;
        };

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_UINT* _buffer;
        public:
            __DynamicNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT* buffer);
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
            NUMBER_OBJECT_UINT* _buffer;
        public:
            __StaticNumberChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT* buffer);
            virtual ~__StaticNumberChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __RandomStateObjectStructureChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            RANDOM_STATE_OBJECT* _buffer;
        public:
            __RandomStateObjectStructureChainBufferTag(ThreadContext& tc, RANDOM_STATE_OBJECT* buffer);
            virtual ~__RandomStateObjectStructureChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Destruct() override;
        };

        class __RandomStateObjectChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            RANDOM_STATE_OBJECT* _buffer;
        public:
            __RandomStateObjectChainBufferTag(ThreadContext& tc, RANDOM_STATE_OBJECT* buffer);
            virtual ~__RandomStateObjectChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __InternalRandomStateObjectChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            void* _buffer;
        public:
            __InternalRandomStateObjectChainBufferTag(ThreadContext& tc, void* buffer);
            virtual ~__InternalRandomStateObjectChainBufferTag();
            virtual bool EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

    public:
        ResourceHolderUINT(ThreadContext& tc);
        virtual ~ResourceHolderUINT();

        NUMBER_OBJECT_UINT* AllocateUBigIntNumberObjectStructure();
        void DeallocateUBigIntNumberObjectStructure(NUMBER_OBJECT_UINT* buffer);
        void UnlinkUBigIntNumberObjectStructure(NUMBER_OBJECT_UINT* buffer);

        __UNIT_TYPE* AllocateBlock(__UNIT_TYPE bit_count);
        void ClearBlock(__UNIT_TYPE* buffer);
        void DeallocateBlock(__UNIT_TYPE* buffer);
        void CheckBlock(__UNIT_TYPE* buffer);
        void UnlinkBlock(__UNIT_TYPE* buffer);

        NUMBER_OBJECT_UINT* AllocateNumber(__UNIT_TYPE bit_count);
        void HookNumber(NUMBER_OBJECT_UINT* buffer);
        void DeallocateNumber(NUMBER_OBJECT_UINT* buffer);
        void CheckNumber(NUMBER_OBJECT_UINT* buffer);
        void UnlinkNumber(NUMBER_OBJECT_UINT* buffer);

        void AttatchStaticNumber(NUMBER_OBJECT_UINT* p, __UNIT_TYPE bit_count);
        void DetatchStaticNumber(NUMBER_OBJECT_UINT* buffer);
        void UnlinkStatickNumber(NUMBER_OBJECT_UINT* buffer);

        RANDOM_STATE_OBJECT* AllocateRandomStateObjectStructure();
        RANDOM_STATE_OBJECT* AllocateRandomStateObject(_UINT32_T seed);
        RANDOM_STATE_OBJECT* AllocateRandomStateObject(_UINT32_T* init_key, _INT32_T key_length);
        void DeallocateRandomStateObject(RANDOM_STATE_OBJECT* buffer);
        void HookRandomStateObject(RANDOM_STATE_OBJECT* buffer);
        void UnlinkRandomStateObject(RANDOM_STATE_OBJECT* buffer);

        void* AllocateInternalRandomStateObject(_UINT32_T seed);
        void* AllocateInternalRandomStateObject(_UINT32_T* init_key, _INT32_T key_length);
        void DeallocateInternalRandomStateObject(void* buffer);
        void HookInternalRandomStateObject(void* buffer);
        void UnlinkInternalRandomStateObject(void* buffer);

    private:
        void UnlinkInternalRandomStateObjectInternally(void* buffer);
    };

}

#endif


/*
 * END OF FILE
 */