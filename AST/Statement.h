#ifndef STATEMENT_H
#define STATEMENT_H

#include <memory>
#include "Expression.h"

namespace Noble::Compiler::AST
{
    struct Statement
    {
        enum Type
        {
            None,
            Expression,
            Print
        };

        Statement(ExprPtr& expr);
        virtual ~Statement() = default;

        Type StatementType = None;
        ExprPtr expression;
    };

    typedef std::unique_ptr<Statement> StatementPtr;
} // Noble::Compiler::AST

#endif //STATEMENT_H
