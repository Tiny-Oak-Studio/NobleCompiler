#include <gtest/gtest.h>
#include <vector>
#include "../Lexer.h"

using namespace Noble::Compiler;

TEST(Lexer, Empty)
{
    Lexer lexer;
    const std::string testString;
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::EndOfFile);
}

TEST(Lexer, SingleKeyword)
{
    Lexer lexer;
    const std::string testString = "function";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::Function);
}

TEST(Lexer, AllKeywords)
{
    Lexer lexer;
    const std::string testString = "and class else false for function if null or print return super this true var while";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::And);
    EXPECT_EQ(tokens[1].type, Token::Type::Class);
    EXPECT_EQ(tokens[2].type, Token::Type::Else);
    EXPECT_EQ(tokens[3].type, Token::Type::False);
    EXPECT_EQ(tokens[4].type, Token::Type::For);
    EXPECT_EQ(tokens[5].type, Token::Type::Function);
    EXPECT_EQ(tokens[6].type, Token::Type::If);
    EXPECT_EQ(tokens[7].type, Token::Type::Null);
    EXPECT_EQ(tokens[8].type, Token::Type::Or);
    EXPECT_EQ(tokens[9].type, Token::Type::Print);
    EXPECT_EQ(tokens[10].type, Token::Type::Return);
    EXPECT_EQ(tokens[11].type, Token::Type::Super);
    EXPECT_EQ(tokens[12].type, Token::Type::This);
    EXPECT_EQ(tokens[13].type, Token::Type::True);
    EXPECT_EQ(tokens[14].type, Token::Type::Variable);
    EXPECT_EQ(tokens[15].type, Token::Type::While);
}

TEST(Lexer, AllPunctuation)
{
    Lexer lexer;
    const std::string testString = ".,/<>{}()-+;";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::Dot);
    EXPECT_EQ(tokens[1].type, Token::Type::Comma);
    EXPECT_EQ(tokens[2].type, Token::Type::Slash);
    EXPECT_EQ(tokens[3].type, Token::Type::Less);
    EXPECT_EQ(tokens[4].type, Token::Type::Greater);
    EXPECT_EQ(tokens[5].type, Token::Type::LeftBrace);
    EXPECT_EQ(tokens[6].type, Token::Type::RightBrace);
    EXPECT_EQ(tokens[7].type, Token::Type::LeftParen);
    EXPECT_EQ(tokens[8].type, Token::Type::RightParen);
    EXPECT_EQ(tokens[9].type, Token::Type::Minus);
    EXPECT_EQ(tokens[10].type, Token::Type::Plus);
    EXPECT_EQ(tokens[11].type, Token::Type::Semicolon);
}

TEST(Lexer, String)
{
    Lexer lexer;
    const std::string testString = "\"this is a string\"";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::String);
    EXPECT_EQ(memcmp(firstCharacter, testString.c_str(), length), 0);
}

TEST(Lexer, NumberNoDecimals)
{
    Lexer lexer;
    const std::string testString = "734";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::Number);
    EXPECT_EQ(memcmp(firstCharacter, testString.c_str(), length), 0);
}

TEST(Lexer, LargeNumberNoDecimals)
{
    Lexer lexer;
    const std::string testString = "73473848529883498347698269823486";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::Number);
    EXPECT_EQ(memcmp(firstCharacter, testString.c_str(), length), 0);
}

TEST(Lexer, SmallDecimal)
{
    Lexer lexer;
    const std::string testString = "11.2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::Number);
    EXPECT_EQ(memcmp(firstCharacter, testString.c_str(), length), 0);
}

TEST(Lexer, SmallDecimalWithWhiteSpace)
{
    Lexer lexer;
    const std::string testString = "  11.2   ";
    const std::string expectedLexeme = "11.2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::Number);
    EXPECT_EQ(memcmp(firstCharacter, expectedLexeme.c_str(), length), 0);
}

TEST(Lexer, LargeDecimal)
{
    Lexer lexer;
    const std::string testString = "12384834683486845864858345884561.27573475374573457345734571910";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    auto [type, firstCharacter, length] = tokens[0];

    EXPECT_EQ(type, Token::Type::Number);
    EXPECT_EQ(memcmp(firstCharacter, testString.c_str(), length), 0);
}

TEST(Lexer, WrongNumberWithDecimal)
{
    Lexer lexer;
    const std::string testString = ".2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    //We expect three distinct token here, because the number parsing should not eat the decimal point
    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].type, Token::Type::Dot);
    EXPECT_EQ(tokens[1].type, Token::Type::Number);
    EXPECT_EQ(tokens[2].type, Token::Type::EndOfFile);
}

TEST(Lexer, WrongNumberWithoutDecimal)
{
    Lexer lexer;
    const std::string testString = "1.";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    //We expect three distinct token here, because the number parsing should not eat the decimal point
    EXPECT_EQ(tokens.size(), 3);
    EXPECT_EQ(tokens[0].type, Token::Type::Number);
    EXPECT_EQ(tokens[1].type, Token::Type::Dot);
    EXPECT_EQ(tokens[2].type, Token::Type::EndOfFile);
}

TEST(Lexer, UnknownCharacter)
{
    Lexer lexer;
    const std::string testString = "|";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    EXPECT_EQ(tokens[0].type, Token::Type::Error);
}