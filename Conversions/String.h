#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <sstream>

namespace Noble::Compiler::Conversions
{
    template <typename T>
    std::string ToString(const T& value)
    {
        std::stringstream ss;
        ss << value;
        return ss.str();
    }

    template <typename T>
    T FromString(const std::string& str)
    {
        std::stringstream ss(str);
        T value;
        ss >> value;
        return value;
    }
}

#endif //STRING_H_INCLUDED
