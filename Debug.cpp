//
// Created by aaron on 27/03/25.
//

#include "Debug.h"

#include <iomanip>

namespace Noble::Compiler
{
    std::string Debug::OpToString(Noble::Core::Op::Code op)
    {
        std::stringstream ss;
        switch (op)
        {
            case Noble::Core::Op::Code::Add:          ss << "ADD"; break;
            case Noble::Core::Op::Code::Constant:     ss << "CST"; break;
            case Noble::Core::Op::Code::Divide:       ss << "DIV"; break;
            case Noble::Core::Op::Code::Equal:        ss << "EQL"; break;
            case Noble::Core::Op::Code::False:        ss << "FAL"; break;
            case Noble::Core::Op::Code::Greater:      ss << "GTR"; break;
            case Noble::Core::Op::Code::Less:         ss << "LES"; break;
            case Noble::Core::Op::Code::Multiply:     ss << "MUL"; break;
            case Noble::Core::Op::Code::Negate:       ss << "NEG"; break;
            case Noble::Core::Op::Code::Not:          ss << "NOT"; break;
            case Noble::Core::Op::Code::Null:         ss << "NUL"; break;
            case Noble::Core::Op::Code::Return:       ss << "RET"; break;
            case Noble::Core::Op::Code::Subtract:     ss << "SUB"; break;
            case Noble::Core::Op::Code::True:         ss << "TRU"; break;
            case Noble::Core::Op::Code::GreaterEqual: ss << "GEQ"; break;
            case Noble::Core::Op::Code::LessEqual:    ss << "LEQ"; break;
            case Noble::Core::Op::Code::NotEqual:     ss << "NEQ"; break;
            default: ss << "Unknown operation '" << op << "'\n"; break;
        }
        return ss.str();
    }

    std::string Debug::TokenToString(const Noble::Compiler::Token& token)
    {
        std::stringstream ss;
        switch (token.type)
        {
            case Noble::Compiler::Token::And:          ss << "And"; break;
            case Noble::Compiler::Token::Bang:         ss << "Bang"; break;
            case Noble::Compiler::Token::Class:        ss << "Class"; break;
            case Noble::Compiler::Token::Comma:        ss << "Comma"; break;
            case Noble::Compiler::Token::Dot:          ss << "Dot"; break;
            case Noble::Compiler::Token::Else:         ss << "Else"; break;
            case Noble::Compiler::Token::Equal:        ss << "Equal"; break;
            case Noble::Compiler::Token::Error:        ss << "Error"; break;
            case Noble::Compiler::Token::False:        ss << "False"; break;
            case Noble::Compiler::Token::For:          ss << "For"; break;
            case Noble::Compiler::Token::Function:     ss << "Function"; break;
            case Noble::Compiler::Token::Greater:      ss << "Greater"; break;
            case Noble::Compiler::Token::Identifier:   ss << "Identifier"; break;
            case Noble::Compiler::Token::If:           ss << "If"; break;
            case Noble::Compiler::Token::Less:         ss << "Less"; break;
            case Noble::Compiler::Token::Minus:        ss << "Minus"; break;
            case Noble::Compiler::Token::None:         ss << "None"; break;
            case Noble::Compiler::Token::Null:         ss << "Null"; break;
            case Noble::Compiler::Token::Number:       ss << "Number"; break;
            case Noble::Compiler::Token::Or:           ss << "Or"; break;
            case Noble::Compiler::Token::Plus:         ss << "Plus"; break;
            case Noble::Compiler::Token::Print:        ss << "Print"; break;
            case Noble::Compiler::Token::Return:       ss << "Return"; break;
            case Noble::Compiler::Token::Semicolon:    ss << "Semicolon"; break;
            case Noble::Compiler::Token::Slash:        ss << "Slash"; break;
            case Noble::Compiler::Token::Star:         ss << "Star"; break;
            case Noble::Compiler::Token::String:       ss << "String"; break;
            case Noble::Compiler::Token::Super:        ss << "Super"; break;
            case Noble::Compiler::Token::This:         ss << "This"; break;
            case Noble::Compiler::Token::True:         ss << "True"; break;
            case Noble::Compiler::Token::Variable:     ss << "Variable"; break;
            case Noble::Compiler::Token::While:        ss << "While"; break;
            case Noble::Compiler::Token::BangEqual:    ss << "BangEqual"; break;
            case Noble::Compiler::Token::EqualEqual:   ss << "EqualEqual"; break;
            case Noble::Compiler::Token::GreaterEqual: ss << "GreaterEqual"; break;
            case Noble::Compiler::Token::LeftBrace:    ss << "LeftBrace"; break;
            case Noble::Compiler::Token::LeftParen:    ss << "LeftParen"; break;
            case Noble::Compiler::Token::LessEqual:    ss << "LessEqual"; break;
            case Noble::Compiler::Token::RightBrace:   ss << "RightBrace"; break;
            case Noble::Compiler::Token::RightParen:   ss << "RightParen"; break;
            case Noble::Compiler::Token::EndOfFile:    ss << "EndOfFile"; break;
            default: ss << "Unknown token '" << token.type << "'\n"; break;
        }
        return ss.str();
    }

    bool Debug::MakeDebugFile(const Frame &frame, const std::string& name)
    {
        std::ofstream debugFile(name + ".debug", std::ios::trunc | std::ios::binary);
        if (!debugFile.is_open())
        {
            std::cerr << "Error: Unable to create debug file '" << name << ".debug'\n";
            return false;
        }
        debugFile << "------------------- Debug Info -------------------\n";
        debugFile << "Op Index | Op Name | Address | Literal Value\n";
        debugFile << "--------------------------------------------------\n";
        for (unsigned i = 0; i < frame.GetOps().Count(); ++i)
        {
            debugFile << std::setw(8) << std::setfill('0') << i << "   ";
            debugFile << OpToString(static_cast<Op::Code>(frame.GetOps()[i])) << "       ";

            switch (frame.GetOps()[i])
            {
                case Op::Code::Constant:
                {
                    const Address::Single constantAddress = frame.ReadAddress(i + 1);
                    debugFile << std::setw(7) << std::setfill('0') << constantAddress << "   ";
                    debugFile << frame.ReadConstant(constantAddress);
                    i += sizeof(Address::Single);
                    break;
                }
                default: break;
            }
            debugFile << "\n";
        }
        return true;
    }

    bool Debug::MakeTokenFile(const std::vector<Token> &tokens, const std::string &name)
    {
        std::ofstream tokenFile(name + ".token", std::ios::trunc | std::ios::binary);
        if (!tokenFile.is_open())
        {
            std::cerr << "Error: Unable to create token file '" << name << ".token'\n";
            return false;
        }

        tokenFile << "--------------------------------------------------\n";
        tokenFile << "                   Token File                     \n";
        tokenFile << "--------------------------------------------------\n";
        for (auto& token : tokens)
        {
            tokenFile << TokenToString(token) << "\n";
        }
        return true;
    }
} // Noble::Compiler