#include <vinx/io.h>
#include <vinx/types.h>
#include <vinx/vinx.h>
#include <vinx/string.h>
#include <vinx/console.h>

char message[] = "hellp world";
char buf[1024];

void kernel_init()
{
  ConsoleInit();
  return;
}
