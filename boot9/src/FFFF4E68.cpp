#include "types.h"

void FUN_FFFF4E68(u32 unit, u16 value)
{
    u32 base = 0x10006000;
    if (unit != 1) {
        base = 0x10007000;
    }
    volatile u16 *reg = (volatile u16 *)(base + 0x24);
    *reg = (*reg & 0xff00) | value;
}
