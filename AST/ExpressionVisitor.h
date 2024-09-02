#ifndef EXPRESSIONVISITOR_H_INCLUDED
#define EXPRESSIONVISITOR_H_INCLUDED

namespace Noble::Compiler::AST
{
    struct ExpressionVisitor
    {
        virtual ~ExpressionVisitor() = default;
        virtual void Visit(struct BinaryExpression* binaryExpression) = 0;
        virtual void Visit(struct GroupingExpression* groupingExpression) = 0;
        virtual void Visit(struct LiteralExpression* literalExpression) = 0;
        virtual void Visit(struct UnaryExpression* unaryExpression) = 0;
    };
}

#endif //EXPRESSIONVISITOR_H_INCLUDED
