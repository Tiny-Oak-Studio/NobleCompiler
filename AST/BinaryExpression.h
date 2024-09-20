#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include <memory>
#include "Expression.h"
#include "ExpressionVisitor.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct BinaryExpression final : Expression
    {
        ExprPtr left = nullptr;
        const Token* operation = nullptr;
        ExprPtr right = nullptr;

        BinaryExpression(ExprPtr& left, const Token* operation, ExprPtr& right);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
}

#endif //BINARYEXPRESSION_H
