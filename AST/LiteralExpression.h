#ifndef LITERALEXPRESSION_H
#define LITERALEXPRESSION_H

#include <string>
#include <stdfloat>
#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct LiteralExpression : Expression
    {
        union
        {
            std::string string;
            std::float64_t number;
            bool boolean;
        } as;

        enum Type
        {
            String,
            Number,
            Boolean,
            Null
        };

        Type type = Null;
    };
}

#endif //LITERALEXPRESSION_H
