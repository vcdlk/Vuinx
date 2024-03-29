## 实模式的内存布局

| 起始地址  | 结束地址  | 大小     | 用途               |
| --------- | --------- | -------- | ------------------ |
| `0x000`   | `0x3FF`   | 1KB      | 中断向量表         |
| `0x400`   | `0x4FF`   | 256B     | BIOS 数据区        |
| `0x500`   | `0x7BFF`  | 29.75 KB | 可用区域           |
| `0x7C00`  | `0x7DFF`  | 512B     | MBR 加载区域       |
| `0x7E00`  | `0x9FBFF` | 607.6KB  | 可用区域           |
| `0x9FC00` | `0x9FFFF` | 1KB      | 扩展 BIOS 数据区   |
| `0xA0000` | `0xAFFFF` | 64KB     | 用于彩色显示适配器 |
| `0xB0000` | `0xB7FFF` | 32KB     | 用于黑白显示适配器 |
| `0xB8000` | `0xBFFFF` | 32KB     | 用于文本显示适配器 |
| `0xC0000` | `0xC7FFF` | 32KB     | 显示适配器 BIOS    |
| `0xC8000` | `0xEFFFF` | 160KB    | 映射内存           |
| `0xF0000` | `0xFFFEF` | 64KB-16B | 系统 BIOS          |
| `0xFFFF0` | `0xFFFFF` | 16B      | 系统 BIOS 入口地址 |
# 保护模式和全局描述符

8086 1M 内存，实模式，理论上病毒可以完全控制计算机；
80286 保护模式 16位

![](./images/80286-segment%20descriptor.jpg)

## 保护模式

- 信息：IT Information Technology 《信息论》
- 寄存器 / 有一些寄存器只能被操作系统访问
- 高速缓存
- 内存 / 描述符
- 外部设备 / 硬盘 / in/out

## 全局描述符

- 内存的起始位置
- 内存的长度 / 界限 = 长度 - 1
- 内存属性

![](./images/80386-segment%20descriptor.jpg)

```cpp
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
} __attribute__((packed)) descriptor;
```

## type segment = 1

| X | C/E | R/W | A |

- A: Accessed 是否被 CPU 访问过
- X: 1/代码 0/数据
- X = 1：代码段
    - C: 是否是依从代码段
    - R: 是否可读
- X = 0: 数据段
    - E: 0 向上扩展 / 1 向下扩展
    - W: 是否可写

## 全局描述符表 GDT Global Descriptor Table

- 表 - 数组 - 顺序表
- 链表 - 链表
- 哈希表

```cpp
descriptor gdt[8192];
```

- 0 必须全为 0 - NULL 描述符
- 8191 描述符

----

- gdtr / 全局描述符表的起始位置和长度

```s
lgdt [gdt_ptr]; 加载 gdt
sgdt [gdt_ptr]; 保存 gdt
```

```cpp
typedef struct pointer
{
    unsigned short limit; // size - 1
    unsigned int base;
} __attribute__((packed)) pointer;
```

## 段选择子

- 只需要一个代码段
- 需要一个或多个数据段 / 栈段 / 数据段
- 加载到段寄存器中 / 校验特权级

```cpp
typedef struct selector
{
    unsigned char RPL : 2; // Request PL 
    unsigned char TI : 1; // 0  全局描述符 1 局部描述符 LDT Local 
    unsigned short index : 13; // 全局描述符表索引
} __attribute__((packed)) selector;
```

- cs / ds / es / ss
- fs / gs

## A20 线

8086 1M 

段地址 * 16 + 偏移地址 > 1M

80286 16M 24 根地址线
386 32 地址线，4G

地址回绕

0x92 端口

- <https://wiki.osdev.org/A20>
- <https://wiki.osdev.org/Non_Maskable_Interrupt>

## PE Protect Enable

cr0 寄存器 0 位 置为 1
