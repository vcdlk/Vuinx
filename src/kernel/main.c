#include <vinx/io.h>
#include <vinx/types.h>
#include <vinx/vinx.h>
#include <vinx/string.h>
#include <vinx/console.h>
#include <vinx/stdarg.h>
#include <vinx/stdio.h>
#include <vinx/assert.h>
#include <vinx/printk.h>
#include <vinx/debug.h>
#include <vinx/global.h>
#include <vinx/interrupt.h>

char message[] = "hellp world\n";
char buf[1024];

void test_args(int cnt, ...)
{
  va_list args;
  va_start(args, cnt);

  int arg;
  while (cnt--)
  {
    arg = va_arg(args, int);
  }
  va_end(args);
}

void kernel_init()
{
  console_init();
  gdt_init();
  // task_init();
  interrupt_init();
  // asm volatile(" \n int 0x80 \n");
  return;
}
