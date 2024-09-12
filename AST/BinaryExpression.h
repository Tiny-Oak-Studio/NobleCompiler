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
        std::unique_ptr<Expression> left = nullptr;
        const Token* operation = nullptr;
        std::unique_ptr<Expression> right = nullptr;

        BinaryExpression(std::unique_ptr<Expression>& left, const Token* operation, std::unique_ptr<Expression>& right);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble

#endif //BINARYEXPRESSION_H
