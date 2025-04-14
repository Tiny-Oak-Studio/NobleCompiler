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
    const std::string NGPLSource = "var testVar = 3; var testA = 21; var testB = testVar + testA;";
    compiler.Compile(NGPLSource, "test");
}