#pragma arm
#include "types.h"

// Current processor mode (CPSR bits 4-0).
u32 FUN_00011A24()
{
    register u32 cpsr __asm("cpsr");
    return cpsr & 0x1F;
}
