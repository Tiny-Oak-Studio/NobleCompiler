#ifndef GROUPING_H_INCLUDED
#define GROUPING_H_INCLUDED

#include "Expression.h"
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    struct GroupingExpression final : Expression
    {
        const Expression* expression = nullptr;

        GroupingExpression(const Expression* expression);

        void Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //GROUPING_H_INCLUDED
