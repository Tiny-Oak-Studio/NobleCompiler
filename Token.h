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

        /**
         * @brief Constructs a Token with Type::None, and a null character pointer with length == 0.
         */
        Token() = default;

        /**
         * @brief Creates a Token object with the specified type, character pointer and character length.
         * @param type The Token::Type the new Token instance will have.
         * @param firstChar Pointer to the first character of the Token instance in the source string.
         * @param length The number of source string characters pointed to by this Token instance.
         */
        Token(Type type, const char* firstChar, std::size_t length);

        /**
         * @brief Creates an error Token with the provided error message.
         * @param errorMessage The error message to be displayed when this Token is parsed.
         */
        explicit Token(const std::string& errorMessage);

        /**
         * @return Returns the string representation of this Token.
         */
        [[nodiscard]] std::string ToString() const;

        /**
         * @return Attempts to parse a float from the given token.
         */
        [[nodiscard]] Core::Runtime::FloatType ToFloat() const;
    };
}

#endif //TOKEN_H_INCLUDED
