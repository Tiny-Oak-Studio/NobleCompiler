#include "BytecodeVisitor.h"

#include "../AST/BinaryExpression.h"
#include "../AST/ExpressionStatement.h"
#include "../AST/GroupingExpression.h"
#include "../AST/LiteralExpression.h"
#include "../AST/UnaryExpression.h"
#include "../AST/VariableExpression.h"
#include "../AST/VariableStatement.h"

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

    std::any BytecodeVisitor::Visit(AST::VariableExpression* variableExpression)
    {
        const Address::Single globalVarAddr = GetGlobalVariable(variableExpression->name->ToString());
        frame->WriteOp(Op::Code::GetGlobal);
        frame->WriteAddress(globalVarAddr);
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::ExpressionStatement* expressionStatement)
    {
        expressionStatement->expression->Accept(this);
        frame->WriteOp(Op::Code::Pop);
        return 0;
    }

    std::any BytecodeVisitor::Visit(AST::VariableStatement* variableStatement)
    {
        //Define Variable
        if (variableStatement->initialiser)
        {
            variableStatement->initialiser->Accept(this);
        }
        else
        {
            frame->WriteOp(Op::Code::Null);
        }
        DefineVariable(variableStatement->name->ToString());
        return 0;
    }

    void BytecodeVisitor::DefineVariable(const std::string& name)
    {
        frame->WriteOp(Op::Code::DefineGlobal);
        //If the global is already defined then we redefine it using the same address
        frame->WriteAddress(globalVariables.contains(name) ? globalVariables[name] : nextGlobalAddress);

        //Map the global var to its address for later access.
        globalVariables[name] = nextGlobalAddress++;
    }

    Address::Single BytecodeVisitor::GetGlobalVariable(const std::string &name)
    {
        if (!globalVariables.contains(name))
        {
            throw Exceptions::ByteCodeVisitorException("Variable with name '" + name + "' has not been defined.");
        }
        return globalVariables[name];
    }
}
