#include "Parser.h"

namespace Noble::Compiler
{
    void Parser::Parse(const std::vector<Token>& tokens)
    {
        currentToken = &tokens.front();
    }

} // Noble::Compiler