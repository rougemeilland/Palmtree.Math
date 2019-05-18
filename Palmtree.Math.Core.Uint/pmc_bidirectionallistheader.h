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

#ifndef PMC_BIDIRECTIONAL_LIST_HEADER_H
#define PMC_BIDIRECTIONAL_LIST_HEADER_H
namespace Palmtree::Math::Core::Internal
{
    template<typename ELEMENT_T>
    class BidirectionalListHeader
    {
    private:
        ELEMENT_T* _this;
        ELEMENT_T* _next;
        ELEMENT_T* _prev;

    protected:
        BidirectionalListHeader(ELEMENT_T* p_this)
        {
            _this = p_this;
            _next = _this;
            _prev = _this;
        }

    private:
        BidirectionalListHeader(const BidirectionalListHeader& p)
        {
        }

    public:
        virtual ~BidirectionalListHeader()
        {
        }

        ELEMENT_T* Next()
        {
            return (_next);
        }

        ELEMENT_T* Prev()
        {
            return (_prev);
        }

        void AddBefore(ELEMENT_T* p)
        {
            p->_prev = _prev;
            p->_next = _this;
            _prev->_next = p;
            _prev = p;
        }

        void AddAffter(ELEMENT_T* p)
        {
            p->_prev = _this;
            p->_next = _next;
            _next->_prev = p;
            _next = p;
        }

        void Remove()
        {
            _prev->_next = _next;
            _next->_prev = _prev;
            _prev = _this;
            _next = _this;
        }

    };
}


#endif


/*
 * END OF FILE
 */