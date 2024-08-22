#include "CodeGen.hh"
#include <fstream>
#include <sstream>
#include <unordered_map>

std::string binOpToInstruction(AST::BinOp op) {
    switch (op) {
    case AST::BinOp::ADD:
        return "        add     t0, t1, t0\n";
    case AST::BinOp::SUB:
        return "        sub     t0, t1, t0\n";
    case AST::BinOp::DIV:
        return "        div     t0, t1, t0\n";
    case AST::BinOp::MUL:
        return "        mul     t0, t1, t0\n";
    case AST::BinOp::MOD:
        return "        rem     t0, t1, t0\n";
    case AST::BinOp::AND:
        return "        and      t0, t1, t0\n"
               "        sltu     t0, zero, t0\n";
    case AST::BinOp::OR:
        return "        or      t0, t1, t0\n"
               "        sltiu   t0, t0, 1\n"
               "        xori    t0, t0, 1\n";
    case AST::BinOp::GT:
        return "        slt     t0, t0, t1\n";
    case AST::BinOp::LT:
        return "        slt     t0, t1, t0\n";
    case AST::BinOp::GEQ:
        return "        slt     t0, t1, t0\n"
               "        sltiu   t0, t0, 1\n";
    case AST::BinOp::LEQ:
        return "        slt     t0, t0, t1\n"
               "        sltiu   t0, t0, 1\n";
    case AST::BinOp::EQ:
        return "        xor     t0, t1, t0\n"
               "        sltiu   t0, t0, 1\n";
    case AST::BinOp::NEQ:
        return "        xor     t0, t1, t0\n"
               "        sltu    t0, x0, t0\n";
    case AST::BinOp::XOR:
        return "        xor     t0, t1, t0\n"
               "        sltu    t0, x0, t0\n";
    case AST::BinOp::BSL:
        return "        sll     t0, t1, t0\n";
    case AST::BinOp::BSR:
        return "        sra     t0, t1, t0\n";
    }
    exit(1);
}

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
                    << "        sw      ra, 0(sp)\n"  // store ra
                    << "        sw      fp, -4(sp)\n" // store caller->fp
                    << "        addi    sp, sp, -8\n"
                    << "        add     fp, zero, sp\n\n"; // init callee->fp
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
            compile(cast->right);
            builder << "        lw      t1, 4(sp)\n"
                    << "        addi    sp, sp, 4\n";
            builder << binOpToInstruction(cast->op);
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
            compile(cast->value);
            builder << "        lw      t1, 4(sp)\n"
                    << "        addi    sp, sp, 4\n"
                    << "        sw      t0, 0(t1)\n";
        } else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
            compile(cast->data);
            builder << "        lw      t0, 0(t0)\n";
        } else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
        } else if (auto cast = dynamic_cast<AST::Not *>(ast)) {
            compile(cast->value);
            builder << "        sltiu   t0, t0, 1\n";
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
