#include "BytecodeVisitor.h"

#include "../AST/BinaryExpression.h"
#include "../AST/GroupingExpression.h"
#include "../AST/LiteralExpression.h"
#include "../AST/UnaryExpression.h"
#include "../AST/VariableExpression.h"

namespace Noble::Compiler::Bytecode
{
    void BytecodeVisitor::GenerateOps(std::vector<AST::StatementPtr>& statements, Frame& frame)
    {
        if (statements.empty()) return;

        this->frame = &frame;
        for (const auto& statement : statements)
        {
            statement->Accept(this);
        }
    }

    std::any BytecodeVisitor::Visit(AST::BinaryExpression* binaryExpression)
    {
        binaryExpression->right->Accept(this);
        binaryExpression->left->Accept(this);

        //std::cout << binaryExpression->operation->ToString() << " ";
        switch (binaryExpression->operation->type)
        {
            case Token::Type::EqualEqual:   frame->WriteOp(Op::Code::Equal);        break;
            case Token::Type::GreaterEqual: frame->WriteOp(Op::Code::GreaterEqual); break;
            case Token::Type::LessEqual:    frame->WriteOp(Op::Code::LessEqual);    break;
            case Token::Type::Minus:        frame->WriteOp(Op::Code::Subtract);     break;
            case Token::Type::Plus:         frame->WriteOp(Op::Code::Add);          break;
            case Token::Type::Star:         frame->WriteOp(Op::Code::Multiply);     break;
            case Token::Type::Slash:        frame->WriteOp(Op::Code::Divide);       break;
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
            case AST::LiteralExpression::Type::Boolean: frame->WriteConstant(ToValue(std::get<bool>(literalExpression->data))); break;
            case AST::LiteralExpression::Type::Null:    frame->WriteConstant(NullValue); break;
            case AST::LiteralExpression::Type::Number:  frame->WriteConstant(ToValue(std::get<FloatType>(literalExpression->data))); break;
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
            case Token::Type::Bang:  frame->WriteOp(Op::Code::Not);    break;
            case Token::Type::Minus: frame->WriteOp(Op::Code::Negate); break;
            default: break;
        }
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::VariableExpression *variableExpression)
    {
        std::cout << "VAR: " << variableExpression->name << "\n";
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::ExpressionStatement* expressionStatement)
    {

    }

    std::any BytecodeVisitor::Visit(AST::VariableStatement* variableStatement)
    {

    }
}
