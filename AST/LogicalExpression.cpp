//
// Created by aaron on 15/04/25.
//

#include "LogicalExpression.h"

#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    LogicalExpression::LogicalExpression(ExprPtr &left, const Token* operation, ExprPtr &right) :
        left(std::move(left)),
        operation(operation),
        right(std::move(right))
    {

    }

    std::any LogicalExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
} // Noble::Compiler::AST