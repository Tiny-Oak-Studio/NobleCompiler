#include "Compiler.h"

#include "Bytecode/BytecodeVisitor.h"
#include "Optimisations/ConstantFoldingVisitor.h"

namespace Noble::Compiler
{
    bool Compiler::Compile(const std::string& NGPLSource, const std::string& frameName)
    {
        //We use the compiler's copy of the source and keep it around as long as the compiler it around
        //because the Lexer and Parser's Tokens point directly to the source for their lexemes.
        source = NGPLSource;

        Lexer lexer;
        Parser parser;
        Frame frame;

        //Optimisations::ConstantFoldingVisitor constantRollerVisitor;
        Bytecode::BytecodeVisitor bytecodeVisitor;
        const std::vector<Token> tokens = lexer.Lex(source.c_str());
        Debug::MakeTokenFile(tokens, frameName);
        std::vector<AST::StatementPtr> AST = parser.Parse(tokens);

        //constantRollerVisitor.FoldConstants(AST);
        bytecodeVisitor.GenerateOps(AST, frame);

        return WriteFrame(frame, frameName) && Debug::MakeDebugFile(frame, frameName);
    }

    bool Compiler::WriteFrame(const Frame &frame, const std::string& name)
    {
        std::ofstream ops(name + ".naf", std::ios::trunc | std::ios::binary);
        if (!ops.is_open())
        {
            std::cerr << "Error: Unable to open assembly file '" << name << ".naf' while writing frame.\n";
            return false;
        }

        ops.write(reinterpret_cast<const std::ostream::char_type*>(frame.GetOps().GetArray()), frame.GetOps().Count() * sizeof(Core::Op::Type));
        ops.close();

        std::ofstream constants(name + ".ndf", std::ios::trunc | std::ios::binary);
        if (!constants.is_open())
        {
            std::cerr << "Error: Unable to open data file '" << name << ".ndf' while writing frame.\n";
            return false;
        }

        constants.write(reinterpret_cast<const std::ostream::char_type*>(frame.GetConstants().GetArray()), frame.GetConstants().Count() * sizeof(ValueType));
        return true;
    }
}
