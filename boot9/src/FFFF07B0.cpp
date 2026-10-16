#include "types.h"

#pragma arm

// Turns the data cache off in the CP15 control register; returns whether it was on.
u32 FUN_FFFF07B0()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 old = control;
    u32 enabled = (old & 4) >> 2;
    control = old & ~4u;
    return enabled;
}
