// The dump selects the bit before it reads the register, as "cmp r0, #0; moveq r2, #0; movne r2, #4", which
// armcc folds into "adds r2, r0, #0; movne r2, #4" unless a schedule barrier keeps the two arms apart. The second
// barrier keeps the scheduler from moving the bic between the and/lsr pair.
#pragma arm
#include "types.h"

// Turns the data cache on or off in the CP15 control register; returns whether it was on.
u32 FUN_FFFF07C8(int enable)
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 bit;
    if (enable != 0) {
        bit = 4;
    } else {
        __schedule_barrier();
        bit = 0;
    }
    u32 v = control;
    u32 old = (v & 4) >> 2;
    __schedule_barrier();
    control = (v & ~4u) | bit;
    return old;
}
