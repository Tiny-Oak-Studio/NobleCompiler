#include "UnaryExpression.h"

namespace Noble::Compiler::AST
{
    UnaryExpression::UnaryExpression(const Token* operation, Expression* right) :
        operation(operation),
        right(right)
    {}

    std::any UnaryExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}