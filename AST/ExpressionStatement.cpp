//
// Created by aaron on 27/03/25.
//

#include "ExpressionStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    ExpressionStatement::ExpressionStatement(ExprPtr &expr) :
        expression(std::move(expr))
    {
        //Nothing
    }

    std::any ExpressionStatement::Accept(struct StatementVisitor *statementVisitor)
    {
        return statementVisitor->Visit(this);
    }
} // Noble::Compiler::AST