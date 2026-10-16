#include "types.h"

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);

u32 FUN_00012834(s32 irq)
{
    u32 state = FUN_00011AC4();
    s32 index = irq / 32;
    s32 bit = irq % 32;
    u32* reg = (u32*)0x1FFFFFF0 + index;
    u32 result = (*reg >> bit) & 1;
    *reg |= 1 << bit;
    FUN_00011AD8(state);
    return result;
}
