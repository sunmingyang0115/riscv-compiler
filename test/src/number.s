        .global _number_new, _number_del, _number_get, _number_set
__number_key:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lui     a0, 228
        addi    a0, a0, -1875

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
__number_error:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    a0, zero, 404
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
_number_new:
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
        jal     ra, _malloc
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, __number_key
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        ld      a0, -8(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_number_del:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        ld      a0, 16(fp)
        ld    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, __number_key
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L2
        ld      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _free
        j       _L1
_L2:
        addi    sp, sp, 0
        addi    a0, zero, 1
        beq     a0, zero, _L1
        jal     ra, __number_error
        addi    sp, sp, 0
_L1:
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_number_get:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        ld      a0, 16(fp)
        ld    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, __number_key
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        lw    a0, 0(a0)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        j       _L3
_L4:
        addi    sp, sp, 0
        addi    a0, zero, 1
        beq     a0, zero, _L3
        jal     ra, __number_error
        addi    sp, sp, 0
_L3:
        lw      a0, -4(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_number_set:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        ld      a0, 24(fp)
        ld    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, __number_key
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L6
        ld      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        j       _L5
_L6:
        addi    sp, sp, 0
        addi    a0, zero, 1
        beq     a0, zero, _L5
        jal     ra, __number_error
        addi    sp, sp, 0
_L5:
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 32
        ret
