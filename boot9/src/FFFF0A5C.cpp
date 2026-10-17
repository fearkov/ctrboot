#include "types.h"

#pragma arm

// Turns the instruction cache on in the CP15 control register; returns whether it was already on.
u32 FUN_FFFF0A5C()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 old = control;
    u32 enabled = (old & 0x1000) >> 12;
    control = old | 0x1000;
    return enabled;
}
