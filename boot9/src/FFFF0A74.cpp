#include "types.h"

#pragma arm

// Turns the instruction cache off in the CP15 control register; returns whether it was on.
u32 FUN_FFFF0A74()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 old = control;
    u32 enabled = (old & 0x1000) >> 12;
    control = old & ~0x1000u;
    return enabled;
}
