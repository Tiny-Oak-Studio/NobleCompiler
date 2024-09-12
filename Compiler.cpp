#include "Compiler.h"

#include "Bytecode/BytecodeVisitor.h"
#include "Optimisations/ConstantRollerVisitor.h"

namespace Noble::Compiler
{
    bool Compiler::Compile(const std::string& NGPLSource)
    {
        //We use the compiler's copy of the source and keep it around as long as the compiler it around
        //because the Lexer and Parser's Tokens point directly to the source for their lexemes.
        source = NGPLSource;

        Lexer lexer;
        Parser parser;
        Core::Frame frame;

        Optimisations::ConstantRollerVisitor constantRollerVisitor;
        Bytecode::BytecodeVisitor bytecodeVisitor;

        std::unique_ptr<AST::Expression> AST = parser.Parse(lexer.Lex(source.c_str()));

        constantRollerVisitor.RollConstants(AST.get());
        bytecodeVisitor.GenerateOps(AST.get(), frame);

        std::cout << "\n" << source;
        std::cout << "\nNum: " << frame.NumOps() << "\n";

        return false;
    }
}
