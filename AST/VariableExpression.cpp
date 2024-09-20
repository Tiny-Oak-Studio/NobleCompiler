#include "VariableExpression.h"

namespace Noble::Compiler::AST
{
    VariableExpression::VariableExpression(const Token* name) :
        name(name)
    {
        ExpressionType = Variable;
    }


    std::any VariableExpression::Accept(ExpressionVisitor *visitor)
    {
        return visitor->Visit(this);
    }
}