// Enables interrupt irq and returns whether it already was. The read goes through a pointer and the write names the
// array again: that is what makes armcc load the address late, where the dump does.
#include "types.h"

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);

u32 FUN_00012590(s32 irq)
{
    u32 state = FUN_00011AC4();
    s32 index = irq / 32;
    s32 bit = irq % 32;
    volatile u32* enabled = (volatile u32*)0x17E01100 + index;
    u32 old = (*enabled >> bit) & 1;
    ((volatile u32*)0x17E01100)[index] = 1 << bit;
    FUN_00011AD8(state);
    return old;
}
