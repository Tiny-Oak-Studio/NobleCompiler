#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include <any>

namespace Noble::Compiler::AST
{
    struct Statement
    {
        virtual ~Statement() = default;

        virtual std::any Accept(struct StatementVisitor* statementVisitor) = 0;
    };

    typedef std::unique_ptr<Statement> StatementPtr;
} // Noble::Compiler::AST

#endif //STATEMENT_H
