#include "Lexer.h"

namespace Noble::Compiler
{
    std::vector<Token> Lexer::Lex(const std::string &NGPLSource)
    {
        std::vector<Token> tokens;
        startCharacter = currentCharacter = &NGPLSource[0];

        Token token;
        while (token.type != Token::Type::EndOfFile)
        {
            SkipWhitespace();
            token = ReadToken();
            tokens.emplace_back(token);
        }

        return tokens;
    }

    Token Lexer::ReadToken()
    {
        startCharacter = currentCharacter;

        if (AtEndOfFile()) return MakeToken(Token::Type::EndOfFile);

        const char c = ReadCharacter();
        if (IsAlpha(c)) return ReadIdentifier();
        if (IsDigit(c)) return ReadNumber();

        switch (c)
        {
            case '(': return MakeToken(Token::Type::LeftParen);
            case ')': return MakeToken(Token::Type::RightParen);
            case '{': return MakeToken(Token::Type::LeftBrace);
            case '}': return MakeToken(Token::Type::RightBrace);
            case ';': return MakeToken(Token::Type::Semicolon);
            case ',': return MakeToken(Token::Type::Comma);
            case '.': return MakeToken(Token::Type::Dot);
            case '-': return MakeToken(Token::Type::Minus);
            case '+': return MakeToken(Token::Type::Plus);
            case '/': return MakeToken(Token::Type::Slash);
            case '*': return MakeToken(Token::Type::Star);

            case '!': return MakeToken(MatchNext('=') ? Token::Type::BangEqual : Token::Type::Bang);
            case '=': return MakeToken(MatchNext('=') ? Token::Type::EqualEqual : Token::Type::Equal);
            case '<': return MakeToken(MatchNext('=') ? Token::Type::LessEqual : Token::Type::Less);
            case '>': return MakeToken(MatchNext('=') ? Token::Type::GreaterEqual : Token::Type::Greater);
            case '"': return ReadString();

            default: return MakeErrorToken("Unexpected character.");
        }
    }

    Token Lexer::MakeToken(const Token::Type type) const
    {
        Token token;
        token.type = type;
        token.firstCharacter = startCharacter;
        token.lastCharacter = currentCharacter;
        return token;
    }

    Token Lexer::MakeErrorToken(const std::string& errorMessage) const
    {
        Token token;
        token.type = Token::Type::Error;
        token.firstCharacter = &errorMessage.front();
        token.lastCharacter = &errorMessage.back();
        return token;
    }

    char Lexer::ReadCharacter()
    {
        return *currentCharacter++;
    }

    bool Lexer::AtEndOfFile() const
    {
        return *currentCharacter == '\0';
    }

    bool Lexer::MatchNext(const char c)
    {
        if (AtEndOfFile()) return false;
        if (*currentCharacter != c) return false;
        currentCharacter++; //Eat the next character only if it matches
        return true;
    }

    bool Lexer::IsDigit(const char c)
    {
        return c >= '0' and c <= '9';
    }

    bool Lexer::IsAlpha(const char c)
    {
        return (c >= 'a' and c <= 'z') or (c >= 'A' and c <= 'Z');
    }

    bool Lexer::IsAlphaNumeric(const char c)
    {
        return IsDigit(c) or IsAlpha(c);
    }

    void Lexer::SkipWhitespace()
    {
        while (true)
        {
            switch (Peek())
            {
                case ' ':
                case '\r':
                case '\t':
                    ReadCharacter();
                    break;
                case '/':
                {
                    if (Peek(1) == '/')
                    {
                        while (!AtEndOfFile() && Peek() != '\n') ReadCharacter();
                    }
                    else return;
                    break;
                }
                default: return; //First non-whitespace character, we quit
            }
        }
    }

    char Lexer::Peek(const int offset) const
    {
        if (AtEndOfFile()) return '\0';
        return *(currentCharacter + offset);
    }

    Token Lexer::ReadString()
    {
        while (!AtEndOfFile() and Peek() != '"') ReadCharacter();
        if (AtEndOfFile()) return MakeErrorToken("Unterminated string.");

        //Eat the close quote
        ReadCharacter();
        return MakeToken(Token::String);
    }

    Token Lexer::ReadNumber()
    {
        while (IsDigit(Peek())) ReadCharacter();

        //Check for decimal part
        if (Peek() == '.' and IsDigit(Peek(1)))
        {
            ReadCharacter(); //Eat the point
            while (IsDigit(Peek())) ReadCharacter(); //Eat all decimal digits
        }

        return MakeToken(Token::Type::Number);
    }

    Token Lexer::ReadIdentifier()
    {
        while (IsAlpha(Peek()) or IsDigit(Peek())) ReadCharacter();
        return MakeToken(GetIdentifierType());
    }

    Token::Type Lexer::GetIdentifierType()
    {
        switch (*startCharacter)
        {
            case 'a': return KeywordCheck(1, "nd", Token::Type::And);
            case 'c': return KeywordCheck(1, "lass", Token::Type::Class);
            case 'e': return KeywordCheck(1, "lse", Token::Type::Else);
            case 'f':
            {
                if (currentCharacter - startCharacter > 1)
                {
                    switch (*(startCharacter + 1))
                    {
                        case 'a': return KeywordCheck(2, "lse", Token::Type::False);
                        case 'o': return KeywordCheck(2, "r", Token::Type::For);
                        case 'u': return KeywordCheck(2, "nction", Token::Type::Function);
                        default: break;
                    }
                }
                break;
            }
            case 'i': return KeywordCheck(1, "f", Token::Type::If);
            case 'n': return KeywordCheck(1, "ull", Token::Type::Null);
            case 'o': return KeywordCheck(1, "r", Token::Type::Or);
            case 'p': return KeywordCheck(1, "rint", Token::Type::Print);
            case 'r': return KeywordCheck(1, "eturn", Token::Type::Return);
            case 's': return KeywordCheck(1, "uper", Token::Type::Super);
            case 't':
            {
                if (currentCharacter - startCharacter > 1)
                {
                    switch (*(startCharacter + 1))
                    {
                        case 'h': return KeywordCheck(2, "is", Token::Type::This);
                        case 'r': return KeywordCheck(2, "ue", Token::Type::True);
                        default: break;
                    }
                }
                break;
            }
            case 'v': return KeywordCheck(1, "ar", Token::Type::Variable);
            case 'w': return KeywordCheck(1, "hile", Token::Type::While);
        }
        return Token::Identifier;
    }

    Token::Type Lexer::KeywordCheck(const int offset, const std::string& rest, const Token::Type type) const
    {
        if (currentCharacter - startCharacter == offset + rest.size() and std::memcmp(startCharacter + offset, rest.c_str(), rest.size()) == 0)
        {
            return type;
        }
        return Token::Identifier;
    }

} // Noble::Compiler