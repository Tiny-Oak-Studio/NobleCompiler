#include "Lexer.h"

namespace Noble::Compiler
{
    std::vector<Token> Lexer::Lex(const std::string &NGPLSource)
    {
        std::vector<Token> tokens;
        startScanHead = currentScanHead = &NGPLSource[0];

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
        startScanHead = currentScanHead;

        if (AtEndOfFile()) return MakeToken(Token::Type::EndOfFile);

        const char c = ReadCharacter();
        if (std::isalpha(c) or c == '_') return ReadIdentifier();
        if (std::isdigit(c)) return ReadNumber();

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

            default: return Token("Unexpected character.");
        }
    }

    Token Lexer::MakeToken(const Token::Type type) const
    {
        return { type, startScanHead, currentScanHead };
    }

    char Lexer::ReadCharacter()
    {
        return *currentScanHead++;
    }

    bool Lexer::AtEndOfFile() const
    {
        return *currentScanHead == '\0';
    }

    bool Lexer::MatchNext(const char c)
    {
        if (AtEndOfFile()) return false;
        if (*currentScanHead != c) return false;
        currentScanHead++; //Eat the next character only if it matches
        return true;
    }

    void Lexer::SkipWhitespace()
    {
        while (true)
        {
            switch (Peek())
            {
                case ' ':
                case '\v':
                case '\f':
                case '\r':
                case '\t':
                    ReadCharacter();
                    break;
                case '/':
                {
                    if (Peek(1) == '/')
                    {
                        while (!AtEndOfFile() and Peek() != '\n') ReadCharacter();
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
        return *(currentScanHead + offset);
    }

    Token Lexer::ReadString()
    {
        while (!AtEndOfFile() and Peek() != '"') ReadCharacter();
        if (AtEndOfFile()) return Token("Unterminated string.");

        //Eat the close quote
        ReadCharacter();
        return MakeToken(Token::String);
    }

    Token Lexer::ReadNumber()
    {
        while (std::isdigit(Peek())) ReadCharacter();

        //Check for decimal part
        if (Peek() == '.' and std::isdigit(Peek(1)))
        {
            ReadCharacter(); //Eat the point
            while (std::isdigit(Peek())) ReadCharacter(); //Eat all decimal digits
        }

        return MakeToken(Token::Type::Number);
    }

    Token Lexer::ReadIdentifier()
    {
        while (std::isalnum(Peek())) ReadCharacter();
        return MakeToken(GetIdentifierType());
    }

    Token::Type Lexer::GetIdentifierType() const
    {
        switch (*startScanHead)
        {
            case 'a': return KeywordCheck(1, "nd", Token::Type::And);
            case 'c': return KeywordCheck(1, "lass", Token::Type::Class);
            case 'e': return KeywordCheck(1, "lse", Token::Type::Else);
            case 'f':
            {
                if (currentScanHead - startScanHead > 1)
                {
                    switch (*(startScanHead + 1))
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
                if (currentScanHead - startScanHead > 1)
                {
                    switch (*(startScanHead + 1))
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
        if (currentScanHead - startScanHead == offset + rest.size() and std::memcmp(startScanHead + offset, rest.c_str(), rest.size()) == 0)
        {
            return type;
        }
        return Token::Identifier;
    }
} // Noble::Compiler