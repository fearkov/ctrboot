#pragma arm
#include "types.h"

// Masks FIQs; returns the previous F bit (0x40 if they were already masked).
u32 FUN_00011B04()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old | 0x40;
    return old & 0x40;
}
