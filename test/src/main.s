        .global _main
_main:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -8
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _number_new
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _number_get
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _number_set
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _number_get
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _number_del
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
