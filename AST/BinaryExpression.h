#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    class BinaryExpression : public Expression
    {
    public:
        const Expression* left = nullptr;
        const Token* operation = nullptr;
        const Expression* right = nullptr;

        BinaryExpression(const Expression* left, const Token* operation, const Expression* right);
    };
} // Noble

#endif //BINARYEXPRESSION_H
