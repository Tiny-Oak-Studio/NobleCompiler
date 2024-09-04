#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include <string>
#include "Lexer.h"
#include "Parser.h"

namespace Noble::Compiler
{
    class Compiler
    {
    public:
        ///@ brief Compiles Noble General-Purpose Language into Noble Assembly-Language
        bool Compile(const std::string& NGPLSource);
    private:
        std::string source;
    };
}

#endif //COMPILER_H_INCLUDED
