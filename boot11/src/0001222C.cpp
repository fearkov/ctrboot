#include "types.h"

extern "C" u32 FUN_00011AC4();
extern "C" u32 FUN_00011AD8(u32 state);

u8 FUN_0001222C(u32 irq, u32 priority)
{
    u32 state = FUN_00011AC4();
    volatile u8* reg = (volatile u8*)(irq + 0x17E01400);
    u32 old = *reg >> 4;
    *reg = priority << 4;
    FUN_00011AD8(state);
    return old;
}
