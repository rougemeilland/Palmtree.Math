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

        class ____UNIT_TYPE_Array_ChainBufferTag
            : public __ChainBufferTag
        {
        private:
            __UNIT_TYPE* _buffer;
            __UNIT_TYPE _word_count;
            __UNIT_TYPE _check_code;
        public:
            ____UNIT_TYPE_Array_ChainBufferTag(__UNIT_TYPE* buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code);
            virtual ~____UNIT_TYPE_Array_ChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Clear() override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StringChainBufferTag
            : public __ChainBufferTag
        {
        private:
            __UNIT_TYPE* _buffer;
            __UNIT_TYPE _word_count;
            __UNIT_TYPE _check_code;
        public:
            __StringChainBufferTag(__UNIT_TYPE * buffer, __UNIT_TYPE word_count, __UNIT_TYPE check_code);
            virtual ~__StringChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Clear() override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __DynamicNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_HEADER* _buffer;
        public:
            __DynamicNumberChainBufferTag(NUMBER_HEADER* buffer);
            virtual ~__DynamicNumberChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __NumberHandleHookingChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_HEADER* _buffer;
        public:
            __NumberHandleHookingChainBufferTag(NUMBER_HEADER* buffer);
            virtual ~__NumberHandleHookingChainBufferTag();
            virtual BOOL EqualsBufferAddress(void* buffer) override;
            void virtual Check() override;
            void virtual Destruct() override;
        };

        class __StaticNumberChainBufferTag
            : public __ChainBufferTag
        {
        private:
            NUMBER_HEADER* _buffer;
        public:
            __StaticNumberChainBufferTag(NUMBER_HEADER* buffer);
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

    public:
        ResourceHolderUINT();
        virtual ~ResourceHolderUINT();

        void* AllocateBytes(size_t size);
        void DeallocateBytes(void* buffer);
        void UnlinkBytes(void* buffer);

        __UNIT_TYPE* AllocateBlock(__UNIT_TYPE bit_count);
        void ClearBlock(__UNIT_TYPE* buffer);
        void DeallocateBlock(__UNIT_TYPE* buffer);
        void CheckBlock(__UNIT_TYPE* buffer);
        void UnlinkBlock(__UNIT_TYPE* buffer);

        wchar_t* AllocateString(__UNIT_TYPE count); // 終端ヌル文字を含めた文字数
        void ClearString(wchar_t* buffer);
        void DeallocateString(wchar_t* buffer);
        void CheckString(wchar_t* buffer);
        void UnlinkString(wchar_t* buffer);

        NUMBER_HEADER* AllocateNumber(__UNIT_TYPE bit_count);
        void HookNumber(NUMBER_HEADER* buffer);
        void DeallocateNumber(NUMBER_HEADER* buffer);
        void CheckNumber(NUMBER_HEADER* buffer);
        void UnlinkNumber(NUMBER_HEADER* buffer);

        void AttatchStaticNumber(NUMBER_HEADER* p, __UNIT_TYPE bit_count);
        void DetatchStaticNumber(NUMBER_HEADER* buffer);
        void UnlinkStatickNumber(NUMBER_HEADER* buffer);
    };

}

#endif


/*
 * END OF FILE
 */