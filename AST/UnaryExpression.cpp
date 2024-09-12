#include "UnaryExpression.h"

namespace Noble::Compiler::AST
{
    UnaryExpression::UnaryExpression(const Token* operation, std::unique_ptr<Expression>& right) :
        operation(operation),
        right(std::move(right))
    {}

    std::any UnaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}