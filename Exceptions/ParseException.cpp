#include "ParseException.h"

namespace Noble::Compiler::Exceptions
{
    ParseException::ParseException(const std::string &errorMessage)
    {
        error = errorMessage;
    }

}