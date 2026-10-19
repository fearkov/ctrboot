// Built at -O0: at every other level armcc folds the "& 1" after the "& 0x1C000000" (they share no bit) into a
// constant 0 and builds "mov r0, #0". The dump keeps the shift and both ANDs, in r0, with the parameter updated
// in place, which is what armcc does when it does not optimize.
#pragma arm
#pragma O0
#include "types.h"

// Writes the TLB lockdown register (CP15 c10, c0, 0): the victim number goes to bits 28:26, then the preserve
// bit (bit 0) is masked out of it, so the value written is always 0.
void FUN_00011D70(u32 victim)
{
    register u32 lockdown __asm("cp15:0:c10:c0:0");
    victim <<= 26;
    victim &= 0x1C000000;
    victim &= 1;
    lockdown = victim;
}
