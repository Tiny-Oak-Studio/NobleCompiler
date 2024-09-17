#ifndef COMPILER_H_INCLUDED
#define COMPILER_H_INCLUDED

#include <string>
#include <fstream>
#include "Lexer.h"
#include "Parser.h"
#include "Frame.h"

namespace Noble::Compiler
{
    class Compiler
    {
    public:
        ///@ brief Compiles Noble General-Purpose Language into Noble Assembly-Language
        bool Compile(const std::string& NGPLSource);
        static bool WriteFrame(const Frame& frame, const std::string& name);
    private:
        std::string source;
    };
}

#endif //COMPILER_H_INCLUDED
