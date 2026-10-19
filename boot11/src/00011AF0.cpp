#pragma arm
#include "types.h"

// Unmasks FIQs; returns the previous F bit (0x40 if they were masked).
u32 FUN_00011AF0()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old & ~0x40u;
    return old & 0x40;
}
