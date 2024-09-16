#include "GroupingExpression.h"

namespace Noble::Compiler::AST
{
    GroupingExpression::GroupingExpression(ExprPtr& expression) :
        expression(std::move(expression))
    {
        ExpressionType = Type::Grouping;
    }

    std::any GroupingExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
}