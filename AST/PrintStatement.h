#ifndef PRINTSTATEMENT_H
#define PRINTSTATEMENT_H

#include "Statement.h"

namespace Noble::Compiler::AST
{
    struct PrintStatement final : Statement
    {
        PrintStatement(ExprPtr& expr);
    };
} // Noble::Compiler::AST

#endif //PRINTSTATEMENT_H
