#include "ByteCodeVisitorException.h"

namespace Noble::Compiler::Exceptions
{
    ByteCodeVisitorException::ByteCodeVisitorException(const std::string &errorMessage)
    {
        error = errorMessage;
    }
} // Noble::Compiler::Exceptions