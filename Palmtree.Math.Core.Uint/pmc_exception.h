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

#ifndef PMC_EXCEPTION_H
#define PMC_EXCEPTION_H


#include <wchar.h>
#include <exception>
#include "pmc.h"

namespace Palmtree::Math::Core::Internal
{
    class Exception
        : std::exception
    {
    private:
        PMC_STATUS_CODE _code;
        const wchar_t* _message;
        const wchar_t* _data;

    protected:
        Exception(PMC_STATUS_CODE code, const wchar_t* message) noexcept(true)
        {
            _code = code;
            _message = message;
            _data = nullptr;
        }

        Exception(PMC_STATUS_CODE code, const wchar_t* message, const wchar_t* data) noexcept(true)
        {
            _code = code;
            _message = message;
            _data = data;
        }

    public:
        Exception(const Exception& p) noexcept(true)
        {
            _code = p._code;
            _message = p._message;
            _data = p._data;
        }

        virtual ~Exception() noexcept(true)
        {
        }

        PMC_STATUS_CODE GetStatusCode() const noexcept(true)
        {
            return (_code);
        }

        wchar_t const* What() const noexcept(true)
        {
            return (_message);
        }

        wchar_t const* Data() const noexcept(true)
        {
            return (_data);
        }

    };

    class ArgumentException
        : public Exception
    {
    public:
        ArgumentException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_ARGUMENT_ERROR, message)
        {
        }

        ArgumentException(const ArgumentException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~ArgumentException() noexcept(true)
        {
        }
    };

    class ArgumentNullException
        : public Exception
    {
    public:
        ArgumentNullException(const wchar_t* message, const wchar_t* param_name) noexcept(true)
            : Exception(PMC_STATUS_ARGUMENT_NULL_ERROR, message, param_name)
        {
        }

        ArgumentNullException(const ArgumentNullException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~ArgumentNullException() noexcept(true)
        {
        }
    };

    class ArgumentOutOfRangeException
        : public Exception
    {
    public:
        ArgumentOutOfRangeException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_ARGUMENT_OUT_OF_RANGE_ERROR, message)
        {
        }

        ArgumentOutOfRangeException(const ArgumentOutOfRangeException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~ArgumentOutOfRangeException() noexcept(true)
        {
        }
    };

    class OverflowException
        : public Exception
    {
    public:
        OverflowException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_OVERFLOW, message)
        {
        }

        OverflowException(const OverflowException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~OverflowException() noexcept(true)
        {
        }
    };

    class DivisionByZeroException
        : public Exception
    {
    public:
        DivisionByZeroException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_DIVISION_BY_ZERO, message)
        {
        }

        DivisionByZeroException(const DivisionByZeroException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~DivisionByZeroException() noexcept(true)
        {
        }
    };

    class ArithmeticException
        : public Exception
    {
    public:
        ArithmeticException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_ARITHMETIC_ERROR, message)
        {
        }

        ArithmeticException(const OverflowException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~ArithmeticException() noexcept(true)
        {
        }
    };

    class FormatException
        : public Exception
    {
    public:
        FormatException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_FORMAT_ERROR, message)
        {
        }

        FormatException(const FormatException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~FormatException() noexcept(true)
        {
        }
    };

    class InsufficientBufferException
        : public Exception
    {
    public:
        InsufficientBufferException(const wchar_t* message)
            : Exception(PMC_STATUS_INSUFFICIENT_BUFFER, message)
        {
        }

        InsufficientBufferException(const InsufficientBufferException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~InsufficientBufferException() noexcept(true)
        {
        }
    };

    class NotEnoughMemoryException
        : public Exception
    {
    public:
        NotEnoughMemoryException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_NOT_ENOUGH_MEMORY, message)
        {
        }

        NotEnoughMemoryException(const NotEnoughMemoryException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~NotEnoughMemoryException() noexcept(true)
        {
        }
    };

    class NotSupportedException
        : public Exception
    {
    public:
        NotSupportedException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_NOT_SUPPORTED, message)
        {
        }

        NotSupportedException(const NotSupportedException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~NotSupportedException() noexcept(true)
        {
        }
    };

    class InternalErrorException
        : public Exception
    {
    public:
        InternalErrorException(const wchar_t* message, const wchar_t* data) noexcept(true)
            : Exception(PMC_STATUS_INTERNAL_ERROR, message, data)
        {
        }

        InternalErrorException(const InternalErrorException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~InternalErrorException() noexcept(true)
        {
        }
    };

    class BadBufferException
        : public Exception
    {
    private:
        const wchar_t* _data;
    public:
        BadBufferException(const wchar_t* message, const wchar_t* data) noexcept(true)
            : Exception(PMC_STATUS_BAD_BUFFER, message, data)
        {
        }

        BadBufferException(const BadBufferException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~BadBufferException() noexcept(true)
        {
        }
    };

    class SEHException
        : public Exception
    {
    private:
        const wchar_t* _data;
    public:
        SEHException(const wchar_t* message) noexcept(true)
            : Exception(PMC_STATUS_BAD_BUFFER, message)
        {
        }

        SEHException(const BadBufferException& p) noexcept(true)
            : Exception(p)
        {
        }

        virtual ~SEHException() noexcept(true)
        {
        }
    };

}
    
#endif //PMC_EXCEPTION_H


/*
 * END OF FILE
 */