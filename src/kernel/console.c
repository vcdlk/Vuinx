#include <vinx/console.h>
#include <vinx/io.h>
#include <vinx/string.h>

#define CRT_ADDR_REG 0x3D4 // CRT(6845)索引寄存器
#define CRT_DATA_REG 0x3D5 // CRT(6845)数据寄存器

#define CRT_START_ADDR_H 0xC // 显示内存起始位置 - 高位
#define CRT_START_ADDR_L 0xD // 显示内存起始位置 - 低位
#define CRT_CURSOR_H 0xE     // 光标位置 - 高位
#define CRT_CURSOR_L 0xF     // 光标位置 - 低位

#define MEM_BASE 0xB8000              // 显卡内存起始位置
#define MEM_SIZE 0x4000               // 显卡内存大小
#define MEM_END (MEM_BASE + MEM_SIZE) // 显卡内存结束位置
#define WIDTH 80                      // 屏幕文本列数
#define HEIGHT 25                     // 屏幕文本行数
#define ROW_SIZE (WIDTH * 2)          // 每行字节数
#define SCR_SIZE (ROW_SIZE * HEIGHT)  // 屏幕字节数

#define ASCII_NULL 0x00
#define ASCII_ENQ 0x05
#define ASCII_BEL 0x07 // \a
#define ASCII_BS 0x08  // \b
#define ASCII_HT 0x09  // \t
#define ASCII_LF 0x0A  // \n
#define ASCII_VT 0x0B  // \v
#define ASCII_FF 0x0C  // \f
#define ASCII_CR 0x0D  // \r
#define ASCII_DEL 0x7F

static uint32_t screen; // 记录当前显示器开始的内存位置
static uint32_t pos;    // 记录当前光标的内存位置

static x, y;                    // 光标位置
static uint8_t attr = 7;        // 字符样式
static uint16_t erase = 0x0720; // 空格

// 获取当前显示器的开始位置
static void GetScrean()
{
    Outb(CRT_ADDR_REG, CRT_START_ADDR_H); // 读取位置高8位
    screen = Inb(CRT_DATA_REG) << 8;
    Outb(CRT_ADDR_REG, CRT_START_ADDR_L); // 读取位置低8位
    screen |= Inb(CRT_DATA_REG);

    screen <<= 1;       // screen *= 2
    screen += MEM_BASE; // 地址位置
    return;
}

// 设置屏幕寄存器位置
static void SetScreen()
{
    Outb(CRT_ADDR_REG, CRT_START_ADDR_H);
    Outb(CRT_DATA_REG, ((screen - MEM_BASE) >> 9) & 0xff);
    Outb(CRT_ADDR_REG, CRT_START_ADDR_L);
    Outb(CRT_DATA_REG, ((screen - MEM_BASE) >> 1) & 0xff);
    return;
}

// 获取光标位置
static void GetCursor()
{
    Outb(CRT_ADDR_REG, CRT_CURSOR_H);
    pos = Inb(CRT_DATA_REG) << 8;
    Outb(CRT_ADDR_REG, CRT_CURSOR_L);
    pos |= Inb(CRT_DATA_REG);

    GetScrean();
    pos <<= 1;
    pos += MEM_BASE;

    uint32_t delta = (pos - screen) >> 1;
    x = delta % WIDTH;
    y = delta / WIDTH;
    return;
}

// 设置光标位置
static void SetCursor()
{
    Outb(CRT_ADDR_REG, CRT_CURSOR_H);
    Outb(CRT_DATA_REG, ((pos - MEM_BASE) >> 9) & 0xff);
    Outb(CRT_ADDR_REG, CRT_CURSOR_L);
    Outb(CRT_DATA_REG, ((pos - MEM_BASE) >> 1) & 0xff);
}
// 退一个字符
static void CommandBs()
{
    if (x)
    {
        x--;
        pos -= 2;
        *(uint16_t *)pos = erase;
    }
}

// 删除当前字符
static void CommandDel()
{
    *(uint16_t *)pos = erase;
}

// 回到当前位置
static void CommandCr()
{
    pos -= (x << 1);
    x = 0;
}

// 屏幕向上滚一行
static void ScrollUp()
{
    if (screen + SCR_SIZE + ROW_SIZE < MEM_END)
    {
        uint32_t *ptr = (uint32_t *)(screen + SCR_SIZE);
        for (size_t i = 0; i < WIDTH; i++)
        {
            *ptr++ = erase;
        }
        screen += ROW_SIZE;
        pos += ROW_SIZE;
    }
    else
    {
        memcpy(MEM_BASE, screen, SCR_SIZE);
        pos -= (screen - MEM_BASE);
        screen = MEM_BASE;
    }
    SetCursor();
    return 0;
}

// \n
static void CommandLf()
{
    if (y + 1 < HEIGHT)
    {
        y++;
        pos += ROW_SIZE;
        return;
    }
    ScrollUp();
}

// 屏幕初始化
void ConsoleInit(void)
{
    ConsoleClear();
    return;
}

// 屏幕清空
void ConsoleClear(void)
{
    screen = MEM_BASE;
    pos = MEM_BASE;
    x = 0;
    y = 0;
    SetCursor();
    SetScreen();

    uint16_t *ptr = (uint16_t *)MEM_BASE;
    while (ptr < MEM_END)
    {
        *ptr++ = erase;
    }

    return;
}

// 向屏幕写字符
void ConsoleWrite(char *buf, uint32_t count)
{
    char ch;
    char *ptr = (char *)pos;
    while (count--)
    {
        ch = *buf;
        buf++;
        switch (ch)
        {
        case ASCII_NULL:
            break;
        case ASCII_BEL:
            // todo start_beep();
            break;
        case ASCII_BS:
            CommandBs();
            break;
        case ASCII_HT:
            break;
        case ASCII_LF:
            CommandLf();
            CommandCr();
            break;
        case ASCII_VT:
            break;
        case ASCII_FF:
            CommandLf();
            break;
        case ASCII_CR:
            CommandCr();
            break;
        case ASCII_DEL:
            CommandDel();
            break;

        default:
        {
            if (x >= WIDTH)
            {
                x -= WIDTH;
                pos -= ROW_SIZE;
                CommandLf();
            }
            *ptr = ch;
            ptr++;
            *ptr = attr;
            ptr++;
            pos += 2;
            x++;

            break;
        }
        }
        SetCursor();
    }

    return;
}