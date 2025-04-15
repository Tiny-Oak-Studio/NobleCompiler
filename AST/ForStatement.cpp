//
// Created by aaron on 16/04/25.
//

#include "ForStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    ForStatement::ForStatement(StatementPtr &initialiser, ExprPtr &condition, ExprPtr &increment, StatementPtr &body) :
        initialiser(std::move(initialiser)),
        condition(std::move(condition)),
        increment(std::move(increment)),
        body(std::move(body))
    {

    }

    std::any ForStatement::Accept(struct StatementVisitor* statementVisitor)
    {
        return statementVisitor->Visit(this);
    }
} // Noble::Compiler::AST