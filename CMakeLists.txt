cmake_minimum_required(VERSION 3.5)
project(NobleCompiler)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_EXTRACT_TIMESTAMP true
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        NobleCompilerTests
        Frame.cpp
        Frame.h
        Lexer.cpp
        Lexer.h
        Parser.cpp
        Parser.h
        Compiler.cpp
        Compiler.h
        Token.cpp
        Token.h
        AST/Expression.cpp
        AST/Expression.h
        AST/ExpressionVisitor.h
        AST/BinaryExpression.cpp
        AST/BinaryExpression.h
        AST/GroupingExpression.cpp
        AST/GroupingExpression.h
        AST/UnaryExpression.cpp
        AST/UnaryExpression.h
        AST/LiteralExpression.h
        AST/LiteralExpression.cpp
        AST/ExpressionTypes.h
        AST/Printer.cpp
        AST/Printer.h
        Exceptions/ParseException.cpp
        Exceptions/ParseException.h
        Conversions/String.cpp
        Conversions/String.h
        Bytecode/BytecodeVisitor.cpp
        Bytecode/BytecodeVisitor.h
        NobleCore/Frame.cpp
        NobleCore/Frame.h
        NobleCore/Translation.cpp
        NobleCore/Translation.h
        NobleCore/Value.cpp
        NobleCore/Value.h
        NobleCompilerTests/NobleCompilerTests.cpp
        NobleCompilerTests/LexerTests.cpp
        NobleCompilerTests/CompilerTests.cpp
        NobleCompilerTests/ASTTests.cpp
        NobleCompilerTests/ParserTests.cpp
        NobleCompilerTests/BytecodeVisitorTests.cpp
        Debug/FramePrinter.cpp
        Debug/FramePrinter.h
        Optimisations/ConstantFoldingVisitor.cpp
        Optimisations/ConstantFoldingVisitor.h
)

target_link_libraries(
        NobleCompilerTests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NobleCompilerTests)
