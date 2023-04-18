#include "vinx/assert.h"
#include "vinx/printk.h"
#include "vinx/types.h"
#include "vinx/stdarg.h"
#include "vinx/stdio.h"

static buf[1024];

static void spin(char *name)
{
    printk("spinning in %s ...\n", name);
    while (true)
        ;
}

void assertion_failure(char *exp, char *file, char *base, int line)
{
    printk("\n-->assert(%s) faile! \n"
           "-->file %s \n"
           "-->base:%s"
           "-->line:%s",
           exp, file, base, line);
    spin("assertion_failure()");

    // 不可能😼到这里
    asm volatile("ud2");
}

void panic(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    int i = vsprintf(buf, fmt, args);
    va_end(args);
    printk("!!!panic!!\n %s", buf);
    spin("panic");
    asm volatile("ud2");
}
