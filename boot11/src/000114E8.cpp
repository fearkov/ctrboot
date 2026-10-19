// The dump zeroes r3, not r0, before the mcr: the zero is held in a register variable bound to r3.
#pragma arm
#include "types.h"

register u32 zero __asm("r3");

// Flushes the whole branch target cache.
void FUN_000114E8()
{
    register u32 flush_branch_target_cache __asm("cp15:0:c7:c5:6");
    zero = 0;
    flush_branch_target_cache = zero;
}
