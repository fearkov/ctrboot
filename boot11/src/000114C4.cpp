// The nibble is picked with "cmp; moveq; movne" into r2. armcc folds a select of this shape into
// "adds r2, r0, #0; movne r2, #0xf"; the schedule barrier in the else arm keeps the two moves apart.
#pragma arm
#include "types.h"

// Sets the four low bits of the CP15 control register to all ones or all zeros; returns their previous value.
u32 FUN_000114C4(int enable)
{
    register u32 control __asm("cp15:0:c1:c0:0");
    u32 bits;
    if (enable != 0) {
        bits = 0xF;
    } else {
        __schedule_barrier();
        bits = 0;
    }
    u32 v = control;
    u32 old = v & 0xF;
    control = (v & ~0xFu) | bits;
    return old;
}
