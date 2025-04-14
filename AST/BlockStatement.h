#ifndef BLOCKSTATEMENT_H
#define BLOCKSTATEMENT_H

#include <vector>
#include "Statement.h"

namespace Noble::Compiler::AST
{
    struct BlockStatement final : Statement
    {
        std::vector<StatementPtr> statements;

        BlockStatement(std::vector<StatementPtr>& statementBlock);

        std::any Accept(StatementVisitor* statementVisitor) override;
    };
} // Noble::Compiler::AST

#endif //BLOCKSTATEMENT_H
