#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

#include <string>
#include "Conversions/String.h"
#include "NobleCore/Value.h"

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
        std::size_t length = 0;

        Token() = default;
        Token(Type type, const char* firstChar, std::size_t length);
        explicit Token(const std::string& errorMessage);

        [[nodiscard]] std::string ToString() const;
        [[nodiscard]] Core::Runtime::FloatType ToFloat() const;
    };
}

#endif //TOKEN_H_INCLUDED
