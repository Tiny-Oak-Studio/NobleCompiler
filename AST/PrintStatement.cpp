#include "PrintStatement.h"

namespace Noble::Compiler::AST
{
    PrintStatement::PrintStatement(ExprPtr& expr) :
        Statement(expr)
    {}
} // Noble::Compiler::AST