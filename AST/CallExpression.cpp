//
// Created by aaron on 16/04/25.
//

#include "CallExpression.h"

#include <complex>

#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    CallExpression::CallExpression(ExprPtr &callee, const Token *paren, std::vector<ExprPtr> &arguments) :
        callee(std::move(callee)),
        paren(paren),
        arguments(std::move(arguments))
    {

    }

    std::any CallExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }
} // Noble::Compiler::AST