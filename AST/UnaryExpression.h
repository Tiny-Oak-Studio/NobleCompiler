#ifndef UNARY_H_INCLUDED
#define UNARY_H_INCLUDED

#include <memory>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct UnaryExpression final : Expression
    {
        const Token* operation = nullptr;
        std::unique_ptr<Expression> right = nullptr;

        UnaryExpression(const Token* operation, std::unique_ptr<Expression>& right);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
}

#endif //UNARY_H_INCLUDED
