#include <vinx/io.h>
#include <vinx/types.h>
#include <vinx/vinx.h>
#include <vinx/string.h>
#include <vinx/console.h>
#include <vinx/stdarg.h>

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
  // ConsoleInit();
  // uint32_t count = 20;
  // while (count--)
  // {
  //   ConsoleWrite(message, sizeof(message) - 1);
  // }

  // ConsoleWrite(message, sizeof(message) - 1);
  test_args(5, 1, 0xaa, 6, 0x55, 10);
  return;
}
