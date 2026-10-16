#include "types.h"

extern volatile u32 DAT_17E01200[];

u32 FUN_00012808(s32 irq)
{
    s32 index = irq / 32;
    s32 bit = irq % 32;
    volatile u32* reg = &DAT_17E01200[index];
    return (*reg >> bit) & 1;
}
