#include "types.h"

u16 FUN_FFFF4FB8(u32 unit, u32 offset, u16 mask)
{
    u32 base = 0x10006000;
    if (unit != 1)
    {
        base = 0x10007000;
    }
    volatile u16 *reg = (volatile u16 *)(base + offset);
    u16 old = *reg;
    *reg = ~(old & mask);
    return old;
}
