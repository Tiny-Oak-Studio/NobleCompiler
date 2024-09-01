#ifndef UNARY_H_INCLUDED
#define UNARY_H_INCLUDED

#include "Expression.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct UnaryExpression
    {
        const Token* operation = nullptr;
        const Expression* right = nullptr;

        UnaryExpression(const Token* operation, const Expression* right);
    };
}

#endif //UNARY_H_INCLUDED
