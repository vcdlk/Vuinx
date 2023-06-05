#ifndef _VINIX_INTERRUPT_H
#define _VINIX_INTERRUPT_H

#include <vinx/types.h>

#define IDT_SIZE 256

#define IRQ_CLOCK 0      // 时钟
#define IRQ_KEYBOARD 1   // 键盘
#define IRQ_CASCADE 2    // 8259 从片控制器
#define IRQ_SERIAL_2 3   // 串口 2
#define IRQ_SERIAL_1 4   // 串口 1
#define IRQ_PARALLEL_2 5 // 并口 2
#define IRQ_FLOPPY 6     // 软盘控制器
#define IRQ_PARALLEL_1 7 // 并口 1
#define IRQ_RTC 8        // 实时时钟
#define IRQ_REDIRECT 9   // 重定向 IRQ2
#define IRQ_MOUSE 12     // 鼠标
#define IRQ_MATH 13      // 协处理器 x87
#define IRQ_HARDDISK 14  // ATA 硬盘第一通道
#define IRQ_HARDDISK2 15 // ATA 硬盘第二通道

#define IRQ_MASTER_NR 0x20 // 主片起始向量号
#define IRQ_SLAVE_NR 0x28  // 从片起始向量号

typedef struct gate_t
{
    uint16_t offset0;    // 段内偏移 0 ~ 15 位
    uint16_t selector;   // 代码段选择子
    uint8_t reserved;    // 保留不用
    uint8_t type : 4;    // 任务门/中断门/陷阱门
    uint8_t segment : 1; // segment = 0 表示系统段
    uint8_t DPL : 2;     // 使用 int 指令访问的最低权限
    uint8_t present : 1; // 是否有效
    uint16_t offset1;    // 段内偏移 16 ~ 31 位
} _packed gate_t;
typedef void *handler_t; // 中断处理函数

void interrupt_init();
void send_eoi(int vector);

// 设置中断处理器函数
void set_interrupt_handler(uint32_t irq, handler_t handler);
void set_interrupt_mask(uint32_t irq, bool enable);

#endif
