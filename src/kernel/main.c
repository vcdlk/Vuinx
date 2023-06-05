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
#include <vinx/clock.h>
#include <vinx/stdlib.h>

char message[] = "hellp world\n";
char buf[1024];

void kernel_init()
{
  console_init();
  gdt_init();
  // task_init();
  interrupt_init();
  clock_init();

  asm volatile("sti");
  hang();

  return;
}
