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
    const std::string testString = "1";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::Number);

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);

    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "1");
}


TEST(Parser, SingleLargeNumberLiteral)
{
    Lexer lexer;
    const std::string testString = "1237361267189716718399";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);

    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "1.23736e+21");
}

TEST(Parser, UnaryAndLiteral)
{
    Lexer lexer;
    const std::string testString = "-1";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(- 1)");
}

TEST(Parser, BinaryAdd)
{
    Lexer lexer;
    const std::string testString = "2 * 4";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(* 2 4)");
}

TEST(Parser, TwoTerms)
{
    Lexer lexer;
    const std::string testString = "2 * 4 + 5 * 2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(+ (* 2 4) (* 5 2))");
}

TEST(Parser, Grouping)
{
    Lexer lexer;
    const std::string testString = "2 * (3 + 2)";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(* 2 (group (+ 3 2)))");
}

TEST(Parser, DecimalUnaryTermsWithGrouping)
{
    Lexer lexer;
    const std::string testString = "3442.45545 * (3.3 + 2.111) * 33";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);
    EXPECT_NE(expr, nullptr);

    AST::Printer printer;
    EXPECT_EQ(printer.Print(expr), "(* 3442.46 (group (+ 3.3 2.111)))");
}