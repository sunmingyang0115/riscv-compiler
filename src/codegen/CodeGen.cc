#include "CodeGen.hh"
#include <fstream>
#include <iostream>
#include <sstream>

class CompilerHelper {
private:
    std::stringstream builder;

public:
    CompilerHelper() : builder{} {
        builder << "        .global _start\n"
                << "_start: add     sp, sp, 400\n" // reserve stack mem
                << "        jal     ra, main\n"
                << "        add     a0, zero, t0\n"
                << "        addi    a7, x0, 93\n"
                << "        ecall\n";
    }
    void compile(AST::Expression *ast) {
        if (auto cast = dynamic_cast<AST::Literal *>(ast)) {
            int value = std::atoi(cast->value.c_str());
            builder << "        addi    t0, zero, " << value << "\n";
            // todo: make this not error for litearls [2047, -2048]
        } else if (auto cast = dynamic_cast<AST::DefFun *>(ast)) {
            // todo: load arguments
            builder << cast->name << ":\n"
                    << "        add     fp, zero, sp\n" // save frame pointer
                    << "        sw      ra, 0(fp)\n"    // store ra
                    << "        addi    sp, sp, -4\n";
            compile(cast->body);
            builder << "        lw      ra, 0(fp)\n"
                    << "        ret\n";
        } else if (auto cast = dynamic_cast<AST::Do *>(ast)) {
            for (AST::Expression *e : cast->expressions) {
                compile(e);
            }
        }
    }
    bool finalize(std::string file) {
        std::ofstream out{file};
        out << builder.rdbuf();
        out.close();
        return true;
    }
};

bool compile(std::string file, AST::Expression *ast) {
    CompilerHelper ch{};
    ch.compile(ast);
    return ch.finalize(file);
}
