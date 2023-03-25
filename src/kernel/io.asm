[bits 32]

section .text;  // 代码段

global Inb; // inb 函数导出

Inb :
    push ebp;
    mov ebp, esp;  保存栈帧

    xor eax, eax; // eax 清空
    mov edx, [ebp + 8]; // port
    in al, dx;

    jmp $ + 2;
    jmp $ + 2;
    jmp $ + 2;   

    leave; 
    ret;


