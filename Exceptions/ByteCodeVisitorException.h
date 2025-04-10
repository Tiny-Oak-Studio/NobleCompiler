//
// Created by aaron on 10/04/25.
//

#ifndef BYTECODEVISITOREXCEPTION_H
#define BYTECODEVISITOREXCEPTION_H

#include <exception>
#include <string>

namespace Noble::Compiler::Exceptions
{
    struct ByteCodeVisitorException final : std::exception
    {
        ByteCodeVisitorException(const std::string& errorMessage);

        std::string error;

        [[nodiscard]] const char* what() const noexcept override
        {
            return error.c_str();
        }
    };
} // Noble

#endif //BYTECODEVISITOREXCEPTION_H
