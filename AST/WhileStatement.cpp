//
// Created by aaron on 15/04/25.
//

#include "WhileStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    WhileStatement::WhileStatement(ExprPtr &condition, StatementPtr &body) :
        condition(std::move(condition)),
        body(std::move(body))
    {

    }

    std::any WhileStatement::Accept(StatementVisitor* statementVisitor)
    {
        return statementVisitor->Visit(this);
    }

} // Noble