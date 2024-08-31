        .global _start

_start: addi    sp, sp, 160
        jal     ra, _main
        addi    a7, x0, 93
        ecall
