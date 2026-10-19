// Built with the instruction scheduler off (#pragma O1): the dump issues the
// and/lsr pair back to back and the orr after it, which the ARM11 scheduler of
// -O3 does not do (it moves the orr between the and and the lsr).
#pragma arm
#pragma O1
#include "types.h"

// Turns the data cache on in the CP15 control register; returns whether it was already on.
u32 FUN_00011288()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 v = control;
    u32 old = (v & 4) >> 2;
    control = v | 4;
    return old;
}
