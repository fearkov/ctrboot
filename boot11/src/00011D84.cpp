#pragma arm
#include "types.h"

// Resets the TLB lockdown register (CP15 c10, c0, 0): nothing preserved, victim 0.
void FUN_00011D84()
{
    register u32 lockdown __asm("cp15:0:c10:c0:0");
    lockdown = 0;
}
