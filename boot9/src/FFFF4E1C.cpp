#include "types.h"

void FUN_FFFF4E1C(u32 unit, u16 value)
{
    u32 base = 0x10006000;
    if (unit != 1) {
        base = 0x10007000;
    }
    volatile u16 *reg = (volatile u16 *)(base + 0x26);
    *reg = (*reg & 0xfc00) | value;
}
