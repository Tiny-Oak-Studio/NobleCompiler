#ifndef CALLEXPRESSION_H
#define CALLEXPRESSION_H

#include <vector>

#include "Expression.h"
#include "../Token.h"

namespace Noble::Compiler::AST
{
    struct CallExpression final : Expression
    {
        ExprPtr callee;
        const Token* paren;
        std::vector<ExprPtr> arguments;

        CallExpression(ExprPtr& callee, const Token* paren, std::vector<ExprPtr>& arguments);

        std::any Accept(ExpressionVisitor *visitor) override;
    };
} // Noble::Compiler::AST

#endif //CALLEXPRESSION_H
