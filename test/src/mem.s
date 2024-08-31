        .global _malloc, _free, _hb_coreDump, _HEAP_INIT
_hb_setSize:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 32
        ret
_hb_getSize:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_hb_setNext:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 4
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 32
        ret
_hb_getNext:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 4
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        lw    a0, 0(a0)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_hb_toRealAddr:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _HEAP_HEAD
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_hb_getEnd:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        lw    a0, 0(a0)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_hb_coreDump:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 24(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
_L1:
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a0, a1
        sltiu   a0, a0, 1
        beq     a0, zero, _L2
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _print
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        ld    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 256
        ld      a1, 0(sp)
        addi    sp, sp, 8
        rem     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
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
        j       _L1
_L2:

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 32
        ret
_hb_heapSize:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        jal     ra, _HEAP_END
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _HEAP_HEAD
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
_malloc:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -8
        addi    sp, sp, -4
        addi    sp, sp, -4
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, fp, -12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, fp, -16
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _mlc_findRegion
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, -1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L4
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        j       _L3
_L4:
        addi    sp, sp, 0
        addi    a0, zero, 1
        beq     a0, zero, _L3
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _mlc_helper
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_toRealAddr
        ld      a1, 0(sp)
        addi    sp, sp, 8
        add     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        addi    sp, sp, 0
_L3:
        ld      a0, -8(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_mlc_helper:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getSize
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, -4
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getNext
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        lw      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setSize
        addi    sp, sp, -4
        addi    a0, fp, -12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    a0, zero, 0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a1, a0
        beq     a0, zero, _L6
        addi    sp, sp, -4
        addi    a0, fp, -16
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getEnd
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        lw      a0, -16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setSize
        lw      a0, -16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        lw      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        j       _L5
_L6:
        addi    sp, sp, -4
        addi    a0, zero, 1
        beq     a0, zero, _L5
        lw      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setSize
        lw      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        addi    sp, sp, -4
_L5:
        lw      a0, 32(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 40
        ret
_mlc_findRegion:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        ld      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        ld      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, -1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
_L7:
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 32(fp)
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getSize
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        and     a0, a1, a0
        sltu    a0, zero, a0
        beq     a0, zero, _L8
        lb      a0, 0(fp)
        ld      a0, 32(fp)
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_heapSize
        ld      a1, 0(sp)
        addi    sp, sp, 8
        xor     a0, a1, a0
        sltiu   a0, a0, 1
        beq     a0, zero, _L9
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, -1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
_L9:
        ld      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 32(fp)
        lw    a0, 0(a0)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        ld      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 32(fp)
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getNext
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
        j       _L7
_L8:
        lw      a0, -4(fp)

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 40
        ret
_free:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 16(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _HEAP_HEAD
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, -4
        addi    sp, sp, -4
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, fp, -12
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _fr_findNearByRegion
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -12(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 24
        ret
_fr_findNearByRegion:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        ld      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        ld      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, -1
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
_L10:
        ld      a0, 24(fp)
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, 16(fp)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        slt     a0, a1, a0
        beq     a0, zero, _L11
        ld      a0, 32(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 24(fp)
        lw    a0, 0(a0)
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        ld      a0, 24(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        ld      a0, 24(fp)
        lw    a0, 0(a0)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getNext
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        addi    sp, sp, 0
        j       _L10
_L11:
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 40
        ret
_HEAP_INIT:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    sp, sp, -4
        addi    a0, fp, -4
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setSize
        addi    sp, sp, -4
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_getEnd
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sw      a0, 0(a1)
        lw      a0, -4(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_heapSize
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 2
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 8
        ld      a1, 0(sp)
        addi    sp, sp, 8
        mul     a0, a1, a0
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sub     a0, a1, a0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setSize
        lw      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_heapSize
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_setNext
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
_test:
        addi    sp, sp, -16
        sd      ra, 0(sp)
        sd      fp, 8(sp)
        add     fp, zero, sp

        addi    a0, zero, 0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 32
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_coreDump
        addi    a0, zero, 100
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _malloc
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        addi    sp, sp, -8
        addi    a0, fp, -8
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 1
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _malloc
        ld      a1, 0(sp)
        addi    sp, sp, 8
        sd      a0, 0(a1)
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        addi    a0, zero, 1
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _malloc
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        addi    a0, zero, 1
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _malloc
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _println
        ld      a0, -8(fp)
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _free
        addi    a0, zero, 0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 32
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_coreDump
        addi    a0, zero, 1
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _malloc
        addi    a0, zero, 0
        addi    sp, sp, -8
        sd      a0, 0(sp)
        addi    a0, zero, 32
        addi    sp, sp, -8
        sd      a0, 0(sp)
        jal     ra, _hb_coreDump
        addi    a0, zero, 0

        add     sp, zero, fp
        ld      ra, 0(sp)
        ld      fp, 8(sp)
        addi    sp, sp, 16
        ret
