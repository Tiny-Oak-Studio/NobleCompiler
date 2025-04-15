#ifndef FORSTATEMENT_H
#define FORSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

namespace Noble::Compiler::AST
{
    struct ForStatement final : Statement
    {
        StatementPtr initialiser;
        ExprPtr condition;
        ExprPtr increment;
        StatementPtr body;

        ForStatement(StatementPtr& initialiser, ExprPtr& condition, ExprPtr& increment, StatementPtr& body);

        std::any Accept(struct StatementVisitor *statementVisitor) override;
    };
} // Noble::Compiler::AST

#endif //FORSTATEMENT_H
