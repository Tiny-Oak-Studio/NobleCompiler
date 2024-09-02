#include "UnaryExpression.h"

namespace Noble::Compiler::AST
{
    UnaryExpression::UnaryExpression(const Token* operation, const Expression* right) :
        operation(operation),
        right(right)
    {}

    void UnaryExpression::Accept(ExpressionVisitor* visitor)
    {
        visitor->Visit(this);
    }
}