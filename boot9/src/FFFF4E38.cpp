#include "types.h"

void FUN_FFFF4E38(u32 unit, u32 mode)
{
    u32 base = 0x10006000;
    if (unit != 1) {
        base = 0x10007000;
    }
    volatile u16 *reg = (volatile u16 *)(base + 0x28);
    switch (mode) {
    case 0:
        *reg = *reg | 0x8000;
        break;
    case 1:
        *reg = *reg & 0x7fff;
        break;
    }
}
