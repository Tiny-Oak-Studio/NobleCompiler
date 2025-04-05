#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

namespace Noble::Compiler::AST
{
    struct ExpressionStatement final : Statement
    {
        ExpressionStatement(ExprPtr& expr);

        std::any Accept(struct StatementVisitor *statementVisitor) override;

        ExprPtr expression;
    };
} // Noble::Compiler::AST

#endif //EXPRESSIONSTATEMENT_H
