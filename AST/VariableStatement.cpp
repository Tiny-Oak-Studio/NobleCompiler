#include "VariableStatement.h"

#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    VariableStatement::VariableStatement(const Token* name, ExprPtr& initialiser) :
        name(name),
        initialiser(std::move(initialiser))
    {

    }

    std::any VariableStatement::Accept(StatementVisitor* statementVisitor)
    {
        return statementVisitor->Visit(this);
    }

} // Noble::Compiler::AST