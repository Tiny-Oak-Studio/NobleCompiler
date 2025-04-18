#include "PrintStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    PrintStatement::PrintStatement(ExprPtr &expression) :
        expression(std::move(expression))
    {

    }

    std::any PrintStatement::Accept(StatementVisitor *statementVisitor)
    {
        return statementVisitor->Visit(this);
    }
} // Noble::Compiler::AST