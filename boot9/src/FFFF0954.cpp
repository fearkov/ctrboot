// The dump does the whole read-mask-subtract-clamp-write in r3 and leaves r0 (the count) alone; armcc builds r1 for
// the read and r0 for the result, so the index is a register variable bound to r3. Each step is a statement of its
// own: folded into one expression, the masked value goes to r1 before the subtraction writes r3.
#pragma arm
#include "types.h"

register s32 gIndex __asm("r3");

// Takes count segments out of the data cache lockdown index (down to none).
void FUN_FFFF0954(s32 count)
{
    register u32 lockdown __asm("cp15:0:c9:c0:0");
    gIndex = lockdown;
    gIndex &= 3;
    gIndex -= count;
    if (gIndex < 0) {
        gIndex = 0;
    }
    lockdown = gIndex;
}
