#pragma arm
#include "types.h"

// Turns the MPU off in the CP15 control register.
void FUN_FFFF0C48()
{
    register u32 control __asm("cp15:0:c1:c0:0");
    control &= ~1u;
}
