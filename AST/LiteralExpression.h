#ifndef LITERALEXPRESSION_H
#define LITERALEXPRESSION_H

#include <string>
#include <stdfloat>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Conversions/String.h"

namespace Noble::Compiler::AST
{
    struct LiteralExpression final : Expression
    {
        std::variant<std::string, std::float64_t, bool> data;

        enum Type
        {
            String,
            Number,
            Boolean,
            Null
        };

        Type type;

        LiteralExpression();
        explicit LiteralExpression(const std::string& value);
        explicit LiteralExpression(std::float64_t value);
        explicit LiteralExpression(bool value);

        std::any Accept(ExpressionVisitor *visitor) override;

        std::string ToString();
    };
}

#endif //LITERALEXPRESSION_H
