#include "GroupingExpression.h"

namespace Noble::Compiler::AST
{
    GroupingExpression::GroupingExpression(Expression* expression) :
        expression(expression)
    {}

    std::any GroupingExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}