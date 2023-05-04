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

  int cnt = 23;
  while (cnt--)
  {
    printk("hello test %#010x\n", cnt);
  }

  printk("hello test %#010x\n", 1);
  printk("hello test %#010x\n", 2);
  printk("hello test %#010x\n", 3);

  console_write(message, sizeof(message) - 1);
  DEBUGK("Test %s", message);

  assert(1 < 2);
  assert(1 > 2);
  return;
}
