#include "Statement.h"

namespace Noble::Compiler::AST
{
    Statement::Statement(ExprPtr &expr) :
        expression(std::move(expr))
    {

    }
} //Noble::Compiler::AST
