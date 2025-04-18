#ifndef PRINTSTATEMENT_H
#define PRINTSTATEMENT_H

#include "Statement.h"
#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct PrintStatement final : Statement
    {
        ExprPtr expression;

        PrintStatement(ExprPtr& expression);

        std::any Accept(StatementVisitor *statementVisitor) override;
    };
} // Noble::Compiler::AST

#endif //PRINTSTATEMENT_H
