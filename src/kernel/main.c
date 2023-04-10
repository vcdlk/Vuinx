#include <vinx/io.h>
#include <vinx/types.h>
#include <vinx/vinx.h>
#include <vinx/string.h>
#include <vinx/console.h>

char message[] = "hellp world\n";
char buf[1024];

void kernel_init()
{
  ConsoleInit();
  uint32_t count = 20;
  while (count--)
  {
    ConsoleWrite(message, sizeof(message) - 1);
  }

  ConsoleWrite(message, sizeof(message) - 1);
  return;
}
