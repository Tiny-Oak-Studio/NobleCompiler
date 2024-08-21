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
        NobleCompilerTests/NobleCompilerTests.cpp
        Lexer.cpp
        Lexer.h
        NobleCompilerTests/LexerTests.cpp
        Parser.cpp
        Parser.h
)
target_link_libraries(
        NobleCompilerTests
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(NobleCompilerTests)
