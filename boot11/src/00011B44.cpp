#pragma arm
#include "types.h"

// Masks IRQs and FIQs; returns the previous I and F bits.
u32 FUN_00011B44()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old | 0xC0;
    return old & 0xC0;
}
