[bits 32]


global _start
_start:
    mov byte [0xb8000], 'K';     进入内核
    jmp $; 阻塞