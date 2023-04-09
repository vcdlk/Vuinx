#ifndef VINUX__TYPES_H_
#define VINUX__TYPES_H_

#define EOF -1           // END OF FILE
#define NULL ((void *)0) // 空指针
#define EOS '\0'

#define bool _Bool
#define true 1
#define false 0

#define _packed __attribute__((packed))

typedef unsigned int size_t;
typedef char int8;
typedef short int16;
typedef long long int32;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#endif