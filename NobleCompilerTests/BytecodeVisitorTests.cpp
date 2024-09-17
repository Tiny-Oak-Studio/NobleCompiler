#include <gtest/gtest.h>
#include "../AST/Expression.h"
#include "../Token.h"
#include "../Lexer.h"
#include "../Parser.h"
#include "../Frame.h"
#include "../Bytecode/BytecodeVisitor.h"

using namespace Noble::Compiler::Bytecode;
using namespace Noble::Compiler;

TEST(BytecodeVisitor, Empty)
{
    Frame frame;
    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(nullptr, frame);
    EXPECT_EQ(frame.GetOps().Count(), 0);
}

TEST(BytecodeVisitor, Startup)
{
    Lexer lexer;
    const std::string testString = "(1 + 1) * 5 + 23.4 / 2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    std::unique_ptr<AST::Expression> expr = parser.Parse(tokens);

    Frame frame;

    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(expr.get(), frame);

    constexpr uint8_t addrSize = sizeof(Address::Single);

    EXPECT_NE(frame.GetOps().Count(), 0);
    EXPECT_EQ(frame.ReadOp(0), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(addrSize + 1), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(2 * addrSize + 2), Op::Code::Divide);
    EXPECT_EQ(frame.ReadOp(2 * addrSize + 3), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(3 * addrSize + 4), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(4 * addrSize + 5), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(5 * addrSize + 6), Op::Code::Add);
    EXPECT_EQ(frame.ReadOp(5 * addrSize + 7), Op::Code::Multiply);
    EXPECT_EQ(frame.ReadOp(5 * addrSize + 8), Op::Code::Add);
}

TEST(BytecodeVisitor, NoDecimals)
{
    Lexer lexer;
    const std::string testString = "(1 + 1) / 2 * 2 + 1 ";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    std::unique_ptr<AST::Expression> expr = parser.Parse(tokens);

    Frame frame;

    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(expr.get(), frame);

    EXPECT_EQ(frame.GetConstants().Count(), 5);
}