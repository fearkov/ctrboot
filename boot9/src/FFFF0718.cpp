#include "types.h"

#pragma arm

// Unmasks FIQs; returns the previous F bit (0x40 if they were masked).
u32 FUN_FFFF0718()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old & ~0x40u;
    return old & 0x40;
}
