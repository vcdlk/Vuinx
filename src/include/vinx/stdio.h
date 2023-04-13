#ifndef _VINX_STDIO_H
#define _VINX_STDIO_H

#include <vinx/stdarg.h>

// 打印到 buf 中
int vsprintf(char *buf, const char *fmt, va_list args);

int sprintf(char *buf, const char *fmt, ...);

#endif