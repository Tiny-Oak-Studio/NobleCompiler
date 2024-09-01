#ifndef GROUPING_H
#define GROUPING_H

#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct GroupingExpression
    {
        const Expression* expression = nullptr;

        GroupingExpression(const Expression* expression);
    };
} // Noble

#endif //GROUPING_H
