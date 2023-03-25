#include <vinx/io.h>
#include <vinx/types.h>
#include <vinx/vinx.h>

int magic = VINUX_MAGIC;
char message[] = "Hello Vinx!!!";
char buf[1024];

#define CRT_ADDR_REG 0x3d4
#define CRT_DATA_REG 0x3d5

#define CRT_CURSOR_H 0xe
#define CRT_CURSOR_L 0xf

void kernel_init()
{
  //   char *video = (char *)0xb8000;
  //   for (int i = 0; i < sizeof message; i++) {
  //     video[i * 2] = message[i];
  //   }
  uint8_t data = Inb(CRT_DATA_REG);
  return;
}
