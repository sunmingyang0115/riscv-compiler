        .global _println, _print
    
_print: ld      t0, 0(sp)
        addi    t1, zero, '\t'
        addi    sp, sp, -1
        sb      t1, 0(sp)
        addi    t2, zero, 1
        addi    t3, zero, 10
pr1:    remu    t1, t0, t3
        add     t1, t1, '0'
        addi    sp, sp, -1
        sb      t1, 0(sp)
        addi    t2, t2, 1
        divu    t0, t0, t3
        beq     t0, zero, pr2
        j       pr1
pr2:    addi    a0, zero, 1
        addi    a1, sp, 0
        add     a2, zero, t2
        addi    a7, zero, 64
        ecall
        add     t2, t2, 8
        add     sp, sp, t2
        ret

_println: ld      t0, 0(sp)
        addi    t1, zero, '\n'
        addi    sp, sp, -1
        sb      t1, 0(sp)
        addi    t2, zero, 1
        addi    t3, zero, 10
prl1:    remu    t1, t0, t3
        add     t1, t1, '0'
        addi    sp, sp, -1
        sb      t1, 0(sp)
        addi    t2, t2, 1
        divu    t0, t0, t3
        beq     t0, zero, prl2
        j       prl1
prl2:    addi    a0, zero, 1
        addi    a1, sp, 0
        add     a2, zero, t2
        addi    a7, zero, 64
        ecall
        add     t2, t2, 8
        add     sp, sp, t2
        ret
