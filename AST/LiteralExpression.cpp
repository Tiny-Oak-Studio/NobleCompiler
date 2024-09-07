#include "LiteralExpression.h"

namespace Noble::Compiler::AST
{
    LiteralExpression::LiteralExpression() :
        type(Type::Null)
    {}

    LiteralExpression::LiteralExpression(const std::string &value) :
        data(value),
        type(Type::String)
    {}

    LiteralExpression::LiteralExpression(const Core::Runtime::FloatType value) :
        data(value),
        type(Type::Number)
    {}

    LiteralExpression::LiteralExpression(const bool value) :
        data(value),
        type(Type::Boolean)
    {}

    std::any LiteralExpression::Accept(ExpressionVisitor* visitor)
    {
        return visitor->Visit(this);
    }

    std::string LiteralExpression::ToString()
    {
        switch (type)
        {
            case Null:    return "null";
            case String:  return std::get<std::string>(data);
            case Number:  return Conversions::ToString(std::get<Core::Runtime::FloatType>(data));
            case Boolean: return std::get<bool>(data) ? "true" : "false";
            default: return "";
        }
    }
}
