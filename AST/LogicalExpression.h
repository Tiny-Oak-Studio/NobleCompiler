#ifndef LOGICALEXPRESSION_H
#define LOGICALEXPRESSION_H

#include "Expression.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct LogicalExpression final : Expression
    {
        ExprPtr left;
        const Token* operation;
        ExprPtr right;

        LogicalExpression(ExprPtr& left, const Token* operation, ExprPtr& right);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble::Compiler::AST

#endif //LOGICALEXPRESSION_H
