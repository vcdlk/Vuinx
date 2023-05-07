#ifndef _VINX_TASK_H
#define _VINX_TASK_H

#include <vinx/types.h>

typedef uint32_t target_t();

typedef struct task_t
{
    uint32_t *stack;
} task_t;

typedef struct task_frame_t
{
    uint32_t edi;
    uint32_t esi;
    uint32_t ebx;
    uint32_t ebp;
    void (*eip)(void);
} task_frame_t;

void task_init();

#endif