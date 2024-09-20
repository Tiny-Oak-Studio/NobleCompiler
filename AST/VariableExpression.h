#ifndef VARIABLEEXPRESSION_H_INCLUDED
#define VARIABLEEXPRESSION_H_INCLUDED

#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct VariableExpression final : Expression
    {
        const Token* name = nullptr;

        explicit VariableExpression(const Token* name);

        std::any Accept(ExpressionVisitor* visitor) override;
    };
}

#endif //VARIABLEEXPRESSION_H_INCLUDED
