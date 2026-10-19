#include "types.h"

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 mask);

u32 FUN_00012474(s32 irq)
{
    u32 state = FUN_00011AC4();
    s32 index = irq / 32;
    s32 bit = irq % 32;
    volatile u32* pending = (volatile u32*)0x17E01200 + index;
    u32 old = (*pending >> bit) & 1;
    ((volatile u32*)0x17E01280)[index] = 1 << bit;
    FUN_00011AD8(state);
    return old;
}
