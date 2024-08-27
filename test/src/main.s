        .global _main
_isPrime:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L2
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        j       _L1
_L2:
        addi    sp, sp, 0
        addi    a0, zero, 1
        beq     a0, zero, _L1
        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 2
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
_L3:
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        mul     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a0, a1
        sltiu   a0, a0, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        and     a0, a1, a0
        sltu    a0, zero, a0
        beq     a0, zero, _L4
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        rem     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L5
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
_L5:
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
        j       _L3
_L4:
        addi    sp, sp, -4
_L1:
        lw      a0, -4(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_getNPrime:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        addi    sp, sp, -4
        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, -1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, fp, -12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
_L6:
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a1, a0
        beq     a0, zero, _L7
        lw      a0, -12(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _isPrime
        beq     a0, zero, _L8
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
_L8:
        addi    a0, fp, -12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
        j       _L6
_L7:
        lw      a0, -4(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_main:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    a0, zero, 27
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _getNPrime
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _print
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
