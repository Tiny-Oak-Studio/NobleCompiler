#ifndef BYTECODEVISITOR_H_INCLUDED
#define BYTECODEVISITOR_H_INCLUDED

#include <any>
#include <vector>
#include <iostream>
#include "../Frame.h"
#include "../AST/ExpressionVisitor.h"
#include "../AST/Statement.h"
#include "../AST/StatementVisitor.h"

namespace Noble::Compiler::Bytecode
{
    class BytecodeVisitor final : public AST::ExpressionVisitor, public AST::StatementVisitor
    {
    public:
        void GenerateOps(std::vector<AST::StatementPtr>& statements, Frame& frame);
    protected:
        Frame* frame = nullptr;

        //ExpressionVisitor
        std::any Visit(AST::BinaryExpression* binaryExpression) override;
        std::any Visit(AST::GroupingExpression* groupingExpression) override;
        std::any Visit(AST::LiteralExpression* literalExpression) override;
        std::any Visit(AST::UnaryExpression* unaryExpression) override;
        std::any Visit(AST::VariableExpression* variableExpression) override;

        //StatementVisitor
        std::any Visit(AST::ExpressionStatement* expressionStatement) override;
        std::any Visit(AST::VariableStatement* expressionStatement) override;
    };
}

#endif //BYTECODEVISITOR_H_INCLUDED
