#ifndef _VINX_CONSOLE_H
#define _VINX_CONSOLE_H
#include <vinx/types.h>

void ConsoleInit(void);
void ConsoleClear(void);
void ConsoleWrite(char *buf, uint32_t count);

#endif