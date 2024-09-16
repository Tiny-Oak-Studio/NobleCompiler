#ifndef CONSTANTROLLERVISITOR_H
#define CONSTANTROLLERVISITOR_H

#include <any>
#include <memory>
#include <vector>
#include <iostream>
#include "../Token.h"
#include "../AST/Expression.h"
#include "../AST/ExpressionVisitor.h"
#include "../NobleCore/Value.h"
#include "../NobleCore/Frame.h"
#include "../NobleCore/Op.h"

namespace Noble::Compiler::Optimisations
{
    class ConstantFoldingVisitor final : public AST::ExpressionVisitor
    {
    public:
        void FoldConstants(std::unique_ptr<AST::Expression>& expression);
    protected:
        std::any Visit(AST::BinaryExpression* binaryExpression) override;
        std::any Visit(AST::GroupingExpression* groupingExpression) override;
        std::any Visit(AST::LiteralExpression* literalExpression) override;
        std::any Visit(AST::UnaryExpression* unaryExpression) override;
    };
}

#endif //CONSTANTROLLERVISITOR_H
