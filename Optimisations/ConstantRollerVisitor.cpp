#include "ConstantRollerVisitor.h"

#include "../AST/BinaryExpression.h"
#include "../AST/GroupingExpression.h"
#include "../AST/LiteralExpression.h"
#include "../AST/UnaryExpression.h"

namespace Noble::Compiler::Optimisations
{
    void ConstantRollerVisitor::RollConstants(AST::Expression* expression)
    {
        if (expression == nullptr) return;

        expression->Accept(this);
    }

    std::any ConstantRollerVisitor::Visit(AST::BinaryExpression* binaryExpression)
    {
        binaryExpression->left->Accept(this);
        binaryExpression->right->Accept(this);

        std::cout << binaryExpression->operation->ToString() << " ";
        return 0;
    }

    std::any ConstantRollerVisitor::Visit(AST::GroupingExpression* groupingExpression)
    {
        groupingExpression->expression->Accept(this);
        return 0;
    }

    std::any ConstantRollerVisitor::Visit(AST::LiteralExpression* literalExpression)
    {
        std::cout << literalExpression->ToString() << " ";
        return 0;
    }

    std::any ConstantRollerVisitor::Visit(AST::UnaryExpression* unaryExpression)
    {
        unaryExpression->right->Accept(this);
        std::cout << unaryExpression->operation->ToString() << " ";
        return 0;
    }
}