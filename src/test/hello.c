#include <stdio.h>

char message[] = "hello world!!!\n";
char buf[1024]; // .bss

int main()
{
    printf(message);
    printf("Decimals:%#x10d\n", 1977);
    printf("Decimals:%#e10d\n", 1977);
    printf("Decimals:%02d\n", 1977);

    return 0;
}
