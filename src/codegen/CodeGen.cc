#include "CodeGen.hh"
#include "Compiler.hh"

// std::string getNewLabel() {
//     static int n = 0;
//     return "_L" + std::to_string(n++);
// }

// std::string binOpToInstruction(AST::BinOp op) {
//     // todo: add short circuiting to some binops
//     switch (op) {
//     case AST::BinOp::ADD:
//         return "        add     a0, a1, a0\n";
//     case AST::BinOp::SUB:
//         return "        sub     a0, a1, a0\n";
//     case AST::BinOp::DIV:
//         return "        div     a0, a1, a0\n";
//     case AST::BinOp::MUL:
//         return "        mul     a0, a1, a0\n";
//     case AST::BinOp::MOD:
//         return "        rem     a0, a1, a0\n";
//     case AST::BinOp::AND:
//         return "        and     a0, a1, a0\n"
//                "        sltu    a0, zero, a0\n";
//     case AST::BinOp::OR:
//         return "        or      a0, a1, a0\n"
//                "        sltiu   a0, a0, 1\n"
//                "        xori    a0, a0, 1\n";
//     case AST::BinOp::GT:
//         return "        slt     a0, a0, a1\n";
//     case AST::BinOp::LT:
//         return "        slt     a0, a1, a0\n";
//     case AST::BinOp::GEQ:
//         return "        slt     a0, a1, a0\n"
//                "        sltiu   a0, a0, 1\n";
//     case AST::BinOp::LEQ:
//         return "        slt     a0, a0, a1\n"
//                "        sltiu   a0, a0, 1\n";
//     case AST::BinOp::EQ:
//         return "        xor     a0, a1, a0\n"
//                "        sltiu   a0, a0, 1\n";
//     case AST::BinOp::NEQ:
//         return "        xor     a0, a1, a0\n"
//                "        sltu    a0, x0, a0\n";
//     case AST::BinOp::XOR:
//         return "        xor     a0, a1, a0\n"
//                "        sltu    a0, x0, a0\n";
//     case AST::BinOp::BSL:
//         return "        sll     a0, a1, a0\n";
//     case AST::BinOp::BSR:
//         return "        sra     a0, a1, a0\n";
//     }
//     exit(1);
// }

// int dataTypeToSize(AST::DataType dt) {
//     switch (dt) {
//     case AST::DataType::D1:
//         return 1;
//     case AST::DataType::D2:
//         return 2;
//     case AST::DataType::D4:
//         return 4;
//     case AST::DataType::D8:
//         return 8;
//     }
//     return -1;
// }

// std::string dataTypeToInstruction(int n) {
//     switch (n) {
//     case 0:
//         return "b";
//     case 1:
//         return "h";
//         break;
//     case 2:
//         return "w";
//     case 3:
//         return "d";
//     }
//     return "-1";
// }

// class CompilerHelper {
// private:
//     std::stringstream builder;
//     std::unordered_map<std::string, int> varOffsetMap;
//     RegAlloc allocator;
//     int offsetFP;
//     void push(int amount, std::string reg) {
//         builder << "        sw      " << reg << ", 0(sp)\n"
//                 << "        addi    sp, sp, " << -amount << "\n";
//     }
//     void pull(int amount, std::string reg) {
//         builder << "        lw      " << reg << ", 4(sp)\n"
//                 << "        addi    sp, sp, " << amount << "\n";
//     }

// public:
//     CompilerHelper() : builder{}, varOffsetMap{}, offsetFP{0}, allocator{} {
//         builder << "        .global _start\n"
//                 << "_start: addi    sp, sp, 400\n" // reserve stack mem
//                 << "        jal     ra, main\n"
//                 << "        addi    a7, x0, 93\n"
//                 << "        ecall\n";
//         // helper functions
//         std::string isZero = getNewLabel(); 
//         std::string isOne = getNewLabel(); 
//         std::string isTwo = getNewLabel(); 
//         std::string isThree = getNewLabel();
//         std::string end = getNewLabel(); 
//         builder << "_sethelper:\n"  // a1 = addr, a0 = value
//                 << "        lb      t0, 1(a1)\n"   // a0 = datatype
//                 << "        addi    t1, t0, 0\n"
//                 << "        beq     t1, zero, " << isZero << "\n"   // = 0
//                 << "        addi    t1, t0, -1\n"
//                 << "        beq     t1, zero, " << isOne << "\n"   // = 1
//                 << "        addi    t1, t0, -2\n"
//                 << "        beq     t1, zero, " << isTwo << "\n"   // = 2
//                 << "        addi    t1, t0, -3\n"
//                 << "        beq     t1, zero, " << isThree << "\n"   // = 3
//                 << "        j       _sethelper" << "\n"  // should never be here
//                 << isZero << ":\n"
//                 << "        addi    a1, zero, 0\n"
//                 << "        sb      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isOne << ":\n"
//                 << "        addi    a1, zero, 1\n"
//                 << "        sh      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isTwo << ":\n"
//                 << "        addi    a1, zero, 3\n"
//                 << "        sw      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isThree << ":\n"
//                 << "        addi    a1, zero, 7\n"
//                 << "        sd      a0, 0(a1)\n"
//                 << end << ":\n"
//                 << "        ret\n";
//         isZero = getNewLabel(); 
//         isOne = getNewLabel(); 
//         isTwo = getNewLabel(); 
//         isThree = getNewLabel();
//         end = getNewLabel(); 
//         builder << "_gethelper:\n"  // a1 = addr, a0 = value
//                 << "        lb      t0, 1(a1)\n"   // a0 = datatype
//                 << "        addi    t1, t0, 0\n"
//                 << "        beq     t1, zero, " << isZero << "\n"   // = 0
//                 << "        addi    t1, t0, -1\n"
//                 << "        beq     t1, zero, " << isOne << "\n"   // = 1
//                 << "        addi    t1, t0, -2\n"
//                 << "        beq     t1, zero, " << isTwo << "\n"   // = 2
//                 << "        addi    t1, t0, -3\n"
//                 << "        beq     t1, zero, " << isThree << "\n"   // = 3
//                 << "        j       _sethelper" << "\n"  // should never be here
//                 << isZero << ":\n"
//                 << "        addi    a1, zero, 0\n"
//                 << "        lb      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isOne << ":\n"
//                 << "        addi    a1, zero, 1\n"
//                 << "        lh      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isTwo << ":\n"
//                 << "        addi    a1, zero, 3\n"
//                 << "        lw      a0, 0(a1)\n"
//                 << "        j       " << end << "\n"
//                 << isThree << ":\n"
//                 << "        addi    a1, zero, 7\n"
//                 << "        ld      a0, 0(a1)\n"
//                 << end << ":\n"
//                 << "        ret\n";
//     }
//     void compile(AST::Expression *ast) {
//         if (auto cast = dynamic_cast<AST::Literal *>(ast)) {
//             int value = std::atoi(cast->value.c_str());
//             builder << "        addi    a0, zero, " << value << "\n";
//             // todo: make this not error for litearls [2047, -2048]
//         } else if (auto cast = dynamic_cast<AST::DefFun *>(ast)) {
//             // todo: load arguments
//             // 'callee'
//             offsetFP = 0;
//             varOffsetMap = {};
//             builder << cast->name << ":\n"
//                     << "        sd      ra, 0(sp)\n"  // store ra
//                     << "        sd      fp, -8(sp)\n" // store caller->fp
//                     << "        addi    sp, sp, -16\n"
//                     << "        add     fp, zero, sp\n\n"; // init callee->fp
//             compile(cast->body);
//             builder << "\n"
//                     << "        add     sp, zero, fp\n" // dealloc sp
//                     << "        addi    sp, sp, 16\n"
//                     << "        ld      ra, 0(sp)\n"
//                     << "        ld      fp, -8(sp)\n"
//                     << "        ret\n";

//         } else if (auto cast = dynamic_cast<AST::Do *>(ast)) {
//             for (AST::Expression *e : cast->expressions) {
//                 compile(e);
//             }
//         } else if (auto cast = dynamic_cast<AST::RefFun *>(ast)) {
//             // todo: load args
//             for (int i = 0; i < cast->arguments.size(); i++) {
//                 compile(cast->arguments.at(i));
//             }
//             builder << "        jal     ra, " << cast->name << "\n";
//         } else if (auto cast = dynamic_cast<AST::Bin *>(ast)) {
//             int r = allocator.newReg();
//             if (r == -1) {
//                 compile(cast->left);
//                 push(4, "a0");
//                 compile(cast->right);
//                 pull(4, "a1");
//                 builder << binOpToInstruction(cast->op);
//             } else {
//                 compile(cast->left);
//                 builder << "        add     t" << r << ", zero, a0\n";
//                 compile(cast->right);
//                 builder << "        add     a1, zero, t" << r << "\n"
//                         << binOpToInstruction(cast->op);
//                 allocator.freeReg(r);
//             }
//         } else if (auto cast = dynamic_cast<AST::DefVar *>(ast)) {
//             // todo: add other datatypes
//             int size = -1;
//             switch (cast->dataType) {
//             case AST::DataType::D1:
//                 size = 1;
//                 break;
//             case AST::DataType::D2:
//                 size = 2;
//                 break;
//             case AST::DataType::D4:
//                 size = 4;
//                 break;
//             case AST::DataType::D8:
//                 size = 8;
//                 break;
//             }
//             builder << "        add     a0, zero, " << cast->dataType << "\n"
//                     << "        sb      a0, 0(sp)\n"
//                     << "        addi    sp, sp, " << -(size + 1) << "\n";
//             varOffsetMap[cast->name] = offsetFP - 1;
//             offsetFP -= size+1;
//         } else if (auto cast = dynamic_cast<AST::RefVar *>(ast)) {
//             builder << "        addi    a0, fp, " << varOffsetMap[cast->name] << "\n";
//         } else if (auto cast = dynamic_cast<AST::Set *>(ast)) {
//             int r = allocator.newReg();
//             if (r == -1) {
//                 compile(cast->data);
//                 push(4, "a0");
//                 compile(cast->value);
//                 pull(4, "a1");
//                 builder << "        jal     ra, _sethelper\n";
//             } else {
//                 compile(cast->data);
//                 builder << "        add     t" << r << ", zero, a0\n";
//                 compile(cast->value);
//                 builder << "        add     a1, zero, t" << r << "\n";
//                 builder << "        jal     ra, _sethelper\n";
//                 allocator.freeReg(r);
//             }

//         } else if (auto cast = dynamic_cast<AST::DeRef *>(ast)) {
//             compile(cast->data);
//             builder << "        jal     ra, _gethelper\n";
//         } else if (auto cast = dynamic_cast<AST::AddrOf *>(ast)) {
//         } else if (auto cast = dynamic_cast<AST::Not *>(ast)) {
//             compile(cast->value);
//             builder << "        sltiu   a0, a0, 1\n";
//         } else if (auto cast = dynamic_cast<AST::Cond *>(ast)) {
//             std::string endIf = getNewLabel();
//             for (int i = 0; i < cast->conds.size(); i++) {
//                 bool last = i == cast->conds.size() - 1;
//                 std::string next = last ? endIf : getNewLabel();

//                 compile(cast->conds.at(i));
//                 builder << "        beq     a0, x0, " << next << "\n";
//                 int beginning = offsetFP;
//                 compile(cast->thens.at(i));
//                 int diff = offsetFP - beginning;
//                 builder << "        addi    sp, sp, " << -diff << "\n"; // dealloc memory
//                 if (!last)
//                     builder << "        j       " << endIf << "\n";

//                 builder << next << ":\n";
//             }
//         }
//     }
//     bool finalize(std::string file) {
//         std::ofstream out{file};
//         out << builder.rdbuf();
//         out.close();
//         return true;
//     }
// };

bool compile(std::string file, AST::Expression *ast) {
    Compiler ch{};
    ch.compile(ast);
    return ch.finalize(file);
}
