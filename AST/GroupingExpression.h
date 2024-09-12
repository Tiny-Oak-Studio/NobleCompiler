#ifndef GROUPING_H_INCLUDED
#define GROUPING_H_INCLUDED

#include <memory>
#include "Expression.h"
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    struct GroupingExpression final : Expression
    {
        std::unique_ptr<Expression> expression = nullptr;

        GroupingExpression(std::unique_ptr<Expression>& expression);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //GROUPING_H_INCLUDED
