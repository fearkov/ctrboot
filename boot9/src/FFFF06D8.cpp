#include "types.h"

#pragma arm

// Unmasks IRQs; returns the previous I bit (0x80 if they were masked).
u32 FUN_FFFF06D8()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old & ~0x80u;
    return old & 0x80;
}
