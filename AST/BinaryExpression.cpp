#include "BinaryExpression.h"

namespace Noble::Compiler::AST
{
    BinaryExpression::BinaryExpression(Expression* left, const Token* operation, Expression* right) :
        left(left),
        operation(operation),
        right(right)
    {}

    std::any BinaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
} // Noble