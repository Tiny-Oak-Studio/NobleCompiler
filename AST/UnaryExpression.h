#ifndef UNARY_H_INCLUDED
#define UNARY_H_INCLUDED

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct UnaryExpression final : public Expression
    {
        const Token* operation = nullptr;
        const Expression* right = nullptr;

        UnaryExpression(const Token* operation, const Expression* right);

        void Accept(ExpressionVisitor *visitor) override;
    };
}

#endif //UNARY_H_INCLUDED
