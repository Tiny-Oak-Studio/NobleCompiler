#ifndef EXPRESSION_H_INCLUDED
#define EXPRESSION_H_INCLUDED

#include <any>
#include <memory>

namespace Noble::Compiler::AST
{
    /**
     * @brief Abstract base class for expressions in the AST
     */
    struct Expression
    {
        enum Type
        {
            None,
            Binary,
            Grouping,
            Literal,
            Unary,
        };

        Type ExpressionType = None;
        virtual ~Expression() = default;
        virtual std::any Accept(struct ExpressionVisitor* visitor) = 0;
    };

    typedef std::unique_ptr<Expression> ExprPtr;
} // Noble

#endif //EXPRESSION_H_INCLUDED
