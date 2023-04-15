#include <vinx/stdarg.h>
#include <vinx/console.h>
#include <vinx/stdio.h>

extern void console_write();

static char buf[1024];

int printk(const char *fmt, ...)
{
    va_list args;
    int i = 0;

    va_start(args, fmt);

    i = vsprintf(buf, fmt, args);

    va_end(args);

    console_write(buf, i);
    return i;
}
