#include <vinx/io.h>
#include <vinx/interrupt.h>
#include <vinx/assert.h>
#include <vinx/debug.h>

#define PIT_CHAN0_REG 0X40
#define PIT_CHAN2_REG 0X42
#define PIT_CTRL_REG 0X43

#define HZ 100
#define OSCILLATOR 1193182
#define CLOCK_COUNTER (OSCILLATOR / HZ)
#define JIFFY (1000 / HZ)

#define SPEAKER_REG 0x61
#define BEEP_HZ 440
#define BEEP_COUNTER (OSCILLATOR / BEEP_HZ)

uint32_t volatile jiffies = 0;
uint32_t jiffy = JIFFY;

uint32_t volatile beeping = 0;

// 定时器中断处理函数
void clock_handler(int vector)
{
    assert(vector == 0x20);
    send_eoi(vector);
    jiffies++;
    DEBUGK("clock jiffies %d ...\n", jiffies);
}

// 计时器初始化
void pit_init()
{
    // 配置计数器 0 时钟
    outb(PIT_CTRL_REG, 0b00110100); // 00 计数器0  11 先读写地址字节，后高字节 010 模式2 0 二进制计数
    outb(PIT_CHAN0_REG, CLOCK_COUNTER & 0xff);
    outb(PIT_CHAN0_REG, (CLOCK_COUNTER >> 8) & 0xff);
}

// 时钟初始化
void clock_init()
{
    pit_init();
    set_interrupt_handler(IRQ_CLOCK, clock_handler);
    set_interrupt_mask(IRQ_CLOCK, true);
}