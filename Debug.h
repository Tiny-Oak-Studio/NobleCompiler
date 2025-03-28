#ifndef DEBUG_H
#define DEBUG_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "NobleCore/Op.h"
#include "Frame.h"
#include "Token.h"

namespace Noble::Compiler
{
    class Debug
    {
    public:
        static std::string OpToString(Noble::Core::Op::Code op);
        static std::string TokenToString(const Noble::Compiler::Token& token);
        static bool MakeDebugFile(const Frame &frame, const std::string& name);
        static bool MakeTokenFile(const std::vector<Token>& tokens, const std::string& name);
    };
} // Noble::Compiler

#endif //DEBUG_H
