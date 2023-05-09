#include <vinx/global.h>
#include <vinx/string.h>
#include <vinx/debug.h>
descriptor_t gdt[GDT_SIZE];
pointer_t gdt_ptr;

void gdt_init()
{
    BMB;
    DEBUGK("init gdt");
    asm volatile("sgdt gdt_ptr");

    memcpy(&gdt, (void *)gdt_ptr.base, gdt_ptr.limit + 1);

    gdt_ptr.base = (uint32_t)&gdt;
    gdt_ptr.limit = sizeof(gdt) - 1;

    asm volatile("lgdt gdt_ptr\n");
    BMB;
}
