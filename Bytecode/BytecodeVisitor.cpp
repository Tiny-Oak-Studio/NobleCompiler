#include "BytecodeVisitor.h"

namespace Noble::Compiler::Bytecode
{
    std::vector<Core::Op::Code> BytecodeVisitor::GenerateOps(AST::Expression* expression)
    {
        std::vector<Core::Op::Code> ops;



        return ops;
    }

    std::any BytecodeVisitor::Visit(AST::BinaryExpression* binaryExpression)
    {
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::GroupingExpression* groupingExpression)
    {
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::LiteralExpression* literalExpression)
    {
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::UnaryExpression* unaryExpression)
    {
        return 0;
    }
}