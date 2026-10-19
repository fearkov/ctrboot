// The dump zeroes r3, not r0, before the mcr: the zero is held in a register variable bound to r3.
#pragma arm
#include "types.h"

register u32 zero __asm("r3");

// Flushes the prefetch buffer.
void FUN_00011490()
{
    register u32 flush_prefetch_buffer __asm("cp15:0:c7:c5:4");
    zero = 0;
    flush_prefetch_buffer = zero;
}
