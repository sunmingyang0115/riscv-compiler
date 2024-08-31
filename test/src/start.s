STACK_SIZE: .quad 2048
HEAP_SIZE:  .quad 65535

        .global _start, _HEAP_HEAD, _HEAP_END

_HEAP_HEAD:
        add     a0, zero, gp
        ret

_HEAP_END:
        ld      a0, HEAP_SIZE
        add     a0, gp, a0
        ret

_start: 
        ld      a0, HEAP_SIZE
        sub     gp, sp, a0

        jal     ra, _HEAP_INIT

        ld      a0, STACK_SIZE
        add     sp, sp, a0
        
        jal     ra, _main
        addi    a7, x0, 93
        ecall
