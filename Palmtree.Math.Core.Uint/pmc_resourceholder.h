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


#include "pmc_exception.h"
#include "pmc_uint_internal.h"


namespace Palmtree::Math::Core::Internal
{

    class Lock
    {
    public:
        Lock();
        ~Lock();
    };

    class ResourceHolder
    {
    protected:
        class __ChainBufferTag
        {
        private:
            __ChainBufferTag* _next;
            __ChainBufferTag* _prev;

        public:
            __ChainBufferTag()
            {
                _next = this;
                _prev = this;
            }

            virtual ~__ChainBufferTag()
            {
                Unlink();
            }

            void Link(__ChainBufferTag* tag)
            {
                tag->_next = _next;
                tag->_prev = this;
                tag->_next->_prev = tag;
                tag->_prev->_next = tag;
            }

            void Unlink()
            {
                if (_next != this)
                {
                    _next->_prev = _prev;
                    _prev->_next = _next;
                    _next = this;
                    _prev = this;
                }
            }

            __ChainBufferTag* Next()
            {
                return (_next);
            }

            __ChainBufferTag* Prev()
            {
                return (_prev);
            }

            virtual BOOL EqualsBufferAddress(void* buffer) = 0;

            void virtual Clear()
            {
            }

            void virtual Check()
            {
            }

            virtual void Destruct() = 0;
        };

        class __RootTag
            : public __ChainBufferTag
        {
        public:
            __RootTag()
            {
            }

            virtual ~__RootTag()
            {
            }

            virtual BOOL EqualsBufferAddress(void* buffer) override
            {
                throw InternalErrorException(L"予期していないコードに到達しました。", L"pmc_resourceholder.h;ResourceHolder::__RootTag::EqualsBufferAddress;1");
            }

            void virtual Destruct() override
            {
            }
        };

    private:
        __RootTag _root_tag;

    protected:
        ResourceHolder()
        {
        }

    public:
        virtual ~ResourceHolder()
        {
            Lock lock_obj;
            while (_root_tag.Next() != &_root_tag)
            {
                __ChainBufferTag* tag = _root_tag.Next();
                tag->Unlink();
                tag->Destruct();
                delete tag;
            }
        }

    protected:
        void LinkTag(__ChainBufferTag* tag)
        {
            _root_tag.Link(tag);
        }

        __ChainBufferTag* FindTag(void* buffer)
        {
            for (__ChainBufferTag* tag = _root_tag.Next(); tag != &_root_tag; tag = tag->Next())
            {
                if (tag->EqualsBufferAddress(buffer))
                    return (tag);
            }
            return (nullptr);
        }
    };

}

#endif//PMC_RESOURCEHOLDER_H
 
 
 /*
  * END OF FILE
  */