#include "AssignmentExpression.h"

namespace Noble::Compiler::AST
{
    AssignmentExpression::AssignmentExpression(const Token *name, ExprPtr &value) :
        name(name),
        value(std::move(value))
    {
        ExpressionType = Type::Assignment;
    }

    std::any AssignmentExpression::Accept(ExpressionVisitor *visitor)
    {
        visitor->Visit(this);
        return 0;
    }


} // Noble::Compiler::AST