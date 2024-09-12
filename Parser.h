#ifndef NOBLE_COMPILER_PARSER_H_INCLUDED
#define NOBLE_COMPILER_PARSER_H_INCLUDED

#include <vector>
#include <memory>
#include <iostream>
#include <initializer_list>
#include "Token.h"
#include "AST/ExpressionTypes.h"

namespace Noble::Compiler
{
    class Parser
    {
    public:
        std::unique_ptr<AST::Expression> Parse(const std::vector<Token>& tokens);
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

        std::unique_ptr<AST::Expression> Expression();
        std::unique_ptr<AST::Expression> Equality();
        std::unique_ptr<AST::Expression> Comparison();
        std::unique_ptr<AST::Expression> Term();
        std::unique_ptr<AST::Expression> Factor();
        std::unique_ptr<AST::Expression> Unary();
        std::unique_ptr<AST::Expression> Primary();
    };
} // Noble::Compiler

#endif //NOBLE_COMPILER_PARSER_H_INCLUDED
