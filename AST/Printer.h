#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

#include <string>
#include "ExpressionVisitor.h"

namespace Noble::Compiler::AST
{
    class Printer final : public ExpressionVisitor
    {
    public:
        std::string Print(struct Expression* expression);
    protected:
        std::any Visit(BinaryExpression* binaryExpression) override;
        std::any Visit(GroupingExpression* groupingExpression) override;
        std::any Visit(LiteralExpression* literalExpression) override;
        std::any Visit(UnaryExpression* unaryExpression) override;

        std::any Parenthesize(const std::string& name, std::initializer_list<Expression*> expressions);
    };
}

#endif //PRINTER_H_INCLUDED
