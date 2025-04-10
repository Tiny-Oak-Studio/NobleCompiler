#ifndef BYTECODEVISITOR_H_INCLUDED
#define BYTECODEVISITOR_H_INCLUDED

#include <any>
#include <vector>
#include <unordered_map>

#include "../Frame.h"
#include "../AST/ExpressionVisitor.h"
#include "../AST/Statement.h"
#include "../AST/StatementVisitor.h"
#include "../Exceptions/ByteCodeVisitorException.h"

namespace Noble::Compiler::Bytecode
{
    class BytecodeVisitor final : public AST::ExpressionVisitor, public AST::StatementVisitor
    {
    public:
        void GenerateOps(std::vector<AST::StatementPtr>& statements, Frame& frame);
    protected:
        Frame* frame = nullptr;
        std::unordered_map<std::string, Address::Single> globalVariables;
        Address::Single nextGlobalAddress = 0;

        //ExpressionVisitor
        std::any Visit(AST::BinaryExpression* binaryExpression) override;
        std::any Visit(AST::GroupingExpression* groupingExpression) override;
        std::any Visit(AST::LiteralExpression* literalExpression) override;
        std::any Visit(AST::UnaryExpression* unaryExpression) override;
        std::any Visit(AST::VariableExpression* variableExpression) override;

        //StatementVisitor
        std::any Visit(AST::ExpressionStatement* expressionStatement) override;
        std::any Visit(AST::VariableStatement* variableStatement) override;

        //Helper methods
        /// @brief Adds a named global variable to the global variables table and assigns it an address.
        void DefineVariable(const std::string& name);
        Address::Single GetGlobalVariable(const std::string& name);
    };
}

#endif //BYTECODEVISITOR_H_INCLUDED
