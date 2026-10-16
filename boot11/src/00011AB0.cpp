#pragma arm
#include "types.h"

u32 FUN_00011AB0()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old & ~0x80u;
    return old & 0x80;
}
