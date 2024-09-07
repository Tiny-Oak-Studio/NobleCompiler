#include "Token.h"

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

    Core::Runtime::FloatType Token::ToFloat() const
    {
        return Conversions::FromString<Core::Runtime::FloatType>(ToString());
    }
}