#ifndef NOBLE_COMPILER_PARSER_H_INCLUDED
#define NOBLE_COMPILER_PARSER_H_INCLUDED

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include "Token.h"
#include "AST/ExpressionTypes.h"
#include "AST/Statement.h"
#include "AST/ExpressionStatement.h"
#include "AST/PrintStatement.h"

namespace Noble::Compiler
{
    class Parser
    {
    public:
        std::vector<AST::StatementPtr> Parse(const std::vector<Token>& tokens);
    protected:
        std::vector<Token> tokens;
        std::size_t currentToken = 0;

        [[nodiscard]] const Token* Peek(int offset = 0) const;
        [[nodiscard]] const Token* Previous() const;
        [[nodiscard]] bool AtEndOfFile() const;
        [[nodiscard]] bool Check(Token::Type type) const;

        bool Match(std::initializer_list<Token::Type> types);
        const Token* Advance();
        const Token* Consume(Token::Type type, const std::string& message);
        void Synchronise();

        AST::ExprPtr Expression();
        AST::StatementPtr Statement();
        AST::StatementPtr ExpressionStatement();
        AST::StatementPtr PrintStatement();
        AST::ExprPtr Equality();
        AST::ExprPtr Comparison();
        AST::ExprPtr Term();
        AST::ExprPtr Factor();
        AST::ExprPtr Unary();
        AST::ExprPtr Primary();
    };
} // Noble::Compiler

#endif //NOBLE_COMPILER_PARSER_H_INCLUDED
