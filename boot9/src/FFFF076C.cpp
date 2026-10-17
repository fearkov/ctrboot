#include "types.h"

#pragma arm

// Masks IRQs and FIQs; returns the previous I and F bits.
u32 FUN_FFFF076C()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old | 0xC0;
    return old & 0xC0;
}
