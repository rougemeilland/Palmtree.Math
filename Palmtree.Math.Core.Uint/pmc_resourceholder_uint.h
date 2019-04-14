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
        class __NumberObjectUintChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_UINT* _buffer;
        public:
            __NumberObjectUintChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT* buffer);
            virtual ~__NumberObjectUintChainBufferTag();
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

        class __NumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            ThreadContext& _tc;
            NUMBER_OBJECT_UINT* _buffer;
        public:
            __NumberHandleHookingChainBufferTag(ThreadContext& tc, NUMBER_OBJECT_UINT* buffer);
            virtual ~__NumberHandleHookingChainBufferTag();
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

    public:
        ResourceHolderUINT(ThreadContext& tc);
        virtual ~ResourceHolderUINT();

        NUMBER_OBJECT_UINT* AllocateNumberObjectUint();
        void DeallocateNumberObjectUint(NUMBER_OBJECT_UINT* buffer);
        void UnlinkNumberObjectUint(NUMBER_OBJECT_UINT* buffer);

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
    };

}

#endif


/*
 * END OF FILE
 */