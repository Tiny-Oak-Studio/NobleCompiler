#ifndef STATEMENTVISITOR_H
#define STATEMENTVISITOR_H

#include <any>

namespace Noble::Compiler::AST
{
    struct StatementVisitor
    {
        virtual ~StatementVisitor() = default;
        virtual std::any Visit(struct VariableStatement* variableStatement) = 0;
        virtual std::any Visit(struct ExpressionStatement* statement) = 0;
        virtual std::any Visit(struct BlockStatement* blockStatement) = 0;
        virtual std::any Visit(struct IfStatement* ifStatement) = 0;
        virtual std::any Visit(struct WhileStatement* whileStatement) = 0;
        virtual std::any Visit(struct ForStatement* forStatement) = 0;
    };
} //Noble::Compiler::AST

#endif //STATEMENTVISITOR_H
