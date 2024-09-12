#include "GroupingExpression.h"

namespace Noble::Compiler::AST
{
    GroupingExpression::GroupingExpression(std::unique_ptr<Expression>& expression) :
        expression(std::move(expression))
    {}

    std::any GroupingExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}