#include "Parser.h"

#include "Exceptions/ParseException.h"

namespace Noble::Compiler
{
    AST::Expression* Parser::Parse(const std::vector<Token>& tokens)
    {
        this->tokens = tokens;
        expressions.clear();
        currentToken = 0;

        return Expression();

        /*
        try
        {
            return Expression();
        }
        catch (std::exception& e)
        {
            std::cout << "ERROR: " << e.what() << "\n";
            return nullptr;
        }*/
    }

    const Token* Parser::Peek(const int offset) const
    {
        return &tokens[currentToken + offset];
    }

    const Token* Parser::Previous() const
    {
        return &tokens[currentToken - 1];
    }

    bool Parser::AtEndOfFile() const
    {
        return Peek()->type == Token::Type::EndOfFile;
    }

    bool Parser::Check(const Token::Type type) const
    {
        if (AtEndOfFile()) return false;
        return Peek()->type == type;
    }

    bool Parser::Match(const std::initializer_list<Token::Type> types)
    {
        for (const auto type : types)
        {
            if (Check(type))
            {
                Advance();
                return true;
            }
        }
        return false;
    }

    const Token* Parser::Advance()
    {
        if (!AtEndOfFile()) currentToken++;
        return Previous();
    }

    const Token* Parser::Consume(const Token::Type type, const std::string &message)
    {
        if (Check(type)) return Advance();

        throw Exceptions::ParseException();
    }

    void Parser::Synchronise()
    {
        Advance();
        while (!AtEndOfFile())
        {
            if (Peek(-1)->type == Token::Type::Semicolon) return;
            switch (Peek()->type)
            {
                case Token::Type::Class:
                case Token::Type::Function:
                case Token::Type::Variable:
                case Token::Type::For:
                case Token::Type::If:
                case Token::Type::While:
                case Token::Type::Print:
                case Token::Type::Return:
                    return;
            }
            Advance();
        }
    }

    AST::Expression* Parser::Expression()
    {
        return Equality();
    }

    AST::Expression* Parser::Equality()
    {
        AST::Expression* expr = Comparison();
        while (Match({Token::Type::BangEqual, Token::Type::EqualEqual}))
        {
            const Token* operation = Previous();
            AST::Expression* right = Comparison();
            expressions.emplace_back(std::make_unique<AST::BinaryExpression>(expr, operation, right));
            expr = expressions.back().get();
        }
        return expr;
    }

    AST::Expression* Parser::Comparison()
    {
        AST::Expression* expr = Term();
        while (Match({Token::Type::Greater, Token::Type::GreaterEqual, Token::Type::Less, Token::Type::LessEqual}))
        {
            const Token* operation = Previous();
            AST::Expression* right = Term();
            expressions.emplace_back(std::make_unique<AST::BinaryExpression>(expr, operation, right));
            return expressions.back().get();
        }
        return expr;
    }

    AST::Expression* Parser::Term()
    {
        AST::Expression* expr = Factor();
        while (Match({Token::Type::Plus, Token::Type::Minus}))
        {
            const Token* operation = Previous();
            AST::Expression* right = Factor();
            expressions.emplace_back(std::make_unique<AST::BinaryExpression>(expr, operation, right));
            return expressions.back().get();
        }
        return expr;
    }

    AST::Expression* Parser::Factor()
    {
        AST::Expression* expr = Unary();
        while (Match({Token::Type::Slash, Token::Type::Star}))
        {
            const Token* operation = Previous();
            AST::Expression* right = Unary();
            expressions.emplace_back(std::make_unique<AST::BinaryExpression>(expr, operation, right));
            return expressions.back().get();
        }
        return expr;
    }

    AST::Expression* Parser::Unary()
    {
        if (Match({Token::Type::Bang, Token::Type::Minus}))
        {
            const Token* operation = Previous();
            AST::Expression* right = Unary();
            expressions.emplace_back(std::make_unique<AST::UnaryExpression>(operation, right));
            return expressions.back().get();
        }
        return Primary();
    }

    AST::Expression* Parser::Primary()
    {
        if (Match({Token::Type::False}))
        {
            expressions.emplace_back(std::make_unique<AST::LiteralExpression>(false));
            return expressions.back().get();
        }
        if (Match({Token::Type::True}))
        {
            expressions.emplace_back(std::make_unique<AST::LiteralExpression>(true));
            return expressions.back().get();
        }
        if (Match({Token::Type::Null}))
        {
            expressions.emplace_back(std::make_unique<AST::LiteralExpression>());
            return expressions.back().get();
        }
        if (Match({Token::Type::Number}))
        {
            expressions.emplace_back(std::make_unique<AST::LiteralExpression>(Previous()->ToFloat()));
            return expressions.back().get();
        }
        if (Match({Token::Type::String}))
        {
            expressions.emplace_back(std::make_unique<AST::LiteralExpression>(Previous()->ToString()));
            return expressions.back().get();
        }
        if (Match({Token::Type::LeftParen}))
        {
            AST::Expression* expr = Expression();
            Consume(Token::Type::RightParen, "Expecting ')' after expression.");
            expressions.emplace_back(std::make_unique<AST::GroupingExpression>(expr));
            return expressions.back().get();
        }
        return nullptr;
    }
}
