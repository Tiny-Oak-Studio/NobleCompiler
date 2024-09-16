#include "ConstantFoldingVisitor.h"

#include "../AST/BinaryExpression.h"
#include "../AST/GroupingExpression.h"
#include "../AST/LiteralExpression.h"
#include "../AST/UnaryExpression.h"

namespace Noble::Compiler::Optimisations
{
    void ConstantFoldingVisitor::FoldConstants(std::unique_ptr<AST::Expression>& expression)
    {
        if (expression == nullptr) return;
        expression->Accept(this);
    }

    std::any ConstantFoldingVisitor::Visit(AST::BinaryExpression* binaryExpression)
    {
        const AST::ExprPtr& leftExpr = binaryExpression->left;
        const AST::ExprPtr& rightExpr = binaryExpression->right;
        if (leftExpr->ExpressionType == AST::Expression::Type::Literal and rightExpr->ExpressionType == AST::Expression::Type::Literal)
        {
            const auto leftLiteral = std::any_cast<AST::LiteralExpression*>(leftExpr->Accept(this));
            const auto rightLiteral = std::any_cast<AST::LiteralExpression*>(rightExpr->Accept(this));
            if (leftLiteral->type == AST::LiteralExpression::Type::Number and rightLiteral->type == AST::LiteralExpression::Type::Number)
            {
                FloatType left = std::get<FloatType>(leftLiteral->data);
                FloatType right = std::get<FloatType>(rightLiteral->data);
                FloatType final = 0;
                switch (binaryExpression->operation->type)
                {
                    case Token::Type::Minus: final = left - right; break;
                    case Token::Type::Plus:  final = left + right; break;
                    case Token::Type::Slash: final = left / right; break;
                    case Token::Type::Star:  final = left * right; break;
                    default: break;
                }
            }
        }
        else
        {
            leftExpr->Accept(this);
            rightExpr->Accept(this);
        }
        //std::cout << binaryExpression->operation->ToString() << " ";
        return 0;
    }

    std::any ConstantFoldingVisitor::Visit(AST::GroupingExpression* groupingExpression)
    {
        groupingExpression->expression->Accept(this);
        return 0;
    }

    std::any ConstantFoldingVisitor::Visit(AST::LiteralExpression* literalExpression)
    {
        //std::cout << literalExpression->ToString() << " ";
        return literalExpression;
    }

    std::any ConstantFoldingVisitor::Visit(AST::UnaryExpression* unaryExpression)
    {
        unaryExpression->right->Accept(this);
        std::cout << unaryExpression->operation->ToString() << " ";
        return 0;
    }
}