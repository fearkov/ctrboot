#pragma arm
#include "types.h"

// Turns the MMU on: sets bit 0 of the CP15 control register.
void FUN_00011B70()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    control = control | 1;
}
