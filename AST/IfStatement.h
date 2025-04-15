#ifndef IFSTATEMENT_H
#define IFSTATEMENT_H

#include "Statement.h"
#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct IfStatement final : Statement
    {
        ExprPtr condition;
        StatementPtr thenBranch;
        StatementPtr elseBranch;

        IfStatement(ExprPtr& condition, StatementPtr& thenBranch, StatementPtr& elseBranch);

        std::any Accept(StatementVisitor* statementVisitor) override;
    };
} // Noble::Compiler::AST

#endif //IFSTATEMENT_H
