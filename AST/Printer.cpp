#include "Printer.h"

#include "AssignmentExpression.h"
#include "BinaryExpression.h"
#include "Expression.h"
#include "ExpressionStatement.h"
#include "GroupingExpression.h"
#include "LiteralExpression.h"
#include "UnaryExpression.h"
#include "VariableExpression.h"
#include "VariableStatement.h"

namespace Noble::Compiler::AST
{
    std::string Printer::Print(Expression *expression)
    {
        return std::any_cast<std::string>(expression->Accept(this));
    }

    std::string Printer::Print(Statement* statement)
    {
        return std::any_cast<std::string>(statement->Accept(this));
    }

    std::any Printer::Visit(BinaryExpression* binaryExpression) {
        return Parenthesize(binaryExpression->operation->ToString(),
                            { binaryExpression->left.get(), binaryExpression->right.get() });
    }

    std::any Printer::Visit(GroupingExpression* groupingExpression) {
        return Parenthesize("group", { groupingExpression->expression.get() });
    }

    std::any Printer::Visit(LiteralExpression* literalExpression)
    {
        if (literalExpression->type == LiteralExpression::Null) return "null";
        return literalExpression->ToString();
    }

    std::any Printer::Visit(UnaryExpression* unaryExpression)
    {
        return Parenthesize(unaryExpression->operation->ToString(), { unaryExpression->right.get() } );
    }

    std::any Printer::Visit(VariableExpression* variableExpression)
    {
        return variableExpression->name->ToString();
    }

    std::any Printer::Visit(AssignmentExpression* assignmentExpression)
    {
        return assignmentExpression->name->ToString() + " = ";
    }

    std::any Printer::Visit(ExpressionStatement* expressionStatement)
    {
        return expressionStatement->expression->Accept(this);
    }

    std::any Printer::Visit(VariableStatement* variableStatement)
    {
        return variableStatement->name->ToString();
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
