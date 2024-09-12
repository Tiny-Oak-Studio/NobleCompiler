#include "BinaryExpression.h"

namespace Noble::Compiler::AST
{
    BinaryExpression::BinaryExpression(std::unique_ptr<Expression>& left, const Token* operation, std::unique_ptr<Expression>& right) :
        left(std::move(left)),
        operation(operation),
        right(std::move(right))
    {}

    std::any BinaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
} // Noble