#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct BinaryExpression final : Expression
    {
        Expression *left = nullptr;
        const Token* operation = nullptr;
        Expression *right = nullptr;

        BinaryExpression(Expression* left, const Token* operation, Expression* right);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //BINARYEXPRESSION_H
