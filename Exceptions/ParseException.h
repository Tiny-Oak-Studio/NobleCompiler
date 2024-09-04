#ifndef PARSEEXCEPTION_H_INCLUDED
#define PARSEEXCEPTION_H_INCLUDED

#include <exception>

namespace Noble::Compiler::Exceptions
{
    class ParseException final : public std::exception
    {
        [[nodiscard]] const char* what() const noexcept override
        {
            return "ParseException: ";
        }
    };
}

#endif //PARSEEXCEPTION_H_INCLUDED
