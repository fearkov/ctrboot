// The dump zeroes r3, not r0, before the mcr: the zero is held in a register variable bound to r3.
#pragma arm
#include "types.h"

register u32 zero __asm("r3");

// Clears the data cache lockdown register (no segment locked down).
void FUN_FFFF0948()
{
    register u32 lockdown __asm("cp15:0:c9:c0:0");
    zero = 0;
    lockdown = zero;
}
