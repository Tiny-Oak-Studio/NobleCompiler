#include <gtest/gtest.h>
#include "../Compiler.h"

/**
 * Full pipeline tests for the compiler
 */

TEST(CompilerTests, Empty)
{
    Noble::Compiler::Compiler compiler;
    compiler.Compile("", "test");
}

TEST(CompilerTests, Startup)
{
    Noble::Compiler::Compiler compiler;
    const std::string NGPLSource = "1 + 1 / 2;";
    compiler.Compile(NGPLSource, "test");
}


TEST(CompilerTests, GlobalVariableSum)
{
    Noble::Compiler::Compiler compiler;
    const std::string NGPLSource = "var test_var = 3; var test_a = 21; var test_b = test_var + test_b;";
    compiler.Compile(NGPLSource, "test");
}