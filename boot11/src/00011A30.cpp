#pragma arm
#include "types.h"

// Current program status register.
u32 FUN_00011A30()
{
    register u32 cpsr __asm("cpsr");
    return cpsr;
}
