[bits 32]

extern kernel_init

global _start
_start:
    mov byte [0xb8000], 'K';     进入内核
    call kernel_init
    int 0x80
    xchg bx, bx
    jmp $; 阻塞