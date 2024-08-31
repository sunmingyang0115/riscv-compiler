#include "CodeGen.hh"
#include "Compiler.hh"

bool compile(std::string file, AST::Expression *ast) {
    Compiler ch{};
    ch.compile(ast);
    return ch.finalize(file);
}
