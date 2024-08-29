#ifndef NOBLE_COMPILER_LEXER_H_INCLUDED
#define NOBLE_COMPILER_LEXER_H_INCLUDED

#include <vector>
#include <string>
#include <cstring>
#include "Token.h"

namespace Noble::Compiler
{
    /**
     * @brief Scans Noble General Purpose Language and produces the corresponding Tokens.
     */
    class Lexer
    {
    public:
        /// @brief Scans the given NGPL string and produces the appropriate list of Tokens
        std::vector<Token> Lex(const std::string& NGPLSource);
    protected:
        /// @brief Produces the next token for the given source string
        Token ReadToken();

        /// @brief Creates a Token of the specified type at the current lexing position
        Token MakeToken(Token::Type type) const;

        /// @brief Makes an error-type token that contains the given message
        Token MakeErrorToken(const std::string& errorMessage) const;

        /// @brief Returns the next character in the source sequence
        char ReadCharacter();

        /// @brief Checks if we've reached the end of the source string
        bool AtEndOfFile() const;

        /// @brief Returns true if the next token in sequence matches the expected one
        bool MatchNext(char c);

        /// @brief Checks if the given character is a numeric digit
        static bool IsDigit(char c);

        /// @brief Checks if the given character is a letter
        static bool IsAlpha(char c);

        /// @brief Checks if the given is either a number or letter
        static bool IsAlphaNumeric(char c);

        /// @brief Scans ahead until we hit a non-whitespace character
        void SkipWhitespace();

        /// @brief Returns a character relative to the current scan-head without moving the scan-head
        char Peek(int offset = 0) const;

        /// @brief Creates a string token, starting at the current scan-head
        Token ReadString();

        /// @brief Create a number token, starting at the current scan-head
        Token ReadNumber();

        /// @brief Reads an identifier from the current scan-head
        Token ReadIdentifier();

        /// @brief Gets the type of the identifier at the scan-head
        Token::Type GetIdentifierType();

        /// @brief Checks if a sequence matches a NGPL keyword
        Token::Type KeywordCheck(int offset, const std::string& rest, Token::Type type) const;

        const char* startCharacter = nullptr;
        const char* currentCharacter = nullptr;
    };
} // Noble::Compiler

#endif //NOBLE_COMPILER_LEXER_H_INCLUDED
