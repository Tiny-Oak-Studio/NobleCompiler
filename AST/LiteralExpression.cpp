#include "LiteralExpression.h"

namespace Noble::Compiler::AST
{
    void LiteralExpression::Accept(ExpressionVisitor* visitor)
    {
        visitor->Visit(this);
    }
}
