#include "Token.h"

#include <iostream>

namespace Noble::Compiler
{
    Token::Token(const Type type, const char* firstChar, const std::size_t length) :
        type(type),
        firstCharacter(firstChar),
        length(length)
    {}

    Token::Token(const std::string& errorMessage) :
        type(Error),
        firstCharacter(&errorMessage.front()),
        length(errorMessage.length())
    {}

    std::string Token::ToString() const
    {
        return { firstCharacter, length };
    }

    std::float64_t Token::ToFloat() const
    {
        return Conversions::FromString<std::float64_t>(ToString());
    }


} // Noble::Compiler