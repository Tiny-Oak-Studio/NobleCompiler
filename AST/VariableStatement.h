#ifndef VARIABLESTATEMENT_H
#define VARIABLESTATEMENT_H

#include <any>
#include "Statement.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct VariableStatement final : Statement
    {
        VariableStatement(const Token* name, ExprPtr& initialiser);

        std::any Accept(StatementVisitor* statementVisitor) override;

        const Token* name;
        ExprPtr initialiser = nullptr;
    };
} // Noble::Compiler::AST

#endif //VARIABLESTATEMENT_H
