#ifndef NOBLE_COMPILER_LEXER_H_INCLUDED
#define NOBLE_COMPILER_LEXER_H_INCLUDED

#include <vector>  //For std::vector
#include <string>  //For std::string
#include <cstring> //For std::memcmp
#include <cctype>  //For std::isdigit, std::isalpha
#include "Token.h" //For Nobel::Compiler::Token

namespace Noble::Compiler
{
    /**
     * @brief Scans Noble General Purpose Language and produces the corresponding Noble Intermediary Tokens.
     *
     * The Lexer scans and produces tokens for the provided NGPL source string, but does no checks to ensure
     * the provided string *is* valid NGPL source - The Lexing phase is intended to be completely distinct from the following
     * Compilation phase where the tokens are then verified to be valid NGPL grammar.
     *
     * This is mostly to reduce coupling and allow for an additional token optimization phase at a later date.
     */
    class Lexer
    {
    public:
        /**
         * @brief Scans the given NGPL string and produces the appropriate list of Tokens
         * @param NGPLSource A string containing NGPL source code.
         * @return An ordered list of Tokens corresponding to the Tokens detected in the provided source.
         *
         * This function produces the entire token stream at once and stuffs in a vector. This
         * *may* be a problem for very large sources that require a lot of memory but there is
         * no plan to address this until it becomes necessary.
         */
        [[nodiscard]] std::vector<Token> Lex(const std::string& NGPLSource);
    protected:
        /**
         * @brief Produces the next Token in the stream for the provided source.
         * @return The next Token in the stream, starting at the scan-head.
         *
         * This method shifts the scan-heads along by one token and returns the token that
         * was just read.
         */
        Token ReadToken();

        /**
         * @brief Convenience method for making a Token of the specified type at the current scan-head position
         * @return A token with the given type, with its first and last chars pointers set to the lexer's scan-heads.
         * @param type The Token::Type the created Token should have.
         */
        [[nodiscard]] Token MakeToken(Token::Type type) const;

        /**
         * @brief Reads the next character in the source sequence.
         * @return The next character in the sequence.
         *
         * Side effect: This moves the current scan-head forward by one character.
         */
        char ReadCharacter();

        /**
         * @brief Checks if we've reached the end of the source string.
         * @return True if the current scan-head is pointer to a null char '\0', otherwise false.
         **/
        [[nodiscard]] bool AtEndOfFile() const;

        /**
         * @brief Checks if the next character in the source sequence matches the given char.
         * @param c The character to match against the next character in the source sequence.
         * @return True if the current scan-head points to a character matching the given character, otherwise false.
         *
         * Side effect: Moves the current scan-head forward if a match is detected.
         *
         * No discard: If you want to move the current scan-head forward by a character, use Lexer::ReadCharacter
         * instead - This method is intended only to match multi-character tokens and so the return value
         * should not be discarded.
         */
        [[nodiscard]] bool MatchNext(char c);

        /**
         * @brief Moves the current scan-head forward until it's no longer pointing at whitespace.
         */
        void SkipWhitespace();

        /**
         * @brief Returns a character relative to the current scan-head without moving the scan-head.
         * @param offset The number of characters forward/back to look from the current scan-head.
         * @return The character at the specified offset from the current scan-head.
         */
        [[nodiscard]] char Peek(int offset = 0) const;

        /// @brief Creates a string token, starting at the current scan-head
        [[nodiscard]] Token ReadString();

        /// @brief Create a number token, starting at the current scan-head
        [[nodiscard]] Token ReadNumber();

        /// @brief Reads an identifier from the current scan-head
        [[nodiscard]] Token ReadIdentifier();

        /// @brief Gets the type of the identifier at the scan-head
        [[nodiscard]] Token::Type GetIdentifierType() const;

        /// @brief Checks if a sequence matches a NGPL keyword
        [[nodiscard]] Token::Type KeywordCheck(int offset, const std::string& rest, Token::Type type) const;

        const char* startScanHead = nullptr;
        const char* currentScanHead = nullptr;
    };
} // Noble::Compiler

#endif //NOBLE_COMPILER_LEXER_H_INCLUDED
