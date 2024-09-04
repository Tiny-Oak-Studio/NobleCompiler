#include "Compiler.h"

namespace Noble::Compiler
{
    bool Compiler::Compile(const std::string& NGPLSource)
    {
        //We use the compiler's copy of the source and keep it around as long as the compiler it around
        //because the Lexer and Parser's Tokens point directly to the source for their lexemes.
        source = NGPLSource;

        Lexer lexer;
        Parser parser;

        parser.Parse(lexer.Lex(source.c_str()));

        return false;
    }
}
