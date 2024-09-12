#include <gtest/gtest.h>
#include "../AST/Expression.h"
#include "../Token.h"
#include "../Lexer.h"
#include "../Parser.h"
#include "../NobleCore/Frame.h"
#include "../Bytecode/BytecodeVisitor.h"

using namespace Noble::Compiler::Bytecode;
using namespace Noble::Compiler;
using namespace Noble::Core;

TEST(BytecodeVisitor, Empty)
{
    Frame frame;
    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(nullptr, frame);
    EXPECT_EQ(frame.NumOps(), 0);
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

    EXPECT_NE(frame.NumOps(), 0);
    EXPECT_EQ(frame.ReadOp(0), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(5), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(10), Op::Code::Divide);
    EXPECT_EQ(frame.ReadOp(11), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(16), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(21), Op::Code::Constant);
    EXPECT_EQ(frame.ReadOp(26), Op::Code::Add);
    EXPECT_EQ(frame.ReadOp(27), Op::Code::Multiply);
    EXPECT_EQ(frame.ReadOp(28), Op::Code::Add);
}