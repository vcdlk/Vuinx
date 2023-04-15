#ifndef _VINX_CONSOLE_H
#define _VINX_CONSOLE_H
#include <vinx/types.h>

void console_init(void);
void console_clear(void);
void console_write(char *buf, uint32_t count);

#endif