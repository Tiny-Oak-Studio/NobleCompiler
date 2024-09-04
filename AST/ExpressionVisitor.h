#ifndef EXPRESSIONVISITOR_H_INCLUDED
#define EXPRESSIONVISITOR_H_INCLUDED

#include <any>

namespace Noble::Compiler::AST
{
    struct ExpressionVisitor
    {
        virtual ~ExpressionVisitor() = default;
        virtual std::any Visit(struct BinaryExpression* binaryExpression) = 0;
        virtual std::any Visit(struct GroupingExpression* groupingExpression) = 0;
        virtual std::any Visit(struct LiteralExpression* literalExpression) = 0;
        virtual std::any Visit(struct UnaryExpression* unaryExpression) = 0;
    };
}

#endif //EXPRESSIONVISITOR_H_INCLUDED
