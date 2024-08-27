#include "Compiler.hh"

void Compiler::initHelper() {
    this->builder << ".section .text\n"
                     "        .globl _start\n"
                     "_start: addi    sp, sp, 160\n" // reserve stack mem
                     "        jal     ra, _main\n"
                     "        addi    a7, x0, 93\n"
                     "        ecall\n";
}
void Compiler::printNumHelper() {
    this->builder << "_print: ld      t0, 0(sp)\n"
                     "        addi    t1, zero, '\\n'\n"
                     "        addi    sp, sp, -1\n"
                     "        sb      t1, 0(sp)\n"
                     "        addi    t2, zero, 1\n"
                     "        addi    t3, zero, 10\n"    // base
                     "pr1:    remu    t1, t0, t3\n"
                     "        add     t1, t1, '0'\n"
                     "        addi    sp, sp, -1\n"
                     "        sb      t1, 0(sp)\n"
                     "        addi    t2, t2, 1\n"
                     "        divu    t0, t0, t3\n"
                     "        beq     t0, zero, pr2\n"
                     "        j       pr1\n"
                     "pr2:    addi    a0, zero, 1\n"
                     "        addi    a1, sp, 0\n"
                     "        add     a2, zero, t2\n"
                     "        addi    a7, zero, 64\n"
                     "        ecall\n"
                     "        add     t2, t2, 8\n"
                     "        add     sp, sp, t2\n"
                     "        ret\n";
}
