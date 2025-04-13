#ifndef PRINTER_H_INCLUDED
#define PRINTER_H_INCLUDED

#include <string>
#include "ExpressionVisitor.h"
#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    class Printer final : public ExpressionVisitor, public StatementVisitor
    {
    public:
        std::string Print(struct Expression* expression);
        std::string Print(struct Statement* statement);
    protected:
        //Expression Visitor Overrides
        std::any Visit(BinaryExpression* binaryExpression) override;
        std::any Visit(GroupingExpression* groupingExpression) override;
        std::any Visit(LiteralExpression* literalExpression) override;
        std::any Visit(UnaryExpression* unaryExpression) override;
        std::any Visit(VariableExpression* variableExpression) override;
        std::any Visit(AssignmentExpression* assignmentExpression) override;

        //Statement Visitor Overrides
        std::any Visit(ExpressionStatement* expressionStatement) override;
        std::any Visit(VariableStatement* variableStatement) override;

        std::any Parenthesize(const std::string& name, std::initializer_list<Expression*> expressions);
    };
}

#endif //PRINTER_H_INCLUDED
