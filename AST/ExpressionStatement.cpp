//
// Created by aaron on 27/03/25.
//

#include "ExpressionStatement.h"

namespace Noble::Compiler::AST
{
    ExpressionStatement::ExpressionStatement(ExprPtr &expr) :
        Statement(expr)
    {
        //Nothing
    }
} // Noble::Compiler::AST