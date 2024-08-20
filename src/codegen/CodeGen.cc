#include "CodeGen.hh"
#include <fstream>
#include <sstream>
#include <unordered_map>

class CompilerHelper {
private:
    std::stringstream builder;
    std::unordered_map<std::string, int> varOffsetMap;
    int offsetFP;

public:
    CompilerHelper() : builder{}, varOffsetMap{}, offsetFP{0} {
        builder << "        .global _start\n"
                << "_start: addi    sp, sp, 400\n" // reserve stack mem
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
            // 'callee'
            offsetFP = 0;
            varOffsetMap = {};
            builder << cast->name << ":\n"
                    << "        sw      ra, 0(sp)\n"        // store ra
                    << "        sw      fp, -4(sp)\n"        // store caller->fp
                    << "        addi    sp, sp, -8\n"
                    << "        add     fp, zero, sp\n\n";     // init callee->fp
            compile(cast->body);
            builder << "\n"
                    << "        add     sp, zero, fp\n" // dealloc sp
                    << "        addi    sp, sp, 8\n"
                    << "        lw      ra, 0(sp)\n"
                    << "        lw      fp, -4(sp)\n"
                    << "        ret\n";
                    
        } else if (auto cast = dynamic_cast<AST::Do *>(ast)) {
            for (AST::Expression *e : cast->expressions) {
                compile(e);
            }
        } else if (auto cast = dynamic_cast<AST::RefFun *>(ast)) {
            // todo: load args
            builder << "        jal     ra, " << cast->name << "\n";
        } else if (auto cast = dynamic_cast<AST::Bin *>(ast)) {
            compile(cast->left);
            builder << "        sw      t0, 0(sp)\n"
                    << "        addi    sp, sp, -4\n";
            offsetFP += 4;
            compile(cast->right);
            builder << "        lw      t1, 4(sp)\n"
                    << "        addi    sp, sp, 4\n";
            offsetFP += 4;
            builder << "        add     t0, t0, t1\n";
        } else if (auto cast = dynamic_cast<AST::DefVar *>(ast)) {
            // todo: add other datatypes
            varOffsetMap[cast->name] = offsetFP;
            builder << "        addi    sp, sp, -4\n";
            offsetFP -= 4;
        } else if (auto cast = dynamic_cast<AST::RefVar *>(ast)) {
            builder << "        addi    t0, fp, " << varOffsetMap[cast->name] << "\n";
        } else if (auto cast = dynamic_cast<AST::Set *>(ast)) {
            compile(cast->data);
            builder << "        sw      t0, 0(sp)\n"
                    << "        addi    sp, sp, -4\n";
            offsetFP += 4;
            compile(cast->value);
            builder << "        lw      t1, 4(sp)\n"
                    << "        addi    sp, sp, 4\n"
                    << "        sw      t0, 0(t1)\n";
        } else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
            compile(cast->data);
            builder << "        lw      t0, 0(t0)\n";
        } else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
            // compile << "        addi    "
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
