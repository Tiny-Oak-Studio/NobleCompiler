#include "BinaryExpression.h"

namespace Noble::Compiler::AST
{
    BinaryExpression::BinaryExpression(ExprPtr& left, const Token* operation, ExprPtr& right) :
        left(std::move(left)),
        operation(operation),
        right(std::move(right))
    {
        ExpressionType = Type::Binary;
    }

    std::any BinaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
} // Noble