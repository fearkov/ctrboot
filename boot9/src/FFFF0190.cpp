#pragma arm
#include "types.h"

u32 FUN_FFFF0190(void)
{
    register u32 cpsr __asm("cpsr");
    return cpsr;
}
