#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <stdfloat>
#include <string>

namespace Noble::Compiler
{
    struct Token
    {
        enum Type
        {
            //Single Char
            LeftParen, RightParen,
            LeftBrace, RightBrace,
            Comma, Dot, Minus, Plus,
            Semicolon, Slash, Star,
            //One or two char
            Bang, BangEqual,
            Equal, EqualEqual,
            Greater, GreaterEqual,
            Less, LessEqual,
            //Literals
            Identifier, String, Number,
            //Keywords
            And, Class, Else, False,
            For, Function, If, Null, Or,
            Print, Return, Super, This,
            True, Variable, While,

            //Error tokens
            Error, EndOfFile, None
        };

        Type type = None;

        const char* firstCharacter = nullptr;
        const char* lastCharacter = nullptr;

        Token() = default;
        Token(Type type, const char* firstChar, const char* lastChar);
        explicit Token(const std::string& errorMessage);

        [[nodiscard]] std::string ToString() const;
        [[nodiscard]] std::float64_t ToFloat() const;
    };
} // Noble::Compiler

#endif //TOKEN_H_INCLUDED
