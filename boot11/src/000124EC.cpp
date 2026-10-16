// Built for space: only -Ospace gives this code.
#pragma Ospace
#include "types.h"

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);

u32 FUN_000124EC(s32 irq)
{
    u32 state = FUN_00011AC4();
    s32 index = irq / 32;
    s32 bit = irq % 32;
    volatile u32* enabled = (volatile u32*)0x17E01100 + index;
    u32 old = (*enabled >> bit) & 1;
    ((volatile u32*)0x17E01180)[index] = 1 << bit;
    FUN_00011AD8(state);
    return old;
}
