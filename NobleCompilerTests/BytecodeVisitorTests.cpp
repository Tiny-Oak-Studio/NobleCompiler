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
    //Checks that visiting nothing works ok.
    Frame frame;
    BytecodeVisitor bytecodeVisitor;
    std::vector<AST::StatementPtr> statements;
    bytecodeVisitor.GenerateOps(statements, frame);
    EXPECT_EQ(frame.GetOps().Count(), 0);
}

TEST(BytecodeVisitor, NumericalStatement)
{
    //Check a numerical statement
    Lexer lexer;

    std::string testString = "(1 + 1) * 5 + 23.4 / 2;";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    std::vector<AST::StatementPtr> statements = parser.Parse(tokens);

    Frame generatedFrame;
    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(statements, generatedFrame);

    Frame manualFrame;
    manualFrame.WriteConstant(ToValue(static_cast<FloatType>(2)));
    manualFrame.WriteConstant(ToValue(static_cast<FloatType>(23.4)));
    manualFrame.WriteOp(Op::Code::Divide);
    manualFrame.WriteConstant(ToValue(static_cast<FloatType>(5)));
    manualFrame.WriteConstant(ToValue(static_cast<FloatType>(1)));
    manualFrame.WriteConstant(ToValue(static_cast<FloatType>(1)));
    manualFrame.WriteOp(Op::Code::Add);
    manualFrame.WriteOp(Op::Code::Multiply);
    manualFrame.WriteOp(Op::Code::Add);

    EXPECT_EQ(memcmp(manualFrame.GetOps().GetArray(), generatedFrame.GetOps().GetArray(), sizeof(Op::Type) * manualFrame.GetOps().Count()), 0);
}

TEST(BytecodeVisitor, NumericalStatementNoDecimals)
{
    Lexer lexer;
    const std::string testString = "(1 + 1) / 2 * 2 + 1;";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;

    std::vector<AST::StatementPtr> statements = parser.Parse(tokens);

    Frame frame;

    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(statements, frame);

    EXPECT_EQ(frame.GetConstants().Count(), 5);
}