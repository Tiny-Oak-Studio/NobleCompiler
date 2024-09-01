#ifndef NOBLE_COMPILER_PARSER_H_INCLUDED
#define NOBLE_COMPILER_PARSER_H_INCLUDED

#include <vector>
#include "Token.h"

namespace Noble::Compiler
{
    class Parser
    {
    public:
        void Parse(const std::vector<Token>& tokens);
    protected:
        const Token* currentToken = nullptr;
    };
} // Noble::Compiler

#endif //NOBLE_COMPILER_PARSER_H_INCLUDED
