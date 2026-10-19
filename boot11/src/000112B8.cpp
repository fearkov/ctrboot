// The dump selects the bit before it reads the register, as "cmp r0, #0; moveq r2, #0; movne r2, #4". A
// single ?: (or an if/else) is folded by armcc into "adds r2, r0, #0; movne r2, #4", so the two arms are two
// separate conditional assignments, kept apart by a scheduling barrier (they stay adjacent and in front of the
// mrc). The second barrier keeps the ARM11 scheduler from moving the bic between the and/lsr pair.
#pragma arm
#include "types.h"

register u32 gBit __asm("r2");

// Turns the data cache on or off in the CP15 control register; returns whether it was on.
u32 FUN_000112B8(int enable)
{
    register u32 control __asm("cp15:0:c1:c0:0");
    if (enable == 0)
        gBit = 0;
    __schedule_barrier();
    if (enable != 0)
        gBit = 4;
    u32 v = control;
    u32 old = (v & 4) >> 2;
    __schedule_barrier();
    control = (v & ~4u) | gBit;
    return old;
}
