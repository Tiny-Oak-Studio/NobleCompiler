#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct BinaryExpression final : Expression
    {
        const Expression* left = nullptr;
        const Token* operation = nullptr;
        const Expression* right = nullptr;

        BinaryExpression(const Expression* left, const Token* operation, const Expression* right);

        void Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //BINARYEXPRESSION_H
