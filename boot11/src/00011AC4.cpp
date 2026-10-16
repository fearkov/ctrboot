#pragma arm
#include "types.h"

u32 FUN_00011AC4()
{
    register u32 cpsr __asm("cpsr");
    u32 old = cpsr;
    cpsr = old | 0x80;
    return old & 0x80;
}
