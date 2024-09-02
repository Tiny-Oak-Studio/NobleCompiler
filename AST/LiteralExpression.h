#ifndef LITERALEXPRESSION_H
#define LITERALEXPRESSION_H

#include <string>
#include <stdfloat>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    struct LiteralExpression final : Expression
    {
        std::variant<std::string, std::float64_t, bool> as;

        enum Type
        {
            String,
            Number,
            Boolean,
            Null
        };

        Type type = Null;

        void Accept(ExpressionVisitor *visitor) override;
    };
}

#endif //LITERALEXPRESSION_H
