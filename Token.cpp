#include "Token.h"

namespace Noble::Compiler
{
    Token::Token(const Type type, const char* firstChar, const char* lastChar) :
        type(type),
        firstCharacter(firstChar),
        lastCharacter(lastChar)
    {}

    Token::Token(const std::string& errorMessage) :
        type(Error),
        firstCharacter(&errorMessage.front()),
        lastCharacter(&errorMessage.back())
    {}

    std::string Token::ToString() const
    {
        return { firstCharacter, static_cast<std::string::size_type>(lastCharacter - firstCharacter) };
    }

    std::float64_t Token::ToFloat() const
    {
        return std::stod(ToString());
    }


} // Noble::Compiler