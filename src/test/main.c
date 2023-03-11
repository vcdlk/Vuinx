#include <vinx/types.h>
#include <stdio.h>

typedef struct descriptor /* 共 8 个字节 */
{
    unsigned short limit_low;      // 段界限 0 ~ 15 位
    unsigned int base_low : 24;    // 基地址 0 ~ 23 位 16M
    unsigned char type : 4;        // 段类型
    unsigned char segment : 1;     // 1 表示代码段或数据段，0 表示系统段
    unsigned char DPL : 2;         // Descriptor Privilege Level 描述符特权等级 0 ~ 3
    unsigned char present : 1;     // 存在位，1 在内存中，0 在磁盘上
    unsigned char limit_high : 4;  // 段界限 16 ~ 19;
    unsigned char available : 1;   // 该安排的都安排了，送给操作系统吧
    unsigned char long_mode : 1;   // 64 位扩展标志
    unsigned char big : 1;         // 32 位 还是 16 位;
    unsigned char granularity : 1; // 粒度 4KB 或 1B
    unsigned char base_high;       // 基地址 24 ~ 31 位
}  descriptor;
// __attribute__((packed))

int main(){
    printf("size of uint8_t:%d\n",sizeof (1));
    printf("size of uint16_t:%d\n",sizeof(uint16_t));
    printf("size of uint32_t:%d\n",sizeof(uint32_t));
    printf("size of uint64_t:%d\n",sizeof(uint64_t));
    printf("size of descriptor:%d\n",sizeof(descriptor));

    descriptor des;
    return 0;
}

