#include "Parser.h"

#include "Exceptions/ParseException.h"

namespace Noble::Compiler
{
    std::unique_ptr<AST::Expression> Parser::Parse(const std::vector<Token>& tokens)
    {
        this->tokens = tokens;
        currentToken = 0;

        return std::move(Expression());

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

    std::unique_ptr<AST::Expression> Parser::Expression()
    {
        return Equality();
    }

    std::unique_ptr<AST::Expression> Parser::Equality()
    {
        std::unique_ptr<AST::Expression> expr = Comparison();
        while (Match({Token::Type::BangEqual, Token::Type::EqualEqual}))
        {
            const Token* operation = Previous();
            std::unique_ptr<AST::Expression> right = Comparison();
            expr = std::make_unique<AST::BinaryExpression>(expr, operation, right);
        }
        return expr;
    }

    std::unique_ptr<AST::Expression> Parser::Comparison()
    {
        std::unique_ptr<AST::Expression> expr = Term();
        while (Match({Token::Type::Greater, Token::Type::GreaterEqual, Token::Type::Less, Token::Type::LessEqual}))
        {
            const Token* operation = Previous();
            std::unique_ptr<AST::Expression> right = Term();
            return std::make_unique<AST::BinaryExpression>(expr, operation, right);
        }
        return expr;
    }

    std::unique_ptr<AST::Expression> Parser::Term()
    {
        std::unique_ptr<AST::Expression> expr = Factor();
        while (Match({Token::Type::Plus, Token::Type::Minus}))
        {
            const Token* operation = Previous();
            std::unique_ptr<AST::Expression> right = Factor();
            return std::make_unique<AST::BinaryExpression>(expr, operation, right);
        }
        return expr;
    }

    std::unique_ptr<AST::Expression> Parser::Factor()
    {
        std::unique_ptr<AST::Expression> expr = Unary();
        while (Match({Token::Type::Slash, Token::Type::Star}))
        {
            const Token* operation = Previous();
            std::unique_ptr<AST::Expression> right = Unary();
            return std::make_unique<AST::BinaryExpression>(expr, operation, right);
        }
        return expr;
    }

    std::unique_ptr<AST::Expression> Parser::Unary()
    {
        if (Match({Token::Type::Bang, Token::Type::Minus}))
        {
            const Token* operation = Previous();
            std::unique_ptr<AST::Expression> right = Unary();
            return std::make_unique<AST::UnaryExpression>(operation, right);
        }
        return Primary();
    }

    std::unique_ptr<AST::Expression> Parser::Primary()
    {
        if (Match({Token::Type::False}))
        {
            return std::make_unique<AST::LiteralExpression>(false);
        }
        if (Match({Token::Type::True}))
        {
            return std::make_unique<AST::LiteralExpression>(true);
        }
        if (Match({Token::Type::Null}))
        {
            return std::make_unique<AST::LiteralExpression>();
        }
        if (Match({Token::Type::Number}))
        {
            return std::make_unique<AST::LiteralExpression>(Previous()->ToFloat());
        }
        if (Match({Token::Type::String}))
        {
            return std::make_unique<AST::LiteralExpression>(Previous()->ToString());
        }
        if (Match({Token::Type::LeftParen}))
        {
            std::unique_ptr<AST::Expression> expr = Expression();
            Consume(Token::Type::RightParen, "Expecting ')' after expression.");
            return std::make_unique<AST::GroupingExpression>(expr);
        }
        return nullptr;
    }
}
