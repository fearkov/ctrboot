// Built with the instruction scheduler off (#pragma O1): the dump issues the
// and/lsr pair back to back and the orr after it, which the ARM11 scheduler
// does not do (it moves the orr between the and and the lsr).
#pragma arm
#pragma O1
#include "types.h"

// Turns the instruction cache on in the CP15 control register; returns whether it was already on.
u32 FUN_000113F4()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = (v & 0x1000) >> 12;
    control = v | 0x1000;
    return old;
}
