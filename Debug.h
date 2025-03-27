#ifndef DEBUG_H
#define DEBUG_H

#include <sstream>
#include <fstream>
#include <iostream>
#include "NobleCore/Op.h"
#include "Frame.h"

namespace Noble::Compiler
{
    class Debug
    {
    public:
        static std::string OpToString(Noble::Core::Op::Code op);
        static bool MakeDebugFile(const Frame &frame, const std::string& name);
    };
} // Noble::Compiler

#endif //DEBUG_H
