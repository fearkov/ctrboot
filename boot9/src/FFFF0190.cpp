#pragma arm
#include "types.h"

// Returns the current program status register.
u32 FUN_FFFF0190(void)
{
    register u32 cpsr __asm("cpsr");
    return cpsr;
}
