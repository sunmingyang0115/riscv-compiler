#include "Compiler.hh"
#include <fstream>
#include <unordered_map>
#include <iostream>

void Compiler::push(int amount, std::string reg) {
    this->builder << "        sw      " << reg << ", 0(sp)\n"
                  << "        addi    sp, sp, " << -amount << "\n";
}
void Compiler::pull(int amount, std::string reg) {
    this->builder << "        lw      " << reg << ", 4(sp)\n"
                  << "        addi    sp, sp, " << amount << "\n";
}

Compiler::Compiler() {
    this->initHelper();
    this->printNumHelper();
    // this->setHelper();
    // this->refHelper();
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

    if (auto cast = dynamic_cast<AST::DefFun *>(ast)) {
        this->offsetFP = 0;
        this->varOffsetMap = {};
        this->builder << "_" << cast->name << ":\n"
                      << "        addi    sp, sp, -16\n"
                         "        sd      ra, 0(sp)\n"       // store ra
                         "        sd      fp, 8(sp)\n"       // store caller->fp
                         "        add     fp, zero, sp\n\n"; // init callee->fp
        compile(cast->body);
        this->builder << "\n"
                      << "        add     sp, zero, fp\n" // dealloc sp
                         "        ld      ra, 0(sp)\n"
                         "        ld      fp, 8(sp)\n"
                         "        addi    sp, sp, 16\n"
                         "        ret\n";
    }
    else if (auto cast = dynamic_cast<AST::RefFun *>(ast)) {
        this->builder << "        jal     ra, _" << cast->name << "\n";
    }
    else if (auto cast = dynamic_cast<AST::Do *>(ast)) {
        for (AST::Expression *e : cast->expressions) {
            compile(e);
        }
    }
    else if (auto cast = dynamic_cast<AST::Literal *>(ast)) {
        int value = std::atoi(cast->value.c_str());
        int lower = value & 0xFFF;
        int upper = value >> 12;
        if (value & 0x800) {
            upper++;
            lower -= 0x1000;
        }
        if (upper != 0) {
            this->builder << "        lui     a0, " << (upper & 0xFFFFF) << "\n";
        }
        if (lower != 0 || lower == 0 && upper == 0) {
            this->builder << "        addi    a0, zero, " << (lower & 0xFFF) << "\n";
        }
    }
    else if (auto cast = dynamic_cast<AST::Bin *>(ast)) {
        // todo: make other binops later
        // more todo: use reg alloc
        // even more todo: add a lowering step that turns (+ d4 d8) to (long+ (int2long d4) d8)
        compile(cast->left);
        this->builder << "        addi    sp, sp, -8\n" // :grimace:
                         "        sd      a0, 0(sp)\n";
        compile(cast->right);
        this->builder << "        ld      a1, 0(sp)\n"
                         "        addi    sp, sp, 8\n"
                         "        add     a0, a1, a0\n";
    }
    else if (auto cast = dynamic_cast<AST::DefVar *>(ast)) {
        
        int size = dataTypeToSize[cast->dataType];
        this->builder << "        addi    sp, sp, " << -size << "\n";
        offsetFP -= size;
        varOffsetMap[cast->name] = std::make_pair(cast->dataType, offsetFP);
    }
    else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
        compile(cast->data);
        std::string loadIns = dataTypeToLoadIns[cast->refTo];
        this->builder << "        " << loadIns << "    a0, 0(a0)\n";
    }
    else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
        // takes an lvalue
        compileLV(cast->data);
    }
    else if (auto cast = dynamic_cast<AST::RefVar *>(ast)) {
        // rvalue of var
        // (compile function assumes rvalue)
        std::string loadIns = dataTypeToLoadIns[varOffsetMap[cast->name].first];
        int offset = varOffsetMap[cast->name].second;
        this->builder << "        " << loadIns << "      a0, " << offset << "(fp)\n";
    }
    else if (auto cast = dynamic_cast<AST::Set *>(ast)) {
        // first arg is an lvalue
        AST::DataType storeDT = compileLV(cast->data);
        std::string storeIns = dataTypeToStoreIns[storeDT];
        this->builder << "        addi    sp, sp, -8\n"
                         "        sd      a0, 0(sp)\n";
        compile(cast->value);
        this->builder << "        ld      a1, 0(sp)\n"
                         "        addi    sp, sp, 8\n"
                         "        " << storeIns << "      a0, 0(a1)\n";
    }
}

AST::DataType Compiler::compileLV(AST::Expression *ast) {
    if (auto content = dynamic_cast<AST::DeRef *>(ast)) {
            // [dt]^B
        compile(content->data);     // compile B 
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
// void refHelper()