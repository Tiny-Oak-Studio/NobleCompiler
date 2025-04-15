//
// Created by aaron on 15/04/25.
//

#include "IfStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    IfStatement::IfStatement(ExprPtr &condition, StatementPtr &thenBranch, StatementPtr &elseBranch) :
        condition(std::move(condition)),
        thenBranch(std::move(thenBranch)),
        elseBranch(std::move(elseBranch))
    {

    }

    std::any IfStatement::Accept(StatementVisitor* statementVisitor)
    {
        return statementVisitor->Visit(this);
    }
} // Noble::Compiler::AST