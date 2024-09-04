#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <any>

namespace Noble::Compiler::AST
{
    /**
     * @brief Abstract base class for expressions in the AST
     */
    struct Expression
    {
        virtual ~Expression() = default;
        virtual std::any Accept(struct ExpressionVisitor* visitor) = 0;
    };
} // Noble

#endif //EXPRESSION_H_INCLUDED
