#ifndef LITERALEXPRESSION_H_INCLUDED
#define LITERALEXPRESSION_H_INCLUDED

#include <string>
#include <stdfloat>
#include <variant>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Conversions/String.h"
#include "../NobleCore/Value.h"

namespace Noble::Compiler::AST
{
    struct LiteralExpression final : Expression
    {
        std::variant<std::string, Core::Runtime::FloatType, bool> data;

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
        explicit LiteralExpression(Core::Runtime::FloatType value);
        explicit LiteralExpression(bool value);

        std::any Accept(ExpressionVisitor *visitor) override;

        std::string ToString();
    };
}

#endif //LITERALEXPRESSION_H_INCLUDED
