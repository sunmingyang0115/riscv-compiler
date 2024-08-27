#include "Compiler.hh"
#include <fstream>
#include <iostream>
#include <unordered_map>

void Compiler::push(int amount, std::string reg) {
    this->builder << "        sw      " << reg << ", 0(sp)\n"
                  << "        addi    sp, sp, " << -amount << "\n";
}
void Compiler::pull(int amount, std::string reg) {
    this->builder << "        lw      " << reg << ", 4(sp)\n"
                  << "        addi    sp, sp, " << amount << "\n";
}
std::string newUniqueLabel() {
    static int n = 0;
    return "_L" + std::to_string(++n);
}

Compiler::Compiler() {
}

void Compiler::compile(AST::Expression *ast) {
    static std::unordered_map<AST::DataType, int> dataTypeToSize = {
        {AST::DataType::D1, 1},
        {AST::DataType::D2, 2},
        {AST::DataType::D4, 4},
        {AST::DataType::D8, 8}};
    static std::unordered_map<AST::DataType, std::string> dataTypeToLoadIns = {
        {AST::DataType::D1, "lb"},
        {AST::DataType::D2, "lh"},
        {AST::DataType::D4, "lw"},
        {AST::DataType::D8, "ld"}};
    static std::unordered_map<AST::DataType, std::string> dataTypeToStoreIns = {
        {AST::DataType::D1, "sb"},
        {AST::DataType::D2, "sh"},
        {AST::DataType::D4, "sw"},
        {AST::DataType::D8, "sd"}};
    static std::unordered_map<AST::BinOp, std::string> binOpToIns = {
        {AST::BinOp::ADD, "        add     a0, a1, a0\n"},
        {AST::BinOp::SUB, "        sub     a0, a1, a0\n"},
        {AST::BinOp::DIV, "        div     a0, a1, a0\n"},
        {AST::BinOp::MUL, "        mul     a0, a1, a0\n"},
        {AST::BinOp::MOD, "        rem     a0, a1, a0\n"},
        {AST::BinOp::AND, "        and     a0, a1, a0\n"
                          "        sltu    a0, zero, a0\n"},
        {AST::BinOp::OR, "        or      a0, a1, a0\n"
                         "        sltiu   a0, a0, 1\n"
                         "        xori    a0, a0, 1\n"},
        {AST::BinOp::GT, "        slt     a0, a0, a1\n"},
        {AST::BinOp::LT, "        slt     a0, a1, a0\n"},
        {AST::BinOp::GEQ, "        slt     a0, a1, a0\n"
                          "        sltiu   a0, a0, 1\n"},
        {AST::BinOp::LEQ, "        slt     a0, a0, a1\n"
                          "        sltiu   a0, a0, 1\n"},
        {AST::BinOp::EQ, "        xor     a0, a1, a0\n"
                         "        sltiu   a0, a0, 1\n"},
        {AST::BinOp::NEQ, "        xor     a0, a1, a0\n"
                          "        sltu    a0, x0, a0\n"},
        {AST::BinOp::XOR, "        xor     a0, a1, a0\n"
                          "        sltu    a0, x0, a0\n"},
        {AST::BinOp::BSL, "        sll     a0, a1, a0\n"},
        {AST::BinOp::BSR, "        sra     a0, a1, a0\n"}};
    
    if (auto cast = dynamic_cast<AST::Export *>(ast)) {
        if (!cast->datas.empty()) {
            this->builder << "        .global ";
            for (int i = 0; i < cast->datas.size(); i++) {
                this->builder << "_" << cast->datas.at(i);
                if (i != cast->datas.size()-1) {
                    this->builder << ", ";
                }
            }
            this->builder << "\n";
        }
    }
    else if (auto cast = dynamic_cast<AST::DefFun *>(ast)) {
        this->offsetFP = 0;
        this->varOffsetMap = {};
        int pos = 16;
        for (int i = cast->argNames.size() - 1; i >= 0; i--) {
            varOffsetMap[cast->argNames.at(i)] = std::make_pair(cast->argTypes.at(i), pos);
            pos += 8;
        }
        this->builder << "_" << cast->name << ":\n"
                      << "        addi    sp, sp, -16\n"
                         "        sd      ra, 0(sp)\n"       // store ra
                         "        sd      fp, 8(sp)\n"       // store caller->fp
                         "        add     fp, zero, sp\n\n"; // init callee->fp
        compile(cast->body);
        this->builder << "\n"
                         "        add     sp, zero, fp\n" // dealloc sp
                         "        ld      ra, 0(sp)\n"
                         "        ld      fp, 8(sp)\n"
                      << "        addi    sp, sp, " << pos << "\n"
                      << "        ret\n";
    } else if (auto cast = dynamic_cast<AST::RefFun *>(ast)) {
        // spill args
        for (int i = 0; i < cast->arguments.size(); i++) {
            compile(cast->arguments.at(i));
            this->builder << "        addi    sp, sp, -8\n" // assume 8 bytes for now
                             "        sd      a0, 0(sp)\n";
        }
        this->builder << "        jal     ra, _" << cast->name << "\n";
    } else if (auto cast = dynamic_cast<AST::Do *>(ast)) {
        for (AST::Expression *e : cast->expressions) {
            compile(e);
        }
    } else if (auto cast = dynamic_cast<AST::Literal *>(ast)) {
        int value = std::atoi(cast->value.c_str());
        int lower = value & 0xFFF;
        int upper = value >> 12;
        if (value & 0x800) {
            upper++;
            lower -= 0x1000;
        }

        if (upper == 0) {
            this->builder << "        addi    a0, zero, " << lower << "\n";
        } else if (lower == 0) {
            this->builder << "        lui     a0, " << (upper & 0xFFFFF) << "\n";
        } else {
            this->builder << "        lui     a0, " << (upper & 0xFFFFF) << "\n";
            this->builder << "        addi    a0, a0, " << lower << "\n";
        }
    } else if (auto cast = dynamic_cast<AST::Bin *>(ast)) {
        // more todo: use reg alloc
        // even more todo: add a lowering step that turns (+ d4 d8) to (long+ (int2long d4) d8)
        compile(cast->left);
        this->builder << "        addi    sp, sp, -8\n" // :grimace:
                         "        sd      a0, 0(sp)\n";
        compile(cast->right);
        this->builder << "        ld      a1, 0(sp)\n"
                         "        addi    sp, sp, 8\n";
        this->builder << binOpToIns[cast->op];
    } else if (auto cast = dynamic_cast<AST::DefVar *>(ast)) {

        int size = dataTypeToSize[cast->dataType];
        this->builder << "        addi    sp, sp, " << -size << "\n";
        offsetFP -= size;
        varOffsetMap[cast->name] = std::make_pair(cast->dataType, offsetFP);
    } else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
        compile(cast->data);
        std::string loadIns = dataTypeToLoadIns[cast->refTo];
        this->builder << "        " << loadIns << "    a0, 0(a0)\n";
    } else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
        // takes an lvalue
        compileLV(cast->data);
    } else if (auto cast = dynamic_cast<AST::RefVar *>(ast)) {
        // rvalue of var
        // (compile function assumes rvalue)
        std::string loadIns = dataTypeToLoadIns[varOffsetMap[cast->name].first];
        int offset = varOffsetMap[cast->name].second;
        this->builder << "        " << loadIns << "      a0, " << offset << "(fp)\n";
    } else if (auto cast = dynamic_cast<AST::Set *>(ast)) {
        // first arg is an lvalue
        AST::DataType storeDT = compileLV(cast->data);
        std::string storeIns = dataTypeToStoreIns[storeDT];
        this->builder << "        addi    sp, sp, -8\n"
                         "        sd      a0, 0(sp)\n";
        compile(cast->value);
        this->builder << "        ld      a1, 0(sp)\n"
                         "        addi    sp, sp, 8\n"
                      << "        " << storeIns << "      a0, 0(a1)\n";
    } else if (auto cast = dynamic_cast<AST::Cond *>(ast)) {
        std::string end = newUniqueLabel();
        int startSP = offsetFP;
        for (int i = 0; i < cast->conds.size(); i++) {
            compile(cast->conds.at(i));
            if (i == cast->conds.size() - 1) {
                this->builder << "        beq     a0, zero, " << end << "\n";
                compile(cast->thens.at(i));
            } else {
                std::string next = newUniqueLabel();
                this->builder << "        beq     a0, zero, " << next << "\n";
                compile(cast->thens.at(i));
                this->builder << "        j       " << end << "\n"
                              << next << ":\n";
            }
            this->builder << "        addi    sp, sp, " << (offsetFP - startSP) << "\n";
        }
        this->builder << end << ":\n";
    } else if (auto cast = dynamic_cast<AST::While *>(ast)) {
        std::string start = newUniqueLabel();
        std::string end = newUniqueLabel();
        int startSP = offsetFP;
        this->builder << start << ":\n";
        compile(cast->cond);
        this->builder << "        beq     a0, zero, " << end << "\n";
        compile(cast->body);
        this->builder << "        addi    sp, sp, " << (offsetFP - startSP) << "\n"
                      << "        j       " << start << "\n"
                      << end << ":\n";
    }
}

AST::DataType Compiler::compileLV(AST::Expression *ast) {
    if (auto content = dynamic_cast<AST::DeRef *>(ast)) {
        // [dt]^B
        compile(content->data); // compile B
        return content->refTo;
    } else if (auto content = dynamic_cast<AST::RefVar *>(ast)) {
        // b
        this->builder << "        addi    a0, fp, " << varOffsetMap[content->name].second << "\n";
        return varOffsetMap[content->name].first;
    } else {
        // error if not valid LV
        exit(2);
    }
}

bool Compiler::finalize(std::string file) {
    std::ofstream out{file};
    out << this->builder.rdbuf();
    out.close();
    return true;
}

Compiler::~Compiler() {}
