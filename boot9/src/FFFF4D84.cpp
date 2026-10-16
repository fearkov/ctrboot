#include "types.h"

void FUN_FFFF4D84(u32 unit, u32 mode)
{
    u16 value;
    switch (mode) {
    case 0:
        value = 0;
        break;
    case 1:
        value = 1;
        break;
    default:
        return;
    }
    u32 base = 0x10006000;
    if (unit != 1) {
        base = 0x10007000;
    }
    volatile u16 *reg = (volatile u16 *)(base + 2);
    *reg = (*reg & 0xfffc) | value;
}
