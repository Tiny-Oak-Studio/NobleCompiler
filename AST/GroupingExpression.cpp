#include "GroupingExpression.h"

namespace Noble::Compiler::AST
{
    GroupingExpression::GroupingExpression(const Expression* expression) :
        expression(expression)
    {}
}