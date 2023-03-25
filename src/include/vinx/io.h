#ifndef VINUX_IO_H
#define VINUX_IO_H

#include "types.h"
#include <vinx/types.h>

extern uint8_t Inb(uint16_t port);  // 输入1个字节
extern uint16_t Inw(uint16_t port); //  输入2个字节

extern void Iutb(uint16_t port, uint8_t value);  // 输出1个字节
extern void Iutw(uint16_t port, uint16_t value); //  输出2个字节

#endif