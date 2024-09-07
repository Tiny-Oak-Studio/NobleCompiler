#include "BytecodeVisitor.h"

#include "../AST/BinaryExpression.h"
#include "../AST/GroupingExpression.h"
#include "../AST/LiteralExpression.h"
#include "../AST/UnaryExpression.h"

namespace Noble::Compiler::Bytecode
{
    void BytecodeVisitor::GenerateOps(AST::Expression* expression, Core::Frame& frame)
    {
        this->frame = &frame;
        expression->Accept(this);
    }

    std::any BytecodeVisitor::Visit(AST::BinaryExpression* binaryExpression)
    {
        binaryExpression->right->Accept(this);
        binaryExpression->left->Accept(this);

        //std::cout << binaryExpression->operation->ToString() << " ";
        switch (binaryExpression->operation->type)
        {
            case Token::Type::Minus: frame->WriteOp(Core::Op::Code::Subtract); break;
            case Token::Type::Plus:  frame->WriteOp(Core::Op::Code::Add);      break;
            case Token::Type::Star:  frame->WriteOp(Core::Op::Code::Multiply); break;
            default: break;
        }
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::GroupingExpression* groupingExpression)
    {
        groupingExpression->expression->Accept(this);
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::LiteralExpression* literalExpression)
    {
        //std::cout << literalExpression->ToString() << " ";
        switch (literalExpression->type)
        {
            case AST::LiteralExpression::Type::Boolean: frame->AddConstant(ToValue(std::get<bool>(literalExpression->data))); break;
            case AST::LiteralExpression::Type::Null:    frame->AddConstant(NullValue); break;
            case AST::LiteralExpression::Type::Number:  frame->AddConstant(ToValue(std::get<FloatType>(literalExpression->data))); break;
            case AST::LiteralExpression::Type::String:  break;
        }
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::UnaryExpression* unaryExpression)
    {
        unaryExpression->right->Accept(this);

        //std::cout << unaryExpression->operation->ToString() << " ";
        switch (unaryExpression->operation->type)
        {
            case Token::Type::Bang:  frame->WriteOp(Core::Op::Code::Not);    break;
            case Token::Type::Minus: frame->WriteOp(Core::Op::Code::Negate); break;
            default: break;
        }
        return 0;
    }
}
