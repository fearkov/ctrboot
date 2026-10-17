#pragma arm
#include "types.h"

// Returns the current mode bits of the CPSR.
u32 FUN_FFFF0184(void)
{
    register u32 cpsr __asm("cpsr");
    return cpsr & 0x1F;
}
