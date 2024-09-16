#include <gtest/gtest.h>
#include "../Compiler.h"

/**
 * Full pipeline tests for the compiler
 */

TEST(CompilerTests, Startup)
{
    Noble::Compiler::Compiler compiler;
    const std::string NGPLSource = "(1 + 1) / 2 * 2 + 1 ";
    compiler.Compile(NGPLSource);
}
