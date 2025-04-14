#include "BlockStatement.h"
#include "StatementVisitor.h"

namespace Noble::Compiler::AST
{
    BlockStatement::BlockStatement(std::vector<StatementPtr> &statementBlock)
    {
        for (auto & statement : statementBlock)
        {
            statements.emplace_back(std::move(statement));
        }
        statementBlock.clear();
    }

    std::any BlockStatement::Accept(StatementVisitor *statementVisitor)
    {
        return statementVisitor->Visit(this);
    }
} // Noble::Compiler::AST