#ifndef WHILESTATEMENT_H
#define WHILESTATEMENT_H

#include "Statement.h"
#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct WhileStatement final : Statement
    {
        ExprPtr condition;
        StatementPtr body;

        WhileStatement(ExprPtr& condition, StatementPtr& body);

        std::any Accept(StatementVisitor *statementVisitor) override;
    };
} // Noble::Compiler::AST

#endif //WHILESTATEMENT_H
