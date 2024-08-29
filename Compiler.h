#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include <string>
#include "Lexer.h"

namespace Noble::Compiler
{
    class Compiler
    {
    public:
        ///@ brief Compiles Noble General-Purpose Language into Noble Assembly-Language
        bool Compile(const std::string& NGPLSource);
    };
}

#endif //COMPILER_H_INCLUDED
