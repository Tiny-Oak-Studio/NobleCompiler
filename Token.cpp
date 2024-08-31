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
} // Noble::Compiler