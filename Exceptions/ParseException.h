#ifndef PARSEEXCEPTION_H_INCLUDED
#define PARSEEXCEPTION_H_INCLUDED

#include <exception>
#include <string>

namespace Noble::Compiler::Exceptions
{
    struct ParseException final : std::exception
    {
        ParseException(const std::string& errorMessage);

        std::string error;

        [[nodiscard]] const char* what() const noexcept override
        {
            return error.c_str();
        }
    };
}

#endif //PARSEEXCEPTION_H_INCLUDED
