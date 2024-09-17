#include "Compiler.h"

#include <atomic>

#include "Bytecode/BytecodeVisitor.h"
#include "Optimisations/ConstantFoldingVisitor.h"

namespace Noble::Compiler
{
    bool Compiler::Compile(const std::string& NGPLSource)
    {
        //We use the compiler's copy of the source and keep it around as long as the compiler it around
        //because the Lexer and Parser's Tokens point directly to the source for their lexemes.
        source = NGPLSource;

        Lexer lexer;
        Parser parser;
        Frame frame;

        //Optimisations::ConstantFoldingVisitor constantRollerVisitor;
        Bytecode::BytecodeVisitor bytecodeVisitor;

        std::unique_ptr<AST::Expression> AST = parser.Parse(lexer.Lex(source.c_str()));

        //constantRollerVisitor.FoldConstants(AST);
        bytecodeVisitor.GenerateOps(AST.get(), frame);
        WriteFrame(frame, "main");

        return true;
    }

    bool Compiler::WriteFrame(const Frame &frame, const std::string& name)
    {
        std::ofstream ops(name + ".naf", std::ios::trunc | std::ios::binary);
        if (!ops.is_open()) return false;

        ops.write(reinterpret_cast<const std::ostream::char_type*>(frame.GetOps().GetArray()), frame.NumOps() * sizeof(Core::Op::Type));
        ops.close();

        std::ofstream constants(name + ".ndf", std::ios::trunc | std::ios::binary);
        if (!constants.is_open()) return false;

        constants.write(reinterpret_cast<const std::ostream::char_type*>(frame.GetConstants().GetArray()), frame.NumConstants() * sizeof(ValueType));
        return true;
    }

}
