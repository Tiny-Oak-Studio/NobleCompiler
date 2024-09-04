#include "Printer.h"

#include "BinaryExpression.h"
#include "Expression.h"
#include "GroupingExpression.h"
#include "LiteralExpression.h"
#include "UnaryExpression.h"

namespace Noble::Compiler::AST
{
    std::string Printer::Print(Expression *expression)
    {
        return std::any_cast<std::string>(expression->Accept(this));
    }

    std::any Printer::Visit(BinaryExpression* binaryExpression) {
        return Parenthesize(binaryExpression->operation->ToString(),
                            { binaryExpression->left, binaryExpression->right });
    }

    std::any Printer::Visit(GroupingExpression* groupingExpression) {
        return Parenthesize("group", { groupingExpression->expression });
    }

    std::any Printer::Visit(LiteralExpression* literalExpression)
    {
        if (literalExpression->type == LiteralExpression::Null) return "null";
        return literalExpression->ToString();
    }

    std::any Printer::Visit(UnaryExpression* unaryExpression)
    {
        return Parenthesize(unaryExpression->operation->ToString(), { unaryExpression->right } );
    }

    std::any Printer::Parenthesize(const std::string& name, const std::initializer_list<Expression*> expressions)
    {
        std::string str = "(" + name;
        for (Expression* expr : expressions)
        {
            str += " ";
            str += std::any_cast<std::string>(expr->Accept(this));
        }
        str += ")";
        return str;
    }
}
