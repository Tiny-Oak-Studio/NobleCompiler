#include <gtest/gtest.h>
#include "../AST/Expression.h"
#include "../Token.h"
#include "../Lexer.h"
#include "../Parser.h"
#include "../NobleCore/Frame.h"
#include "../Bytecode/BytecodeVisitor.h"

using namespace Noble::Compiler::Bytecode;
using namespace Noble::Compiler;

TEST(BytecodeVisitor, Startup)
{
    Lexer lexer;
    const std::string testString = "(1 + 1) * 5 + 23.4 / 2";
    const std::vector<Token> tokens = lexer.Lex(testString.c_str());

    Parser parser;
    AST::Expression* expr = parser.Parse(tokens);

    Noble::Core::Frame frame;

    BytecodeVisitor bytecodeVisitor;
    bytecodeVisitor.GenerateOps(expr, frame);
}