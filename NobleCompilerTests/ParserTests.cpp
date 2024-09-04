#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../Parser.h"
#include "../Lexer.h"
#include "../AST/Printer.h"

using namespace Noble::Compiler;

TEST(Parser, SingleNumberLiteral)
{
    Lexer lexer;
    const std::vector<Token> tokens = lexer.Lex("1");

    EXPECT_EQ(tokens[0].type, Token::Type::Number);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);

    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "1");
}

TEST(Parser, UnaryAndLiteral)
{
    Lexer lexer;
    const std::vector<Token> tokens = lexer.Lex("-1");
    EXPECT_EQ(tokens[0].type, Token::Type::Minus);
    EXPECT_EQ(tokens[1].type, Token::Type::Number);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(- 1)");
}

TEST(Parser, BinaryAdd)
{
    Lexer lexer;
    const std::vector<Token> tokens = lexer.Lex("2 * 4");
    EXPECT_EQ(tokens[0].type, Token::Type::Number);
    EXPECT_EQ(tokens[1].type, Token::Type::Star);
    EXPECT_EQ(tokens[2].type, Token::Type::Number);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(* 2 4)");
}

TEST(Parser, TwoTerms)
{
    Lexer lexer;
    const std::vector<Token> tokens = lexer.Lex("2 * 4 + 5 * 2");
    EXPECT_EQ(tokens[0].type, Token::Type::Number);
    EXPECT_EQ(tokens[1].type, Token::Type::Star);
    EXPECT_EQ(tokens[2].type, Token::Type::Number);
    EXPECT_EQ(tokens[3].type, Token::Type::Plus);
    EXPECT_EQ(tokens[4].type, Token::Type::Number);
    EXPECT_EQ(tokens[5].type, Token::Type::Star);
    EXPECT_EQ(tokens[6].type, Token::Type::Number);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(+ (* 2 4) (* 5 2))");
}

TEST(Parser, Grouping)
{
    Lexer lexer;
    const std::vector<Token> tokens = lexer.Lex("2 * (3 + 2)");
    EXPECT_EQ(tokens[0].type, Token::Type::Number);
    EXPECT_EQ(tokens[1].type, Token::Type::Star);
    EXPECT_EQ(tokens[2].type, Token::Type::LeftParen);
    EXPECT_EQ(tokens[3].type, Token::Type::Number);
    EXPECT_EQ(tokens[4].type, Token::Type::Plus);
    EXPECT_EQ(tokens[5].type, Token::Type::Number);
    EXPECT_EQ(tokens[6].type, Token::Type::RightParen);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(* 2 (group (+ 3 2)))");
}