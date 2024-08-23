#include "CodeGen.hh"
#include "RegAlloc.hh"
#include <fstream>
#include <sstream>
#include <unordered_map>

std::string getNewLabel() {
    static int n = 0;
    return "_L" + std::to_string(n++);
}

std::string binOpToInstruction(AST::BinOp op) {
    // todo: add short circuiting to some binops
    switch (op) {
    case AST::BinOp::ADD:
        return "        add     a0, a1, a0\n";
    case AST::BinOp::SUB:
        return "        sub     a0, a1, a0\n";
    case AST::BinOp::DIV:
        return "        div     a0, a1, a0\n";
    case AST::BinOp::MUL:
        return "        mul     a0, a1, a0\n";
    case AST::BinOp::MOD:
        return "        rem     a0, a1, a0\n";
    case AST::BinOp::AND:
        return "        and     a0, a1, a0\n"
               "        sltu    a0, zero, a0\n";
    case AST::BinOp::OR:
        return "        or      a0, a1, a0\n"
               "        sltiu   a0, a0, 1\n"
               "        xori    a0, a0, 1\n";
    case AST::BinOp::GT:
        return "        slt     a0, a0, a1\n";
    case AST::BinOp::LT:
        return "        slt     a0, a1, a0\n";
    case AST::BinOp::GEQ:
        return "        slt     a0, a1, a0\n"
               "        sltiu   a0, a0, 1\n";
    case AST::BinOp::LEQ:
        return "        slt     a0, a0, a1\n"
               "        sltiu   a0, a0, 1\n";
    case AST::BinOp::EQ:
        return "        xor     a0, a1, a0\n"
               "        sltiu   a0, a0, 1\n";
    case AST::BinOp::NEQ:
        return "        xor     a0, a1, a0\n"
               "        sltu    a0, x0, a0\n";
    case AST::BinOp::XOR:
        return "        xor     a0, a1, a0\n"
               "        sltu    a0, x0, a0\n";
    case AST::BinOp::BSL:
        return "        sll     a0, a1, a0\n";
    case AST::BinOp::BSR:
        return "        sra     a0, a1, a0\n";
    }
    exit(1);
}

class CompilerHelper {
private:
    std::stringstream builder;
    std::unordered_map<std::string, int> varOffsetMap;
    RegAlloc allocator;
    int offsetFP;

public:
    CompilerHelper() : builder{}, varOffsetMap{}, offsetFP{0}, allocator{} {
        builder << "        .global _start\n"
                << "_start: addi    sp, sp, 400\n" // reserve stack mem
                << "        jal     ra, main\n"
                << "        addi    a7, x0, 93\n"
                << "        ecall\n";
    }
    void compile(AST::Expression *ast) {
        if (auto cast = dynamic_cast<AST::Literal *>(ast)) {
            int value = std::atoi(cast->value.c_str());
            builder << "        addi    a0, zero, " << value << "\n";
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
            int r = allocator.newReg();
            if (r == -1) {
                compile(cast->left);
                builder << "        sw      a0, 0(sp)\n"
                        << "        addi    sp, sp, -4\n";
                compile(cast->right);
                builder << "        lw      a1, 4(sp)\n"
                        << "        addi    sp, sp, 4\n"
                        << binOpToInstruction(cast->op);
            } else {
                compile(cast->left);
                builder << "        add     t" << r << ", zero, a0\n";
                compile(cast->right);
                builder << "        add     a1, zero, t" << r << "\n"
                        << binOpToInstruction(cast->op);
                allocator.freeReg(r);
            }
        } else if (auto cast = dynamic_cast<AST::DefVar *>(ast)) {
            // todo: add other datatypes
            varOffsetMap[cast->name] = offsetFP;
            builder << "        addi    sp, sp, -4\n";
            offsetFP -= 4;
        } else if (auto cast = dynamic_cast<AST::RefVar *>(ast)) {
            builder << "        addi    a0, fp, " << varOffsetMap[cast->name] << "\n";
        } else if (auto cast = dynamic_cast<AST::Set *>(ast)) {
            int r = allocator.newReg();
            if (r == -1) {
                compile(cast->data);
                builder << "        sw      a0, 0(sp)\n"
                        << "        addi    sp, sp, -4\n";
                compile(cast->value);
                builder << "        lw      a1, 4(sp)\n"
                        << "        addi    sp, sp, 4\n"
                        << "        sw      a0, 0(a1)\n";
            } else {
                compile(cast->data);
                builder << "        add     t" << r << ", zero, a0\n";
                compile(cast->value);
                builder << "        add     a1, zero, t" << r << "\n"
                        << "        sw      a0, 0(a1)\n";
                allocator.freeReg(r);
            }
            
        } else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
            compile(cast->data);
            builder << "        lw      a0, 0(a0)\n";
        } else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
        } else if (auto cast = dynamic_cast<AST::Not *>(ast)) {
            compile(cast->value);
            builder << "        sltiu   a0, a0, 1\n";
        } 
        else if (auto cast = dynamic_cast<AST::Cond *>(ast)) {
            // todo: make cond dealloc mem
            std::string endIf = getNewLabel();
            for (int i = 0; i < cast->conds.size(); i++) {
                bool last = i == cast->conds.size() - 1;
                std::string next = last? endIf: getNewLabel();
                compile(cast->conds.at(i));
                builder << "        beq     a0, x0, " << next << "\n";
                compile(cast->thens.at(i));
                if (!last)
                    builder << "        j       " << endIf << "\n";
                
                builder << next << ":\n";
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
