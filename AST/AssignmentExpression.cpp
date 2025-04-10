#include "AssignmentExpression.h"

namespace Noble::Compiler::AST
{
    AssignmentExpression::AssignmentExpression(const Token *name, ExprPtr &value) :
        value(std::move(value)),
        name(name)
    {

    }

    std::any AssignmentExpression::Accept(ExpressionVisitor *visitor)
    {
        visitor->Visit(this);
    }


} // Noble::Compiler::AST