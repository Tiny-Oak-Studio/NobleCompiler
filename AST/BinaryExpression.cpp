#include "BinaryExpression.h"

namespace Noble::Compiler::AST
{
    BinaryExpression::BinaryExpression(const Expression* left, const Token* operation, const Expression* right) :
        left(left),
        operation(operation),
        right(right)
    {}

    void BinaryExpression::Accept(ExpressionVisitor* visitor)
    {
        visitor->Visit(this);
    }
} // Noble