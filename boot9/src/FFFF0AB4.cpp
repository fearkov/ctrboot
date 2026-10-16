#pragma arm
#include "types.h"

void FUN_FFFF0AB4(void)
{
    register u32 invalidate_icache __asm("cp15:0:c7:c5:0");
    invalidate_icache = 0;
}
