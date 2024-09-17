#ifndef BYTECODEVISITOR_H_INCLUDED
#define BYTECODEVISITOR_H_INCLUDED

#include <any>
#include "../Frame.h"
#include "../AST/Expression.h"
#include "../AST/ExpressionVisitor.h"

namespace Noble::Compiler::Bytecode
{
    class BytecodeVisitor final : public AST::ExpressionVisitor
    {
    public:
        void GenerateOps(AST::Expression* expression, Frame& frame);
    protected:
        Frame* frame = nullptr;

        std::any Visit(AST::BinaryExpression* binaryExpression) override;
        std::any Visit(AST::GroupingExpression* groupingExpression) override;
        std::any Visit(AST::LiteralExpression* literalExpression) override;
        std::any Visit(AST::UnaryExpression* unaryExpression) override;
    };
}

#endif //BYTECODEVISITOR_H_INCLUDED
