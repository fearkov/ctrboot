#pragma arm
#include "types.h"

void FUN_FFFF07F0(void)
{
    register u32 invalidate_dcache __asm("cp15:0:c7:c6:0");
    invalidate_dcache = 0;
}
