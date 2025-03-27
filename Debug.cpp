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

} // Noble::Compiler