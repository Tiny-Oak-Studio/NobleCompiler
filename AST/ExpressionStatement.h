#ifndef EXPRESSIONSTATEMENT_H
#define EXPRESSIONSTATEMENT_H

#include "Expression.h"
#include "Statement.h"

namespace Noble::Compiler::AST
{
    struct ExpressionStatement final : Statement
    {
        ExpressionStatement(ExprPtr& expr);
    };
} // Noble::Compiler::AST

#endif //EXPRESSIONSTATEMENT_H
