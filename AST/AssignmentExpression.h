#ifndef ASSIGNMENTEXPRESSION_H
#define ASSIGNMENTEXPRESSION_H

#include "../Token.h"
#include "Expression.h"
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    struct AssignmentExpression final : Expression
    {
        AssignmentExpression(const Token* name, ExprPtr& value);

        std::any Accept(ExpressionVisitor *visitor) override;

        const Token* name;
        ExprPtr value;
    };
} // Noble::Compiler::AST

#endif //ASSIGNMENTEXPRESSION_H
