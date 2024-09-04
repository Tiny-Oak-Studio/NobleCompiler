#ifndef GROUPING_H_INCLUDED
#define GROUPING_H_INCLUDED

#include "Expression.h"
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    struct GroupingExpression final : Expression
    {
        Expression* expression = nullptr;

        GroupingExpression(Expression* expression);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //GROUPING_H_INCLUDED
