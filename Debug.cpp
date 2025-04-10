//
// Created by aaron on 27/03/25.
//

#include "Debug.h"

#include <iomanip>

namespace Noble::Compiler
{
    std::string Debug::OpToString(Op::Code op)
    {
        std::stringstream ss;
        switch (op)
        {
            case Op::Code::Add:          ss << "ADD"; break;
            case Op::Code::Constant:     ss << "CST"; break;
            case Op::Code::DefineGlobal: ss << "DFG"; break;
            case Op::Code::Divide:       ss << "DIV"; break;
            case Op::Code::Equal:        ss << "EQL"; break;
            case Op::Code::False:        ss << "FAL"; break;
            case Op::Code::GetGlobal:    ss << "GEG"; break;
            case Op::Code::Greater:      ss << "GTR"; break;
            case Op::Code::GreaterEqual: ss << "GEQ"; break;
            case Op::Code::Less:         ss << "LES"; break;
            case Op::Code::LessEqual:    ss << "LEQ"; break;
            case Op::Code::Multiply:     ss << "MUL"; break;
            case Op::Code::Negate:       ss << "NEG"; break;
            case Op::Code::Not:          ss << "NOT"; break;
            case Op::Code::NotEqual:     ss << "NEQ"; break;
            case Op::Code::Null:         ss << "NUL"; break;
            case Op::Code::Pop:          ss << "POP"; break;
            case Op::Code::PopN:         ss << "PPN"; break;
            case Op::Code::Print:        ss << "PRT"; break;
            case Op::Code::Return:       ss << "RET"; break;
            case Op::Code::Subtract:     ss << "SUB"; break;
            case Op::Code::True:         ss << "TRU"; break;
            default: ss << "Unknown operation '" << op << "'\n"; break;
        }
        return ss.str();
    }

    std::string Debug::TokenToString(const Token& token)
    {
        std::stringstream ss;
        switch (token.type)
        {
            case Token::And:          ss << "And"; break;
            case Token::Bang:         ss << "Bang"; break;
            case Token::Class:        ss << "Class"; break;
            case Token::Comma:        ss << "Comma"; break;
            case Token::Dot:          ss << "Dot"; break;
            case Token::Else:         ss << "Else"; break;
            case Token::Equal:        ss << "Equal"; break;
            case Token::Error:        ss << "Error"; break;
            case Token::False:        ss << "False"; break;
            case Token::For:          ss << "For"; break;
            case Token::Function:     ss << "Function"; break;
            case Token::Greater:      ss << "Greater"; break;
            case Token::Identifier:   ss << "Identifier"; break;
            case Token::If:           ss << "If"; break;
            case Token::Less:         ss << "Less"; break;
            case Token::Minus:        ss << "Minus"; break;
            case Token::None:         ss << "None"; break;
            case Token::Null:         ss << "Null"; break;
            case Token::Number:       ss << "Number"; break;
            case Token::Or:           ss << "Or"; break;
            case Token::Plus:         ss << "Plus"; break;
            case Token::Print:        ss << "Print"; break;
            case Token::Return:       ss << "Return"; break;
            case Token::Semicolon:    ss << "Semicolon"; break;
            case Token::Slash:        ss << "Slash"; break;
            case Token::Star:         ss << "Star"; break;
            case Token::String:       ss << "String"; break;
            case Token::Super:        ss << "Super"; break;
            case Token::This:         ss << "This"; break;
            case Token::True:         ss << "True"; break;
            case Token::Variable:     ss << "Variable"; break;
            case Token::While:        ss << "While"; break;
            case Token::BangEqual:    ss << "BangEqual"; break;
            case Token::EqualEqual:   ss << "EqualEqual"; break;
            case Token::GreaterEqual: ss << "GreaterEqual"; break;
            case Token::LeftBrace:    ss << "LeftBrace"; break;
            case Token::LeftParen:    ss << "LeftParen"; break;
            case Token::LessEqual:    ss << "LessEqual"; break;
            case Token::RightBrace:   ss << "RightBrace"; break;
            case Token::RightParen:   ss << "RightParen"; break;
            case Token::EndOfFile:    ss << "EndOfFile"; break;
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
                case Op::Code::DefineGlobal:
                {
                    const Address::Single globalVarAddress = frame.ReadAddress(i + 1);
                    debugFile << std::setw(7) << std::setfill('0') << globalVarAddress << "   ";
                    i += sizeof(Address::Single);
                    break;
                }
                case Op::Code::GetGlobal:
                {
                    const Address::Single globalVarAddress = frame.ReadAddress(i + 1);
                    debugFile << std::setw(7) << std::setfill('0') << globalVarAddress << "   ";
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