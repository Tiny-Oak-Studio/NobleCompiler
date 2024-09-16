#include "UnaryExpression.h"

namespace Noble::Compiler::AST
{
    UnaryExpression::UnaryExpression(const Token* operation, ExprPtr& right) :
        operation(operation),
        right(std::move(right))
    {
        ExpressionType = Expression::Type::Unary;
    }

    std::any UnaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}