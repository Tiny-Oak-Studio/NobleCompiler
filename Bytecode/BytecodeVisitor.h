#ifndef BYTECODEVISITOR_H_INCLUDED
#define BYTECODEVISITOR_H_INCLUDED

#include <any>
#include <vector>
#include "../AST/Expression.h"
#include "../AST/ExpressionVisitor.h"
#include "../NobleCore/Op.h"

namespace Noble::Compiler::Bytecode
{
    class BytecodeVisitor final : public AST::ExpressionVisitor
    {
    public:
        std::vector<Core::Op::Code> GenerateOps(AST::Expression* expression);
    protected:
        std::any Visit(AST::BinaryExpression* binaryExpression) override;
        std::any Visit(AST::GroupingExpression* groupingExpression) override;
        std::any Visit(AST::LiteralExpression* literalExpression) override;
        std::any Visit(AST::UnaryExpression* unaryExpression) override;
    };
}

#endif //BYTECODEVISITOR_H_INCLUDED
