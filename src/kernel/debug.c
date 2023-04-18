#include "vinx/debug.h"
#include "vinx/stdarg.h"
#include "vinx/stdio.h"
#include "vinx/printk.h"

static char buf[1024];

void debugk(char *file, int line, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf(buf, fmt, args);
    printk("[%s] [%d] [%s]", file, line, buf);
    va_end(args);
}
