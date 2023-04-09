[bits 32]

section .text;  // 代码段

global Inb; // inb 函数导出
global Inw; // inw 函数导出
global Outb;    输出1个字节
global Outw;    输出2个字节

Inb :
    push ebp;
    mov ebp, esp;  保存栈帧

    xor eax, eax ; 将 eax 清空
    mov edx, [ebp + 8]; port 
    in al, dx; 将端口号 dx 的 8 bit 输入到 al

    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟

    leave ; 恢复栈帧
    ret;


Inw :
    push ebp;
    mov ebp, esp;  保存栈帧

    xor eax, eax ; 将 eax 清空
    mov edx, [ebp + 8]; port 
    in ax, dx; 将端口号 dx 的 16 bit 输入到 ax

    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟

    leave; 
    ret;

Outb:
    push ebp;
    mov ebp, esp;  保存栈帧

    mov edx, [ebp + 8]; port
    mov eax, [ebp + 12]; value
    out dx, al; 将al 中的8bit输出到端口号dx

    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟

    leave; 
    ret;



Outw:
    push ebp;
    mov ebp, esp;  保存栈帧

    mov edx, [ebp + 8]; port
    mov eax, [ebp + 12]; value
    out dx, ax; 将al 中的8bit输出到端口号dx

    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟
    jmp $+2 ; 一点点延迟

    leave; 
    ret;
