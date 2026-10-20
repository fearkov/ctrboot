// The dump selects the bit before it reads the register, as "cmp r0, #0; moveq r2, #0; movne r2, #0x1000", which
// armcc folds into "adds r2, r0, #0; movne r2, #0x1000" unless a schedule barrier keeps the two arms apart. The
// second barrier keeps the scheduler from moving the bic between the and/lsr pair.
#pragma arm
#include "types.h"

// Turns the instruction cache on or off in the CP15 control register; returns whether it was on.
u32 FUN_FFFF0A8C(int enable)
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 bit;
    if (enable != 0) {
        bit = 0x1000;
    } else {
        __schedule_barrier();
        bit = 0;
    }
    u32 v = control;
    u32 old = (v & 0x1000) >> 12;
    __schedule_barrier();
    control = (v & ~0x1000u) | bit;
    return old;
}
